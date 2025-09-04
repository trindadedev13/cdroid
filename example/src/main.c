#include <cdroid/activity.h>
#include <cdroid/linearlayout.h>
#include <cdroid/log.h>
#include <cdroid/pub.h>
#include <cdroid/textview.h>
#include <cdroid/view.h>

void
text_callback ()
{
  LOGD ("TextClicked");
}

int
main (int argc, char **argv)
{
  /** get the main activity reference */
  struct cdroid_activity act;
  if (cdroid_pub_get_main_activity (&act) != 0)
    {
      LOGE ("Something wrong with the main activity at %s, "
            "closing...\n",
            __func__);
      return -1;
    }

  /** creates new linearlayout */
  struct cdroid_view content;
  if (cdroid_linearlayout_new (&content, &act) != 0)
    {
      LOGE ("Failed to create linearlayout at %s\n", __func__);
      return -1;
    }

  /** defines content orientation to vertical */
  if (cdroid_linearlayout_set_orientation (&content, ORIENTATION_VERTICAL)
      != 0)
    {
      LOGE ("Failed to set linearlayout orientation at %s\n", __func__);
      return -1;
    }

  /** creates a new textview */
  struct cdroid_view tv;
  if (cdroid_textview_new (&tv, &act) != 0)
    {
      LOGE ("Failed to create textview at %s\n", __func__);
      return -1;
    }

  /** changes textview text */
  if (cdroid_textview_set_text (&tv, "Hello world from CDroid") != 0)
    {
      LOGE ("Failed to set textview text value at %s\n", __func__);
      return -1;
    }

  if (cdroid_view_add_view (&content, &tv) != 0)
    {
      LOGE ("Failed to add textview in linearlayout at %s\n", __func__);
      return -1;
    }

  if (cdroid_view_set_click_listener (&tv, text_callback) != 0)
    {
      LOGE ("Failed to set textview click callback at %s\n", __func__);
      return -1;
    }

  /** defines activity content */
  if (cdroid_activity_set_contentview (&act, &content) != 0)
    {
      LOGE ("Failed to set MainActivity content view at %s\n", __func__);
      return -1;
    }
  return 0;
}