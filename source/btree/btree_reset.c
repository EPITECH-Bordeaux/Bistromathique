#include "btree.h"

int		btree_reset(t_btree *btree)
{
  if (btree == NULL)
    return (BT_ERR);
  btree->move_success = MY_FALSE;
  btree->aff = MY_FALSE;
  btree->current = NULL;
  btree->top = NULL;
  btree->id_max = 0;
  btree->nbr_nodes = 0;
  return (BT_OK);
}
