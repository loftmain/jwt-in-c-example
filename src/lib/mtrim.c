/*
   $Id: mtrim.c,v 1.0 2018/11/26 srp Exp $

   Copyright (c) 2018
             NewSystech Inc.  All rights reserved.

   2018-11-26
     * 문자열의 가운데 space 제거 ( 2개 이상인 경우)
*/

#include <stdio.h>
#include <string.h>

void mtrim(char *src)
{
	char dest[2048];
	char *sptr, *dptr;
	int space_flag = -1;

	memset(dest, 0, sizeof dest);
	sptr = src;
	dptr = dest;

	while(*sptr)
	{
		if (*sptr == ' ' || *sptr == '\t') {
			if ( space_flag == 0) {
				space_flag = 1;
				*dptr++ = ' ';
			}
			*sptr++;
			continue;
		} else {
			space_flag = 0;
		}
		*dptr++ = *sptr++;
	}
	strcpy(src, dest);
}

