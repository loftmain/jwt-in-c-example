/*
   $Id: it_loging.c,v 1.7 2002/11/06 srp Exp $

   Copyright (c) 2000, 2001, 2002
             i-TOP System Inc.  All rights reserved.

   2002-12-13
	 * message loging
*/

#include "config.h"
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <dirent.h>
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
#include <stdlib.h>
#include "../IT.extern.h"

#define MKDIR "/bin/mkdir"
int it_patch_loging(char *format,...);

extern void timestr(char *tim);
extern int get_cfg(char* ENV, char* value);
extern int size_check(char *file, int size);
extern int fcopy(char *src, char *dest, mode_t pmode);

int ismodcfg(char* _homedir, char* _daemon);

int it_loging(char *format,...)
{
  	FILE 	*fp;

  	va_list argptr;

  	char 	t[16];
	char 	it_home[256], itlog[300], backfile[310];
	char	it_mode[10];
	int		idefault = 0;

	if (IS_NOS2O_AGENT == 1) return 0;

  	memset(t, 0, sizeof t);
  	memset(it_home, 0, sizeof it_home);

  	timestr(t);

  	if (get_cfg("IT_HOME", it_home) < 0) {
		if (IS_NOS2O_AGENT == 2) return 0;
     	openlog("S2O", LOG_PID, LOG_DAEMON);
     	syslog(LOG_ERR, "%s: get_cfg(): can't find it_home\n", S2O_DAEMON);
     	closelog();  
     	return(-1);
    }

	memset(it_mode, 0, sizeof it_mode);
	get_cfg("IT_MODE", it_mode);

  	memset(itlog, 0x00, sizeof itlog);
	if ( !strncmp(S2O_DAEMON, "IT.orac", strlen("IT.orac"))){
  		sprintf(itlog, "%s/IT.log.orac", it_home);
	}else if ( !strncmp(S2O_DAEMON, "IT.uptd", strlen("IT.uptd"))){
  		sprintf(itlog, "%s/IT.log.uptd", it_home);
	}else if ( !strncmp(S2O_DAEMON, "IT.chkd", strlen("IT.chkd")) && strcmp(it_mode, "0")){
  		sprintf(itlog, "%s/IT.log.chkd", it_home);
	}else if ( !strncmp(S2O_DAEMON, "IT.scnsmp", strlen("IT.scnsmp"))){
  		sprintf(itlog, "%s/IT.log.scnsmp", it_home);
	}else if ( !strncmp(S2O_DAEMON, "IT.sscnsmp", strlen("IT.sscnsmp"))){
  		sprintf(itlog, "%s/IT.log.sscnsmp", it_home);
    } else if ( !strncmp(S2O_DAEMON, "IT.scnchk", strlen("IT.scnchk"))){
        sprintf(itlog, "%s/IT.log.scnchk", s2oenv.log_home);
    }else if ( !strncmp(S2O_DAEMON, "IT.sscnchk", strlen("IT.sscnchk"))){
        sprintf(itlog, "%s/IT.log.sscnchk", s2oenv.log_home);
	} else {
  		sprintf(itlog, "%s/IT.log", it_home);
		idefault = 1;
	}

  	if (size_check(itlog, it_log_size) < 0) {
     	memset(backfile, 0, sizeof backfile);
     	sprintf(backfile, "%s.bak", itlog);
     	fcopy(itlog, backfile, 0600);
     	if ((fp = fopen(itlog, "w")) == NULL) {
			if (IS_NOS2O_AGENT == 2) return 0;
        	openlog("S2O",LOG_PID,LOG_DAEMON);
        	syslog(LOG_ERR,"%s: file(%s) create error!", S2O_DAEMON, itlog);
        	closelog();
        	return(-1);
       	}
	} else {
      	if ((fp = fopen(itlog, "a")) == NULL) {
			if (IS_NOS2O_AGENT == 2) return 0;
         	openlog("S2O",LOG_PID,LOG_DAEMON);
         	syslog(LOG_ERR,"%s: file(%s) append error!", S2O_DAEMON, itlog);
         	closelog();
         	return(-1);
        }
	}

  	fprintf(fp, "%s ", t);
  	va_start(argptr, format);
  	vfprintf(fp, format, argptr);
  	va_end(argptr);
  	fclose(fp);


	/* �Ϲ� user�� ����ϴ� ���� 0666���� root�� ����ϴ� ���� 0644�� ���� */

	/* if ( ismodcfg(it_home, "IT.tibe") == 1) { */  /* IT.log ���Ͽ� �״� ��쿡�� ��� */ /* 2024/01/10 */

	if ( !strncmp(S2O_DAEMON, "IT.orac", strlen("IT.orac"))){
  		chmod(itlog, 0666);
	} else if (idefault == 1 && ismodcfg(it_home, "IT.tibe") == 1) {  /* IT.log ���Ͽ� �״� ��쿡�� ��� */
  		chmod(itlog, 0666);
	} else {
  		chmod(itlog, 0644); 
	}

  	return(0);
}

