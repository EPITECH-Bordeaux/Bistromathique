#include "bistro.h"

/* TODO: "int pars_reset(t_pars *pars)" */

int		parser_type_nb(t_bistro *data, char *str, int i)
{
  return (BI_OK);
}

int		parser_type_op(t_bistro *data, char *str, int i)
{
  int		j;

  j = 0;
  while (j < OP_NBR && data->op_def[j].c != str[i])
    j += 1;
  if (j >= OP_NBR || (j < OP_NBR && data->pars.op != NULL))
    return (BI_ERR);
  data->pars.op = &data->op_def[j];
  data->pars.parsing_nb = MY_FALSE;
  return (BI_OK);
}

int		parser_type_parent(t_bistro *data, char *str, int i)
{
  int		ret;

  ret = BI_ERR;
  if (str[i] == data->parent[PARENT_OPEN])
    {
      data->pars.level += 1;
      ret = BI_OK;
    }
  else if (str[i] == data->parent[PARENT_CLOSE])
    {
      data->pars.level -= 1;
      ret = BI_OK;
    }
  if (data->pars.level < 0)
    return (BI_ERR);
  if (ret == BI_OK)
    data->pars.parsing_nb = MY_FALSE;
  return (ret);
}

int		parser_type(t_bistro *data, char *str, int i)
{
  if (str[i] == ' ' || str[i] == '\t')
    {
      data->pars.parsing_nb = MY_FALSE;
      return (BI_OK);
    }
  if (parser_type_parent(data, str, i) == BI_OK)
    return (BI_OK);
  else if (parser_type_op(data, str, i) == BI_OK)
    return (BI_OK);
  else if (parser_type_nb(data, str, i) == BI_OK)
    return (BI_OK);
  return (BI_ERR);
}

int		parser_init(t_pars *pars)
{
  pars->op = NULL;
  pars->nb = NULL;
  pars->nb_len = 0;
  pars->parsing_nb = MY_FALSE;
  return (BI_OK);
}

int		parser_btree_nb(t_bistro *data, char cas)
{
  t_nb_op	*new;

  new = xmalloc(sizeof(t_nb_op));
  new->type_node = TYPE_NODE_NB;
  new->nb = data->pars.nb;
  new->size = (size_t)data->pars.nb_len;
  new->is_neg = MY_FALSE;
  new->is_alloc = MY_FALSE;
  write(1, "nb :", 4);
  write(1, data->pars.nb, data->pars.nb_len);
  write(1, "\n", 1);
  if (cas)
    btree_node_add(data->pars.btree, new, RIGHT, DAD);
  else
    btree_node_add(data->pars.btree, new, LEFT, DAD);
  return (BI_OK);
}

int		parser_btree_op(t_bistro *data, char cas)
{
  t_nb_op	*new;

  new = xmalloc(sizeof(t_nb_op));
  new->type_node = TYPE_NODE_OP;
  new->op_def = data->pars.op;
  new->level = data->pars.level;
  printf("op: %c (level: %d)\n", data->pars.op->c, data->pars.level);
  if (cas)
    btree_node_add(data->pars.btree, new, DAD, LEFT);
  else
    btree_node_add(data->pars.btree, new, RIGHT, DAD);
  return (BI_OK);
}

int		parser_btree(t_bistro *data)
{
  char		cas;
  t_node	*node;

  node = data->pars.btree->current;
  if (node != NULL &&
      (data->pars.level < ((t_nb_op *)(node->data))->level || 
       data->pars.op->prop < ((t_nb_op *)(node->data))->op_def->prop))
    cas = 1;
  else
    cas = 0;
  parser_btree_op(data, cas);
  parser_btree_nb(data, cas);
  return (BI_OK);
}

int		parser_end(t_bistro *data)
{
  if (data->pars.nb == NULL)
    return (BI_ERR);
  else
    {
      printf("ENDING\n");
      parser_btree_nb(data, 1);
    }
  return (BI_OK);
}

int		parser(t_bistro *data, char *str, int len, bool is_end)
{
  int       	i;

  i = 0;
  parser_init(&data->pars);
  while (i < len)
    {
      if (parser_type(data, str, i) == BI_ERR)
	return (BI_ERR);
      if (data->pars.nb != NULL && data->pars.op != NULL)
	{
	  parser_btree(data);
	  parser_init(&data->pars);
	}
      i = i + 1;
    }
  if (data->pars.parsing_nb == MY_TRUE && is_end == 0)
    {
      data->pars.parsing_nb = MY_FALSE;
      data->pars.nb = NULL;
      return (i - data->pars.nb_len);
    }
  else if (is_end != 0)
    return (parser_end(data));
  return (i);
}
