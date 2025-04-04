/*
   $Id: set_sysmods.c,v 1.7 2003/10/21 srp Exp $
  	Copyright (c) 2000, 2001, 2002, 2003
   	NEWSYSTECH Inc.  All rights reserved.

*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int getitem(int ch, char *src, char *dest, int seqitem);

int set_sysmods(char *cfgname)
{
  	FILE 	*fd;

    char    week[][5] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  	char 	fline[512];
	char 	sysmodsName[256], cycle[10];
	char	ftime[6], ttime[6],	fweek[3], fday[3], fyear[5], fmonth[3], tweek[3], tday[3], tyear[5], tmonth[3];	
	char    fromTime[32], toTime[32], tmp[5];
  	int 	sysmods_num = 0, i;

  	if ((fd = fopen (cfgname, "r")) == NULL)
	{
      	it_loging("libIT.a(%s): set_sysmonds() file(%s) open error.\n", S2O_DAEMON, cfgname);
      	return (-1);
    }

  	while (fgets(fline, 512, fd) != NULL)
	{
      	/* perl-style comments */
      	if (fline[0] == '#' || isspace (fline[0]) || fline[0] == '\n')
			continue;
		if ( fline[strlen(fline)-1] == '\n') fline[strlen(fline)-1] = '\0';
		
		memset(cycle, 0x00, sizeof cycle);
		memset(fromTime, 0x00, sizeof fromTime);
		memset(toTime, 0x00, sizeof toTime);
	    memset(sysmodsName, 0x00, sizeof sysmodsName);

		memset(ftime, 0x00, sizeof ftime);
		memset(fweek, 0x00, sizeof fweek);
		memset(fday, 0x00, sizeof fday);
		memset(fmonth, 0x00, sizeof fmonth);
		memset(fyear, 0x00, sizeof fyear);

		memset(ttime, 0x00, sizeof ttime);
		memset(tday, 0x00, sizeof tday);
		memset(tweek, 0x00, sizeof tweek);
		memset(tmonth, 0x00, sizeof tmonth);
		memset(tyear, 0x00, sizeof tyear);

		getitem(';', fline, cycle, 1);
		getitem(';', fline, fromTime, 2);
		getitem(';', fline, toTime, 3);
		getitem(';', fline, sysmodsName, 4);


		if (strcmp(cycle, "Daily") == 0)
		{
			strcpy(ftime, fromTime);
			strcpy(ttime, toTime);
		}
		else if (strcmp(cycle, "Weekly") == 0)
		{
			memset(tmp, 0x00, sizeof tmp);		
		    getitem('-', fromTime, tmp, 1);
			getitem('-', fromTime, ftime, 2);
			for (i = 0; i < 7; i++)
				if (strcmp(tmp, week[i]) == 0)
					break;
			sprintf(fweek, "%02d", i);
			memset(tmp, 0x00, sizeof tmp);
			getitem('-', toTime, tmp, 1);
			getitem('-', toTime, ttime, 2);
			for ( i = 0; i < 7; i++)
				if (strcmp(tmp, week[i]) == 0)
					break;
			sprintf(tweek, "%02d", i);
		}
		else if (strcmp(cycle, "Monthly") == 0)
		{
			getitem('-', fromTime, fday, 1);
			getitem('-', fromTime, ftime, 2);
			getitem('-', toTime, tday, 1);
			getitem('-', toTime, ttime, 2);
		}
		else if(strcmp(cycle, "None") == 0)
		{
			getitem('-', fromTime, fyear, 1);
			getitem('-', fromTime, fmonth, 2);
			getitem('-', fromTime, fday, 3);
			getitem('-', fromTime, ftime,4);
			getitem('-', toTime, tyear, 1);
			getitem('-', toTime, tmonth, 2);
			getitem('-', toTime, tday, 3);
			getitem('-', toTime, ttime,4);
		}
		else if (strcmp(cycle, "WeekMonth") == 0)
		{
			memset(tmp, 0x00, sizeof tmp);
		    getitem('-', fromTime, tmp, 1);
			if ( !strcmp(tmp, "1st")) sprintf(fday, "1");
			else if ( !strcmp(tmp, "2nd")) sprintf(fday, "2");
			else if ( !strcmp(tmp, "3rd")) sprintf(fday, "3");
			else if ( !strcmp(tmp, "4th")) sprintf(fday, "4");
			else sprintf(fday, "9");
			memset(tmp, 0x00, sizeof tmp);
		    getitem('-', fromTime, tmp, 2);
			for (i = 0; i < 7; i++)
				if (strcmp(tmp, week[i]) == 0)
					break;
			sprintf(fweek, "%02d", i);
			getitem('-', fromTime, ftime, 3);


			memset(tmp, 0x00, sizeof tmp);
			getitem('-', toTime, tmp, 1);
			if ( !strcmp(tmp, "1st")) sprintf(tday, "1");
			else if ( !strcmp(tmp, "2nd")) sprintf(tday, "2");
			else if ( !strcmp(tmp, "3rd")) sprintf(tday, "3");
			else if ( !strcmp(tmp, "4th")) sprintf(tday, "4");
			else sprintf(tday, "9");
			memset(tmp, 0x00, sizeof tmp);
			getitem('-', toTime, tmp, 2);
			for ( i = 0; i < 7; i++)
				if (strcmp(tmp, week[i]) == 0)
					break;
			sprintf(tweek, "%02d", i);
			getitem('-', toTime, ttime, 3);

			if ( atoi(fday) > 4 || atoi(fweek) > 6 || atoi(tday) > 4 || atoi(tweek) > 6) {
				it_loging("libIT.a(%s): set_sysmods() Invalid format. (%s)\n", S2O_DAEMON, fline);
				continue;
			}

		} else {
			it_loging("libIT.a(%s): set_sysmods() Invalid format. (%s)\n", S2O_DAEMON, fline);
			continue;
		}

		if ( strlen(ftime) != 5 || strlen(ttime) != 5) {
			it_loging("libIT.a(%s): set_sysmods() Invalid format. (%s)\n", S2O_DAEMON, fline);
			continue;
		}

  		/* reallocate array to hold the new entry */
		defSysmods = (struct def_sysmods *) realloc (defSysmods, (sysmods_num + 1) * sizeof (struct def_sysmods));

		if (defSysmods == NULL)
		{
			it_loging("libIT.a(%s): set_sysmods() defSysmods struct realloc error.\n", S2O_DAEMON);
			fclose(fd);
  			return(-1);
		}

	    strcpy(defSysmods[sysmods_num].sysmodsName, sysmodsName); 
		strcpy(defSysmods[sysmods_num].cycle, cycle);

	    /*strcpy(defSysmods[sysmods_num].ftime, ftime);*/

		strcpy(defSysmods[sysmods_num].fweek, fweek);
		strcpy(defSysmods[sysmods_num].fday, fday);
		strcpy(defSysmods[sysmods_num].fmonth, fmonth);
		strcpy(defSysmods[sysmods_num].fyear, fyear);

		defSysmods[sysmods_num].ftime[0] = ftime[0];
		defSysmods[sysmods_num].ftime[1] = ftime[1];
		defSysmods[sysmods_num].ftime[2] = ftime[3];
		defSysmods[sysmods_num].ftime[3] = ftime[4];

		defSysmods[sysmods_num].fhour[0] = ftime[0];
		defSysmods[sysmods_num].fhour[1] = ftime[1];
		defSysmods[sysmods_num].fhour[2] = '\0';

		defSysmods[sysmods_num].fmin[0] = ftime[3];
		defSysmods[sysmods_num].fmin[1] = ftime[4];
		defSysmods[sysmods_num].fmin[2] = '\0';

	    /*strcpy(defSysmods[sysmods_num].ttime, ttime);*/
		strcpy(defSysmods[sysmods_num].tweek, tweek);
		strcpy(defSysmods[sysmods_num].tday, tday);
		strcpy(defSysmods[sysmods_num].tmonth, tmonth);
		strcpy(defSysmods[sysmods_num].tyear, tyear);

		defSysmods[sysmods_num].ttime[0] = ttime[0];
		defSysmods[sysmods_num].ttime[1] = ttime[1];
		defSysmods[sysmods_num].ttime[2] = ttime[3];
		defSysmods[sysmods_num].ttime[3] = ttime[4];

		defSysmods[sysmods_num].thour[0] = ttime[0];
		defSysmods[sysmods_num].thour[1] = ttime[1];
		defSysmods[sysmods_num].thour[2] = '\0';

		defSysmods[sysmods_num].tmin[0] = ttime[3];
		defSysmods[sysmods_num].tmin[1] = ttime[4];
		defSysmods[sysmods_num].tmin[2] = '\0';

      	sysmods_num++;
    }
	fclose(fd);
  	return (sysmods_num);
}

