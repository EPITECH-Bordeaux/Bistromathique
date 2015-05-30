#include "bistro.h"

int		parser_btree_op(t_bistro *bi)
{
  t_nb_op	*new;

  new = xmalloc(sizeof(t_nb_op));
  memset(new, 0, sizeof(t_nb_op));

  new->op = bi->pars.op;
  new->level = bi->pars.level;

  while (bi->pars.pile_op &&
	 (new->level < bi->pars.pile_op->level ||
	  (new->level == bi->pars.pile_op->level &&
	   op_def[new->op].prop <= op_def[bi->pars.pile_op->op].prop)))
    {
      op_def[bi->pars.pile_op->op].fct_calc(bi, &bi->pars.pile_nb);
      /* FREE */
      bi->pars.pile_op = bi->pars.pile_op->next;
    }
  new->next = bi->pars.pile_op;
  bi->pars.pile_op = new;
  
  bi->pars.op = -1;
  bi->pars.last_node = TYPE_NODE_OP;
  return (BI_OK);
}

int		parser_btree_nb(t_bistro *bi)
{
  t_nb_op	*new;

  new = xmalloc(sizeof(t_nb_op));
  memset(new, 0, sizeof(t_nb_op));
  new->nb = bi->pars.nb;
  new->nbr = atoi(bi->pars.nb);
  new->is_neg = bi->pars.is_neg;
  new->len_nb = bi->pars.len_nb;
  new->next = bi->pars.pile_nb;
  bi->pars.pile_nb = new;
  bi->pars.nb = NULL;
  bi->pars.len_nb = 0;
  bi->pars.last_node = TYPE_NODE_NB;
  return (BI_OK);
}

int		parser_token(t_bistro *bi, char *str, int *pos, int len_str)
{
  int		ret_v;

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
  parser_token_unknow(bi, str, *pos);
  return (TOKEN_ERROR);
}

int		parser_reinit(t_pars *pars)
{
  pars->level = 0;
  pars->token = TOKEN_START;
  pars->op = -1;
  pars->pile_op = NULL;
  pars->pile_nb = NULL;
  return (BI_OK);
}

int		parser(t_bistro *bi, char *str, int len_str)
{
  int		pos;

  pos = 0;
  if (len_str == 0)
    return (0);
  if (bi->pars.token == TOKEN_START || bi->pars.token == TOKEN_END ||
      bi->pars.token == TOKEN_ERROR)
    parser_reinit(&bi->pars);
  while (pos < len_str && bi->pars.token != TOKEN_END)
    {
      if ((bi->pars.token = parser_token(bi, str, &pos, len_str)) == TOKEN_ERROR)
	return (BI_ERR);
      if (bi->pars.op != -1)
	parser_btree_op(bi);
      if (bi->pars.nb != NULL)
	parser_btree_nb(bi);
      pos += 1;
    }
  if (bi->pars.token == TOKEN_END && bi->pars.level != 0)
    print_error("The number of open and close parentheses are not equal");


  if (bi->pars.token == TOKEN_END)
    {
      while (bi->pars.pile_op)
	{
	  op_def[bi->pars.pile_op->op].fct_calc(bi, &bi->pars.pile_nb);
	  /* FREE */
	  bi->pars.pile_op = bi->pars.pile_op->next;
	}
      printf("res :%d\n", bi->pars.pile_nb->nbr);
      write(1, "\n", 1);
      bi->pars.pile_nb = NULL;
    }


  return (pos - bi->pars.len_nb);
}
