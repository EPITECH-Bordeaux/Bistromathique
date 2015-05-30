#include "bistro.h"

bool	calc_add(t_bistro *bi, t_nb_op **pile_nb)
{
  (*pile_nb)->next->nbr = (*pile_nb)->next->nbr + (*pile_nb)->nbr;
  (*pile_nb) = (*pile_nb)->next;
  return (false);
}
