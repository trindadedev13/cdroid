package cdroid.app.legacy;

import android.app.Activity;

public class CDroid
{
  static { System.loadLibrary ("cdroid"); }

  public static final native int
  nativeInit (final Activity c, final String libPath, final String fnName);
}
