#include "bistro.h"

void	options_printusage(int argc, char **argv)
{
  printf("Usage: %s [OPTION]... [EXPRESSION]...\n\n",
	 argc > 0 ? argv[0] : "./COMMAND");
  printf(
"  -b, --base=BASE            Help\n");
  printf(
"  -d, --decimal              Help\n");
  printf(
"  -f, --file                 Help\n");
  printf(
"  -o, --operators=OPERATORS  Help\n");
  printf(
"      --operator-add=CHAR    Help\n\
      --operator-sub=CHAR    Help\n\
      --operator-mul=CHAR    Help\n\
      --operator-div=CHAR    Help\n\
      --operator-mod=CHAR    Help\n");
  printf("\n\nBistromathique, version "BI_VERSION"\n\
Author(s): Nathan Poirier <nathan@poirier.io>,\n\
           Timothy Greil <timothy.greil@epitech.eu>\n");
}

int	option_setop(t_bistro *bi, int op, char c)
{
  if (op < 0 || op >= OP_NBR)
    {
      print_error("Operator: You try to change an operator that doesn't \
exist");
      return (BI_ERR);
    }
  op_def[op].c = c;
  return (BI_OK);
}

int	option_setops(t_bistro *bi, char *ops)
{
  int	i;

  i = 0;
  while (ops[i])
    {
      if (option_setop(bi, i, ops[i]) == BI_ERR)
	return (BI_ERR);
      i++;
    }
  /* '--operators' must change at least 4 operators (add, sub, mul, div).
     Others are optionnal. */
  if (i < 4)
    {
      print_error("Operators: You must specify at least 4 operators");
      return (BI_ERR);
    }
  return (BI_OK);
}

int	options_parse(t_bistro *bi, int argc, char **argv)
{
  int	c;
  int	opt_index;
  int	opt_op_offset;

  opt_op_offset = 300;
  struct option long_options[] =
    {
      {"help",		no_argument,		0, 'h'},
      {"base",		required_argument,	0, 'b'},
      {"file",		no_argument,		0, 'f'},
      {"decimal",	no_argument,		0, 'd'},
      {"operators",	required_argument,	0, 'o'},
      {"operator-add",	required_argument,	0, opt_op_offset + OP_ADD},
      {"operator-sub",	required_argument,	0, opt_op_offset + OP_SUB},
      {"operator-mul",	required_argument,	0, opt_op_offset + OP_MUL},
      {"operator-div",	required_argument,	0, opt_op_offset + OP_DIV},
      {"operator-mod",	required_argument,	0, opt_op_offset + OP_MOD},
      {0, 0, 0, 0}
    };

  opt_index = 0;
  while ((c = getopt_long(argc, argv, "hb:fdo:",
			  long_options, &opt_index)) != -1)
    {
      if (c == 'h')
	bi->opt.display_help = true;
      else if (c == 'b')
	{
	  if (base_update(&bi->base, optarg) == BI_ERR)
	    return (BI_ERR);
	}
      else if (c == 'f')
	bi->opt.read_file = true;
      else if (c == 'd')
	bi->opt.decimal_mode = true;
      else if (c == 'o')
	{
	  if (option_setops(bi, optarg) == BI_ERR)
	    return (BI_ERR);
	}
      else if (c >= opt_op_offset && c <= opt_op_offset + OP_MOD)
	{
	  if (strlen(optarg) != 1)
	    {
	      print_error("option '--%s' require a single caracter",
			  long_options[opt_index].name);
	      return (BI_ERR);
	    }
	  if (option_setop(bi, c - opt_op_offset, optarg[0]) == BI_ERR)
	    return (BI_ERR);
	}
      else
	{
	  fprintf(stderr, "Try '%s --help' for more information.\n",
		  argc > 0 ? argv[0] : "./COMMAND");
	  return (BI_ERR);
	}
    }
  if (optind < argc)
    bi->opt.argv_index = optind;
  else
    bi->opt.argv_index = 0;
  return (BI_OK);
}
