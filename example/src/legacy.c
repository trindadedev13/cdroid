#include <cdroid/legacy/activity.h>
#include <cdroid/legacy/linearlayout.h>
#include <cdroid/legacy/log.h>
#include <cdroid/legacy/pub.h>
#include <cdroid/legacy/textview.h>
#include <cdroid/legacy/toast.h>
#include <cdroid/legacy/view.h>

struct cdroid_activity main_act = { 0 };

void
text_callback ()
{
  struct cdroid_toast my;
  cdroid_toast_new (&my, &main_act, "TextClicked", TOAST_DURATION_SHORT);
  cdroid_toast_show (&my);
}

int
main (int argc, char **argv)
{

  /** to use legacy, we need tell the cdroid to use call legacy init too */
  cdroid_pub_legacy_init ();

  /** get the main activity reference */
  if (cdroid_pub_get_main_activity (&main_act) != 0)
    {
      LOGE ("Something wrong with the main activity at %s, "
            "closing...\n",
            __func__);
      return -1;
    }

  /** creates new linearlayout */
  struct cdroid_view content;
  if (cdroid_linearlayout_new (&content, &main_act) != 0)
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
  if (cdroid_textview_new (&tv, &main_act) != 0)
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
  if (cdroid_activity_set_contentview (&main_act, &content) != 0)
    {
      LOGE ("Failed to set MainActivity content view at %s\n", __func__);
      return -1;
    }
  return 0;
}