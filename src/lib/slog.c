/*
   $Id: slog.c,v 1.7 2003/04/04 srp Exp $

   Copyright (c) 2000, 2001, 2002, 2003
             i-TOP System Inc.  All rights reserved.

   2003-04-04
     * Argument가 있을 경우 Argument를 syslog 보낼 수 있도록 수정.
*/
#include "config.h"
#include <sys/types.h>
#include <sys/param.h>
#include <sys/file.h>
#include <sys/ipc.h>
#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif
#include <signal.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <syslog.h>
#include "../IT.extern.h"

int slog_info(char *msg,...)
{
   	va_list argptr;	

   	char tmsg[2048];

   	memset(tmsg, 0x00, sizeof tmsg);
   	va_start(argptr, msg);
   	vsprintf(tmsg, msg, argptr);

   	openlog("S2O", LOG_PID|LOG_NDELAY, LOG_DAEMON|LOG_USER|LOG_AUTH);
   	syslog(LOG_INFO, "%s", tmsg);
   	closelog();

   	va_end(argptr);
	return 1;
}

int slog_warn(char *msg,...)
{
   	va_list argptr;
   	char tmsg[2048];

   	memset(tmsg, 0x00, sizeof tmsg);
   	va_start(argptr, msg);
   	vsprintf(tmsg, msg, argptr);

   	openlog("S2O", LOG_PID|LOG_NDELAY, LOG_DAEMON|LOG_USER|LOG_AUTH);
   	syslog(LOG_WARNING, "%s", tmsg);
   	closelog();

   	va_end(argptr);
	return 1;
}

int slog_crit(char *msg,...)
{
   	va_list argptr;
   	char tmsg[2048];

   	memset(tmsg, 0x00, sizeof tmsg);
   	va_start(argptr, msg);
   	vsprintf(tmsg, msg, argptr);

   	openlog("S2O", LOG_PID|LOG_NDELAY, LOG_DAEMON|LOG_USER|LOG_AUTH);
   	syslog(LOG_CRIT, "%s", tmsg);
   	closelog();

   	va_end(argptr);
	return 1;
}

int ksecslog(char *msg,...)
{
   va_list argptr;	
   char tmsg[2048];

   memset(tmsg, 0x00, sizeof tmsg);
   va_start(argptr,msg);
   vsprintf(tmsg,msg,argptr);
   openlog("USECCMD",LOG_PID,LOG_INFO);
   syslog(LOG_INFO,"%s", tmsg);
   closelog();
   va_end(argptr);
   return 1;
}
