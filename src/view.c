#include "cdroid/view.h"

#include "cdroid/internal/ptr.h"
#include "cdroid/internal/state.h"
#include "cdroid/internal/viewhelper.h"
#include "cdroid/log.h"

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
    case VIEW_TEXT:
      return "TextView";
    case VIEW_LINEARLAYOUT:
      return "LinearLayout";
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
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  j_class v = j_env_find_class (env, "android/view/ViewGroup");
  if (!v)
    {
      LOGE ("Failed to get android/view/ViewGroup class ref "
            "at %s\n",
            __func__);
      return -1;
    }

  j_bool res = j_env_is_instanceof (env, self->instance, v);
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
  if (cdroid_view_is_viewgroup (self) != 0)
    {
      LOGE ("%s is not a ViewGroup.\n", cdroid_view_type_tostr (self->type));
      return -1;
    }

  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  /** get android.view.View#addView(android.view.View) */
  j_method_id m_id = j_env_get_method_id (env, self->clazz, "addView",
                                          "(Landroid/view/View;)V");
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
 * @param self     : The view
 * @param listener : The code to be executed (callback)
 */
i8
cdroid_view_set_click_listener (struct cdroid_view *self,
                                cdroid_view_click_listener listener)
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  /** here we create View.OnClickListener */
  j_object ptr = NULL;
  uiptr c_ptr = (uiptr)listener;

  if (__cdroid_ptr_new__ (c_ptr, 0, &ptr) != 0)
    {
      LOGE ("Failed to create Java Pointer at %s.\n", __func__);
      return -1;
    }

  j_object j_listener = NULL;
  if (__cdroid_viewhelper_create_click_listener__ (ptr, &j_listener) != 0)
    {
      LOGE ("Failed to create View.OnClickListener at %s.\n", __func__);
      return -1;
    }

  /** now we call View#setOnClickListener */

  /** get
   * android.view.View#setOnClickListener(android.view.View$OnClickListener) */
  j_method_id m_id
      = j_env_get_method_id (env, self->clazz, "setOnClickListener",
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