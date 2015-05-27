#include "bistro.h"

int	base_update(t_base *base, char *str)
{
  int	i;
  int	j;

  i = 0;
  while (str[i])
    {
      /* Check if base already contains that caracter */
      j = 0;
      while (j < i)
	{
	  if (str[j] == str[i])
	    {
	      print_error("Invalid base: Contains several times the \
character '%c'", str[i]);
	      return (BI_ERR);
	    }
	  j++;
	}
      i++;
    }
  /* Check base len */
  if (i < 2)
    {
      print_error("Invalid base: Must contain at least two characters");
      return (BI_ERR);
    }
  /* Copy base in memory and update base functions */
  base->basestr = strdup(str);
  if (base->basestr == NULL)
    xalloc_err();
  base->fct_isinbase = &base_str_isin;
  base->fct_valueinbase = &base_str_value;
  return (BI_OK);
}

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
