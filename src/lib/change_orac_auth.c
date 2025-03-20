/*
   $Id:change_orac_auth.c, v1.0 2020/02/28 srp Exp $

   Copyright (c) 2020
             NewSystech Inc.  All rights reserved.

   2020-02-28
     * IT.orac 일반 사용자로 실행에 다른 권한 변경
*/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pwd.h>
#include "../IT.extern.h"

int change_owner(char* file, char* user)
{
	FILE *pfp;
	struct passwd *u_info;	
	char owner[128];
	char cmdbuf[256];
	char tbuf[512];
    struct  stat stbuf;
	int ret_num; 

	it_loging("libIT.a(%s): change_owner() Changed Owner of file %s to %s.\n", S2O_DAEMON, file, user);

	/*
		struct passwd {
			char    *pw_name;       유저 이름
			char    *pw_passwd;     유저 패스워드
			uid_t   pw_uid;         유저 id
			gid_t   pw_gid;         그룹 id
			char    *pw_gecos;      실제 이름
			char    *pw_dir;        홈 디렉토리
			char    *pw_shell;      shell 프로그램
		};
	*/

	/* struct group *g_info; */
	/* g_info = getgrnam(value); */
	/*
		struct group {
			char    *gr_name;        group name
			char    *gr_passwd;      group password
			gid_t   gr_gid;          group id
			char    **gr_mem;        group members
		};
	*/

	u_info = getpwnam(user);
	if (u_info != NULL) {
		if (chown(file, u_info->pw_uid, u_info->pw_gid) == 0) {
		}
	}

	memset(owner, 0, sizeof owner);
	if (stat(file, &stbuf) == 0) {
		memset(cmdbuf, 0, sizeof cmdbuf);
		sprintf(cmdbuf, "ls -ld %s", file);
		if ((pfp=popen(cmdbuf, "r")) != NULL) {
			while(fgets(tbuf, 511, pfp) != NULL) {
				sscanf(tbuf, "%*s %*s %s", owner);
				if (strcmp(user, owner)) break;
			}
			pclose(pfp);
		}
	}

	if (strcmp(user, owner)) {
		memset(cmdbuf, 0, sizeof cmdbuf);
		sprintf(cmdbuf, "/bin/chown -R %s %s", user, file);
		ret_num = system(cmdbuf);
	}
}

int check_file_perm(char *file, char* user, int iscreate, int isfile)
{
	FILE *pfp;
	FILE *fp;
	char cmds[512];
    char mod[256], owner[256];
	char *ptr;
	char tbuf[512];
    struct  stat stbuf;
	int ret_num;

	if (iscreate == 1) {
		if (isfile == 1) {
			/* file 인 경우 */
    		if (stat(file, &stbuf) != 0) {
				if ((fp = fopen(file, "w")) != NULL){
					fprintf(fp,"");
					fclose(fp);
				} else {
					it_loging("libIT.a(%s): check_file_perm() file(%s) create fail.\n", S2O_DAEMON, file);
				}
			}
		} else if (isfile == 0) {
    		if (stat(file, &stbuf) != 0) {
       			memset(cmds, 0, sizeof cmds);
        		sprintf(cmds, "/bin/mkdir -p %s", file);
        		ret_num = system(cmds);
    		}
		}
	}

	/* 2020-05-07 */
   if (stat(file, &stbuf) != 0) return(0);

    memset(cmds, 0, sizeof cmds);
    sprintf(cmds, "ls -ld %s", file);
    if ((pfp=popen(cmds, "r")) != NULL) {
        while(fgets(tbuf, 511, pfp) != NULL) {
            ptr = (char*) strchr(tbuf, '\n');
            if ( ptr != NULL) *ptr = '\0';
			memset(mod, 0, sizeof mod);
			memset(owner, 0, sizeof owner);
            sscanf(tbuf, "%s %*s %s", mod, owner);

			if ( strcmp(owner, user)) change_owner(file, user);

			/* if ( strcmp(mod, "drwxrwxrwx")) chmod(file, 0777); */
        }
        pclose(pfp);
	} else {
		it_loging("libIT.a(%s): check_file_perm() command(%s) fail.\n", S2O_DAEMON, cmds);
    }

	if ( isfile == 1) chmod(file, 0666); /* 2024/03/22 */
	else chmod(file, 0777); /* 2024/03/22 */

	return 1;
}

