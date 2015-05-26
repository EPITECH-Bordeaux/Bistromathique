#include "bistro.h"

int		parser(t_bistro *data, char *str, int len, int is_end)
{
  int       	i;

  i = 0;
  while (i < len)
    {
      printf("str[%d] = %c\n", i, str[i]);
      i++;
    }
  return (i);
}
