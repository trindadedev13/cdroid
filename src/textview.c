#include "cdroid/textview.h"

#include "cdroid/activity.h"
#include "cdroid/internal/j.h"
#include "cdroid/internal/state.h"
#include "cdroid/internal/types.h"
#include "cdroid/log.h"

static i8
__cdroid_check_clazz__ (j_env *env)
{
  if (!__state__.__textview_clazz__)
  {
    /** get TextView class ref */
    j_class clazz = j_env_find_class (env, "android/widget/TextView");
    if (!clazz)
    {
      LOGE ("Failed to get TextView Class at %s\n", __func__);
      return -1;
    }
    __state__.__textview_clazz__ = j_env_new_global_ref (env, clazz);
    j_env_delete_local_ref (env, clazz);
  }
  return 0;
}

/**
 * Creates a new textview instance
 *
 * @param dest : The dest struct
 * @param act  : The Activity (for context)
 */
i8
cdroid_textview_new (struct cdroid_view *dest, struct cdroid_activity *act)
{
  j_method_id con;
  j_object ins;
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
  {
    LOGE ("Failed to get env at %s\n", __func__);
    return -1;
  }

  if (__cdroid_check_clazz__ (env) != 0)
    return -1;

  /** call textview class constructor */
  con = j_env_get_method_id (env, __state__.__textview_clazz__, "<init>",
                             "(Landroid/content/Context;)V");
  if (!con)
  {
    LOGE ("Failed to get TextView Class Constructor at %s\n", __func__);
    return -1;
  }

  ins = j_env_new_object (env, __state__.__textview_clazz__, con,
                          act->instance);
  if (!ins)
  {
    LOGE ("Failed to instanciate TextView at %s\n", __func__);
    return -1;
  }

  dest->type = VIEW_TEXT;
  dest->instance = j_env_new_global_ref (env, ins);
  j_env_delete_local_ref (env, ins);
  dest->__special__ = NULL;
  return 0;
}

/**
 * Defines the displayed text of textview
 *
 * @param self : The textview data struct
 * @param txt  : The new text
 */
i8
cdroid_textview_set_text (struct cdroid_view *self, const char *txt)
{
  j_method_id m_id;
  j_string java_text;
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
  {
    LOGE ("Failed to get env at %s\n", __func__);
    return -1;
  }

  /** get android.widget.TextView#setText(java.lang.CharSequence) */
  m_id = j_env_get_method_id (env, __state__.__textview_clazz__, "setText",
                              "(Ljava/lang/CharSequence;)V");
  if (!m_id)
  {
    LOGE ("Failed to get setText(java/lang/CharSequence) "
          "method id.\n");
    return -1;
  }

  /**
   * calls android.widget.TextView#setText(java.lang.String)
   * passing the new text
   */
  java_text = j_env_new_string_utf (env, txt);
  j_env_call_void_method (env, self->instance, m_id, java_text);
  j_env_delete_local_ref (env, java_text);
  return 0;
}
