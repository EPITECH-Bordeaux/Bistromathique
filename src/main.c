#include "bistro.h"

int		main(int ac, char **av)
{
  t_bistro	*data;

  if ((data = init()) == NULL)
    return (EXIT_FAILURE);
  data->pars.btree->aff = MY_TRUE;
  reader_readfd(data, 0, NULL);
  return (EXIT_SUCCESS);
}
