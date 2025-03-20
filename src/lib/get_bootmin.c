/*
   $Id: get_bootmin.c,v 1.0 2019/03/05 srp Exp $

   Copyright (c) 2019
             NewSystech Inc.  All rights reserved.

   2019-03-05
	 * uptime으로 부터 경과된 min 계산
*/

#include "config.h"
#include "../IT.extern.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int it_loging(char *format,...);

int get_bootmin(_uptime)
char *_uptime;     /* _uptime : uptime command result */
{
	/*
		boot time 계산
		8:48pm  up 8 min(s),  1 user,  load average: 0.01, 0.08, 0.06 (sun)
		9:40pm  up 1 hr(s),  1 user,  load average: 0.00, 0.00, 0.00 (sun)
		12:15pm  up 15:35,  1 user,  load average: 0.01, 0.00, 0.00 (sun)
		2:02pm  up 1 day(s), 59 min(s),  1 user,  load average: 0.01, 0.01, 0.02 (sun)
		2:02pm  up 1 day(s), 1 hr(s),  1 user,  load average: 0.01, 0.01, 0.02 (sun)
		3:02pm  up 1 day(s),  1:59,  1 user,  load average: 0.01, 0.01, 0.02 (sun)
		3:02pm  up 1 day(s), 2 hr(s),  1 user,  load average: 0.01, 0.01, 0.02 (sun)

		4:30pm  up 3 min,  1 user,  load average: 0.71, 0.63, 0.26
		04:26PM   up 11 mins,  2 users,  load average: 0.03, 0.07, 0.06
		5:17pm  up   0:04,  1 user,  load average: 0.52, 0.87, 0.41
		8:56pm  up 1 day(s), 16 min(s),  1 user,  load average: 0.00, 0.00, 0.00 (sun)
		17:25:08 up 1 day, 16 min,  2 users,  load average: 0.00, 0.01, 0.05
		5:26pm  up 1 day  0:13,  1 user,  load average: 0.00, 0.01, 0.00 (suse)
		5:09pm  up 1807 days, 14 hrs,  2 users,  load average: 0.01, 0.01, 0.02

		07:46AM up 16 days, 24 mins, 1 user, load average: 0.11, 0.20, 0.22
		04:13:19 up 1 day,  1:00,  8 users,  load average: 0.02, 0.05, 0.21
		12:49:10 up 25 days, 21:30, 28 users,  load average: 0.50, 0.66, 0.52
		3:52pm up 1323 day(s), 22:52, 53 users, load average: 2.20, 2.24, 2.12
		07:33:31 up 174 days,  5:12,  2 users,  load average: 0.17, 0.14, 0.17
		2:30pm  up 14days, 2:39, 33 users,  load average: 1.71, 1.88, 1.80
	*/

	int ifind = 0;
	int uptime_min = 0;
	char buf_1024[1024];
	char *ptr;
	char buf[2048], buf1[256], buf2[256];

	ptr = (char*) strstr(_uptime, "up");
	if ( ptr == NULL) {
		it_loging("libIT.a(%s): get_bootmin() uptime format error. (%s)\n", S2O_DAEMON, _uptime);
		return (-1);
	}

	memset(buf_1024, 0, sizeof buf_1024);
	strcpy(buf_1024, ptr);

	ptr = (char*) strstr(buf_1024, "user");
	if ( ptr == NULL) {
		it_loging("libIT.a(%s): get_bootmin() uptime format error. (%s)\n", S2O_DAEMON, _uptime);
		return (-1);
	}

	*ptr = '\0';

	ptr = (char*) strrchr(buf_1024, ',');
	if ( ptr == NULL) {
		it_loging("libIT.a(%s): get_bootmin() uptime format error. (%s)\n", S2O_DAEMON, _uptime);
		return (-1);
	}

	*ptr = '\0';

	memset(buf, 0, sizeof buf);

	ptr = (char*) strstr(buf_1024, "day");
	if ( ptr != NULL) { /* day(s) 존재하는 경우 */
		ifind = 1;
		strcpy(buf, ptr);
		*ptr = '\0';
		memset(buf2, 0, sizeof buf2);
		sscanf(buf_1024, "%*s %s", buf2);
		if (strlen(buf2) > 0) {
			uptime_min = uptime_min + atoi(buf2) * 24 * 60 ;
		}
	} else { /* day(s) 존재하지 않는 경우 */
		strcpy(buf, buf_1024);
	}

	memset(buf_1024, 0, sizeof buf_1024);
	ptr = (char*) strstr(buf, "hr");
	if ( ptr != NULL) { /* hr이 존재하는 경우 */
		strcpy(buf_1024, ptr);
		*ptr = '\0';
		memset(buf1, 0, sizeof buf1);
		sscanf(buf, "%*s %s", buf1);
		if ( strlen(buf1) == 1 || strlen(buf1) == 2) {
			ifind = 1;
			uptime_min = uptime_min+atoi(buf1) * 60 ;
		}
	} else {
		strcpy(buf_1024, buf);
	}

	memset(buf, 0, sizeof buf);
	ptr = (char*) strstr(buf_1024, "min");
	if ( ptr != NULL) {
		*ptr = '\0';
		memset(buf1, 0, sizeof buf1);
		sscanf(buf_1024, "%*s %s", buf1);
		if ( strlen(buf1) == 1 || strlen(buf1) == 2) {
			ifind = 1;
			uptime_min = uptime_min+atoi(buf1) ;
		}
	} else {
		ptr = (char*) strstr(buf_1024, ":");
		if ( ptr != NULL) {
			strcpy(buf, ptr+1);
			*ptr = '\0';
			memset(buf1, 0, sizeof buf1);
			sscanf(buf_1024, "%*s %s", buf1);

			if ( strlen(buf1) == 1 || strlen(buf1) == 2) {
				uptime_min = uptime_min+atoi(buf1) * 60 ;
				memset(buf1, 0, sizeof buf1);
				sscanf(buf, "%s", buf1);

				if ( strlen(buf1) == 1 || strlen(buf1) == 2) {
					ifind = 1;
					uptime_min = uptime_min+atoi(buf1) ;
				}
			}
		}
	}

	if ( ifind == 0) {
		it_loging("libIT.a(%s): get_bootmin() uptime format error. (%s)\n", S2O_DAEMON, _uptime);
		return(-1);
	}
	return uptime_min;
}

