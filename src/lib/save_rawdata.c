#include "config.h"
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <syslog.h>
#include "../IT.extern.h"

extern void timestr2(char *tim);
extern int it_loging(char *format,...);

int save_rawdata(char* ithome, char *filename, char *format,...)
{
  	va_list argptr;
  	FILE *fp, *logfp;
  	char t[16];
	char backfile[256];
	char fname[256];
	char mkdir[256];
	char dumpdir[256];
	struct stat s1;
	int ret;

	memset(dumpdir, 0, sizeof dumpdir);
	sprintf(dumpdir, "%s/dump", ithome);

    if (stat(dumpdir, &s1) < 0)  {
        sprintf(mkdir, "/bin/mkdir -p %s", dumpdir);
        ret = system(mkdir);
    }

	memset(fname, 0, sizeof fname);
	sprintf(fname, "%s/%s", dumpdir, filename);

  	memset(t,0,sizeof t);
  	timestr2(t);

	if (size_check(fname, save_rawdata_size) < 0) {
		memset(backfile, 0, sizeof backfile);		
		sprintf(backfile, "%s.bak", fname);
		fcopy(fname, backfile, 0600);
		if ((fp = fopen(fname, "w")) == NULL) {
			it_loging("libIT.a(%s): save_rawdata(): file(%s) open error!", S2O_DAEMON, fname);
			return(-1);
		}
	} else {
  		if((fp=fopen(fname,"a")) == NULL)
    	{
			it_loging("libIT.a(%s): save_rawdata(): file(%s) open error!!", S2O_DAEMON, fname);
     		return(-1);
    	}
	}
  	fprintf(fp,"%s ",t);
  	va_start(argptr,format);
  	vfprintf(fp,format,argptr);
  	va_end(argptr);
  	fclose(fp);
  	chmod(fname,0600);
  	return(0);
}

