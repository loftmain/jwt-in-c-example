   /************************************************************************/
   /*  FILENAME     : get_s2opid.c                                         */
   /*  DISCRIPTION  : s2o 데몬의 pid를 읽는다.                             */
   /*  DATE         : 2018. 03. 07                                         */
   /*  WRITTEN      :                                                      */
   /*  MODIFIED     :                                                      */
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
#include <stdlib.h>
#include <time.h>
#include "../IT.extern.h"

extern int loging(char *msg,...);

int get_s2opid(char* homedir, char *daemon, int seq_num)
{
	FILE *fp;
	int sernum;
	int ret;
	char pidfile[256];

	memset(pidfile, 0, sizeof pidfile);

	if (seq_num > 0)
		sprintf(pidfile, "%s/pid/%s_%d.pid", homedir,daemon, seq_num);
	else
		sprintf(pidfile, "%s/pid/%s.pid", homedir, daemon);

	if((fp=fopen(pidfile,"r")) == NULL)
	{
		loging("file(%s) open error!\n", pidfile);
		return(-1);
	}

	ret = fscanf(fp,"%d", &sernum);
	fclose(fp);

	if(sernum < 0) return(-1);

	return(sernum);
}

int compare_s2opid(char* _DAEMON)
{
	FILE *fp;
	int sernum;
	int ret;
	int pid = getpid();

	if (strlen(S2O_PIDFILE) == 0) return 0;	

	if((fp=fopen(S2O_PIDFILE, "r")) == NULL)
	{
		it_loging("libIT.a(%s): compare_s2opid() file(%s) open error!\n", _DAEMON, S2O_PIDFILE);
		return(0);
	}

	ret = fscanf(fp,"%d", &sernum);
	fclose(fp);

	if (sernum == pid) return 1;
	else {
		it_loging("libIT.a(%s): compare_s2opid() Terminate the program because DAEMON(%s) pid and s2o pid file's pid are different. ( daemonpid:%d, s2opidfile:%d)\n", _DAEMON, _DAEMON, sernum, pid);
		exit(1);
	}
}

