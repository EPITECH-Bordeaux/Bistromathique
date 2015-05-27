#include "bistro.h"

int		init(t_bistro *bi)
{
  memset(bi, 0, sizeof(t_bistro));
  if ((bi->pars.btree = btree_init()) == NULL)
    return (BI_ERR); /* TODO: MSG ERR */
  bi->pars.level = 0;
  bi->pars.last_token = TYPE_START;
  bi->parent[PARENT_OPEN] = DEFAULT_P_OPEN;
  bi->parent[PARENT_CLOSE] = DEFAULT_P_CLOSE;
  bi->base.fct_isinbase = &base_dec_isin;
  bi->base.fct_valueinbase = &base_dec_value;
  return (BI_OK);
}
