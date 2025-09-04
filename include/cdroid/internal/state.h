#ifndef __cdroid_internal_state_h__
#define __cdroid_internal_state_h__

#include "cdroid/internal/j.h"

struct __cdroid_state__
{
  j_object activity;
  j_vm *jvm;
};

extern struct __cdroid_state__ __state__;

int __cdroid_state_get_env__ (void **);

#endif