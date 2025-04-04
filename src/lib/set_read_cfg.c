#include "config.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#include <stdlib.h>

#include "../IT.extern.h"
#include "../msgid_schd.h"

extern int getitem(int ch, char *src, char *dest, int seqitem);
extern int it_loging(char *format,...);
extern int rtrim(char* sbuf);

int set_secure_file(cfgname)
char *cfgname;		
{
	FILE *fd, *pfd;
	
	struct stat statbuf;
	char tmpstr[300], linebuf[256], dirname[256];
	_llInt_ dirsize;
	char descrip[10], fline[512], pathname[256];
	char flag_size[2], flag_uid[2], flag_gid[2], flag_perms[2], flag_mtime[2];
	char file_maxsize[15], file_maxcount[15], msgcode[10];
	char file_minsize[15];
	int i = 0, j, k;

  	if ((fd = fopen (cfgname, "r")) == NULL) {
      	return (-1);
    }

  	/* read lines off of the file until EOF */
  	while (fgets(fline, 511, fd) != NULL) {
      	/* perl-style comments */
      	if (fline[0] == '#' || isspace (fline[0]) || fline[0] == '\n')
			continue;

		memset(pathname, 0x00, sizeof pathname);
		memset(flag_size, 0x00, sizeof flag_size);
		memset(flag_uid, 0x00, sizeof flag_uid);
		memset(flag_gid, 0x00, sizeof flag_gid);
		memset(flag_perms, 0x00, sizeof flag_perms);
		memset(flag_mtime, 0x00, sizeof flag_mtime);
		memset(file_maxsize, 0x00, sizeof file_maxsize);
		memset(file_maxcount, 0x00, sizeof file_maxcount);
		memset(msgcode, 0x00, sizeof msgcode);
		memset(file_minsize, 0x00, sizeof file_minsize);

		getitem(';', fline, pathname, 1);
		getitem(';', fline, flag_size, 2);
		getitem(';', fline, flag_uid, 3);
		getitem(';', fline, flag_gid, 4);
		getitem(';', fline, flag_perms, 5);
		getitem(';', fline, flag_mtime, 6);
		getitem(';', fline, file_maxsize, 7);
		getitem(';', fline, file_maxcount, 8);
		getitem(';', fline, msgcode, 9);
		getitem(';', fline, file_minsize, 10);

  		/* reallocate array to hold the new entry */
		defSecureFile = (struct def_securefile *) realloc (defSecureFile, (i + 1) * sizeof (struct def_securefile));

		if (defSecureFile == NULL) {
			it_loging("libIT.a(%s): set_secure_file() struct realloc error.\n", S2O_DAEMON);
			fclose(fd);
  			return(-1);
		}

		if (stat(pathname, &statbuf) < 0) {
			defSecureFile[i].type = 1;
			strcpy(defSecureFile[i].file, pathname);	

			defSecureFile[i].size = -1;
			strcpy(defSecureFile[i].flag_size, flag_size);	

			defSecureFile[i].uid = -1;
			strcpy(defSecureFile[i].flag_uid, flag_uid);	

			defSecureFile[i].gid = -1; 
			strcpy(defSecureFile[i].flag_gid, flag_gid);	

			strcpy(defSecureFile[i].perms, "---------");	
			strcpy(defSecureFile[i].flag_perms, flag_perms);	

			defSecureFile[i].mtime = -1;
			strcpy(defSecureFile[i].flag_mtime, flag_mtime);

			rtrim(file_maxsize);
			if (strlen(file_maxsize) == 0) defSecureFile[i].maxsize = 0;
			else sscanf(file_maxsize, "%lld", &defSecureFile[i].maxsize);

			rtrim(file_maxcount);
			if (strlen(file_maxcount) == 0) defSecureFile[i].maxcount = 0;
			else sscanf(file_maxcount, "%d", &defSecureFile[i].maxcount);

			strcpy(defSecureFile[i].msgcode, msgcode);	
			
			rtrim(file_minsize);
			if (strlen(file_minsize) == 0) defSecureFile[i].minsize = 0;
			else sscanf(file_minsize, "%lld", &defSecureFile[i].minsize);

			i++;
			/* 무결성 감시 대상 파일(%s)이 존재하지 않습니다 */
			/*
			wlog(MSG_C_SEC01, STR_C_SEC01_1, pathname);
			*/
			continue;
		}

		/* put permissions into readable form */

		for (j = 0; j < 9; j++) {
			/*
		 	 * test whether permission set
		 	 * using bitwise AND
		 	*/
			if (statbuf.st_mode & octarray[j])
				descrip[j] = perms[j];
			else
				descrip[j] = '-';
		}

		descrip[9] = '\0';		/* make sure we've a string */
		if (!S_ISDIR(statbuf.st_mode)) {
			defSecureFile[i].type = 1;
			defSecureFile[i].size = statbuf.st_size;
		}
		else {
			defSecureFile[i].type = 2;
			memset(tmpstr, 0, sizeof tmpstr);
			sprintf(tmpstr, "du -sk %s", pathname);
			if((pfd = popen(tmpstr, "r")) != NULL) {
				if (fgets(linebuf, 255, pfd) != NULL){
					memset(dirname, 0, sizeof dirname);
					sscanf(linebuf, "%lld %s", &dirsize, dirname);				
					if(!strcmp(dirname, pathname))
						defSecureFile[i].size = dirsize;
					else
						defSecureFile[i].size = -1;
						
				}
				else
					defSecureFile[i].size = -1;
				pclose(pfd);
			} else 
				defSecureFile[i].size = -1;
		}

/*		it_loging("libIT.a(%s): set_secure_file() %s size = %d\n", S2O_DAEMON, pathname, defSecureFile[i].size);*/

		strcpy(defSecureFile[i].file, pathname);	
		strcpy(defSecureFile[i].flag_size, flag_size);	
		defSecureFile[i].uid = statbuf.st_uid;
		strcpy(defSecureFile[i].flag_uid, flag_uid);	
		defSecureFile[i].gid = statbuf.st_gid;
		strcpy(defSecureFile[i].flag_gid, flag_gid);	
		strcpy(defSecureFile[i].perms, descrip);	
		defSecureFile[i].perms[strlen(descrip)] = '\0';
		strcpy(defSecureFile[i].flag_perms, flag_perms);	
		defSecureFile[i].mtime = statbuf.st_mtime;
		strcpy(defSecureFile[i].flag_mtime, flag_mtime);

		rtrim(file_maxsize);
		if (strlen(file_maxsize) == 0) defSecureFile[i].maxsize = 0;
		else sscanf(file_maxsize, "%lld", &defSecureFile[i].maxsize);

		rtrim(file_maxcount);
		if (strlen(file_maxcount) == 0) defSecureFile[i].maxcount = 0;
		else sscanf(file_maxcount, "%d", &defSecureFile[i].maxcount);

		strcpy(defSecureFile[i].msgcode, msgcode);	

		rtrim(file_minsize);
		if (strlen(file_minsize) == 0) defSecureFile[i].minsize = 0;
		else sscanf(file_minsize, "%lld", &defSecureFile[i].minsize);

		i++;

	}		/* end while */

	fclose(fd);

	return(i);
}

