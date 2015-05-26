#include "btree.h"

void	test(t_node *node, void *data)
{
  printf("Node ID: %d\n", node->id);
}

int		main()
{
  t_btree	*btree;

  btree = btree_init();
  btree->aff = MY_TRUE;
  btree_node_add(btree, NULL, LEFT, DAD);
  btree_node_add(btree, NULL, LEFT, DAD);
  btree_node_add(btree, NULL, RIGHT, DAD);
  btree_exec(btree, &test, EXEC_POST, NULL);
  return (0);
}
