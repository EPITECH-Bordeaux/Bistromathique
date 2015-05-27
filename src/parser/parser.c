#include "bistro.h"

int		parser_type_nb(t_bistro *data, char *str, int i)
{
  if (data->base.fct_isinbase(&data->base, str[i]) == false)
    return (BI_ERR);
  if (data->pars.parsing_nb == false)
    data->pars.nb = str + i;
  data->pars.nb_len += 1;
  data->pars.parsing_nb = true;
  return (BI_OK);
}

int		parser_type_op(t_bistro *data, char *str, int i)
{
  int		j;

  j = 0;
  while (j < OP_NBR && op_def[j].c != str[i])
    j += 1;
  if (j >= OP_NBR || (j < OP_NBR && data->pars.op != -1))
    return (BI_ERR);
  data->pars.op = j;
  data->pars.parsing_nb = false;
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
    data->pars.parsing_nb = false;
  return (ret);
}

int		parser_type(t_bistro *data, char *str, int i)
{
  if (str[i] == ' ' || str[i] == '\t')
    {
      data->pars.parsing_nb = false;
      return (BI_OK);
    }
  if (str[i] == '\n' || str[i] == 0)
    {
      data->pars.is_end = true;
      return (BI_OK);
    }
  if (parser_type_parent(data, str, i) == BI_OK)
    return (BI_OK);
  else if (parser_type_op(data, str, i) == BI_OK)
    return (BI_OK);
  else if (parser_type_nb(data, str, i) == BI_OK)
    return (BI_OK);
  print_error("Unknow char: '%c'\n", str[i]);
  return (BI_ERR);
}

int		parser_init(t_pars *pars)
{
  pars->is_end = false;
  pars->op = -1;
  pars->nb = NULL;
  pars->nb_len = 0;
  pars->parsing_nb = false;
  return (BI_OK);
}

int		parser_end(t_bistro *data, int i)
{
  if (data->pars.nb == NULL)
    return (BI_ERR);
  else
    parser_btree_nb(data, 1);
  display_tree(data->pars.btree);
  btree_reset(data->pars.btree);
  data->pars.last_token = TYPE_START;
  return (i);
}

int		parser(t_bistro *data, char *str, int len)
{
  int       	i;

  i = 0;
  parser_init(&data->pars);
  if (len == 0)
    data->pars.is_end = true;
  while (i < len && data->pars.is_end == false)
    {
      if (parser_type(data, str, i) == BI_ERR)
	return (BI_ERR);
      if (data->pars.nb != NULL && data->pars.op != -1)
	{
	  parser_btree(data);
	  parser_init(&data->pars);
	}
      i = i + 1;
    }
  if (data->pars.parsing_nb == true && data->pars.is_end == false)
    {
      data->pars.parsing_nb = false;
      data->pars.nb = NULL;
      return (i - data->pars.nb_len);
    }
  else if (data->pars.is_end == true)
    return (parser_end(data, i));
  return (i);
}
