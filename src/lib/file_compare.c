/*
   $Id: file_compare.c,v 1.7 2014/12/03 srp Exp $

   Copyright (c) 2014
             NEWSYSTECH Inc.  All rights reserved.
*/

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif
#include "../IT.extern.h"
#include "../msgid_schd.h"

extern int it_loging(char *format,...);

int file_compare(char *file1, char *file2, char* _rcvmode, char* _SERVER, char* _hostinfo, char* _rcvsendinfo)
{
	FILE *fp1, *fp2;
	char rbuf1[2048];
	char rbuf2[2048];
	int	 ret = 1;
	int  line1 = 0;
	int  line2 = 0;
	int	 realline = 0;
	char *sptr;
	char filename[128];
	char servername[128];
	char cocode[32];
	int	min = 0;

	memset(filename, 0, sizeof filename);
	sptr = strrchr(file2, '/');
	if (sptr != NULL) {
		sprintf(filename, "%s", sptr+1);
	}
	

	if ((fp1=fopen(file1, "r")) == NULL) {
       	it_loging("libIT.a(%s): file_compare() <pid:%d>  file_read file(%s) open error!\n", _SERVER, getpid(), file1);
		return -1;
	}

	if ((fp2=fopen(file2, "r")) == NULL) {
       	it_loging("libIT.a(%s): file_compare() <pid:%d>  file_read file(%s) open error!\n", _SERVER, getpid(), file2);
		fclose(fp1);
		return -1;
	}

	while(1) {
		memset(rbuf1, 0, sizeof rbuf1);
		if (line1 > -1) {
			if (fgets(rbuf1, 2047, fp1) != NULL) {
				if ( rbuf1[strlen(rbuf1)-1] == '\n') rbuf1[strlen(rbuf1)-1] = '\0';
				line1++;
			} else {
				line1 = -99;
			}
		}

		memset(rbuf2, 0, sizeof rbuf2);
		if (line2 > -1) {
			if (fgets(rbuf2, 2047, fp2) != NULL) {
				if ( rbuf2[strlen(rbuf2)-1] == '\n') rbuf2[strlen(rbuf2)-1] = '\0';
				line2++;
				if ( rbuf2[0] != '#') realline++;
			} else {
				line2 = -99;
			}
		}

		if (line1 != line2 || strcmp(rbuf1, rbuf2)) {
			if (!strcmp(filename, "ecs_decode.cfg")) {
				if (line1 == line2 && rbuf1[0]=='#' && rbuf2[0]== '#') continue;  /* ecs_decode.cfg ���Ϸ� �߰� */
			} else {
				if (line1 == line2 && rbuf1[0]=='#') continue; 
			}
			ret = 0; 
			break;
		}
		if (line1 == line2 && line1 == -99) {
			break;
		}
	}
	fclose(fp1);
	fclose(fp2);


	if ( !strcmp(_rcvmode, "s2ocfg") || !strcmp(_rcvmode, "s2ocfgs")) {

		if (!strcmp(filename, "process.cfg"))
		{
			if (strlen(_rcvsendinfo) < 5) /* Sub �����͸� ���ļ� �� ��� ������ ������ */
			{
				if (ret == 0 || realline == 0)
				{
					memset(rbuf1, 0, sizeof rbuf1);
					get_cfg("IT_MODE", rbuf1);

					if (!strcmp(rbuf1, "1")) {        /* �����͸� ���� */

						line1 = 0;
						line2 = 0;
						memset(rbuf1, 0, sizeof rbuf1);
						sprintf(rbuf1, "grep -v ^# %s |wc -l", file1);
						if ((fp1 = popen(rbuf1, "r")) != NULL) {
							memset(rbuf2, 0, sizeof rbuf2);
							fgets(rbuf2, 511, fp1);
							sscanf(rbuf2, "%d", &line1);
							pclose(fp1);
						}
						memset(rbuf1, 0, sizeof rbuf1);
						sprintf(rbuf1, "grep -v ^# %s |wc -l", file2);
						if ((fp1 = popen(rbuf1, "r")) != NULL) {
							memset(rbuf2, 0, sizeof rbuf2);
							fgets(rbuf2, 511, fp1);
							sscanf(rbuf2, "%d", &line2);
							pclose(fp1);
						}

						memset(servername, 0, sizeof servername);
						memset(cocode, 0, sizeof cocode);
						strcpy(servername, _hostinfo);
						sptr = (char*)strrchr(servername, '.');
						if (sptr != NULL) {
							strcpy(cocode, sptr+1);	
							*sptr = '\0';
						}

						memset(rbuf1, 0, sizeof rbuf1);
						get_cfg("MON_SET_PRS_MIN", rbuf1);
						min = atoi(rbuf1);
						if ( min < 1)  {
							min = 5;
						}
		
						if ( line1 - line2 >= min ) {
							wlog2("CPRS013", cocode, servername, STR_C_PRS13_4, line1, line2);
							it_loging("libIT.a(%s): file_compare() <pid:%d> Number of process monitoring settings has been reduced. "
										"(Previous:%d, Current:%d, Set:%d, HostString:%s)\n", _SERVER, getpid(), line1, line2, min, _hostinfo);
						} else if ( line2 == 0) {
							/* Agent���� ����� */
							/*
							wlog2("CPRS013", cocode, servername, STR_C_PRS13_5);
							*/
							it_loging("libIT.a(%s): file_compare() <pid:%d> No processes registered for monitoring.\n", _SERVER, getpid());
						}
					}
				}
			}
		}
	}
	return ret;
}

