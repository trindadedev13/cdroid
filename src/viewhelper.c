#include "cdroid/internal/viewhelper.h"

#include "cdroid/internal/j.h"
#include "cdroid/internal/state.h"
#include "cdroid/internal/types.h"
#include "cdroid/log.h"

static j_class __viewhelper_clazz__ = NULL;

static i8
__cdroid_check_clazz__ (j_env *env)
{
  if (!__viewhelper_clazz__)
    {
      /** get ViewHelper class ref */
      j_class clazz = j_env_find_class (env, "cdroid/app/ViewHelper");
      if (!clazz)
        {
          LOGE ("Failed to get ViewHelper Class at %s\n", __func__);
          return -1;
        }
      __viewhelper_clazz__ = clazz;
    }
  return 0;
}

/**
 * Creates a View.OnClickListener instance.
 *
 * @param ptr  : The java Pointer class instance, it store the pointer for the
 * click fn.
 * @patam dest : The new View.OnClickListener mem dest.
 */
i8
__cdroid_viewhelper_create_click_listener__ (j_object ptr, j_object *dest)
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  if (__cdroid_check_clazz__ (env) != 0)
    return -1;

  /** get cdroid.app.ViewHelper#createClickListener(cdroid.app.Pointer) */
  j_method_id m_id = j_env_get_static_method_id (
      env, __viewhelper_clazz__, "createClickListener",
      "(Lcdroid/app/Pointer;)Landroid/view/View$OnClickListener;");
  if (!m_id)
    {
      LOGE ("Failed to get createClickListener(cdroid/app/View) "
            "method id.\n");
      return -1;
    }

  /**
   * calls cdroid.app.ViewHelper#createClickListener(cdroid.app.Pointer)
   * passing the view and pointer
   */
  j_object listener
      = j_env_call_static_object_method (env, __viewhelper_clazz__, m_id, ptr);
  if (!listener)
    {
      LOGE ("Failed to create View.OnClickListener at %s.\n", __func__);
      return -1;
    }
  *dest = listener;
  return 0;
}