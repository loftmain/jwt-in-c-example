/*
 * Copyright (c) 2000 - 2004 ITOP SYSTEM Inc. All rights reserved.
 *
 * NAME
 *      get_chkrouter.c - Agent router list get.
 *
 * MODIFIED     (MM/DD/YYYY)
 *  MyungKyun   01/08/2004 - Connect timeout 설정 기능 추가.
 *
 */
#include "config.h"
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <ctype.h>

#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int get_cfg(char* ENV, char* value);

int get_chkrouter(char *config_fname)
{
  	FILE 	*fd;

	char	tbuf[1024];
  	char 	fline[256];
	char 	hostname[64], hostip[32], type[7];
	char	companycode[10];
	char	it_company[10], ELevel[5];
  	int 	router_num = 0, i, k;
	int		timeout = 5;
	int		attempt = 1;
  	struct 	hostent *host = NULL;
	char	notchkfrom[10];
	char	notchkto[10];
	char	tmpbuf[128];
	int 	evt_lvl_mincnt = 0;

	memset(it_company, 0, sizeof it_company);
    if (get_cfg("IT_COMPANY_CODE", it_company) < 0) {
		it_loging("libIT.a(%s): get_chkrouter() parameter(IT_COMPANY_CODE) error!\n", S2O_DAEMON);
   	}
  	if ((fd = fopen(config_fname, "r")) == NULL) {
      	return (-1);
    }

  	/* read lines off of the file until EOF */
  	while (fgets(tbuf, 256, fd) != NULL) {
      	/* perl-style comments */
      	if (tbuf[0] == '#' || tbuf[0] == ';' || isspace (tbuf[0]) || tbuf[0] == '\n') /* ; 모니터링 제외로 추가 */
			continue;

		memset(fline, 0, sizeof fline);
		memset(notchkfrom, 0, sizeof notchkfrom);
		memset(notchkto, 0, sizeof notchkto);

		getitem('^', tbuf, fline, 1);
		getitem('^', tbuf, notchkfrom, 2);
		getitem('^', tbuf, notchkto, 3);

		memset(tmpbuf, 0, sizeof tmpbuf);
		getitem('^', tbuf, tmpbuf, 6);
		evt_lvl_mincnt = atoi(tmpbuf);
		if (evt_lvl_mincnt < 1) evt_lvl_mincnt = 1;
		else if ( evt_lvl_mincnt > 9) evt_lvl_mincnt = 9;

		memset(type, 0x00, sizeof type);	
		memset(hostip, 0x00, sizeof hostip);		/* No delete this line */
		memset(companycode, 0x00, sizeof companycode);
		memset(ELevel, 0x00, sizeof ELevel);
		memset(hostname, 0x00, sizeof hostname);
		attempt = 1;
		sscanf(fline, "%s %s %s %d %s %d %s", hostname, hostip, type, &timeout, companycode, &attempt, ELevel);

		if (!strcmp(hostname, "ServerCheckInt") || !strcmp(hostname, "RouterCheckInt") ||
		    !strcmp(hostname, "PacketSize") || !strcmp(hostname, "nPackets"))
			continue;

		if ((strcmp(type, "ROUTER") != 0 ) && (strcmp(type, "PING") !=0) && (strcmp(type, "DISK") !=0))		/* N/W 장비가 아닐 경우 */
			continue;

		if (strlen(hostip) < 8 ) {			/* 최소 Bytes 지정 */
	      	/* lookup the hostname */
	      	/* if the string is an IP addy, it will just put that there */
	      	if ((host = gethostbyname(hostname)) == NULL) {
		  		it_loging("libIT.a(%s): get_chkrouter() unable to resolve hostname %s\n", S2O_DAEMON, hostname);
				continue;
			}
		} else {
			if ((host = gethostbyname(hostip)) == NULL) {
		  		it_loging("libIT.a(%s): get_chkrouter() unable to resolve hostip %s\n", S2O_DAEMON, hostip);
				continue;
			}
		}

  		/* reallocate array to hold the new entry */
		routers = (struct router_struct *) realloc (routers, (router_num + 1) * sizeof (struct router_struct));
		if (routers == NULL) {
			it_loging("libIT.a(%s): get_chkrouter() routers rerealloc error\n", S2O_DAEMON);
			fclose(fd);
  			return(-1);
		}
		if (strcmp(ELevel, "F")) strcpy(ELevel, "C");

	    strcpy (routers[router_num].name, hostname);
	    strcpy (routers[router_num].ip, hostip);
	   	strcpy(routers[router_num].type, type);
		strcpy(routers[router_num].company, companycode);
		strcpy(routers[router_num].ELevel, ELevel);
		strcpy(routers[router_num].notchkfrom, notchkfrom);
		strcpy(routers[router_num].notchkto, notchkto);
	    routers[router_num].num_err = 0;
		routers[router_num].latency = 0;
	    routers[router_num].timeout = timeout;
	    routers[router_num].attempt = attempt;
	    routers[router_num].mon_daemon = 1;
	    routers[router_num].name[strlen(hostname)] = '\0';
	    routers[router_num].ip[strlen(hostip)] = '\0';
	    routers[router_num].type[strlen(type)] = '\0';
		routers[router_num].company[strlen(companycode)] = '\0';
		routers[router_num].ELevel[strlen(ELevel)] = '\0';
		if(strlen(routers[router_num].company)<2) strcpy(routers[router_num].company, it_company);
		routers[router_num].notchkfrom[strlen(notchkfrom)] = '\0';
		routers[router_num].notchkto[strlen(notchkto)] = '\0';
		routers[router_num].evt_lvl_mincnt= evt_lvl_mincnt;
		routers[router_num].evt_lvl_skipcnt= 0;
		router_num++;
	}
	fclose(fd);

  	return(router_num);
}
