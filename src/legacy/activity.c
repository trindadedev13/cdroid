#include "cdroid/legacy/activity.h"

#include "cdroid/legacy/internal/state.h"
#include "cdroid/legacy/log.h"

/**
 * Creates a new activity from a class ref and instance.
 *
 * @param dest     : The dest struct
 * @param clazz    : The class ref
 * @param instance : The instance object
 */
i8
cdroid_activity_new (struct cdroid_activity *dest, j_class clazz,
                     j_object instance)
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  /** store global ref of activity instance object */
  dest->instance = j_env_new_global_ref (env, instance);
  dest->clazz = j_env_new_global_ref (env, clazz);
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
 * 0  => Valid
 * -1 => Instance OR class ref is invalid
 * ‐2 => Instance AND class ref is invalid
 */
i8
cdroid_activity_is_valid (struct cdroid_activity *self)
{
  i8 res = 0;
  if (!self->instance)
    --res;
  if (!self->clazz)
    --res;
  return res;
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
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  /** get android.app.Activity#setContent(android.view.View) */
  j_method_id m_id = j_env_get_method_id (env, self->clazz, "setContentView",
                                          "(Landroid/view/View;)V");
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