   /************************************************************************/
   /*  FILENAME     : date1.c                                              */
   /*  DISCRIPTION  : Mar 01 12:12:12 의 형식으로 data를 얻음.             */
   /*  DATE         : 1997. 05. 19                                         */
   /*  WRITTEN      : stmpywb                                              */
   /************************************************************************/

#include <time.h>
#include <string.h>
#include <stdio.h>

void date1(tim)
char *tim;
{
  	static char *allmonth[] = {
      "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
	};
  	char *mon;
  	time_t tvec;
  	struct tm *dbuf;
 
  	memset(tim,0,sizeof tim);
  	time(&tvec);
  	dbuf=localtime(&tvec);
  	mon=allmonth[dbuf->tm_mon];
  	sprintf(tim,"%s %2d %2.2d:%2.2d:%2.2d",mon,dbuf->tm_mday,
         dbuf->tm_hour,dbuf->tm_min,dbuf->tm_sec);
}

void make_date1(char* tim, int time_gap_hour)
{
  	static char *allmonth[] = {
      "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
	};

  	char *mon;
  	time_t dtvec;
  	struct tm ddbuf;

	if (time_gap_hour == 0) {
		date1(tim);
		return;
	}

    time(&dtvec);
    memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf);
    ddbuf.tm_hour += time_gap_hour;
    ddbuf.tm_isdst = -1;
    dtvec = mktime(&ddbuf);
    memcpy(&ddbuf,localtime(&dtvec),sizeof ddbuf); 

  	memset(tim,0,sizeof tim);
  	mon=allmonth[ddbuf.tm_mon];
  	sprintf(tim,"%s %2d %2.2d:%2.2d:%2.2d", mon, ddbuf.tm_mday,
         ddbuf.tm_hour, ddbuf.tm_min, ddbuf.tm_sec);
}

