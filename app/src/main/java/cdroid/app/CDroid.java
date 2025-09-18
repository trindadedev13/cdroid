package cdroid.app;

import android.app.Activity;
import android.app.Application;

public class CDroid extends Application {
  static {
    System.loadLibrary("cdroid");
  }

  public static final native int nativeInit(
      final Activity c, final String libPath, final String fnName);
}
