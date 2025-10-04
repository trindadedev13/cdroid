package cdroid.app;

import android.util.Log;
import android.view.View;

public class ViewHelper
{
  public static final View.OnClickListener
  createClickListener (final long callbackPtr)
  {
    return new View.OnClickListener () {
      private final long mCallbackPtr = callbackPtr;

      @Override public void onClick (final View v)
      {
        Log.d ("ViewHelper", "Callback: " + mCallbackPtr);
        CDroid.nativeCall (mCallbackPtr);
      }
    };
  }
}
