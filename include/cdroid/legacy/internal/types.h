#ifndef __cdroid_legacy_types_h__
#define __cdroid_legacy_types_h__

#ifdef __cplusplus
#define CDROID_HEADER_BEGIN                                                   \
  extern "C"                                                                  \
  {
#define CDROID_HEADER_END }
#else
#define CDROID_HEADER_BEGIN
#define CDROID_HEADER_END
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t ui8;
typedef uint16_t ui16;
typedef uint32_t ui32;
typedef uint64_t ui64;
typedef uintptr_t uiptr;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#ifndef NULL
#define NULL ((void *)0)
#endif

#define mem_set(s, c, size) memset (s, c, size)
#define mem_free(p) free (p)
#define str_dup(s) strdup (s)

#endif