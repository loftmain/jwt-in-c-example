/*
   $Id: write_ver.c, v1.0 2015/07/15 srp Exp $
	- 프로그램별 버전 저장 기능	
   Copyright (c) 2015
             NewSystech Inc.
         All rights reserved.

*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

extern char S2O_DAEMON[64];
extern int it_loging(char *format,...);
extern int fcopy(char *src, char *dest, mode_t pmode);

int write_ver(char* _homedir, char* _version, char* _pgmname)
{
    FILE    *fp, *fpw;
    char    rbuf[256], chkbuf[256];
    char    *s;
    int     ichg = 0;
    int     i_space_line = 0;

	char	orgfile[256];
	char	tmpfile[256];
	struct stat statbuf;
	char 	key[128];
	char 	value[128];
	char	ver_item[128];
	int 	ifind = 0;

	time_t  tvec_tmp;
	struct  tm *dbuf_tmp;
	char daytime_tmp[64];

    time(&tvec_tmp);
    dbuf_tmp = localtime(&tvec_tmp);

    memset(daytime_tmp, 0, sizeof daytime_tmp);
    sprintf(daytime_tmp, "%-4.4d-%-2.2d-%-2.2d %-2.2d:%-2.2d:%-2.2d",
                dbuf_tmp->tm_year+1900, dbuf_tmp->tm_mon+1, dbuf_tmp->tm_mday,
                dbuf_tmp->tm_hour, dbuf_tmp->tm_min, dbuf_tmp->tm_sec);

	memset(orgfile, 0, sizeof orgfile);
	memset(tmpfile, 0, sizeof tmpfile);

	sprintf(orgfile, "%s/s2over_info.cfg", _homedir);
	sprintf(tmpfile, "%s/s2over_info_%s.cfg", _homedir, _pgmname);

	memset(ver_item, 0, sizeof ver_item);
	sprintf(ver_item, "VERSION_%s", _pgmname);

    if ((fpw = fopen(tmpfile, "w")) == NULL) {
        it_loging("libIT.a(%s): write_ver() file(%s) open error!\n", S2O_DAEMON, tmpfile);
        return(-1);
    }

    if ((fp = fopen(orgfile, "r")) == NULL) {
       if (stat(orgfile, &statbuf) != -1) {
            it_loging("libIT.a(%s): write_ver() file(%s) open error!\n", S2O_DAEMON, orgfile);
            fclose(fpw);
            return(-1);
        }
    } else {
        memset(rbuf, 0, sizeof rbuf);
        while (fgets(rbuf,256,fp) != NULL) {
            if ((rbuf[0] == '#') || (rbuf[0] == '\n')) {
                if (strncmp(rbuf, "#LOGIN_ID", strlen("#LOGIN_ID")) != 0 && strncmp(rbuf, "#SAVE_DATE", strlen("#SAVE_DATE")) != 0 &&
                    strncmp(rbuf, "#ACCESS_IP", strlen( "#ACCESS_IP")) != 0 && strncmp(rbuf, "#USER_IP", strlen( "#USER_IP")) != 0) {
                    memset(chkbuf, 0, sizeof chkbuf);
                    sscanf(rbuf, "%s", chkbuf);
                    if (strlen(chkbuf)  == 0) { /* 두라인 연속 space 라인인 경우 skip */
                        i_space_line++;
                        if (i_space_line < 2) fputs(rbuf, fpw);
                    } else {
                        i_space_line = 0;
                        fputs(rbuf, fpw);
                    }
                }
                continue;
            }
            i_space_line = 0;
		
			memset(chkbuf, 0, sizeof chkbuf);
			strcpy(chkbuf, rbuf);	

            s = (char *)strchr(chkbuf, '=');
			if (s != NULL) {
				memset(value, 0, sizeof value);
				sprintf(s+1, "%s", value);
				*s = '\0';	
				sscanf(chkbuf, "%s", key);
				
				if ( !strcmp(key, ver_item)) {
					ifind = 1;	
					if ( strcmp(value, _version)){
						memset(rbuf, 0, sizeof rbuf);
						sprintf(rbuf, "%s = %s,%s\n", ver_item, _version, daytime_tmp);
            			ichg = 1;
					}
				}
			}	
			fputs(rbuf, fpw);
		}
		fclose(fp);
	}
	if(ifind == 0) {
		memset(rbuf, 0, sizeof rbuf);
		sprintf(rbuf, "%s = %s,%s\n", ver_item, _version, daytime_tmp);
		ichg = 1;
		fputs(rbuf, fpw);
    }

    fclose(fpw);

	if (ichg == 1) {
		/*if (fcopy(tmpfile, orgfile, 0644) < 0) { */
		if (fcopy(tmpfile, orgfile, 0666) < 0) {
			it_loging("libIT.a(%s): write_ver() file(%s) copy fail\n", _pgmname, orgfile);
			unlink(tmpfile);
       		if (stat(tmpfile, &statbuf) != -1) {
    			if ((fpw = fopen(tmpfile, "w")) != NULL) {
					memset(rbuf, 0, sizeof rbuf);
					sprintf(rbuf, "%s = %s,%s\n", ver_item, _version, daytime_tmp);
					fputs(rbuf, fpw);
    				fclose(fpw);
				}
			}
			return -1;
		}
		unlink(tmpfile);
       	if (stat(tmpfile, &statbuf) != -1) {
    		if ((fpw = fopen(tmpfile, "w")) != NULL) {
				memset(rbuf, 0, sizeof rbuf);
				sprintf(rbuf, "%s = %s,%s\n", ver_item, _version, daytime_tmp);
				fputs(rbuf, fpw);
    			fclose(fpw);
			}
		}
		return 1;
	}
	unlink(tmpfile);
    if (stat(tmpfile, &statbuf) != -1) {
    	if ((fpw = fopen(tmpfile, "w")) != NULL) {
			memset(rbuf, 0, sizeof rbuf);
			sprintf(rbuf, "%s = %s,%s\n", ver_item, _version, daytime_tmp);
			fputs(rbuf, fpw);
    		fclose(fpw);
		}
	}
	return(-1);
}
