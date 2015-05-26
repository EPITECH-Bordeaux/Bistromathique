#include "bistro.h"

void		print_error(char *format, ...)
{
  va_list	ap;

  fprintf(stderr, "bistromathique: error: ");
  va_start(ap, format);
  vfprintf(stderr, format, ap);
  va_end(ap);
  fprintf(stderr, "\n");
}
