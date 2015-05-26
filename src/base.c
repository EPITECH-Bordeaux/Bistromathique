#include "bistro.h"

bool	base_dec_isin(t_base *base, char c)
{
  return (c >= '0' && c <= '9');
}

char	base_dec_value(t_base *base, char c)
{
  return (c - '0');
}

bool	base_str_isin(t_base *base, char c)
{
  int	i;

  i = 0;
  while (base->basestr[i])
    {
      if (base->basestr[i] == c)
	return (true);
      i++;
    }
  return (false);
}

char	base_str_value(t_base *base, char c)
{
  int	i;

  i = 0;
  while (base->basestr[i])
    {
      if (base->basestr[i] == c)
	return (i);
      i++;
    }
  return (-1);
}
