#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int check_lic()
{
  time_t tvec, cmptvec;
  struct tm time_str;

  time(&tvec);

  time_str.tm_year    = 2001 - 1900;
  time_str.tm_mon = 6 - 1;
  time_str.tm_mday = 30;
  time_str.tm_hour = 0;
  time_str.tm_min = 0;
  time_str.tm_sec = 1;
  time_str.tm_isdst = -1;
  cmptvec = mktime(&time_str);

  if(cmptvec == -1) return(-1);

  if(tvec > cmptvec) return(-1);
  return(0);
}

/*  company code 별 라이센스 점검 */
int check_lic2(char* _itcompany, int *_maxcnt)
{
	char lic_s2o_list[][9][64] = {
          {"KEAD","0","2019","02","28","23","59","0","한국장애인고용공단"},
          /*{"GILL","0","2020","04","01","09","01","0","경기도평생교육진흥원"},*/
          /*{"GILL","0","2018","03","31","23","59","0","경기도평생교육진흥원"},*/
          /*{"ITOPS","0","2018","03","07","15","50","0","NewSystech"},*/
          {"ITOPS","1","2017","08","11","05","00","200","NewSystech"},
          {"","","","","","","","",""}};
          /* managemet_type : 0(기한), 1(수량) */
          /* managemet_type=0 : company, 0, expire_year, expire_month, expire_day, expire_hour, expire_min, 0, description */
          /* managemet_type=1 : company, 1, check_start_year, check_start_month, check_start_day, check_start_hour, check_start_min, lic_count,description */

	int i = 0;

	time_t tvec1, cmptvec;
  	struct tm time_str;

	time(&tvec1);

	*_maxcnt = 0;

	while (strcmp(lic_s2o_list[i][0], "")) {
		if ( !strcmp(lic_s2o_list[i][0], _itcompany)) {
			time_str.tm_year	= atoi(lic_s2o_list[i][2]) - 1900;
			time_str.tm_mon		= atoi(lic_s2o_list[i][3]) - 1;
			time_str.tm_mday	= atoi(lic_s2o_list[i][4]);
			time_str.tm_hour	= atoi(lic_s2o_list[i][5]);
			time_str.tm_min		= atoi(lic_s2o_list[i][6]);
			time_str.tm_sec		= 0;
			time_str.tm_isdst	= -1;
			cmptvec = mktime(&time_str);

			if ( !strcmp(lic_s2o_list[i][1], "0")) {
				if(cmptvec == -1) return(0);
				return (cmptvec - tvec1);
			} else if ( !strcmp(lic_s2o_list[i][1], "1")) {
				if(cmptvec == -1) return(0);
				if ( cmptvec - tvec1 > 0) return(0);

				*_maxcnt = atoi(lic_s2o_list[i][7]);
				return(0);
			}
		}
		i++;
	}
  	return(0);
}

