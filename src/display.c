#include "bistro.h"

int		display_tree(t_btree *btree)
{
  t_node       	*node;
  int		nbr;

  nbr = 0;
  btree->aff = MY_TRUE;
  btree->current = btree->top;
  btree->current->from = FROM_DAD;
  while (nbr >= 0)
    {
      node = btree_get_current_node(btree);
      if (node->from == FROM_DAD)
	{
	  if (((t_nb_op *)node->data)->type_node == TYPE_NODE_OP)
	    printf("%c\n", op_def[((t_nb_op *)node->data)->op].c);
	  else
	    {
	      write(1, ((t_nb_op *)node->data)->nb, ((t_nb_op *)node->data)->size);
	      printf("\n");
	    }
	}
      if (node->from == FROM_DAD && btree_move_down(btree, LEFT) == BT_OK)
	nbr += 1;
      else if ((node->from == FROM_LEFT || node->from == FROM_DAD) &&
	       btree_move_down(btree, RIGHT) == BT_OK)
	nbr += 1;
      else
	{
	  btree_move_up(btree);
	  nbr -= 1;
	}
    }
  printf("\n");
  return (BI_OK);
}
