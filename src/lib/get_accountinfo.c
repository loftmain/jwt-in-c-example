/*
	* 2021-11-01
		- os user 정보를 모니터링하기 위해 사용
		- 계정 암호 관련 확인 명령어 : chage -l 계정
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
/*#include "../accountinfo.h" */
#include "config.h"
#include "../IT.extern.h"

#if defined(LINUX)
    char defaultusers[][16]={"daemon", "bin", "sys", "adm", "listen", "nobody", "nobody4", "noaccess", "diag",
                            "listen", "operator", "games", "gopher","news", "sync", "shutdown", "halt", "operator", ""};
#elif defined(HPUX)
    char defaultusers[][16]={"bin", "uucp", "mail", "open", "help", "games", "demo", "maint", "finger",
                            "toor", "system", "who", "ingress", "lp", "nuucp", "visitor", "manager", "telnet",
                            "date", "uptime", "finger", "sync", "play", "daemon", "guest","nobody", "nobody4", "noaccess","tftp",""};
#elif defined(AIX)
    char defaultusers[][16]={"bin", "uucp", "mail", "open", "help", "games", "demo", "maint", "finger",
                            "toor", "system", "who", "ingress", "lp", "nuucp", "visitor", "manager", "telnet",
                            "date", "uptime", "finger", "sync", "play", "daemon", "guest","nobody", "nobody4",
                            "noaccess", "invscout", "snapp", ""};
#else
    char defaultusers[][16]={"bin", "uucp", "mail", "open", "help", "games", "demo", "maint", "finger",
                            "toor", "system", "who", "ingress", "lp", "nuucp", "visitor", "manager", "telnet",
                            "date", "uptime", "finger", "sync", "play", "daemon", "guest","nobody", "nobody4", "noaccess",""};
#endif

int get_shadow_chgtime(char *src, char* dest, int *_time_diff);

