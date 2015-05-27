#include "bistro.h"

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
