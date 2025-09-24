#include "cdroid/internal/jni.h"
#include "cdroid/log.h"

extern "C" {

/** OnLoad and OnUnLoad Functions from Legacy */
extern jint __cdroid_legacy_jni_on_load__ (JavaVM *, void *);
extern void __cdroid_legacy_jni_on_unload__ (JavaVM *, void *);

/**
 * this function is called when Native Libraries is loaded with
 * System#loadLibrary(name).
 * should return the java version needed for the
 * native lib
 */
jint
JNI_OnLoad (JavaVM *jvm, void *__reserved__)
{
  return __cdroid_legacy_jni_on_load__ (jvm, __reserved__);
}

void
JNI_UnLoad (JavaVM *jvm, void *__reserved__)
{
  __cdroid_legacy_jni_on_unload__ (jvm, __reserved__);
}

/**
 * this function is called when activity creates.
 *
 * @env      : The JNI Environment
 * @clazz    : The clazz ref to caller
 * @act      : The activity instance
 */
JNIEXPORT jint JNICALL
CDROID_JAVA (Main, nativeInit) (JNIEnv *env, jclass clazz, jobject act,
                                  jstring lib_path, jstring fn_name)
{
  /** convert lib path java string to C Chars */
  const char *lib_path_str = env->GetStringUTFChars (lib_path, NULL);
  if (!lib_path_str)
    {
      LOGE ("Invalid library name provided. Please provided "
            "a valid one.");
      return -1;
    }

  /** convert main fn name java string to C Chars */
  const char *fn_name_str = env->GetStringUTFChars (fn_name, NULL);
  if (!fn_name_str)
    {
      LOGE ("Invalid function name provided. Please "
            "provided a valid one.");
      return -1;
    }

  /** release java strings */
  env->ReleaseStringUTFChars (lib_path, lib_path_str);
  env->ReleaseStringUTFChars (lib_path, fn_name_str);
  return 0;
}

}