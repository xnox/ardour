// Generated by gtkmmproc -- DO NOT MODIFY!

#include <gtkmm/calendar.h>
#include <gtkmm/private/calendar_p.h>

#include <gtk/gtktypebuiltins.h>
// -*- c++ -*-
/* $Id$ */

/* 
 *
 * Copyright 1998-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gtk/gtkcalendar.h>

namespace Gtk
{

}


namespace
{

const Glib::SignalProxyInfo Calendar_signal_month_changed_info =
{
  "month_changed",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};


const Glib::SignalProxyInfo Calendar_signal_day_selected_info =
{
  "day_selected",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};


const Glib::SignalProxyInfo Calendar_signal_day_selected_double_click_info =
{
  "day_selected_double_click",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};


const Glib::SignalProxyInfo Calendar_signal_prev_month_info =
{
  "prev_month",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};


const Glib::SignalProxyInfo Calendar_signal_next_month_info =
{
  "next_month",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};


const Glib::SignalProxyInfo Calendar_signal_prev_year_info =
{
  "prev_year",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};


const Glib::SignalProxyInfo Calendar_signal_next_year_info =
{
  "next_year",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};

} // anonymous namespace

// static
GType Glib::Value<Gtk::CalendarDisplayOptions>::value_type()
{
  return gtk_calendar_display_options_get_type();
}


namespace Glib
{

Gtk::Calendar* wrap(GtkCalendar* object, bool take_copy)
{
  return dynamic_cast<Gtk::Calendar *> (Glib::wrap_auto ((GObject*)(object), take_copy));
}

} /* namespace Glib */

namespace Gtk
{


/* The *_Class implementation: */

const Glib::Class& Calendar_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &Calendar_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gtk_calendar_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:
  }

  return *this;
}

void Calendar_Class::class_init_function(void* g_class, void* class_data)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);

  klass->month_changed = &month_changed_callback;
  klass->day_selected = &day_selected_callback;
  klass->day_selected_double_click = &day_selected_double_click_callback;
  klass->prev_month = &prev_month_callback;
  klass->next_month = &next_month_callback;
  klass->prev_year = &prev_year_callback;
  klass->next_year = &next_year_callback;
}


void Calendar_Class::month_changed_callback(GtkCalendar* self)
{
  CppObjectType *const obj = dynamic_cast<CppObjectType*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));

  // Non-gtkmmproc-generated custom classes implicitly call the default
  // Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
  // generated classes can use this optimisation, which avoids the unnecessary
  // parameter conversions if there is no possibility of the virtual function
  // being overridden:
  if(obj && obj->is_derived_())
  {
    try // Trap C++ exceptions which would normally be lost because this is a C callback.
    {
      // Call the virtual member method, which derived classes might override.
      obj->on_month_changed();
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
  }
  else
  {
    BaseClassType *const base = static_cast<BaseClassType*>(
        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
    );

    // Call the original underlying C function:
    if(base && base->month_changed)
      (*base->month_changed)(self);
  }
}

void Calendar_Class::day_selected_callback(GtkCalendar* self)
{
  CppObjectType *const obj = dynamic_cast<CppObjectType*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));

  // Non-gtkmmproc-generated custom classes implicitly call the default
  // Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
  // generated classes can use this optimisation, which avoids the unnecessary
  // parameter conversions if there is no possibility of the virtual function
  // being overridden:
  if(obj && obj->is_derived_())
  {
    try // Trap C++ exceptions which would normally be lost because this is a C callback.
    {
      // Call the virtual member method, which derived classes might override.
      obj->on_day_selected();
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
  }
  else
  {
    BaseClassType *const base = static_cast<BaseClassType*>(
        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
    );

    // Call the original underlying C function:
    if(base && base->day_selected)
      (*base->day_selected)(self);
  }
}

