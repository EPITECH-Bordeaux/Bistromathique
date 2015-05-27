#include "bistro.h"

int		main(int ac, char **av)
{
  t_bistro	*data;

  printf("\u2510\n\u2518\n");
  if ((data = init()) == NULL)
    return (EXIT_FAILURE);  
  reader_readfd(data, 0, NULL);
  return (EXIT_SUCCESS);
}
