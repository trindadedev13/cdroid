package cdroid.app;

import android.app.Activity;

public class CDroid
{
  static { System.loadLibrary ("cdroid"); }
  public static final native int init (final Activity c, final String libPath,
                                       final String fnName);
}
