#include "bistro.h"

/*
** Display error message and abort program.
*/
void	xalloc_err()
{
  char	*msg;

  msg = "\nFatal error: memory exhausted!\n";
  write(STDERR_FILENO, msg, strlen(msg));
  abort();
}

/*
** Allocate n bytes and returns a pointer to the allocated memory.
** On error, a message is displayed and program abort.
*/
void	*xmalloc(size_t n)
{
  void	*p;

  p = malloc(n);
  if (p == 0)
    xalloc_err();
  return (p);
}

/*
** Allocate n bytes and returns a pointer to the allocated memory.
** On error, a message is displayed and program abort.
*/
void	*xrealloc(void *p, size_t n)
{
  p = realloc(p, n);
  if (p == 0)
    xalloc_err();
  return (p);
}
