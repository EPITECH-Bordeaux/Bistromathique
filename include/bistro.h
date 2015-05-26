#ifndef BISTRO_H_
# define BISTRO_H_

/*
** ========
** INCLUDES
** ========
*/

# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include "btree.h"

/*
** =============
** DEFINE MACROS
** =============
*/

# define BI_OK		0
# define BI_ERR		-1

# define READER_BUFSIZE	4096

# define OP_NBR		5

# define TYPE_NODE_OP	0
# define TYPE_NODE_NB	1

# define PARENT_OPEN	0
# define PARENT_CLOSE	1

# define ADD		0
# define SUB		1
# define MUL		2
# define DIV		3
# define MOD		4

# define DEFAULT_ADD	'+'
# define DEFAULT_SUB	'-'
# define DEFAULT_MUL	'*'
# define DEFAULT_DIV	'/'
# define DEFAULT_MOD	'%'

# define PROP_ADD	0
# define PROP_SUB	0
# define PROP_MUL	1
# define PROP_DIV	1
# define PROP_MOD	1

/*
** ===============
** TYPES SHORTCUTS
** ===============
*/

typedef unsigned char  	t_node_type;
typedef unsigned char	t_op_prop;

/*
** ==========
** STRUCTURES
** ==========
*/

typedef struct		s_op_def
{
  size_t		op;
  char			op_c;
  t_op_prop		prop;
}			t_op_def;

typedef struct		s_nb_op
{
  t_node_type		type_node;
  t_op_def		*op_def;
  char			*nbr;
  size_t		size;
  t_my_bool		is_neg;
  t_my_bool		is_alloc;
}			t_nb_op;

typedef struct		s_pars
{
  
  t_btree		*btree;
}			t_pars;

typedef struct		s_bistro
{
  t_pars		*pars;
  char			*base;
  t_op_def		op_def[OP_NBR];
  char			parent[2];
}			t_bistro;

/*
** ==========
** PROTOTYPES
** ==========
*/

/*
** General
*/

/* init.c */
t_bistro	*init();

/*
** READER
*/

/* reader.c */
int		reader_readfd(t_bistro *data, int fd, char *filename);

/*
** PARSER
*/

/* parser.c */
int		parser(t_bistro *data, char *str, int len, int is_end);

/*
** UTILS
*/

/* xalloc.c */
void		*xmalloc(size_t n);
void		*xrealloc(void *p, size_t n);

/* print_error.c */
void		print_error(char *format, ...);

#endif /* !BISTRO_H_ */
