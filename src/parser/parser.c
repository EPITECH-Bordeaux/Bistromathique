#include "bistro.h"

int		parser_btree_op(t_bistro *bi)
{
  t_bt		*new;

  new = xmalloc(sizeof(t_bt));
  new->type_node = TYPE_NODE_OP;
  new->data.op = bi->pars.op;
  new->data.level = bi->pars.level;
  if (bi->pars.bt == NULL)
    bi->pars.bt = new;
  return (BI_OK);
}

int		parser_btree_nb(t_bistro *bi)
{
  t_bt		*new;

  new = xmalloc(sizeof(t_bt));
  new->type_node = TYPE_NODE_NB;
  new->data.nb = bi->pars.nb;
  new->data.is_neg = bi->pars.is_neg;
  new->data.len_nb = bi->pars.len_nb;
  if (bi->pars.bt->type_node)
    new = new; /* TOP */
  else if (1)
    new = new; /* RIGHT */
  else
    while (1)
      new = new; /* TOP */
  return (BI_OK);
}

int             parser_token(t_bistro *bi, char *str, int *pos, int len_str)
{
  int           ret_v;

  if (str[*pos] == ' ' || str[*pos] == '\t')
    return (bi->pars.token);
  if (parser_token_parent_open(bi, str, *pos) == TOKEN_P_OPEN)
    return (TOKEN_P_OPEN);
  else if (parser_token_parent_close(bi, str, *pos) == TOKEN_P_CLOSE)
    return (TOKEN_P_CLOSE);
  else if ((ret_v = parser_token_nb(bi, str, pos, len_str)) == TOKEN_NB ||
           ret_v == TOKEN_REBUFF)
    return (ret_v);
  else if (parser_token_op(bi, str, *pos) == TOKEN_OP)
    return (TOKEN_OP);
  if (parser_token_end(bi, str, *pos) == TOKEN_END)
    return (TOKEN_END);
  return (TOKEN_ERROR);
}

int		parser(t_bistro *bi, char *str, int len_str)
{
  int		pos;

  pos = 0;
  if (len_str == 0)
    return (0);
  if (bi->pars.token == TOKEN_START || bi->pars.token == TOKEN_END)
    {
      bi->pars.level = 0;
      bi->pars.token = TOKEN_START;
      bi->pars.op = -1;
      bi->pars.bt = NULL;
    }
  while (pos < len_str && bi->pars.token != TOKEN_END)
    {
      if ((bi->pars.token = parser_token(bi, str, &pos, len_str)) == TOKEN_ERROR)
	return (BI_ERR);
      if (bi->pars.op != -1)
	{
	  printf("%c\n", op_def[bi->pars.op].c);
	  parser_btree_op(bi);	 
	  bi->pars.op = -1;
	}
      if (bi->pars.nb != NULL)
	{
	  write(1, bi->pars.nb, bi->pars.len_nb);
	  write(1, "\n", 1);	    
	  parser_btree_nb(bi);	 
	  bi->pars.nb = NULL;
	  bi->pars.len_nb = 0;
	}
      pos += 1;
    }
  if (bi->pars.token == TOKEN_END && bi->pars.level != 0)
    printf("Warning: Missing parent '%c'\n", bi->parent[PARENT_CLOSE]);
  return (pos - bi->pars.len_nb);
}
