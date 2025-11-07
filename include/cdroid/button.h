#ifndef __cdroid_button_h__
#define __cdroid_button_h__

#include "cdroid/activity.h"
#include "cdroid/internal/types.h"
#include "cdroid/view.h"

CDROID_HEADER_BEGIN

i8 cdroid_button_new (struct cdroid_view *, struct cdroid_activity *);
i8 cdroid_button_set_text (struct cdroid_view *, const char *);

CDROID_HEADER_END

#endif
