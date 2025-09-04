# CDroid
 - Create android apps with C.

## References
 - [GNU C](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html)
 - [Android Developers](https://developer.android.com/)
 - [Oracle JNI Docs](https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/jniTOC.html)

## Building
  To Build CDroid you should use the `build.cr`  

### Library

- Build library:  
    ```bash
    crystal run build.rb -- --build
    ```  

- Build library and example:  
    ```bash
    crystal run build.rb -- --build --example
    ```  

### Android APK (wip)
 - Well, to build the apk it's more nhe boring  

- First Build library, example and prepare files to build apk:  
    ```bash
    crystal run build.rb -- --build --example --prepare
    ```
- Now we should build the apk in android folder  
  I Use AIDE Mobile to run it, i don't how you can do it in your device for now.  

## Community
[![Join our Discord server!](https://invidget.switchblade.xyz/5hSStgYfru)](https://discord.gg/5hSStgYfru)
