/*
   $Id: file_read.c,v 1.7 2008/11/26 srp Exp $

   Copyright (c) 2000, 2001, 2002
             i-TOP System Inc.  All rights reserved.

*/

#include "config.h"
#include <stdio.h>
#include <string.h>
#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif

extern char S2O_DAEMON[64];
extern int it_loging(char *format,...);

int file_read(char *file, char *value)
{
	FILE *fp;
	char rbuf[2048];

	if ((fp=fopen(file, "r")) == NULL) {
       	it_loging("libIT.a(%s):  file_read() file(%s) open error!\n", S2O_DAEMON, file);
		return -1;
	}
	memset(rbuf, 0, sizeof rbuf);
	while (fgets(rbuf, 2047, fp) != NULL) {
		strcat(value, rbuf);
		memset(rbuf, 0, sizeof rbuf);
	}
	fclose(fp);
	return -1;	/* 해당 env를 못찾은 경우 error return */
}

