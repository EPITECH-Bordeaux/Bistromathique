#include "bistro.h"

int		parser_btree_nb(t_bistro *data, char side)
{
  t_nb_op	*new;

  new = xmalloc(sizeof(t_nb_op));
  new->type_node = TYPE_NODE_NB;
  new->nb = data->pars.nb;
  new->size = (size_t)data->pars.nb_len;
  new->is_neg = false;
  new->is_alloc = false;
  btree_node_add(data->pars.btree, new, side, DAD);
  return (BI_OK);
}

int		parser_btree_op(t_bistro *data, char side)
{
  t_nb_op	*new;

  new = xmalloc(sizeof(t_nb_op));
  new->type_node = TYPE_NODE_OP;
  new->op = data->pars.op;
  new->level = data->pars.level;
  btree_node_add(data->pars.btree, new, side, LEFT);
  return (BI_OK);
}

int		parser_btree(t_bistro *data)
{
  t_node	*node;

  node = data->pars.btree->current;
  if (node != NULL &&
      (data->pars.level < ((t_nb_op *)(node->data))->level ||
              op_def[data->pars.op].prop <
       op_def[((t_nb_op *)(node->data))->op].prop))
    {
      parser_btree_nb(data, RIGHT);
      while (btree_move_up(data->pars.btree));
      parser_btree_op(data, DAD);
    }
  else
    {
      parser_btree_op(data, RIGHT);
      btree_move_down(data->pars.btree, RIGHT);
      parser_btree_nb(data, LEFT);
    }
  return (BI_OK);
}
