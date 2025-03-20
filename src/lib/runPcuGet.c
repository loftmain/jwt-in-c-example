/*
   $Id: runPcuGet.c,v 1.7 2003/06/30 srp Exp $

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
#define PCU "/usr/bin/ps -eo pid,ppid,user,vsz,sz,tty,state,stime,pcpu,time,args|egrep -v 'ps -eo|COMMAND|defunct'"
#elif defined(LINUX)
#define PCU "/bin/ps -w -eo pid,ppid,user,vsz,rss,tty,stat,stime,pcpu,time,args|egrep -v 'COMMAND|ps -w'"
#elif defined(AIX)
#define PCU "/usr/bin/ps -eo pid,ppid,user,vsz,vsz,tty,state,etime,pcpu,time,args|egrep -v 'COMMAND|ps -eo|defunct|idle'"
#elif defined(NCRUX)
/*#define PCU  "/sbin/ps -eo pid,ppid,user,vsz,nice,tty,state,stime,pcpu,time,args|egrep -v 'idleproc|ps -eo|COMMAND'"*/
/*UNIX_SV mympras 4.2 3.3 POWEREDGE_8E Pentium III(TM)-ISA/PCI*/
#define PCU  "/sbin/ps -eo pid,ppid,user,vsz,nice,tty,etime,pcpu,time,args|egrep -v 'idleproc|ps -eo|COMMAND'"
#else   /* SUN, UNIX */
#define PCU	 "ps -eo pid,ppid,user,vsz,rss,tty,s,stime,pcpu,time,args|egrep -v 'COMMAND|ps -eo'"
#endif

extern int it_loging(char *format,...);
extern int rtrim(char* sbuf);
extern int getitem(int ch, char *src, char *dest, int seqitem);
extern int getitemc(int ch, char *src);

