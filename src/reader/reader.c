#include "bistro.h"

/*
** Malloc buffers.
** The uparsed caracters are copied to the new buffer.
** New buffer size depends on the number of uparsed caracters and the previous
** buffer size.
*/
void	reader_buf_alloc(char **buf, int *bufsize, int rlen, int remaining)
{
  char	*nbuf;

  if (*buf == NULL)
    {
      *buf = xmalloc(READER_BUFSIZE);
      *bufsize = READER_BUFSIZE;
      return ;
    }
  /* TODO: Decrease bufsize dynamicly and good algo for increasing algo size */
  if (remaining > *bufsize / 2)
    *bufsize += READER_BUFSIZE;
  nbuf = xmalloc(*bufsize);
  if (remaining > 0)
    memcpy(nbuf, *buf + (rlen - remaining), remaining);
  *buf = nbuf;
}

/*
** Read a file descriptor and pass the content to the parser.
** Readed content is stored in a 'malloced' buffer and passed to parser while
** reading.
** The parser return how many character has been parsed. The unparsed
** characters are copied to the next buffer to be parsed in the next read.
*/
int	reader_readfd(t_bistro *data, int fd, char *filename)
{
  int	rlen;
  char	*buf;
  int	bufsize;
  int	readed;
  int	remaining;

  buf = NULL;
  reader_buf_alloc(&buf, &bufsize, 0, 0);
  remaining = 0;
  while ((rlen = read(fd, buf + remaining, bufsize - remaining)) >= 0)
    {
      if (rlen > 0 && buf[rlen - 1] == '\n')
	rlen--;
      readed = parser(data, buf, rlen + remaining, (rlen == 0));
      if (readed < 0)
	return (BI_ERR);
      if (rlen == 0)
	break;
      rlen += remaining;
      remaining = rlen - readed;
      reader_buf_alloc(&buf, &bufsize, rlen, remaining);
    }
  if (rlen < 0)
    {
      print_error("Error while reading '%s': %m",
		  (filename != NULL) ? filename : "standard input");
      return (BI_ERR);
    }
  return (BI_OK);
}
