/*
   $Id: get_itdev.c, v1.0 2021/07/09 srp Exp $
   Copyright (c) 2021
             NewSystech Inc.
         All rights reserved.

*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include "../config.h"
#include "../libIT.h"

extern int it_loging(char *format,...);

int get_itdev(char* _itdev, char *owner)
{
	char *SYSLOG1 = "/etc/syslog.conf";
	char *SYSLOG2 = "/etc/rsyslog.conf";
	char *SYSLOG3 = "/etc/syslog-ng/syslog-ng.conf";

	char tmp_it_dev[256], tmp_it_dev_home[256];

	FILE *pfp;
	char cmdbuf[256];
	char tbuf[2048];
	char *s;
	char buf1[256], buf2[256];
	char syslogconf[256];
	char user[256];
	int find = 0;

	memset(user, 0, sizeof user);

	memset(tmp_it_dev, 0, sizeof tmp_it_dev);
	memset(tmp_it_dev_home, 0, sizeof tmp_it_dev_home);

#if defined(LINUX)

	get_cfg("IT_DEV_HOME",  tmp_it_dev);
	sscanf(tmp_it_dev, "%s", tmp_it_dev_home);

	if (strlen(tmp_it_dev_home) > 0 ) {

		memset(tmp_it_dev, 0, sizeof tmp_it_dev);
		sprintf(tmp_it_dev, "%s/S2O_IT.dev", tmp_it_dev_home);

		memset(cmdbuf, 0, sizeof cmdbuf);
		sprintf(cmdbuf, "/bin/ps -e -eo user,pid,ppid,args|grep syslog|egrep -v 'COMMAND|ps -w|grep'");

		memset(syslogconf, 0, sizeof syslogconf);

		if ((pfp = popen(cmdbuf, "r")) != NULL) {
			while (fgets(tbuf, 2047, pfp) != NULL) {
				memset(user, 0, sizeof user);
				memset(buf1, 0, sizeof buf1);
				memset(buf2, 0, sizeof buf2);
				sscanf(tbuf, "%s %*s %*s %s", user, buf1);
				s=(char*) strrchr(buf1, '/');
				if ( s != NULL) {
					strcpy(buf2, s+1);
				} else {
					strcpy(buf2, buf1);
				}
				if ( !strcmp(buf2, "syslog-ng")) {
					strcpy(syslogconf, SYSLOG3);
					break;
				} else if ( !strcmp(buf2, "rsyslogd")) {
					strcpy(syslogconf, SYSLOG2);
					break;
				} else if ( !strcmp(buf2, "syslogd")) {
					strcpy(syslogconf, SYSLOG1);
					break;
				}
			}
			pclose(pfp);
		
			if (strlen(syslogconf) > 0) {
				memset(cmdbuf, 0, sizeof cmdbuf);
				sprintf(cmdbuf, "grep IT.dev %s", syslogconf);	
				if (( pfp = popen(cmdbuf, "r")) != NULL) {
					while(fgets(tbuf, 2047, pfp ) != NULL) {
						if (find == 0) find = 1;
						s = (char*) strchr(tbuf, '#');
						if ( s!= NULL)  *s = '\0';
						s = (char*)strstr(tbuf, "S2O_IT.dev");
						if ( s != NULL) {
							find = 3;
							break;
						}
						s = (char*)strstr(tbuf, "IT.dev");
						if ( s != NULL) {
							find = 2;
						}
					}
					pclose(pfp);
				}

				if ( find == 3 ) {
					memset(tmp_it_dev, 0, sizeof tmp_it_dev);
					sprintf(tmp_it_dev, "%s/S2O_IT.dev", tmp_it_dev_home);
					strcpy(_itdev, tmp_it_dev);

					sprintf(owner, "%s", user);
				}
			}
		}

	}

#endif

	return find;
}