int change_orac_auth(char* homedir, char* user)
{
    char work_dir[256];
	char pid_dir[256];
	char file[512], cfg[512], file2[512];
	char tmpbuf[256], tmpbuf2[256];
	int oracle_count, i;
    struct  stat stbuf;
	char cmdbuf[256];
	FILE *pfp;

	/***************************************************/

	/* s2o_home/dump.orac */
    memset(work_dir, 0, sizeof work_dir);
    sprintf(work_dir, _ORAC_DUMP_DIR_ /* %s/dump.orac */, homedir);
	check_file_perm(work_dir, user, 1, 0);

	/* ora_tscheck.dat.bak */
	memset(file, 0, sizeof file);
	sprintf(file, "%s/ora_tscheck.dat", work_dir);
	check_file_perm(file, user, 1, 1); /* 2024/03/22 */
	/*check_file_perm(file, user, 0, 1);*/

	/* ora_tscheck.dat.bak */
	memset(file, 0, sizeof file);
	sprintf(file, "%s/ora_tscheck.dat.bak", work_dir);
	check_file_perm(file, user, 1, 1); /* 2024/03/22 */
	/*check_file_perm(file, user, 0, 1);*/

	/* oracheck_encrypt.cfg */
	memset(file, 0, sizeof file);
	sprintf(file, "%s/oracheck_encrypt.cfg", work_dir);
	check_file_perm(file, user, 1, 1); /* 2024/03/22 */
	/*check_file_perm(file, user, 0, 1);*/

	/***************************************************/

	/* pid dir */
	memset(pid_dir, 0, sizeof pid_dir);
	sprintf(pid_dir, "%s/pid", work_dir);
	check_file_perm(pid_dir, user, 1, 0);

	/* IT.orac.pid */
	memset(file, 0, sizeof file);
	sprintf(file, "%s/IT.orac.pid", pid_dir);
	/* sprintf(file, "%s/pid/IT.orac.pid", homedir);*/
	check_file_perm(file, user, 1, 1);

	memset(file2, 0, sizeof file2);
	sprintf(file2, "%s/pid/IT.orac.pid", homedir);

	if ( stat(file2, &stbuf) == 0) unlink(file2); 

	memset(cmdbuf, 0, sizeof cmdbuf);
	sprintf(cmdbuf, "ln -s %s %s", file, file2);
	system(cmdbuf);
	
	/***************************************************/

	/* IT.log.orac */
	memset(file, 0, sizeof file);
	sprintf(file, "%s/IT.log.orac", homedir);
	check_file_perm(file, user, 1, 1);

	/* IT.log.orac.bak */
	memset(file, 0, sizeof file);
	sprintf(file, "%s/IT.log.orac.bak", homedir);
	check_file_perm(file, user, 1, 1);


	/* oraqm.dat */
	memset(file, 0, sizeof file);
	sprintf(file, "%s/oraqm.dat", homedir);
	check_file_perm(file, user, 1, 1);

	/* oraqm.dat.bak */
	memset(file, 0, sizeof file);
	sprintf(file, "%s/oraqm.dat.bak", homedir);
	check_file_perm(file, user, 1, 1);

	/***************************************************/

	/*
		ORACLE_PSWD? 를 oracle_home/ORACLE_PSWD? ->  orale_home/dump.orac/ORACLE_PSWD?
	*/

	memset(cfg, 0, sizeof cfg);
	sprintf(cfg, "%s/oracheck.cfg", homedir);

   	if (stat(cfg, &stbuf) == 0) {
		memset(tmpbuf, 0, sizeof tmpbuf);
		if (get_cfg2(cfg, "ORACLE_COUNT", tmpbuf) >= 0 ) {
			oracle_count = atoi(tmpbuf);		
			for ( i = 1; i <= oracle_count; i++) {
				memset(tmpbuf, 0, sizeof tmpbuf);
				memset(tmpbuf2, 0, sizeof tmpbuf2);
				sprintf(tmpbuf, "ORACLE_PSWD%d", i);	
				if (get_cfg2(cfg, tmpbuf, tmpbuf2) >= 0) {
					if (!strcmp(tmpbuf, tmpbuf2)) {
						memset(file, 0, sizeof file);
						memset(file2, 0, sizeof file2);
						sprintf(file, "%s/ORACLE_PSWD%d", homedir, i);
						sprintf(file2, "%s/ORACLE_PSWD%d", work_dir, i);

   						if (stat(file2, &stbuf) != 0) {
   							if (stat(file, &stbuf) == 0) {
								/*if (fcopy(file, file2, 0644) < 0) {*/
								if (fcopy(file, file2, 0666) < 0) { /* 2024/03/22 */
									it_loging("libIT.a(%s): change_orac_auth() file(ORACLE_PSWD%d) copy fail\n", S2O_DAEMON, i);
								} else {
									check_file_perm(file2, user, 1, 1);
									it_loging("libIT.a(%s): change_orac_auth() file(ORACLE_PSWD%d) copy success\n", S2O_DAEMON, i);
								}
							}
						}
					}
				}
			}
		}
	}

	/* ha_status_cfg */
	memset(cfg, 0, sizeof cfg);
	sprintf(cfg, "%s/%s", homedir, DEFFILE_HA_STATUS);
   	if (stat(cfg, &stbuf) == 0) {
		chmod(cfg, 0666);  /* 2024/03/22 */
		/*chmod(cfg, 0644);*/
	}
	/***************************************************/
		
}

