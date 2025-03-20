/*
 * Copyright (c) 2000, 2001, ITOP SYSTEM Inc. All rights reserved.
 *
 * NAME
 *      getdata.c - 문자열에서 해당 column의 data 얻기
 *
 * MODIFIED     (MM/DD/YYYY)
 *  MyungKyun   10/22/2001 - 
 *
 */

#include <stdio.h>
#include <string.h>

int getdata(char *ibuf, char *obuf, int n)
{
  	char s[9][257];
  	int i;

  	for(i = 0; i < 9; i++)
     	memset(s[i], 0x00, sizeof s[i]);

  	if(ibuf[0] == ' ')
     	return(-1); 
  	if(ibuf[0] == '\n')
     	return(-1); 
  	if(ibuf[0] == '#')
     	return(-1); 

  	for(i=0; i<9; i++)
     	memset(s[i], 0, sizeof s[i]);

  	sscanf(ibuf,"%s%s%s%s%s%s%s%s%s",s[0],s[1],s[2],s[3],s[4],s[5],
					s[6],s[7],s[8]);

  	if((n < 1) || (n > 9)) {
     	printf("Invalid argument!\n");
     	return(-1); 
    }

  	if(strlen(s[n-1]) == 0) {
     	printf("Data가 없습니다..!!!!!!!\n");
     	return(-1);
    }
  	memset(obuf,0,sizeof obuf);
  	strcpy(obuf,s[n-1]);
  	return(0);
}
