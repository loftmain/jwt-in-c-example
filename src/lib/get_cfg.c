/*
   $Id: get_cfg.c,v 1.7 2002/11/04 srp Exp $

   Copyright (c) 2000, 2001, 2002
             i-TOP System Inc.  All rights reserved.

   2002-11-05
	 * /etc/IT.cfg���� �ش� parameter�� �� ��������.
*/

#include "config.h"
#include <stdio.h>
#include <string.h>
#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif

extern char S2O_DAEMON[64];

extern int it_loging(char *format,...);

int get_cfg(ENV, value)
char *ENV;     /* ENV  : s2o environment variable. */
char *value;   /* value: s2o ENV value */
{
	FILE 	*fp;
    char 	rbuf[256], chkbuf[256], temp_value[256];
    char 	*s, *msg;

    if ((fp = fopen("/etc/IT.cfg", "r")) == NULL) {
       	return(-1);
	}

    memset(rbuf, 0, sizeof rbuf);
    while (fgets(rbuf,256,fp) != NULL) {
       	/* ignore comment and null line */
       	if ((rbuf[0] == '#') || (rbuf[0] == '\n')) continue;

       	memset(chkbuf, 0, sizeof chkbuf);
       	sscanf(rbuf, "%s", chkbuf);
       	s = (char *)strchr(chkbuf, '=');
       	if ( s != NULL)
           	*s = '\0';

       	if (!strcmp(ENV, chkbuf)) { 		/* ã�����ϴ� ENV �̸�. */
          	s = (char *)strchr(rbuf, '=');
          	if ( s != NULL) {
              	memset(temp_value, 0, sizeof temp_value);	/* Not delete */
              	sscanf(s + 1, "%s", temp_value);
				if (strlen(temp_value) <= 0) {
              		fclose(fp);
					return(-1);
				} else
					strcpy(value, temp_value);
              	fclose(fp);
              	return(0);
            } /* �ش� ENV �� ã������, '=' ���ڿ��� ������ ���� string�� ã��.*/
          	else
            	continue;
		} else
         	continue;
	}  /* while loop end  */
    fclose(fp);
    return(-1); /* �ش� ENV�� ��ã�� ��� error return */
}

int get_cfg2(config, ENV, value)
char 	*config;			/* config : syscheck.cfg */
char 	*ENV;     			/* ENV    : s2o environment variable. */
char 	*value;   			/* value  : s2o ENV value */
{
	FILE 	*fp;
    char 	rbuf[256], chkbuf[256], temp_value[256];
    char 	*s, *msg;

    if ((fp = fopen(config, "r")) == NULL) {
       	it_loging("libIT.a(%s): get_cfg2() file(%s) open error!\n", S2O_DAEMON, config);
       	return(-1);
	}

    while (fgets(rbuf, 256, fp) != NULL) {
       	/* ignore comment and null line */
       	if ((rbuf[0] == '#') || (rbuf[0] == '\n'))
          	continue;
		memset(chkbuf, 0x00, sizeof chkbuf);
       	sscanf(rbuf, "%s", chkbuf);
       	s = (char *) strchr(chkbuf, '=');
       	if ( s != NULL)
           	*s = '\0';

       	if (!strcmp(ENV, chkbuf)) { 		/* ã�����ϴ� ENV �̸�. */
          	s = (char *)strchr(rbuf, '=');
          	if ( s != NULL) {
				memset(temp_value, 0x00, sizeof temp_value); /* not delete */
              	sscanf(s + 1, "%s", temp_value);
				if (strlen(temp_value) <= 0) {
              		fclose(fp);
					return(-1);
				} else {
					strcpy(value, temp_value);
				}
              	fclose(fp);
              	return(0);
            } /* �ش� ENV �� ã������, '=' ���ڿ��� ������ ���� string�� ã��.*/
          	else 
            	continue;
		} else 
         	continue;
	}  /* while loop end  */
    fclose(fp);
    return(-1); /* �ش� ENV�� ��ã�� ��� error return */
}

int get_config2(char *config, char *env, char *value)
{
	FILE *fp;
	char rbuf[1025], chkbuf[1025];
	char value_tmp[1025];
	char *s;
	char *a;

	if ((fp=fopen(config, "r")) == NULL) {
       	it_loging("libIT.a(%s): get_config2() file(%s) open error!\n", S2O_DAEMON, config);
		return -1;
	}

	memset(rbuf, 0, sizeof rbuf);
	while (fgets(rbuf, 1024, fp) != NULL) {
		/* ignore comment and null line */
		if ((rbuf[0] == '#') || (rbuf[0] == '\n')){
			memset(rbuf, 0, sizeof rbuf);
			continue;
		}
		memset(chkbuf, 0, sizeof chkbuf);
		sscanf(rbuf, "%s", chkbuf);
		s = (char *)strchr(chkbuf, '=');
		if (s != NULL)
			*s = '\0';

		if (!strcmp(env, chkbuf)) {			/* ã�����ϴ� env�̸� */
			s = (char *)strchr(rbuf, '=');
			if (s != NULL) {
				memset(value_tmp, 0, sizeof value_tmp);
				/*
				sscanf(s + 1, "%s", value_tmp);
				strcpy(value,value_tmp);
				*/
				s = s + 1;
				while(*s == ' '){
					s = s+1;
				}

				a = (char *)strchr(s, '\n');
				*a = '\0';
				strcpy(value, s);
				fclose(fp);
				return 0;
			} /* �ش� env�� ã������, '=' ���ڿ��� ������ ���� string�� ã�� */
			else{
				memset(rbuf, 0, sizeof rbuf);
				continue;
			}
		}
		else{
			memset(rbuf, 0, sizeof rbuf);
			continue;
		}
	} 	/* end while loop */
	fclose(fp);
	return -1;	/* �ش� env�� ��ã�� ��� error return */
}