int it_loging_f(char*_sub, char *format,...)
{
  	FILE 	*fp;

  	va_list argptr;

  	char 	t[16];
	char 	it_home[256], itlog[350], backfile[360];
	char	sptr;
	char 	subname[60];

	memset(subname, 0, sizeof subname);
	sprintf(subname, "%s", _sub);

	if (IS_NOS2O_AGENT == 1) return 0;

  	memset(t, 0, sizeof t);
  	memset(it_home, 0, sizeof it_home);

  	timestr(t);

  	if (get_cfg("IT_HOME", it_home) < 0) {
		if (IS_NOS2O_AGENT == 2) return 0;
     	openlog("S2O", LOG_PID, LOG_DAEMON);
     	syslog(LOG_ERR, "%s: get_cfg(): can't find it_home\n", S2O_DAEMON);
     	closelog();  
     	return(-1);
    }

  	memset(itlog, 0x00, sizeof itlog);
	if (strlen(subname) > 0) 
  		sprintf(itlog, "%s/IT.log.%s", it_home, subname);
	else
  		sprintf(itlog, "%s/IT.log", it_home);

  	if (size_check(itlog, it_log_size) < 0) {
     	memset(backfile, 0, sizeof backfile);
     	sprintf(backfile, "%s.bak", itlog);
		if (!strcmp(subname ,"s2o")) 
     		fcopy(itlog, backfile, 0666);
		else
     		fcopy(itlog, backfile, 0600);
     	if ((fp = fopen(itlog, "w")) == NULL) {
			if (IS_NOS2O_AGENT == 2) return 0;
        	openlog("S2O",LOG_PID,LOG_DAEMON);
        	syslog(LOG_ERR,"%s: file(%s) create error!", S2O_DAEMON, itlog);
        	closelog();
        	return(-1);
       	}
	} else {
      	if ((fp = fopen(itlog, "a")) == NULL) {
			if (IS_NOS2O_AGENT == 2) return 0;
         	openlog("S2O",LOG_PID,LOG_DAEMON);
         	syslog(LOG_ERR,"%s: file(%s) append error!", S2O_DAEMON, itlog);
         	closelog();
         	return(-1);
        }
	}
  	fprintf(fp, "%s ", t);
  	va_start(argptr, format);
  	vfprintf(fp, format, argptr);
  	va_end(argptr);
  	fclose(fp);

	if ( !strcmp(subname, "s2o")) {
	} else if (ismodcfg(it_home, "IT.tibe") == 1) {
  		chmod(itlog, 0666);
	} else if ( !strncmp(S2O_DAEMON, "IT.orac", strlen("IT.orac"))){
  		chmod(itlog, 0666);
	} else {
  		chmod(itlog, 0644); 
	}
  	return(0);
}

int ismodcfg(char* _homedir, char* _daemon)
{
    FILE    *pfd;
    char cmdbuf[256];
    char linebuf[1024], buf[512];

    memset(cmdbuf, 0, sizeof cmdbuf);
    sprintf(cmdbuf, "cat %s/mod.cfg|grep %s", _homedir, _daemon);

    if ((pfd = popen(cmdbuf, "r")) == NULL) {
        /*it_loging("libIT.a(%s): ismodcfg() command(%s) open error!\n", S2O_DAEMON, cmdbuf);*/
     	openlog("S2O", LOG_PID, LOG_DAEMON);
       	syslog(LOG_ERR, "%s: ismodcfg() command(%s) open error!", S2O_DAEMON, cmdbuf);
     	closelog();  
        return(-1);
    }
    memset(linebuf, 0, sizeof linebuf);
    while (fgets(linebuf, 1023, pfd) != NULL) {
        memset(buf, 0, sizeof buf);
        sscanf(linebuf, "%s", buf);
        if (!strcmp(buf, _daemon)) {
            pclose(pfd);
            return(1);
        }
    }
    pclose(pfd);
    return(0);
}

