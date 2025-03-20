
/*
   $Id: read_ha_status_set.c,v 1.0 2015/06/05 srp Exp $

   Copyright (c) 2015
             NewSystech Inc.  All rights reserved.

   2015-06-05
     * ha_status.cfg ���Ͽ��� HA ���� Ȯ��
*/

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include "../IT.extern.h"
#include "../msgid_s2o.h"

int read_ha_status_set(char* SERVER, char* ha_status_cfg, int* cnt_ha_list, long* ha_status_mtime, int* daemon_start)
{
    /* HA ���� Ȯ�� */

    struct stat statbuf;
    char buf[256];
    char tmp_status[64];
    char ITEM[32];
    int i;
    int cnt;
	int i_reload_cfg = 0;

	if (stat(ha_status_cfg, &statbuf) == 0) {  /* ���� ���� �����ϸ� */
		if ((*ha_status_mtime) != statbuf.st_mtime) { /* ���� ������ �����ϴ� ��� */
			*ha_status_mtime = (long)statbuf.st_mtime;
			memset(buf, 0, sizeof buf);
			get_cfg2(ha_status_cfg, "HA_CNT", buf);
			if (strlen(buf) == 0) cnt = 0;
			else cnt = atoi(buf);

            if (cnt < 1) { /* ������ ������ ���(������ ���� ���) */
                for(i = 0; i < *cnt_ha_list && i < DEFMAX_HA_CNT ; i++) {
                    if (!strcmp(halist[i].status, "STANDBY") || !strcmp(halist[i].status, "ACTIVE")) {
						if (!strcmp(SERVER, "IT.schd")) {
                        	it_loging("libIT.a(%s): read_ha_status_set() HA process monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
                        	it_loging("libIT.a(%s): read_ha_status_set() HA filesystem monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
                        	it_loging("libIT.a(%s): read_ha_status_set() HA inodes monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
							wlog(MSG_W_HAC08, STR_W_HAC08_1);
							it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_1);
							wlog(MSG_W_HAC08, STR_W_HAC08_2);
							it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_2);
							wlog(MSG_W_HAC08, STR_W_HAC08_4);
							it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_4);
						} else if (!strcmp(SERVER, "IT.orac")) {
                        	it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
							wlog(MSG_W_HAC08, STR_W_HAC08_3);
							it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_3);
						} else if (!strcmp(SERVER, "IT.sndd")) {
                        	it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
							/* wlog(MSG_W_HAC08, STR_W_HAC08_3); */
							it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_3);
						}
                    }
                }

                *cnt_ha_list = 0;
                halist = (struct ha_list *) realloc(halist, (1 * sizeof (struct ha_list)));
                if (halist == NULL) {
                    it_loging("libIT.a(%s): read_ha_status_set() ha_list struct realloc error.\n", SERVER);
                }
                strcpy(halist[*cnt_ha_list].status, "NONE");

                if ( strlen(buf) == 0 ) {
                    it_loging("libIT.a(%s): read_ha_status_set() HA_CNT item is not exist in the file(%s).\n", SERVER, ha_status_cfg);
                } else if (atoi(buf) < 1) {
                    it_loging("libIT.a(%s): read_ha_status_set() HA_CNT=%d in the file(%s).\n", SERVER, atoi(buf), ha_status_cfg);
                }
            } else {
                if (*cnt_ha_list > cnt) { /* ������ ������ �����ϴ� ���(������ ���� ���) */
                    for(i = cnt; i < *cnt_ha_list && i < DEFMAX_HA_CNT; i++) {
                        if (!strcmp(halist[i].status, "STANDBY") || !strcmp(halist[i].status, "ACTIVE")) {
							if (!strcmp(SERVER, "IT.schd")) {
                            	it_loging("libIT.a(%s): read_ha_status_set() HA process monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
                            	it_loging("libIT.a(%s): read_ha_status_set() HA filesystem monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
                            	it_loging("libIT.a(%s): read_ha_status_set() HA inodes monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
								wlog(MSG_W_HAC08, STR_W_HAC08_1);
								it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_1);
								wlog(MSG_W_HAC08, STR_W_HAC08_2);
								it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_2);
								wlog(MSG_W_HAC08, STR_W_HAC08_4);
								it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_4);
							} else if (!strcmp(SERVER, "IT.orac")) {
                            	it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
								wlog(MSG_W_HAC08, STR_W_HAC08_3);
								it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_3);
							} else if (!strcmp(SERVER, "IT.sndd")) {
                            	it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
								/* wlog(MSG_W_HAC08, STR_W_HAC08_3); */
								it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_3);
							}
                        }
                    }
                }

                /* ����� 1�Ǹ�(A-S) */

                for(i=0; i < 1; i++) {
                    memset(tmp_status, 0, sizeof tmp_status);
                    memset(ITEM, 0, sizeof ITEM);
                    sprintf(ITEM, "STATUS_%d", i+1);
                    if ( get_cfg2(ha_status_cfg, ITEM, tmp_status) < 0) {
                        it_loging("libIT.a(%s): read_ha_status_set() %s item is not exist in the file(%s).\n", SERVER, ITEM, ha_status_cfg);
                        strcpy(tmp_status, "NONE");
                    }
                    if ( i < *cnt_ha_list ) { /* ���� ��ϵ� ��� */
                        if (!strcmp(tmp_status, "STANDBY")) {
                            if (strcmp(halist[i].status, "STANDBY")) {
                                strcpy(halist[i].status, "STANDBY");
								if (!strcmp(SERVER, "IT.schd")) {
                                	it_loging("libIT.a(%s): read_ha_status_set() HA process monitoring ended. (status=%s)\n", SERVER, halist[i].status);
                                	it_loging("libIT.a(%s): read_ha_status_set() HA filesystem monitoring ended. (status=%s)\n", SERVER, halist[i].status);
                                	it_loging("libIT.a(%s): read_ha_status_set() HA inodes monitoring ended. (status=%s)\n", SERVER, halist[i].status);
									wlog(MSG_W_HAC08, STR_W_HAC08_1);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_1);
									wlog(MSG_W_HAC08, STR_W_HAC08_2);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_2);
									wlog(MSG_W_HAC08, STR_W_HAC08_4);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_4);
								} else if (!strcmp(SERVER, "IT.orac")) {
                                	it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring ended. (status=%s)\n", SERVER, halist[i].status);
									wlog(MSG_W_HAC08, STR_W_HAC08_3);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_3);
								} else if (!strcmp(SERVER, "IT.sndd")) {
                                	it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring ended. (status=%s)\n", SERVER, halist[i].status);
									/* wlog(MSG_W_HAC08, STR_W_HAC08_3); */
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_3);
								}
                            }
                        } else if (!strcmp(tmp_status, "ACTIVE")) {
                            if (strcmp(halist[i].status, "ACTIVE")) {
                                strcpy(halist[i].status, "ACTIVE");
								i_reload_cfg = 1; /* ����͸� ���� ���� �ٽ� read */
								if (!strcmp(SERVER, "IT.schd")) {
                                	it_loging("libIT.a(%s): read_ha_status_set() HA process monitoring started. (status=%s)\n", SERVER, halist[i].status);
                                	it_loging("libIT.a(%s): read_ha_status_set() HA filesystem monitoring started. (status=%s)\n", SERVER, halist[i].status);
                                	it_loging("libIT.a(%s): read_ha_status_set() HA inodes monitoring started. (status=%s)\n", SERVER, halist[i].status);
									wlog(MSG_W_HAC07, STR_W_HAC07_1);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC07_1);
									wlog(MSG_W_HAC07, STR_W_HAC07_2);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC07_2);
									wlog(MSG_W_HAC07, STR_W_HAC07_4);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC07_4);
								} else if (!strcmp(SERVER, "IT.orac")) {
                                	it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring started. (status=%s)\n", SERVER, halist[i].status);
									wlog(MSG_W_HAC07, STR_W_HAC07_3);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC07_3);
								} else if (!strcmp(SERVER, "IT.sndd")) {
                                	it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring started. (status=%s)\n", SERVER, halist[i].status);
									/* wlog(MSG_W_HAC07, STR_W_HAC07_3); */
									it_loging("%s: read_ha_status_set() %s\n", SERVER, STR_W_HAC07_3);
								}
                            }
                        }
                        strcpy(halist[i].status, tmp_status);
                    } else { /* �߰��� ��� */
                        if (!strcmp(tmp_status, "ACTIVE")) {
							i_reload_cfg = 1; /* ����͸� ���� ���� �ٽ� read */
                        }
                        halist = (struct ha_list *) realloc(halist, ((*cnt_ha_list)+1) * sizeof (struct ha_list));
                        if (halist == NULL) {
                            it_loging("libIT.a(%s): read_ha_status_set() ha_list struct realloc error.\n", SERVER);
                        }
                        strcpy(halist[*cnt_ha_list].status, tmp_status);
                        (*cnt_ha_list)++;

						if ((*daemon_start) == 0) { /* daemon ���۽ÿ��� �߻����� �ʵ��� */
							if (!strcmp(SERVER, "IT.schd")) {
                        		it_loging("libIT.a(%s): read_ha_status_set() HA process monitoring inserted. (status=%s)\n", SERVER, halist[i].status);
                       		 	it_loging("libIT.a(%s): read_ha_status_set() HA filesystem monitoring inserted. (status=%s)\n", SERVER, halist[i].status);
                       		 	it_loging("libIT.a(%s): read_ha_status_set() HA inodes monitoring inserted. (status=%s)\n", SERVER, halist[i].status);
                        		if (!strcmp(tmp_status, "ACTIVE")) {
									wlog(MSG_W_HAC07, STR_W_HAC07_1);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC07_1);
									wlog(MSG_W_HAC07, STR_W_HAC07_2);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC07_2);
									wlog(MSG_W_HAC07, STR_W_HAC07_4);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC07_4);
                        		} else if (!strcmp(tmp_status, "STANDBY")) {
									wlog(MSG_W_HAC08, STR_W_HAC08_1);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_1);
									wlog(MSG_W_HAC08, STR_W_HAC08_2);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_2);
									wlog(MSG_W_HAC08, STR_W_HAC08_4);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_4);
								}
							} else if (!strcmp(SERVER, "IT.orac")) {
                        		it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring inserted. (status=%s)\n", SERVER, halist[i].status);
                        		if (!strcmp(tmp_status, "ACTIVE")) {
									wlog(MSG_W_HAC07, STR_W_HAC07_3);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC07_3);
                        		} else if (!strcmp(tmp_status, "STANDBY")) {
									wlog(MSG_W_HAC08, STR_W_HAC08_3);
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_3);
								}
							} else if (!strcmp(SERVER, "IT.sndd")) {
                        		it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring inserted. (status=%s)\n", SERVER, halist[i].status);
                        		if (!strcmp(tmp_status, "ACTIVE")) {
									/* wlog(MSG_W_HAC07, STR_W_HAC07_3); */
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC07_3);
                        		} else if (!strcmp(tmp_status, "STANDBY")) {
									/* wlog(MSG_W_HAC08, STR_W_HAC08_3); */
									it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_3);
								}
							}
						}
                    }
                }
            }
        }
    } else { /* ���� ������ �������� �ʴ� ��� */
        if ( *cnt_ha_list > 0) { /* ������ ������ ������ �����ϸ�(������ ���� ���) */
            for(i = 0; i < *cnt_ha_list && i < DEFMAX_HA_CNT; i++) {
                if (!strcmp(halist[i].status, "STANDBY") || !strcmp(halist[i].status, "ACTIVE")) {
					if (!strcmp(SERVER, "IT.schd")) {
                    	it_loging("libIT.a(%s): read_ha_status_set() HA process monitoring deleted. (status=%s)\n", SERVER,  halist[i].status);
                    	it_loging("libIT.a(%s): read_ha_status_set() HA filesystem monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
                    	it_loging("libIT.a(%s): read_ha_status_set() HA inodes monitoring deleted. (status=%s)\n", SERVER, halist[i].status);
						wlog(MSG_W_HAC08, STR_W_HAC08_1);
						it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_1);
						wlog(MSG_W_HAC08, STR_W_HAC08_2);
						it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_2);
						wlog(MSG_W_HAC08, STR_W_HAC08_4);
						it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_4);
					} else if (!strcmp(SERVER, "IT.orac")) {
                    	it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring deleted. (status=%s)\n", SERVER,  halist[i].status);
						wlog(MSG_W_HAC08, STR_W_HAC08_3);
						it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_3);
					} else if (!strcmp(SERVER, "IT.sndd")) {
                    	it_loging("libIT.a(%s): read_ha_status_set() HA oracle monitoring deleted. (status=%s)\n", SERVER,  halist[i].status);
						/* wlog(MSG_W_HAC08, STR_W_HAC08_3); */
						it_loging("libIT.a(%s): read_ha_status_set() %s\n", SERVER, STR_W_HAC08_3);
					}
                }
            }
        }
        *cnt_ha_list = 0;
        halist = (struct ha_list *) realloc(halist, (1 * sizeof (struct ha_list)));
        if (halist == NULL) {
            it_loging("libIT.a(%s): read_ha_status_set() ha_list struct realloc error.\n", SERVER);
        }
        strcpy(halist[*cnt_ha_list].status, "NONE");
    }

	(*daemon_start) = 0;
	return i_reload_cfg;
}
