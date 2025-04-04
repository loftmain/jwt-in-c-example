   /************************************************************************/
   /*  FILENAME     : changedate.c                                         */
   /*  DISCRIPTION  : string중 yyyymmdd,mmdd,yyyymmdd-1,mmdd-1             */
   /*  DATE         : 2008.10.23                                           */
   /*  WRITTEN      :                                                      */
   /************************************************************************/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../IT.extern.h"

int datechg(char *_fname, char *_fname_org, int position, int _type, int _back, int _yesterday);
int datechg_today(char *_fname, char *_fname_org, int position, int _type);
int datechg_today_yesterday(char *_fname, char *_fname_org, int position, int _type);
int datechg_yesterday(char *_fname, char *_fname_org, int position, int _type, int _back);
int datechg_yesterday_yesterday(char *_fname, char *_fname_org, int position, int _type);
int datechg_today_yesterday_back(char *_fname, char *_fname_org, int position, int _type);
int datechg_today_back(char *_fname, char *_fname_org, int position, int _type, int _back);

#define LOGTYPE_1	1	/* yyyymmdd */
#define LOGTYPE_2	2	/* yyyymmdd-1 */
#define LOGTYPE_3	3	/* ddmmyyyy */
#define LOGTYPE_4	4	/* mmddyyyy-1 */
#define LOGTYPE_5	5	/* mmddyyyy */
#define LOGTYPE_6	6	/* mmddyyyy-1 */
#define LOGTYPE_7	7	/* yymmdd */
#define LOGTYPE_8	8	/* yymmdd-1 */
#define LOGTYPE_9	9	/* mmdd */
#define LOGTYPE_10	10	/* mmdd-1 */
#define LOGTYPE_11	11	/* yyyy.mm.dd */
#define LOGTYPE_12	12	/* yyyymmdd-hh */
#define LOGTYPE_13	13	/* yyyy-mm-dd */
#define LOGTYPE_14	14	/* mm-dd */
#define LOGTYPE_15	15	/* yyyymm */
#define LOGTYPE_16	16	/* yyyymmdd/yyyymmdd */
#define LOGTYPE_17	17	/* <dd> */
#define LOGTYPE_18	18	/* yyyymmdd_hh */
#define LOGTYPE_19	19	/* yyyymmdd_h */
#define LOGTYPE_20	20	/* yyyymmdd/yyyy-mm-dd */

/*
chgmode
-----------------
순위
 0 변화 없음
17 <dd> 
 2 yyyymmdd-1
12 yyyymmdd-hh
18 yyyymmdd_hh
19 yyyymmdd_h
16 yyyymmdd/yyyymmdd
20 yyyymmdd/yyyy-mm-dd
 1 yyyymmdd
 4 mmddyyyy-1
 3 ddmmyyyy
 6 mmddyyyy-1
 5 mmddyyyy
 8 yymmdd-1
 7 yymmdd
10 mmdd-1
 9 mmdd
11 yyyy.mm.dd
13 yyyy-mm-dd
14 mm-dd
15 yyyymm

chgmode_new
-----------------
<[yyyy]>,<[yy]>,<[mm]>,<[dd]>,<[dd-1]>,<[hh]>,<[h]>
*/


/*#if defined(__DEV__)*/

int datefmt_today_yesterday_new(char _pattern[][3][16])
{
	struct  tm ddbuf;
	time_t  dtvec;
	int	i = 0;

	time(&dtvec);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);
	ddbuf.tm_mday -= 1;
	ddbuf.tm_isdst = -1;
	dtvec = mktime(&ddbuf);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);

	while(strcmp(_pattern[i][0], "")) {
		if (!strcmp(_pattern[i][0], "<[dd-1]>")){
			sprintf(_pattern[i][2], "%-2.2d", ddbuf.tm_mday);
		}
		i++;
	}
}

int datefmt_today_new(char _pattern[][3][16])
{
	struct  tm *dbuf;
	time_t  tvec;
	int i = 0;

	time(&tvec);
	dbuf = localtime(&tvec);

	while(strcmp(_pattern[i][0], "")) {
		if (!strcmp(_pattern[i][0], "<[yyyy]>")){
			sprintf(_pattern[i][2], "%4d", dbuf->tm_year+1900);
		} else if (!strcmp(_pattern[i][0], "<[yy]>")){
			sprintf(_pattern[i][2], "%2d", (dbuf->tm_year+1900)%100);
		} else if (!strcmp(_pattern[i][0], "<[mm]>")){
			sprintf(_pattern[i][2], "%-2.2d", dbuf->tm_mon+1);
		} else if (!strcmp(_pattern[i][0], "<[dd]>")){
			sprintf(_pattern[i][2], "%-2.2d", dbuf->tm_mday);
		} else if (!strcmp(_pattern[i][0], "<[hh]>")){
			sprintf(_pattern[i][2], "%-2.2d", dbuf->tm_hour);
		} else if (!strcmp(_pattern[i][0], "<[h]>")){
			sprintf(_pattern[i][2], "%d", dbuf->tm_hour);
		}
		i++;
	}
}

