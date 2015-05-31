#include "bistro.h"

int		parser_btree_op(t_bistro *bi, char op, int level)
{
  t_op		*last;
  t_op		*new;

  new = xmalloc(sizeof(t_op));
  new->op = op;
  new->level = level;
  while (bi->pars.pile_op &&
	 (new->level < bi->pars.pile_op->level ||
	  (new->level == bi->pars.pile_op->level &&
	   op_def[new->op].prop <= op_def[bi->pars.pile_op->op].prop)))
    {
      op_def[bi->pars.pile_op->op].fct_calc(bi, &bi->pars.pile_nb);
      last = bi->pars.pile_op;
      bi->pars.pile_op = bi->pars.pile_op->next;
      free(last);
    }
  new->next = bi->pars.pile_op;
  bi->pars.pile_op = new;
  return (BI_OK);
}

int		parser_btree_nb(t_bistro *bi, char *str,
				int last_pos, int len_nb)
{
  t_nb		*new;

  new = xmalloc(sizeof(t_nb));
  new->pos = last_pos - len_nb + 1;
  new->nb = str + new->pos;
  new->len_nb = len_nb;
  new->nbr = atoi(new->nb);
  new->next = bi->pars.pile_nb;
  new->is_neg = false;
  bi->pars.pile_nb = new;
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
  pars->pile_op = NULL;
  pars->pile_nb = NULL;
  return (BI_OK);
}

int		parser_end(t_bistro *bi, char *str, int len_str)
{
  t_op		*last;
  
  while (bi->pars.pile_op)
    {
      op_def[bi->pars.pile_op->op].fct_calc(bi, &bi->pars.pile_nb);
      last = bi->pars.pile_op;
      bi->pars.pile_op = bi->pars.pile_op->next;
      free(last);
    }
  printf("res :%d\n", bi->pars.pile_nb->nbr);
  free(bi->pars.pile_nb);
  bi->pars.pile_nb = NULL;
  return (BI_OK);
}

int		parser(t_bistro *bi, char *str, int len_str)
{
  int		pos;

  pos = 0;
  if (len_str == 0)
    return (0);
  if (bi->pars.token == TOKEN_START || bi->pars.token == TOKEN_END)
    parser_reinit(&bi->pars);
  while (pos < len_str && bi->pars.token != TOKEN_END)
    {
      if ((bi->pars.token = parser_token(bi, str, &pos, len_str)) ==
	  TOKEN_ERROR)
	{
	  while (pos < len_str && parser_token_end(bi, str , pos) != TOKEN_END)
	    pos += 1;
	  if (pos < len_str)
	    bi->pars.token = TOKEN_END;
	  return (pos);
	}
      pos += 1;
    }
  if (bi->pars.token == TOKEN_END && bi->pars.level != 0)
    print_error("The number of open and close parentheses are not equal");
  if (bi->pars.token == TOKEN_END)
    parser_end(bi, str, len_str);
  return (pos);
}
