/*
   $Id: get_process.c,v 1.7 2003/06/30 srp Exp $

   Copyright (c) 2000, 2001, 2002, 2003
             i-TOP System Inc.  All rights reserved.

   2003-06-30
     * 서버의 process name 정보를 읽어서 배열에 저장.
*/
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../IT.extern.h"

#if defined(HPUX)
#define PS      "/usr/bin/ps -eo user,pid,ppid,state,args|egrep -v 'COMMAND|ps -eo'"
#define PS_CNT  "/usr/bin/ps -ef|grep '%s' |grep -v grep |wc -l"
#define PS_CNT2 "/usr/bin/ps -eo user,pid,ppid,args|grep '%s'|egrep -v 'COMMAND|ps -eo'"
#define PS_CNT3 "/usr/bin/ps -eo user,pid,ppid,args|egrep '%s|%s'|egrep -v 'COMMAND|ps -eo'"
#define PS_CNT4 "/usr/bin/ps -eo user,pid,ppid,args|egrep '%s|%s|%s'|egrep -v 'COMMAND|ps -eo'"
#elif defined(LINUX)
#define PS      "/bin/ps -w -eo user,pid,ppid,stat,args|egrep -v 'COMMAND|ps -w'"
#define PS_CNT  "/bin/ps -ef|grep '%s' |grep -v grep |wc -l"
#define PS_CNT2 "/bin/ps -w -eo user,pid,ppid,args|grep '%s'|egrep -v 'COMMAND|ps -w'"
#define PS_CNT3 "/bin/ps -w -eo user,pid,ppid,args|egrep '%s|%s'|egrep -v 'COMMAND|ps -w'"
#define PS_CNT4 "/bin/ps -w -eo user,pid,ppid,args|egrep '%s|%s|%s'|egrep -v 'COMMAND|ps -w'"
#elif defined(AIX)
#define PS      "/usr/bin/ps -eo user,pid,ppid,stat,args|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT  "/usr/bin/ps -ef|grep '%s' |grep -v grep |wc -l" 
#define PS_CNT2 "/usr/bin/ps -eo user,pid,ppid,args|grep '%s'|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT3 "/usr/bin/ps -eo user,pid,ppid,args|egrep '%s|%s'|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT4 "/usr/bin/ps -eo user,pid,ppid,args|egrep '%s|%s|%s'|egrep -v 'COMMAND|ps -eo'" 
#elif defined(DGUX) 
#define PS      "/usr/bin/ps -eo user,pid,ppid,s,args|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT  "/usr/bin/ps -ef|grep '%s' |grep -v grep |wc -l" 
#define PS_CNT2 "/usr/bin/ps -eo user,pid,ppid,args|grep '%s'|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT3 "/usr/bin/ps -eo user,pid,ppid,args|egrep '%s|%s'|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT4 "/usr/bin/ps -eo user,pid,ppid,args|egrep '%s|%s|%s'|egrep -v 'COMMAND|ps -eo'" 
#elif defined(NCRUX)
/*#define PS      "/sbin/ps -eo user,pid,ppid,s,args|egrep -v 'COMMAND|ps -eo'" */
#define PS      "/sbin/ps -eo user,pid,ppid,args|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT  "/sbin/ps -ef|grep '%s' |grep -v grep |wc -l" 
#define PS_CNT2 "/sbin/ps -eo user,pid,ppid,args|grep '%s'|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT3 "/sbin/ps -eo user,pid,ppid,args|egrep '%s|%s'|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT4 "/sbin/ps -eo user,pid,ppid,args|egrep '%s|%s|%s'|egrep -v 'COMMAND|ps -eo'" 
#else   /* SUN, UNIX */
#define PS      "ps -eo user,pid,ppid,s,args|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT  "ps -ef|grep '%s' |grep -v grep |wc -l" 
#define PS_CNT2 "ps -eo user,pid,ppid,args|grep '%s'|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT3 "ps -eo user,pid,ppid,args|egrep '%s|%s'|egrep -v 'COMMAND|ps -eo'" 
#define PS_CNT4 "ps -eo user,pid,ppid,args|egrep '%s|%s|%s'|egrep -v 'COMMAND|ps -eo'" 
#endif

extern int it_loging(char *format,...);
extern int rtrim(char* sbuf);

