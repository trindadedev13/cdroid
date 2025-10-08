#ifndef __cdroid_log_h__
#define __cdroid_log_h__

#include "cdroid/internal/types.h"

CDROID_HEADER_BEGIN

#include <android/log.h>

static void
LOGE (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  __android_log_vprint (ANDROID_LOG_ERROR, "CDroid", fmt, args);
  va_end (args);
}

static void
LOGD (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  __android_log_vprint (ANDROID_LOG_DEBUG, "CDroid", fmt, args);
  va_end (args);
}

static void
LOGI (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  __android_log_vprint (ANDROID_LOG_INFO, "CDroid", fmt, args);
  va_end (args);
}

CDROID_HEADER_END

#endif
