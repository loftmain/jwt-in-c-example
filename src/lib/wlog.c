/*
 * Copyright (c) 2000, 2001, ITOP SYSTEM Inc. All rights reserved.
 *
 * NAME
 *      wlog.c - message를 IT.dev로 send
 *
 * MODIFIED     (MM/DD/YYYY)
 *  MyungKyun   01/14/2002 - MSG Queue size 50%이상이면 MSG를 버림.
 *  MyungKyun   01/12/2002 - 통합정리.
 *
 */
#ifndef WLOG_H
#define WLOG_H
#include "config.h"
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif

#include "../IT.extern.h"

#ifdef __cplusplus
extern "C" {
#endif

/* #define DEBUG */

#define IPCS_Q  "ipcs -qa"

int wlog(char *mid, char *msg,...);
int wlog2(char *mid, char *company, char *host, char *msg,...);

extern void date1(char* tim);
extern int get_cfg(char* ENV, char* value);
extern int is_valid_msg(char *v_msg);
extern int loging(char *msg,...);
extern int it_loging(char *format,...);

#ifdef __cplusplus
}
#endif

int 	parse_mid(char *mid);

int wlog_fail(char *msg);

int wlog(char *mid, char *msg,...)
{
	char 	company_code[100];
	struct 	msqid_ds ds;
  	MSGQ  	sbuf;
  	va_list argptr;	

  	int 	msqid, i, flag = 0, ratio;
  	char 	tmsg[4096], *bmsg, mmsg[4096];
  	char 	host[64], time1[50];
  	char 	*s;
	char	tmp_s2o[64];

	if (IS_NOS2O_AGENT == 1) return 0;

  	memset(tmsg, 0x00, sizeof tmsg);
  	va_start(argptr, msg);
  	vsprintf(tmsg, msg, argptr);
  	va_end(argptr);

  	/* \n delete */
  	memset(mmsg, 0x00, sizeof mmsg);
  	bmsg = mmsg;
  	for (i = 0; i < strlen(tmsg); i++) {
     	if (tmsg[i] != '\n') {
        	*bmsg = tmsg[i];
        	bmsg++;
       	}
    }

  	memset(host, 0x00, sizeof host);
  	if (gethostname(host, sizeof(host)) != 0) {
		usleep(1000000);
  		if (gethostname(host, sizeof(host)) != 0) {
     		/*loging("wlog(): gethostname error!\n");*/
     		it_loging("libIT.a(%s): wlog() gethostname error!\n", S2O_DAEMON);
			return (-1);
		}
	}
		
  	memset(time1, 0x00, sizeof time1);
  	date1(time1);


  	/* IT.cfg에서 ITCONS company얻기. */
  	memset(company_code, 0x00, sizeof company_code);
  	if (get_cfg("IT_COMPANY_CODE",company_code) < 0) {
     	/*loging("libIT.a: wlog() get parameter(IT_COMPANY_CODE) error!\n");*/
     	it_loging("libIT.a(%s): wlog() get parameter(IT_COMPANY_CODE) error!\n", S2O_DAEMON);
		usleep(1000000);
  		memset(company_code, 0x00, sizeof company_code);
  		if (get_cfg("IT_COMPANY_CODE",company_code) < 0) {
     		/*loging("libIT.a: wlog() get parameter(IT_COMPANY_CODE) error!\n");*/
     		it_loging("libIT.a(%s): wlog() get parameter(IT_COMPANY_CODE) error!\n", S2O_DAEMON);
     		strcpy(company_code, "ERROR");
		}
    }

	if (IS_WLOG_LOGING == 1)
	{
		memset(tmp_s2o, 0, sizeof tmp_s2o);
		sscanf(S2O_DAEMON, "%s", tmp_s2o);
		if (strlen(tmp_s2o) == 0) strcpy(tmp_s2o, "wlog_loging");

  		it_loging("libIT.a(%s): wlog() DEBUG_wlog(%s %s %s %s %s)\n", S2O_DAEMON, tmp_s2o, mid, company_code, time1, host, mmsg);
		return(0);
	}

  	/* msg id가 invalid format일 경우 */
  	if (is_valid_msg(mid) < 0) {
		return(-1);
	}

	if(strlen(mmsg) > 2000)	{
        it_loging("libIT.a(%s): wlog() over size - original=%s\n", S2O_DAEMON, mmsg);
		mmsg[2000] = '\0';
	}

  	sprintf(sbuf.mtext, 
			"%s %s %s %s %s\n", mid, company_code, time1, host, mmsg);

  	sbuf.mtype = 1;

  	if ((msqid = msgget(key, 0666)) <0) {
		wlog_fail(sbuf.mtext);
		return(-2);
	}

	/*
	// MSG QUEUE가 50%이상 사용중일 경우 MSG 버림.
	*/

   	if (msgctl(msqid, IPC_STAT, &ds) < 0) {
		/*loging("wlog(): msgctl(), IPC_STAT error!\n");*/
		it_loging("libIT.a(%s): wlog() msgctl(), IPC_STAT error!\n", S2O_DAEMON);
		wlog_fail(sbuf.mtext);
      	return(-1);
	}

#ifdef DEBUG
	it_loging("libIT.a(%s): wlog() msg_cbytes -> %d, msg_qbytes -> %d\n", S2O_DAEMON, ds.msg_cbytes, ds.msg_qbytes);

  	if ((pfp = popen(IPCS_Q, "r")) == NULL) {
   		it_loging("libIT.a(%s): wlog() ipcs command open error.\n", S2O_DAEMON);
		wlog_fail(sbuf.mtext);
      	return(-1);
   	}

	while (fgets(rcvbuf, 2047, pfp) != NULL) {
		it_loging("libIT.a(%s): wlog() %s\n", S2O_DAEMON, rcvbuf);
	}
	pclose(pfp);
#endif

	ratio = ((float)ds.msg_cbytes / (float)ds.msg_qbytes) * 100;

	if (ratio < 90 && ds.msg_qnum < 1000) {
  		if(msgsnd(msqid, &sbuf, strlen(sbuf.mtext) + 1, IPC_NOWAIT) < 0)  {
			wlog_fail(sbuf.mtext);
     		return(-1);
		}
	} else {
		wlog_fail(sbuf.mtext);
	}

  	return(0); /* if msgsnd() is success */
}

