/*
 * Copyright (c) 2000, 2001, ITOP SYSTEM Inc. All rights reserved.
 *
 * NAME
 *      time.cpp - Lib Function
 *
 * MODIFIED     (MM/DD/YYYY)
 *  MyungKyun   10/30/2001 - 통합정리.
 *
 */

#include <time.h>
#include <stdio.h>
#include <string.h>

/* time buf(week)에 SUN ~ SAT return */
void bfweek(char *week)
{
	char *const wday[] = {
		"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
	};

	time_t tvec;
	struct tm *tmptr;
	time(&tvec);
	tvec -= 86400;
	tmptr = localtime(&tvec);
	strcpy(week, wday[tmptr->tm_wday]);
}

/* time buf(tmb)에 yymmdd  return */
void bffullday(char *tmb)
{
	time_t tvec;
	struct tm *tmptr;
	time(&tvec);
	tvec -= 86400;
	tmptr = localtime(&tvec);
	sprintf(tmb, "%04d%02d%02d", tmptr->tm_year+1900,
				tmptr->tm_mon+1, tmptr->tm_mday);
}

int getDayIndexOfWeek( int _year, int _month, int _day)
{
	int i;
	int days;
	int end_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	if ( _year % 4  == 0 && (_year % 400 == 0 ||  _year % 100 != 0 )) end_day[1] = 29;
	 
	_year--;
	
	days = _year * 365 + _year / 4 + _year / 400 - _year / 100;
	
	for( i = 0; i < _month -1; i++) days += end_day[i];
	
	days+= _day;

	/* 0: sunday */
	return days % 7;
}

int getDayIndexOfWeekString( int _year, int _month, int _week, int _dayth, char* _timestr)
{
	int weekfirst = -1;
	int day = 1;

	weekfirst = getDayIndexOfWeek( _year, _month, 1);

	if (weekfirst == _week) {
		day = 1;
	} else if ( weekfirst > _week) {
		day = 7 - weekfirst + _week + 1;
	} else if ( weekfirst < _week) {
		if ( _week == 0) day = 1 + 7 - weekfirst;
		else day = 1 + _week - weekfirst;
	}

	day += 7*(_dayth-1);

	sprintf(_timestr, "%4.4d%2.2d%2.2d", _year, _month, day);

	return 1;
}