int get_accountinfo()
{
	FILE *pfp, *fd;
	char tbuf[1024], tbuf2[1024], tbuf3[1024], user[128], password[256], pass[256], uid[16], gid[16], home[256], shell[64];
	char buf[128], buf2[128];
	char description[512];
	char expire_period[30];
	char file[256];
	char last_pwchg[20];
	int i, default_user;
	char *ptr;
	int mode = 0;
	struct stat stbuf;
	int user_num = 0;
	int tmpnum = 0;
	int maxage = -1;
	int compat = 0;
	int trusted = -1;
	
	/*accounts = (struct account_struct *) malloc(sizeof(struct account_struct));*/

#if defined(HPUX) || defined(SUN2)
	if (stat("/etc/nsswitch.conf", &stbuf) == 0) { /* 파일이 존재 할 경우 */
		if ((pfp=popen("grep passwd: /etc/nsswitch.conf", "r")) != NULL) {
			while(fgets(tbuf, 1023, pfp) != NULL) {
				if(tbuf[strlen(tbuf)-1] =='\n') tbuf[strlen(tbuf)-1] = '\0';
				memset(buf, 0, sizeof buf);
				memset(buf2, 0, sizeof buf2);
				sscanf(tbuf, "%s %s", buf, buf2);
				if (!strcmp(buf,"passwd:") && !strcmp(buf2, "compat")) compat = 1;
			}
			pclose(pfp);
		}
	}
#endif

	/* 계정 list 생성 */
	if ((fd=fopen("/etc/passwd", "r")) != NULL) {
		while(fgets(tbuf, 1023, fd) != NULL) {
			tbuf[strlen(tbuf)] = '\0';
			if(tbuf[strlen(tbuf)-2]=='\n' || tbuf[strlen(tbuf)-2]=='\r') tbuf[strlen(tbuf)-2] = '\0';
			if(tbuf[strlen(tbuf)-1]=='\n' || tbuf[strlen(tbuf)-1]=='\r') tbuf[strlen(tbuf)-1] = '\0';
			if(tbuf[strlen(tbuf)]=='\n' || tbuf[strlen(tbuf)]=='\r') tbuf[strlen(tbuf)] = '\0';

			ltrim(tbuf);
			rtrim(tbuf);
			memset(user, 0, sizeof user);
			memset(password, 0, sizeof password);
			memset(uid, 0, sizeof uid);
			memset(gid, 0, sizeof gid);
			memset(description, 0, sizeof description);
			memset(home, 0, sizeof home);
			memset(shell, 0, sizeof shell);

			ptr = (char*) strchr(tbuf, ':');
			if (ptr != NULL) {
				memset(tbuf2, 0, sizeof tbuf2);
				strcpy(tbuf2, ptr+1);
				*ptr = '\0';
				strcpy(user, tbuf);
				ptr = (char*) strchr(tbuf2, ':');
				if (ptr != NULL) {
					memset(tbuf, 0, sizeof tbuf);
					strcpy(tbuf, ptr+1);
					*ptr = '\0';
					strcpy(pass, tbuf2);
					ptr = (char*) strchr(tbuf, ':');
					if (ptr != NULL) {
						memset(tbuf2, 0, sizeof tbuf2);
						strcpy(tbuf2, ptr+1);
						*ptr = '\0';
						strcpy(uid, tbuf);
						ptr = (char*) strchr(tbuf2, ':');
						if (ptr != NULL) {
							memset(tbuf, 0, sizeof tbuf);
							strcpy(tbuf, ptr+1);
							*ptr = '\0';
							strcpy(gid, tbuf2);
							ptr = (char*) strchr(tbuf, ':');
							if (ptr != NULL) {
								memset(tbuf2, 0, sizeof tbuf2);
								strcpy(tbuf2, ptr+1);
								*ptr = '\0';
								strcpy(description, tbuf);
								ptr = (char*) strchr(tbuf2, ':');
								if (ptr != NULL) {
									memset(tbuf, 0, sizeof tbuf);
									strcpy(tbuf, ptr+1);
									*ptr = '\0';
									strcpy(home, tbuf2);
									ptr = (char*) strchr(tbuf, ':');
									if (ptr != NULL) *ptr = '\0';
									strcpy(shell, tbuf);
								} else {
									continue;
								}
							} else {
								continue;
							}
						} else {
							continue;
						}
					} else {
						continue;

					}
				} else {
					continue;
				}
			} else {
				continue;
			}

			i = 0;
			default_user = 0;
			while (strcmp(defaultusers[i],"")) {
				if (!strcmp(defaultusers[i], user)) {
					default_user = 1;
				}
				i++;
			}

			accounts = (struct account_struct *)realloc(accounts, (user_num + 1) * sizeof(struct account_struct));

			strcpy(accounts[user_num].name, user);
			strcpy(accounts[user_num].uid, uid);
			strcpy(accounts[user_num].gid, gid);
			strcpy(accounts[user_num].description, description);
			strcpy(accounts[user_num].home, home);
			strcpy(accounts[user_num].shell, shell);
			accounts[user_num].default_user = default_user;
			accounts[user_num].LOCK = 0;
			accounts[user_num].salt_fail = 0;
			strcpy(accounts[user_num].last_time, "");
			strcpy(accounts[user_num].last_host, "");
			strcpy(accounts[user_num].last_pwchg, "");
			strcpy(accounts[user_num].last_loginget, "");
			strcpy(accounts[user_num].status, "");
			strcpy(accounts[user_num].expire_period, "");
			strcpy(accounts[user_num].expire_date, "");
			strcpy(accounts[user_num].expire_time, "");
			accounts[user_num].remain_expire = -1;
			accounts[user_num].maxday = -1;
			accounts[user_num].sort_find = 0;
			
#if defined(HPUX)
			strcpy(accounts[user_num].password, pass);
			if(strlen(pass) == 0)
				accounts[user_num].NOPASS = 1;
			else
				accounts[user_num].NOPASS = 0;
#else

			if (stat("/etc/shadow", &stbuf) == 0) { /* 파일이 존재 할 경우 */
				strcpy(accounts[user_num].password, "");
				accounts[user_num].NOPASS = 0;
			} else {
				strcpy(accounts[user_num].password, pass);
				if(strlen(pass) == 0)
					accounts[user_num].NOPASS = 1;
				else
					accounts[user_num].NOPASS = 0;
			}
#endif
			accounts[user_num].passerr = 0;
			user_num++;
		}
		fclose(fd);
	}

#if defined(AIX)
	/* local 테스트 장비 itops119 (192.168.0.119) */
	/* 계정 list 생성 */
	/* 패스워드 만료일이 존재하지 않는 관계로 마지막 패스워드 변경일+최대패스워드사용가능일(주) 계산 필요 */
	/* 
		/etc/security/passwd
			test01:
				password = Ydiidid
				lastupdate = 1637211170
				flag = 
		/etc/security/user
			default:
				admin = false
				minage = 0
				maxage = 8
	*/
	
    if ((fd = fopen("/etc/security/passwd", "r")) != NULL) 
	{
        while(fgets(tbuf, 1023, fd) != NULL) {
            if(tbuf[0] == '*' || tbuf[0] == '\n') continue;
            memset(buf, 0, sizeof buf);
            memset(buf2, 0, sizeof buf2);
            memset(password, 0, sizeof password);
            sscanf(tbuf, "%s %s %s", buf, buf2, password);

            if(strlen(buf2) == 0 && buf[strlen(buf)-1] == ':') {
                memset(user, 0, sizeof user);
                strncpy(user, buf, strlen(buf)-1);
            } else if(!strcmp(buf, "password")  && !strcmp(buf2, "=")) {
                for(i = 0; i < user_num; i++) {
                    if(!strcmp(accounts[i].name, user)) {
                        strcpy(accounts[i].password, password);
                        break;
                    }
                }
            } else if(!strcmp(buf, "lastupdate")  && !strcmp(buf2, "=")) {
                for(i = 0; i < user_num; i++) {
                    if(!strcmp(accounts[i].name, user)) {
                        if(strlen(password) > 0) {
							strcpy(accounts[i].expire_period, password);
                            memset(buf, 0, sizeof buf);
                            epoch2date(atoi(password), buf);
                            /*sprintf(buf, "%s", epoch2date(atoi(password)));*/
                            strcpy(accounts[i].last_pwchg, buf);
                        } else {
                            strcpy(accounts[i].last_pwchg, "");
                        }
                        break;
                    }
                }
            }
        }
        fclose(fd);
    }

	/*
	lastupdate

	1)
	pwdadm -q alpha

	alpha:
	lastupdate = 1265940457
	flags = ADMCHG

	2)
	pwdadm -q alpha |grep lastupdate
	lastupdate = 1265940457

	3)
	lssec -f /etc/security/passwd -s alpha lastupdate
	alpha lastupdate = 1265940457
	*/

	/*
	maxage
	1)
	lssec -f /etc/security/user -s default -a maxage
	default maxage = 12
	*/

    if ((fd = fopen("/etc/security/user", "r")) != NULL) {
        while(fgets(tbuf, 1023, fd) != NULL) {
            if(tbuf[0] == '*' || tbuf[0] == '\n') continue;
            memset(buf, 0, sizeof buf);
            memset(buf2, 0, sizeof buf2);
            memset(password, 0, sizeof password);
            sscanf(tbuf, "%s %s %s", buf, buf2, password);

            if (strlen(buf2) == 0 && buf[strlen(buf)-1] == ':') {
                memset(user, 0, sizeof user);
                strncpy(user, buf, strlen(buf)-1);
            } else if(!strcmp(buf, "expires")  && !strcmp(buf2, "=")) {
                if (!strcmp(password , "0101000070"))  { /* LOCK 된 경우 */
                    for(i = 0; i < user_num; i++) {
                        if(!strcmp(accounts[i].name, user)) {
                            accounts[i].LOCK = 1;
                            break;
                        }
                    }
                }
            } else if(!strcmp(buf, "maxage")  && !strcmp(buf2, "=")) {
				if (!strcmp(user, "default")) {
					maxage = atoi(password);	
					 it_loging("libIT.a(%s): get_accountinfo() /etc/security/user file read maxage = %d\n", S2O_DAEMON, maxage);
				}
            } else if(!strcmp(buf, "account_locked")  && !strcmp(buf2, "=")) {
                if (!strcmp(password , "true"))  { /* LOCK 된 경우 */
                    for(i = 0; i < user_num; i++) {
                        if(!strcmp(accounts[i].name, user)) {
                            accounts[i].LOCK = 1;
                            break;
                        }
                    }
                }
            } else if(!strcmp(buf, "auth1")  && !strcmp(buf2, "=") && !strcmp(password, "NONE")) {
                for(i = 0; i < user_num; i++) {
                    if(!strcmp(accounts[i].name, user)) {
                        accounts[i].NOPASS = 1;
                        break;
                    }
                }
            }
        }
        fclose(fd);
    }

	if ( maxage < 1) {
		/*
		maxage
		1)
		lssec -f /etc/security/user -s default -a maxage
		default maxage = 12
		*/

		if ((pfp=popen("lssec -f /etc/security/user -s default -a maxage", "r")) != NULL) {
			while(fgets(tbuf, 1023, pfp) != NULL) {
				memset(buf, 0, sizeof buf);
				memset(buf2, 0, sizeof buf2);
            	sscanf(tbuf, "%*s %s %*s %s", buf, buf2);
				if (!strcmp(buf, "maxage")) {
					maxage = atoi(buf2);
					it_loging("libIT.a(%s): get_accountinfo() lssec -f /etc/security/user -s default -a maxage = %d\n", S2O_DAEMON, maxage);
				}
			}
			pclose(pfp);
		}
		if (maxage < 1) {
			maxage = 12;
			it_loging("libIT.a(%s): get_accountinfo() temporary maxage = %d\n", S2O_DAEMON, maxage);
		}
	}

	for(i = 0; i < user_num; i++) {
		if ( strlen(accounts[i].expire_period) > 0) {
			tmpnum = atoi(accounts[i].expire_period) + maxage * 7 * 86400; /* 만료일 maxage는 주단위임 */
			memset(buf, 0, sizeof buf);
			epoch2date(tmpnum, buf);
			/*sprintf(buf, "%s", epoch2date(tmpnum));*/
			strcpy(accounts[i].expire_time, buf);
			strcpy(accounts[i].expire_date, accounts[i].expire_time);
			accounts[i].expire_date[8] = '\0';
			accounts[i].remain_expire = tmpnum - time(0);
			accounts[i].maxday = maxage * 7;
    	}
	}
#elif defined(HPUX)
	/* local 테스트 장비 itops119 (192.168.0.119) */
    mode = -1; /* 0: trust mode, 1: shadow mode, 2: password mode */
    trusted = 1;

	for(i = 0; i < user_num; i++) {
		if (!strcmp(accounts[i].name, "root")) {
			if(!strcmp(accounts[i].password, "x")) {
				mode = 1;       /* shadow mode */
				trusted = 0;
			} else if(!strcmp(accounts[i].password, "*")) {
				mode = 0;
			} else if (strlen(accounts[i].password) > 1) { 
				mode = 2;
			} 
			break;
		}
	}

	if ( mode < 0) {
		mode = 0;
    	for(i = 0; i < user_num; i++) {
       	 if(!strcmp(accounts[i].password, "x")) {
       	     mode = 1;       /* shadow mode */
       	     trusted = 0;
            break;
        } else if (strlen(accounts[i].password) > 1) { /* trusted mode */
            mode = 2;
            break;
        } /* trusted mode */
    }
	}

    if (mode < 2) {
        for(i = 0; i < user_num; i++) {
            strcpy(accounts[i].password, "");
        }
        if (mode == 1) { /* shadow mode */
            /*if ((pfp=popen("cat /etc/shadow | awk -F: '{print $1,$2,$3}'", "r")) != NULL) {*/
            /*if ((pfp=popen("cat /etc/shadow", "r")) != NULL) {*/
            if ((pfp=fopen("/etc/shadow", "r")) != NULL) {
                while(fgets(tbuf, 1023, pfp) != NULL) {
					/* 1.사용자명:2.패스워드:3.패스워드파일최종수정일:4.패스워드변경최소일:5.패스워드변경최대일:6.패스워드만료경고기간:7.패스워드파기기간:8.계정만료기간:9.예약필드 */
                    memset(user, 0, sizeof user);
                    memset(password, 0, sizeof password);
                    memset(buf, 0, sizeof buf);
					memset(buf2, 0, sizeof buf2);
					memset(expire_period, 0, sizeof expire_period);
                    /*sscanf(tbuf, "%s %s %s", user, password, buf);*/
                    getitem(':', tbuf, user, 1);
                    getitem(':', tbuf, password, 2);
                    getitem(':', tbuf, expire_period, 3);
                    getitem(':', tbuf, buf, 5);
					sscanf(buf, "%s", buf2);
					maxage = atoi(buf2);

                    memset(last_pwchg, 0, sizeof last_pwchg);

                    if (strlen(expire_period) > 0) {
                         get_shadow_chgtime(expire_period, last_pwchg, &tmpnum);
                    }


                    for(i = 0; i < user_num; i++) {
                        if(!strcmp(accounts[i].name, user)) {
                            strcpy(accounts[i].password, password);
                            if(strlen(password)==0) accounts[i].NOPASS = 1;
                            if (strncmp(password, "*LK*", strlen("*LK*")) == 0 || strcmp(password, "NP") == 0 || strcmp(password, "*") == 0 ||
                            strncmp(password, "*LK*NP", strlen("*LK*NP")) == 0 || strncmp(password, "NP*LK*", strlen("NP*LK*")) == 0) 
							{
                                accounts[i].LOCK = 1; 
                            }
							/*
                            last_pwchg[8] = '\0';
                            if (strlen(last_pwchg) == 8) {
                                strcat(last_pwchg, " 00:00:00\0");
                            } else {
                                memset(last_pwchg, 0, sizeof last_pwchg);
							}
							*/

                            strcpy(accounts[i].last_pwchg, last_pwchg);
                            strcpy(accounts[i].expire_period, expire_period);
							accounts[i].maxday=maxage;

                        	if ( strlen(expire_period) > 0 && (maxage > 0 && maxage < 99999) ) {
                           		memset(buf2, 0, sizeof buf2);
                           		sprintf(buf2, "%d", atoi(expire_period) + maxage);

                            	get_shadow_chgtime(buf2, buf, &tmpnum);
                            	strcpy(accounts[i].expire_time, buf);
                            	strcpy(accounts[i].expire_date, accounts[i].expire_time);
								accounts[i].expire_date[8] = '\0';
                            	accounts[i].remain_expire = tmpnum;
                        	}
                            break;
                        }
                    }
                }
                /*pclose(pfp);*/
                fclose(pfp);
            }
        } else if (mode == 0) {  /* trusted mode */

			/* 
				/etc/default/security
				PASSWORD_MAXDAYS=90
			*/

			if ((pfp=popen("grep PASSWORD_MAXDAYS /etc/default/security", "r")) != NULL) {
				while(fgets(tbuf, 1023, pfp) != NULL) {
					ptr = (char*)strchr(tbuf, '=');
					if ( ptr != NULL) {
						memset(buf, 0, sizeof buf);
						memset(buf2, 0, sizeof buf2);
						sscanf(ptr+1, "%s", buf2);
						*ptr = '\0';
						sscanf(tbuf, "%s", buf);
						if (!strcmp(buf, "PASSWORD_MAXDAYS")) {
							maxage = atoi(buf2);
							it_loging("libIT.a(%s): get_accountinfo() /etc/default/security PASSWORD_MAXDAYS = %d\n", S2O_DAEMON, maxage);
						}
					}
				}
				pclose(pfp);
			}
			if (maxage < 1) {
				maxage = 90;
				it_loging("libIT.a(%s): get_accountinfo() temporary PASSWORD_MAXDAYS = %d\n", S2O_DAEMON, maxage);
			}

			/*
			(sample)
			/tcb/files/auth/u/user001    (  <--- /tcb/files/auth/name[0]/name )
			user001:\						trusted database name
			:u_name=user001:\				login ID for account (must match database name)
			:u_id#1201:\					uid corresponding to the login ID
			:u_pwd=n97jxy5cCgthc:\			encrypted password
			:u_auditid#9:\					unique audit id
			:u_auditflag#1:\				audit flag (1 = audit enabled )
			:u_succhg#853776632:\			time_t value of last successful password change
			:u_unsucchg#852832389:\			time_t value of last unsuccessful password change
			:u_suclog#857328687:\			time_t value of last successful login
			:u_suctty=ttyp4:\				terminal used for last successful login
			:u_unsuclog#855686195:\			time_t value of last unsuccessful login
			:u_unsuctty=ttypc:\				terminal used for last unsuccessful login
			:u_lock@:\						account is not administratively locked
			:chkent:						required last entry field
			*/

            for(i = 0; i < user_num; i++) {
                memset(file, 0, sizeof file);
                sprintf(file, "/tcb/files/auth/%c/%s", accounts[i].name[0], accounts[i].name);
                if ((fd = fopen(file, "r")) != NULL) {
                    while(fgets(tbuf, 1023, fd) != NULL) {
                        if(tbuf[0] == '#' || tbuf[0] == '\n') continue;
                        ptr = (char*)strstr(tbuf, "u_pwd");
                        if (ptr != NULL) {
                            memset(tbuf2, 0, sizeof tbuf2);
                            strcpy(tbuf2, ptr+strlen("u_pwd"));
                            ptr = (char*)strchr(tbuf2, '=');
                            if(ptr!=NULL) {
                                memset(tbuf3, 0, sizeof tbuf3);
                                strcpy(tbuf3, ptr+1);
                                ptr = (char*)strchr(tbuf3, ':');
                                if(ptr!=NULL) *ptr = '\0';
                                ptr = (char*)strchr(tbuf3, '\\');
                                if(ptr!=NULL) *ptr = '\0';
                                strcpy(accounts[i].password, password);
                                if (strlen(tbuf3) == 0)
                                    if(strlen(password)==0) accounts[i].NOPASS = 1;
                                else if (!strcmp(tbuf3, "*"))
                                    if(strlen(password)==0) accounts[i].LOCK = 1;
                            }
                        }

                        ptr = (char*)strstr(tbuf, "u_lock");
                        if (ptr != NULL) {
                            if(*(ptr+(strlen("u_lock"))) !='@')
                                accounts[i].LOCK = 1;
                        }

						accounts[i].maxday=maxage;

						ptr = (char*)strstr(tbuf, "u_succhg");  /* u_succhg#828919424: */
						if (ptr != NULL) {
							memset(tbuf2, 0, sizeof tbuf2);
							strcpy(tbuf2, ptr);
							ptr = (char*) strchr(tbuf2, ':');
							if (ptr != NULL) {
								*ptr = '\0';
								ptr = (char*) strchr(tbuf2, '#');
								if (ptr != NULL) {
									memset(tbuf3, 0, sizeof tbuf3);
									sscanf(ptr+1, "%s", tbuf3);
									memset(buf, 0, sizeof buf);

									strcpy(accounts[i].expire_period, tbuf3);
									epoch2date(atoi(tbuf3), buf);
									/*sprintf(buf, "%s", epoch2date(atoi(tbuf3)));*/

									strcpy(accounts[i].last_pwchg, buf);
									tmpnum = atoi(accounts[i].expire_period) + maxage * 86400;
									memset(buf, 0, sizeof buf);

									epoch2date(tmpnum, buf);
									/*sprintf(buf, "%s", epoch2date(tmpnum));*/
									/*sprintf(buf, "%s", epoch2date(tmpnum));*/

									strcpy(accounts[i].expire_time, buf);
									strcpy(accounts[i].expire_date, accounts[i].expire_time);
									accounts[i].expire_date[8] = '\0';
									accounts[i].remain_expire = tmpnum - time(0);
								}
							}
						}
                    }
                    fclose(fd);
                }
            }

			/*
			/////////////////////////////////////////////////////////////////////////
			(참고 sample)
			/tcb/files/auth/system/default	
			default:\
			:d_name=default:\
			:d_boot_authenticate@:\
			:u_pwd=*:\
			:u_owner=root:u_auditid#-1:\
			:u_auditflag#-1:\
			:u_minchg#0:u_maxlen#8:u_exp#15724800:u_life#16934400:\
			:u_pw_expire_warning#604800:u_pswduser=root:u_pickpw:u_genpwd:\
			:u_restrict@:u_nullpw@:u_genchars@:u_genletters:\
			:u_suclog#0:u_unsuclog#0:u_maxtries#3:u_lock:\
			:\
			:t_logdelay#2:t_maxtries#10:t_login_timeout#0:\
			:chkent:


			/tcb/files/auth/o/oracle	
			oracle:u_name=oracle:u_id#600:\
			:u_pwd=*:\
			:u_auditid#67:\
			:u_auditflag#1:\
			:u_exp#3024000:u_life#4838400:u_succhg#1150751962:u_unsucchg#1150691460:\
			:u_pw_expire_warning#604800:u_pswduser=oracle:u_nullpw:u_pwchanger=root:\
			:u_suclog#1150752396:u_suctty=/dev/pts/1:u_unsuclog#1150692078:u_unsuctty=ssh:\
			:u_lock@:chkent:
			/////////////////////////////////////////////////////////////////////////
			*/
        }
    }
#else	/* SunOS, Linux */
	/*
		linux 명령어 : chage -l 계정
	*/

	if (stat("/etc/shadow", &stbuf) == 0) { /* 파일이 존재 할 경우 */
		/*if ((pfp=popen("cat /etc/shadow | awk -F: '{print $1,$2,$3}'", "r")) != NULL) {*/
		/*if ((pfp=popen("cat /etc/shadow", "r")) != NULL) {*/
		if ((pfp=fopen("/etc/shadow", "r")) != NULL) {
			while(fgets(tbuf, 1023, pfp) != NULL) {
				/* 1.사용자명:2.패스워드:3.패스워드파일최종수정일:4.패스워드변경최소일:5.패스워드변경최대일(99999):6.패스워드만료경고기간:7.패스워드파기기간:8.계정만료기간:9.예약필드 */
				memset(user, 0, sizeof user);
				memset(password, 0, sizeof password);
				memset(buf, 0, sizeof buf);
				memset(buf2, 0, sizeof buf2);
				memset(expire_period, 0, sizeof expire_period);
				/*sscanf(tbuf, "%s %s %s", user, password, buf);*/
				getitem(':', tbuf, user, 1);
				getitem(':', tbuf, password, 2);
				getitem(':', tbuf, expire_period, 3);
				getitem(':', tbuf, buf, 5);
				sscanf(buf, "%s", buf2);
				if (strlen(buf2) == 0) maxage = -1;
				else maxage = atoi(buf2);

				memset(last_pwchg, 0, sizeof last_pwchg);

				if (strlen(expire_period) > 0) {
					 get_shadow_chgtime(expire_period, last_pwchg, &tmpnum);
				}


				for(i = 0; i < user_num; i++) {
					if(!strcmp(accounts[i].name, user)) {
						strcpy(accounts[i].password, password);
#if defined(SUN2)
						if(strlen(password)==0) accounts[i].NOPASS = 1;

						if (strncmp(password, "*LK*", strlen("*LK*")) == 0 || strcmp(password, "NP") == 0 ||
							strncmp(password, "*LK*NP", strlen("*LK*NP")) == 0 || strncmp(password, "NP*LK*", strlen("NP*LK*")) == 0)
						{
#elif defined(LINUX)

						if(strlen(password)==0) accounts[i].NOPASS = 1;

						if (strcmp(password, "*")==0 || password[0] == '!')
						{
#endif
							accounts[i].LOCK = 1;
						}
				
						/*	
						last_pwchg[8] = '\0';

						if (strlen(last_pwchg) == 8) {
							strcat(last_pwchg, " 00:00:00");
						} else {
							memset(last_pwchg, 0, sizeof last_pwchg);
						}
						*/

						strcpy(accounts[i].last_pwchg, last_pwchg);
						strcpy(accounts[i].expire_period, expire_period);
						accounts[i].maxday = maxage;
						if ( strlen(expire_period) > 0 && (maxage > 0 && maxage < 99999) ) {
							memset(buf2, 0, sizeof buf2);
							sprintf(buf2, "%d", atoi(expire_period) + maxage);

							get_shadow_chgtime(buf2, buf, &tmpnum);
							strcpy(accounts[i].expire_time, buf);
							strcpy(accounts[i].expire_date, accounts[i].expire_time);
							accounts[i].expire_date[8] =  '\0';
							accounts[i].remain_expire = tmpnum;
						}
						break;
					} /* if(!strcmp(accounts[i].name, user)) { */
				} /* for(i = 0; i < user_num; i++) { */
			} /* while(fgets(tbuf, 1023, pfp) != NULL) { */
			fclose(pfp);
			/*pclose(pfp);*/
		} /* if ((pfp=popen("cat /etc/shadow", "r")) != NULL) { */
 	} /* if (stat("/etc/shadow", &stbuf) == 0) { */

#endif

	return user_num;
}

int get_shadow_chgtime(char *src, char* dest, int *_time_diff)
{
    time_t cmptvec;
    struct tm ddbuf;
    char time_str[256];

    ddbuf.tm_year    = 1970 - 1900;
    ddbuf.tm_mon = 0 ;
    ddbuf.tm_mday = 1+atoi(src);
    ddbuf.tm_hour = 0;
    ddbuf.tm_min = 0;
    ddbuf.tm_sec = 0;
    ddbuf.tm_isdst = -1;
    cmptvec = mktime(&ddbuf);

    memset(time_str, 0, sizeof time_str);
    sprintf(time_str, "%4d%-2.2d%-2.2d %-2.2d:%-2.2d:%-2.2d", ddbuf.tm_year+1900, ddbuf.tm_mon+1, ddbuf.tm_mday, ddbuf.tm_hour, ddbuf.tm_min, ddbuf.tm_sec);
    strcpy(dest, time_str);

	/* 현재 시간과의 차이 */
	*_time_diff = cmptvec - time(0);

    return(0);
}

