#include "bistro.h"

void		init_op_one(t_op_def *ops, int nbr, char c, t_op_prop prop)
{
  if (nbr >= 0 && nbr < OP_NBR)
    {
      ops[nbr].c = c;
      ops[nbr].op = nbr;
      ops[nbr].prop = prop;
    }
}

void		init_ops(t_op_def *ops)
{
  init_op_one(ops, OP_ADD, DEFAULT_ADD, PROP_ADD);
  init_op_one(ops, OP_SUB, DEFAULT_SUB, PROP_SUB);
  init_op_one(ops, OP_MUL, DEFAULT_MUL, PROP_MUL);
  init_op_one(ops, OP_DIV, DEFAULT_DIV, PROP_DIV);
  init_op_one(ops, OP_MOD, DEFAULT_MOD, PROP_MOD);
}

t_bistro	*init()
{
  t_bistro	*bi;

  if ((bi = malloc(sizeof(t_bistro))) == NULL)
    return (NULL); /* TODO: MSG ERR */
  memset(bi, 0, sizeof(t_bistro));
  if ((bi->pars.btree = btree_init()) == NULL)
    return (NULL); /* TODO: MSG ERR */
  bi->pars.level = 0;
  init_ops(bi->op_def);
  bi->parent[PARENT_OPEN] = DEFAULT_P_OPEN;
  bi->parent[PARENT_CLOSE] = DEFAULT_P_CLOSE;
  bi->base.fct_isinbase = &base_dec_isin;
  bi->base.fct_valueinbase = &base_dec_value;
  return (bi);
}
