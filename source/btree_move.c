#include "btree.h"

int		btree_move_top(t_btree *btree)
{
  if (btree == NULL || btree->top == NULL)
    return (BT_ERR);
  if (btree->aff == MY_TRUE)
    printf("Move on top of btree, id: %d to id: %d\n",
	   btree->current->id, btree->top->id);
  btree->current = btree->top;
  return (BT_OK);
}

int		btree_move_up(t_btree *btree)
{
  t_node	*from;
  
  if (btree == NULL)
    return (BT_ERR);
  btree->move_success = MY_FALSE;
  if (btree->current == NULL || btree->current->dad == NULL)
    return (BT_ERR);
  btree->move_success = MY_TRUE;
  if (btree->aff == MY_TRUE)
    printf("Move on dad, id: %d to id: %d\n",
	   btree->current->id, btree->current->dad->id);
  from = btree->current;
  btree->current = btree->current->dad;
  if (btree->current->left == from)
    btree->current->from = FROM_LEFT;
  else
    btree->current->from = FROM_RIGHT;
  return (BT_OK);
}

int		btree_move_down(t_btree *btree, t_from side)
{
  if (btree == NULL)
    return (BT_ERR);
  btree->move_success = MY_FALSE;
  if (btree->current == NULL ||
      (side == RIGHT && btree->current->right == NULL) ||
      (side != RIGHT && btree->current->left == NULL))
    return (BT_ERR);
  btree->move_success = MY_TRUE;
  if (side == RIGHT)
    {
      if (btree->aff == MY_TRUE)
	printf("Move on right, id: %d to id: %d\n",
	       btree->current->id, btree->current->right->id);
      btree->current = btree->current->right;
    }
  else
    {
      if (btree->aff == MY_TRUE)
	printf("Move on left, id: %d to id: %d\n",
	       btree->current->id, btree->current->left->id);
      btree->current = btree->current->left;
    }
  btree->current->from = FROM_DAD;
  return (BT_OK);
}

int		btree_move(t_btree *btree, t_from side)
{
  if (side == DAD)
    return (btree_move_up(btree));
  else
    return (btree_move_down(btree, side));
  return (BT_OK);
}
