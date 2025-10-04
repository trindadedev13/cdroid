#ifndef __cdroid_internal_callback_h__
#define __cdroid_internal_callback_h__

#include "cdroid/internal/types.h"

CDROID_HEADER_BEGIN

typedef void (*__cdroid_callback_fn__) (void *);

struct __cdroid_callback_node__
{
  __cdroid_callback_fn__ fn;
  void *udata;
  struct __cdroid_callback_node__ *next;
};

i8 __cdroid_callback_node_register__ (__cdroid_callback_fn__, void *,
                                      struct __cdroid_callback_node__ **);
i8 __cdroid_callback_node_unregister__ (struct __cdroid_callback_node__ *);

CDROID_HEADER_END

#endif