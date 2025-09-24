#include "cdroid/legacy/activity.h"
#include "cdroid/legacy/internal/j.h"
#include "cdroid/legacy/internal/state.h"
#include "cdroid/legacy/log.h"

/**
 * this function is called when Native Libraries is loaded with
 * System#loadLibrary(name).
 * should return the java version needed for the
 * native lib
 */
j_int
__cdroid_legacy_jni_on_load__ (j_vm *jvm, void *__reserved__)
{
  __state__.jvm = jvm;
  return JNI_VERSION_1_6;
}

void
__cdroid_legacy_jni_on_unload__ (j_vm *jvm, void *__reserved__)
{
  __cdroid_state_delete__ ();
}

/**
 * this function is called when activity creates.
 *
 * @env      : The JNI Environment
 * @clazz    : The clazz ref to caller
 * @act      : The activity instance
 */
J_EXPORT j_int J_CALL
CDROID_JAVA (CDroid, nativeInit) (j_env *env, j_class clazz, j_object act,
                                  j_string lib_path, j_string fn_name)
{
  /** find android.app.Activity class ref */
  j_class act_class = j_env_find_class (env, "android/app/Activity");
  if (!act_class)
    {
      LOGE ("Failed to find android/app/Activity class at "
            "%s\n",
            __func__);
      return -1;
    }

  /** create cdroid android activity */
  if (cdroid_activity_new (&__state__.main_activity, act_class, act) != 0)
    {
      LOGE ("Failed to create main activity at %s\n", __func__);
      return -1;
    }

  /** convert lib path java string to C Chars */
  const char *lib_path_str = j_env_get_str_utf_chars (env, lib_path, NULL);
  if (!lib_path_str)
    {
      LOGE ("Invalid library name provided. Please provided "
            "a valid one.");
      return -1;
    }

  /** convert main fn name java string to C Chars */
  const char *fn_name_str = j_env_get_str_utf_chars (env, fn_name, NULL);
  if (!fn_name_str)
    {
      LOGE ("Invalid function name provided. Please "
            "provided a valid one.");
      return -1;
    }

  /** load and call the main function based on input */
  if (__cdroid_state_load_main__ (lib_path_str, fn_name_str) != 0)
    {
      LOGE ("Failed to run cdroid main at %s\n", __func__);
      return -1;
    }

  /** release java strings */
  j_env_release_str_utf_chars (env, lib_path, lib_path_str);
  j_env_release_str_utf_chars (env, lib_path, fn_name_str);
  return 0;
}