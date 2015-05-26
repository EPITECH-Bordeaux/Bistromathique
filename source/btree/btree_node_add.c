#include "btree.h"

int		btree_node_add_link(t_btree *btree, t_node *new,
				    t_from side_cur, t_from side_new)
{
  if (btree->aff == MY_TRUE)
      printf("\tLinked with id: %d\n", btree->current->id);
  if (side_cur == DAD)
    {      
      if (side_new == RIGHT)
	new->right = btree->current;
      else
	new->left = btree->current;
      btree->current->dad = new;
      if (btree->current == btree->top)
	btree->top = new;
    }
  else if (side_cur == RIGHT)
    {
      btree->current->right = new;
      new->dad = btree->current;
    }
  else
    {
      btree->current->left = new;
      new->dad = btree->current;
    }
  return (BT_OK);
}

t_node		*btree_node_add(t_btree *btree, void *data,
				t_from side_cur, t_from side_new)
{
  t_node	*new;

  if (btree == NULL)
    return (NULL);
  if ((new = malloc(sizeof(t_node))) == NULL)
    return (NULL);
  new->data = data;
  new->dad = NULL;
  new->left = NULL;
  new->right = NULL;
  new->from = FROM_INIT;
  new->id = btree->id_max;
  btree->id_max += 1;
  btree->nbr_nodes += 1;
  if (btree->aff == MY_TRUE)
    printf("Node created with id: %d\n", new->id);
  if (btree->current == NULL)
    {
      btree->current = new;
      btree->top = new;
      return (BT_OK);
    }
  else
    btree_node_add_link(btree, new, side_cur, side_new);
  return (new);
}
