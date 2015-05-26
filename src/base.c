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
  return (true);
}

char	base_str_value(t_base *base, char c)
{
  return (0);
}
