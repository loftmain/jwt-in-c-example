/*
   $Id: get_evt_subclass.c,v 1.0 2015/03/02 srp Exp $

   Copyright (c) 2000, 2015
             NewSystech Inc.  All rights reserved.

   2015-03-02
     * Disk의 파일시스템명 가져오기 위해 사용
	 * oracle tablespace의 SID^tablespac명 가져오기 위해 사용
*/

#include <stdio.h>
#include <string.h>

int get_evt_subclass(char *mid, char* msgstr, char* subclass)
{
	char  *ptr;
	char bufstr1[2048], bufstr2[2048];

	/* get subclass */
	if((!strncmp(mid,"CDSK", 4) || !strncmp(mid,"FDSK", 4)) && mid[5]=='1' && mid[6]=='1') {
		ptr = (char*)strchr(msgstr, '(');
		if ( ptr != NULL) {
			strcpy(subclass, ptr+1);
			ptr = (char*)strchr(subclass, ')');
			if ( ptr != NULL) *ptr='\0';
		}
	} else if((!strncmp(mid,"CORA",4) || !strncmp(mid,"FORA",4)) && mid[5]=='0' && mid[6]=='6') {
		memset(bufstr1, 0, sizeof bufstr1);
		ptr = (char*)strchr(msgstr, '[');
		if ( ptr != NULL) {
			strcpy(subclass, ptr+1);
			ptr = (char*)strchr(subclass, ']');
			if ( ptr != NULL) {
				strcpy(bufstr1, ptr+1);
				*ptr = '\0';
			}
		} else {
			ptr = (char*)strchr(msgstr, '(');
			if ( ptr != NULL) {
				strcpy(subclass, ptr+1);
				ptr = (char*)strchr(subclass, ')');
				if ( ptr != NULL) {
					strcpy(bufstr1, ptr+1);
					*ptr = '\0';
				}
			}
		}
        memset(bufstr2, 0, sizeof bufstr2);
		ptr = (char*)strchr(bufstr1, '(');
		if (ptr != NULL) {
			strcpy(bufstr2, ptr+1);
			ptr = (char*)strchr(bufstr2, ')');
			if (ptr != NULL) {
				*ptr = '\0';
				strcat(subclass,"^");
				strcat(subclass,bufstr2);
			} else return(0);
		} else return(0);
	}
	return(1);
}