int changedate_new(char *fname, char *fname_org)
{
	char pattern[][3][16]={	{"<[yyyy]>", "1", ""}, {"<[yy]>", "1", ""}
							, {"<[mm]>", "2", ""}, {"<[dd]>", "3", ""}, {"<[dd-1]>", "3", ""}
							, {"<[hh]>", "4", ""}, {"<[h]>", "4", ""}, 	{"", "", ""}};
	char *ptr;	
	char tmpfname[256], tmpfname2[256];
	int mode = 0;
	int i = 0;

	memset(tmpfname, 0, sizeof tmpfname);
	strcpy(tmpfname, fname_org);

	if ((char*)strstr(tmpfname, "<[")==NULL) return 0;

	datefmt_today_new(pattern);
	datefmt_today_yesterday_new(pattern);

	while(strcmp(pattern[i][0], "")) {
		while(1){
			ptr = (char*)strstr(tmpfname, pattern[i][0]);
			if (ptr == NULL) break;	

			mode = atoi(pattern[i][1]);
			memset(tmpfname2, 0, sizeof tmpfname2);
			strcpy(tmpfname2, ptr+strlen(pattern[i][0]));
			*ptr = '\0';
			strcat(tmpfname, pattern[i][2]);
			strcat(tmpfname, tmpfname2);
		}
		i++;
	}
	if ( mode > 0) strcpy(fname, tmpfname);
	return mode;
}

/*#endif */

