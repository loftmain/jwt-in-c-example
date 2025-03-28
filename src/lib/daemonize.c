/*
   $Id: daemonize.c,v 1.7 2002/09/02 srp Exp $

   Copyright (c) 2000, 2001, 2002
             i-TOP System Inc.  All rights reserved.

   2002-09-16
     * daemon 생성 module.
	 * Unix Daemon Server Program
*/
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../IT.extern.h"

#if defined(HPUX)
#define PS_temp      "/usr/bin/ps -eo ppid,args|grep -v grep|grep "
#elif defined(LINUX)
#define PS_temp      "/bin/ps -w -eo ppid,args|grep -v grep|grep "
#elif defined(AIX)
#define PS_temp      "/usr/bin/ps -eo ppid,args|grep -v grep|grep "
#elif defined(DGUX)
#define PS_temp      "/usr/bin/ps -eo ppid,args|grep -v grep|grep "
#elif defined(NCRUX)
#define PS_temp      "/sbin/ps -eo ppid,args|grep -v grep|grep "
#else   /* SUN, UNIX */
#define PS_temp      "ps -eo ppid,args|grep -v grep|grep "
#endif

extern int get_cfg(char* ENV, char* value);
extern int it_loging(char *format,...);
extern int rtrim(char* sbuf);

void daemonize_func(char *fname, int count, int seq_num, char* _DAEMON_VER);

void daemonize(char *fname, int count, char* _DAEMON_VER)
{
	int seq_num = -1;
	daemonize_func(fname, count, seq_num, _DAEMON_VER);
}

void daemonize2(char *fname, int count, int seq_num, char* _DAEMON_VER)
{
	daemonize_func(fname, count, seq_num, _DAEMON_VER);
}

void daemonize_func(char *fname, int count, int seq_num, char* _DAEMON_VER)
{
	int 	i, lfp;
	char 	str[10], cmdbuf[300], pid_file[300];
	FILE 	*pfp;
	int		ppid, proc_num = 0;
	char	process[256], ps_string[350], fline[256];
	char	daemon_name[300];
	char	daemon_ver[32];
	char	it_home[256];
	char	pid_dir[256];
	int ret;
	struct stat stbuf1;
	
   	memset(it_home, 0, sizeof it_home);
   	if (get_cfg("IT_HOME", it_home) < 0) {
      	it_loging("libIT.a(%s): daemonize_func() parameter(IT_HOME) read error!\n", fname);
		exit(1);
	}

	/* 이미 기동 중인지 체크*/
#if defined(HPUX)
    putenv("UNIX95=XPG4");
#endif

	memset(daemon_ver, 0, sizeof daemon_ver);
	sscanf(_DAEMON_VER, "%s", daemon_ver);

	/* 변경 주의 - IT.orac 일반 user로 실행시 */
	if (strlen(daemon_ver) > 0) write_ver(it_home, _DAEMON_VER, fname);

	if (count > 0) {
		memset(ps_string, 0, sizeof ps_string);
		memset(daemon_name, 0, sizeof daemon_name);

		if ( seq_num > 0) {
			sprintf(daemon_name, "%s/%s -n %d",it_home, fname, seq_num);
		} else {
			sprintf(daemon_name, "%s/%s",it_home, fname);
		}

		/*
		strcpy(ps_string, PS_temp);
		strcat(ps_string, daemon_name);
		*/

		sprintf(ps_string, "%s '%s'", PS_temp, daemon_name);
		
		if((pfp = popen(ps_string, "r")) == NULL){
			 it_loging("libIT.a(%s): daemonize_func() daemon get() pipe open error.\n", fname);
			 exit(1);
		}

		while(fgets(fline, 255, pfp) != NULL){
			memset(process, 0x00, sizeof process);
			sscanf(fline, "%d %255c", &ppid, process);
			rtrim(process);
			if(process[strlen(process)-1] == '\n') process[strlen(process)-1] = '\0';
			if((ppid == 1) && (!strcmp(daemon_name, process))){
				proc_num++;
			}
		}
		pclose(pfp);
	
		if(proc_num >= count){
			it_loging("libIT.a(%s): daemonize_func() execute error(daemonize) -- daemon already exists!\n", fname);
			printf("%s: execute error(daemonize) -- daemon already exists!!\n", fname);
			exit(1);
		}
	}

	/*end */

	if (getppid() == 1) { 					/* already a daemon */
		it_loging("libIT.a(%s): daemonize_func() getppid() == 1, already a daemon\n", fname);
		exit(1);
	}

	i = fork();
	if (i < 0) {
		it_loging("libIT.a(%s): daemonize_func() fork error\n", fname);
		exit(1); 					/* fork error */
	}
	if (i > 0) {
		/*it_loging("libIT.a(%s): daemonize_func() fork (parent exits)\n", fname);*/
		exit(0); 					/* parent exits */
	}

	/* child (daemon) continues */
	setsid(); 								/* obtain a new process group */
	for (i = getdtablesize(); i >= 0; --i) close(i); /* close all descriptors */
	i = open("/dev/null", O_RDWR); ret=dup(i); ret=dup(i); 	 /* handle standart I/O */
	umask(027); 					/* set newly created file permissions */
	/*chdir("/"); */					/* change running directory */

	ret=chdir(it_home); 					/* change running directory */


	memset(pid_dir, 0, sizeof pid_dir);
	if (!strcmp(fname, "IT.orac")) {
		sprintf(pid_dir, _ORAC_DUMP_DIR_ /* %s/dump.orac */, it_home);
		strcat(pid_dir, "/pid");
		if (stat(pid_dir, &stbuf1) != 0) {
			sprintf(pid_dir, "%s/pid", it_home);
		}
	} else {
		sprintf(pid_dir, "%s/pid", it_home);
	}

   	memset(cmdbuf, 0, sizeof cmdbuf);
	sprintf(cmdbuf, "/bin/mkdir -p %s", pid_dir);
	/*sprintf(cmdbuf, "/bin/mkdir -p %s/pid", it_home);*/
	ret=system(cmdbuf);

   	memset(pid_file, 0, sizeof pid_file);

	if ( seq_num > 0) 
		sprintf(pid_file, "%s/%s_%d.pid", pid_dir, fname, seq_num);
	else
		sprintf(pid_file, "%s/%s.pid", pid_dir, fname);

	lfp = open(pid_file, O_RDWR|O_CREAT, 0640);

	if (lfp < 0) {
		it_loging("libIT.a(%s): daemonize_func() pid_file(%s) open error \n", fname, pid_file);
		exit(1); 						/* can not open */
	}
	if (lockf(lfp, F_TLOCK, 0) < 0) {
		it_loging("libIT.a(%s): daemonize_func() pid_file(%s) lock \n", fname, pid_file);
		exit(0); 	/* can not lock */
	}

	/* first instance continues */
	memset(str, 0x00, sizeof str);
	sprintf(str, "%d", getpid());
	write(lfp, str, sizeof(str)); 	/* record pid to lockfile */
	close(lfp);

	if ( seq_num >= 0)  chmod(pid_file, 0666);

	sleep(3);

	memset(S2O_PIDFILE, 0, sizeof S2O_PIDFILE);

	if ( count == 1) {
		sprintf(S2O_PIDFILE, "%s", pid_file);	

		if (compare_s2opid(fname) < 0) {
			exit(1);
		}
	}
}

/* EOF */

