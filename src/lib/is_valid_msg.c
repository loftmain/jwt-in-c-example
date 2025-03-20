/*
 * Copyright (c) 2000, 2001, ITOP SYSTEM Inc. All rights reserved.
 *
 * NAME
 *      is_valid_msg.c - 
 *
 * MODIFIED     (MM/DD/YYYY)
 *  MyungKyun	01/27/2004 - Message Code 'A' 추가 (Alarm stop)
 *  MyungKyun	03/15/2002 - Message Code 'U' 추가 (User Command)
 *  MyungKyun	03/15/2002 - Message Code 'R' 추가 (RealTime Performance)
 *  MyungKyun   03/07/2002 - Capa Data를 표현하기 위해 Message Code 'P' 추가.
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../IT.extern.h"

extern int getitemc(int ch, char *src);

int is_valid_msg(char *v_msg)
{
  	char v_mid[256];

  	if (strlen(v_msg) < 7)  /* message의 전체 길는 는 msg ID의 길이 보다 큼.*/
     	return(-1);

  	memset(v_mid, 0x00, sizeof v_mid);
  	sscanf(v_msg, "%s", v_mid);  /* msgid가 7자리 인가 */

  	if (strlen(v_mid) != 7)
     	return(-1);


  	if ((v_msg[0] != 'A') &&				/* Console Alarm stop holding */
		(v_msg[0] != 'C') &&				/* Critial */
	   	(v_msg[0] != 'D') &&				/* Defined messages */
	   	(v_msg[0] != 'E') &&				/* Error */
	   	(v_msg[0] != 'F') && 				/* Fatal */
	   	(v_msg[0] != 'I') && 				/* Information */
	   	(v_msg[0] != 'L') && 				/* Let's Talk, Console Manual Message */
	   	(v_msg[0] != 'O') && 				/* Operation */
	   	(v_msg[0] != 'P') && 				/* Not vew messages type */
	   	(v_msg[0] != 'R') && 				/* Real time messages */
       	(v_msg[0] != 'S') && 				/* Severe */
       	(v_msg[0] != 'T') && 				/* Console alarm stop release */
	   	(v_msg[0] != 'U') &&				/* User command messages */
	   	(v_msg[0] != 'W') && 				/* Warning */
	   	(v_msg[0] != 'Y') && 				/* 마스터 콘솔 이벤트 clear message */
	   	(v_msg[0] != 'Z'))  				/* 마스터 콘솔 이벤트 clear message(sound stop) */
      	return(-1);

  	if (!isdigit(v_msg[4]))
     	return(-1);

  	if (!isdigit(v_msg[5]))
     	return(-1);
  	if (!isdigit(v_msg[6]))
     	return(-1);

  	return(0);
}

int is_valid_format(char *v_msg)
{
	char    agent_month[256], agent_day[256], agent_time[256];	
	char    tmp_mid[256], tmp_ccode[256], tmp_hname[256], tmp_msg[256];

	char 	msg_buf[512];
	char	*ptr;

	memset(msg_buf, 0, sizeof msg_buf);
	memset(agent_month, 0, sizeof agent_month);
	memset(agent_day, 0, sizeof agent_day);
	memset(agent_time, 0, sizeof agent_time);
	memset(tmp_mid, 0, sizeof tmp_mid);
	memset(tmp_ccode, 0, sizeof tmp_ccode);
	memset(tmp_hname, 0, sizeof tmp_hname);
	memset(tmp_msg, 0, sizeof tmp_msg);

	memset(msg_buf, 0, sizeof msg_buf);
	sscanf(v_msg, "%255c", msg_buf);

	ptr = (char*) strchr(msg_buf, '%');
	if (ptr != NULL) {
		while(1) {
			ptr = (char*) strchr(msg_buf, '%');
			if (ptr != NULL) *ptr = ' ';
			else break;
		}
	}

	sscanf(msg_buf, "%s %s %s %s %s %s %s", tmp_mid, tmp_ccode, agent_month, agent_day, agent_time, tmp_hname, tmp_msg);

	if (strlen(tmp_mid) != 7 ) return(-1);	
	if (strlen(tmp_ccode) > 5 ) return(-2);	

	if (strlen(agent_month) != 3) return(-3);	
	if (strlen(agent_day) > 2) return(-4);	
	if (strlen(agent_time) > 8) return(-5);	

	if (getitemc(':', agent_time) != 2) return(-6);

	if(strlen(tmp_msg) == 0) return(-7);

	return 1;
}

