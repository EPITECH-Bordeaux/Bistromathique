#include "bistro.h"

int		main(int ac, char **av)
{
  t_bistro	bi;
  int		i;

  if (init(&bi) == BI_ERR)
    return (EXIT_FAILURE);
  if (options_parse(&bi, ac, av) == BI_ERR)
    return (EXIT_FAILURE);
  if (bi.opt.display_help)
    {
      options_printusage(ac, av);
      return (EXIT_SUCCESS);
    }
  if (bi.opt.argv_index == 0)
    reader_readfd(&bi, 0, NULL);
  else
    {
      i = bi.opt.argv_index;
      while (i < ac)
	{
	  if (bi.opt.read_file)
	    reader_readfile(&bi, av[i]);
	  else
	    reader_readstr(&bi, av[i]);
	  i++;
	}
    }
  return (EXIT_SUCCESS);
}
