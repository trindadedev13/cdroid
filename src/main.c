#include <android/log.h>
#include <jni.h>

#include "cdroid/internal/j.h"
#include "cdroid/internal/state.h"

#ifndef LOGE
// #define LOGE(fmt, ...) fprintf (stderr, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...)                                                        \
  __android_log_print (ANDROID_LOG_ERROR, "CDroid", fmt, ##__VA_ARGS__)
#endif

/**
 * this function is called when Native Libraries is loaded with
 * System#loadLibrary(name).
 * should return the java version needed for the
 * native lib
 */
j_int
JNI_OnLoad (j_vm *jvm, void *__reserved__)
{
  /** we dont need to initiaze anything yet */
  __state__.activity = NULL;
  __state__.jvm = jvm;
  return JNI_VERSION_1_6;
}

void
JNI_UnLoad (j_vm *jvm, void *__reserved__)
{
  j_env env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at JNI_UnLoad\n");
      return;
    }

  j_delete_global_ref (&env, __state__.activity);

  __state__.jvm = NULL;
  __state__.activity = NULL;
}

/**
 * this function is called when activity creates.
 *
 * @env      : The JNI Environment
 * @clazz    : The clazz ref to caller
 * @act      : The activity instance
 */
J_EXPORT void J_CALL
Java_cdroid_app_CDroid_init (j_env *env, j_class clazz, j_object ct)
{
  j_object c = j_new_global_ref (env, ct);
  __state__.activity = c;
}