int wlog2(char *mid, char *company, char *host, char *msg,...)
{
	struct msqid_ds ds;
  	MSGQ  sbuf;
  	va_list argptr;	
  	int msqid, i, flag=0, ratio;
  	char tmsg[4096], /* tmid[50], */ *bmsg, mmsg[4096];
  	char time1[50];
  	char *s;
	char 	company_code[100];
	char 	tmp_s2o[64];

	if (IS_NOS2O_AGENT == 1) return 0;

  	memset(tmsg, 0, sizeof tmsg);
  	va_start(argptr, msg);
  	vsprintf(tmsg, msg, argptr);
  	va_end(argptr);

  	/* '\n' delete */
  	memset(mmsg, 0, sizeof mmsg);
  	bmsg = mmsg;
  	for(i = 0; i < strlen(tmsg); i++) {
     	if (tmsg[i] != '\n') {
        	*bmsg = tmsg[i];
        	bmsg++;
       	}
    }

  	memset(time1, 0, sizeof time1);
  	date1(time1);

	if (IS_WLOG_LOGING == 1) {
		memset(tmp_s2o, 0, sizeof tmp_s2o);
		sscanf(S2O_DAEMON, "%s", tmp_s2o);
		if (strlen(tmp_s2o) == 0) strcpy(tmp_s2o, "wlog_loging");
  		it_loging("libIT.a(%s): wlog2() DEBUG_wlog(%s %s %s %s %s)\n", S2O_DAEMON, tmp_s2o, mid, company, time1, host, mmsg);
		return(0);
	}

  	/* msg id가 invalid format일 경우 */
  	if (is_valid_msg(mid) < 0) return(-1);



  	/* mid 변경시 wlog()를 두번 call할 경우 bug 발생 */
	/*
  	memset(tmid, 0, sizeof tmid);
  	strcpy(tmid, mid); 
	*/

  	/* msg id가 invalid format일 경우 */
	/*
  	if (parse_mid(tmid) < 0)
     	return(-1);
	*/


	/*
  	if ((*tmid == 'I') || (*tmid == 'W') || (*tmid == 'S') || (*tmid == 'C') || (*tmid == 'P') || (*tmid == 'O') ||(*tmid =='Z') || (*tmid =='E')||(*tmid == 'F'))
	*/


	if (strlen(mmsg) > 2000) {
        it_loging("libIT.a(%s): wlog2() over size - original=%s\n", S2O_DAEMON, mmsg);
		mmsg[2000] = '\0';
	}

   	sprintf(sbuf.mtext,"%s %s %s %s %s\n", mid, company, time1, host, mmsg);


  	sbuf.mtype = 1;

  	if ((msqid = msgget(key, 0666)) <0) {
		wlog_fail(sbuf.mtext);
      	return(-2);
	}


	/*
	// MSG QUEUE가 50%이상 사용중일 경우 MSG 버림.
	*/
   	if (msgctl(msqid, IPC_STAT, &ds) < 0) {
		wlog_fail(sbuf.mtext);
      	return(-1);
	}


	ratio = ((float)ds.msg_cbytes / (float)ds.msg_qbytes) * 100;

	if (ratio < 90 && ds.msg_qnum < 1000) {
  		if(msgsnd(msqid, &sbuf, strlen(sbuf.mtext) + 1, IPC_NOWAIT) < 0)  {
			/* it_loging("libIT.a(%s): wlog2() msgsend error - %s\n", S2O_DAEMON, sbuf.mtext);*/
			wlog_fail(sbuf.mtext);
     		return(-1);
		}
	} else {
		wlog_fail(sbuf.mtext);
	}	
  	return(0); /* if msgsnd() is success */
}

