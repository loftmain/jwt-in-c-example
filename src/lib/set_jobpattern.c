/*
   $Id: set_jobpattern.c,v 1.7 2003/11/12 srp Exp $

   Copyright (c) 2000, 2001, 2002, 2003
             i-TOP System Inc.  All rights reserved.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int getitem(int ch, char *src, char *dest, int seqitem);
extern int lltrim(char* sbuf);
extern int rtrim(char * sbuf);
extern char *strupr(char *string);

int set_jobpattern(char *cfgname)
{
	FILE 	*fd;
	char	jobname[128], msgcode[8];
	char 	patterns[10][129], options[10][10];
	char	mode[10], duration[10], max_count[10];
	char 	fline[2048]; 
	char	svcname[128];
	char	actioncmd[256];
	char	msgupper[5];
	int 	num = 0;
	int 	i;

	if ((fd = fopen (cfgname, "r")) == NULL) 
	{
		it_loging("libIT.a(%s): set_jobpattern() file open error\n", S2O_DAEMON);
		return(-1);
	}

	while (fgets(fline, 2047, fd) != NULL) 
	{
		if (fline[0] == '#' || isspace (fline[0]) || fline[0] == '\n') continue;

		if (fline[strlen(fline)-1] == '\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';
		if (fline[strlen(fline)-1] == '\n' || fline[strlen(fline)-1] == '\r') fline[strlen(fline)-1] = '\0';
		
  		/* reallocate array to hold the new entry */
		defJobPattern = (struct def_jobpattern *) realloc (defJobPattern, (num + 1) * sizeof (struct def_jobpattern));

		if (defJobPattern == NULL) 
		{
			it_loging("libIT.a(%s): set_jobpattern() struct realloc error.\n", S2O_DAEMON);
			fclose(fd);
  			return(-1);
		}
		memset(jobname, 0x00, sizeof jobname);
		for(i = 0; i < 10; i++){
			memset(patterns[i], 0x00, sizeof patterns[i]);
			memset(options[i], 0x00, sizeof options[i]);
		}
		memset(msgcode, 0x00, sizeof msgcode);
		memset(mode, 0x00, sizeof mode);
		memset(duration, 0x00, sizeof duration);
		memset(max_count, 0x00, sizeof max_count);
		memset(svcname, 0x00, sizeof svcname);
		memset(actioncmd, 0x00, sizeof actioncmd);
		memset(msgupper, 0x00, sizeof msgupper);

		getitem(';', fline, jobname, 1);
		getitem(';', fline, msgcode, 2);
		getitem(';', fline, patterns[0], 3);
		getitem(';', fline, mode, 4);
		getitem(';', fline, duration, 5);
		getitem(';', fline, max_count, 6);
		getitem(';', fline, patterns[1], 7);
		getitem(';', fline, options[1], 8);
		getitem(';', fline, patterns[5], 9);
		getitem(';', fline, options[5], 10);
		getitem(';', fline, svcname, 11);
		getitem(';', fline, patterns[2], 12);
		getitem(';', fline, options[2], 13);
		getitem(';', fline, patterns[3], 14);
		getitem(';', fline, options[3], 15);
		getitem(';', fline, patterns[4], 16);
		getitem(';', fline, options[4], 17);
		getitem(';', fline, patterns[6], 18);
		getitem(';', fline, options[6], 19);
		getitem(';', fline, patterns[7], 20);
		getitem(';', fline, options[7], 21);
		getitem(';', fline, patterns[8], 22);
		getitem(';', fline, options[8], 23);
		getitem(';', fline, patterns[9], 24);
		getitem(';', fline, options[9], 25);
		getitem(';', fline, actioncmd, 26);
		getitem(';', fline, msgupper, 27);

		for(i = 0; i < 10; i++) {
			lltrim(patterns[i]);
			lltrim(options[i]);
		}

		if (patterns[0][strlen(patterns[0])-1] == '\n') patterns[0][strlen(patterns[0])-1] = '\0';
		if (svcname[strlen(svcname)-1] == '\n') svcname[strlen(svcname)-1] = '\0';

		if(strlen(svcname) == 0) strcpy(svcname, jobname);

		strcpy(defJobPattern[num].jobname, jobname);
		strcpy(defJobPattern[num].msgcode, msgcode);

		if ( msgupper[0] == 'Y') strupr(patterns[0]);
	    strcpy(defJobPattern[num].patterns[0], patterns[0]);

		for(i = 1; i < 10; i++) {
			if ( msgupper[0] == 'Y') strupr(patterns[i]);
	    	strcpy(defJobPattern[num].patterns[i], patterns[i]);
	    	strcpy(defJobPattern[num].options[i], options[i]);
		}
	    strcpy(defJobPattern[num].svcname, svcname);

	    defJobPattern[num].mode = atoi(mode);
	    defJobPattern[num].duration = atoi(duration);
	    defJobPattern[num].max_count = atoi(max_count);
	    defJobPattern[num].lastevttime = 0;
		
		lltrim(actioncmd);
		rtrim(actioncmd);

	    strcpy(defJobPattern[num].actioncmd, actioncmd);
		strcpy(defJobPattern[num].msgupper, msgupper);

		defJobPattern[num].lastactiontime = 0;
	
      	num++;
    }
	fclose(fd);
  	return (num);
}

