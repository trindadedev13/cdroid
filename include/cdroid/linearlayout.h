#ifndef __cdroid_linearlayout_h__
#define __cdroid_linearlayout_h__

#include "cdroid/internal/types.h"

CDROID_HEADER_BEGIN

#include "cdroid/internal/j.h"

#include "cdroid/activity.h"
#include "cdroid/view.h"

#define ORIENTATION_HORIZONTAL 0x00000000
#define ORIENTATION_VERTICAL 0x00000001

/** we don't need to store any linearlayout-only data */
struct __cdroid_linearlayout__;

i8 cdroid_linearlayout_new (struct cdroid_view *, struct cdroid_activity *);
i8 cdroid_linearlayout_set_orientation (struct cdroid_view *, i8);
i8 cdroid_linearlayout_set_gravity (struct cdroid_view *, i32);

CDROID_HEADER_END

#endif
