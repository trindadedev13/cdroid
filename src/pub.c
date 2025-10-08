#include "cdroid/pub.h"

#include "cdroid/activity.h"
#include "cdroid/internal/state.h"
#include "cdroid/log.h"

/**
 * Provides the main activity instance.
 *
 * Returns 0 if all ok
 * Returns -1 if class OR instance is invalid
 * Returns -2 if class AND instance is invalid
 *
 * @param dest : The dest struct
 */
i8
cdroid_pub_get_main_activity (struct cdroid_activity *dest)
{
  i8 r = 0;
  if ((r = cdroid_activity_is_valid (&__state__.main_activity)) != 0)
    {
      if (r == -1)
        LOGE ("Invalid class OR instance for main "
              "activity at %s\n",
              __func__);
      return r;
      if (r == -2)
        LOGE ("Invalid class AND instance for main "
              "activity at %s\n",
              __func__);
      return r;
    }
  *dest = __state__.main_activity;
  return r;
}
