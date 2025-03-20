/*
   $Id: file_write.c,v 1.7 2008/11/27 srp Exp $

   Copyright (c) 2000, 2001, 2002
             i-TOP System Inc.
         All rights reserved.

*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int fcopy(char *src, char *dest, mode_t pmode);
extern int size_check(char *file, int size);

int rcvd_local_write(char* ithome, int sockno, char *str)
{
    FILE    *fp;
    char    backfile[300];
    char    file[256];
    char    dir[256];
    char    mkdir[256];
    struct  stat s1;
	/* int		msg_size = 500000;*/
	int		msg_size = 3000000;
	int		ret;
	int 	isockn = sockno;


	/* sockno는 여러개의 파일을 생성하지 않기 위해 사용됨 */
	/* 현재는 0, 4 만 발생함, ( 0:IT.mond, 4:IT.rcvd )  */
	/* IT.rcvd에서 accept시 중복을 줄이기 위해 사용했으나 fork 처리로 인해 4만 발생함)

	if ( isockn != 0 && isockn != 10000) {
		isockn = 1;
	}

    memset(dir, 0, sizeof dir);
    sprintf(dir, "%s/RCVD_DAT", ithome);

    if (stat(dir, &s1) < 0)  {
        sprintf(mkdir, "/bin/mkdir -p %s", dir);
        ret = system(mkdir);
    }
	
    memset(file, 0, sizeof file);
    sprintf(file, "%s/rcvd_%d.dat", dir, isockn);

	if (isockn == 0) msg_size = 5000000; /* sockeno = 0 은 IT.mond에서 들어옴 */

    if (size_check(file, msg_size) < 0) { 
        sprintf(backfile, "%s/rcvd_%d_bak.dat", dir, isockn);
        fcopy(file, backfile, 0600);

        if ((fp = fopen(file, "w")) == NULL) {
            it_loging("libIT.a(%s): rcvd_local_write() file(%s) open error.\n", S2O_DAEMON, file);
            return(-1);
        }
    } else {
        if ((fp = fopen(file, "a")) == NULL) {
            it_loging("libIT.a(%s): rcvd_local_write() file(%s) open error.\n", S2O_DAEMON, file);
            return(-1);
        }
    }
	if ( str[strlen(str)-1] == '\n') fprintf(fp, "%s", str);
    else fprintf(fp, "%s\n", str);
    fclose(fp);
    return(0);
}
