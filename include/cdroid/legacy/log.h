#ifndef __cdroid_legacy_log_h__
#define __cdroid_legacy_log_h__

#include "cdroid/legacy/internal/types.h"

CDROID_HEADER_BEGIN

#include <android/log.h>

#ifndef LOGE
#define LOGE(fmt, ...)                                                        \
  __android_log_print (ANDROID_LOG_ERROR, "CDroid", fmt, ##__VA_ARGS__)
#endif

#ifndef LOGD
#define LOGD(fmt, ...)                                                        \
  __android_log_print (ANDROID_LOG_DEBUG, "CDroid", fmt, ##__VA_ARGS__)
#endif

#ifndef LOGI
#define LOGI(fmt, ...)                                                        \
  __android_log_print (ANDROID_LOG_INFO, "CDroid", fmt, ##__VA_ARGS__)
#endif

CDROID_HEADER_END

#endif