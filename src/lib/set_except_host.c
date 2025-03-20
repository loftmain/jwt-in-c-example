/*
   $Id: set_except_host.c,v 1.7 2014/12/09 srp Exp $

   Copyright (c) 2014
             NEWSYSTECH Inc.  All rights reserved.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int getitem(int ch, char *src, char *dest, int seqitem);

int set_except_host(char* _SERVER, char* cfgname)
{
    char except_cfg[256];
    char fline[1024];
    char name[100], cocode[100];
    char perf_yn[100], svr_dn_msg_yn[100], svr_msg_yn[100];
	/* char reason[256]; */
	char tm_from[20], tm_to[20];
    FILE *fd;
    int i;
	struct stat stbuf1;	

    int num = 0;

    /*
    hostname;co_code;performance(Y/N);server down message(Y/N);server message(Y/N);
    */

 	if (stat(cfgname, &stbuf1) != 0) {
		return(-1);
	}

    if ((fd = fopen(cfgname, "r")) == NULL)
    {
		if (!strcmp(_SERVER, "IT.mond")) 
        	it_loging_f("mond", "libIT.a(%s): set_except_host() %s file open error\n", _SERVER, cfgname);
		else
        	it_loging("libIT.a(%s): set_except_host() %s file open error\n", _SERVER, cfgname);
        return(-1);
    }
    while (fgets(fline, 1023, fd) != NULL)
    {
        if (fline[0] == '#' || fline[0] == '\n') continue;

        if(fline[strlen(fline)-1] =='\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';
        if(fline[strlen(fline)-1] =='\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';

        memset(name, 0, sizeof name);
        memset(cocode, 0, sizeof cocode);
        memset(perf_yn, 0, sizeof perf_yn);
        memset(svr_dn_msg_yn, 0, sizeof svr_dn_msg_yn);
        memset(svr_msg_yn, 0, sizeof svr_msg_yn);
		/*memset(reason, 0, sizeof reason);*/
		memset(tm_from, 0, sizeof tm_from);
		memset(tm_to, 0, sizeof tm_to);

        getitem(';', fline, name, 1);
        getitem(';', fline, cocode, 2);
        getitem(';', fline, perf_yn, 3);
        getitem(';', fline, svr_dn_msg_yn, 4);
        getitem(';', fline, svr_msg_yn, 5);
        /*getitem(';', fline, reason, 6);*/
        getitem(';', fline, tm_from, 7);
        getitem(';', fline, tm_to, 8);

        if (strlen(name)> 60) name[60] = '\0';
        if (strlen(cocode) > 7)  cocode[7] = '\0';

        if (strlen(name) == 0 && strlen(cocode) == 0) continue;

        if (strlen(perf_yn) > 5)  perf_yn[6] = '\0';
        if (strlen(svr_dn_msg_yn) > 5)  svr_dn_msg_yn[6] = '\0';
        if (strlen(svr_msg_yn) > 5)  svr_msg_yn[6] = '\0';

        defexcept_host = (struct def_except_host *) realloc(defexcept_host, (num+1) * sizeof (struct def_except_host));
        if(defexcept_host == NULL) {
			if (!strcmp(_SERVER, "IT.mond")) 
            	it_loging_f("mond", "libIT.a(%s): set_except_host() realloc error.\n", _SERVER);
			else
            	it_loging("libIT.a(%s): set_except_host() realloc error.\n", _SERVER);
            fclose(fd);
            return(-1);
        }
        strcpy(defexcept_host[num].name, name);
        strcpy(defexcept_host[num].cocode, cocode);
        strcpy(defexcept_host[num].perf_yn, perf_yn);
        strcpy(defexcept_host[num].svr_dn_msg_yn, svr_dn_msg_yn);
        strcpy(defexcept_host[num].svr_msg_yn, svr_msg_yn);
        strcpy(defexcept_host[num].tm_from, tm_from);
        strcpy(defexcept_host[num].tm_to, tm_to);
        num++;
    }
    fclose(fd);
    for (i = 0; i < num; i++) {
		if (!strcmp(_SERVER, "IT.mond")) 
        it_loging_f("mond", "libIT.a(%s): set_except_host() except_host : %s,%s,%s,%s,%s,%s,%s,\n", _SERVER, defexcept_host[i].name, defexcept_host[i].cocode,
				defexcept_host[i].perf_yn,defexcept_host[i].svr_dn_msg_yn, defexcept_host[i].svr_msg_yn, defexcept_host[i].tm_from, defexcept_host[i].tm_to);
        it_loging("libIT.a(%s): set_except_host() except_host : %s,%s,%s,%s,%s,%s,%s,\n", _SERVER, defexcept_host[i].name, defexcept_host[i].cocode,
				defexcept_host[i].perf_yn,defexcept_host[i].svr_dn_msg_yn, defexcept_host[i].svr_msg_yn, defexcept_host[i].tm_from, defexcept_host[i].tm_to);
    }

    return num;
}
