/*
    Copyright (C) 2012 Paul Davis 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <dlfcn.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include <glib.h>
#include <glib/gstdio.h>
#include <glibmm/miscutils.h>
#include <glibmm/fileutils.h>

#include "ardour/linux_vst_support.h"
#include "pbd/basename.h"
#include "pbd/error.h"

#include "i18n.h"

/***********************************************************/
/* VSTFX - A set of modules for managing linux VST plugins */
/* vstfx.cc, vstfxwin.cc and vstfxinfofile.cc              */
/***********************************************************/

/*Simple error handler stuff for VSTFX*/

void vstfx_error (const char *fmt, ...)
{
	va_list ap;
	char buffer[512];

	va_start (ap, fmt);
	vsnprintf (buffer, sizeof(buffer), fmt, ap);
	vstfx_error_callback (buffer);
	va_end (ap);
}

/*default error handler callback*/

void default_vstfx_error_callback (const char *desc)
{
	PBD::error << desc << endmsg;
}

void (*vstfx_error_callback)(const char *desc) = &default_vstfx_error_callback;

/* --- */

/*Create and return a pointer to a new VSTFX handle*/

VSTHandle *
vstfx_handle_new ()
{
	VSTHandle* vstfx = (VSTHandle *) calloc (1, sizeof (VSTHandle));
	return vstfx;
}

/*Create and return a pointer to a new vstfx instance*/

VSTState *
vstfx_new ()
{
	VSTState* vstfx = (VSTState *) calloc (1, sizeof (VSTState));
	
	/*Mutexes*/
	
	pthread_mutex_init (&vstfx->lock, 0);
	pthread_cond_init (&vstfx->window_status_change, 0);
	pthread_cond_init (&vstfx->plugin_dispatcher_called, 0);
	pthread_cond_init (&vstfx->window_created, 0);

	/*Safe values*/
	
	vstfx->want_program = -1;
	vstfx->want_chunk = 0;
	vstfx->n_pending_keys = 0;
	vstfx->has_editor = 0;
	vstfx->program_set_without_editor = 0;
	vstfx->linux_window = 0;
	vstfx->linux_plugin_ui_window = 0;
	vstfx->eventProc = 0;
	vstfx->extra_data = 0;
	vstfx->want_resize = 0;
	
	return vstfx;
}

/*This loads the plugin shared library*/

void* vstfx_load_vst_library(const char* path)
{
	void* dll;
	char* full_path;
	char* envdup;
	char* lxvst_path;
	size_t len1;
	size_t len2;

	/*Try and load the shared library pointed to by the path - 
	NOTE: You have to give RTLD_LAZY or RTLD_NOW to dlopen or
	you get some occasional failures to load - dlerror reports
	invalid arguments*/

	if ((dll = dlopen (path, RTLD_LOCAL | RTLD_LAZY)) != 0) {
		return dll;
	}

	if (Glib::file_test (path, Glib::FILE_TEST_EXISTS)) {
		PBD::error << string_compose (_("Could not open existing LXVST plugin: %1"), dlerror()) << endmsg;
		return 0;
	}
		
	/*We didn't find the library so try and get the path specified in the
	env variable LXVST_PATH*/

	envdup = getenv ("LXVST_PATH");
	
	/*Path not specified - not much more we can do*/
	
	if (envdup == 0)
		return 0;
	
	/*Copy the path into envdup*/
		
	envdup = strdup (envdup);
	
	if (envdup == 0)
		return 0;
		
	len2 = strlen(path);

	/*Try all the possibilities in the path - deliminated by : */

	lxvst_path = strtok (envdup, ":");
	
	while (lxvst_path != 0)
	{
		vstfx_error ("\"%s\"", lxvst_path);
		len1 = strlen(lxvst_path);
		
		full_path = (char*)malloc(len1 + 1 + len2 + 1);
		memcpy(full_path, lxvst_path, len1);
		full_path[len1] = '/';
		memcpy(full_path + len1 + 1, path, len2);
		full_path[len1 + 1 + len2] = '\0';

		/*Try and load the library*/

		if ((dll = dlopen(full_path, RTLD_LOCAL | RTLD_LAZY)) != 0)
		{
			/*Succeeded */
			break;
		}
	
		/*Try again*/

		lxvst_path = strtok (0, ":");
	}

	/*Free the path*/

	free(envdup);

	return dll;
}

/*This loads up a plugin, given the path to its .so file and
 finds its main entry point etc*/

