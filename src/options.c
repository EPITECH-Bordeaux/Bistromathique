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
	fprintf(stderr, "TODO: base=%s\n", optarg);
      else if (c == 'f')
	bi->opt.read_file = true;
      else if (c == 'd')
	bi->opt.decimal_mode = true;
      else if (c == 'o')
	fprintf(stderr, "TODO: operators=%s\n", optarg);
      else if (c >= opt_op_offset && c <= opt_op_offset + OP_MOD)
	fprintf(stderr, "TODO: operator-?=%s\n", optarg);
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
