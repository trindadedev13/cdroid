package cdroid.app;

import android.app.Activity;

public class Main
{
  static { System.loadLibrary ("cdroid"); }

  public static final native int
  nativeInit (final Activity c, final String libPath, final String fnName);
}