int changedate(char *fname, char *fname_org, int *position)
{
	char *ptr;

	if ((ptr = strstr(fname,"<dd>"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_17, 1, 0);
	} else if ((ptr = strstr(fname,"yyyymmdd-1"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_2, 1, 0);
	} else if ((ptr = strstr(fname,"yyyymmdd-hh"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_12, 1, 0);
	} else if ((ptr = strstr(fname,"yyyymmdd_hh"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_18, 1, 0);
	} else if ((ptr = strstr(fname,"yyyymmdd_h"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_19, 1, 0);
	} else if ((ptr = strstr(fname,"yyyymmdd/yyyymmdd"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_16, 1, 0);
	} else if ((ptr = strstr(fname,"yyyymmdd/yyyy-mm-dd"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_20, 1, 0);
	} else if ((ptr = strstr(fname,"yyyymmdd"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_1, 1, 0);
    } else if ((ptr = strstr(fname,"ddmmyyyy-1"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_4, 1, 0);
    } else if ((ptr = strstr(fname,"ddmmyyyy"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_3, 1, 0);
    } else if ((ptr = strstr(fname,"mmddyyyy-1"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_6, 1, 0);
    } else if ((ptr = strstr(fname,"mmddyyyy"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_5, 1, 0);
    } else if ((ptr = strstr(fname,"yymmdd-1"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_8, 1, 0);
    } else if ((ptr = strstr(fname,"yymmdd"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_7, 1, 0);
    } else if ((ptr = strstr(fname,"mmdd-1"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_10, 1, 0);
    } else if ((ptr = strstr(fname,"mmdd"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_9, 1, 0);
    } else if ((ptr = strstr(fname,"yyyy.mm.dd"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_11, 1, 0);
    } else if ((ptr = strstr(fname,"yyyy-mm-dd"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_13, 1, 0);
    } else if ((ptr = strstr(fname,"mm-dd"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_14, 1, 0);
    } else if ((ptr = strstr(fname,"yyyymm"))!=NULL) {
    	*position = ptr - fname;
		return datechg(fname, fname_org, *position, LOGTYPE_15, 1, 0);
	}
	return 0;
}

int datechg(char *_fname, char *_fname_org, int position, int _type, int _back, int _yesterday)
{
	if (_type == LOGTYPE_1 || _type == LOGTYPE_3 || _type == LOGTYPE_5 || _type == LOGTYPE_7 || 
		_type == LOGTYPE_9 || _type == LOGTYPE_11 || _type == LOGTYPE_12 || _type == LOGTYPE_13 || 
		_type == LOGTYPE_14 || _type == LOGTYPE_15 || _type == LOGTYPE_16 || _type == LOGTYPE_18 || 
		_type == LOGTYPE_19 || _type == LOGTYPE_20 ) {
		if (_yesterday == 1) 
			return datechg_today_yesterday(_fname, _fname_org, position, _type);
		else
			return datechg_today(_fname, _fname_org, position, _type);
	} else if (_type == LOGTYPE_2 || _type == LOGTYPE_4 || _type == LOGTYPE_6 || _type == LOGTYPE_8 || 
				_type == LOGTYPE_10 ) {
		if (_yesterday == 1) 
			return datechg_yesterday_yesterday(_fname, _fname_org, position, _type);
		else
			return datechg_yesterday(_fname, _fname_org, position, _type, _back);
	} else if ( _type == LOGTYPE_17 ) {
		if (_yesterday == 1) 
			return datechg_today_yesterday_back(_fname, _fname_org, position, _type);
		else
			return datechg_today_back(_fname, _fname_org, position, _type, _back);
	}
	return 0;
}

int datechg_today(char *_fname, char *_fname_org, int position, int _type)
{
	struct  tm *dbuf;
	time_t  tvec;
	char time_str[64];
	int j;
	int	num;
	char tmp_fname[256];

	time(&tvec);
	dbuf = localtime(&tvec);

	memset(time_str, 0, sizeof time_str);

	switch (_type)
	{
		case LOGTYPE_1:
			sprintf(time_str, "%4d%-2.2d%-2.2d", dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday);
			num = 8;
			break;
		case LOGTYPE_3:
			sprintf(time_str, "%-2.2d%-2.2d%4d", dbuf->tm_mday, dbuf->tm_mon+1, dbuf->tm_year+1900);
			num = 8;
			break;
		case LOGTYPE_5:
			sprintf(time_str, "%-2.2d%-2.2d%4d", dbuf->tm_mon+1, dbuf->tm_mday, dbuf->tm_year+1900);
			num = 8;
			break;
		case LOGTYPE_7:
			sprintf(time_str, "%-2.2d%-2.2d%-2.2d", (dbuf->tm_year+1900)%100, dbuf->tm_mon+1, dbuf->tm_mday);
			num = 6;
			break;
		case LOGTYPE_9:
			sprintf(time_str, "%-2.2d%-2.2d", dbuf->tm_mon+1, dbuf->tm_mday);
			num = 4;
			break;
		case LOGTYPE_11:
			sprintf(time_str, "%4d.%-2.2d.%-2.2d", dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday);
			num = 10;
			break;
		case LOGTYPE_12:
			sprintf(time_str, "%4d%-2.2d%-2.2d-%-2.2d", dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday, dbuf->tm_hour);
			num = 11;
			break;
		case LOGTYPE_13:
			sprintf(time_str, "%4d-%-2.2d-%-2.2d", dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday);
			num = 10;
			break;
		case LOGTYPE_14:
			sprintf(time_str, "%-2.2d-%-2.2d", dbuf->tm_mon+1, dbuf->tm_mday);
			num = 5;
			break;
		case LOGTYPE_15:
			sprintf(time_str, "%4d%-2.2d", dbuf->tm_year+1900, dbuf->tm_mon+1);
			num = 6;
			break;
		case LOGTYPE_16:
			sprintf(time_str, "%4d%-2.2d%-2.2d/%4d%-2.2d%-2.2d", dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday,
																dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday);
			num = 17;
			break;
		case LOGTYPE_18:
			sprintf(time_str, "%4d%-2.2d%-2.2d_%-2.2d", dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday, dbuf->tm_hour);
			num = 11;
			break;
		case LOGTYPE_19:
			sprintf(time_str, "%4d%-2.2d%-2.2d_%d", dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday, dbuf->tm_hour);
			num = strlen(time_str);

			memset(tmp_fname, 0, sizeof tmp_fname);
			strcpy(tmp_fname, _fname_org);

    		for (j = position; j < position+num; j++)     /* log 날짜변경 */
    			tmp_fname[j] = time_str[j-position];

			if ( num == 11) { /* 10시 이상일 경우 뒤에 부분을 새로 만듬 */
    			for (j = position+10; j < strlen(_fname_org); j++) 
    				tmp_fname[j+1] = _fname_org[j];
			}
			strcpy(_fname, tmp_fname);
			return _type;
		case LOGTYPE_20:
			sprintf(time_str, "%4d%-2.2d%-2.2d/%4d-%-2.2d-%-2.2d", dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday,
																dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday);
			num = 19;
			break;
		default:
			return 0;
	}

    for (j = position; j < position+num; j++)     /* log 날짜변경 */
    	_fname[j] = time_str[j-position];

	return _type;
}

int datechg_today_yesterday(char *_fname, char *_fname_org, int position, int _type)
{
	struct  tm ddbuf;
	time_t  dtvec;
	char time_str[64];
	char tmp_fname[256];
	int j;
	int	num;

	time(&dtvec);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);
	ddbuf.tm_mday -= 1;
	ddbuf.tm_isdst = -1;
	dtvec = mktime(&ddbuf);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);

	memset(time_str, 0, sizeof time_str);

	switch (_type)
	{
		case LOGTYPE_1:
			sprintf(time_str, "%4d%-2.2d%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 8;
			break;
		case LOGTYPE_3:
			sprintf(time_str, "%-2.2d%-2.2d%4d", ddbuf.tm_mday, ddbuf.tm_mon+1, ddbuf.tm_year+1900);
			num = 8;
			break;
		case LOGTYPE_5:
			sprintf(time_str, "%-2.2d%-2.2d%4d", ddbuf.tm_mon+1, ddbuf.tm_mday, ddbuf.tm_year+1900);
			num = 8;
			break;
		case LOGTYPE_7:
			sprintf(time_str, "%-2.2d%-2.2d%-2.2d", (ddbuf.tm_year+1900)%100, ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 6;
			break;
		case LOGTYPE_9:
			sprintf(time_str, "%-2.2d%-2.2d", ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 4;
			break;
		case LOGTYPE_11:
			sprintf(time_str, "%4d.%-2.2d.%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 10;
			break;
		case LOGTYPE_12:
			sprintf(time_str, "%4d%-2.2d%-2.2d-%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday, ddbuf.tm_hour);
			num = 11;
			break;
		case LOGTYPE_13:
			sprintf(time_str, "%4d-%-2.2d-%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 10;
			break;
		case LOGTYPE_14:
			sprintf(time_str, "%-2.2d-%-2.2d", ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 5;
			break;
		case LOGTYPE_15:
			sprintf(time_str, "%4d%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1);
			num = 7;
			break;
		case LOGTYPE_16:
			sprintf(time_str, "%4d%-2.2d%-2.2d/%4d%-2.2d%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday,
																ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 17;
			break;
		case LOGTYPE_18:	/* yyyymmdd_hh */
			sprintf(time_str, "%4d%-2.2d%-2.2d_%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday, ddbuf.tm_hour);
			num = 11;
			break;
		case LOGTYPE_19:	/* yyyymmdd_h */
			sprintf(time_str, "%4d%-2.2d%-2.2d_%d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday, ddbuf.tm_hour);
			num = strlen(time_str);

			memset(tmp_fname, 0, sizeof tmp_fname);
			strcpy(tmp_fname, _fname_org);

    		for (j = position; j < position+num; j++)     /* log 날짜변경 */
    			tmp_fname[j] = time_str[j-position];

			if ( num == 11) { /* 10시 이상일 겨우 뒤에 부분을 새로 만듬 */
    			for (j = position+10; j < strlen(_fname_org); j++) 
    				tmp_fname[j+1] = _fname_org[j];
			}
			strcpy(_fname, tmp_fname);
			return _type;
		case LOGTYPE_20:
			sprintf(time_str, "%4d%-2.2d%-2.2d/%4d-%-2.2d-%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday,
																ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 19;
			break;
		default:
			return 0;
	}

    for (j = position; j < position+num; j++)     /* log 날짜변경 */
    	_fname[j] = time_str[j-position];

	return _type;
}

int datechg_yesterday(char *_fname, char *_fname_org, int position, int _type, int _back)
{
	struct  tm ddbuf;
	time_t  dtvec;
	char time_str[32];
	int j;
	int num;

	time(&dtvec);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);
	ddbuf.tm_mday -= 1;
	ddbuf.tm_isdst = -1;
	dtvec = mktime(&ddbuf);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);

	memset(time_str, 0, sizeof time_str);

	switch (_type)
	{
		case LOGTYPE_2:
			sprintf(time_str, "%4d%-2.2d%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 8;
			break;
		case LOGTYPE_4:
			sprintf(time_str, "%-2.2d%-2.2d%4d", ddbuf.tm_mday, ddbuf.tm_mon+1, ddbuf.tm_year+1900);
			num = 8;
			break;
		case LOGTYPE_6:
			sprintf(time_str, "%-2.2d%-2.2d%4d", ddbuf.tm_mon+1, ddbuf.tm_mday, ddbuf.tm_year+1900);
			num = 8;
			break;
		case LOGTYPE_8:
			sprintf(time_str, "%-2.2d%-2.2d%-2.2d", (ddbuf.tm_year+1900)%100, ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 6;
			break;
		case LOGTYPE_10:
			sprintf(time_str, "%-2.2d%-2.2d", ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 4;
			break;
		case LOGTYPE_17:
			sprintf(time_str, "%-2.2d", ddbuf.tm_mday);
			num = 2;
			break;
		default:
			return 0;
	}

	for (j=position;j<position+num;j++)
   		_fname[j]=time_str[j-position];

	if (_back == 1) {
    	for(j=position+num+2;j<strlen(_fname);j++)
    		_fname[j-2] = _fname[j];
		_fname[j-2]='\0';
	}

	return _type;
}

int datechg_yesterday_yesterday(char *_fname, char *_fname_org, int position, int _type)
{
	struct  tm ddbuf;
	time_t  dtvec;
	char time_str[32];
	int j;
	int num;

	time(&dtvec);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);
	ddbuf.tm_mday -= 2;
	ddbuf.tm_isdst = -1;
	dtvec = mktime(&ddbuf);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);


	memset(time_str, 0, sizeof time_str);

	switch (_type)
	{
		case LOGTYPE_2:
			sprintf(time_str, "%4d%-2.2d%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 8;
			break;
		case LOGTYPE_4:
			sprintf(time_str, "%-2.2d%-2.2d%4d", ddbuf.tm_mday, ddbuf.tm_mon+1, ddbuf.tm_year+1900);
			num = 8;
			break;
		case LOGTYPE_6:
			sprintf(time_str, "%-2.2d%-2.2d%4d", ddbuf.tm_mon+1, ddbuf.tm_mday, ddbuf.tm_year+1900);
			num = 8;
			break;
		case LOGTYPE_8:
			sprintf(time_str, "%-2.2d%-2.2d%-2.2d", (ddbuf.tm_year+1900)%100, ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 6;
			break;
		case LOGTYPE_10:
			sprintf(time_str, "%-2.2d%-2.2d", ddbuf.tm_mon+1, ddbuf.tm_mday);
			num = 4;
			break;
		default:
			return 0;
	}

	for (j=position;j<position+num;j++)
   		_fname[j]=time_str[j-position];

	return _type;
}

int datechg_today_back(char *_fname, char *_fname_org, int position, int _type, int _back)
{
	struct  tm *dbuf;
	time_t  tvec;
	char time_str[32];
	int j;
	int	num;

	time(&tvec);
	dbuf = localtime(&tvec);

	memset(time_str, 0, sizeof time_str);

	switch (_type)
	{
		case LOGTYPE_17:
			sprintf(time_str, "%-2.2d", dbuf->tm_mday);
			num = 2;
			break;
		default:
			return 0;
	}

    for (j = position; j < position+num; j++)     /* log 날짜변경 */
    	_fname[j] = time_str[j-position];

	if (_back == 1) {
    	for(j=position+num+2;j<strlen(_fname);j++)
    		_fname[j-2] = _fname[j];
		_fname[j-2]='\0';
	}

	return _type;
}

int datechg_today_yesterday_back(char *_fname, char *_fname_org, int position, int _type)
{
	struct  tm ddbuf;
	time_t  dtvec;
	char time_str[32];
	int j;
	int	num;

	time(&dtvec);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);
	ddbuf.tm_mday -= 1;
	ddbuf.tm_isdst = -1;
	dtvec = mktime(&ddbuf);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);

	memset(time_str, 0, sizeof time_str);

	switch (_type)
	{
		case LOGTYPE_17:
			sprintf(time_str, "%-2.2d", ddbuf.tm_mday);
			num = 2;
			break;
		default:
			return 0;
	}

    for (j = position; j < position+num; j++)     /* log 날짜변경 */
    	_fname[j] = time_str[j-position];

	return _type;
}

int datechg_onemin_ago(char* _daytime_aix)
{

	struct  tm ddbuf;
	time_t  dtvec;
	char time_str[32];

	time(&dtvec);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);
	ddbuf.tm_min -= 1;
	ddbuf.tm_isdst = -1;
	dtvec = mktime(&ddbuf);
	memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);

	sprintf(time_str, "%-2.2d%-2.2d%-2.2d%-2.2d%-2.2d",
                ddbuf.tm_mon+1, ddbuf.tm_mday, ddbuf.tm_hour, ddbuf.tm_min, ddbuf.tm_year-100);

	strcpy(_daytime_aix, time_str);
}