int wlog_no_vsprintf(char *mid, char *msg)
{
	struct 	msqid_ds ds;
  	MSGQ  	sbuf;
	char 	company_code[100];

  	int 	msqid, i, flag = 0, ratio;
  	char 	host[64], time1[50];

	if (IS_NOS2O_AGENT == 1) return 0;

  	memset(host, 0x00, sizeof host);
  	if (gethostname(host, sizeof(host)) != 0) {
     	it_loging("libIT.a(%s): wlog_no_vsprintf() gethostname error!\n", S2O_DAEMON);
		return (-1);
	}
		
  	memset(time1, 0x00, sizeof time1);
  	date1(time1);

  	/* IT.cfg에서 ITCONS company얻기. */
  	memset(company_code, 0x00, sizeof company_code);
  	if (get_cfg("IT_COMPANY_CODE",company_code) < 0) {
     	it_loging("libIT.a(%s): wlog_no_vsprintf() get parameter(IT_COMPANY_CODE) error!\n", S2O_DAEMON);
		
		usleep(1000000);

  		memset(company_code, 0x00, sizeof company_code);
  		if (get_cfg("IT_COMPANY_CODE",company_code) < 0) {
     		it_loging("libIT.a(%s): wlog_no_vsprintf() get parameter(IT_COMPANY_CODE) error!\n", S2O_DAEMON);
     		strcpy(company_code, "ERROR");
		}
    }


  	/* msg id가 invalid format일 경우 */
  	if (is_valid_msg(mid) < 0) return(-1);

	if (strlen(msg) > 2000) {
        it_loging("libIT.a(%s): wlog_no_vsprintf() over size - original=%s\n", S2O_DAEMON, msg);
		msg[2000] = '\0';
	}

  	sprintf(sbuf.mtext, 
			"%s %s %s %s %s\n", mid, company_code, time1, host, msg);

  	sbuf.mtype = 1;

  	if ((msqid = msgget(key, 0666)) <0) {
		wlog_fail(sbuf.mtext);
		return(-2);
	}

	/*
	// MSG QUEUE가 50%이상 사용중일 경우 MSG 버림.
	*/
   	if (msgctl(msqid, IPC_STAT, &ds) < 0) {
		/* 2015-06-12*/
		/* loging("wlog(): msgctl(), IPC_STAT error!\n");*/
		it_loging("libIT.a(%s): wlog_no_vsprintf() msgctl(), IPC_STAT error!\n", S2O_DAEMON);
		wlog_fail(sbuf.mtext);
      	return(-1);
	}

	ratio = ((float)ds.msg_cbytes / (float)ds.msg_qbytes) * 100;

	if (ratio < 95 && ds.msg_qnum < 1000) {
  		if(msgsnd(msqid, &sbuf, strlen(sbuf.mtext) + 1, IPC_NOWAIT) < 0) {
			wlog_fail(sbuf.mtext);
     		return(-1);
		}
	} else {
		wlog_fail(sbuf.mtext);
	}

  	return(0); /* if msgsnd() is success */
}

