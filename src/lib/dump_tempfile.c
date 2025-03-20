#include "config.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#if defined(HPUX) || defined(DGUX) || defined(AIX) || defined(LINUX)
#include <sys/file.h>
#else
#include <sys/filio.h>
#endif

extern char S2O_DAEMON[64];
extern int it_loging(char *format,...);

int dump_tempfile(char *dirpath)
{
	char	tempfile[256], str[256];
   	int 	lfp;

	umask(027);

	sprintf(tempfile, "%s/s2odio_%d.tmp", dirpath, getpid());

	if ((lfp = open(tempfile, O_RDWR|O_CREAT, 0640)) < 0)
        return(-1);                        	/* can not open */

    if (lockf(lfp, F_TLOCK, 0) < 0) {
		close(lfp);
       	return(-2);    						/* can not lock */
	}

	sprintf(str, "s2o execute file process id : %d", getpid());
    if (write(lfp, str, strlen(str)) <= 0) {   /* record pid to lockfile */
		close(lfp);
		return(-3);
	}

	close(lfp);
	
	if (unlink(tempfile) < 0) {
		it_loging("libIT.a(%s): dump_tempfile() file(%s) unlink error(%d)\n", S2O_DAEMON, tempfile, errno);
		return(-4);
	}

	return(0);
}
