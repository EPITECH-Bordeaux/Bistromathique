#include "bistro.h"

int		init(t_bistro *bi)
{
  memset(bi, 0, sizeof(t_bistro));
  bi->base.fct_isinbase = &base_dec_isin;
  bi->base.fct_valueinbase = &base_dec_value;
  return (BI_OK);
}