int wlog2_no_vsprintf(char *mid, char *company, char *host, char *msg)
{
	struct msqid_ds ds;
  	MSGQ  sbuf;
  	va_list argptr;	
  	int msqid, i, flag=0, ratio;
  	char tmsg[4096], /* tmid[50], */ *bmsg, mmsg[4096];
  	char time1[50];
  	char *s;
	char 	company_code[100];
	char 	tmp_s2o[64];

	if (IS_NOS2O_AGENT == 1) return 0;

  	memset(tmsg, 0, sizeof tmsg);
	strcpy(tmsg, msg);

  	/* '\n' delete */
  	memset(mmsg, 0, sizeof mmsg);
  	bmsg = mmsg;
  	for(i = 0; i < strlen(tmsg); i++) {
     	if (tmsg[i] != '\n') {
        	*bmsg = tmsg[i];
        	bmsg++;
       	}
    }

  	memset(time1, 0, sizeof time1);
  	date1(time1);

	if (IS_WLOG_LOGING == 1) {
		memset(tmp_s2o, 0, sizeof tmp_s2o);
		sscanf(S2O_DAEMON, "%s", tmp_s2o);
		if (strlen(tmp_s2o) == 0) strcpy(tmp_s2o, "wlog_loging");
  		it_loging("libIT.a(%s): wlog2_no_vsprintf() DEBUG_wlog(%s %s %s %s %s)\n", tmp_s2o, mid, company, time1, host, mmsg);
		return(0);
	}

  	/* msg id가 invalid format일 경우 */
  	if (is_valid_msg(mid) < 0) return(-1);



  	/* mid 변경시 wlog()를 두번 call할 경우 bug 발생 */
	/*
  	memset(tmid, 0, sizeof tmid);
  	strcpy(tmid, mid); 
	*/

  	/* msg id가 invalid format일 경우 */
	/*
  	if (parse_mid(tmid) < 0)
     	return(-1);
	*/


	/*
  	if ((*tmid == 'I') || (*tmid == 'W') || (*tmid == 'S') || (*tmid == 'C') || (*tmid == 'P') || (*tmid == 'O') ||(*tmid =='Z') || (*tmid =='E')||(*tmid == 'F'))
	*/


	if (strlen(mmsg) > 2000) {
        it_loging("libIT.a(%s): wlog2_no_vsprintf() over size - original=%s\n", S2O_DAEMON, mmsg);
		mmsg[2000] = '\0';
	}

   	sprintf(sbuf.mtext,"%s %s %s %s %s\n", mid, company, time1, host, mmsg);


  	sbuf.mtype = 1;

  	if ((msqid = msgget(key, 0666)) <0) {
		wlog_fail(sbuf.mtext);
      	return(-2);
	}


	/*
	// MSG QUEUE가 50%이상 사용중일 경우 MSG 버림.
	*/
   	if (msgctl(msqid, IPC_STAT, &ds) < 0) {
		wlog_fail(sbuf.mtext);
      	return(-1);
	}


	ratio = ((float)ds.msg_cbytes / (float)ds.msg_qbytes) * 100;

	if (ratio < 90 && ds.msg_qnum < 1000) {
  		if(msgsnd(msqid, &sbuf, strlen(sbuf.mtext) + 1, IPC_NOWAIT) < 0)  {
			wlog_fail(sbuf.mtext);
     		return(-1);
		}
	} else {
		wlog_fail(sbuf.mtext);
	}	
  	return(0); /* if msgsnd() is success */
}

int wlog_direct(char *mid, char *tmsg) /* 시간 변경 없이 전송 */
{
	struct 	msqid_ds ds;
  	MSGQ  	sbuf;
  	int 	msqid, i, flag = 0, ratio;
	char	*sptr; 

	if (IS_NOS2O_AGENT == 1) return 0;

  	/* msg id가 invalid format일 경우 */
  	if (is_valid_msg(mid) < 0) return(-1);

	if (strlen(tmsg) > 2046) {
        it_loging("libIT.a(%s): wlog_direct() over size - original=%s\n", S2O_DAEMON, tmsg);
		tmsg[2046] = '\0';
	}

  	sprintf(sbuf.mtext, "%s", tmsg);

	sptr = (char*) strchr(sbuf.mtext, '\n');
	if ( sptr == NULL) strcat(sbuf.mtext, "\n");

  	sbuf.mtype = 1;

  	if ((msqid = msgget(key, 0666)) <0) {
		wlog_fail(sbuf.mtext);
		return(-2);
	}

	/*
	// MSG QUEUE가 50%이상 사용중일 경우 MSG 버림.
	*/
   	if (msgctl(msqid, IPC_STAT, &ds) < 0) {
		/* 2015-06-12*/
		it_loging("libIT.a(%s): wlog(): msgctl(), IPC_STAT error!\n", S2O_DAEMON);
		wlog_fail(sbuf.mtext);
      	return(-1);
	}

	ratio = ((float)ds.msg_cbytes / (float)ds.msg_qbytes) * 100;

	if (ratio < 95 && ds.msg_qnum < 1000) {
  		if(msgsnd(msqid, &sbuf, strlen(sbuf.mtext) + 1, IPC_NOWAIT) < 0) {
			wlog_fail(sbuf.mtext);
     		return(-1);
		}
	} else {
		wlog_fail(sbuf.mtext);
	}

  	return(0); /* if msgsnd() is success */
}

