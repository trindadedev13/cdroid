#include "cdroid/linearlayout.h"

#include "cdroid/activity.h"
#include "cdroid/internal/j.h"
#include "cdroid/internal/state.h"
#include "cdroid/internal/types.h"
#include "cdroid/log.h"

/**
 * Creates a new linearlayout instance
 *
 * @param dest : The dest struct
 * @param act  : The Activity (for context)
 */
i8
cdroid_linearlayout_new (struct cdroid_view *dest, struct cdroid_activity *act)
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  /** get linearlayout class ref */
  j_class clazz = j_env_find_class (env, "android/widget/LinearLayout");
  if (!clazz)
    {
      LOGE ("Failed to get LinearLayout Class at %s\n", __func__);
      return -1;
    }

  /** call linearlayout class constructor */
  j_method_id con = j_env_get_method_id (env, clazz, "<init>",
                                         "(Landroid/content/Context;)V");
  if (!con)
    {
      LOGE ("Failed to get LinearLayout Class Constructor "
            "at %s\n",
            __func__);
      return -1;
    }

  j_object ins = j_env_new_object (env, clazz, con, act->instance);
  if (!ins)
    {
      LOGE ("Failed to instanciate LinearLayout at %s\n", __func__);
      return -1;
    }

  dest->type = VIEW_LINEARLAYOUT;
  dest->clazz = clazz;
  dest->instance = j_env_new_global_ref (env, ins);
  j_env_delete_local_ref (env, ins);
  dest->__special__ = NULL;
  return 0;
}

/**
 * Defines the linearlayout orientation
 *
 * @param self : The linearlayout data struct
 * @param txt  : The new orientation
 */
i8
cdroid_linearlayout_set_orientation (struct cdroid_view *self, i8 orientation)
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  /** get android.widget.LinearLayout#setOrientation(int) */
  j_method_id m_id
      = j_env_get_method_id (env, self->clazz, "setOrientation", "(I)V");
  if (!m_id)
    {
      LOGE ("Failed to get setOrientation(int) method id.\n");
      return -1;
    }

  /**
   * calls android.widget.LinearLayout#setOrientation(int)
   * passing the new orientation
   */
  j_env_call_void_method (env, self->instance, m_id, orientation);
  return 0;
}