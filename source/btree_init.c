#include "btree.h"

t_btree		*btree_init()
{
  t_btree	*new;

  if ((new = malloc(sizeof(t_btree))) == NULL)
    return (NULL);
  btree_reset(new);
  return (new);
}
