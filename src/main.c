#include "bistro.h"

int		main(int ac, char **av)
{
  t_bistro	*bi;

  if ((bi = init()) == NULL)
    return (EXIT_FAILURE);
  if (options_parse(bi, ac, av) == BI_ERR)
    return (EXIT_FAILURE);
  if (bi->opt.display_help)
    {
      options_printusage(ac, av);
      return (EXIT_SUCCESS);
    }
  reader_readfd(bi, 0, NULL);
  return (EXIT_SUCCESS);
}
