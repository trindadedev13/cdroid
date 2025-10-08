#ifndef __cdroid_internal_j_h__
#define __cdroid_internal_j_h__

#include "cdroid/internal/types.h"

CDROID_HEADER_BEGIN

#include <jni.h>

/** types */
#define j_object jobject
#define j_class jclass
#define j_int jint
#define j_method_id jmethodID
#define j_string jstring
#define j_bool jboolean
#define j_long jlong

#define j_env JNIEnv
#define j_vm JavaVM

#define J_EXPORT JNIEXPORT
#define J_CALL JNICALL
#define J_TRUE JNI_TRUE
#define J_FALSE JNI_FALSE

/** functions */
/** funtions:env */
#define j_env_new_global_ref(env, obj) (*env)->NewGlobalRef (env, obj)
#define j_env_delete_global_ref(env, obj) (*env)->DeleteGlobalRef (env, obj)
#define j_env_find_class(env, name) (*env)->FindClass (env, name)

#define j_env_get_method_id(env, clazz, name, sign)                           \
  (*env)->GetMethodID (env, clazz, name, sign)
#define j_env_get_static_method_id(env, clazz, name, sign)                    \
  (*env)->GetStaticMethodID (env, clazz, name, sign)

#define __VA_END__ () va_end (args)

/**
 * Functions that have variadics arguments.
 * we do this because C90 don't support variadic in macros.
 */

static void
j_env_call_void_method (j_env *env, j_object obj, j_method_id id, ...)
{
  va_list args;
  va_start (args, id);
  (*env)->CallVoidMethodV (env, obj, id, args);
  va_end (args);
}

static j_long
j_env_call_long_method (j_env *env, j_object obj, j_method_id id, ...)
{
  j_long ret;
  va_list args;
  va_start (args, id);
  ret = (*env)->CallLongMethodV (env, obj, id, args);
  va_end (args);
  return ret;
}

static j_object
j_env_call_static_object_method (j_env *env, j_class clazz, j_method_id id,
                                 ...)
{
  j_object ret;
  va_list args;
  va_start (args, id);
  ret = (*env)->CallStaticObjectMethodV (env, clazz, id, args);
  va_end (args);
  return ret;
}

static j_object
j_env_new_object (j_env *env, j_class clazz, j_method_id id, ...)
{
  j_object ret;
  va_list args;
  va_start (args, id);
  ret = (*env)->NewObjectV (env, clazz, id, args);
  va_end (args);
  return ret;
}

#define j_env_get_str_utf_chars(env, js, v)                                   \
  (*env)->GetStringUTFChars (env, js, v)
#define j_env_release_str_utf_chars(env, str, chars)                          \
  (*env)->ReleaseStringUTFChars (env, str, chars)

#define j_env_new_string_utf(env, chars) (*env)->NewStringUTF (env, chars)
#define j_env_delete_local_ref(env, ref) (*env)->DeleteLocalRef (env, ref)
#define j_env_is_instanceof(env, obj, clazz)                                  \
  (*env)->IsInstanceOf (env, obj, clazz)

/** functions:jvm */
#define j_vm_get_env(jvm, env, version) (*jvm)->GetEnv (jvm, env, version)
#define j_vm_attach_current_thread(jvm, penv, args)                           \
  (*jvm)->AttachCurrentThread (jvm, penv, args)

#define CDROID_JAVA_PREFIX cdroid_app
#define CONCAT2(prefix, class, function) CONCAT1 (prefix, class, function)
#define CONCAT1(prefix, class, function) Java_##prefix##_##class##_##function
#define CDROID_JAVA(class, function)                                          \
  CONCAT2 (CDROID_JAVA_PREFIX, class, function)

CDROID_HEADER_END

#endif
