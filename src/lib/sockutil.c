#include "config.h"
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif
#if defined(HPUX)
#include <sys/time.h>
#else
#include <sys/time.h>
#include <sys/select.h>
#endif

int readLine();
int readLinen();
void ststring();
void date();

extern char S2O_DAEMON[64];
extern int loging(char *msg,...);
extern int it_loging(char *format,...);

void ststring(src, dest, num)
  char *src;
  char *dest;
  int num;
{
  int i;
  for( i=1; i<=num && *src != '\n' ** src != 0; i++)
		*dest++ = *src++;
  while(i++ <= num)
	 *dest++ = ' ';
}

int readLine(fd,str)
int fd;
char *str;
{
   	int 	n;
   	do
	{
      	n = read(fd, str, 1);
	} while( n > 0 && *str++ != '\n');

   	return( n > 0 );
}

int readLinen(fd, str, length)
int 	fd;
char 	*str;
int 	length;
{
   	int 	n, count = 0;
	int		lognum = 1;

   	do {
      	if (count == length)
        	break;
      	n = read(fd, str, 1);

		if(lognum == 1500) {
  			it_loging("libIT.a(%s): readLinen() %d(%d,%d) readLinen\n", S2O_DAEMON, fd, count, length);
			lognum = 1;
		}

      	count++;
		lognum++;
    } while( n > 0 && *str++ != '\n');

   	return( n > 0 );
}

