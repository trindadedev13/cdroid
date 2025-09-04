#ifndef __cdroid_internal_j_h__
#define __cdroid_internal_j_h__

#include <jni.h>

/** types */
#define j_object jobject
#define j_class jclass
#define j_int jint

#define j_env JNIEnv
#define j_vm JavaVM

#define J_EXPORT JNIEXPORT
#define J_CALL JNICALL

/** functions */
/** funtions:env */
#define j_new_global_ref(env, obj) (*env)->NewGlobalRef (env, obj)
#define j_delete_global_ref(env, obj) (*env)->DeleteGlobalRef (env, obj)

/** functions:jvm */
#define j_vm_get_env(jvm, env, version) (*jvm)->GetEnv (jvm, env, version)
#define j_vm_attach_current_thread(jvm, penv, args)                           \
  (*jvm)->AttachCurrentThread (jvm, penv, args)

#endif