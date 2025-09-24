#ifndef __cdroid_legacy_toast_h__
#define __cdroid_legacy_toast_h__

#include "cdroid/legacy/internal/types.h"

CDROID_HEADER_BEGIN

#include "cdroid/legacy/activity.h"
#include "cdroid/legacy/internal/j.h"

#define TOAST_DURATION_SHORT 0x00000000
#define TOAST_DURATION_LONG 0x00000001

struct cdroid_toast
{
  j_object instance;
};

i8 cdroid_toast_new (struct cdroid_toast *, struct cdroid_activity *,
                     const char *, i8);
i8 cdroid_toast_show (struct cdroid_toast *);

CDROID_HEADER_END

#endif