VSTHandle *
vstfx_load (const char *path)
{
	char* buf = 0;
	VSTHandle* fhandle;
	
	/*Create a new handle we can use to reference the plugin*/

	fhandle = vstfx_handle_new();
	
	/*See if we have .so appended to the path - if not we need to make sure it is added*/

	if (strstr (path, ".so") == 0)
	{

		/*Append the .so to the path - Make sure the path has enough space*/
		
		buf = (char *)malloc(strlen(path) + 4); //The .so and a terminating zero

		sprintf (buf, "%s.so", path);
		
		fhandle->nameptr = strdup (path);

	}
	else
	{
		/*We already have .so appened to the filename*/
		
		buf = strdup(path);
		
		fhandle->nameptr = strdup (path);
	}

	/* get a name for the plugin based on the path: ye old VST problem where
	   we don't know anything about its name until we load and instantiate the plugin
	   which we don't want to do at this point
	*/
	
	fhandle->name = strdup (PBD::basename_nosuffix (fhandle->nameptr).c_str());

	/*call load_vstfx_library to actually load the .so into memory*/

	if ((fhandle->dll = vstfx_load_vst_library (buf)) == 0)
	{
		vstfx_unload (fhandle);
		
		free(buf);
		
		return 0;
	}

	/*Find the main entry point into the plugin*/

	if ((fhandle->main_entry = (main_entry_t) dlsym(fhandle->dll, "main")) == 0)
	{
		/*If it can't be found, unload the plugin and return a 0 handle*/
		
		vstfx_unload (fhandle);
		
		free(buf);
		
		return 0;
	}

	free(buf);

	/*return the handle of the plugin*/

	return fhandle;
}

/*This unloads a plugin*/

int
vstfx_unload (VSTHandle* fhandle)
{
	if (fhandle->plugincnt)
	{
		/*Still have plugin instances - can't unload the library
		- actually dlclose keeps an instance count anyway*/
		
		return -1;
	}

	/*Valid plugin loaded?*/

	if (fhandle->dll)
	{
		dlclose(fhandle->dll);
		fhandle->dll = 0;
	}

	if (fhandle->nameptr)
	{
		free (fhandle->nameptr);
		free (fhandle->name);
	}
	
	/*Don't need the plugin handle any more*/
	
	free (fhandle);
	return 0;
}

/*This instantiates a plugin*/

VSTState *
vstfx_instantiate (VSTHandle* fhandle, audioMasterCallback amc, void* userptr)
{
	VSTState* vstfx = vstfx_new ();

	if(fhandle == 0)
	{
	    vstfx_error( "** ERROR ** VSTFX : The handle was 0\n" );
	    return 0;
	}

	if ((vstfx->plugin = fhandle->main_entry (amc)) == 0) 
	{
		vstfx_error ("** ERROR ** VSTFX : %s could not be instantiated :(\n", fhandle->name);
		free (vstfx);
		return 0;
	}
	
	vstfx->handle = fhandle;
	vstfx->plugin->user = userptr;
		
	if (vstfx->plugin->magic != kEffectMagic)
	{
		vstfx_error ("** ERROR ** VSTFX : %s is not a VST plugin\n", fhandle->name);
		free (vstfx);
		return 0;
	}
	
	vstfx->plugin->dispatcher (vstfx->plugin, effOpen, 0, 0, 0, 0);
	
	/*May or May not need to 'switch the plugin on' here - unlikely
	since FST doesn't and most plugins start up 'On' by default - I think this is the least of our worries*/
	
	//vstfx->plugin->dispatcher (vstfx->plugin, effMainsChanged, 0, 1, 0, 0);
	
	vstfx->vst_version = vstfx->plugin->dispatcher (vstfx->plugin, effGetVstVersion, 0, 0, 0, 0);
	
	vstfx->handle->plugincnt++;
	vstfx->wantIdle = 0;
	
	return vstfx;
}

/*Close a vstfx instance*/

