#include "bistro.h"

t_bistro	*init()
{
  t_bistro	*bi;

  if ((bi = malloc(sizeof(t_bistro))) == NULL)
    return (NULL); /* TODO: MSG ERR */
  memset(bi, 0, sizeof(t_bistro));
  if ((bi->pars.btree = btree_init()) == NULL)
    return (NULL); /* TODO: MSG ERR */
  bi->pars.level = 0;
  bi->pars.last_token = TYPE_START;
  bi->parent[PARENT_OPEN] = DEFAULT_P_OPEN;
  bi->parent[PARENT_CLOSE] = DEFAULT_P_CLOSE;
  bi->base.fct_isinbase = &base_dec_isin;
  bi->base.fct_valueinbase = &base_dec_value;
  return (bi);
}
