#include "bistro.h"

int		parser_token_parent_open(t_bistro *bi, char *str, int pos)
{
  if (str[pos] != bi->parent[PARENT_OPEN])
    return (TOKEN_ERROR);
  bi->pars.level += 1;
  switch (bi->pars.token)
    {
    case TOKEN_P_CLOSE :
      bi->pars.op = OP_MUL;
      break;
    case TOKEN_NB :
      bi->pars.op = OP_MUL;
      break;
    }
  return (TOKEN_P_OPEN);
}

int		parser_token_parent_close(t_bistro *bi, char *str, int pos)
{
  if (str[pos] != bi->parent[PARENT_CLOSE])
    return (TOKEN_ERROR);
  bi->pars.level -= 1;
  if (bi->pars.level < 0)
    {
      print_error("More parentheses are closed then opened");
      return (TOKEN_ERROR);
    }
  switch (bi->pars.token)
    {
    case TOKEN_OP :
      print_error("An operator can't be followed by a close parenthese");
      return (TOKEN_ERROR);
    }
  return (TOKEN_P_CLOSE);
}

int		parser_token_nb(t_bistro *bi, char *str, int *pos, int len_str)
{
  bi->pars.len_nb = 0;
  while (bi->base.fct_isinbase(&bi->base, str[*pos + bi->pars.len_nb]) == true &&
	 *pos + bi->pars.len_nb < len_str)
    bi->pars.len_nb += 1;
  if (bi->pars.len_nb == 0)
    return (TOKEN_ERROR);
  else if (bi->pars.len_nb > 0 && *pos + bi->pars.len_nb - 1 < len_str)
    bi->pars.nb = str + *pos;
  switch (bi->pars.token)
    {
    case TOKEN_P_CLOSE :
      bi->pars.op = OP_MUL;
      break;
    case TOKEN_NB :
      print_error("Two numbers separed by an espace");
      return (TOKEN_ERROR);
    }
  *pos += bi->pars.len_nb - 1;
  if (*pos + 1 >= len_str)
    return (TOKEN_REBUFF);
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
  bi->pars.op = i;
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
