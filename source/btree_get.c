#include "btree.h"

int		btree_get_check(t_btree *btree)
{
  if (btree == NULL)
    return (BT_ERR);
  return (BT_OK);
}

t_node		*btree_get_current_node(t_btree *btree)
{
  if (btree_get_check(btree) == BT_ERR)
    return (NULL);
  return (btree->current);
}

void		*btree_get_current_data(t_btree *btree)
{
  if (btree_get_check(btree) == BT_ERR)
    return (NULL);
  if (btree->current == NULL)
    return (NULL);
  return (btree->current->data);
}

t_node		*btree_get_top_node(t_btree *btree)
{
  if (btree_get_check(btree) == BT_ERR)
    return (NULL);
  return (btree->top);
}

void		*btree_get_top_data(t_btree *btree)
{
  if (btree_get_check(btree) == BT_ERR)
    return (NULL);
  if (btree->top == NULL)
    return (NULL);
  return (btree->top->data);
}
