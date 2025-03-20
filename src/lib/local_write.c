/*
   $Id: local_write.c,v 1.7 2002/09/02 srp Exp $

   Copyright (c) 2000, 2001, 2002
             i-TOP System Inc.
         All rights reserved.

   2002-09-06
     * S2O Agent daemon 수행시 Network 장애로 인한 전송실패시 local 파일로 저장.
*/

#include <stdio.h>
#include <string.h>
#include "../IT.extern.h"

extern int size_check(char *file, int size);
extern int fcopy(char *src, char *dest, mode_t pmode);
extern int it_loging(char *format,...);

int local_write(char *file, char *str)
{
    FILE 	*fp;
    char 	backfile[100];

    if (size_check(file, it_local_data_size) < 0) {
       	sprintf(backfile, "%s.bak", file);
       	fcopy(file, backfile, 0600);

       	if ((fp = fopen(file, "w")) == NULL) {
          	it_loging("libIT.a(%s): local_write() file(%s) open error.\n", S2O_DAEMON, file);
          	return(-1);
        }
	} else {
       	if ((fp = fopen(file, "a")) == NULL) {
          	it_loging("libIT.a(%s): local_write() file(%s) open error.\n", S2O_DAEMON, file);
          	return(-1);
        }
	}
	if ( str[strlen(str)-1] != '\n') fprintf(fp, "%s\n", str);
    else fprintf(fp, "%s", str);
    fclose(fp);
    return(0);
}
