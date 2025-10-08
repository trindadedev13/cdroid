#ifndef __cdroid_view_h__
#define __cdroid_view_h__

#include "cdroid/internal/types.h"

CDROID_HEADER_BEGIN

#include "cdroid/internal/callback.h"
#include "cdroid/internal/j.h"

#include "cdroid/view.h"

enum cdroid_view_type
{
  VIEW,
  VIEW_TEXT,
  VIEW_LINEARLAYOUT
};

struct cdroid_view
{
  enum cdroid_view_type type;

  j_class clazz;
  j_object instance;

  void *__special__;
};

const char *cdroid_view_type_tostr (enum cdroid_view_type);

i8 cdroid_view_is_viewgroup (struct cdroid_view *);
i8 cdroid_view_add_view (struct cdroid_view *, struct cdroid_view *);
i8 cdroid_view_set_click_listener (struct cdroid_view *,
                                   __cdroid_callback_fn__, void *);

CDROID_HEADER_END

#endif
