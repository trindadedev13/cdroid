package cdroid.app;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity
{
  @Override
  protected void
  onCreate (Bundle savedInstanceState)
  {
    super.onCreate (savedInstanceState);
    CDroid.init (this);
  }
}
