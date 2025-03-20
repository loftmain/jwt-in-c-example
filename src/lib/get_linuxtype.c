   /************************************************************************/
   /*  FILENAME     : get_linuxtype.c                                      */
   /*  DISCRIPTION  : Linux 종류를 확인한다.                               */
   /*  DATE         : 2018. 05. 04                                         */
   /*  WRITTEN      :                                                      */
   /*  MODIFIED     :                                                      */
   /************************************************************************/

#include "config.h"
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include "../IT.extern.h"

extern int loging(char *msg,...);

int get_linuxtype(char* _linuxtype, char* _detail)
{
	FILE *pfp;
	char linux_type[256];
	char linux_detail[1024];
	char tmp_detail[1024];
	char tmp_detail2[1024];
	char tbuf[1024];
	char *ptr;
	int line = 0;
	char buf1[1024], buf2[1024], buf3[1024];

    memset(linux_type, 0, sizeof linux_type);
	memset(linux_detail, 0, sizeof linux_detail);

/*

cat /etc/*-release |uniq

실행예시 (Ubuntu 14.04.3)
root@zetawiki:~# grep . /etc/*-release
/etc/lsb-release:DISTRIB_ID=Ubuntu
/etc/lsb-release:DISTRIB_RELEASE=14.04
/etc/lsb-release:DISTRIB_CODENAME=trusty
/etc/lsb-release:DISTRIB_DESCRIPTION="Ubuntu 14.04.3 LTS"
/etc/os-release:NAME="Ubuntu"
/etc/os-release:VERSION="14.04.3 LTS, Trusty Tahr"
/etc/os-release:ID=ubuntu
/etc/os-release:ID_LIKE=debian
/etc/os-release:PRETTY_NAME="Ubuntu 14.04.3 LTS"
/etc/os-release:VERSION_ID="14.04"
/etc/os-release:HOME_URL="http://www.ubuntu.com/"
/etc/os-release:SUPPORT_URL="http://help.ubuntu.com/"
/etc/os-release:BUG_REPORT_URL="http://bugs.launchpad.net/ubuntu/"

실행예시 (CentOS 6.5)
[root@zetawiki ~]# grep . /etc/*-release
/etc/centos-release:CentOS release 6.5 (Final)
/etc/lsb-release:LSB_VERSION=base-4.0-amd64:base-4.0-noarch:core-4.0-amd64:core-4.0-noarch:graphics-4.0-amd64:graphics-4.0-noarch:printing-4.0-amd64:printing-4.0-noarch
/etc/redhat-release:CentOS release 6.5 (Final)
/etc/system-release:CentOS release 6.5 (Final)

실행예시 (Fedora 11 Leonidas)
[root@zetawiki ~]# cat /etc/*-release | uniq
Fedora release 11 (Leonidas)

실행예시 (Oracle Enterprise Linux Server 5.5)
[root@zetawiki ~]# cat /etc/*-release | uniq
Enterprise Linux Enterprise Linux Server release 5.5 (Carthage)
Red Hat Enterprise Linux Server release 5.5 (Tikanga)

실행예시 (SUSE Linux Enterprise Server 11)
zetawiki:~ # cat /etc/*-release | uniq
SUSE Linux Enterprise Server 11 (x86_64)
VERSION = 11
PATCHLEVEL = 1
LSB_VERSION="core-2.0-noarch:core-3.2-noarch:core-4.0-noarch:core-2.0-x86_64:core-3.2-x86_64:core-4.0-x86_64"

추가 정보 (CentOS)
[oracle@sms-157 s2o]$ lsb_release -a
LSB Version:    :base-4.0-amd64:base-4.0-noarch:core-4.0-amd64:core-4.0-noarch:graphics-4.0-amd64:graphics-4.0-noarch:printing-4.0-amd64:printing-4.0-noarch
Distributor ID: CentOS
Description:    CentOS release 6.5 (Final)
Release:        6.5
Codename:       Final

root@newsys01 IT.wora_pcasset]# lsb_release -a
LSB Version:    :core-4.0-amd64:core-4.0-ia32:core-4.0-noarch:graphics-4.0-amd64:graphics-4.0-ia32:graphics-4.0-noarch:printing-4.0-amd64:printing-4.0-ia32:printing-4.0-noarch
Distributor ID: CentOS
Description:    CentOS release 5.11 (Final)
Release:        5.11
Codename:       Final
*/

    if ((pfp=popen("cat /etc/*-release |uniq", "r")) != NULL) {
        line = 0;
        memset(buf2, 0, sizeof buf2);
        memset(buf3, 0, sizeof buf3);
        while(fgets(tbuf, 1023,pfp) != NULL) {
            if(tbuf[strlen(tbuf)-1] == '\n') tbuf[strlen(tbuf)-1] = '\0';
            if(tbuf[strlen(tbuf)-1] == '\"') tbuf[strlen(tbuf)-1] = '\0';
            memset(buf1, 0, sizeof buf1);
            sscanf(tbuf, "%s", buf1);
            if (strlen(buf1) == 0) continue;

            if (line == 0) {
                strcpy(buf2, tbuf);
                strcpy(buf3, tbuf);
            }

            if ( strlen(linux_type) == 0) {
                /* Oracle Linux */
                ptr = (char*) strstr(tbuf, "Oracle Linux Server");
                if ( ptr != NULL) {
                    strcpy(linux_type, LINUX_ORACLE);
					strcpy(linux_detail, ptr);
                    break;
                }

                /* RHEL 검색 */
                ptr = (char*) strstr(tbuf, "Red Hat Enterprise Linux");
                if ( ptr != NULL) {
                    strcpy(linux_type, LINUX_RHEL);
					strcpy(linux_detail, ptr);
                    break;
                }

                /* CentOS 검색 */
                ptr = (char*) strstr(tbuf, "CentOS release");
                if ( ptr != NULL) {
                    strcpy(linux_type, LINUX_CENTOS);
					strcpy(linux_detail, ptr);
                    break;
                }
                ptr = (char*) strstr(tbuf, "CentOS Linux release");
                if ( ptr != NULL) {
                    strcpy(linux_type, LINUX_CENTOS);
					strcpy(linux_detail, ptr);
                    break;
                }

                /* Redhat 검색 */
                ptr = (char*) strstr(tbuf, "Red Hat Linux");
                if ( ptr != NULL) {
                    strcpy(linux_type, LINUX_REDHAT);
					strcpy(linux_detail, ptr);
                    break;
                }

                /* SUSE 검색 */
                ptr = (char*) strstr(tbuf, "SUSE Linux");
				if ( ptr == NULL) ptr = (char*) strstr(tbuf, "SUSE LINUX");
                if ( ptr != NULL) {
                    strcpy(linux_type, LINUX_SUSE);
					strcpy(linux_detail, ptr);
                    break;
                }

                /* Oracle Enterprise Linux 검색 */
                ptr = (char*) strstr(tbuf, "Enterprise Linux Enterprise Linux");
                if ( ptr != NULL) {
                    strcpy(linux_type, LINUX_ORACLE);
					strcpy(linux_detail, ptr);
                    break;
                }

                /* Fedora 검색 */
                ptr = (char*) strstr(tbuf, "Fedora release");
                if ( ptr != NULL) {
                    strcpy(linux_type, LINUX_FEDORA);
					strcpy(linux_detail, ptr);
                    break;
                }

                /* Debian 검색 */
                ptr = (char*) strstr(tbuf, "PRETTY_NAME");
                if ( ptr != NULL) {
                    ptr = (char*) strstr(tbuf, "Debian");
                    if ( ptr != NULL) {
                        strcpy(linux_type, LINUX_DEBIAN);
						strcpy(linux_detail, ptr);
                        break;
                    }
                }

                /* ubuntu 검색 */
                ptr = (char*) strstr(tbuf, "DISTRIB_ID");
                if (ptr != NULL) {
                    /*strcpy(linux_type, "ubuntu"); */
                    strcpy(linux_type, LINUX_UBUNTU);
                    memset(buf2, 0, sizeof buf2);
                    getitem('=', tbuf, buf2, 2);
                    strcpy(buf3, buf2);
                }

                /* Amazon Linux */
                ptr = (char*) strstr(tbuf, "Amazon Linux");
                if ( ptr != NULL) {
                    strcpy(linux_type, LINUX_AMAZON);
					strcpy(linux_detail, ptr);
                    break;
                }
            }

            if ( !strcmp(linux_type, LINUX_UBUNTU)) {
                ptr = (char*) strstr(tbuf, "DISTRIB_RELEASE");
                if (ptr != NULL) {
                    memset(buf2, 0, sizeof buf2);
                    getitem('=', tbuf, buf2, 2);
                    strcat(buf3, " ");
                    strcat(buf3, buf2);
                }
            }

            ptr = (char*) strstr(tbuf, "DISTRIB_DESCRIPTION");
            if (ptr != NULL) {
                memset(buf2, 0, sizeof buf2);
                getitem('=', tbuf, buf2, 2);
                /* strcpy(linux_type, "ubuntu"); */
                strcpy(linux_type, LINUX_UBUNTU);
				if (buf2[0] =='\"') 
					strcpy(linux_detail, buf2+1);
				else
					strcpy(linux_detail, buf2);
            }

            line++;
        }
		pclose(pfp);

		if ( strlen(linux_type) > 0 ) {
			memset(tmp_detail, 0, sizeof tmp_detail);
			memset(tmp_detail2, 0, sizeof tmp_detail2);
			if (!strcmp(linux_type, LINUX_RHEL) || !strcmp(linux_type, LINUX_REDHAT) || !strcmp(linux_type, LINUX_CENTOS)) {
				/* detail 다시 확인 */
    			if ((pfp=popen("cat /etc/redhat-release |uniq", "r")) != NULL) {
        			memset(buf2, 0, sizeof buf2);
        			memset(buf3, 0, sizeof buf3);
        			while(fgets(tbuf, 1023,pfp) != NULL) {
            			if(tbuf[strlen(tbuf)-1] == '\n') tbuf[strlen(tbuf)-1] = '\0';
            			if(tbuf[strlen(tbuf)-1] == '\"') tbuf[strlen(tbuf)-1] = '\0';
            			memset(buf1, 0, sizeof buf1);
            			sscanf(tbuf, "%s", buf1);
            			if (strlen(buf1) == 0) continue;

                		/* RHEL 검색 */
                		ptr = (char*) strstr(tbuf, "Red Hat Enterprise Linux");
                		if ( ptr != NULL) {
							strcpy(tmp_detail, ptr);
                    		break;
                		}
                		/* CentOS 검색 */
                		ptr = (char*) strstr(tbuf, "CentOS release");
                		if ( ptr != NULL) {
							strcpy(tmp_detail, ptr);
                    		break;
                		}
                		ptr = (char*) strstr(tbuf, "CentOS Linux release");
                		if ( ptr != NULL) {
							strcpy(tmp_detail, ptr);
                    		break;
                		}

                		/* Redhat 검색 */
                		ptr = (char*) strstr(tbuf, "Red Hat Linux");
                		if ( ptr != NULL) {
							strcpy(tmp_detail, ptr);
                    		break;
                		}

						if (strlen(tmp_detail2)+strlen(tmp_detail) < 511) {
							strcat(tmp_detail2, tmp_detail);
							strcat(tmp_detail2, ". ");
						}
					}
				}	
			}

			sprintf(_linuxtype, "%s", linux_type);
			if ( strlen(tmp_detail) > 0) sprintf(_detail, "%s", tmp_detail);
			else if ( strlen(tmp_detail2) > 0) sprintf(_detail, "%s", tmp_detail2);
			else sprintf(_detail, "%s", linux_detail);
			return 1;
		}
	} else {
		return -1;
	}

/* 

rpm -qa *-release 

실행예시 (CentOS 6.2)
[root@zetawiki ~]# rpm -qa *-release
centos-release-6-2.el6.centos.7.x86_64

실행예시 (Fedora 11 Leonidas)
[root@zetawiki ~]# rpm -qa *-release
fedora-release-11-1.noarch

실행예시 (Oracle Enterprise Linux Server 5.5)
[root@zetawiki ~]# rpm -qa *-release
enterprise-release-5-0.0.22

실행예시 (SUSE Linux Enterprise Server 11)
zetawiki:~ # rpm -qa *-release
sles-release-11.1-1.152
lsb-release-2.0-1.2.18

*/

    if ((pfp=popen("rpm -qa *-release|uniq 2>/dev/null", "r")) != NULL) {

		memset(linux_type, 0, sizeof linux_type);
		memset(tbuf, 0, sizeof tbuf);

        while(fgets(tbuf, 1023,pfp) != NULL) {
            if(tbuf[strlen(tbuf)-1] == '\n') tbuf[strlen(tbuf)-1] = '\0';
            if(tbuf[strlen(tbuf)-1] == '\"') tbuf[strlen(tbuf)-1] = '\0';
			if (!strncmp(tbuf, "centos-release", strlen("centos-release"))){
				strcpy(linux_type, LINUX_CENTOS);
				strcpy(linux_detail, tbuf);
				break;
			} else if (!strncmp(tbuf, "fedora-release", strlen("fedora-release"))){
				strcpy(linux_type, LINUX_FEDORA);
				strcpy(linux_detail, tbuf);
				break;
			} else if (!strncmp(tbuf, "enterprise-release", strlen("enterprise-release"))){
				strcpy(linux_type, LINUX_ORACLE);
				strcpy(linux_detail, tbuf);
				break;
			} else if (!strncmp(tbuf, "sles-release", strlen("sles-release"))){
				strcpy(linux_type, LINUX_SUSE);
				strcpy(linux_detail, tbuf);
				break;
			}
			memset(tbuf, 0, sizeof tbuf);
		}
		pclose(pfp);
		if ( strlen(linux_type) > 0) {
			sprintf(_linuxtype, linux_type);
			sprintf(_detail, linux_detail);
			return 1;
		}
	}


/* 
cat /etc/issue*

실행예시 (Ubuntu 14.04.3)
root@zetawiki:~# grep . /etc/issue*
/etc/issue:Ubuntu 14.04.3 LTS \n \l
/etc/issue.net:Ubuntu 14.04.3 LTS

실행예시 (CentOS 6.5)
[root@zetawiki ~]# grep . /etc/issue*
/etc/issue:CentOS release 6.5 (Final)
/etc/issue:Kernel \r on an \m
/etc/issue.net:CentOS release 6.5 (Final)
/etc/issue.net:Kernel \r on an \m

실행예시 (Fedora 11)
[root@zetawiki ~]# cat /etc/issue
Fedora release 11 (Leonidas)
Kernel \r on an \m (\l)

실행예시 (Oracle Enterprise Linux 5.5)
[root@zetawiki ~]# cat /etc/issue
Enterprise Linux Enterprise Linux Server release 5.5 (Carthage)
Kernel \r on an \m

실행예시 (SUSE Linux Enterprise Server 11)
zetawiki:~ # cat /etc/issue

Welcome to SUSE Linux Enterprise Server 11 SP1  (x86_64) - Kernel \r (\l).

*/

    if ((pfp=popen("cat /etc/issue*|uniq 2>/dev/null", "r")) != NULL) {

		memset(linux_type, 0, sizeof linux_type);

		memset(tbuf, 0, sizeof tbuf);
        while(fgets(tbuf, 1023,pfp) != NULL) {

            if(tbuf[strlen(tbuf)-1] == '\n') tbuf[strlen(tbuf)-1] = '\0';
            if(tbuf[strlen(tbuf)-1] == '\"') tbuf[strlen(tbuf)-1] = '\0';

			ptr = (char*) strstr(tbuf, "Ubuntu");
			if ( ptr != NULL) {	
				strcpy(linux_type, LINUX_UBUNTU);
				strcpy(linux_detail, tbuf);
				break;
			}

			ptr = (char*) strstr(tbuf, "CentOS release");
			if ( ptr != NULL) {	
				strcpy(linux_type, LINUX_CENTOS);
				strcpy(linux_detail, tbuf);
				break;
			}

			ptr = (char*) strstr(tbuf, "Fedora release");
			if ( ptr != NULL) {	
				strcpy(linux_type, LINUX_FEDORA);
				strcpy(linux_detail, tbuf);
				break;
			}

			ptr = (char*) strstr(tbuf, "SUSE Linux");
			if ( ptr != NULL) {	
				strcpy(linux_type, LINUX_SUSE);
				strcpy(linux_detail, tbuf);
				break;
			}

			memset(tbuf, 0, sizeof tbuf);
		}
		pclose(pfp);

		if ( strlen(linux_type) > 0) {
			sprintf(_linuxtype, linux_type);
			sprintf(_detail, linux_detail);
			return 1;
		}
	}
	

	return 0;
}

