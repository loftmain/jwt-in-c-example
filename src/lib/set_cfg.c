/*
   $Id: set_cfg.c,v 1.0 2009/06/01 srp Exp $

   Copyright (c) 2009
             i-TOP System Inc.  All rights reserved.

*/

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif
#include "../IT.extern.h"

extern int get_cfg(char *, char *);
extern int it_loging(char *format,...);
extern int fcopy(char *src, char *dest, mode_t pmode);
extern int size_check(char *file, int size);

int set_cfg(ns, ENV1, value1, ENV2, value2)
int	ns;
char *ENV1;     /* ENV  : s2o environment variable. */
char *value1;   /* value: s2o ENV value */
char *ENV2;     /* ENV  : s2o environment variable. */
char *value2;   /* value: s2o ENV value */
{
	FILE 	*fp, *fpw;
    char 	rbuf[256], chkbuf[256];
	char	tmpfile[300], it_home[256];
    char 	*s, *msg;
	int		ichg = 0;

	memset(it_home, 0, sizeof it_home);

	if (get_cfg("IT_HOME", it_home) < 0) {	
	 	it_loging("libIT.a(%s): set_cfg() parameter(IT_HOME) read error!\n", S2O_DAEMON);
		return(-1);
	}

	memset(tmpfile, 0, sizeof tmpfile);
	sprintf(tmpfile, "%s/_IT.cfg.%d", it_home, ns);

    if ((fp = fopen("/etc/IT.cfg", "r")) == NULL) {
	 	it_loging("libIT.a(%s): set_cfg() file(/etc/IT.cfg) open error!\n", S2O_DAEMON);
       	return(-1);
	}

    if ((fpw = fopen(tmpfile, "w")) == NULL) {
	 	it_loging("libIT.a(%s): set_cfg() file(%s) open error!\n", S2O_DAEMON, tmpfile);
    	fclose(fp);
       	return(-1);
	}

    memset(rbuf, 0, sizeof rbuf);
    while (fgets(rbuf,256,fp) != NULL) {
       	/* ignore comment and null line */
       	if ((rbuf[0] == '#') || (rbuf[0] == '\n')) {
			fputs(rbuf, fpw);
          	continue;
		}
       	memset(chkbuf, 0, sizeof chkbuf);
       	sscanf(rbuf, "%s", chkbuf);
       	s = (char *)strchr(chkbuf, '=');
       	if ( s != NULL)
           	*s = '\0';
       	if (strlen(ENV1) > 0 && !strcmp(ENV1, chkbuf)) { 		/* 찾고자하는 ENV 이면. */
			memset(rbuf, 0, sizeof rbuf);
			sprintf(rbuf, "%s = %s\n", ENV1, value1);
			ichg = 1;
		} else if (strlen(ENV2) > 0 && !strcmp(ENV2, chkbuf)) {	/* 찾고자하는 ENV 이면. */
			memset(rbuf, 0, sizeof rbuf);
			sprintf(rbuf, "%s = %s\n", ENV2, value2);
			ichg = 1;
		}
		fputs(rbuf, fpw);
	}  /* while loop end  */
    fclose(fp);
	fclose(fpw);
	if(ichg == 1) {
        if (fcopy(tmpfile, "/etc/IT.cfg", 0644) < 0) {
            it_loging("libIT.a(%s): set_cfg() file(/etc/IT.cfg) copy fail\n", S2O_DAEMON);
			unlink(tmpfile);
            return -1;
        }
		unlink(tmpfile);
		return 1;
	}
	unlink(tmpfile);
    return(-1);
}

