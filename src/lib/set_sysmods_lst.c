/*
   $Id: set_sysmods_lst.c,v 1.7 2014/12/09 srp Exp $

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

int set_sysmods_lst(char* _SERVER, char* cfgname)
{
    char fline[512];
    char hostname[64], cocode[64];
	char from[32], to[32];
    FILE *fd;
    int i;
	struct stat stbuf1;

    int num = 0;

    /* hostname;co_code;from;to */

	if (stat(cfgname, &stbuf1) != 0) {
		return(-1);
	}

    if ((fd = fopen(cfgname, "r")) == NULL)
    {
        it_loging("libIT.a(%s): set_sysmods_lst() %s file open error\n", _SERVER, cfgname);
        return(-1);
    }
    while (fgets(fline, 511, fd) != NULL)
    {
        if (fline[0] == '#' || fline[0] == '\n') continue;

        if(fline[strlen(fline)-1] =='\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';
        if(fline[strlen(fline)-1] =='\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';

        memset(hostname, 0, sizeof hostname);
        memset(cocode, 0, sizeof cocode);
		memset(from, 0, sizeof from);
		memset(to, 0, sizeof to);

        getitem(';', fline, hostname, 1);
        getitem(';', fline, cocode, 2);
        getitem(';', fline, from, 3);
        getitem(';', fline, to, 4);

        if (strlen(hostname)> 49) hostname[49] = '\0';
        if (strlen(cocode) > 7)  cocode[7] = '\0';
        if (strlen(from) > 20)  from[20] = '\0';
        if (strlen(to) > 20)  to[20] = '\0';

        if (strlen(hostname) == 0 && strlen(cocode) == 0) continue;

        defsysmods_lst = (struct def_sysmods_lst *) realloc(defsysmods_lst, (num+1) * sizeof (struct def_sysmods_lst));
        if(defsysmods_lst == NULL) {
            it_loging("libIT.a(%s): set_sysmods_lst() realloc error.\n", _SERVER);
            fclose(fd);
            return(-1);
        }
        strcpy(defsysmods_lst[num].hostname, hostname);
        strcpy(defsysmods_lst[num].cocode, cocode);
        strcpy(defsysmods_lst[num].from, from);
        strcpy(defsysmods_lst[num].to, to);
        num++;
    }
    fclose(fd);
    for (i = 0; i < num; i++) {
        it_loging("libIT.a(%s): set_sysmods_lst() sysmods_lst : %s,%s,%s,%s;\n", _SERVER, defsysmods_lst[i].hostname, defsysmods_lst[i].cocode,
				defsysmods_lst[i].from,defsysmods_lst[i].to);
    }
    return num;
}
