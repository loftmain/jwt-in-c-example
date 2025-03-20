/*
 * Copyright (c) 2000, 2001, ITOP SYSTEM Inc. All rights reserved.
 *
 * NAME
 *      dump_ps.c - process list dump.
 *
 * MODIFIED     (MM/DD/YYYY)
 *
 */
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "../msgid_schd.h"

#if defined(LINUX)
/* CentOS오류로 수정.
#define PSC		"ps -w -eo user,pid,ppid,pcpu,vsz,rss,tty,s,stime,time,args|sort +3 -r|egrep -v 'sort +3|ps -w'"
#define PSM		"ps -w -eo user,pid,ppid,pcpu,vsz,rss,tty,s,stime,time,args|sort +4 -r|egrep -v 'sort +4|ps -w'"
*/
#define PSC		"ps -w -eo user,pid,ppid,pcpu,vsz,rss,tty,s,stime,time,args|sort -k4 -r|egrep -v 'sort -k4|ps -w'"
#define PSM		"ps -w -eo user,pid,ppid,pcpu,vsz,rss,tty,s,stime,time,args|sort -k5 -r|egrep -v 'sort -k5|ps -w'"
#elif defined(AIX)
#define PSC		"/usr/bin/ps -eo user,pid,ppid,pcpu,vsz,vsz,tty,state,etime,time,args|sort +3 -r|egrep -v 'sort +3|ps -eo'"
#define PSM		"/usr/bin/ps -eo user,pid,ppid,pcpu,vsz,vsz,tty,state,etime,time,args|sort +4 -r|egrep -v 'sort +4|ps -eo'"
#elif defined(HPUX)
#define PSC		"ps -eo user,pid,ppid,pcpu,vsz,sz,tty,state,stime,time,args|sort +3 -r|egrep -v 'sort +3|ps -eo'"
#define PSM		"ps -eo user,pid,ppid,pcpu,vsz,sz,tty,state,stime,time,args|sort +4 -r|egrep -v 'sort +4|ps -eo'"
#elif defined(NCRUX)
#define PSC		"/sbin/ps -eo user,pid,ppid,pcpu,vsz,nice,tty,state,stime,time,args|sort +3 -r|egrep -v 'sort +3|ps -eo'"
#define PSM		"/sbin/ps -eo user,pid,ppid,pcpu,vsz,nice,tty,state,stime,time,args|sort +4 -r|egrep -v 'sort +4|ps -eo'"
#elif defined(SUN2)
#define PSC		"ps -eo user,pid,ppid,pcpu,vsz,rss,tty,s,stime,time,args|sort +3 -r|egrep -v 'sort +3|ps -eo'"
#define PSM		"ps -eo user,pid,ppid,pcpu,vsz,rss,tty,s,stime,time,args|sort +4 -r|egrep -v 'sort +4|ps -eo'"
#else
#define PSC		"/bin/ps -eo user,pid,ppid,vsz,rss,tty,s,stime,time,args|sort +3 -r|egrep -v 'sort +3|ps -eo'"
#define PSM		"/bin/ps -eo user,pid,ppid,vsz,rss,tty,s,stime,time,args|sort +3 -r|egrep -v 'sort +3|ps -eo'"
#endif

#define TRUE    1
#define FALSE   0


extern char S2O_DAEMON[64];

extern int get_cfg2(char* config, char* ENV, char* value);
extern int it_loging(char *format,...);
extern int rtrim(char* sbuf);
extern int wlog(char *mid, char *msg,...);
extern int get_cfg(char* ENV, char* value);

