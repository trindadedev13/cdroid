#ifndef __cdroid_jni_h__
#define __cdroid_jni_h__

#include <jni.h>

#define CDROID_JAVA_PREFIX cdroid_app
#define CONCAT2(prefix, class, function) CONCAT1 (prefix, class, function)
#define CONCAT1(prefix, class, function) Java_##prefix##_##class##_##function
#define CDROID_JAVA(class, function)                                          \
  CONCAT2 (CDROID_JAVA_PREFIX, class, function)

#endif