int parse_mid(char *mid)
{
  	if(strlen(mid) != 7)
     	return(-1);

  	if((mid[0] != 'I') && (mid[0] != 'W') && (mid[0] != 'S') && (mid[0] != 'C') && (mid[0] != 'P') && (mid[0] != 'O') && (mid[0] != 'Z') &&(mid[0] !='E') && (mid[0] != 'F'))
      	return(-1);

  	if(!isdigit(mid[4]))
     	return(-1);
  	if(!isdigit(mid[5]))
     	return(-1);
  	if(!isdigit(mid[6]))
     	return(-1);
  	return(0);
}

/* wlog 실패시(queue관련 문제)인 경우 local.dat에 쌓을 수 있도록 처리 */
int wlog_fail(char *msg)
{
	char homedir[256];	
	char local_file[300];
	char tmsg[4096];

	memset(homedir, 0, sizeof homedir);
	if (get_cfg("IT_HOME", homedir) < 0) {
		usleep(100000);
		if (get_cfg("IT_HOME", homedir) < 0) {
			return 0;
		}
	}
	memset(local_file, 0, sizeof local_file);
	sprintf(local_file, "%s/local.dat", homedir);
	memset(tmsg, 0, sizeof tmsg);
	strcpy(tmsg, msg);
	if (tmsg[strlen(tmsg)-1] != '\n') tmsg[strlen(tmsg)-1] = '\n';

	local_write(local_file, tmsg);
}
#endif

void dump_user_wlog(int _argc,  char *_argv[] )
{
	FILE *pfp;
	char cmdbuf[256];
	char tbuf[1024], sbuf[1024];
	char pwdstr[1024];
	char parentcmdstr[1024];
	char argstr[3072];
	char wlog_pid[64], wlog_ppid[64];
	char reqcmd_pid[64], reqcmd_ppid[64];
	char *sptr;
	int i;
	
	memset(argstr, 0, sizeof argstr);
	for(i = 0; i < _argc; i++) {
		if ( i != 0 ) strcat(argstr, " ");
		strcat(argstr, _argv[i]);
	}

	memset(pwdstr, 0, sizeof pwdstr);
	memset(parentcmdstr, 0, sizeof parentcmdstr);
	memset(wlog_pid, 0, sizeof wlog_pid);
	memset(wlog_ppid, 0, sizeof wlog_ppid);

	sprintf(wlog_pid, "%d", getpid());
	sprintf(wlog_ppid, "%d", getppid());
	
	memset(cmdbuf, 0, sizeof cmdbuf);
	strcpy(cmdbuf, "pwd");
	if ((pfp=popen(cmdbuf, "r")) == NULL) {
		it_loging_f("s2o", "%s: command(%s) open error!\n", S2O_DAEMON, cmdbuf);
	} else {
		memset(tbuf, 0, sizeof tbuf);
		while(fgets(tbuf, 1023, pfp) != NULL) {
			sptr = (char*) strchr(tbuf, '\n');
			if (sptr != NULL) *sptr = '\0';
			memset(sbuf, 0, sizeof sbuf);
			sscanf(tbuf, "%s", sbuf);
			if (strlen(sbuf) > 0) {
				sprintf(pwdstr, "%s", tbuf);
			}
		}
		pclose(pfp);
	}

	if ( strcmp(wlog_ppid, "1")) /* ppid가 1인 경우는 대상 아님 */
	{
		memset(cmdbuf, 0, sizeof cmdbuf);
		sprintf(cmdbuf, "/bin/ps -ef|grep \"%s\"|grep -v grep", wlog_ppid);
		if ((pfp = popen(cmdbuf, "r")) == NULL) {
			it_loging_f("s2o", "%s: command(%s) open error!\n", S2O_DAEMON, cmdbuf);
		} else {
			while (fgets(tbuf, 1023, pfp) != NULL) {
				sptr = (char*)strchr(tbuf, '\n');
				if (sptr != NULL) *sptr = '\0';
				memset(reqcmd_pid, 0, sizeof reqcmd_pid);
				memset(reqcmd_ppid, 0, sizeof reqcmd_ppid);
				sscanf(tbuf, "%*s %s %s", reqcmd_pid, reqcmd_ppid);				
				if(!strcmp(wlog_ppid, reqcmd_pid)) {
					sprintf(parentcmdstr, "%s", tbuf);
				}
			}
			pclose(pfp);
		}
	}

	it_loging_f("s2o", "%s: UserDefined-Execution. parent_cmd(%s), wlog_info(pid:%s, ppid:%s, pwd:%s, cmd:%s)\n", S2O_DAEMON, parentcmdstr, wlog_pid, wlog_ppid, pwdstr, argstr);
}

