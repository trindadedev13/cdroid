#include "cdroid/legacy/internal/state.h"

#include <dlfcn.h>
#include <unistd.h>

#include "cdroid/legacy/activity.h"
#include "cdroid/legacy/internal/j.h"
#include "cdroid/legacy/internal/types.h"
#include "cdroid/legacy/log.h"

typedef int (*cdroid_main_func) (int argc, char *argv[]);

struct __cdroid_state__ __state__ = {};

/**
 * Provides the JNIEnv instance or -1 if error.
 *
 * @param dest : The dest struct
 */
i8
__cdroid_state_get_env__ (void **dest)
{
  j_vm *v = __state__.jvm;
  j_env *env = NULL;
  if (j_vm_get_env (v, (void **)&env, JNI_VERSION_1_6) != JNI_OK)
    {
      if (j_vm_attach_current_thread (v, &env, NULL) != JNI_OK)
        {
          return -1;
        }
    }
  *dest = env;
  return 0;
}

/**
 * Loads the main function from a shared object
 *
 * @param libPath : The path of shared object
 * @param fnName  : The name of function inside shared object
 */
int
__cdroid_state_load_main__ (const char *lib_path, const char *fn_name)
{
  void *lib_hdl = dlopen (lib_path, RTLD_GLOBAL);
  if (lib_hdl == NULL)
    {
      const char *lib_name = strrchr (lib_path, '/');
      if (lib_name && *lib_name)
        {
          lib_name += 1;
          lib_hdl = dlopen (lib_name, RTLD_GLOBAL);
        }
    }

  if (!lib_hdl)
    {
      LOGE ("Failed to load library %s at %s\n", lib_path, __func__);
      return -1;
    }

  cdroid_main_func fn = (cdroid_main_func)dlsym (lib_hdl, fn_name);
  if (!fn)
    {
      LOGE ("Failed to load function %s at library %s at %s\n", fn_name,
            lib_path, __func__);
      return -1;
    }

  int argc = 1;
  char *argv[] = { str_dup ("cdroid") };
  int status = fn (argc, argv);
  size_t i = 0;
  for (; i < argc; ++i)
    {
      if (argv[i])
        {
          mem_free (argv[i]);
        }
    }
  return status;
}

i8
__cdroid_state_delete__ ()
{
  j_env *env = NULL;
  if (__cdroid_state_get_env__ ((void **)&env) != 0)
    {
      LOGE ("Failed to get env at %s\n", __func__);
      return -1;
    }

  __state__.jvm = NULL;
  cdroid_activity_delete (&__state__.main_activity);

  j_env_delete_global_ref (env, __state__.__ptr_clazz__);
  j_env_delete_global_ref (env, __state__.__viewhelper_clazz__);
  j_env_delete_global_ref (env, __state__.__toast_clazz__);

  return 0;
}