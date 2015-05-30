#include "bistro.h"

int		parser_btree_op(t_bistro *bi)
{
  t_bt		*new;

  printf("IN ADDR: %p\n", (void *)bi->pars.bt);
  new = xmalloc(sizeof(t_bt));
  new->type_node = TYPE_NODE_OP;
  new->data.op = bi->pars.op;
  new->data.level = bi->pars.level;
  if (bi->pars.token == TOKEN_P_OPEN)
    new->data.level -= 1;
  printf("%c (level :%d) (addr: %p)\n", op_def[bi->pars.op].c, new->data.level, (void *)new);
  if (bi->pars.bt->type_node == TYPE_NODE_NB)
    new->left = bi->pars.bt;
  else if (op_def[bi->pars.bt->data.op].prop >= op_def[bi->pars.op].prop ||
	   bi->pars.bt->data.level > bi->pars.level)
    {
      while (bi->pars.bt->dad != NULL && (op_def[bi->pars.bt->data.op].prop >=
				     op_def[bi->pars.op].prop ||
				     bi->pars.bt->data.level > bi->pars.level))
	{
	  bi->pars.bt = bi->pars.bt->dad;
	}
      if (bi->pars.bt->dad == NULL &&
	  (op_def[bi->pars.bt->data.op].prop >= op_def[bi->pars.op].prop ||
	   bi->pars.bt->data.level > bi->pars.level))
	{
	  bi->pars.bt->dad = new;
	  new->left = bi->pars.bt;
	}
      else
	{
	  new->dad = bi->pars.bt->dad;
	  new->dad->right = new;
	  new->left = bi->pars.bt;
	  new->left->dad = new;
	}
    }
  else
    {
      new->left = bi->pars.bt->right;
      bi->pars.bt->right = new;
      new->dad = bi->pars.bt;
    }
  bi->pars.bt = new;
  bi->pars.op = -1;
  bi->pars.last_node = TYPE_NODE_OP;
  return (BI_OK);
}

int		parser_btree_nb(t_bistro *bi)
{
  t_bt		*new;

  write(1, bi->pars.nb, bi->pars.len_nb);
  write(1, "\n", 1);
  new = xmalloc(sizeof(t_bt));
  new->type_node = TYPE_NODE_NB;
  new->data.nb = bi->pars.nb;
  new->data.is_neg = bi->pars.is_neg;
  new->data.len_nb = bi->pars.len_nb;
  if (bi->pars.bt == NULL)
    bi->pars.bt = new;
  else
    bi->pars.bt->right = new;
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
  pars->bt = NULL;
  return (BI_OK);
}

int		print_btree(t_bt *node)
{
  if (node->type_node == TYPE_NODE_NB)
    {
      write(1, "Nb :", 4);
      write(1, node->data.nb, node->data.len_nb);
      write(1, "\n", 1);
    }
  else
    printf("Op: %c\n", op_def[node->data.op].c);
  if (node->left)
    {
      printf("LEFT\n");
      print_btree(node->left);
    }
  if (node->right)
    {
      printf("RIGHT\n");
      print_btree(node->right);
    }
  printf("DAD\n");
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


  printf("---- BTREE ----\n");
  while (bi->pars.bt->dad != NULL)
    bi->pars.bt = bi->pars.bt->dad;
  print_btree(bi->pars.bt);



  return (pos - bi->pars.len_nb);
}