int set_cfg2(ns, config, ENV1, value1, ENV2, value2)
int ns;
char *config;	/* file */
char *ENV1;     /* ENV  : s2o environment variable. */
char *value1;   /* value: s2o ENV value */
char *ENV2;     /* ENV  : s2o environment variable. */
char *value2;   /* value: s2o ENV value */
{
	FILE    *fp, *fpw;
	char    rbuf[256], chkbuf[256];
	char    tmpfile[256];
	char    *s, *msg;
	int     ichg = 0;

	memset(tmpfile, 0, sizeof tmpfile);
	sprintf(tmpfile, "%s.%d", config, ns);
	
    if ((fp = fopen(config, "r")) == NULL) {
	 	it_loging("libIT.a(%s): set_cfg2() file(%s) open(read) error!\n", S2O_DAEMON, config);
       	return(-1);
	}

	if ((fpw = fopen(tmpfile, "w")) == NULL) {
		it_loging("libIT.a(%s) set_cfg2() %s open(write) error!\n", S2O_DAEMON, tmpfile);
		fclose(fp);
		return(-1);
	}

	memset(rbuf, 0, sizeof rbuf);
	while (fgets(rbuf,256,fp) != NULL) {
		/* ignore comment and null line */
		if ((rbuf[0] == '#') || (rbuf[0] == '\n')) {
			fputs(rbuf, fpw);
			continue;
		}
		memset(chkbuf, 0, sizeof chkbuf);
		sscanf(rbuf, "%s", chkbuf);
		s = (char *)strchr(chkbuf, '=');

		if ( s != NULL) *s = '\0';

		if (strlen(ENV1) > 0 && !strcmp(ENV1, chkbuf)) {        /* 찾고자하는 ENV 이면. */
			memset(rbuf, 0, sizeof rbuf);
			sprintf(rbuf, "%s = %s\n", ENV1, value1);
			ichg = 1;
		} else if (strlen(ENV2) > 0 && !strcmp(ENV2, chkbuf)) { /* 찾고자하는 ENV 이면. */
			memset(rbuf, 0, sizeof rbuf);
			sprintf(rbuf, "%s = %s\n", ENV2, value2);
			ichg = 1;
		}
		fputs(rbuf, fpw);
    }  /* while loop end  */
    fclose(fp);
    fclose(fpw);
    if(ichg == 1) {
        if (fcopy(tmpfile, config, 0644) < 0) {
            it_loging("libIT.a(%s): set_cfg2() file(%s) copy fail\n", S2O_DAEMON, config);
            unlink(tmpfile);
            return -99;
        }
        unlink(tmpfile);
        return 1;
    }
    unlink(tmpfile);
    return(-1);
}

int set_cfg3(char* program, char *config, char *ENV1, char *value1, char *ENV2, char *value2)
{
	FILE    *fp, *fpw;
	char    rbuf[256], chkbuf[256];
	char    tmpfile[256];
	char    *s, *msg;
	int     ichg1 = 0;
	int     ichg2 = 0;
	struct  stat stbuf;

	memset(tmpfile, 0, sizeof tmpfile);
	sprintf(tmpfile, "%s.%s", config, program);
	
    if ((fp = fopen(config, "r")) == NULL) {
		if (stat(config, &stbuf) >= 0) it_loging("libIT.a(%s): set_cfg3() file(%s) open(read) error!\n", S2O_DAEMON, config);
	}

	if ((fpw = fopen(tmpfile, "w")) == NULL) {
		it_loging("libIT.a(%s): set_cfg3() %s open(write) error!\n", S2O_DAEMON, tmpfile);
		fclose(fp);
		return(-1);
	}

	if (fp != NULL) {
		memset(rbuf, 0, sizeof rbuf);
		while (fgets(rbuf,256,fp) != NULL) {
			/* ignore comment and null line */
			if ((rbuf[0] == '#') || (rbuf[0] == '\n')) {
				fputs(rbuf, fpw);
				continue;
			}
			memset(chkbuf, 0, sizeof chkbuf);
			sscanf(rbuf, "%s", chkbuf);
			s = (char *)strchr(chkbuf, '=');

			if ( s != NULL) *s = '\0';

			if (strlen(ENV1) > 0 && !strcmp(ENV1, chkbuf)) {        /* 찾고자하는 ENV 이면. */
				memset(rbuf, 0, sizeof rbuf);
				sprintf(rbuf, "%s = %s\n", ENV1, value1);
				ichg1 = 1;
			} else if (strlen(ENV2) > 0 && !strcmp(ENV2, chkbuf)) { /* 찾고자하는 ENV 이면. */
				memset(rbuf, 0, sizeof rbuf);
				sprintf(rbuf, "%s = %s\n", ENV2, value2);
				ichg2 = 1;
			}
			fputs(rbuf, fpw);
    	}  /* while loop end  */
    	fclose(fp);
	}

    if (ichg1 == 0 || ichg2 == 0) {
		if (ichg1 == 0 && strlen(ENV1) > 0) {        /* 찾고자하는 ENV 이면. */
			memset(rbuf, 0, sizeof rbuf);
			sprintf(rbuf, "%s = %s\n", ENV1, value1);
			ichg1 = 1;
			fputs(rbuf, fpw);
		}
		if (ichg2 == 0 && strlen(ENV2) > 0) { /* 찾고자하는 ENV 이면. */
			memset(rbuf, 0, sizeof rbuf);
			sprintf(rbuf, "%s = %s\n", ENV2, value2);
			ichg2 = 1;
			fputs(rbuf, fpw);
		}
	}

    fclose(fpw);
    if(ichg1 == 1 || ichg2 == 1) {
        if (fcopy(tmpfile, config, 0644) < 0) {
            it_loging("libIT.a(%s): set_cfg3() file(%s) copy fail\n", S2O_DAEMON, config);
            unlink(tmpfile);
            return -99;
        }
        unlink(tmpfile);
        return 1;
    }
    unlink(tmpfile);
    return(-1);
}

