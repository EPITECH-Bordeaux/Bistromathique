#include "bistro.h"

int		main(int ac, char **av)
{
  t_bistro	*data;

  if ((data = init()) == NULL)
    return (EXIT_FAILURE);  
  reader_readfd(data, 0, NULL);
  return (EXIT_SUCCESS);
}
