#ifndef __cdroid_internal_state_h__
#define __cdroid_internal_state_h__

#include "cdroid/internal/types.h"

CDROID_HEADER_BEGIN

#include "cdroid/activity.h"
#include "cdroid/internal/j.h"

struct __cdroid_state__
{
  struct cdroid_activity main_activity;
  j_vm *jvm;
};

extern struct __cdroid_state__ __state__;

i8 __cdroid_state_get_env__ (void **);

int __cdroid_state_load_main__ (const char *, const char *);

CDROID_HEADER_END

#endif