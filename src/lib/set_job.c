/*
   $Id: set_job.c,v 1.7 2003/10/21 srp Exp $

   Copyright (c) 2000, 2001, 2002, 2003
             i-TOP System Inc.  All rights reserved.

*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "../IT.extern.h"
#include "config.h"

extern int it_loging(char *format,...);
extern int changedate(char *fname, char* fname_org, int *position);
extern int getitem(int ch, char *src, char *dest, int seqitem);
extern int changedate_new(char *fname, char *fname_org);

int set_job(char *cfgname)
{
  	FILE 	*fd;

    char    week[][5] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  	char 	fline[256], line1[256]; 
	char 	jobName[128], cycle[10];
	char	ftime[6], ttime[6],	fweek[3], fday[3], tweek[3], tday[3], chktime[6];
	char	logPath[256], logPath_org[256];
	char	msgcode[8], ELevel[2];
	char    fromTime[16], toTime[16], tmp[5];
  	int 	job_num = 0, i, j, position;
	int 	chgmode;
	char	*ptr;

  	if ((fd = fopen (cfgname, "r")) == NULL) {
      	it_loging("libIT.a(%s): set_job() file open error.\n", S2O_DAEMON);
      	return (-1);
    }

  	while (fgets(fline, 256, fd) != NULL) {
      	/* perl-style comments */
      	if (fline[0] == '#' || isspace (fline[0]) || fline[0] =='\n')
			continue;

		memset(line1, 0x00, sizeof line1);
	    memset(jobName, 0x00, sizeof jobName);
		memset(cycle, 0x00, sizeof cycle);
		memset(fromTime, 0x00, sizeof fromTime);
		memset(toTime, 0x00, sizeof toTime);
		memset(logPath, 0x00, sizeof logPath);
		memset(logPath_org, 0x00, sizeof logPath_org);
		memset(chktime, 0x00, sizeof chktime);
		memset(ELevel, 0x00, sizeof ELevel);

		getitem(';', fline, line1, 1);
		getitem(';', fline, ELevel, 2);

		sscanf(line1, "%s %s %s %s %s %s %s", jobName, cycle, fromTime, toTime, chktime, msgcode, logPath);

		strcpy(logPath_org, logPath);

		position = -1;
		chgmode = 0; 
		chgmode = changedate(logPath, logPath_org, &position);

		memset(ftime, 0x00, sizeof ftime);
		memset(ttime, 0x00, sizeof ttime);
		memset(fday, 0x00, sizeof fday);
		memset(tday, 0x00, sizeof tday);
		memset(tweek, 0x00, sizeof tweek);
		memset(fweek, 0x00, sizeof fweek);
		memset(tmp,0x00,sizeof tmp);

		if (strcmp(cycle, "Day") == 0) 
		{
			strcpy(ftime, fromTime);
			strcpy(ttime, toTime);
		} 
		else if (strcmp(cycle, "Week") == 0)
		{
		    getitem('-', fromTime, tmp, 1);
			getitem('-', fromTime, ftime, 2);
			for (i = 0; i < 7; i++)
				if (strcmp(tmp, week[i]) == 0)
					break;

			sprintf(fweek, "%-2.2d", i);
			memset(tmp, 0x00, sizeof tmp);
			getitem('-', toTime, tmp, 1);
			getitem('-', toTime, ttime, 2);
			for ( i = 0; i < 7; i++)
				if (strcmp(tmp, week[i]) == 0)
					break;
			sprintf(tweek, "%-2.2d", i);
		}
		else if (strcmp(cycle, "Month") == 0)
		{
			getitem('-', fromTime, fday, 1);
			getitem('-', fromTime, ftime, 2);
			getitem('-', toTime, tday, 1);
			getitem('-', toTime, ttime, 2);
		}
  		/* reallocate array to hold the new entry */
		defJob = (struct def_job *) realloc (defJob, (job_num + 1) * sizeof (struct def_job));

		if (defJob == NULL) {
			it_loging("libIT.a(%s): set_Job() struct realloc error.\n", S2O_DAEMON);
			fclose(fd);
  			return(-1);
		} 

	    strcpy(defJob[job_num].jobName, jobName); 
		strcpy(defJob[job_num].cycle, cycle);
	    strcpy(defJob[job_num].ftime, ftime);
	    strcpy(defJob[job_num].ttime, ttime);
		strcpy(defJob[job_num].fweek, fweek);
		strcpy(defJob[job_num].tweek, tweek);
		strcpy(defJob[job_num].fday, fday);
		strcpy(defJob[job_num].tday, tday);
		strcpy(defJob[job_num].msgcode, msgcode);
	    strcpy(defJob[job_num].logPath, logPath);
	    strcpy(defJob[job_num].logPath_org, logPath_org);

		if (strcmp(ELevel, "F")) strcpy(ELevel, "C");

		strcpy(defJob[job_num].ELevel, ELevel);

		defJob[job_num].position = 0;
		defJob[job_num].chgmode = chgmode;
		defJob[job_num].nlogPath = position;
		defJob[job_num].nftime = atoi(chktime);
		defJob[job_num].openerr = 0;
		memset(fline, 0, sizeof fline);
      	job_num++;
    }
	fclose(fd);
	
  	return (job_num);
}


