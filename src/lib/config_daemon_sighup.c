
/*
 * Copyright (c) 2022, NewSystech Inc. All rights reserved.
 *
 * NAME
 *      config_daemon_sighup.c - config 파일에 따른 관련 daemon에 sighup 기능 ( 설정(IT.cmdd), upload (IT.uptd) 시 )
 *
 * MODIFIED     (MM/DD/YYYY)
 *  03/17/2022 - config 파일에 따른 관련 daemon에 sighup 기능 ( 설정, upload 시 )
 *
 */

#include "config.h"
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "../IT.extern.h"
#include "../msgid_cmdd.h"

int daemon_sig_cfg(char* cfgname, char* homedir);

int config_daemon_sighup(char *config, char* mode, char* cocode, char* homedir)
{
    char config_files[][4][30]={
            {"2", "db2bufferpool.cfg", "IT.db2d", "1"},
            {"2", "db2check.cfg", "IT.db2d", "1"},
            {"1", "db2check.cfg", "IT.wrtd", "1"},
            {"0", "db2check.cfg", "IT.sndd", "1"},
            {"2", "db2database.cfg", "IT.db2d", "1"},
            {"2", "db2errlist.cfg", "IT.db2d", "1"},
            {"2", "db2tablespace.cfg", "IT.db2d", "1"},
			{"1", "call_f.cfg", "IT.call_f", "1"},
            {"0", "chkagent.cfg", "IT.chkd", "1"},
            {"1", "chkport.cfg", "IT.svcd", "1"},
			{"1", "chkpttime.cfg", "IT.wrtd", "1"},
            {"1", "chkschedule.cfg", "IT.chkd", "1"},
            {"1", "chksnmp.cfg", "IT.smpd", "1"},
            {"1", "chksnmpu.cfg", "IT.smpud", "1"},
            {"1", "chkweb.cfg", "IT.webd", "1"},
            {"1", "ecs.cfg", "IT.ecsd", "1"},
            {"2", "disk.cfg", "IT.schd", "1"},
            {"1", "except_host.cfg", "IT.wrtd", "0"},
			{"2", "except_chktime.cfg", "IT.schd", "1"},
			{"2", "except_chktime.cfg", "IT.perf", "1"},
			{"1", "except_chktime_master.cfg", "IT.chkd", "1"},
            {"1", "except_dbinsert.cfg", "IT.oraw", "0"},
            {"1", "except_dbinsert.cfg", "IT.orawl", "0"},
            {"1", "except_dbinsert.cfg", "IT.orawp", "0"},
            {"1", "except_dbinsert.cfg", "IT.orawpm", "0"},
            {"1", "except_dbinsert.cfg", "IT.orawpe", "0"},
            {"1", "except_dbinsert.cfg", "IT.orawped", "0"},
            {"1", "except_dbinsert.cfg", "IT.orawpes", "0"},
            {"1", "except_dbinsert.cfg", "IT.orawpese", "0"},
            {"1", "except_dbinsert.cfg", "IT.orawpesp", "0"},
            {"2", "ha_mon_sync.cfg", "IT.mond", "1"},
            {"2", "inodes.cfg", "IT.schd", "1"},
            {"2", "joblog.cfg", "IT.jobd", "1"},
            {"2", "jobpattern.cfg", "IT.jobd", "1"},
            {"2", "logcheck.cfg", "IT.jobd", "1"},
            {"2", "mmdb.cfg", "IT.mmdb", "1"},
            {"2", "nbucheck.cfg", "IT.jobd", "1"},
            {"2", "network.cfg", "IT.schd", "1"},
            {"2", "oracheck.cfg", "IT.orac", "1"},
            {"1", "oracheck.cfg", "IT.wrtd", "1"},
            {"0", "oracheck.cfg", "IT.sndd", "1"},
            {"2", "oraerrlist.cfg", "IT.orac", "1"},
            {"2", "orainvalidobj.cfg", "IT.orac", "1"},
            {"2", "orasegment.cfg", "IT.orac", "1"},
            {"2", "oratablespace.cfg", "IT.orac", "1"},
            {"2", "orawaitevent.cfg", "IT.orac", "1"},
            {"2", "asm.cfg", "IT.orac", "1"},
            {"2", "oraqm.cfg", "IT.orac", "1"},
            {"2", "process.cfg", "IT.schd", "1"},
            {"2", "proccpu.cfg", "IT.schd", "1"},
            {"2", "s2o_trap.cfg", "IT.trapd", "1"},
            {"2", "s2o_trappattern.cfg", "IT.trapd", "1"},
            {"2", "securefile.cfg", "IT.schd", "1"},
            {"2", "securityVA.cfg", "IT.jobd", "1"},
            {"2", "sqlcheck.cfg", "IT.sqld", "1"},
            {"2", "sqlerrlist.cfg", "IT.sqld", "1"},
            {"2", "swcheck.cfg", "IT.jobd", "1"},
            {"2", "syscheck.cfg", "IT.schd", "1"},
            {"2", "syscheck.cfg", "IT.perf", "1"},
            {"0", "syslog_", "IT.sndd", "1"},
            {"0", "syslog_", "IT.qsnd", "1"},
            {"1", "syslog_", "IT.locd", "1"},
            {"1", "syslog_", "IT.wrtd", "1"},
            {"2", "syslog_", "IT.schd", "1"},
            {"1", "sysmods.cfg", "IT.wrtd", "1"},
            {"0", "sysmods.cfg", "IT.sndd", "1"},
            {"2", "tbcheck.cfg", "IT.tibe", "1"},
            {"1", "tbcheck.cfg", "IT.wrtd", "1"},
            {"0", "tbcheck.cfg", "IT.sndd", "1"},
            {"2", "tberrlist.cfg", "IT.tibe", "1"},
            {"2", "tbtablespace.cfg", "IT.tibe", "1"},
            {"2", "mariacheck.cfg", "IT.mariad", "1"},
            {"1", "mariacheck.cfg", "IT.wrtd", "1"},
            {"0", "mariacheck.cfg", "IT.sndd", "1"},
            {"2", "mariaerrlist.cfg", "IT.mariad", "1"},
            {"2", "mysqlcheck.cfg", "IT.mysqld", "1"},
            {"1", "mysqlcheck.cfg", "IT.wrtd", "1"},
            {"0", "mysqlcheck.cfg", "IT.sndd", "1"},
            {"2", "mysqlerrlist.cfg", "IT.mysqld", "1"},
            {"2", "pgsqlcheck.cfg", "IT.pgsql", "1"},
            {"1", "pgsqlcheck.cfg", "IT.wrtd", "1"},
            {"0", "pgsqlcheck.cfg", "IT.sndd", "1"},
            {"2", "pgsqlerrlist.cfg", "IT.pgsql", "1"},
            {"2", "awsrds.cfg", "IT.awsd", "1"},
            {"1", "webexcept.cfg", "IT.webd", "1"},
            {"","","",""}};


	int i;
	char chkservcfg[256];
	int find = 0;
	char tmpchkd[20];
	char tmpmond[20];
	char tmpbuf[32];
	char tmpcom[20];
   
   if ( !strcmp(mode, "1")) {
		if (!strncmp(config, "chkserv", 7)) {
			sprintf(chkservcfg, "chkserv_%s.cfg", cocode);
			if (!strcmp(chkservcfg, config)) {
				daemon_sig_cfg("IT.chkd", homedir);
				daemon_sig_cfg("IT.mond", homedir);
				return 1;
			} else {
				/*
				for(i=2; i< 10; i++) {
					memset(tmpbuf, 0, sizeof tmpbuf);
					memset(tmpcom, 0, sizeof tmpcom);
					memset(tmpchkd, 0, sizeof tmpchkd);
					memset(tmpmond, 0, sizeof tmpmond);

					sprintf(tmpbuf, "IT_COMPANY_CODE%dK", i);
    				get_cfg(tmpbuf, tmpcom);

           	     	memset(chkservcfg, 0, sizeof chkservcfg);
           	     	sprintf(chkservcfg, "chkserv_%s.cfg", tmpcom);

           	     	if (!strcmp(chkservcfg, config)) {
						sprintf(tmpchkd, "IT.chkd%dk", i);
						sprintf(tmpmond, "IT.mond%dk", i);
           	     		daemon_sig_cfg(tmpchkd, homedir);
           	     		daemon_sig_cfg(tmpmond, homedir);
                		return 1;
					}	
				}
				*/
        	}
    	}
	}

    i = 0;
    find = 0;
    while(strcmp(config_files[i][0],"")) {
        if (!strncmp(config, config_files[i][1], strlen(config_files[i][1]))) {
            if (!strcmp(config_files[i][0],"2") || !strcmp(config_files[i][0], mode)){
                daemon_sig_cfg(config_files[i][2], homedir);
            }
            find = 1;
        } else if (find == 1) {
            break;
        }
        i++;
    }
    return 1;
}

