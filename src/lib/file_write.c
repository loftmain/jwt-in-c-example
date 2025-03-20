/*
   $Id: file_write.c,v 1.7 2008/11/27 srp Exp $

   Copyright (c) 2000, 2001, 2002
             i-TOP System Inc.
         All rights reserved.

*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../IT.extern.h"

extern int size_check(char *file, int size);
extern int fcopy(char *src, char *dest, mode_t pmode);
extern int it_loging(char *format,...);

int file_write(char *file, char *str, int mode)
{
    FILE 	*fp;
    char 	backfile[256];

	if (mode == 1) {
    	if (size_check(file, it_local_data_size) < 0) {
       		sprintf(backfile, "%s.bak", file);
       		fcopy(file, backfile, 0600);

       		if ((fp = fopen(file, "w")) == NULL) {
          		it_loging("libIT.a(%s): file_write() file(%s) open error.\n", S2O_DAEMON, file);
          		return(-1);
        	}
		} else {
       		if ((fp = fopen(file, "a")) == NULL) {
       		   	it_loging("libIT.a(%s): file_write() file(%s) open error.\n", S2O_DAEMON, file);
          		return(-1);
        	}
		}
	} else if (mode == 0) {
       	if ((fp = fopen(file, "w")) == NULL) {
       		it_loging("libIT.a(%s): file_write() file(%s) open error.\n", S2O_DAEMON,file);
       		return(-1);
       }
	}
    /*fprintf(fp, "%s", str);*/
    /*fprintf(fp, str);*/
    /*it_loging("libIT.a(%s): TEST - %s\n", S2O_DAEMON, str);*/
    fputs(str, fp);
    fclose(fp);
    return(0);
}


int working_write(char* _file, char* _item, char* _msg)
{
    FILE *fp;
    char tmpdir[256];
    char cmdbuf[512];    
    char chktime[32];
	struct stat s1;
	char *sptr;
    time_t tvec;
    struct tm *dbuf;

	memset(tmpdir, 0, sizeof tmpdir);
	sprintf(tmpdir, "%s", _file);

	sptr = (char*) strrchr(tmpdir, '/');
	if (sptr != NULL) {
		*sptr = '\0';
		if (strlen(tmpdir) > 1) {
			if (stat(tmpdir, &s1) < 0) {
				memset(cmdbuf, 0, sizeof cmdbuf);
				sprintf(cmdbuf, "mkdir -p %s", tmpdir);
				if (system(cmdbuf) < 0) {
					it_loging("%s: command(%s) execute fail.\n", S2O_DAEMON, cmdbuf);
					return -1;
				}
			}
		}
	}
	
    time(&tvec);
    dbuf = localtime(&tvec);
    memset(chktime, 0, sizeof chktime);
    sprintf(chktime, "%-4.4d%-2.2d%-2.2d%-2.2d%-2.2d%-2.2d"
                    , dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday, dbuf->tm_hour, dbuf->tm_min, dbuf->tm_sec);


    if ((fp=fopen(_file, "w")) == NULL) {
        it_loging("%s: <pid:%d> file(%s) open error.\n", S2O_DAEMON, getpid(), _file);
        return(-1);
    }

    memset(cmdbuf, 0, sizeof cmdbuf);
    sprintf(cmdbuf, "%s;%ld;%s;%s;%d;%s;\n", _item, tvec, chktime, S2O_DAEMON, getpid(), _msg);
    fputs(cmdbuf, fp);
    fclose(fp);
    return(0);
}

