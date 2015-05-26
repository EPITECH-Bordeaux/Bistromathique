#include "btree.h"

void		btree_exec_func(t_node *node,void (*f)(t_node *node, void *data),
				char type, void *data)
{
  if (type == EXEC_PRE && node->from == FROM_DAD)
    f(node, data);
  else if (type == EXEC_IN && (node->from == FROM_LEFT || node->left == NULL))
    f(node, data);
  else if (type == EXEC_POST &&
	   (node->from == FROM_RIGHT || node->right == NULL))
    f(node, data);
}

int		btree_exec(t_btree *btree, void (*f)(t_node *node, void *data),
			   char type, void *data)
{
  t_my_bool    	flag;
  t_node	*tmp;

  flag = MY_TRUE;
  tmp = btree->current;
  btree->current = btree->top;
  btree->current->from = FROM_DAD;
  while (flag == MY_TRUE)
    {
      btree_exec_func(btree->current, f, type, data);
      if (btree->current->from == FROM_DAD && btree->current->left != NULL)
	btree_move(btree, LEFT);
      else if ((btree->current->from == FROM_DAD && btree->current->right != NULL) ||
	       (btree->current->from == FROM_LEFT && btree->current->right != NULL))
	btree_move(btree, RIGHT);
      else if (btree->current->dad != NULL)
	btree_move(btree, DAD);
      else
	flag = MY_FALSE;
    }
  btree->current = tmp;
  return (BT_OK);
}