int it_dmsloging(char *format,...)
{
  	FILE 	*fp;
	DIR		*dp;
  	va_list argptr;
  	char 	t[16];
	char 	it_home[256], itlog[300], backfile[310];
	char	bufstr[300];
	int		ret;
	

  	memset(t, 0, sizeof t);
  	memset(it_home, 0, sizeof it_home);

  	timestr(t);
  	if (get_cfg("IT_HOME", it_home) < 0) {
     	openlog("S2O", LOG_PID, LOG_DAEMON);
     	syslog(LOG_ERR, "%s: get_cfg(): can't find it_home\n", S2O_DAEMON);
     	closelog();  
     	return(-1);
    }
	memset(bufstr, 0, sizeof bufstr);
	sprintf(bufstr, "%s/DMS/log", it_home);

	if ((dp = opendir(bufstr)) == NULL) {
		memset(bufstr, 0, sizeof bufstr);
		sprintf(bufstr, "%s -p %s/DMS/log", MKDIR, it_home);
		ret = system(bufstr);
	} else
		closedir(dp);

  	memset(itlog, 0x00, sizeof itlog);
  	sprintf(itlog, "%s/DMS/log/IT.dmslog", it_home);

  	if (size_check(itlog, it_log_size) < 0) {
     	memset(backfile, 0, sizeof backfile);
     	sprintf(backfile, "%s.bak", itlog);
     	fcopy(itlog, backfile, 0600);
     	if ((fp = fopen(itlog, "w")) == NULL) {
        	openlog("S2O",LOG_PID,LOG_DAEMON);
        	syslog(LOG_ERR,"%s: file(%s) create error!", S2O_DAEMON, itlog);
        	closelog();
        	return(-1);
       	}
	} else {
      	if ((fp = fopen(itlog, "a")) == NULL) {
         	openlog("S2O",LOG_PID,LOG_DAEMON);
         	syslog(LOG_ERR,"%s: file(%s) append error!", S2O_DAEMON, itlog);
         	closelog();
         	return(-1);
        }
	}
  	fprintf(fp, "%s ", t);
  	va_start(argptr, format);
  	vfprintf(fp, format, argptr);
  	va_end(argptr);
  	fclose(fp);
  	chmod(itlog, 0644); 
  	return(0);
}

int it_patch_loging(char *format,...)
{
    FILE    *fp;
    va_list argptr;

    char    t[16];
    char 	itlog[300], backfile[310];
    char 	tmsg[4096];
    char 	it_home[256];

	memset(it_home, 0, sizeof it_home);
  	if (get_cfg("IT_HOME", it_home) < 0) {
       it_loging("libIT.a(%s): it_patch_loging()  get(IT_HOME) error - %s", S2O_DAEMON, tmsg);
     	return(-1);
    }

    memset(tmsg, 0x00, sizeof tmsg);
    va_start(argptr, format);
    vsprintf(tmsg, format, argptr);
    va_end(argptr);

    memset(t, 0, sizeof t);

    timestr(t);
    memset(itlog, 0x00, sizeof itlog);
    sprintf(itlog, "%s/IT.patchlog", it_home);

    if (size_check(itlog, it_log_size) < 0) {
        memset(backfile, 0, sizeof backfile);
        sprintf(backfile, "%s.bak", itlog);
        fcopy(itlog, backfile, 0600);
        if ((fp = fopen(itlog, "w")) == NULL) {
            it_loging("libIT.a(%s): it_patch_loging() open error - %s", S2O_DAEMON, tmsg);
            return(-1);
        }
    } else {
        if ((fp = fopen(itlog, "a")) == NULL) {
            it_loging("libIT.a(%s): it_patch_loging()  open error - %s", S2O_DAEMON, tmsg);
            return(-1);
        }
    }
    fprintf(fp, "%s ", t);
    fprintf(fp, "%s", tmsg);
    fclose(fp);
    chmod(itlog, 0644);
    return(0);
}

int it_capa_loging(char *format,...)
{
    FILE    *fp;
	DIR		*dp;
    va_list argptr;

    char 	it_home[256], currday[9], daytime[64];
    char 	itlog[300], tmsg[4096];
	struct	stat stbuf;
	int 	iFexits = 0;

	memset(it_home, 0x00, sizeof it_home);
  	if (get_cfg("IT_HOME", it_home) < 0) {
       	it_loging("libIT.a(%s): it_capa_loging() get(IT_HOME:%s) error!\n", S2O_DAEMON, it_home);
     	return(-1);
    }

    memset(tmsg, 0x00, sizeof tmsg);
    memset(currday, 0x00, sizeof currday);
    
    va_start(argptr, format);
    vsprintf(tmsg, format, argptr);
    va_end(argptr);

	/*daytime = va_arg(argptr, char*);*/

	memset(daytime, 0, sizeof daytime);
	sscanf(tmsg, "%s", daytime);
	strncpy(currday, daytime, 8);

	/* ������Ʈ ���� ��ġ �� dump ������ �� ����� ó�� ���� */
    memset(itlog, 0x00, sizeof itlog);
    sprintf(itlog, "%s/dump/cpu_raw_%s.lst", it_home, currday);

	if (stat(itlog, &stbuf) == 0) iFexits = 1;

    if ((fp = fopen(itlog, "a")) == NULL) {
    	it_loging("libIT.a(%s); it_capa_loging() open error - %s", S2O_DAEMON, tmsg);
       	return(-1);
    }

	if (iFexits == 0) {
		fprintf(fp, "TIME           USER\tSYS\tWIO\tIDLE\n");	
	}

    fprintf(fp, "%s", tmsg);
    fclose(fp);
    chmod(itlog, 0644);
    return(0);
}

