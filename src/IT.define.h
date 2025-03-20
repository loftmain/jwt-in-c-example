#ifndef IT_DEFINE_H
#define IT_DEFINE_H

#include <sys/socket.h>
#include "config.h"

/* Int 값 범위 */
/*
short (int)                 	-32768 - 32767
unsigned short (int)        	0 - 65535
(signed) int                	-2147483648 - 2147483647
unsigned (int)              	0 - 4294967295
(signed) long (int)         	-2147483648 - 2147483647
unsigned long (int)         	0 - 4294967295
(signed) long long (int)    	-9223372036854775808 - 9223372036854775807
unsigned long long (int) 0  	- 18446744073709551615
*/
 
/* init.h */
/*************************************************************************************************/
#define _uInt_ unsigned int              /* %u */     /* 0 - 4294967295 */
#define _lInt_ long int                  /* %ld */    /* -2147483648 - 2147483647 */
#define _ulInt_ unsigned long int        /* %lu */    /* 0 - 4294967295 */
#define _llInt_ long long int            /* %lld */   /* -9223372036854775808 - 9223372036854775807 */
#define _ullInt_ unsigned long long int  /* %llu */   /* 0 - 18446744073709551615 */
/*************************************************************************************************/

/* IT.h */
/*************************************************************************************************/
#define OPENERR -10
#define INVALID -11

#define S2O_VERSION	"5.9.9.08-24"

/*#define DEBUG*/
/*#define ENGLISH*/

/* variable to determine the size of IT.dat */
static int it_data_size       = 50000000; 
/*static int it_data_size       = 500000;  */	

/* variable to determine the size of local.dat */
/*static int it_local_data_size = 10000000;*/
static int it_local_data_size = 50000000;

/* variable to determine the size of IT.log */
static int it_log_size        = 50000000;
/* static int it_log_size        = 30000000;*/

/* variable to determine the size of oracle-check-data */
static int ora_data_size        = 10000000;

static int save_rawdata_size        = 5000000;

/* message queue key for IT daemon this is for normal IT communication */
static key_t key = 7777;  
/* static key_t key = 117448289; */		/* Nokia message queue value */
static key_t keyl= 7778;  /* message queue for log server */
static char *device = "IT.dev";

#define  MSGSZ     4097
#define  RCVLENGTH 2049
#define  BACKUP    "IT"

#define VERSION_FILE "S2O_VERSION.cfg"

/* FILE NAME DEFINE */
#define DEFFILE_EVENT_RSLT_INIT		"IT_EVTRSLT"  /* 사용하지 않음 */
#define DEFFILE_EVENT_RSLT_DAT		"IT_EVTRSLT.dat" /* 사용하지 않음 */
#define DEFFILE_EVENT_RSLT_LOST		"IT_EVTRSLT.lost" /* 사용하지 않음 */
#define DEFFILE_EVENT_RSLT_CHK  	"chkpt_evtrslt.cfg" /* 사용하지 않음 */
#define DEFFILE_EVENT_RSLT_CNT  	3 /* 사용하지 않음 */

#define DEFFILE_EVENT_RSLT_INIT2	"IT_EVTRSLT2" /* 사용하지 않음 ( 2022/06/27) */
#define DEFFILE_EVENT_RSLT_DAT2		"IT_EVTRSLT2.dat"
#define DEFFILE_EVENT_RSLT_LOST2	"IT_EVTRSLT2.lost"
#define DEFFILE_EVENT_RSLT_CHK2  	"chkpt_evtrslt2.cfg"
#define DEFFILE_EVENT_RSLT_CNT2  	3

#define DEFFILE_SMS_LGD				"sms_lgd.cfg"
#define DEFFILE_TALK_LGD			"talk_lgd.cfg"
#define DEFFILE_TALK_DKCNS			"talk_dkcns.cfg"
#define DEFFILE_TALK_HYUMC			"talk_hyumc.cfg"

#define DEFFILE_HA_MON_SYNC			"ha_mon_sync.cfg"
#define DEFFILE_HA_STATUS			"ha_status.cfg"
#define DEFFILE_HA_STATUS_LAST		"ha_status_last.cfg"
#define DEFFILE_HA_STATUS_CHG		"ha_status_chg.cfg"
#define DEFMAX_HA_CNT				1    /* 현재는 1건만 처리되도록 */

#define DEFFILE_AWSRDS				"awsrds.cfg"

#define DEBUG_CALL_TALK					1
#define DEBUG_CALL_SMS					2
#define DEBUG_CALL_MAIL                 3
#define DEBUG_CALL_PHONE                4
#define DEBUG_CALL_MUST                 5  /* 무조건 loging */

#define DEF_LOG_WAKD				"IT_wakd.log"	/* IT.wakd 데몬 log */

typedef void    Sigfunc(int);   /* for signal handlers */

/* prototypes for our socket wrapper functions: see {Sec errors} */
#if defined(NCRUX)
int      Accept(int, struct sockaddr *, int *);
#else
int      Accept(int, struct sockaddr *, socklen_t *);
#endif
int      readable_timeo(int, int);
ssize_t  readn(int, void *, size_t);
ssize_t  writen(int, const void *, size_t);