int get_process()
{
  	FILE 	*pfp;

  	int 	pid, ppid, proc_num = 0;
  	/*char 	stat[5], process[256], owner[64],  fline[15000];*/
  	char 	stat[15000], process[256], owner[15000],  fline[15000];

	struct run_process *rProcess_tmp;

#if defined(HPUX)
	putenv("UNIX95=XPG4");
#endif

  	if ((pfp = popen (PS, "r")) == NULL) {
      	it_loging("libIT.a(%s): get_process() pipe open error.\n", S2O_DAEMON);
      	return (-1);
    }

  	/* read lines off of the file until EOF */
  	while (fgets(fline, 14998, pfp) != NULL) {
		memset(process, 0x00, sizeof process);
		memset(owner, 0x00, sizeof owner);
		memset(stat, 0, sizeof stat);
#if defined(NCRUX)
		sscanf(fline, "%s %d %d %255c", owner, &pid, &ppid, process);
		strcpy(stat, "-");	
#else
		sscanf(fline, "%s %d %d %s %255c", owner, &pid, &ppid, stat, process);
#endif

		if (strlen(stat) > 4) continue;
		if (strlen(owner) > 63) continue;

  		/* reallocate array to hold the new entry */
		if (proc_num > 0) {
			rProcess_tmp = rProcess;
		}

		rProcess = (struct run_process *) realloc (rProcess, (proc_num + 1) * sizeof (struct run_process));

		if (rProcess == NULL) {
			it_loging("libIT.a(%s): get_process() struct realloc error.1,(count=%d)\n", S2O_DAEMON, proc_num);
			pclose(pfp);
			if (proc_num > 0) {
				rProcess=rProcess_tmp;
				rProcess = (struct run_process *) realloc (rProcess, sizeof (struct run_process));
				if (rProcess == NULL) {
					it_loging("libIT.a(%s): get_process() struct realloc error.2,(count=%d)\n", S2O_DAEMON, proc_num);
					rProcess=rProcess_tmp;
					free(rProcess);
				}
			}
  			return(-1);
		}
	    rProcess[proc_num].pid = pid;
	    rProcess[proc_num].ppid = ppid;
	    strcpy (rProcess[proc_num].stat, stat);
	    strcpy (rProcess[proc_num].owner, owner);
		rtrim(process);
	    strcpy (rProcess[proc_num].processName, process);
	    rProcess[proc_num].stat[strlen(stat)] = '\0';
	    rProcess[proc_num].processName[strlen(process)] = '\0';
	    rProcess[proc_num].owner[strlen(owner)] = '\0';

      	proc_num++;
    }
	pclose(pfp);
  	return (proc_num);
}

int get_process_cnt(char* _prsname)
{
  	FILE 	*pfp;

#if defined(HPUX9000)
  	char 	fline[4096];
#else
  	char 	fline[15000];
#endif
	int 	fline_len = sizeof(fline)-1;

	int 	num = 0;
	char	cmdbuf[256];

#if defined(HPUX)
	putenv("UNIX95=XPG4");
#endif

	memset(cmdbuf, 0, sizeof cmdbuf);
	sprintf(cmdbuf, PS_CNT, _prsname);

  	if ((pfp = popen (cmdbuf, "r")) == NULL) {
      	it_loging("libIT.a(%s): get_process_cnt() pipe open error.\n", S2O_DAEMON);
      	return (-1);
    }
  	if (fgets(fline, fline_len, pfp) != NULL) {
		num = atoi(fline);	
	}
	pclose(pfp);

	return num;
}

int get_process_cnt2(char* _prsname)
{
  	FILE 	*pfp;
#if defined(HPUX9000)
  	char 	fline[4096];
#else
  	char 	fline[15000];
#endif
	int 	fline_len = sizeof(fline)-1;

	int 	num = 0;
	char	cmdbuf[256];
	char	process[256];

#if defined(HPUX)
	putenv("UNIX95=XPG4");
#endif

	memset(cmdbuf, 0, sizeof cmdbuf);
	sprintf(cmdbuf, PS_CNT2, _prsname);

  	if ((pfp = popen (cmdbuf, "r")) == NULL) {
      	it_loging("libIT.a(%s): get_process_cnt2() pipe open error.\n", S2O_DAEMON);
      	return (-1);
    }

  	while (fgets(fline, fline_len, pfp) != NULL) {
		memset(process, 0, sizeof process);
		sscanf(fline, "%*s %*s %*s %100c", process);
		if (!strncmp(process, _prsname, strlen(_prsname))) num++;
	}
	pclose(pfp);
	return num;
}

int get_process_cnt3(char* _prsname, char* _prsname2)
{
  	FILE 	*pfp;
#if defined(HPUX9000)
  	char 	fline[4096];
#else
  	char 	fline[15000];
#endif
	int 	fline_len = sizeof(fline)-1;

	int 	num = 0;
	char	cmdbuf[256];
	char	process[256];

#if defined(HPUX)
	putenv("UNIX95=XPG4");
#endif

	memset(cmdbuf, 0, sizeof cmdbuf);
	sprintf(cmdbuf, PS_CNT3, _prsname, _prsname2);

  	if ((pfp = popen (cmdbuf, "r")) == NULL) {
      	it_loging("libIT.a(%s): get_process_cnt3() pipe open error.\n", S2O_DAEMON);
      	return (-1);
    }

  	while (fgets(fline, fline_len, pfp) != NULL) {
		memset(process, 0, sizeof process);
		sscanf(fline, "%*s %*s %*s %s", process);
		if (!strcmp(process, _prsname) || !strcmp(process, _prsname2)) num++;
	}
	pclose(pfp);
	return num;
}

int get_process_cnt4(char* _prsname, char* _prsname2, char* _prsname3)
{
  	FILE 	*pfp;
#if defined(HPUX9000)
  	char 	fline[4096];
#else
  	char 	fline[15000];
#endif
	int 	fline_len = sizeof(fline)-1;

	int 	num = 0;
	char	cmdbuf[256];
	char	process[256];

#if defined(HPUX)
	putenv("UNIX95=XPG4");
#endif

	memset(cmdbuf, 0, sizeof cmdbuf);
	sprintf(cmdbuf, PS_CNT4, _prsname, _prsname2, _prsname3);

  	if ((pfp = popen (cmdbuf, "r")) == NULL) {
      	it_loging("libIT.a(%s): get_process_cnt4() pipe open error.\n", S2O_DAEMON);
      	return (-1);
    }

  	while (fgets(fline, fline_len, pfp) != NULL) {
		memset(process, 0, sizeof process);
		sscanf(fline, "%*s %*s %*s %s", process);
		if (!strcmp(process, _prsname) || !strcmp(process, _prsname2) || !strcmp(process, _prsname3)) num++;
	}
	pclose(pfp);
	return num;
}


