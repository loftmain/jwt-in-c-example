/*
   $Id: set_except_chktime.c,v 1.0 2021/06/06 srp Exp $

   Copyright (c) 2021
             NEWSYSTECH Inc.  All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include "../IT.extern.h"
/*#include "../except_chktime.h"*/

extern int it_loging(char *format,...);
extern int getitem(int ch, char *src, char *dest, int seqitem);

int set_except_chktime(char* _SERVER, char* cfgname, int _cnt_except_chktime)
{
    char fline[512];
    FILE *fd;
    struct stat stbuf1;
	struct except_check_time extchktm;	
	int i;
	char    week[][5] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	char	tmpbuf1[64], tmpbuf2[64];

	struct	tm *dbuf;
	time_t	tvec;
	char	old12month[32];
	char	*sptr;

    int num = 0;

    /*#Item;Cycle;From;To;Apply;Note;Subitem */
	
    if (stat(cfgname, &stbuf1) != 0) {
		if (_cnt_except_chktime == -100 || _cnt_except_chktime > 0) {
			it_loging_f("except", "libIT.a(%s): set_except_chktime() file(%s) not found.\n", _SERVER, cfgname);
		}
        return(-1);
    }

	time(&tvec);
	dbuf = localtime(&tvec);

	memset(old12month, 0, sizeof old12month);
	sprintf(old12month, "%4d%-2.2d", dbuf->tm_year+1900-1, dbuf->tm_mon+1);

    if ((fd = fopen(cfgname, "r")) == NULL)
    {
		it_loging("libIT.a(%s): set_except_chktime() %s file open error\n", _SERVER, cfgname);
		it_loging_f("except", "libIT.a(%s): set_except_chktime() file(%s) open error\n", _SERVER, cfgname);
        return(-1);
    }

	it_loging_f("except", "libIT.a(%s): set_except_chktime() file(%s) read.\n", _SERVER, cfgname);

    while (fgets(fline, 511, fd) != NULL)
    {
        if (fline[0] == '#' || fline[0] == '\n') continue;

        if(fline[strlen(fline)-1] =='\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';
        if(fline[strlen(fline)-1] =='\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';

		memset(extchktm.Item, 0, sizeof extchktm.Item);
		memset(extchktm.Subitem, 0, sizeof extchktm.Subitem);
		memset(extchktm.Cycle, 0, sizeof extchktm.Cycle);
		memset(extchktm.From, 0, sizeof extchktm.From);
		memset(extchktm.From_week, 0, sizeof extchktm.From_week);
		memset(extchktm.To, 0, sizeof extchktm.To);
		memset(extchktm.To_week, 0, sizeof extchktm.To_week);
		memset(extchktm.Apply, 0, sizeof extchktm.Apply);
		memset(extchktm.Subitemplus, 0, sizeof extchktm.Subitemplus);
	
        getitem(';', fline, extchktm.Item, 1);
        getitem(';', fline, extchktm.Cycle, 2);
        getitem(';', fline, extchktm.From, 3);
        getitem(';', fline, extchktm.To, 4);
        getitem(';', fline, extchktm.Apply, 5);
		getitem(';', fline, extchktm.Subitem, 7);
		getitem(';', fline, extchktm.Subitemplus, 8);

		if (!strcmp(extchktm.Cycle, "Daily")) {
		} else if (!strcmp(extchktm.Cycle, "Monthly")) {
		} else if (!strcmp(extchktm.Cycle, "Weekly")) {
			memset(tmpbuf1, 0, sizeof tmpbuf1);
			memset(tmpbuf2, 0, sizeof tmpbuf2);
			getitem('-', extchktm.From, tmpbuf1, 1);
			getitem('-', extchktm.From, tmpbuf2, 2);

			for(i = 0; i < 7; i++) {
				if (!strcmp(week[i], tmpbuf1)) {
					sprintf(extchktm.From_week, "%d-%s", i, tmpbuf2);
					break;
				}
			}

			memset(tmpbuf1, 0, sizeof tmpbuf1);
			memset(tmpbuf2, 0, sizeof tmpbuf2);
			getitem('-', extchktm.To, tmpbuf1, 1);
			getitem('-', extchktm.To, tmpbuf2, 2);

			for(i = 0; i < 7; i++) {
				if (!strcmp(week[i], tmpbuf1)) {
					sprintf(extchktm.To_week, "%d-%s", i, tmpbuf2);
					break;
				}
			}
		} else if (!strcmp(extchktm.Cycle, "None")) {
			if (strncmp(extchktm.To, old12month, strlen(old12month)) < 0) {
				sptr = (char*) strchr(fline, '\n');
				if ( sptr != NULL) *sptr = '\0';

               	it_loging("libIT.a(%s): set_except_chktime() Excluded because the set period has passed more than one year. (%s)\n" , _SERVER, fline);
               	it_loging_f("except", "libIT.a(%s): set_except_chktime() Excluded because the set period has passed more than one year. (%s)\n" , _SERVER, fline);
				continue;
			}
		}

        stExceptChktime = (struct except_check_time *) realloc(stExceptChktime, (num+1) * sizeof (struct except_check_time));
        if(stExceptChktime == NULL) {
            it_loging("libIT.a(%s): set_except_chktime() realloc error.\n", _SERVER);
            it_loging_f("except", "libIT.a(%s): set_except_chktime() realloc error.\n", _SERVER);
            fclose(fd);
            return(-1);
        }

        stExceptChktime[num] = extchktm;
        num++;
    }
    fclose(fd);

	it_loging("libIT.a(%s): set_except_chktime() cnt = %d\n", _SERVER, num);
	it_loging_f("except", "libIT.a(%s): set_except_chktime() cnt = %d\n", _SERVER, num);
	
    for (i = 0; i < num; i++) {
		it_loging("libIT.a(%s): set_except_chktime() list = %s,%s,%s,%s,%s,%s,%s,\n", _SERVER
				, stExceptChktime[i].Item, stExceptChktime[i].Cycle, stExceptChktime[i].From, stExceptChktime[i].To
				, stExceptChktime[i].Apply, stExceptChktime[i].Subitem,stExceptChktime[i].Subitemplus);

		it_loging_f("except", "libIT.a(%s): set_except_chktime() list = %s,%s,%s,%s,%s,%s,%s,\n", _SERVER
				, stExceptChktime[i].Item, stExceptChktime[i].Cycle, stExceptChktime[i].From, stExceptChktime[i].To
				, stExceptChktime[i].Apply, stExceptChktime[i].Subitem,stExceptChktime[i].Subitemplus);
    }

    return num;
}

int is_except_chktime(char* _SERVER, int _except_chktime_cnt, char* _item, char* _subitem, char* _subitemplus)
{
	int i;	
	time_t tvec;
	struct tm *dbuf;
	char ctime[32];
	char daytime[32];
	char yeartime[32];
	char weektime[32];

	if ( _except_chktime_cnt < 1) return -1;

	time(&tvec);
	dbuf = localtime(&tvec);

	memset(ctime, 0, sizeof ctime);
	sprintf(ctime, "%-2.2d:%-2.2d", dbuf->tm_hour, dbuf->tm_min);

	memset(daytime, 0, sizeof daytime);
	sprintf(daytime, "%2.2d-%-2.2d:%-2.2d", dbuf->tm_mday, dbuf->tm_hour, dbuf->tm_min);

	memset(yeartime, 0, sizeof yeartime);
	sprintf(yeartime, "%-4.4d%-2.2d%2.2d-%-2.2d:%-2.2d"
					, dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday, dbuf->tm_hour, dbuf->tm_min);

	memset(weektime, 0, sizeof weektime);
	sprintf(weektime, "%d-%-2.2d:%-2.2d", dbuf->tm_wday, dbuf->tm_hour, dbuf->tm_min);

	for(i = 0; i < _except_chktime_cnt; i++) {
		if (stExceptChktime[i].Apply[0] == 'N') continue;
		if (!strcmp(stExceptChktime[i].Item, _item)) {
			if (strlen(_subitem) > 0 || strlen(stExceptChktime[i].Subitem) > 0 ) {
				if (strcmp(stExceptChktime[i].Subitem, _subitem)) continue;
			}
			if (strlen(_subitemplus) > 0 || strlen(stExceptChktime[i].Subitemplus) > 0 ) {
				if (strcmp(stExceptChktime[i].Subitemplus, _subitemplus)) continue;
			}

			if ( !strcmp(stExceptChktime[i].Cycle, "Daily")) {	/* Daily 설정인 경우 */
				if ( strcmp(stExceptChktime[i].From,  stExceptChktime[i].To) > 0) {
					if (strcmp(ctime, stExceptChktime[i].From) >= 0 || strcmp(ctime, stExceptChktime[i].To) <= 0) return 1;
				} else {
					if (strcmp(ctime, stExceptChktime[i].From) >= 0 && strcmp(ctime, stExceptChktime[i].To) <= 0) return 1;
				}
			} else if ( !strcmp(stExceptChktime[i].Cycle, "Monthly")) {	/* Monthly 설정인 경우 */
				if ( strcmp(stExceptChktime[i].From,  stExceptChktime[i].To) > 0) {
					if (strcmp(daytime, stExceptChktime[i].From) >= 0 || strcmp(daytime, stExceptChktime[i].To)<=0) return 1;
				} else {
					if (strcmp(daytime, stExceptChktime[i].From) >= 0 && strcmp(daytime, stExceptChktime[i].To) <=0) return 1;
				}
			} else if ( !strcmp(stExceptChktime[i].Cycle, "Weekly")) { /* Weekly 설정인 경우 */
				if ( strcmp(stExceptChktime[i].From_week,  stExceptChktime[i].To_week) > 0) {
					if (strcmp(weektime, stExceptChktime[i].From_week) >= 0 || strcmp(weektime, stExceptChktime[i].To_week)<=0) return 1;
				} else {
					if (strcmp(weektime, stExceptChktime[i].From_week) >= 0 && strcmp(weektime, stExceptChktime[i].To_week) <=0) return 1;
				}
			} else if ( !strcmp(stExceptChktime[i].Cycle, "None")) { /* 기간 설정인 경우 */
				if (strcmp(yeartime, stExceptChktime[i].From) >= 0 && strcmp(yeartime, stExceptChktime[i].To) <=0) return 1;
			}
		}
	}

	return 0;
}


