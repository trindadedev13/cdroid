#include "cdroid/toast.h"

#include "cdroid/activity.h"
#include "cdroid/log.h"
#include "cdroid/internal/j.h"
#include "cdroid/internal/state.h"
#include "cdroid/internal/types.h"

static i8
__cdroid_check_clazz__ (j_env *env)
{
  if (!__state__.__toast_clazz__)
    {
      /** get Toast class ref */
      j_class clazz = j_env_find_class (env, "android/widget/Toast");
      if (!clazz)
        {
          LOGE ("Failed to get Toast Class at %s\n", __func__);
          return -1;
        }
      __state__.__toast_clazz__ = j_env_new_global_ref (env, clazz);
      j_env_delete_local_ref (env, clazz);
    }
  return 0;
}

/**
 * Makes a Toast Message instance. 
 *
 * @param dest     : Toast dest struct data
 * @param act      : The activity to show toast
 * @param msg      : The message to be displayed
 * @param duration : The duration of toast, see TOAST_DURATION_* macros.
 */
i8
cdroid_toast_new (struct cdroid_toast *dest, struct cdroid_activity *act, const char *msg, i8 duration)
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  if (__cdroid_check_clazz__ (env) != 0)
    return -1;

  /** get android.widget.Toast#makeText(android.content.Context, java.lang.CharSequence, int) */
  j_method_id m_id = j_env_get_static_method_id (
      env, __state__.__toast_clazz__, "makeText",
      "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
  if (!m_id)
    {
      LOGE ("Failed to get Toast#makeText(android.content.Context, java.lang.CharSequence, int) "
            "method id.\n");
      return -1;
    }

  j_string java_msg = j_env_new_string_utf (env, msg);
  j_object ins = j_env_call_static_object_method (env, __state__.__toast_clazz__, m_id, act->instance, java_msg, duration);
  if (!ins)
    {
      LOGE ("Failed to create Toast at %s.\n", __func__);
      return -1;
    }

  dest->instance = ins;
  return 0;
}

i8
cdroid_toast_show (struct cdroid_toast *self)
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  if (__cdroid_check_clazz__ (env) != 0)
    return -1;

  /** get android.widget.Toast#show() */
  j_method_id m_id = j_env_get_method_id (env, __state__.__toast_clazz__, "show", "()V");
  if (!m_id)
    {
      LOGE ("Failed to get Toast#show() method id.\n");
      return -1;
    }

  j_env_call_void_method (env, self->instance, m_id);
  return 0;
}