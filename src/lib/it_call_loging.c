/*
   $Id: call_loging.c,v 1.0 2015/07/22 srp Exp $

   Copyright (c) 2015
             NewSystech Inc.  All rights reserved.

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

extern void timestr(char *tim);
extern int get_cfg(char* ENV, char* value);
extern int size_check(char *file, int size);
extern int fcopy(char *src, char *dest, mode_t pmode);
extern int it_loging(char *format,...);

int it_call_loging(int _idebug_type, char *format,...)
{
  	FILE 	*fp;
	DIR		*dp;
  	va_list argptr;
  	char 	t[16];
	char 	it_home[256], itcalllog[300], backfile[512];
	char	bufstr[256];
	char 	talk_debug[5], sms_debug[5], mail_debug[5], phone_debug[5];
	char	szDebug_type[64];
	char	all_debug[5];
	
  	memset(t, 0, sizeof t);
  	timestr(t);

  	memset(it_home, 0, sizeof it_home);
  	if (get_cfg("IT_HOME", it_home) < 0) {
		it_loging("libIT.a(%s): it_call_loging() get_cfg() error!\n", S2O_DAEMON);
     	return(-1);
    }

	memset(all_debug, 0, sizeof all_debug);
  	get_cfg("DEBUG_CALL_ALL", all_debug); 

	memset(szDebug_type, 0, sizeof szDebug_type);
	if (_idebug_type == DEBUG_CALL_TALK) {
		memset(talk_debug, 0, sizeof talk_debug);
  		get_cfg("DEBUG_CALL_TALK", talk_debug); 
		if (all_debug[0]!='Y' && talk_debug[0] != 'Y') return(-1);
		strcpy(szDebug_type, "[TALK]");
	} else if (_idebug_type == DEBUG_CALL_SMS) {
		memset(sms_debug, 0, sizeof sms_debug);
  		get_cfg("DEBUG_CALL_SMS", sms_debug);
		if (all_debug[0]!='Y' && sms_debug[0] != 'Y') return(-1);
		strcpy(szDebug_type, "[SMS]");
	} else if (_idebug_type == DEBUG_CALL_MAIL) {
		memset(mail_debug, 0, sizeof mail_debug);
  		get_cfg("DEBUG_CALL_MAIL", mail_debug);
		if (all_debug[0]!='Y' && mail_debug[0] != 'Y') return(-1);
		strcpy(szDebug_type, "[MAIL]");
	} else if (_idebug_type == DEBUG_CALL_PHONE) {
		memset(phone_debug, 0, sizeof phone_debug);
  		get_cfg("DEBUG_CALL_PHONE", phone_debug);
		if (all_debug[0]!='Y' && phone_debug[0] != 'Y') return(-1);
		strcpy(szDebug_type, "[PHONE]");
	} else if (_idebug_type == DEBUG_CALL_MUST) {
		strcpy(szDebug_type, "[MUST]");
	} else {
		if (all_debug[0]!='Y' && phone_debug[0] != 'Y') return(-1);
		strcpy(szDebug_type, "[ALL]");
		return(-1);
	}

  	memset(itcalllog, 0x00, sizeof itcalllog);
  	/*sprintf(itcalllog, "%s/IT.log.call", it_home);*/
  	sprintf(itcalllog, "%s/IT.calllog", it_home);

  	if (size_check(itcalllog, it_log_size) < 0) {
     	memset(backfile, 0, sizeof backfile);
     	sprintf(backfile, "%s.bak", itcalllog);
     	fcopy(itcalllog, backfile, 0600);
     	if ((fp = fopen(itcalllog, "w")) == NULL) {
        	return(-1);
       	}
	} else {
      	if ((fp = fopen(itcalllog, "a")) == NULL) {
         	return(-1);
        }
	}
  	fprintf(fp, "%s %s ", t, szDebug_type);
  	va_start(argptr, format);
  	vfprintf(fp, format, argptr);
  	va_end(argptr);
  	fclose(fp);
  	chmod(itcalllog, 0644); 
  	return(0);
}

