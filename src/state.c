#include "cdroid/internal/state.h"

#include "cdroid/internal/j.h"

struct __cdroid_state__ __state__ = {};

int
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