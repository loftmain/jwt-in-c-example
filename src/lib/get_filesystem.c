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
#define DF      "/usr/bin/bdf"
#define DFL     "/usr/bin/bdf -l"
#elif defined(LINUX)
#define DF      "/bin/df -k"
#define DFL     "/bin/df -kl"
#elif defined(AIX)
#define DF      "/usr/bin/df -Pk"
#define DFL     "/usr/bin/df -Pk"
#elif defined(DGUX) 
#define DF      "/usr/bin/df -k"
#define DFL     "/usr/bin/df -kl"
#elif defined(NCRUX)
#define DF      "/sbin/df -k"
#define DFL     "/sbin/df -kl"
#else   /* SUN, UNIX */
#define DF      "/usr/sbin/df -k"
#define DFL     "/usr/sbin/df -kl"
#endif

extern int it_loging(char *format,...);
extern int get_cfg2(char* config, char* ENV, char* value);

int get_filesystem(char *cfgname)
{
    FILE    *pfd;
    char    filesystem[256], mounted[256];
    char    linebuf[512];
	char 	localonly[5];
	char	syscfg[128];
	int		linecount = 0;


   	if (get_cfg2(cfgname, "OPTION_DISKSPACE", localonly) < 0)
    	strcpy(localonly, "N");

	if (!strcmp(localonly, "Y")) {                 /* local file system only */
		if ((pfd = popen(DFL, "r")) == NULL) {
			it_loging("libIT.a(%s): get_filesystem() command(%s) execution error!\n", S2O_DAEMON, DFL);
 			return(-1);
		}
	} else {
		if ((pfd = popen(DF, "r")) == NULL) {
			it_loging("libIT.a(%s): get_filesystem() command(%s) execution error!\n", S2O_DAEMON, DF);
     		return(-1);
		}
	}

	memset(filesystem, 0x00, sizeof filesystem);
	memset(mounted, 0x00, sizeof mounted);
	while (fgets(linebuf, 511, pfd) != NULL) {
		if (linecount == -1) {              /* df -k header skip */
			linecount++;
			continue;
		}

		if (strlen(filesystem) == 0) {          /* df -k 결과가 2 line인지 check */
			sscanf(linebuf, "%s %*s %*s %*s %*s %s", filesystem, mounted);
			if (strlen(mounted) == 0)           /* 2 line 중 첫번째 line인 경우 */
				continue;
		} else
			sscanf(linebuf, "%*s %*s %*s %*s %s", mounted);
/*
		if (!strncmp(mounted, "/cdrom", 6) ||
			!strncmp(mounted, "/proc", 5)  ||
			!strncmp(mounted, "/mnt/cdrom", 10)  ||
			!strncmp(mounted, "/dev/shm", 8)  ||
			!strncmp(mounted, "/dev/odm", 8)  ||
			!strncmp(mounted, "/etc/mnttab", 11)  ||
			!strncmp(mounted, "/dev/fd", 7)) {
				memset(filesystem, 0x00, sizeof filesystem);
				memset(mounted, 0x00, sizeof mounted);
				continue; 
		}
*/
		rMounted = (struct run_mounted *) realloc (rMounted, (linecount + 1) * sizeof (struct run_mounted));

		if (rMounted == NULL) {
			it_loging("libIT.a(%s): get_filesystem() run_mounted struct realloc error.\n", S2O_DAEMON);
			pclose(pfd);
 			return(-1);
		}
		strcpy(rMounted[linecount].filesystem, filesystem);
		strcpy(rMounted[linecount].mounted, mounted);
		rMounted[linecount].filesystem[strlen(filesystem)] = '\0';
		rMounted[linecount].mounted[strlen(mounted)] = '\0';
		memset(filesystem, 0x00, sizeof filesystem);
		memset(mounted, 0x00, sizeof mounted);
		linecount++;
	}
	pclose(pfd);
	return(linecount);
}
