#ifndef BTREE_H_
# define BTREE_H_

# include <stdlib.h>
# include <stdio.h>

# define BT_OK		0
# define BT_ERR		-1

# define MY_FALSE	0
# define MY_TRUE	1

# define EXEC_PRE	0
# define EXEC_IN       	1
# define EXEC_POST	2

# define DAD		0
# define LEFT		1
# define RIGHT		2
# define FROM_DAD	DAD
# define FROM_LEFT	LEFT
# define FROM_RIGHT	RIGHT
# define FROM_INIT	3
# define FROM_OTHER	4

typedef char		t_from;
typedef char		t_my_bool;
typedef unsigned int	t_bt_id;

typedef struct		s_node
{
  void			*data;
  t_from		from;
  t_bt_id		id;
  struct s_node		*dad;
  struct s_node		*left;
  struct s_node		*right;
}			t_node;

typedef struct		s_btree
{
  t_my_bool		aff;
  t_my_bool		move_success;
  size_t		nbr_nodes;
  t_bt_id		id_max;
  struct s_node		*top;
  struct s_node		*current;
}			t_btree;

/*
** btree_init.c
*/
t_btree			*btree_init();

/*
** btree_reset.c
*/
int			btree_reset(t_btree *btree);

/*
** btree_node_add.c
*/
int			btree_node_add_link(t_btree *btree, t_node *node,
					t_from side, t_from side_new);
t_node			*btree_node_add(t_btree *btree, void *data,
					t_from side, t_from side_new);

/*
** btree_move.c
*/
int			btree_move_top(t_btree *btree);
int			btree_move_up(t_btree *btree);
int			btree_move_down(t_btree *btree, t_from side);
int			btree_move(t_btree *btree, t_from side);

/*
** btree_get.c
*/
t_node			*btree_get_current_node(t_btree *btree);
void			*btree_get_current_data(t_btree *btree);
t_node			*btree_get_top_node(t_btree *btree);
void			*btree_get_top_data(t_btree *btree);

/*
** btree_free.c
*/
void			btree_free(t_btree *btree);

/*
** btree_aff.c
*/
int			btree_exec(t_btree *btree, void (*f)(t_node *node, void *data),
				   char type, void *data);

#endif /* !BTREE_H_ */