int runPcuGet(char* arg)
{
  	FILE 	*pfp;

  	int 	proc_num = 0;
	char	buf[256], tmpbuf[256], fline[15000];
  	char 	run_pname[4096], run_owner[24], run_cputime[16], run_tty[24], run_stime[24], run_stime_tmp[5];
	char	run_state[16];
	int     time_day = 0, time_hour = 0, time_min = 0;
	int		run_pcutime = 0, run_memory = 0, run_sz, run_pid, run_ppid;
	float   run_pcuusage = 0;
	struct run_pcu *runPcu_tmp;

#if defined(HPUX)
    putenv("UNIX95=XPG4");
#endif

  	if ((pfp = popen(PCU, "r")) == NULL) {
      	it_loging("libIT.a(%s): runPcuGet() pipe open error.\n", S2O_DAEMON);
      	return (-1);
    }

  	/* read lines off of the file until EOF */
  	while (fgets(fline, 14998, pfp) != NULL) {

		if(proc_num > 0) {
			runPcu_tmp = runPcu;
		}

  		/* reallocate array to hold the new entry */
		runPcu = (struct run_pcu *) realloc (runPcu, (proc_num + 1) * sizeof (struct run_pcu));
		if (runPcu == NULL) {
			it_loging("libIT.a(%s): runPcuGet() struct realloc error.1,(count=%d)\n", S2O_DAEMON, proc_num);
			pclose(pfp); /*추가*/
			if (proc_num > 0) {
				runPcu = runPcu_tmp;
				runPcu = (struct run_pcu *) realloc (runPcu, sizeof (struct run_pcu));
				if (runPcu == NULL) {
					it_loging("libIT.a(%s): runPcuGet() struct realloc error.2,(count=%d)\n", S2O_DAEMON, proc_num);
					runPcu = runPcu_tmp;
					free(runPcu);
				}
			}
  			return(-1);
		}

		memset(run_pname, 0x00, sizeof run_pname);
#if defined(NCRUX)
		sscanf(fline, "%*d %*d %*s %*d %*d %*s %s %*f %*s %s", run_stime, run_pname);
		strcpy(run_state, "-");
#else
		sscanf(fline, "%*d %*d %*s %*d %*d %*s %*s %s %*f %*s %s", run_stime, run_pname);
#endif
		if (strlen(run_pname) == 0)					/* format이 맞지 않을 경우 skip */
			continue;

		memset(run_pname, 0x00, sizeof run_pname);
#if defined(HPUX)
		if(strlen(run_stime)==3) {
			sscanf(fline, "%d %d %s %d %d %s %s %s %s %f %s %255c", &run_pid, &run_ppid, run_owner, &run_memory, &run_sz, run_tty, run_state, run_stime, run_stime_tmp, &run_pcuusage, run_cputime, run_pname);
			strcat(run_stime, run_stime_tmp);
		} else {
			sscanf(fline, "%d %d %s %d %d %s %s %s %f %s %255c", &run_pid, &run_ppid, run_owner, &run_memory, &run_sz, run_tty, run_state, run_stime, &run_pcuusage, run_cputime, run_pname);
		}
#else
		sscanf(fline, "%d %d %s %d %d %s %s %s %f %s %255c", &run_pid, &run_ppid, run_owner, &run_memory, &run_sz, run_tty, run_state, run_stime, &run_pcuusage, run_cputime, run_pname);
#endif

		if (getitemc('-', run_cputime) == 0) { 	/* '-' 표시가 없을 경우 */
			time_day = 0;
			if (getitemc(':', run_cputime) > 1) {
				memset(buf, 0x00, sizeof buf);
				if (getitem(':', run_cputime, buf, 1) ==  0) 
					time_hour = atoi(buf);
				memset(buf, 0x00, sizeof buf);
				if (getitem(':', run_cputime, buf, 2) ==  0) 
					time_min = atoi(buf);
			} else {
				time_hour = 0;
				memset(buf, 0x00, sizeof buf);
				if (getitem(':', run_cputime, buf, 1) ==  0) 
					time_min = atoi(buf);
			}
		} else {					/* Time 표시가 dd-hh:mm:ss 일 경우 */
			memset(buf, 0x00, sizeof buf);
			if (getitem('-', run_cputime, buf, 1) < 0) 
				time_day = 0;
			else
				time_day = atoi(buf);
			memset(tmpbuf, 0x00, sizeof tmpbuf);
			if (getitem(':', run_cputime, tmpbuf, 1) == 0) {
				memset(buf, 0x00, sizeof buf);
				if (getitem('-', tmpbuf, buf, 2) < 0)
					time_hour = 0;
				else
					time_hour = atoi(buf);
			} else
				time_hour = 0;
			memset(buf, 0x00, sizeof buf);
			if (getitem(':', run_cputime, buf, 2) == 0) 
				time_min = atoi(buf);
			else 
				time_min = 0;
		}
		run_pcutime = (time_day * 1440) + (time_hour * 60) + time_min;

		rtrim(run_pname);

	    strcpy (runPcu[proc_num].processName, run_pname);
	    strcpy (runPcu[proc_num].owner, run_owner);
		runPcu[proc_num].pid = run_pid;
		runPcu[proc_num].ppid = run_ppid;
		runPcu[proc_num].memory = run_memory;
		runPcu[proc_num].sz = run_sz;
	    strcpy (runPcu[proc_num].tty, run_tty);
	    strcpy (runPcu[proc_num].state, run_state);
	    strcpy (runPcu[proc_num].stime, run_stime);
		runPcu[proc_num].cpuusage = run_pcuusage;
		runPcu[proc_num].cputime = run_pcutime;

		runPcu[proc_num].processName[strlen(run_pname)] = '\0';
		runPcu[proc_num].owner[strlen(run_owner)] = '\0';
/*
		if (proc_num < 10) {
			it_loging("libIT.a(%s): runPcuGet() -> %d %s %d %3.1f %d %s\n", S2O_DAEMON, runPcu[proc_num].pid, runPcu[proc_num].owner, runPcu[proc_num].memory, runPcu[proc_num].cpuusage, runPcu[proc_num].cputime, runPcu[proc_num].processName);
		}
*/
      	proc_num++;
    }
	pclose(pfp);
  	return (proc_num);
}
