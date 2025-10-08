#include "cdroid/internal/viewhelper.h"

#include "cdroid/internal/callback.h"
#include "cdroid/internal/j.h"
#include "cdroid/internal/state.h"
#include "cdroid/internal/types.h"
#include "cdroid/log.h"

static i8
__cdroid_check_clazz__ (j_env *env)
{
  if (!__state__.__viewhelper_clazz__)
    {
      /** get ViewHelper class ref */
      j_class clazz = j_env_find_class (env, "cdroid/app/ViewHelper");
      if (!clazz)
        {
          LOGE ("Failed to get ViewHelper Class at %s\n", __func__);
          return -1;
        }
      __state__.__viewhelper_clazz__ = j_env_new_global_ref (env, clazz);
      j_env_delete_local_ref (env, clazz);
    }
  return 0;
}

/**
 * Creates a View.OnClickListener instance.
 *
 * @param callback : The callback ptr
 * @patam dest     : The new View.OnClickListener mem dest.
 */
i8
__cdroid_viewhelper_create_click_listener__ (
    struct __cdroid_callback_node__ *callback, j_object *dest)
{
  j_method_id m_id;
  j_long callback_ptr;
  j_object listener;
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  if (__cdroid_check_clazz__ (env) != 0)
    return -1;

  /** get cdroid.app.ViewHelper#createClickListener(long) */
  m_id = j_env_get_static_method_id (env, __state__.__viewhelper_clazz__,
                                     "createClickListener",
                                     "(J)Landroid/view/View$OnClickListener;");
  if (!m_id)
    {
      LOGE ("Failed to get createClickListener(long) "
            "method id.\n");
      return -1;
    }

  callback_ptr = (j_long)(uiptr)callback;

  /**
   * calls cdroid.app.ViewHelper#createClickListener(long)
   * passing the view and pointer
   */
  listener = j_env_call_static_object_method (
      env, __state__.__viewhelper_clazz__, m_id, callback_ptr);
  if (!listener)
    {
      LOGE ("Failed to create View.OnClickListener at %s.\n", __func__);
      return -1;
    }
  *dest = j_env_new_global_ref (env, listener);
  j_env_delete_local_ref (env, listener);
  return 0;
}
