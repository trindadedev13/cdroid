#ifndef __cdroid_legacy_internal_j_h__
#define __cdroid_legacy_internal_j_h__

#include "cdroid/legacy/internal/types.h"

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

#define j_env_call_void_method(env, obj, id, ...)                             \
  (*env)->CallVoidMethod (env, obj, id, ##__VA_ARGS__)
#define j_env_call_long_method(env, obj, id, ...)                             \
  (*env)->CallLongMethod (env, obj, id, ##__VA_ARGS__)
#define j_env_call_static_object_method(env, clazz, id, ...)                  \
  (*env)->CallStaticObjectMethod (env, clazz, id, ##__VA_ARGS__)

#define j_env_new_object(env, clazz, id, ...)                                 \
  (*env)->NewObject (env, clazz, id, ##__VA_ARGS__)
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

#define CDROID_JAVA_PREFIX cdroid_app_legacy
#define CONCAT2(prefix, class, function) CONCAT1 (prefix, class, function)
#define CONCAT1(prefix, class, function) Java_##prefix##_##class##_##function
#define CDROID_JAVA(class, function)                                          \
  CONCAT2 (CDROID_JAVA_PREFIX, class, function)

CDROID_HEADER_END

#endif