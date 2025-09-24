#ifndef __cdroid_legacy_activity_h__
#define __cdroid_legacy_activity_h__

#include "cdroid/legacy/internal/types.h"

CDROID_HEADER_BEGIN

#include "cdroid/legacy/internal/j.h"

#include "cdroid/legacy/view.h"

struct cdroid_activity
{
  j_class clazz;
  j_object instance;
};

i8 cdroid_activity_new (struct cdroid_activity *, j_class, j_object);
i8 cdroid_activity_delete (struct cdroid_activity *);
i8 cdroid_activity_is_valid (struct cdroid_activity *);

i8 cdroid_activity_set_contentview (struct cdroid_activity *,
                                    struct cdroid_view *);

CDROID_HEADER_END

#endif