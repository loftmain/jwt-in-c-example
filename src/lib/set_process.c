/*
   $Id: set_process.c,v 1.7 2003/06/30 srp Exp $

   Copyright (c) 2000, 2001, 2002, 2003
             i-TOP System Inc.  All rights reserved.

   2003-06-30
     * process run count �׸��߰�.
*/
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int getitem(int ch, char *src, char *dest, int seqitem);
extern int rtrim(char* sbuf);

int set_process(char *cfgname)
{
  	FILE 	*fd;

  	char 	fline[1024]; 
	char 	processName[512], msgid[8], msgid_run[8], ftime[5], ttime[5], minRunCount[5], maxRunCount[5];
	char	processPattern[256], processDisplay[512];
	char	autorestart[2], autocmd[256], autoaction[2], actioncmd[256];
	char	cluster[5], clustername[64], alias[128], owner[64], o_count[10];
	char	pid_bracket[5];
	char	ha_yn[128];
  	int 	proc_num = 0, i, k;
	char 	buf[128];
	/*time_t	tmTmp = time(0);*/

  	if ((fd = fopen (cfgname, "r")) == NULL) {
      	it_loging("libIT.a(%s): set_process() file open error.\n", S2O_DAEMON);
      	return (-1);
    }

  	/* read lines off of the file until EOF */
  	while (fgets(fline, 1023, fd) != NULL) {
      	/* perl-style comments */
      	if (fline[0] == '#' || isspace (fline[0]) || fline[0] == '\n')
			continue;

		memset(processName, 0x00, sizeof processName);
		memset(processPattern, 0x00, sizeof processPattern);
		memset(processDisplay, 0x00, sizeof processDisplay);
		memset(msgid, 0x00, sizeof msgid);
		memset(msgid_run, 0x00, sizeof msgid_run);
		memset(ftime, 0x00, sizeof ftime);
		memset(ttime, 0x00, sizeof ttime);
		memset(autorestart, 0x00, sizeof autorestart);
		memset(autocmd, 0x00, sizeof autocmd);
		memset(autoaction, 0x00, sizeof autoaction);
		memset(actioncmd, 0x00, sizeof actioncmd);
		memset(minRunCount, 0x00, sizeof minRunCount);
		memset(maxRunCount, 0x00, sizeof maxRunCount);
		memset(cluster, 0x00, sizeof cluster);
		memset(clustername, 0x00, sizeof clustername);
		strcpy(minRunCount, "1");
		/*strcpy(maxRunCount, "0"); */
		memset(alias, 0x00, sizeof alias);
		memset(owner, 0x00, sizeof owner);
		memset(o_count, 0x00, sizeof o_count);
		memset(ha_yn, 0x00, sizeof ha_yn);
		memset(pid_bracket, 0x00, sizeof pid_bracket);

		getitem(';', fline, processName, 1);
		getitem(';', fline, msgid, 2);
		getitem(';', fline, ftime, 3);
		getitem(';', fline, ttime, 4);
		getitem(';', fline, minRunCount, 5);
		getitem(';', fline, autorestart, 6);
		getitem(';', fline, autocmd, 7);
		getitem(';', fline, maxRunCount, 8);
		getitem(';', fline, autoaction, 9);
		getitem(';', fline, actioncmd, 10);
		getitem(';', fline, cluster, 11);
		getitem(';', fline, clustername, 12);
		getitem(';', fline, alias, 13);
		getitem(';', fline, owner, 14);
		getitem(';', fline, o_count, 15);
		getitem(';', fline, ha_yn, 16);
		getitem(';', fline, processPattern, 17);
		getitem(';', fline, pid_bracket, 18);

  		/* reallocate array to hold the new entry */
		dProcess = (struct define_process *) realloc (dProcess, (proc_num + 1) * sizeof (struct define_process));

		if (dProcess == NULL) {
			it_loging("libIT.a(%s): set_process() struct realloc error.\n", S2O_DAEMON);
			fclose(fd);
  			return(-1);
		}

		if (strlen(msgid) == 7) {
			strcpy(msgid_run, msgid);
			if (msgid[0] == 'F') msgid_run[0] = 'C';
		} else {
			memset(msgid, 0, sizeof msgid);
		}
	
		rtrim(processName);
	    strcpy (dProcess[proc_num].processName, processName);
	    strcpy (dProcess[proc_num].msgid, msgid);
	    strcpy (dProcess[proc_num].msgid_run, msgid_run);
	    strcpy (dProcess[proc_num].ftime, ftime);
	    strcpy (dProcess[proc_num].ttime, ttime);
	    strcpy (dProcess[proc_num].processPattern, processPattern);

		if ( strlen(processPattern) > 0)
			sprintf(processDisplay, "%s ... %s", processName, processPattern);
		else
			sprintf(processDisplay, "%s", processName);
	    strcpy (dProcess[proc_num].processDisplay, processDisplay);

		memset(buf, 0, sizeof buf);
		sscanf(minRunCount, "%s", buf);

		if ( strlen(buf) == 0) {
			dProcess[proc_num].minRunCount = 1;
		} else if ( !strcmp(buf, "0")) {
			dProcess[proc_num].minRunCount = 0;
		} else {
	    	dProcess[proc_num].minRunCount = atoi(minRunCount);
			if ( dProcess[proc_num].minRunCount == 0) dProcess[proc_num].minRunCount = 1;
		}

		/*dProcess[proc_num].maxRunCount = atoi(maxRunCount);*/

		memset(buf, 0, sizeof buf);
		sscanf(maxRunCount, "%s", buf);

		if ( strlen(buf) == 0) {
			dProcess[proc_num].maxRunCount = -1;
		} else if ( !strcmp(buf, "0")) {
			dProcess[proc_num].maxRunCount = 0;
		} else {
	    	dProcess[proc_num].maxRunCount = atoi(buf);
			if ( dProcess[proc_num].maxRunCount == 0) dProcess[proc_num].maxRunCount = -1;
		}

	    strcpy (dProcess[proc_num].autorestart, autorestart);
	    strcpy (dProcess[proc_num].autocmd, autocmd);
		strcpy (dProcess[proc_num].autoaction, autoaction);
		strcpy (dProcess[proc_num].actioncmd, actioncmd);
		strcpy (dProcess[proc_num].cluster, cluster);
		strcpy (dProcess[proc_num].clustername, clustername);
		strcpy (dProcess[proc_num].alias, alias);
		strcpy (dProcess[proc_num].owner, owner);
	    strcpy (dProcess[proc_num].pid_bracket, pid_bracket);

		dProcess[proc_num].o_count = atoi(o_count);
	    dProcess[proc_num].num_err = 0;
	    dProcess[proc_num].err_down = 0;
	    dProcess[proc_num].err_run = 0;
	    dProcess[proc_num].cluster_active = 0;
	    dProcess[proc_num].cluster_failtime = 0;
	    dProcess[proc_num].downflag = 0;
	    dProcess[proc_num].downdumptm = 0;
		dProcess[proc_num].pid = -1;
	    /*dProcess[proc_num].downdumptm = tmTmp - 9*60;*/

		if( dProcess[proc_num].o_count < 1) dProcess[proc_num].o_count = 1;

		sscanf(ha_yn, "%s", dProcess[proc_num].ha_yn);

	    dProcess[proc_num].processName[strlen(processName)] = '\0';
	    dProcess[proc_num].processPattern[strlen(processPattern)] = '\0';
	    dProcess[proc_num].processDisplay[strlen(processDisplay)] = '\0';
	    dProcess[proc_num].msgid[strlen(msgid)] = '\0';
	    dProcess[proc_num].ftime[strlen(ftime)] = '\0';
	    dProcess[proc_num].ttime[strlen(ttime)] = '\0';
	    dProcess[proc_num].autorestart[strlen(autorestart)] = '\0';
	    dProcess[proc_num].autocmd[strlen(autocmd)] = '\0';
		dProcess[proc_num].autoaction[strlen(autoaction)] = '\0';
		dProcess[proc_num].actioncmd[strlen(actioncmd)] = '\0';
		dProcess[proc_num].cluster[strlen(cluster)] = '\0';
		dProcess[proc_num].clustername[strlen(clustername)] = '\0';
		dProcess[proc_num].alias[strlen(alias)] = '\0';
		dProcess[proc_num].owner[strlen(owner)] = '\0';
		dProcess[proc_num].ha_yn[strlen(ha_yn)] = '\0';
		dProcess[proc_num].pid_bracket[strlen(pid_bracket)] = '\0';

      	proc_num++;
    }
	fclose(fd);
  	return (proc_num);
}