int delete_dump_orac(char *homedir)
{
    char mkdir[512];
    int dumpps_maxday = 14;
    int ret;
    time_t  curtime = 0;
    char buf[128];
    char dumpdir[256];
    DIR     *dp;
    struct  dirent *dirp;
    char fbuf[512];
    struct  stat s1;
    int dtime = 0;

    curtime = time(0);

    memset(dumpdir, 0, sizeof dumpdir);
    sprintf(dumpdir, _ORAC_DUMP_DIR_ /* %s/dump.orac */, homedir);

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

        dtime = 60 * 60 * 24 * dumpps_maxday;

        if ((curtime - s1.st_mtime) > dtime) {  /* 1분:60, 1일:86400, 7일:604800 */
            it_loging("libIT.a(%s): delete_dump_orac() unlink file(%s) create_day = %d, max_day = %d\n", S2O_DAEMON, fbuf, (curtime - s1.st_mtime)/86400, dumpps_maxday);
            unlink(fbuf);
        } else {
            /*it_loging("libIT.a(%s): delete_dump_orac() file(%s) create_day = %d, max_day = %d\n", S2O_DAEMON, fbuf, (curtime - s1.st_mtime)/86400, dumpps_maxday);*/
        }
    }
    closedir(dp);
}

/***************************************************************/

int change_user_auth(char* homedir, char* user, char* daemon)
{
	char file[512];
	/***************************************************/

	/* s2over_info.cfg */
	memset(file, 0, sizeof file);
	sprintf(file, "%s/s2over_info.cfg", homedir);
	check_file_perm(file, user, 1, 1);
	
	/* s2over_info_IT.orac.cfg */
	memset(file, 0, sizeof file);
	sprintf(file, "%s/s2over_info_%s.cfg", homedir, daemon);
	check_file_perm(file, user, 1, 1); 
}

/***************************************************************/



