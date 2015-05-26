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
}

t_bistro	*init()
{
  t_bistro	*new;

  if ((new = malloc(sizeof(t_bistro))) == NULL)
    return (NULL); /* TODO: MSG ERR */
  if ((new->pars = malloc(sizeof(t_pars))) == NULL)
    return (NULL); /* TODO: MSG ERR */
  init_ops(new->op_def);
  return (new);
}
