   /************************************************************************/
   /*  FILENAME     : loging_f.c                                           */
   /*  DISCRIPTION  : message  logging                                     */
   /*                 IT.log에 의해 사용됨.                                */
   /*     -순서: loging() -> IT.log -> loging_f()                          */
   /*  DATE         : 2000. 08. 30                                         */
   /*  MODIFIED     : 2000. 08. 30                                         */
   /*  WRITTEN      : ywoopark                                             */
   /************************************************************************/

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
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <syslog.h>
#include "../IT.extern.h"

extern void timestr(char *tim);

int loging_f(char *fname, char *format,...)
{
  	va_list argptr;
  	FILE *fp, *logfp;
  	char t[16];
	char backfile[256];

  	memset(t,0,sizeof t);
  	timestr(t);

	if (size_check(fname, it_log_size) < 0) {
		memset(backfile, 0, sizeof backfile);		
		sprintf(backfile, "%s.bak", fname);
		fcopy(fname, backfile, 0600);
		if ((fp = fopen(fname, "w")) == NULL) {
			return(-1);
		}
	} else {
  		if((fp=fopen(fname,"a")) == NULL)
    	{
     		openlog("IT TOOLS",LOG_PID,LOG_DAEMON);
     		syslog(LOG_ERR,"loging_f(): file(%s) open error!", fname);
     		closelog();
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

/*
int loging_f(char *fname, char *format,...)
{
  	va_list argptr;
  	FILE *fp, *logfp;
  	char t[16];

  	memset(t,0,sizeof t);
  	timestr(t);

  	if((fp=fopen(fname,"a")) == NULL)
    {
     	openlog("IT TOOLS",LOG_PID,LOG_DAEMON);
     	syslog(LOG_ERR,"loging_f(): file(%s) open error!", fname);
     	closelog();
     	return(-1);
    }
  	fprintf(fp,"%s ",t);
  	va_start(argptr,format);
  	vfprintf(fp,format,argptr);
  	va_end(argptr);
  	fclose(fp);
  	chmod(fname,0600);
  	return(0);
}
*/