int dump_clear(char* mode, char *ithome)
{
	char mkdir[512];
	int dumpps_maxday = 21;
	int ret;
	time_t  curtime = 0;
	char buf[128];
	char dumpdir[256];
	DIR 	*dp;
	struct 	dirent *dirp;
	char fbuf[512];
	struct  stat s1;
	int dtype = 0;
	int dtime = 0;
	char *ptr;
	int i;
	char tmpfile[256];
	char dumptype[][10] = {"cpu", "cio", "swapu", "pgs", "mem", "ppg", "que", "top", "topm", "psc", "swap", "prs", ""};

	curtime = time(0);

	memset(buf, 0, sizeof buf);
	get_cfg("IT_DUMP_PS_MAXDAY", buf);

	if ( strlen(buf) > 0) dumpps_maxday = atoi(buf);

	if ( dumpps_maxday < 5 ) dumpps_maxday = 5;
	else if ( dumpps_maxday > 60) dumpps_maxday = 60;

	/*if (strlen(mode) == 0) it_loging("libIT.a(%s): dump_clear() unlink max_day = %d\n", S2O_DAEMON, dumpps_maxday);*/
	it_loging("libIT.a(%s): dump_clear() unlink max_day = %d\n", S2O_DAEMON, dumpps_maxday);

	memset(dumpdir, 0, sizeof dumpdir);
	sprintf(dumpdir, "%s/dump", ithome);

	if ((dp = opendir(dumpdir)) == NULL) {
		sprintf(mkdir, "/bin/mkdir -p %s", dumpdir);
		ret=system(mkdir);
		dp = opendir(dumpdir);
	}

	while ((dirp = readdir(dp)) != NULL) {
		if (!strcmp(dirp->d_name,".") || !strcmp(dirp->d_name,".."))
			continue;

		sprintf(fbuf, "%s/%s", dumpdir, dirp->d_name);
		if (stat(fbuf, &s1) < 0)
			continue;

		dtype = 0;

		memset(tmpfile, 0, sizeof tmpfile);
		strcpy(tmpfile, dirp->d_name);

		ptr = (char*) strrchr(tmpfile, '.');

		if (ptr != NULL) {
			if ( !strcmp(ptr, ".lst")) {
				ptr = (char*) strchr(tmpfile, '_');
				if (ptr != NULL) {
					*ptr = '\0';
					i = 0;
					while(strcmp(dumptype[i], "")) {
						if ( !strcmp(tmpfile, dumptype[i])) {
							dtype = 1;
							break;
						}
						i++;
					}
				}
			} else if ( !strcmp(ptr, ".gz")) {
				ptr = (char*) strstr(tmpfile, ".lst.gz");
				if (ptr != NULL) {
					ptr = (char*) strchr(tmpfile, '_');
					if (ptr != NULL) {
						*ptr = '\0';
						i = 0;
						while(strcmp(dumptype[i], "")) {
							if ( !strcmp(tmpfile, dumptype[i])) {
								dtype = 1;
								break;
							}
							i++;
						}
					}
				}
			}
		}

		/* 
			dump_ps로 생성된 파일과 기타 생성된 파일을 구분함
			dump_ps 생성된 파일 : 21일 ( 5 ~ 60 )
			기타 생성된 파일 : 7일
		*/

#if defined(__DEL__)
		if ( dtype == 1) {
			dtime = 60 * 60 * 24 * dumpps_maxday;
			/* dtime = 1209600;*/ /* 60 * 60 * 24 * 14; */
			/* dtime = 1814400;*/ /* 60 * 60 * 24 * 21; */
		} else dtime = 604800;  /* 60 * 60 * 24 * 7; */
#endif
		dtime = 60 * 60 * 24 * dumpps_maxday;

		if ((curtime - s1.st_mtime) > dtime) {	/* 1분:60, 1일:86400, 7일:604800 */
			it_loging("libIT.a(%s): dump_clear() unlink file(%s) create_day = %d, max_day = %d\n", S2O_DAEMON, fbuf, (curtime - s1.st_mtime)/86400, dumpps_maxday);
			unlink(fbuf);
		} else {
			/*it_loging("libIT.a(%s): dump_clear() file(%s) create_day = %d, max_day = %d\n", S2O_DAEMON, fbuf, (curtime - s1.st_mtime)/86400, dumpps_maxday);*/
		}
	}
	closedir(dp);
}

