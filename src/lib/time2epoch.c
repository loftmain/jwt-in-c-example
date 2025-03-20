#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static char *allmonth[] =
{
	"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
};

char buff[256] ;

extern int getitem(int ch, char *src, char *dest, int seqitem);

long time2epoch(char *msg_month, int msg_day, char *msg_time)
{
    int i;
    char hour[3], minute[3], second[3];
    time_t    t1, t2;
    struct tm *currdate, agentdate;

    time(&t1);
    currdate = localtime(&t1);

    for (i = 0; i < 12; i++) {
        if (!strcmp(allmonth[i], msg_month))
            break;
    }

    memset(hour, 0x00, sizeof hour);
    memset(minute, 0x00, sizeof minute);
    memset(second, 0x00, sizeof second);
    getitem(':', msg_time, hour, 1);
    getitem(':', msg_time, minute, 2);
    getitem(':', msg_time, second, 3);

    agentdate.tm_mon = i;                       /* Set month */
    agentdate.tm_mday= msg_day;                 /* Set day */
    agentdate.tm_year= currdate->tm_year;       /* Set year */
    agentdate.tm_hour= atoi(hour);              /* Set hour */
    agentdate.tm_min = atoi(minute);            /* Set minute */
    agentdate.tm_sec = atoi(second);            /* Set second */

    if (agentdate.tm_year > 1900)               /* 4-digit date? */
        agentdate.tm_year -= 1900 ;             /* yes, adjust */
    else if (agentdate.tm_year < 50)            /* 2000-2049 */
        agentdate.tm_year += 100;

    agentdate.tm_isdst = -1;            /* Determine if DST is in effect */

    t2 = mktime(&agentdate);            /* From struct to time_t */

    return ((long) t2);
}

char *epoch2time(int epoch)
{
    time_t CurrTime ;
    struct tm TestTime ;
    char *fmt = "%b %d %H:%M:%S %Y" ;

    CurrTime = epoch;

    memcpy(&TestTime, localtime(&CurrTime), sizeof(TestTime)) ;
    strftime(buff, sizeof(buff), fmt, &TestTime) ;

    return buff;
}

char *epoch2date(int epoch, char* _date)
{
    time_t CurrTime ;
    struct tm TestTime ;
    char *fmt = "%Y%m%d %H:%M:%S" ;

    CurrTime = epoch;

    memcpy(&TestTime, localtime(&CurrTime), sizeof(TestTime)) ;
    strftime(buff, sizeof(buff), fmt, &TestTime) ;
	strcpy(_date, buff);

    return buff;
}

long difftime_msg(char *msg_month, char* msg_day, char *msg_time)
{
    int i;
    char hour[3], minute[3], second[3];
    time_t    t1, t2;
    struct tm *currdate, agentdate;

    time(&t1);
    currdate = localtime(&t1);

    for (i = 0; i < 12; i++) {
        if (!strcmp(allmonth[i], msg_month))
            break;
    }

	memcpy(&agentdate,localtime(&t1),sizeof agentdate);

    memset(hour, 0x00, sizeof hour);
    memset(minute, 0x00, sizeof minute);
    memset(second, 0x00, sizeof second);
    getitem(':', msg_time, hour, 1);
    getitem(':', msg_time, minute, 2);
    getitem(':', msg_time, second, 3);

    agentdate.tm_mon = i;                       /* Set month */
    agentdate.tm_mday= atoi(msg_day);                 /* Set day */
    agentdate.tm_year= currdate->tm_year;       /* Set year */
    agentdate.tm_hour= atoi(hour);              /* Set hour */
    agentdate.tm_min = atoi(minute);            /* Set minute */
    agentdate.tm_sec = atoi(second);            /* Set second */

	if ( currdate->tm_mon < i ) {
		agentdate.tm_year = agentdate.tm_year-1;
	}
		
	/*if ( i == 11 && currdate->tm_mon == 0 ) {*/ /* 1월에 12월 data인 경우 */
		/*agentdate.tm_year = agentdate.tm_year-1; */
	/*} else if ( i == 0 && currdate->tm_mon == 11 ) { */ /* 12월에 1월 data인 경우  */
		/*agentdate.tm_year = agentdate.tm_year+1;*/
	/*}*/

    t2 = (long)mktime(&agentdate);            /* From struct to time_t */
    return (long)(t1- t2); /* sec */
}