void Calendar_Class::day_selected_double_click_callback(GtkCalendar* self)
{
  CppObjectType *const obj = dynamic_cast<CppObjectType*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));

  // Non-gtkmmproc-generated custom classes implicitly call the default
  // Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
  // generated classes can use this optimisation, which avoids the unnecessary
  // parameter conversions if there is no possibility of the virtual function
  // being overridden:
  if(obj && obj->is_derived_())
  {
    try // Trap C++ exceptions which would normally be lost because this is a C callback.
    {
      // Call the virtual member method, which derived classes might override.
      obj->on_day_selected_double_click();
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
  }
  else
  {
    BaseClassType *const base = static_cast<BaseClassType*>(
        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
    );

    // Call the original underlying C function:
    if(base && base->day_selected_double_click)
      (*base->day_selected_double_click)(self);
  }
}

void Calendar_Class::prev_month_callback(GtkCalendar* self)
{
  CppObjectType *const obj = dynamic_cast<CppObjectType*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));

  // Non-gtkmmproc-generated custom classes implicitly call the default
  // Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
  // generated classes can use this optimisation, which avoids the unnecessary
  // parameter conversions if there is no possibility of the virtual function
  // being overridden:
  if(obj && obj->is_derived_())
  {
    try // Trap C++ exceptions which would normally be lost because this is a C callback.
    {
      // Call the virtual member method, which derived classes might override.
      obj->on_prev_month();
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
  }
  else
  {
    BaseClassType *const base = static_cast<BaseClassType*>(
        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
    );

    // Call the original underlying C function:
    if(base && base->prev_month)
      (*base->prev_month)(self);
  }
}

void Calendar_Class::next_month_callback(GtkCalendar* self)
{
  CppObjectType *const obj = dynamic_cast<CppObjectType*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));

  // Non-gtkmmproc-generated custom classes implicitly call the default
  // Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
  // generated classes can use this optimisation, which avoids the unnecessary
  // parameter conversions if there is no possibility of the virtual function
  // being overridden:
  if(obj && obj->is_derived_())
  {
    try // Trap C++ exceptions which would normally be lost because this is a C callback.
    {
      // Call the virtual member method, which derived classes might override.
      obj->on_next_month();
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
  }
  else
  {
    BaseClassType *const base = static_cast<BaseClassType*>(
        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
    );

    // Call the original underlying C function:
    if(base && base->next_month)
      (*base->next_month)(self);
  }
}

void Calendar_Class::prev_year_callback(GtkCalendar* self)
{
  CppObjectType *const obj = dynamic_cast<CppObjectType*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));

  // Non-gtkmmproc-generated custom classes implicitly call the default
  // Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
  // generated classes can use this optimisation, which avoids the unnecessary
  // parameter conversions if there is no possibility of the virtual function
  // being overridden:
  if(obj && obj->is_derived_())
  {
    try // Trap C++ exceptions which would normally be lost because this is a C callback.
    {
      // Call the virtual member method, which derived classes might override.
      obj->on_prev_year();
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
  }
  else
  {
    BaseClassType *const base = static_cast<BaseClassType*>(
        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
    );

    // Call the original underlying C function:
    if(base && base->prev_year)
      (*base->prev_year)(self);
  }
}

void Calendar_Class::next_year_callback(GtkCalendar* self)
{
  CppObjectType *const obj = dynamic_cast<CppObjectType*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));

  // Non-gtkmmproc-generated custom classes implicitly call the default
  // Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
  // generated classes can use this optimisation, which avoids the unnecessary
  // parameter conversions if there is no possibility of the virtual function
  // being overridden:
  if(obj && obj->is_derived_())
  {
    try // Trap C++ exceptions which would normally be lost because this is a C callback.
    {
      // Call the virtual member method, which derived classes might override.
      obj->on_next_year();
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
  }
  else
  {
    BaseClassType *const base = static_cast<BaseClassType*>(
        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
    );

    // Call the original underlying C function:
    if(base && base->next_year)
      (*base->next_year)(self);
  }
}


Glib::ObjectBase* Calendar_Class::wrap_new(GObject* o)
{
  return manage(new Calendar((GtkCalendar*)(o)));

}


/* The implementation: */

Calendar::Calendar(const Glib::ConstructParams& construct_params)
:
  Gtk::Widget(construct_params)
{
  }

Calendar::Calendar(GtkCalendar* castitem)
:
  Gtk::Widget((GtkWidget*)(castitem))
{
  }

