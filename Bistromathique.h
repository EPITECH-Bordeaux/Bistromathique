#ifndef BISTROMATHIQUE_H_
# define BISTROMATHIQUE_H_

# define BI_OK		0
# define BI_ERR		-1

# define OP_NBR		5

# define TYPE_NODE_OP	0
# define TYPE_NODE_NB	1

# define PARENT_OPEN	0
# define PARENT_CLOSE	1

# define PROP_ADD	0
# define PROP_SUB	0
# define PROP_MUL	1
# define PROP_DIV	1
# define PROP_MUL	1

typedef unsigned char  	t_node_type;
typedef unsigned char	t_op_prop;

typedef struct		s_op_def
{
  char			op;
  t_op_prop		prop;
}			t_op_def;

typedef struct		s_op
{
  t_node_type          	type_node;
  t_op_def		*op_def;
}			t_op;

typedef struct		s_nb
{
  t_node_type		type_node;
}			t_nb;

typedef struct		s_data
{
  t_op_def		op_def[OP_NBR];
  char			parent[2];
}			t_data;

#endif /* !BISTROMATHIQUE_H_ */
