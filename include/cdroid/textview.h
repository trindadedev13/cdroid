#ifndef __cdroid_textview_h__
#define __cdroid_textview_h__

#include "cdroid/internal/types.h"

CDROID_HEADER_BEGIN

#include "cdroid/internal/j.h"

#include "cdroid/activity.h"
#include "cdroid/view.h"

/** we don't need to store any textview-only data */
struct __cdroid_textview__;

i8 cdroid_textview_new (struct cdroid_view *, struct cdroid_activity *);
i8 cdroid_textview_set_text (struct cdroid_view *, const char *);

CDROID_HEADER_END

#endif
