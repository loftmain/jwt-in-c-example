/*
 * Copyright (c) 2000 - 2004 ITOP SYSTEM Inc. All rights reserved.
 *
 * NAME
 *      get_chkserv.c - Agent server list get.
 *
 * MODIFIED     (MM/DD/YYYY)
 *  MyungKyun   01/08/2004 - Connect timeout 설정 기능 추가.
 *
 */
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <ctype.h>
#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int get_cfg(char* ENV, char* value);

int get_chkserv(char *config_fname)
{
  	FILE 	*fd;

  	char 	tbuf[1024];
  	char 	fline[256];
	char 	hostname[64], hostip[16], type[7];
	char	it_company[10];
	char	companycode[10], ELevel[5];
  	int 	host_num = 0, router_num = 0, i, k;
	int		timeout = 5;
	int		attempt;
  	struct 	hostent *host = NULL;
	char	notchkfrom[10], notchkto[10], notchksyslog[5], notchkperf[5];
	char	chkCrFile[10];
	char	chkTimeSync[5];
	char	gapTimeSync[5];
	char 	tmpbuf[128];
	int		evt_lvl_mincnt = 0;

	memset(it_company, 0, sizeof it_company);
    if (get_cfg("IT_COMPANY_CODE", it_company) < 0) {
	    it_loging("libIT.a(%s): get_chkserv() parameter(IT_COMPANY_CODE) error!\n", S2O_DAEMON);
	}

  	if ((fd = fopen(config_fname, "r")) == NULL) {
      	return (-1);
    }


  	/* read lines off of the file until EOF */
  	while (fgets(tbuf, 255, fd) != NULL) {
      	/* perl-style comments */
      	if (tbuf[0] == '#' || (tbuf[0] == ';') || isspace (tbuf[0]) || tbuf[0] == '\n') /* ; 체크 하지 않을 경우 사용. */
			continue;

		/* #hostname       ip address          N/W     Timeout     CompanyCode     Attempt     EventLevel ChkTime GapTime ChkCrFile  ^NotCheckTimeFrom^NotCheckTimeTo^PerfCheck^SyslogCheck^EventLevelMinCnt^Note^DisableReason */

		memset(fline, 0, sizeof fline);
		memset(notchkfrom, 0, sizeof notchkfrom);
		memset(notchkto, 0, sizeof notchkto);
		memset(notchksyslog, 0, sizeof notchksyslog);
		memset(notchkperf, 0, sizeof notchkperf);
		memset(chkCrFile, 0, sizeof chkCrFile);

		getitem('^', tbuf, fline, 1);
		getitem('^', tbuf, notchkfrom, 2);
		getitem('^', tbuf, notchkto, 3);
		getitem('^', tbuf, notchkperf, 4);
		getitem('^', tbuf, notchksyslog, 5);

		memset(tmpbuf, 0, sizeof tmpbuf);
		getitem('^', tbuf, tmpbuf, 6);
		evt_lvl_mincnt = atoi(tmpbuf);
		if (evt_lvl_mincnt < 1) evt_lvl_mincnt = 1;
		else if ( evt_lvl_mincnt > 9) evt_lvl_mincnt = 9;

		/*getitem('^', tbuf, chkCrFile, 9);*/

		memset(type, 0x00, sizeof type);	
		memset(hostip, 0x00, sizeof hostip);		/* No delete this line */
		memset(companycode, 0x00, sizeof companycode);
		memset(ELevel, 0x00, sizeof ELevel);
		memset(chkTimeSync, 0, sizeof chkTimeSync);
		memset(gapTimeSync, 0, sizeof gapTimeSync);
		attempt = 1;

		sscanf(fline, "%s %s %s %d %s %d %s %s %s %s", hostname, hostip, type, &timeout, companycode, &attempt, ELevel, chkTimeSync, gapTimeSync, chkCrFile);

		if (!strcmp(hostname, "ServerCheckInt") || !strcmp(hostname, "RouterCheckInt") ||
		    !strcmp(hostname, "PacketSize") || !strcmp(hostname, "nPackets"))
			continue;

		if (strcmp(type, "SERVER") != 0 )		/* 서버가 아닐 경우 */
			continue;

		if (strlen(hostip) < 8 ) {			/* 최소 Bytes 지정 */
	      	/* lookup the hostname */
	      	/* if the string is an IP addy, it will just put that there */
	      	if ((host = gethostbyname(hostname)) == NULL) {
		  		it_loging("libIT.a(%s): get_chkserv() unable to resolve hostname %s\n", S2O_DAEMON, hostname);
				continue;
			}
		} else {
	      	if ((host = gethostbyname(hostip)) == NULL) {
		  		it_loging("libIT.a(%s): get_chkserv() unable to resolve hostip %s\n", S2O_DAEMON, hostip);
				continue;
			}
		}

		if (strcmp(ELevel, "F")) strcpy(ELevel, "C");

  		/* reallocate array to hold the new entry */
		hosts = (struct host_struct *) realloc (hosts, (host_num + 1) * sizeof (struct host_struct));
		if (hosts == NULL) {
			it_loging("libIT.a(%s): get_chkserv() hosts rerealloc error\n", S2O_DAEMON);
			fclose(fd);
  			return(-1);
		}

	    strcpy (hosts[host_num].name, hostname);
	    strcpy (hosts[host_num].ip, hostip);
	   	strcpy(hosts[host_num].type, type);
		strcpy(hosts[host_num].company, companycode);
		strcpy(hosts[host_num].ELevel, ELevel);
	    hosts[host_num].timeout = timeout;
	    hosts[host_num].attempt = attempt;
		strcpy(hosts[host_num].notchkfrom, notchkfrom);
		strcpy(hosts[host_num].notchkto, notchkto);
		strcpy(hosts[host_num].notchksyslog, notchksyslog);
		strcpy(hosts[host_num].chkCrFile, chkCrFile);
		strcpy(hosts[host_num].chkTimeSync, chkTimeSync);
		if (strlen(gapTimeSync) > 0 && atoi(gapTimeSync) > 0) strcpy(hosts[host_num].gapTimeSync, gapTimeSync);
		else strcpy(hosts[host_num].gapTimeSync, "1");
	    hosts[host_num].name[strlen(hostname)] = '\0';
	    hosts[host_num].ip[strlen(hostip)] = '\0';
	    hosts[host_num].type[strlen(type)] = '\0';
		hosts[host_num].company[strlen(companycode)] = '\0';
		hosts[host_num].ELevel[strlen(ELevel)] = '\0';
		hosts[host_num].notchkfrom[strlen(notchkfrom)] = '\0';
		hosts[host_num].notchkto[strlen(notchkto)] = '\0';
		hosts[host_num].notchkperf[strlen(notchkperf)] = '\0';
		hosts[host_num].notchksyslog[strlen(notchksyslog)] = '\0';
		hosts[host_num].chkCrFile[strlen(chkCrFile)] = '\0';
		hosts[host_num].icontinue = 0;
		hosts[host_num].connport_time = 0;
		hosts[host_num].evt_lvl_mincnt = evt_lvl_mincnt;
		hosts[host_num].evt_lvl_skipcnt = 0;
	    hosts[host_num].num_err = 0;
	    hosts[host_num].wlog_sys01 = 0;
	    hosts[host_num].wlog_sys03 = 0;

		if (strlen(hosts[host_num].company) < 2) 
			strcpy (hosts[host_num].company, it_company);
		host_num++;
    }
	fclose(fd);

  	return(host_num);
}

