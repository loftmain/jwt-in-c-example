/*
   $Id: get_osrease.c,v 1.0 2018/05/09 srp Exp $

   Copyright (c) 2018
             NewSystech. Inc.  All rights reserved.

   2018-05-09
     * OS release 정보를 없음
*/
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../IT.extern.h"

#if defined(HPUX)
#define RELEASE         "/bin/uname -r"
#elif defined(LINUX)
#define RELEASE     "/bin/uname -r"
#elif defined(AIX)
#define RELEASE      "uname -vr"
#elif defined(DGUX) 
#define RELEASE     "/bin/uname -r"
#elif defined(NCRUX)
#define RELEASE     "/bin/uname -r"
#else   /* SUN, UNIX */
#define RELEASE     "/bin/uname -r"
#endif

extern int it_loging(char *format,...);
extern int rtrim(char* sbuf);

int get_osrelease(char* _release)
{
  	FILE 	*pfp;
	char tbuf[512];
	char os_release[512];
	char buf1[256], buf2[256];

	memset(os_release, 0, sizeof os_release);

  	if ((pfp = popen (RELEASE, "r")) == NULL) {
      	it_loging("libIT.a(%s): get_osrelease() pipe open error.\n", S2O_DAEMON);
      	return (-1);
    }

  	/* read lines off of the file until EOF */
	memset(tbuf, 0, sizeof tbuf);
  	while (fgets(tbuf, 511, pfp) != NULL) {

#if defined(HPUX)
		memset(buf1, 0, sizeof buf1);
		memset(buf2, 0, sizeof buf2);
		getitem('.', tbuf, buf1, 2);
		getitem('.', tbuf, buf2, 3);
		sprintf(os_release, "%s.%s", buf1, buf2);
#elif defined(LINUX)
		memset(buf1, 0, sizeof buf1);
		getitem('-', tbuf, buf1, 1);
		sscanf(buf1, "%s", os_release);
#elif defined(AIX)
		memset(buf1, 0, sizeof buf1);
		memset(buf2, 0, sizeof buf2);
		sscanf(tbuf, "%s %s", buf1, buf2);
		sprintf(os_release, "%s.%s", buf2, buf1);
#else   /* SUN, UNIX */
		sscanf(tbuf, "%s", os_release);	
#endif
		
    }
	pclose(pfp);

	if ( strlen(os_release) > 0) {
		strcpy(_release, os_release);
		return(1);
	}

  	return(0);
	
}