void vstfx_close (VSTState* vstfx)
{
	vstfx_destroy_editor(vstfx);
	
	if(vstfx->plugin)
	{
		vstfx->plugin->dispatcher (vstfx->plugin, effMainsChanged, 0, 0, 0, 0);
		
		/*Calling dispatcher with effClose will cause the plugin's destructor to
		be called, which will also remove the editor if it exists*/
		
		vstfx->plugin->dispatcher (vstfx->plugin, effClose, 0, 0, 0, 0);
	}

	if (vstfx->handle->plugincnt)
			vstfx->handle->plugincnt--;
		
	/*vstfx_unload will unload the dll if the instance count allows - 
	we need to do this because some plugins keep their own instance count
	and (JUCE) manages the plugin UI in its own thread.  When the plugins
	internal instance count reaches zero, JUCE stops the UI thread and won't
	restart it until the next time the library is loaded.  If we don't unload
	the lib JUCE will never restart*/
	
	
	if (vstfx->handle->plugincnt)
	{
		return;
	}
	
	/*Valid plugin loaded - so we can unload it and 0 the pointer
	to it.  We can't free the handle here because we don't know what else
	might need it.  It should be / is freed when the plugin is deleted*/

	if (vstfx->handle->dll)
	{
		dlclose(vstfx->handle->dll); //dlclose keeps its own reference count
		vstfx->handle->dll = 0;
	}
	free(vstfx);
}


bool 
vstfx_save_state (VSTState* vstfx, char * filename)
{
	FILE* f = g_fopen (filename, "wb");
	if (f)
	{
		int bytelen;
		int numParams = vstfx->plugin->numParams;
		int i;
		char productString[64];
		char effectName[64];
		char vendorString[64];
		int success;

		/* write header */
		
		fprintf(f, "<plugin_state>\n");

		success = vstfx_call_dispatcher(vstfx, effGetProductString, 0, 0, productString, 0);
		
		if(success == 1)
		{
			fprintf (f, "  <check field=\"productString\" value=\"%s\"/>\n", productString);
		}
		else
		{
			printf ("No product string\n");
		}

		success = vstfx_call_dispatcher(vstfx, effGetEffectName, 0, 0, effectName, 0);
		
		if(success == 1)
		{
			fprintf (f, "  <check field=\"effectName\" value=\"%s\"/>\n", effectName);
			printf ("Effect name: %s\n", effectName);
		}
		else
		{
			printf ("No effect name\n");
		}

		success = vstfx_call_dispatcher(vstfx, effGetVendorString, 0, 0, vendorString, 0);
		
		if( success == 1 )
		{
			fprintf (f, "  <check field=\"vendorString\" value=\"%s\"/>\n", vendorString);
			printf ("Vendor string: %s\n", vendorString);
		}
		else
		{
			printf ("No vendor string\n");
		}


		if(vstfx->plugin->flags & 32 )
		{
			numParams = 0;
		}

		for(i=0; i < numParams; i++)
		{
			float val;
			
			pthread_mutex_lock( &vstfx->lock );
			val = vstfx->plugin->getParameter(vstfx->plugin, i );
			pthread_mutex_unlock( &vstfx->lock );
			fprintf( f, "  <param index=\"%d\" value=\"%f\"/>\n", i, val );
		}

		if(vstfx->plugin->flags & 32 )
		{
			printf( "getting chunk...\n" );
			void * chunk;
			bytelen = vstfx_call_dispatcher(vstfx, 23, 0, 0, &chunk, 0 );
			printf( "got tha chunk..\n" );
			if( bytelen )
			{
				if( bytelen < 0 )
				{
					printf( "Chunke len < 0 !!! Not saving chunk.\n" );
				}
				else
				{
					//char *encoded = g_base64_encode( chunk, bytelen );
					//fprintf( f, "  <chunk size=\"%d\">\n    %s\n  </chunk>\n", bytelen, encoded );
					//g_free( encoded );
				}
			}
		} 

		fprintf( f, "</plugin_state>\n" );
		fclose( f );
	}
	else
	{
		printf ("Could not open state file\n");
		return false;
	}
	return true;
}

/*Set up a call to the plugins 'dispatcher' function*/

int vstfx_call_dispatcher (VSTState* vstfx, int opcode, int index, int val, void *ptr, float opt) 
{
	pthread_mutex_lock (&vstfx->lock);
	
	/*Set up the opcode and parameters*/
	
	vstfx->dispatcher_opcode = opcode;
	vstfx->dispatcher_index = index;
	vstfx->dispatcher_val = val;
	vstfx->dispatcher_ptr = ptr;
	vstfx->dispatcher_opt = opt;
	
	/*Signal that we want the call to happen*/
	
	vstfx->dispatcher_wantcall = 1;

	/*Wait for the call to happen*/

	pthread_cond_wait (&vstfx->plugin_dispatcher_called, &vstfx->lock);
	pthread_mutex_unlock (&vstfx->lock);

	/*Return the result*/
	
	return vstfx->dispatcher_retval;
}
