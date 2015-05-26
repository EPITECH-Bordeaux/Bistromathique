#include "bistro.h"

void		init_op_one(t_op_def *ops, int nbr, char c, t_op_prop prop)
{
  if (nbr >= 0 && nbr < OP_NBR)
    {
      ops[nbr].op_c = c;
      ops[nbr].op = nbr;
      ops[nbr].prop = prop;
    }
}

void		init_ops(t_op_def *ops)
{
  init_op_one(ops, ADD, DEFAULT_ADD, PROP_ADD);
  init_op_one(ops, SUB, DEFAULT_SUB, PROP_SUB);
  init_op_one(ops, MUL, DEFAULT_MUL, PROP_MUL);
  init_op_one(ops, DIV, DEFAULT_DIV, PROP_DIV);
  init_op_one(ops, MOD, DEFAULT_MOD, PROP_MOD);
}

t_bistro	*init()
{
  t_bistro	*new;

  if ((new = malloc(sizeof(t_bistro))) == NULL)
    return (NULL); /* TODO: MSG ERR */
  memset(new, 0, sizeof(t_bistro));
  if ((new->pars = malloc(sizeof(t_pars))) == NULL)
    return (NULL); /* TODO: MSG ERR */
  if ((new->pars->btree = btree_init()) == NULL)
    return (NULL); /* TODO: MSG ERR */
  new->base = NULL;
  init_ops(new->op_def);
  return (new);
}
