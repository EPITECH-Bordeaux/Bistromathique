#include "bistro.h"

int		main(int ac, char **av)
{
  t_bistro	*data;

  data = init();
  parser(data);
  return (1);
}
