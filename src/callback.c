#include "cdroid/internal/callback.h"

#include <stdlib.h>

#include "cdroid/internal/callback.h"
#include "cdroid/internal/j.h"
#include "cdroid/internal/types.h"
#include "cdroid/log.h"

static struct __cdroid_callback_node__ *__callback_list__ = NULL;

i8
__cdroid_callback_node_register__ (__cdroid_callback_fn__ fn, void *udata,
                                   struct __cdroid_callback_node__ **dest)
{
  *dest = malloc (sizeof (struct __cdroid_callback_node__));
  if (*dest == NULL)
    {
      LOGE ("Failed to allocate callback node at %s.\n", __func__);
      return -1;
    }

  (*dest)->fn = fn;
  (*dest)->udata = udata;
  (*dest)->next = __callback_list__;
  __callback_list__ = *dest;
  return 0;
}

i8
__cdroid_callback_node_unregister__ (struct __cdroid_callback_node__ *node)
{
  struct __cdroid_callback_node__ **cur = &__callback_list__;

  if (!node)
    {
      LOGE ("Invalid Node to unregister at %s.\n", __func__);
      return -1;
    }

  while (*cur)
    {
      if (*cur == node)
        {
          *cur = node->next;
          free (node);
          return 0;
        }
      cur = &(*cur)->next;
    }

  return 0;
}

/**
 * Calls a native function from a native ptr.
 *
 * @param callback_ptr : The callback
 */
J_EXPORT j_int J_CALL
CDROID_JAVA (CDroid, nativeCall) (j_env *env, j_class clazz,
                                  j_long callback_ptr)
{
  struct __cdroid_callback_node__ *callback
      = (struct __cdroid_callback_node__ *)callback_ptr;
  callback->fn (callback->udata);
  (void)env;
  (void)clazz;
  return 0;
}
