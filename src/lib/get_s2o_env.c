/*
   $Id: get_s2o_env.c,v 1.0 2018/12/10 srp Exp $

   Copyright (c) 2018
             NewSystech Inc.  All rights reserved.

	** 자산 SCAN
	
   2018-12-10
     * 서버의 s2o 정보를 가져옴
*/

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../IT.extern.h"

extern int get_envhome(char* _envhome);

int get_s2o_env(char* _msg)
{
	char env_home[256];

	s2oenv.chkonly = 0;

	/***** env_home *********/
	memset(s2oenv.env_home, 0, sizeof s2oenv.env_home);
	if (get_envhome(env_home) < 1) {
		sprintf(_msg, "The location of the environment(IT.cfg) file could not be found.");
		return(-1);
	}
	strcpy(s2oenv.env_home, env_home);

	/***** env_file *********/
	memset(s2oenv.env_file, 0, sizeof s2oenv.env_file);
	sprintf(s2oenv.env_file, "%s/IT.cfg\0", s2oenv.env_home);

	/***** bin_home *********/
	memset(s2oenv.bin_home, 0, sizeof s2oenv.bin_home);
	if (get_cfg("IT_HOME", s2oenv.bin_home) < 0) {
		sprintf(_msg, "get parameter(IT_HOME) error!");
		return(-1);
	}
	if (s2oenv.bin_home[strlen(s2oenv.bin_home)-1] == '/') s2oenv.bin_home[strlen(s2oenv.bin_home)-1] = '\0';
	if (strlen(s2oenv.bin_home) == 0) {
		sprintf(_msg, "get parameter(IT_HOME) error!");
		return(-1);
	}

	/***** cfg_home *********/
	memset(s2oenv.cfg_home, 0, sizeof s2oenv.cfg_home);
	sprintf(s2oenv.cfg_home, "%s", s2oenv.bin_home);

	/*
	if (get_cfg("IT_CFG_HOME", s2oenv.cfg_home) < 0) {
	}
	if (s2oenv.cfg_home[strlen(s2oenv.cfg_home)-1] == '/') s2oenv.cfg_home[strlen(s2oenv.cfg_home)-1] = '\0';
	if (strlen(s2oenv.cfg_home) == 0) {
		sprintf(s2oenv.cfg_home, "%s/%s", s2oenv.bin_home, _DEF_CFG_);
	}
	*/

	/***** log_home *********/
	memset(s2oenv.log_home, 0, sizeof s2oenv.log_home);
	sprintf(s2oenv.log_home, "%s", s2oenv.bin_home);

	/*
	if (get_cfg("IT_LOG_HOME", s2oenv.log_home) < 0) {
	}
	if (s2oenv.log_home[strlen(s2oenv.log_home)-1] == '/') s2oenv.log_home[strlen(s2oenv.log_home)-1] = '\0';
	if (strlen(s2oenv.log_home) == 0) {
		sprintf(s2oenv.log_home, "%s/%s", s2oenv.bin_home, _DEF_LOG_);
	}
	*/

	/***** dat_home *********/
	memset(s2oenv.dat_home, 0, sizeof s2oenv.dat_home);
	sprintf(s2oenv.dat_home, "%s", s2oenv.bin_home);

	/*
	if (get_cfg("IT_DAT_HOME", s2oenv.dat_home) < 0) {
	}
	if (s2oenv.dat_home[strlen(s2oenv.dat_home)-1] == '/') s2oenv.dat_home[strlen(s2oenv.dat_home)-1] = '\0';
	if (strlen(s2oenv.dat_home) == 0) {
		sprintf(s2oenv.dat_home, "%s/%s", s2oenv.bin_home, _DEF_DAT_);
	}
	*/

	/***** mode *********/
	memset(s2oenv.mode, 0, sizeof s2oenv.mode);
	if (get_cfg("IT_MODE", s2oenv.mode) < 0) {
	}
	if (strcmp(s2oenv.mode, "1")) strcpy(s2oenv.mode, "0");

	/***** mainhost *********/
	memset(s2oenv.mainhost, 0, sizeof s2oenv.mainhost);
	if (get_cfg("IT_MAINHOST", s2oenv.mainhost) < 0) {
		sprintf(_msg, "get parameter(IT_MAINHOST) error!");
		return(-1);
	}

	/***** mainhost_ip *********/
	memset(s2oenv.mainhost_ip, 0, sizeof s2oenv.mainhost_ip);
	if (get_cfg("IT_MAINHOST_IP", s2oenv.mainhost_ip) < 0) {
		sprintf(_msg, "get parameter(IT_MAINHOST_IP) error!");
		return(-1);
	}

	/***** mainmaster_ip *********/
	memset(s2oenv.mainmaster_ip, 0, sizeof s2oenv.mainmaster_ip);
	get_cfg("IT_MASTER_IP", s2oenv.mainmaster_ip);

	if ( strlen(s2oenv.mainmaster_ip) == 0) {
		get_cfg("IT_MASTER", s2oenv.mainmaster_ip);
		if (!strcmp(s2oenv.mainmaster_ip, "reserved")) memset(s2oenv.mainmaster_ip, 0, sizeof s2oenv.mainmaster_ip);
	}

	/***** company_code *********/
	memset(s2oenv.company_code, 0, sizeof s2oenv.company_code);
	if (get_cfg("IT_COMPANY_CODE", s2oenv.company_code) < 0) {
		sprintf(_msg, "get parameter(IT_COMPANY_CODE) error!");
		return(-1);
	}

	/***** oracle_home *********/
	/***** oracle_ld_lib_path *********/
	memset(s2oenv.oracle_home, 0, sizeof s2oenv.oracle_home);
	memset(s2oenv.ld_lib_path, 0, sizeof s2oenv.ld_lib_path);
	if ( !strcmp(s2oenv.mode, "1")) {
		get_cfg("IT_ORACLE_HOME", s2oenv.oracle_home);
		get_cfg("IT_ORACLE_LD_LIBRARY_PATH", s2oenv.ld_lib_path);
	}

	/***** s2o_host *********/
	memset(s2oenv.s2o_host, 0, sizeof s2oenv.s2o_host);
	if (strlen(S2O_DAEMON) > 0 ) {
		if ( get_s2o_hostname(S2O_DAEMON, s2oenv.s2o_host, 0) < 0) {
			sprintf(_msg, "hostname get error!");
			return(-1);
		}
	} else {
		if ( get_s2o_hostname("libITscn.a", s2oenv.s2o_host, 0) < 0) {
			sprintf(_msg, "hostname get error!");
			return(-1);
		}
	}

	/***** cmd_port *********/
	memset(s2oenv.cmd_port, 0, sizeof s2oenv.cmd_port);
	get_cfg("IT_CMD_PORT", s2oenv.cmd_port);
	if(strlen(s2oenv.cmd_port) == 0) strcpy( s2oenv.cmd_port, _DEF_CMD_PORT_);

	/***** upt_port *********/
	memset(s2oenv.upt_port, 0, sizeof s2oenv.upt_port);
	get_cfg("IT_UPT_PORT", s2oenv.upt_port);
	if(strlen(s2oenv.upt_port) == 0) strcpy( s2oenv.upt_port, _DEF_UPT_PORT_);

	/***** type *********/
	memset(s2oenv.type, 0, sizeof s2oenv.type);
	get_cfg("IT_TYPE", s2oenv.type);

	/***** mainhost_nosend *********/
	memset(s2oenv.mainhost_nosend, 0, sizeof s2oenv.mainhost_nosend);
	get_cfg("IT_MAINHOST_NOSEND", s2oenv.mainhost_nosend);

	/***** pid_dir *********/
	memset(s2oenv.pid_dir, 0, sizeof s2oenv.pid_dir);
	sprintf(s2oenv.pid_dir, "%s/pid", s2oenv.log_home);

	/***** patch_dir *********/
	memset(s2oenv.patch_dir, 0, sizeof s2oenv.patch_dir);
	sprintf(s2oenv.patch_dir, "%s/patch_tmp", s2oenv.log_home);

	/***** patchfail_dir *********/
	memset(s2oenv.patchfail_dir, 0, sizeof s2oenv.patchfail_dir);
	sprintf(s2oenv.patchfail_dir, "%s/patch_tmp_fail", s2oenv.log_home);

	/***** patchbackup_dir *********/
	memset(s2oenv.patchbackup_dir, 0, sizeof s2oenv.patchbackup_dir);
	sprintf(s2oenv.patchbackup_dir, "%s/patch_backup", s2oenv.log_home);

	/***** key_dir *********/
	memset(s2oenv.key_dir, 0, sizeof s2oenv.key_dir);
	sprintf(s2oenv.key_dir, "%s", s2oenv.dat_home);

	/***** syspatch_yn *********/
	memset(s2oenv.syspatch_yn, 0, sizeof s2oenv.syspatch_yn);
	strcpy(s2oenv.syspatch_yn, "Y");
	/*
    if (!strcmp(s2oenv.company_code, "LPL")
        || !strcmp(s2oenv.company_code, "LPLNJ")
        || !strcmp(s2oenv.company_code, "LPLVM")
        || !strcmp(s2oenv.company_code, "LPLRS")
        || !strcmp(s2oenv.company_code, "ITOPS")
        || !strcmp(s2oenv.company_code, "LPLPO"))
    {
		strcpy(s2oenv.syspatch_yn, "Y");
	} else {
		strcpy(s2oenv.syspatch_yn, "N");
	}
	*/

	/***** upt_cu_system *********/
	memset(s2oenv.upt_cu_system, 0, sizeof s2oenv.upt_cu_system);
	get_cfg("UPT_CU_SYSTEM", s2oenv.upt_cu_system);

	return 0;

}

int loging_s2o_env()
{
    it_loging("libIT.a(%s): loging_s2o_env() bin_home(%s), cfg_home(%s), log_home(%s), dat_home(%s), mode(%s),"
            " mainhost(%s), mainhost_ip(%s), mainhost_nosend(%s), company_code(%s), oracle_home(%s),"
            " s2o_host(%s), cmd_port(%s), upt_port(%s), ld_lib_path(%s),"
            " type(%s), pid_dir(%s), patch_dir(%s), patchbackup_dir(%s), patchfail_dir(%s)\n"
            , S2O_DAEMON , s2oenv.bin_home, s2oenv.cfg_home, s2oenv.log_home, s2oenv.dat_home, s2oenv.mode, s2oenv.mainhost
            , s2oenv.mainhost_ip,s2oenv.mainhost_nosend,  s2oenv.company_code, s2oenv.oracle_home, s2oenv.s2o_host, s2oenv.cmd_port
            , s2oenv.upt_port, s2oenv.ld_lib_path, s2oenv.type, s2oenv.pid_dir
            , s2oenv.patch_dir, s2oenv.patchbackup_dir, s2oenv.patchfail_dir);
}