int ___it_debugloging(char* _daemon, int _debugtype, char *format,...)
{
    FILE    *fp;
    va_list argptr;
    char    t[16];
    char    itdebuglog[300], backfile[310];
    char    bufstr[256];
	char	it_home[256];
    char	tmsg[4096];

	if ( _debugtype == 1) 
	{
		memset(it_home, 0, sizeof it_home);
  		if (get_cfg("IT_HOME", it_home) < 0) {
	       	it_loging("libIT.a(%s): ___it_debugloging() get(IT_HOME) error - %s", _daemon, tmsg);
     		return(-1);
		}

    	memset(t, 0, sizeof t);
    	timestr(t);

    	memset(itdebuglog, 0x00, sizeof itdebuglog);
    	sprintf(itdebuglog, "%s/IT.debuglog", it_home);

    	if (size_check(itdebuglog, it_log_size) < 0) {
        	memset(backfile, 0, sizeof backfile);
        	sprintf(backfile, "%s.bak", itdebuglog);
        	fcopy(itdebuglog, backfile, 0600);
        	if ((fp = fopen(itdebuglog, "w")) == NULL) {
            	it_loging("libIT.a(%s): ___it_debugloging() file(%s) create error!", _daemon, itdebuglog);
            	return(-1);
        	}
    	} else {
        	if ((fp = fopen(itdebuglog, "a")) == NULL) {
            	it_loging("libIT.a(%s): ___it_debugloging() file(%s) append error!", _daemon, itdebuglog);
            	return(-1);
        	}
    	}
    	fprintf(fp, "%s ", t);
    	va_start(argptr, format);
    	vfprintf(fp, format, argptr);
    	va_end(argptr);
    	fclose(fp);
    	chmod(itdebuglog, 0644);
	}

    return(0);
}

int it_scloging(char *format,...)
{
  	FILE 	*fp;

  	va_list argptr;

  	char 	t[16];
	char 	it_home[256], itlog[300], backfile[310];

	if (IS_NOS2O_AGENT == 1) return 0;

  	memset(t, 0, sizeof t);
  	memset(it_home, 0, sizeof it_home);

  	timestr(t);
  	if (get_cfg("IT_HOME", it_home) < 0) {
		if (IS_NOS2O_AGENT == 2) return 0;
     	openlog("S2O", LOG_PID, LOG_DAEMON);
     	syslog(LOG_ERR, "%s: get_cfg(): can't find it_home\n", S2O_DAEMON);
     	closelog();  
     	return(-1);
    }
  	memset(itlog, 0x00, sizeof itlog);
  	sprintf(itlog, "%s/IT.sclog", it_home);

  	if (size_check(itlog, it_log_size) < 0) {
     	memset(backfile, 0, sizeof backfile);
     	sprintf(backfile, "%s.bak", itlog);
     	fcopy(itlog, backfile, 0600);
     	if ((fp = fopen(itlog, "w")) == NULL) {
			if (IS_NOS2O_AGENT == 2) return 0;
        	openlog("S2O",LOG_PID,LOG_DAEMON);
        	syslog(LOG_ERR,"%s: file(%s) create error!", S2O_DAEMON, itlog);
        	closelog();
        	return(-1);
       	}
	} else {
      	if ((fp = fopen(itlog, "a")) == NULL) {
			if (IS_NOS2O_AGENT == 2) return 0;
         	openlog("S2O",LOG_PID,LOG_DAEMON);
         	syslog(LOG_ERR,"%s: file(%s) append error!", S2O_DAEMON, itlog);
         	closelog();
         	return(-1);
        }
	}
  	fprintf(fp, "%s ", t);
  	va_start(argptr, format);
  	vfprintf(fp, format, argptr);
  	va_end(argptr);
  	fclose(fp);

  	return(0);
}

