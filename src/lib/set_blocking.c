#include <stdio.h>
#include <fcntl.h>

int set_blocking(int fd, int set)
{
  int val;
#define FLAG_TO_SET O_NDELAY

  if((val = fcntl(fd, F_GETFL, 0)) == -1)
	return -1;
  if(set) /* Turn blocking on - ie. clear nonblock flag */
	val &= ~FLAG_TO_SET;
  else
    val |= FLAG_TO_SET;
  return fcntl( fd, F_SETFL, val);
#undef FLAG_TO_SET
}
