/*
   $Id: get_s2o_hostname.c,v 2.0 2016/07/07 srp Exp $

   Copyright (c) 2016
             NewSystech Inc.  All rights reserved.

   2016-07-07
     * 서버의 hostname를 가져옴 ( DR, SUFFIX, FIXED 등 hostname 처리)
*/

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../IT.extern.h"

int get_s2o_hostname(char* _SERVER, char *_s2ohost, int _msg_force);

int get_s2o_hostname(char* _SERVER, char *_s2ohost, int _msg_force)
{
    char    suffix[30];
    char    drcenter[5];
    char    it_hostname_fix[10];
    char    fixed_hostname[256];
    char    temp_host[256];
    char    host2[256];

    memset(temp_host, 0, sizeof temp_host);

    memset(suffix, 0, sizeof suffix);
    get_cfg("IT_SUFFIX", suffix);

    memset(drcenter, 0, sizeof drcenter);
    get_cfg("IT_DRCENTER", drcenter);

    memset(it_hostname_fix, 0, sizeof it_hostname_fix);
    get_cfg("IT_HOSTNAME_FIX", it_hostname_fix);

    memset(fixed_hostname, 0, sizeof fixed_hostname);
    get_cfg("FIXED_HOSTNAME", fixed_hostname);

    memset(host2, 0, sizeof host2);
    gethostname(host2, sizeof host2);

    /* 도메인 "." 제거 위해 사용 */
    getitem('.', host2, temp_host, 1);

    if (strlen(_s2ohost) == 0 && strlen(temp_host) == 0) {
        return(-1);
    }

    /* suffix  변경 hostname_suffix */
    if(strlen(suffix) > 0)
    {
        strcat(temp_host, "_");
        strcat(temp_host, suffix);
    }

    /* drcenter 변경 */
    if(drcenter[0] == 'Y') strcat(temp_host, "_DR");

    /* hostname 고정으로 사용하는 경우 */
    if (it_hostname_fix[0]=='Y' && strlen(fixed_hostname) > 0) {
        strcpy(temp_host, fixed_hostname);
		/*
        if (strlen(temp_host) > 0 && strcmp(temp_host, _s2ohost)) {
            it_loging("libIT.a(%s): get_s2o_hostname() Host name of the message is set. (set hostname=%s)\n", _SERVER, fixed_hostname);
		}
		*/
    }

	if (strlen(temp_host) > 0) {
		if (strcmp(temp_host, _s2ohost)) {
			if (strlen(_s2ohost) > 0)
				it_loging("libIT.a(%s): get_s2o_hostname() s2o management hostname changed.(%s -> %s), real hostname(%s)\n", _SERVER, _s2ohost, temp_host, host2);
			else if ( strcmp(temp_host, host2)) 
				it_loging("libIT.a(%s): get_s2o_hostname() s2o management hostname.(%s), real hostname(%s)\n", _SERVER, temp_host, host2);
			else if ( _msg_force == 1) it_loging("libIT.a(%s): get_s2o_hostname() hostname.(%s)\n", _SERVER, temp_host);

			strcpy(_s2ohost, temp_host);
		}
		return 1;
	} else {
		if (strlen(_s2ohost) == 0) return -1;
	}
	return 0;
}

