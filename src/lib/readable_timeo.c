/* include readable_timeo */
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "../IT.extern.h"

#if defined(HPUX)
#include <sys/time.h>
#else
#include <sys/time.h>
#include <sys/select.h>
#endif

extern int it_loging(char *format,...);
int
readable_timeo(int fd, int sec)
{
	fd_set			rset;
	struct timeval	tv;

	FD_ZERO(&rset);
	FD_SET(fd, &rset);

	tv.tv_sec = sec;
	tv.tv_usec = 0;

	return(select(fd+1, &rset, NULL, NULL, &tv));
		/* 4> 0 if descriptor is readable */
}
/* end readable_timeo */

int
Readable_timeo(int fd, int sec)
{
	int		n;

	if ( (n = readable_timeo(fd, sec)) < 0)
		it_loging("libIT.a(%s): readable_timeo() function error.%d,%d\n", S2O_DAEMON, fd,n);
	return(n);
}
