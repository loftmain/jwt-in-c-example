/*
   $Id: rtrim.c,v 1.7 2003/06/30 srp Exp $

   Copyright (c) 2000, 2001, 2002, 2003
             i-TOP System Inc.  All rights reserved.

   2003-06-30
     * 문자열의 오른쪽 space 제거
*/

#include <stdio.h>
#include <string.h>

int rtrim(sbuf)
char *sbuf;
{
  	int 	i, len;

  	len = strlen(sbuf);

  	if (len > 2) {
		for (i = len -1; i >= 0; i--) {
			if ((sbuf[i] != ' ') && (sbuf[i] != '\n') && (sbuf[i] != '\t'))
				break;
        } 
		if (i != (len - 1))
			sbuf[i+1] = '\0';
	}
  	return(0);
}
