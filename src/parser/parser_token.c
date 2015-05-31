#include "bistro.h"

int		parser_token_parent_open(t_bistro *bi, char *str, int pos)
{
  if (str[pos] != parent_def[PARENT_OPEN])
    return (TOKEN_ERROR);
  bi->pars.level += 1;
  switch (bi->pars.token)
    {
    case TOKEN_P_CLOSE :
      parser_btree_op(bi, OP_MUL, bi->pars.level);
      break;
    case TOKEN_NB :
      parser_btree_op(bi, OP_MUL, bi->pars.level);
      break;
    }
  return (TOKEN_P_OPEN);
}

int		parser_token_parent_close(t_bistro *bi, char *str, int pos)
{
  if (str[pos] != parent_def[PARENT_CLOSE])
    return (TOKEN_ERROR);
  bi->pars.level -= 1;
  if (bi->pars.level < 0)
    {
      print_error("More parentheses are closed then opened");
      return (TOKEN_ERROR);
    }
  switch (bi->pars.token)
    {
    case TOKEN_P_OPEN :
      print_error("An open parenthese can't be followed by a close parenthese");
      return (TOKEN_ERROR);
    case TOKEN_OP :
      print_error("An operator can't be followed by a close parenthese");
      return (TOKEN_ERROR);
    }
  return (TOKEN_P_CLOSE);
}

int		parser_token_nb(t_bistro *bi, char *str, int *pos, int len_str)
{
  int		len_nb;
  
  len_nb = 0;
  while (*pos + len_nb < len_str &&
	 bi->base.fct_isinbase(&bi->base, str[*pos + len_nb])
	 == true)
    len_nb += 1;
  if (len_nb == 0)
    return (TOKEN_ERROR);
  switch (bi->pars.token)
    {
    case TOKEN_P_CLOSE :
      parser_btree_op(bi, OP_MUL, bi->pars.level);
      break;
    case TOKEN_NB :
      print_error("Two numbers separed by an espace");
      return (TOKEN_ERROR);
    }
  if (*pos + len_nb >= len_str)
    return (TOKEN_REBUFF);
  *pos += len_nb - 1;
  parser_btree_nb(bi, str, *pos, len_nb);
  return (TOKEN_NB);
}

int		parser_token_op(t_bistro *bi, char *str, int pos)
{
  int		i;

  i = 0;
  while (i < OP_NBR && op_def[i].c != str[pos])
    i += 1;
  if (i >= OP_NBR)
    return (TOKEN_ERROR);
  switch (bi->pars.token)
    {
    case TOKEN_P_OPEN :
      print_error("A close parenthese can't be followed by an operator");
      return (TOKEN_ERROR);
    case TOKEN_OP :
      print_error("An operator is next to another");
      return (TOKEN_ERROR);
    case TOKEN_START :
      print_error("The calcul can't start with an operator");
      return (TOKEN_ERROR);
    }
  parser_btree_op(bi, i, bi->pars.level);
  return (TOKEN_OP);
}

int		parser_token_end(t_bistro *bi, char *str, int pos)
{
  if (str[pos] != '\n' && str[pos] != '\0' && str[pos] != ';')
    return (TOKEN_ERROR);
  switch (bi->pars.token)
    {
    case TOKEN_OP:
      print_error("An operator ending the expression");
      return (TOKEN_ERROR);
    }
  return (TOKEN_END);
}

int		parser_token_unknow(t_bistro *bi, char *str, int pos)
{
  int		i;

  i = 0;
  if (bi->base.fct_isinbase(&bi->base, str[pos]) == true ||
      str[pos] == parent_def[PARENT_OPEN] ||
      str[pos] == parent_def[PARENT_CLOSE])
    return (TOKEN_ERROR);
  while (i < OP_NBR)
    {
      if (op_def[i].c == str[pos])
	return (TOKEN_ERROR);
      i += 1;
    }
  print_error("Unknow character: '%c'", str[pos]);
  return (TOKEN_ERROR);
}
