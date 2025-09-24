#ifndef __cdroid_legacy_textview_h__
#define __cdroid_legacy_textview_h__

#include "cdroid/legacy/internal/types.h"

CDROID_HEADER_BEGIN

#include "cdroid/legacy/internal/j.h"

#include "cdroid/legacy/activity.h"
#include "cdroid/legacy/view.h"

/** we don't need to store any textview-only data */
struct __cdroid_textview__;

i8 cdroid_textview_new (struct cdroid_view *, struct cdroid_activity *);
i8 cdroid_textview_set_text (struct cdroid_view *, const char *);

CDROID_HEADER_END

#endif