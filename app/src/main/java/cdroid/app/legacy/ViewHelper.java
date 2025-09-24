package cdroid.app.legacy;

import android.view.View;

public class ViewHelper
{
  public static final View.OnClickListener
  createClickListener (final Pointer ptr)
  {
    return new View.OnClickListener () {
      @Override public void onClick (final View v) { ptr.call (); }
    };
  }
}
