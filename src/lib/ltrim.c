/*
   $Id: ltrim.c,v 1.7 2003/06/30 srp Exp $

   Copyright (c) 2000, 2001, 2002, 2003
             i-TOP System Inc.  All rights reserved.

   2003-06-30
     * 문자열의 왼쪽 space 제거
*/

#include <stdio.h>
#include <string.h>

int ltrim(sbuf)
char *sbuf;
{
  	int 	len;
  	char 	ss[2048];
  	char 	*s;

  	memset(ss, 0, sizeof ss);
  	len = strlen(sbuf);
  	if (len > 2) {
     	strcpy(ss, sbuf);
     	s = ss;
     	if (s != NULL) {
        	while (*s == ' ' || *s == '\t')
             	s++;
        	memset(sbuf, 0, sizeof sbuf);
        	strcpy(sbuf, s);
        } 
	}
  	return(0);
}

int lltrim(sbuf)
char *sbuf;
{
  	int 	len;
  	char 	ss[2048];
  	char 	*s;

	if(sbuf[0] != ' ') return -1;

  	memset(ss, 0, sizeof ss);
   	strcpy(ss, sbuf);
   	s = ss;
   	if (s != NULL) {
      	while (*s == ' '|| *s == '\t') s++;
      	memset(sbuf, 0, sizeof sbuf);
      	strcpy(sbuf, s);
	}
  	return(0);
}