Calendar::~Calendar()
{
  destroy_();
}

Calendar::CppClassType Calendar::calendar_class_; // initialize static member

GType Calendar::get_type()
{
  return calendar_class_.init().get_type();
}

GType Calendar::get_base_type()
{
  return gtk_calendar_get_type();
}


Calendar::Calendar()
:
  Glib::ObjectBase(0), //Mark this class as gtkmmproc-generated, rather than a custom class, to allow vfunc optimisations.
  Gtk::Widget(Glib::ConstructParams(calendar_class_.init()))
{
  }

int Calendar::select_month(guint month, guint year)
{
  return gtk_calendar_select_month(gobj(), month, year);
}

void Calendar::select_day(guint day)
{
  gtk_calendar_select_day(gobj(), day);
}

int Calendar::mark_day(guint day)
{
  return gtk_calendar_mark_day(gobj(), day);
}

int Calendar::unmark_day(guint day)
{
  return gtk_calendar_unmark_day(gobj(), day);
}

void Calendar::clear_marks()
{
  gtk_calendar_clear_marks(gobj());
}

void Calendar::display_options(CalendarDisplayOptions flags)
{
  gtk_calendar_display_options(gobj(), ((GtkCalendarDisplayOptions)(flags)));
}

void Calendar::set_display_options(CalendarDisplayOptions flags)
{
  gtk_calendar_set_display_options(gobj(), ((GtkCalendarDisplayOptions)(flags)));
}

CalendarDisplayOptions Calendar::get_display_options() const
{
  return ((CalendarDisplayOptions)(gtk_calendar_get_display_options(const_cast<GtkCalendar*>(gobj()))));
}

void Calendar::get_date(guint& year, guint& month, guint& day) const
{
  gtk_calendar_get_date(const_cast<GtkCalendar*>(gobj()), &(year), &(month), &(day));
}

void Calendar::freeze()
{
  gtk_calendar_freeze(gobj());
}

void Calendar::thaw()
{
  gtk_calendar_thaw(gobj());
}


Glib::SignalProxy0< void > Calendar::signal_month_changed()
{
  return Glib::SignalProxy0< void >(this, &Calendar_signal_month_changed_info);
}

Glib::SignalProxy0< void > Calendar::signal_day_selected()
{
  return Glib::SignalProxy0< void >(this, &Calendar_signal_day_selected_info);
}

Glib::SignalProxy0< void > Calendar::signal_day_selected_double_click()
{
  return Glib::SignalProxy0< void >(this, &Calendar_signal_day_selected_double_click_info);
}

Glib::SignalProxy0< void > Calendar::signal_prev_month()
{
  return Glib::SignalProxy0< void >(this, &Calendar_signal_prev_month_info);
}

Glib::SignalProxy0< void > Calendar::signal_next_month()
{
  return Glib::SignalProxy0< void >(this, &Calendar_signal_next_month_info);
}

Glib::SignalProxy0< void > Calendar::signal_prev_year()
{
  return Glib::SignalProxy0< void >(this, &Calendar_signal_prev_year_info);
}

Glib::SignalProxy0< void > Calendar::signal_next_year()
{
  return Glib::SignalProxy0< void >(this, &Calendar_signal_next_year_info);
}


void Gtk::Calendar::on_month_changed()
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->month_changed)
    (*base->month_changed)(gobj());
}

void Gtk::Calendar::on_day_selected()
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->day_selected)
    (*base->day_selected)(gobj());
}

void Gtk::Calendar::on_day_selected_double_click()
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->day_selected_double_click)
    (*base->day_selected_double_click)(gobj());
}

void Gtk::Calendar::on_prev_month()
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->prev_month)
    (*base->prev_month)(gobj());
}

void Gtk::Calendar::on_next_month()
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->next_month)
    (*base->next_month)(gobj());
}

void Gtk::Calendar::on_prev_year()
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->prev_year)
    (*base->prev_year)(gobj());
}

void Gtk::Calendar::on_next_year()
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->next_year)
    (*base->next_year)(gobj());
}


} // namespace Gtk

