#ifndef __vstfx_h__
#define __vstfx_h__

#include <setjmp.h>
#include <signal.h>
#include <pthread.h>
#include <stdio.h>

/******************************************************************************************/
/*VSTFX - an engine to manage native linux VST plugins - derived from FST for Windows VSTs*/
/******************************************************************************************/
 
extern void (*vstfx_error_callback)(const char *msg);

void vstfx_set_error_function (void (*func)(const char *));

void  vstfx_error (const char *fmt, ...);

/*We will use the vestige headers*/

#define VESTIGE_HEADER

#include <ardour/vestige/aeffectx.h>

typedef struct _VSTFX VSTFX;
typedef struct _VSTFXHandle VSTFXHandle;
typedef struct _VSTFXInfo VSTFXInfo;
typedef struct _VSTFXKey VSTFXKey;


/*Struct to contain the info about a plugin*/

struct _VSTFXInfo 
{
    char *name;
    char *creator;
    int UniqueID;
    char *Category;
    
    int numInputs;
    int numOutputs;
    int numParams;

    int wantMidi;
    int wantEvents;
    int hasEditor;
    int canProcessReplacing;

    /* i think we should save the parameter Info Stuff soon. */
    // struct VstParameterInfo *infos;
    char **ParamNames;
    char **ParamLabels;
};

/*The AEffect which contains the info about a plugin instance*/

typedef struct AEffect * (*main_entry_t)(audioMasterCallback);

/*A handle used to identify a plugin to vstfx*/

struct _VSTFXHandle
{
    void*    dll;
    char*    name;
    char*    nameptr; /* ptr returned from strdup() etc. */
	
    main_entry_t main_entry;

    int plugincnt;
};

/*No key forwarding enabled in vstfx at the moment - maybe
  not required*/

struct _VSTFXKey
{
    /** virtual-key code, or 0 if this _VSTFXKey is a `character' key */
    int special;
    /** `character' key, or 0 if this _VSTFXKey is a virtual-key */
    int character;
};



/*Structure used to describe the instance of VSTFX responsible for
  a particular plugin instance.  These are connected together in a 
  linked list*/

struct _VSTFX 
{
    struct AEffect*    plugin;
    int      	window;            /* The plugin's parent X11 XWindow */
    int         plugin_ui_window;  /*The ID of the plugin UI window created by the plugin*/
    int         xid;               /* X11 XWindow */
	
    int         want_resize;       /*Set to signal the plugin resized its UI*/
    void*       extra_data;        /*Pointer to any extra data*/
	
    void* event_callback_thisptr;
    void (*eventProc) (void* event);
	
    VSTFXHandle*  handle;
	
    int		width;
    int 	height;
    int		wantIdle;
    int		destroy;
    int		vst_version;
    int 	has_editor;
	
    int		program_set_without_editor;

    int		want_program;
    int 	want_chunk;
    int		n_pending_keys;
    unsigned char* wanted_chunk;
    int 	wanted_chunk_size;
    int		current_program;
    float	*want_params;
    float	*set_params;
	
    VSTFXKey	pending_keys[16];

    int		dispatcher_wantcall;
    int		dispatcher_opcode;
    int		dispatcher_index;
    int		dispatcher_val;
    void *	dispatcher_ptr;
    float	dispatcher_opt;
    int		dispatcher_retval;

    struct _VSTFX* next;
    pthread_mutex_t lock;
    pthread_cond_t  window_status_change;
    pthread_cond_t  plugin_dispatcher_called;
    pthread_cond_t  window_created;
    int             been_activated;
};

/*API to vstfx*/

extern int	    vstfx_launch_editor(VSTFX* vstfx);
extern int          vstfx_init (void* possible_hmodule);
extern void         vstfx_exit ();
extern VSTFXHandle* vstfx_load (const char*);
extern int          vstfx_unload (VSTFXHandle*);
extern VSTFX*       vstfx_instantiate (VSTFXHandle*, audioMasterCallback amc, void* userptr);
extern void         vstfx_close (VSTFX*);

extern int          vstfx_create_editor (VSTFX* vstfx);
extern int          vstfx_run_editor (VSTFX*);
extern void         vstfx_destroy_editor (VSTFX*);
extern int          vstfx_get_XID (VSTFX*);
extern void         vstfx_move_window_into_view (VSTFX*);

extern VSTFXInfo*   vstfx_get_info (char *dllpathname);
extern void         vstfx_free_info (VSTFXInfo *info);
extern void         vstfx_event_loop_remove_plugin (VSTFX* fst);
extern int          vstfx_call_dispatcher(VSTFX *vstfx, int opcode, int index, int val, void *ptr, float opt );

/** Load a plugin state from a file.**/

extern int vstfx_load_state (VSTFX* vstfx, char * filename);

/** Save a plugin state to a file.**/

extern int vstfx_save_state (VSTFX* vstfx, char * filename);


#endif /* __vstfx_h__ */