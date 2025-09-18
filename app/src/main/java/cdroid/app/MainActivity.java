package cdroid.app;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends Activity
{

  @Override
  protected void
  onCreate (Bundle savedInstanceState)
  {
    super.onCreate (savedInstanceState);
    final String libPath = getApplicationInfo ().nativeLibraryDir + "/"
                           + "libcdroid_main.so";
    int res = CDroid.nativeInit (
        /** activity = */
        this,
        /** libPath  = */
        libPath,
        /** fnName   = */
        "main");
    if (res != 0)
      {
        Toast
            .makeText (this,
                       "Failed to initialize CDroid. "
                           + "Check logcat.",
                       400)
            .show ();
        System.exit (1);
      }
  }
}
