#include "cdroid/view.h"

#include "cdroid/internal/state.h"
#include "cdroid/internal/viewhelper.h"
#include "cdroid/log.h"
#include <sys/cdefs.h>

static i8
__cdroid_get_view_clazz__ (struct cdroid_view *self, j_class *dest)
{
  j_class clazz;
  switch (self->type)
  {
  case VIEW_LINEARLAYOUT:
    clazz = __state__.__linearlayout_clazz__;
    break;
  case VIEW_TEXT:
    clazz = __state__.__textview_clazz__;
    break;
  case VIEW_BUTTON:
    clazz = __state__.__button_clazz__;
    break;
  default:
    return -1;
  };
  *dest = clazz;
  return 0;
}

/**
 * Returns the string value of type enum
 */
const char *
cdroid_view_type_tostr (enum cdroid_view_type type)
{
  switch (type)
  {
  case VIEW:
    return "View";
  case VIEW_LINEARLAYOUT:
    return "LinearLayout";
  case VIEW_TEXT:
    return "TextView";
  default:
    return "Unknown View";
  };
}

/**
 * Checks if the view is a viewgroup
 *
 * Returns 0  if it's a viewgroup
 * Returns -1 if error or it's not a viewgroup.
 *
 * @param self : The view to be checked
 */
i8
cdroid_view_is_viewgroup (struct cdroid_view *self)
{
  j_class v;
  j_bool res;
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
  {
    LOGE ("Failed to get env at %s\n", __func__);
    return -1;
  }

  v = j_env_find_class (env, "android/view/ViewGroup");
  if (!v)
  {
    LOGE ("Failed to get android/view/ViewGroup class ref "
          "at %s\n",
          __func__);
    return -1;
  }

  res = j_env_is_instanceof (env, self->instance, v);
  return (res == J_TRUE) ? 0 : -1;
}

/**
 * Adds a new view inside a viewgroup
 *
 * it'll add the ```child``` view in ```self```
 * if it's a viewgroup instance.
 *
 * @param self  : The parent view to be added
 * @param child : The child view to be added
 */
i8
cdroid_view_add_view (struct cdroid_view *self, struct cdroid_view *child)
{
  j_method_id m_id;
  j_class clazz;
  j_env *env = NULL;

  if (cdroid_view_is_viewgroup (self) != 0)
  {
    LOGE ("%s is not a ViewGroup.\n", cdroid_view_type_tostr (self->type));
    return -1;
  }

  if (__cdroid_state_get_env__ ((void **)&env) != 0)
  {
    LOGE ("Failed to get env at %s\n", __func__);
    return -1;
  }

  if (__cdroid_get_view_clazz__ (self, &clazz) != 0)
  {
    LOGE ("Failed to get valid clazz for view: %s at %s\n",
          cdroid_view_type_tostr (self->type), __func__);
    return -1;
  }

  /** get android.view.View#addView(android.view.View) */
  m_id = j_env_get_method_id (env, clazz, "addView", "(Landroid/view/View;)V");
  if (!m_id)
  {
    LOGE ("Failed to get addView(android/view/View) method id.\n");
    return -1;
  }

  /**
   * calls android.view.View#addView(android.view.View)
   * passing the content instance
   */
  j_env_call_void_method (env, self->instance, m_id, child->instance);

  LOGD ("Added %s at %s.\n", cdroid_view_type_tostr (child->type),
        cdroid_view_type_tostr (self->type));

  return 0;
}

/**
 * Defines the click event listener of a view.
 *
 *
 * @param self  : The view
 * @param fn    : The function to be executed (callback)
 * @param udata : User data
 */
i8
cdroid_view_set_click_listener (struct cdroid_view *self,
                                __cdroid_callback_fn__ fn, void *udata)
{
  struct __cdroid_callback_node__ *node;
  j_object j_listener;
  j_method_id m_id;
  j_class clazz;

  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
  {
    LOGE ("Failed to get env at %s\n", __func__);
    return -1;
  }

  __cdroid_callback_node_register__ (fn, udata, &node);

  if (__cdroid_viewhelper_create_click_listener__ (node, &j_listener) != 0)
  {
    LOGE ("Failed to create View.OnClickListener at %s.\n", __func__);
    return -1;
  }

  if (__cdroid_get_view_clazz__ (self, &clazz) != 0)
  {
    LOGE ("Failed to get valid clazz for view: %s at %s\n",
          cdroid_view_type_tostr (self->type), __func__);
    return -1;
  }

  /** now we call View#setOnClickListener */

  /** get
   * android.view.View#setOnClickListener(android.view.View$OnClickListener) */
  m_id = j_env_get_method_id (env, clazz, "setOnClickListener",
                              "(Landroid/view/View$OnClickListener;)V");
  if (!m_id)
  {
    LOGE ("Failed to get setOnClickListener(cdroid/app/View) "
          "method id.\n");
    return -1;
  }

  /**
   * calls
   * android.view.View#setOnClickListener(android.view.View$OnClickListener)
   * passing the View click listener
   */
  j_env_call_void_method (env, self->instance, m_id, j_listener);

  return 0;
}