int set_log(char *cfgname)
{
  	FILE 	*fd;
  	char 	fline[256], line1[256];
	char 	logName[128];
	char	logPath[256], logPath_org[256];
	char	msgcode[8], ELevel[5];
  	int 	log_num = 0, i, j, position, chgmode;
	int		position_time = -1;
	char	*ptr;
	int		chgmode_new;
	int		chgmode_time;
	char	monfrom[32], monto[32];
	char	monweek[32];
	char	filecheck1[32], filecheck2[32];
	char	allevent_yn[5];
	char	newlogcheck[5];
	char	newlogdelaytime[10];
	char	newlogcheckaction[512];
	char	isfileitv[32];
	char	tmphost[100];

  	if ((fd = fopen (cfgname, "r")) == NULL) {
      	it_loging("libIT.a(%s): set_log() file open error.\n", S2O_DAEMON);
      	return (-1);
    }

  	while (fgets(fline, 255, fd) != NULL) {
      	/* perl-style comments */
      	if (fline[0] == '#' || isspace (fline[0]) || fline[0] == '\n') continue;

		if (fline[strlen(fline)-1] == '\n') fline[strlen(fline)-1] = '\0';

		memset(line1, 0x00, sizeof line1);
	    memset(logName, 0x00, sizeof logName);
		memset(logPath, 0x00, sizeof logPath);
		memset(msgcode, 0x00, sizeof msgcode);
		memset(ELevel, 0x00, sizeof ELevel);

		memset(monfrom, 0, sizeof monfrom);
		memset(monto, 0, sizeof monto);
		memset(monweek, 0, sizeof monweek);
		memset(filecheck1, 0, sizeof filecheck1);
		memset(filecheck2, 0, sizeof filecheck2);
		memset(allevent_yn, 0, sizeof allevent_yn);
		memset(logPath_org, 0, sizeof logPath_org);

		memset(newlogcheck, 0, sizeof newlogcheck);
		memset(newlogdelaytime, 0, sizeof newlogdelaytime);
		memset(newlogcheckaction, 0, sizeof newlogcheckaction);
		memset(isfileitv, 0, sizeof isfileitv);

		getitem(';', fline, line1, 1);
		getitem(';', fline, ELevel, 2);
		getitem(';', fline, monfrom, 3); /* from */
		getitem(';', fline, monto, 4); /* to */
		getitem(';', fline, monweek, 5); 
		getitem(';', fline, filecheck1, 6); /* ���� ���� ���� üũ �ð���(hh24) */
		getitem(';', fline, filecheck2, 7); /* ���� ���� ���� üũ �ð�(hh24) */
		getitem(';', fline, allevent_yn, 8); /* �ű� ��� �߻��� ������ �̺�Ʈ �߻� */
		
		/* 2015-10-21 */
		getitem(';', fline, newlogcheck, 9); /* �ű� �α����� ���� ���� Ȯ�ο��� */
		getitem(';', fline, newlogdelaytime, 10);  /* �ű� �α� �̻������� ���ֵǴ� �ð� */
		getitem(';', fline, newlogcheckaction, 11);  /* �ű� �α� �̻��� ����� action */
		getitem(';', fline, isfileitv, 12);  /* ���� ���� ���� interval */
		/* 2015-10-21 */

		if(strlen(monfrom) > 4) monfrom[4] ='\0';
		if(strlen(monto) > 4) monto[4] ='\0';
		if(strlen(monweek) > 7) monweek[7] ='\0';
		if(strlen(filecheck1) > 4) filecheck1[4] ='\0';
		if(strlen(filecheck2) > 4) filecheck2[4] ='\0';

        sscanf(line1, "%s %s %s", logName, msgcode, logPath);

		strcpy(logPath_org, logPath);

		position = -1;
		position_time = -1;

		chgmode_new = 0;
		chgmode_new = changedate_new(logPath, logPath_org);

		chgmode = 0;
		if (chgmode_new == 0) {
			chgmode = changedate(logPath, logPath_org, &position);
		}

  		/* reallocate array to hold the new entry */
		deflog = (struct def_log *) realloc (deflog, (log_num + 1) * sizeof (struct def_log));

		if (deflog == NULL) {
			fclose(fd);
			it_loging("libIT.a(%s): set_log() struct realloc error.\n", S2O_DAEMON);
  			return(-1);
		}

		chgmode_time = 0;
		if (chgmode_new == 0) {
			ptr = (char*) strstr(logPath, "hh.mi.ss");
			if (ptr != NULL) {
				chgmode_time = 1;
				position_time = ptr - logPath;
			} else {
				ptr = (char*) strstr(logPath, "hhmiss");
				if (ptr!=NULL) {
					chgmode_time = 2;
					position_time = ptr - logPath;
				} else {
					ptr = (char*) strstr(logPath, "hhmi");
					if (ptr!=NULL) {
						chgmode_time = 3;
						position_time = ptr - logPath;
					}
				}
			}
		}

	    strcpy(deflog[log_num].logName, logName); 
		strcpy(deflog[log_num].msgcode, msgcode);
	    strcpy(deflog[log_num].logPath, logPath);
	    strcpy(deflog[log_num].logPath_org, logPath_org);
		deflog[log_num].chgmode = chgmode;
		deflog[log_num].chgmode_new = chgmode_new;
		deflog[log_num].chgmode_time = chgmode_time;
		deflog[log_num].position = 0;
		deflog[log_num].isfile = -1;
		deflog[log_num].nlogPath = position;
		deflog[log_num].nlogPath_time = position_time;
		if(strcmp(ELevel, "F"))  strcpy(ELevel, "C");
		strcpy(deflog[log_num].ELevel, ELevel);
		strcpy(deflog[log_num].monfrom, monfrom);
		strcpy(deflog[log_num].monto, monto);
		strcpy(deflog[log_num].monweek, monweek);
		strcpy(deflog[log_num].filecheck1, filecheck1);
		strcpy(deflog[log_num].filecheck2, filecheck2);
		strcpy(deflog[log_num].allevent_yn, allevent_yn);
		strcpy(deflog[log_num].newlogcheck, newlogcheck);
		deflog[log_num].newlogdelaytime = atoi(newlogdelaytime);
		if ( deflog[log_num].newlogdelaytime < 1) deflog[log_num].newlogdelaytime = 30;
		strcpy(deflog[log_num].newlogcheckaction, newlogcheckaction);
		deflog[log_num].isfileitv = atoi(isfileitv);
		deflog[log_num].openerr = 0;
		deflog[log_num].newloglasttime = time(0);
		deflog[log_num].newlogchecktime = time(0);
		strcpy(deflog[log_num].newlogcheck_event, "N");
		strcpy(deflog[log_num].ispattern, "N");
		deflog[log_num].filelasttime = time(0);
		deflog[log_num].filechecktime = time(0);
		strcpy(deflog[log_num].filecheck_event, "N");
		strcpy(deflog[log_num].charset, "");	/* �Ѿ���Ƿ�� �ӽ� �߰� (2022/10/05) */

#if defined(LINUX)
		if ( (char *)strstr(logName, "UPS") != NULL || !strcmp(logPath, "/var/log/messages")) {
			memset(tmphost, 0, sizeof tmphost);
			if(gethostname(tmphost,sizeof(tmphost)) != 0){
				it_loging("libIT.a(%s): set_log() gethostname error!\n", S2O_DAEMON);	
			}
			if (!strcmp(tmphost, "sms-hyumc") || !strcmp(tmphost, "itops05")) {
				strcpy(deflog[log_num].charset, "UTF8");	/* �Ѿ���Ƿ�� �ӽ� �߰� (2022/10/05) */
			}
		}
#endif
      	log_num++;
		memset(fline, 0, sizeof fline);
    }
	fclose(fd);
  	return (log_num);
}
