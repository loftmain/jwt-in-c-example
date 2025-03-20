/*
   $Id: set_allow_host.c,v 1.0 2015/08/18 srp Exp $

   Copyright (c) 2015
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

int set_allow_host(char* _SERVER, char* cfgname)
{
    FILE *fd;
    char fline[512];
    char name[100], cocode[100];
	struct stat stbuf1;	
    int num = 0;
    int i;

    /* hostname;co_code;hw_type;is_reg; */

 	if (stat(cfgname, &stbuf1) != 0) {
		return(-1);
	}

    if ((fd = fopen(cfgname, "r")) == NULL)
    {
        it_loging("libIT.a(%s): set_allow_host() %s file open error\n", _SERVER, cfgname);
        return(-1);
    }
    while (fgets(fline, 511, fd) != NULL)
    {
        if (fline[0] == '#' || fline[0] == '\n') continue;

        if(fline[strlen(fline)-1] =='\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';
        if(fline[strlen(fline)-1] =='\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';

        memset(name, 0, sizeof name);
        memset(cocode, 0, sizeof cocode);

        getitem(';', fline, name, 1);
        getitem(';', fline, cocode, 2);

        if (strlen(name)> 49) name[49] = '\0';
        if (strlen(cocode) > 7)  cocode[7] = '\0';
        if (strlen(name) == 0 || strlen(cocode) == 0) continue;

        defallow_host = (struct def_allow_host *) realloc(defallow_host, (num+1) * sizeof (struct def_allow_host));
        if(defallow_host == NULL) {
            it_loging("libIT.a(%s): set_allow_host() realloc error.\n", _SERVER);
            fclose(fd);
            return(-1);
        }
        strcpy(defallow_host[num].name, name);
        strcpy(defallow_host[num].cocode, cocode);
		defallow_host[num].inew = 0;
        num++;
    }
    fclose(fd);
    for (i = 0; i < num; i++) {
        it_loging("libIT.a(%s): set_allow_host() allow_host : %s,%s\n", _SERVER, defallow_host[i].name, defallow_host[i].cocode);
    }

    return num;
}
