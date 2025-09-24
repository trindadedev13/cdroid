package cdroid.app.legacy;

public class Pointer
{
  private final long raw;
  private final boolean isFn;

  public Pointer (final long raw, final boolean isFn)
  {
    this.raw = raw;
    this.isFn = isFn;
  }

  public final long
  getRaw ()
  {
    return raw;
  }

  public final void
  call ()
  {
    if (isFn)
      nativeCall ();
  }

  public final native int nativeCall ();
}
