#ifndef __cdroid_legacy_linearlayout_h__
#define __cdroid_legacy_linearlayout_h__

#include "cdroid/legacy/internal/types.h"

CDROID_HEADER_BEGIN

#include "cdroid/legacy/internal/j.h"

#include "cdroid/legacy/activity.h"
#include "cdroid/legacy/view.h"

#define ORIENTATION_HORIZONTAL 0x00000000
#define ORIENTATION_VERTICAL 0x00000001

/** we don't need to store any linearlayout-only data */
struct __cdroid_linearlayout__;

i8 cdroid_linearlayout_new (struct cdroid_view *, struct cdroid_activity *);
i8 cdroid_linearlayout_set_orientation (struct cdroid_view *, i8);

CDROID_HEADER_END

#endif