/* 무결성 체크 COMMAND 프로그램 FUNCTION */
int set_secure_file_cmd(cfgname)
char *cfgname;		
{
	FILE *fd;
	
	struct stat statbuf;

	char descrip[10], fline[512], pathname[256];
	char uid_name[25], gid_name[25], perms_char[6], level_char[2]; 
	char msgcode[10];
	int  level_int = 0;
	int  i = 0, j, k;

  	if ((fd = fopen (cfgname, "r")) == NULL) 
      	return (-1);

  	/* read lines off of the file until EOF */
  	while (fgets(fline, 511, fd) != NULL) 
	{
      	/* perl-style comments */
      	if (fline[0] == '#' || isspace (fline[0]) || fline[0] == '\n')
			continue;

		memset(pathname, 0x00, sizeof pathname);
		memset(uid_name, 0x00, sizeof uid_name);
		memset(gid_name, 0x00, sizeof gid_name);
		memset(perms_char, 0x00, sizeof perms_char);
		memset(msgcode, 0x00, sizeof msgcode);
		memset(level_char, 0x00, sizeof level_char);

		getitem(';', fline, pathname, 1);
		getitem(';', fline, uid_name, 2);
		getitem(';', fline, gid_name, 3);
		getitem(';', fline, perms_char, 4);	
		getitem(';', fline, msgcode, 5);
		getitem(';', fline, level_char, 6);

  		/* reallocate array to hold the new entry */
		defSecureFileCmd = (struct def_securefile_cmd *) realloc (defSecureFileCmd, (i + 1) * sizeof (struct def_securefile_cmd));

		if (defSecureFileCmd == NULL) 
		{
			it_loging("libIT.a(%s): set_secure_file_cmd() struct realloc error.\n", S2O_DAEMON);
			fclose(fd);
  			return(-1);
		}

		if ((stat(pathname, &statbuf) < 0) || (strlen(defSecureFileCmd[i].perms_char) != 3))
		{
			defSecureFileCmd[i].type = 1; 					/* Base type set 1 */
			strcpy(defSecureFileCmd[i].file, pathname);	
			defSecureFileCmd[i].uid = -1;
			strcpy(defSecureFileCmd[i].uid_name, uid_name);	
			defSecureFileCmd[i].gid = -1; 
			strcpy(defSecureFileCmd[i].gid_name, gid_name);	
			strcpy(defSecureFileCmd[i].perms, "---------");	
			strcpy(defSecureFileCmd[i].perms_char, perms_char);	
			strcpy(defSecureFileCmd[i].msgcode, msgcode);	
			rtrim(level_char);
			defSecureFileCmd[i].level_int = atoi(level_char);	

			i++;
			/* 무결성 감시 Command 대상 설정 파일/디렉토리(%s)가 존재하지 않거나 모드 설정이 잘못되었습니다 */
			/*
			wlog(MSG_C_SEC11, STR_C_SEC11_1, pathname);
			it_loging("libIT.a(%s): set_secure_file_cmd: Not found file or directory (%s).\n", S2O_DAEMON, pathname);
			*/	
			continue;
		} 

		/* put permissions into readable form */

		for (j = 0; j < 9; j++) 
		{
			/* test whether permission set using bitwise AND */
			if (statbuf.st_mode & octarray[j])
				descrip[j] = perms[j];
			else
				descrip[j] = '-';
		}
		descrip[9] = '\0';		/* make sure we've a string */

		if (!S_ISDIR(statbuf.st_mode)) 
			defSecureFileCmd[i].type = 1;  /* type is file */
		else 
			defSecureFileCmd[i].type = 2; 	/* type is directory */

		strcpy(defSecureFileCmd[i].file, pathname);	
		defSecureFileCmd[i].uid = statbuf.st_uid;
		strcpy(defSecureFileCmd[i].uid_name, uid_name);	
		defSecureFileCmd[i].gid = statbuf.st_gid;
		strcpy(defSecureFileCmd[i].gid_name, gid_name);	
		/* 이부분 수정이 필요함 */
		strcpy(defSecureFileCmd[i].perms, descrip);	
		defSecureFileCmd[i].perms[strlen(descrip)] = '\0';
		strcpy(defSecureFileCmd[i].perms_char, perms_char);	
		strcpy(defSecureFileCmd[i].msgcode, msgcode);	
		rtrim(level_char);
		defSecureFileCmd[i].level_int = atoi(level_char);	

		i++;
	}		/* end while */
	fclose(fd);

	for (k = 0; k < i; k++) 
		it_loging("libIT.a(%s): set_secure_file_cmd : %s, uid: %d(%s), gid:%d(%s), perms: %s(%s), type:%d, level:%d\n", S2O_DAEMON, defSecureFileCmd[k].file, defSecureFileCmd[k].uid, defSecureFileCmd[k].uid_name, defSecureFileCmd[k].gid, defSecureFileCmd[k].gid_name, defSecureFileCmd[k].perms, defSecureFileCmd[k].perms_char, defSecureFileCmd[k].type, defSecureFileCmd[k].level_int);

	return(i);
}
