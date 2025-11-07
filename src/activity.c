#include "cdroid/activity.h"

#include "cdroid/internal/state.h"
#include "cdroid/log.h"

static i8
__cdroid_check_clazz__ (j_env *env)
{
  if (!__state__.__activity_clazz__)
  {
    /** get Activity class ref */
    j_class clazz = j_env_find_class (env, "android/app/Activity");
    if (!clazz)
    {
      LOGE ("Failed to get Activity Class at %s\n", __func__);
      return -1;
    }
    __state__.__activity_clazz__ = j_env_new_global_ref (env, clazz);
    j_env_delete_local_ref (env, clazz);
  }
  return 0;
}

/**
 * Creates a new activity from a class ref and instance.
 *
 * @param dest     : The dest struct
 * @param clazz    : The class ref
 * @param instance : The instance object
 */
i8
cdroid_activity_new (struct cdroid_activity *dest, j_object instance)
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
  {
    LOGE ("Failed to get env at %s\n", __func__);
    return -1;
  }

  if (__cdroid_check_clazz__ (env) != 0)
    return -1;

  dest->instance = j_env_new_global_ref (env, instance);
  return 0;
}

/**
 * Deletes the global allocate data of activity
 *
 * @param self : The activity instance
 */
i8
cdroid_activity_delete (struct cdroid_activity *self)
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
  {
    LOGE ("Failed to get env at %s\n", __func__);
    return -1;
  }

  /** delete global ref of activity object instance */
  j_env_delete_global_ref (env, self->instance);
  return 0;
}

/**
 * Returns 0 if the activity is valid
 *
 */
i8
cdroid_activity_is_valid (struct cdroid_activity *self)
{
  if (!self->instance)
    return -1;
  return 0;
}

/**
 * Defines the content view of activity
 *
 * Use it to define the screen content
 *
 * @param self    : The Activity
 * @param content : The content
 */
i8
cdroid_activity_set_contentview (struct cdroid_activity *self,
                                 struct cdroid_view *content)
{
  j_method_id m_id;
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
  {
    LOGE ("Failed to get env at %s\n", __func__);
    return -1;
  }

  /** get android.app.Activity#setContent(android.view.View) */
  m_id = j_env_get_method_id (env, __state__.__activity_clazz__,
                              "setContentView", "(Landroid/view/View;)V");
  if (!m_id)
  {
    LOGE ("Failed to get setContentView(android/view/View) "
          "method id.\n");
    return -1;
  }

  /**
   * calls android.app.Activity#setContent(android.view.View)
   * passing the content instance
   */
  j_env_call_void_method (env, self->instance, m_id, content->instance);
  return 0;
}
