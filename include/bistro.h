#ifndef BISTRO_H_
# define BISTRO_H_

/*
** ========
** INCLUDES
** ========
*/

# include <stdbool.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
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

# define OP_ADD		0
# define OP_SUB		1
# define OP_MUL		2
# define OP_DIV		3
# define OP_MOD		4

# define DEFAULT_ADD	'+'
# define DEFAULT_SUB	'-'
# define DEFAULT_MUL	'*'
# define DEFAULT_DIV	'/'
# define DEFAULT_MOD	'%'
# define DEFAULT_P_OPEN	'('
# define DEFAULT_P_CLOSE ')'

# define PROP_ADD	0
# define PROP_SUB	0
# define PROP_MUL	1
# define PROP_DIV	1
# define PROP_MOD	1

typedef struct s_base		t_base;
/*
** ===============
** TYPES SHORTCUTS
** ===============
*/

typedef unsigned char  	t_node_type;
typedef unsigned char	t_op_prop;

typedef bool (*t_fct_isinbase)(t_base *base, char c);
typedef char (*t_fct_valueinbase)(t_base *base, char c);

/*
** ==========
** STRUCTURES
** ==========
*/

typedef struct		s_op_def
{
  size_t		op;
  char			c;
  t_op_prop		prop;
}			t_op_def;

typedef struct		s_nb_op
{
  t_node_type		type_node;
  t_op_def		*op_def;
  int			level;
  char			*nb;
  size_t		size;
  t_my_bool		is_neg;
  t_my_bool		is_alloc;
}			t_nb_op;

typedef struct		s_pars
{
  t_op_def		*op;
  char			*nb;
  size_t		nb_len;
  t_my_bool		parsing_nb;
  int			level;
  t_btree		*btree;
}			t_pars;

struct			s_base
{
  char			*basestr;
  t_fct_isinbase	fct_isinbase;
  t_fct_valueinbase	fct_valueinbase;
};

typedef struct		s_bistro
{
  t_base		base;
  t_pars		pars;
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

/* base.c */
bool		base_dec_isin(t_base *base, char c);
char		base_dec_value(t_base *base, char c);
bool		base_str_isin(t_base *base, char c);
char		base_str_value(t_base *base, char c);

/*
** READER
*/

/* reader.c */
int		reader_readfd(t_bistro *data, int fd, char *filename);

/*
** PARSER
*/

/* parser.c */
int		parser(t_bistro *data, char *str, int len, bool is_end);

/*
** UTILS
*/

/* xalloc.c */
void		*xmalloc(size_t n);
void		*xrealloc(void *p, size_t n);

/* print_error.c */
void		print_error(char *format, ...);

#endif /* !BISTRO_H_ */