int dump_ps(char *mode, char *ithome, char *daytime)
{
	FILE	*pfp, *fp;
	char syscfg[128];
	
  	char tbuf[1024], cmdbuf[300], fbuf[15000], mkdir[256], cfg[256]; 
	char top_flag_cfg[256], top_flag_daytime[13];
	char user[48], pcpu[12], tty[12];
	char pid[12], ppid[12], vsz[12], rss[12];
	/*char pid[1024], ppid[1024], vsz[1024], rss[1024];*/
    char state[12], etime[24], etime_tmp[5], cputime[24], args[512];
	int	linecnt = 0, topskipflag = FALSE;
	int TOP_PCU = 10;
	char *ptr;
	int ret_num;

#if defined(HPUX)
	putenv("UNIX95=XPG4");
#endif

	sprintf(syscfg, "%s/syscheck.cfg", ithome);
	memset(cmdbuf, 0, sizeof cmdbuf);
	if ( !strcmp(mode, "topm")) 
		get_cfg2(syscfg, "TOP_PCU_MEM", cmdbuf); 
	else
		get_cfg2(syscfg, "TOP_PCU", cmdbuf); 

	if (strlen(cmdbuf) > 0)
		TOP_PCU = atoi(cmdbuf);

	/* 2019-08-22 */
	dump_clear(mode, ithome);

	/* 
	// TOP 10 PROCESS 정보를 같은 시간데 같은 정보를 보내지 않기 위한 FLAG CHECK 
	*/

	sprintf(top_flag_cfg, "%s/dump/top_flag.cfg", ithome);

	if (!strcmp(mode, "cpu") || !strcmp(mode, "swapu") || !strcmp(mode, "top") || !strcmp(mode, "pgs") || !strcmp(mode, "topm")) { /* pgs pagescan */
  		if ((fp = fopen(top_flag_cfg, "r")) == NULL) {
			fp = fopen(top_flag_cfg, "w");
			/*fprintf(fp, daytime);*/
			fputs(daytime, fp);
			fclose(fp);
		} else {
			while ((fgets(fbuf, 255, fp)) != NULL) {
				memset(top_flag_daytime, 0x00, sizeof top_flag_daytime);
				sscanf(fbuf, "%s", top_flag_daytime);
			}
			fclose(fp);
			if (!strcmp(top_flag_daytime, daytime)) {
				topskipflag = TRUE;
			} else {
				fp = fopen(top_flag_cfg, "w");
				/*fprintf(fp, daytime);*/
				fputs(daytime, fp);
				fclose(fp);
			}
		}
	} else{
		topskipflag = TRUE;
	}

	sprintf(cfg, "%s/dump/%s_%s.lst", ithome, mode, daytime);

  	if ((fp = fopen(cfg, "w")) == NULL) {
		it_loging("libIT.a(%s): dump_ps() write file(%s) open error!\n", S2O_DAEMON, cfg);
		return(-1);
  	}
	memset(cmdbuf, 0, sizeof cmdbuf);
	if (!strcmp(mode, "mem") || !strcmp(mode, "pgs") || !strcmp(mode, "topm"))
		sprintf(cmdbuf, "%s", PSM);
	else
		sprintf(cmdbuf, "%s", PSC);

  	if ((pfp = popen(cmdbuf, "r")) == NULL) {
      	it_loging("libIT.a(%s): dump_ps() pipe open error.\n", S2O_DAEMON);
		fclose(fp); /* 추가*/
      	return (-1);
    }

	while (fgets(fbuf, 14998, pfp) != NULL) {
		/*fprintf(fp, fbuf);*/
		fputs(fbuf, fp);

		/* ps 명령어 header 제거 */
		ptr = (char*) strstr(fbuf, "COMMAND");
		if ( ptr != NULL) continue;

		/* TOP 10 PROCESS 서버 저장은 cpu, swap 만 수행 */
		if (!topskipflag) {
			if (linecnt < TOP_PCU) {
				/*	
				sscanf(fbuf, "%*s %s %s %*s %s %s", pid, ppid, vsz, rss);
				if (!isdigit(pid[0]) || !isdigit(ppid[0]) || !isdigit(vsz[0]) || !isdigit(rss[0])) continue;
				*/

				memset(args, 0x00, sizeof args);
				sscanf(fbuf, "%s %s %s %s %s %s %s %s %s %s %511c", user, pid, ppid, pcpu, vsz, rss, tty, state, etime, cputime, args);
#if defined(HPUX)
				if (strlen(etime)==3) {
					sscanf(fbuf, "%s %s %s %s %s %s %s %s %s %s %s %511c", user, pid, ppid, pcpu, vsz, rss, tty, state, etime, etime_tmp, cputime, args);
					strcat(etime, etime_tmp);
				}
#endif
				sprintf(tbuf, "%s %s %s %s %s %s %s %s %s %s %s", user, pid, ppid, pcpu, vsz, rss, tty, state, etime, cputime, args);
				rtrim(args);

				if (!strcmp(mode, "topm")) wlog(MSG_P_TOP07, "%s %s", daytime, tbuf);
				else wlog(MSG_P_TOP05, "%s %s", daytime, tbuf);
			}
		}
		linecnt++;
	}
	pclose(pfp);
	fclose(fp);

	memset(cmdbuf, 0, sizeof cmdbuf);
	sprintf(cmdbuf, "gzip -f %s", cfg);
	ret_num = system(cmdbuf);

    return(0);
}
