package cdroid.app;

import android.view.View;
import android.util.Log;

public class ViewHelper {
  public static final View.OnClickListener createClickListener(final long callbackPtr) {
    return new View.OnClickListener() {
      private final long mCallbackPtr = callbackPtr;

      @Override
      public void onClick(final View v) {
        Log.d ("ViewHelper", "Callback: " + mCallbackPtr);
        CDroid.nativeCall(mCallbackPtr);
      }
    };
  }
}
