#include "cdroid/internal/ptr.h"

#include "cdroid/internal/j.h"
#include "cdroid/internal/state.h"
#include "cdroid/internal/types.h"
#include "cdroid/log.h"

static j_class __ptr_clazz__ = NULL;

static i8
__cdroid_check_clazz__ (j_env *env)
{
  if (!__ptr_clazz__)
    {
      /** get Pointer class ref */
      j_class clazz = j_env_find_class (env, "cdroid/app/Pointer");
      if (!clazz)
        {
          LOGE ("Failed to get Pointer Class at %s\n", __func__);
          return -1;
        }
      __ptr_clazz__ = clazz;
    }
  return 0;
}

/**
 * Create a Pointer.java object
 *
 * @param raw  : The raw pointer
 * @param is_gn : Indicates if its a function (0 = true, else false)
 * @param dest : The new createf object
 */
i8
__cdroid_ptr_new__ (uiptr raw, i8 is_fn, j_object *dest)
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  if (__cdroid_check_clazz__ (env) != 0)
    return -1;

  /** call Pointer class constructor */
  j_method_id con
      = j_env_get_method_id (env, __ptr_clazz__, "<init>", "(JZ)V");
  if (!con)
    {
      LOGE ("Failed to get Pointer Class Constructor "
            "at %s\n",
            __func__);
      return -1;
    }

  j_object ins = j_env_new_object (env, __ptr_clazz__, con, (j_long)raw,
                                   (is_fn == 0) ? JNI_TRUE : JNI_FALSE);
  if (!ins)
    {
      LOGE ("Failed to instanciate Pointer at %s\n", __func__);
      return -1;
    }

  *dest = ins;
  return 0;
}

/**
 * Calls a native function from a native ptr.
 *
 * @param self : The pointer java object
 */
J_EXPORT j_int J_CALL
CDROID_JAVA (Pointer, nativeCall) (j_env *env, j_object instance)
{
  if (__cdroid_check_clazz__ (env) != 0)
    return -1;

  /** get cdroid.app.Pointer#getRaw(): long */
  j_method_id m_id = j_env_get_method_id (env, __ptr_clazz__, "getRaw", "()J");
  if (!m_id)
    {
      LOGE ("Failed to get nativeCall() method id.\n");
      return -1;
    }

  j_long jraw = j_env_call_long_method (env, instance, m_id);
  if (jraw == 0 || (jraw & 0xF) != 0)
    {
      LOGD ("Invalid pointer at address: 0x%lx\n", (uiptr)jraw);
      return -1;
    }

  cdroid_view_click_listener raw = (cdroid_view_click_listener)(uiptr)jraw;
  raw ();
  return 0;
}