Sigfunc *Signal(int, Sigfunc *);

/* use octarray for determining
 * if permission bits set
 */
static short octarray[9] = {
		0400,0200,0100,0040,0020,0010,
		0004,0002,0001
};

/* mnemonic codes for file permissions,
 * 10 chars long because of terminating null
 */
static char perms[] = "rwxrwxrwx";

#define LINUX_CENTOS    "CentOS"
#define LINUX_RHEL      "RHEL"
#define LINUX_REDHAT    "Redhat"
#define LINUX_UBUNTU    "Ubuntu"
#define LINUX_SUSE      "SUSE"
#define LINUX_DEBIAN    "Debian"
#define LINUX_FEDORA    "Fedora"
#define LINUX_ORACLE    "Oracle Linux"
#define LINUX_AMAZON    "Amazon Linux"

#define CALL_SJU_LOG	"IT_call_sju.log"		/* 세종대학교 CALL 연계 처리 로그 */

#define _SCAN_SEC_PATCH_ "%s/DAT/SCAN/SEC_PATCH"		/* pc scan(보안 패치) 파일 저장 위치(Master) */
#define _SCAN_ASSET_ "%s/DAT/SCAN/ASSET"		/* 자산 수집 저장 위치(Master) */
#define _SCAN_DIR_ "%s/SCAN"                            /* 자산 수집 위치(서버) */
#define _SCAN_DIR2_ "%s"                            /* 자산 수집 위치(서버) */
#define _BAK_NAME_      "bak"
#define _BAK_FAIL_NAME_ "bak_fail"


#define _ORAC_DUMP_DIR_		"%s/dump.orac"		/* IT.orac 작업 디렉토리 */
#define _ORA_THD_SESSION	2
#define _ORA_THD_ASM		3
#define _ORA_THD_QUERYMON	4

/*******************************************/
/* ASSET SCAN ******************************/
/*******************************************/
#define _DEF_DAT_       "dat"
#define _DEF_CFG_       "cfg"
#define _DEF_LOG_       "log"

#if defined(SUN2)
#define _DEF_RCFILE1_   "/etc/rc2.d/S73s2o-scn"
#elif defined(LINUX)
#define _DEF_RCFILE1_   "/etc/init.d/s2o-scn"
#define _DEF_RCFILE2_   "/etc/rc.d/init.d/s2o-scn"
#elif defined(AIX)
#define _DEF_RCFILE1_   "/etc/rc.d/rc2.d/S97s2o-scn"
#elif defined(HPUX)
#define _DEF_RCFILE1_   "/sbin/rc2.d/S210s2o-scn"
#else
#endif

#define _DEF_CMD_PORT_  "7703"
#define _DEF_UPT_PORT_  "7706"

#define _SAV_GPU_MEM_ "%s/_gpu_mem_%d.txt"

#define _SAV_SCHD_S2OVER_ "%s/_schd_s2over_%d.txt" /* IT.schd에서 agent 버전 정보 syslog로 전송 시간 저장 */

/*#define _RCVD_RECV_	"%s/dump/_rcvd.recv"*/
/*************************************************************************************************/


/***********************************************************************/
/* exception check time 설정 */
/***********************************************************************/
#define _DEF_EXCEPT_PRS_DOWN_ITEM_CHECK "Process_Down_Check(byProcess)"
#define _DEF_EXCEPT_CPU_USAGE_CHECK "Cpu_Usage_Check"
#define _DEF_EXCEPT_QUEUE_LENGTH_CHECK "Queue_Length_Check"
#define _DEF_EXCEPT_MEM_PHYSICAL_CHECK "Physical_Memory_Check"
#define _DEF_EXCEPT_MEM_SWAP_CHECK "Swap_Memory_Check"
#define _DEF_EXCEPT_DISK_IO_CHECK "Disk_I/O_Check"
#define _DEF_EXCEPT_FS_USAGE_ITEM_CHECK "FileSystem_Usage_Check(byFilesystem)"
#define _DEF_EXCEPT_PRS_LIMIT_ITEM_CHECK "Process_Limit_Check(byProcess)"
#define _DEF_EXCEPT_HW_CHECK "H/W_Check"
#define _DEF_EXCEPT_NIC_TRAFFIC_CHECK "Nic_Traffic_Check"
#define _DEF_EXCEPT_DISK_INODE_ITEM_CHECK "Disk_Inode_Check(byFilesystem)"
#define _DEF_EXCEPT_NETWORK_PORTCNT_ITEM_CHECK "Network_Port_Count_Check(byPort)"
#define _DEF_EXCEPT_SECURE_FILE_ITEM_CHECK "Secure_File_Check(bySecureFile)"

/* Master */
#define _DEF_EXCEPT_MASTER_SERVER_CHECK "Server_Check(byEquipment)"
#define _DEF_EXCEPT_MASTER_WEBPAGE_CHECK "WEBPage_Check(byWebPage)"
#define _DEF_EXCEPT_MASTER_POLLINGSNMP_CHECK "Polling_Snmp_Check(byEquipment)"
/***********************************************************************/

typedef struct _msgbuf {
   long mtype;
   char mtext[MSGSZ];
} MSGQ;


#endif