int set_cfgs(int ns, char ENV[10][256], char value[10][256], int itemnum)
{
	FILE 	*fp, *fpw;
    char 	rbuf[256], chkbuf[256];
	char	tmpfile[300], it_home[256];
    char 	*s, *msg;
	int		ichg = 0;
	int		i;
	int		ifind[10] = {0,0,0,0,0,0,0,0,0,0};
	int		iline = 0;
	int		iItemMax = 0;
	int		isnull = 0;

	memset(it_home, 0, sizeof it_home);

	if (get_cfg("IT_HOME", it_home) < 0) {	
	 	it_loging("libIT.a(%s): set_cfgs() parameter(IT_HOME) read error!\n", S2O_DAEMON);
		return(-1);
	}

	memset(tmpfile, 0, sizeof tmpfile);
	sprintf(tmpfile, "%s/_IT.cfg.%d", it_home, ns);

    if ((fp = fopen("/etc/IT.cfg", "r")) == NULL) {
	 	it_loging("libIT.a(%s): set_cfgs() file(/etc/IT.cfg) open error!\n", S2O_DAEMON);
       	return(-1);
	}
    memset(rbuf, 0, sizeof rbuf);
    while (fgets(rbuf,256,fp) != NULL) {
		iline++;
       	memset(chkbuf, 0, sizeof chkbuf);
       	sscanf(rbuf, "%s", chkbuf);
		for(i = 0; i < itemnum; i++) {
       		if (strlen(ENV[i]) > 0 && !strcmp(ENV[i], chkbuf)) { 		/* 찾고자하는 ENV 이면. */
				iItemMax = iline;
				ifind[i] = 1;
			}
		}
	}  /* while loop end  */
    fclose(fp);

    if ((fp = fopen("/etc/IT.cfg", "r")) == NULL) {
	 	it_loging("libIT.a(%s): set_cfgs() file(/etc/IT.cfg) open error!\n", S2O_DAEMON);
       	return(-1);
	}

    if ((fpw = fopen(tmpfile, "w")) == NULL) {
	 	it_loging("libIT.a(%s): set_cfgs() file(%s) open error!\n", S2O_DAEMON, tmpfile);
    	fclose(fp);
       	return(-1);
	}

    memset(rbuf, 0, sizeof rbuf);
	iline = 0;
    while (fgets(rbuf,256,fp) != NULL) {
		iline++;
       	/* ignore comment and null line */
       	if ((rbuf[0] == '#') || (rbuf[0] == '\n')) {
			fputs(rbuf, fpw);
          	continue;
		}
       	memset(chkbuf, 0, sizeof chkbuf);
       	sscanf(rbuf, "%s", chkbuf);
       	s = (char *)strchr(chkbuf, '=');
       	if ( s != NULL)
           	*s = '\0';

		isnull = 0;
		for(i = 0; i < itemnum; i++) {
       		if (strlen(ENV[i]) > 0 && !strcmp(ENV[i], chkbuf)) { 		/* 찾고자하는 ENV 이면. */
				memset(rbuf, 0, sizeof rbuf);
				if (!strcmp(value[i], "_NULL_")) {
					sprintf(rbuf, "\n");
					isnull = 1;
				} else {
					sprintf(rbuf, "%s = %s\n", ENV[i], value[i]);
				}
				ichg = 1;
				ifind[i] = 2;
			}
		}

		if (isnull == 0) fputs(rbuf, fpw);
		
		if ( iItemMax > 0 && iItemMax == iline) {
			for(i = 0; i < itemnum; i++) {
				if (ifind[i] == 0) {
					if (strcmp(value[i], "_NULL_")) {
						sprintf(rbuf, "%s = %s\n", ENV[i], value[i]);
						fputs(rbuf, fpw);
						ichg = 1;
						ifind[i] = 2;
					}
				}
			}
		}
	}  /* while loop end  */
    fclose(fp);

	for(i = 0; i < itemnum; i++) {
		if (ifind[i] == 0) {
			if (strcmp(value[i], "_NULL_")) {
				sprintf(rbuf, "%s = %s\n", ENV[i], value[i]);
				fputs(rbuf, fpw);
				ichg = 1;
			}
		}
	}
	fclose(fpw);

	if(ichg == 1) {
        if (fcopy(tmpfile, "/etc/IT.cfg", 0644) < 0) {
            it_loging("libIT.a(%s): set_cfgs() file(/etc/IT.cfg) copy fail\n", S2O_DAEMON);
			unlink(tmpfile);
            return -1;
        }
		unlink(tmpfile);
		return 1;
	}
	unlink(tmpfile);
    return(-1);
}
