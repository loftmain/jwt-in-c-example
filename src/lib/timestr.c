   /************************************************************************/
   /*  FILENAME     : logtime.c                                            */
   /*  DISCRIPTION  : loging() 에서 사용될 date,time 얻기                  */
   /*  DATE         : 2000. 08. 29                                         */
   /*  MODIFIED     : 2000. 08. 29                                         */
   /*  WRITTEN      : ywoopark                                             */
   /************************************************************************/

#include <time.h>
#include <stdio.h>
#include <string.h>

void timestr(char *tim)  	/* 16 Byte time buffer required */
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

  	sprintf(tim,"%s %2d %2.2d:%2.2d:%2.2d",mon,dbuf->tm_mday, dbuf->tm_hour,dbuf->tm_min,dbuf->tm_sec);
}

void timestr2(char *tim)  	/* 16 Byte time buffer required */
{
  	time_t tvec;
  	struct tm *dbuf;

  	time(&tvec);
  	dbuf=localtime(&tvec);

  	sprintf(tim, "%-4.4d%2.2d%2.2d%2.2d%2.2d%2.2d",dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday, dbuf->tm_hour,dbuf->tm_min, dbuf->tm_sec);
}

int compare_time(int type, char* time_from, char* time_to) /* type: 1(yyyymmddhh24mi) */
{
	time_t tvec;
	struct tm *dbuf;
	char time_c[20];

	memset(time_c, 0, sizeof time_c);	

	if (type != 1 || (strlen(time_from) !=12 && strlen(time_to) !=12) ) return(-1);

	time(&tvec);
	dbuf=localtime(&tvec);

	if (type == 1) 
	{	
		sprintf(time_c, "%-4.4d%2.2d%2.2d%2.2d%2.2d", dbuf->tm_year+1900, dbuf->tm_mon+1, dbuf->tm_mday, dbuf->tm_hour, dbuf->tm_min);	

		if (strlen(time_from)==12 && strlen(time_to)==12) {
			if (strcmp(time_c, time_from)>=0 && strcmp(time_c, time_to) <= 0) return(1);	
			return(0);
		} else if (strlen(time_from)==12 && strlen(time_to)==0){
			if (strcmp(time_c, time_from) >= 0) return(1);	
			return(0);
		} else if (strlen(time_from)==0 && strlen(time_to)==12){
			if (strcmp(time_c, time_to) <= 0) return(1);
			return(0);
		} else return(-1);
	} else {
		return(-1);
	}

	return(0);
}

