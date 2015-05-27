#ifndef BISTRO_H_
# define BISTRO_H_

/*
** ========
** INCLUDES
** ========
*/

# include <getopt.h>
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

# define BI_VERSION	"1.0-snapshot"

# define READER_BUFSIZE	4096

# define OP_NBR		5

# define TYPE_OP	0
# define TYPE_NB	1
# define TYPE_P_OPEN	2
# define TYPE_P_CLOSE	3
# define TYPE_START	4

# define TYPE_NODE_OP	TYPE_OP
# define TYPE_NODE_NB	TYPE_NB

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
typedef unsigned char	t_type;

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

static const	t_op_def	op_def[] =
  {
    {OP_ADD, DEFAULT_ADD, PROP_ADD},
    {OP_SUB, DEFAULT_SUB, PROP_SUB},
    {OP_MUL, DEFAULT_MUL, PROP_MUL},
    {OP_DIV, DEFAULT_DIV, PROP_DIV},
    {OP_MOD, DEFAULT_MOD, PROP_MOD}
  };

typedef struct		s_nb_op
{
  t_node_type		type_node;
  int			op;
  int			level;
  char			*nb;
  size_t		size;
  bool			is_neg;
  bool			is_alloc;
}			t_nb_op;

typedef struct		s_pars
{
  t_type		last_token;
  int			op;
  char			*nb;
  size_t		nb_len;
  bool			parsing_nb;
  int			level;
  bool			is_end;
  t_btree		*btree;
}			t_pars;

struct			s_base
{
  char			*basestr;
  t_fct_isinbase	fct_isinbase;
  t_fct_valueinbase	fct_valueinbase;
};

typedef struct		s_opt
{
  bool			display_help;
  bool			read_file;
  bool			decimal_mode;
}			t_opt;

typedef struct		s_bistro
{
  t_opt			opt;
  t_base		base;
  t_pars		pars;
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

/* options.c */
void		options_printusage(int argc, char **argv);
int		options_parse(t_bistro *bi, int argc, char **argv);

/*
** READER
*/

/* reader.c */
int		reader_readfd(t_bistro *data, int fd, char *filename);

/*
** PARSER
*/

/* parser_btree.c */
int		parser_btree_nb(t_bistro *data, char cas);
int             parser_btree_op(t_bistro *data, char side);
int		parser_btree(t_bistro *data);

/* parser.c */
int		parser(t_bistro *data, char *str, int len);

/*
** UTILS
*/

/* xalloc.c */
void		*xmalloc(size_t n);
void		*xrealloc(void *p, size_t n);

/* print_error.c */
void		print_error(char *format, ...);

#endif /* !BISTRO_H_ */
