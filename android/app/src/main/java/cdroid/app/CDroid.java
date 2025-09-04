package cdroid.app;

import android.app.Activity;

public class CDroid
{
  static { System.loadLibrary ("cdroid"); }
  public static final native void init (final Activity c);
}