int daemon_sig_cfg(char* agent, char* homedir)
{
    FILE    *pfp;

    char    buf[256], cmdbuf[256];
    int     pid, ppid, linecnt;

    /*
    ** S2O Agent가 process daemon으로 존재하는지 확인.
    */

    it_loging("libIT.a(%s): daemon_sig_cfg() Attempt signal(SIGHUP) to agent(%s).\n", S2O_DAEMON, agent);

#if defined(LINUX)
    sprintf(cmdbuf, "ps -e -o user,pid,ppid,args|grep \"%s/%s\"|grep -v grep", homedir, agent);
#else
    sprintf(cmdbuf, "ps -ef|grep \"%s/%s\"|grep -v grep", homedir, agent);
#endif

    if ((pfp = popen(cmdbuf, "r")) == NULL) {
        it_loging("libIT.a(%s): daemon_sig_cfg() pipe(daemon_sig) command execution error.\n", S2O_DAEMON);
        return(-1);
    }

    linecnt = 0;
    while (fgets(buf, 255, pfp) != NULL) {
        linecnt++;
        sscanf(buf, "%*s %d %d", &pid, &ppid);
        if (ppid == 1 || !strcmp(agent, "IT.orac") || !strcmp(agent, "IT.oraqm")) {
            kill(pid, SIGHUP);
            if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = '\0';
            it_loging("libIT.a(%s): daemon_sig_cfg() Daemon(%s) SIGHUP\n", S2O_DAEMON, buf);
        }
    }
    pclose(pfp);

    if (linecnt <= 0) {
        /* S2O Agent(%s)가 실행되고 있지 않아 초기화에 실패하였습니다. */
        wlog(MSG_W_UPT32, STR_W_UPT32, agent);
        memset(buf, 0, sizeof buf);
        sprintf(buf, STR_W_UPT32, agent);
        it_loging("libIT.a(%s): daemon_sig_cfg() %s\n", S2O_DAEMON, buf);
        return (-2);
    }

    it_loging("libIT.a(%s): daemon_sig_cfg() Send signal(SIGHUP) to agent(%s).\n", S2O_DAEMON, agent);
    return (0);
}

