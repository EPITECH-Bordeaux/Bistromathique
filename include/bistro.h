#ifndef BISTRO_H_
# define BISTRO_H_

/*
** ========
** INCLUDES
** ========
*/

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <getopt.h>
# include <stdbool.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

/*
** =============
** DEFINE MACROS
** =============
*/

# define UNUSED __attribute__((unused))

# define BI_OK		0
# define BI_ERR		-1

# define BI_VERSION	"1.0-snapshot"

# define READER_BUFSIZE	4096

# define TOKEN_ERROR    0
# define TOKEN_NB       1
# define TOKEN_OP       2
# define TOKEN_P_OPEN   3
# define TOKEN_P_CLOSE  4
# define TOKEN_ESPACE   5
# define TOKEN_START    6
# define TOKEN_END      7
# define TOKEN_REBUFF   8

# define TYPE_NODE_OP	TOKEN_OP
# define TYPE_NODE_NB	TOKEN_NB

# define PARENT_OPEN	0
# define PARENT_CLOSE	1

# define OP_NBR         5
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
typedef struct s_nb_op		t_nb_op;
typedef struct s_bistro		t_bistro;
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
typedef bool (*t_fct_calc)(t_bistro *bi, t_nb_op *res, t_nb_op *nbleft,
			   t_nb_op *nbright);

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
  t_fct_calc		fct_calc;
}			t_op_def;

struct			s_nb_op
{
  int			op;
  int			level;
  char			*nb;
  size_t		len_nb;
  bool			is_neg;
};

typedef struct          s_bt
{
  t_node_type           type_node;
  t_nb_op               data;
  struct s_bt           *dad;
  struct s_bt           *left;
  struct s_bt           *right;
}                       t_bt;

typedef struct		s_pars
{
  char                  token;
  int                   len_nb;
  char                  *nb;
  bool                  is_neg;
  int                   op;
  int                   level;
  t_bt                  *bt;
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
  int			argv_index;
}			t_opt;

struct			s_bistro
{
  t_opt			opt;
  t_base		base;
  t_pars		pars;
  char			parent[2];
};

/*
** ==========
** PROTOTYPES
** ==========
*/

/*
** GENERAL
*/

/* init.c */
int		init(t_bistro *bi);

/* base.c */
int		base_update(t_base *base, char *str);
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
int		reader_readfile(t_bistro *data, char *filename);
int		reader_readstr(t_bistro *data, char *str);

/*
** PARSER
*/

/* parser_token.c */
int             parser_token_parent_open(t_bistro *bi, char *str, int pos);
int             parser_token_parent_close(t_bistro *bi, char *str, int pos);
int             parser_token_nb(t_bistro *bi, char *str, int *pos, int len_str);
int             parser_token_op(t_bistro *bi, char *str, int pos);
int             parser_token_end(t_bistro *bi, char *str, int pos);

/* parser.c */
int             parser_token(t_bistro *bi, char *str, int *pos, int len_str);
int             parser(t_bistro *bi, char *str, int len_str);

/*
** CALCULATION
*/

/* calc_add.c */
bool		calc_add(t_bistro *bi, t_nb_op *res,
			 t_nb_op *nbleft, t_nb_op *nbright);

/* calc_sub.c */
bool		calc_sub(t_bistro *bi, t_nb_op *res,
			 t_nb_op *nbleft, t_nb_op *nbright);

/* calc_mul.c */
bool		calc_mul(t_bistro *bi, t_nb_op *res,
			 t_nb_op *nbleft, t_nb_op *nbright);

/* calc_div.c */
bool		calc_div(t_bistro *bi, t_nb_op *res,
			 t_nb_op *nbleft, t_nb_op *nbright);

/* calc_mod.c */
bool		calc_mod(t_bistro *bi, t_nb_op *res,
			 t_nb_op *nbleft, t_nb_op *nbright);

/*
** UTILS
*/

/* xalloc.c */
void		xalloc_err();
void		*xmalloc(size_t n);
void		*xrealloc(void *p, size_t n);

/* print_error.c */
void		print_error(char *format, ...);

/*
** =========
** VARIABLES
** =========
*/
UNUSED static t_op_def		op_def[] =
  {
    {OP_ADD, DEFAULT_ADD, PROP_ADD, &calc_add},
    {OP_SUB, DEFAULT_SUB, PROP_SUB, &calc_sub},
    {OP_MUL, DEFAULT_MUL, PROP_MUL, &calc_mul},
    {OP_DIV, DEFAULT_DIV, PROP_DIV, &calc_div},
    {OP_MOD, DEFAULT_MOD, PROP_MOD, &calc_mod}
  };

#endif /* !BISTRO_H_ */
