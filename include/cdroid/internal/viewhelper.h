#ifndef __cdroid_viewhelper_h__
#define __cdroid_viewhelper_h__

#include "cdroid/internal/types.h"

CDROID_HEADER_BEGIN

#include "cdroid/internal/j.h"
#include "cdroid/internal/callback.h"

i8 __cdroid_viewhelper_create_click_listener__ (struct __cdroid_callback_node__ *, j_object *);

CDROID_HEADER_END

#endif