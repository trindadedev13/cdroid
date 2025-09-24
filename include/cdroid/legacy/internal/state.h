#ifndef __cdroid_legacy_internal_state_h__
#define __cdroid_legacy_internal_state_h__

#include "cdroid/legacy/internal/types.h"

CDROID_HEADER_BEGIN

#include "cdroid/legacy/activity.h"
#include "cdroid/legacy/internal/j.h"

struct __cdroid_state__
{
  struct cdroid_activity main_activity;
  j_vm *jvm;

  j_class __ptr_clazz__;
  j_class __toast_clazz__;
  j_class __viewhelper_clazz__;
};

extern struct __cdroid_state__ __state__;

i8 __cdroid_state_get_env__ (void **);

int __cdroid_state_load_main__ (const char *, const char *);

i8 __cdroid_state_delete__ ();

CDROID_HEADER_END

#endif