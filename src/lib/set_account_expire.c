/*
   $Id: set_account_expire.c,v 1.0 2021/11/02 srp Exp $

   Copyright (c) 2021
             NEWSYSTECH Inc.  All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
/*#include "../accountinfo.h"*/
#include "config.h"
#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int getitem(int ch, char *src, char *dest, int seqitem);

int set_account_expire(char* _SERVER, char* cfgname)
{
	char fline[512];
	FILE *fd;
	struct stat stbuf1;
	char item[128];
	char tmpbuf[128];
	int i;
	char *ptr;

	time_t tvec1;
	struct tm *dbuf1;

	memset(acc_expire_chk.apply, 0, sizeof acc_expire_chk.apply);
	memset(acc_expire_chk.lastchktime, 0, sizeof acc_expire_chk.lastchktime);
	memset(acc_expire_chk.exclude_expired, 0, sizeof acc_expire_chk.exclude_expired);
	memset(acc_expire_chk.exclude_lock, 0, sizeof acc_expire_chk.exclude_lock);

	acc_expire_chk.hour = -1;
	acc_expire_chk.min = -1;
	acc_expire_chk.warn = -1;
	acc_expire_chk.crit = -1;

	acc_expire_exp_cnt = 0;

	/*
	account_expire.cfg
	ACCOUNT_EXPIRE_CHECK;Y;10;10;10;N;N;
	ACCOUNT_EXPIRE_EXCEPT;test01;#예외설정
	ACCOUNT_EXPIRE_EXCEPT;test02;#예외설정
	*/

	if (stat(cfgname, &stbuf1) != 0) {
		return(-1);
	}

	if ((fd = fopen(cfgname, "r")) == NULL)
	{
		it_loging("libIT.a(%s): set_account_expire() (%s) file open error\n", _SERVER, cfgname);
		return(-1);
	}

	while (fgets(fline, 511, fd) != NULL)
	{
		if (fline[0] == '#' || fline[0] == '\n') continue;

		if(fline[strlen(fline)-1] =='\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';
		if(fline[strlen(fline)-1] =='\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';

		memset(item, 0, sizeof item);
		getitem(';', fline, item, 1);

		if ( !strcmp(item, "ACCOUNT_EXPIRE_CHECK")) {

			getitem(';', fline, acc_expire_chk.apply, 2);

			memset(tmpbuf, 0, sizeof tmpbuf);
			getitem(';', fline, tmpbuf, 3);
			acc_expire_chk.hour = atoi(tmpbuf);

			memset(tmpbuf, 0, sizeof tmpbuf);
			getitem(';', fline, tmpbuf, 4);
			acc_expire_chk.min = atoi(tmpbuf);

			memset(tmpbuf, 0, sizeof tmpbuf);
			getitem(';', fline, tmpbuf, 5);
			acc_expire_chk.warn = atoi(tmpbuf);

			memset(tmpbuf, 0, sizeof tmpbuf);
			getitem(';', fline, tmpbuf, 6);
			acc_expire_chk.crit = atoi(tmpbuf);

			getitem(';', fline, acc_expire_chk.exclude_expired, 7);
			getitem(';', fline, acc_expire_chk.exclude_lock, 8);

			time(&tvec1);
			dbuf1 = localtime(&tvec1);

			if ( (dbuf1->tm_hour > acc_expire_chk.hour)
				|| (dbuf1->tm_hour == acc_expire_chk.hour && dbuf1->tm_min > acc_expire_chk.min))
			{
				sprintf(acc_expire_chk.lastchktime, "%-4.4d%-2.2d%-2.2d %-2.2d:%-2.2d:%-2.2d", dbuf1->tm_year+1900
									, dbuf1->tm_mon+1, dbuf1->tm_mday, dbuf1->tm_hour, dbuf1->tm_min, dbuf1->tm_sec);
			}
		} else if ( !strcmp(item, "ACCOUNT_EXPIRE_EXCEPT")) {

			ptr = (char*)strchr(fline, '#');
			if ( ptr != NULL) *ptr = '\0';

			acc_expire_exp = (struct acc_expire_except *) realloc(acc_expire_exp, (acc_expire_exp_cnt+1) * sizeof (struct acc_expire_except));
			if(acc_expire_exp == NULL) {
				it_loging("libIT.a(%s): set_account_expire() acc_expire_exp realloc error.\n", _SERVER);
				fclose(fd);
				return(-1);
			}

			memset(tmpbuf, 0, sizeof tmpbuf);
			getitem(';', fline, tmpbuf, 2);
			strcpy(acc_expire_exp[acc_expire_exp_cnt].name, tmpbuf);
			acc_expire_exp_cnt++;

		}
	}
	fclose(fd);

	it_loging("libIT.a(%s): set_account_expire() acc_expire_check - apply(%s), hour(%d), min(%d), warning(%d), critical(%d), exclude_expired(%s), exclude_lock(%s)\n", _SERVER, acc_expire_chk.apply, acc_expire_chk.hour, acc_expire_chk.min, acc_expire_chk.warn, acc_expire_chk.crit, acc_expire_chk.exclude_expired, acc_expire_chk.exclude_lock);

	for (i = 0; i < acc_expire_exp_cnt; i++) {
		it_loging("libIT.a(%s): set_account_expire() excluded user - %s\n", _SERVER, acc_expire_exp[i].name);
		/*it_loging("libIT.a(%s): set_account_expire() acc_expire_except - %s\n", _SERVER, acc_expire_exp[i].name);*/
	}
	return 1;

}


