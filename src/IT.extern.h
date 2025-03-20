#ifndef IT_EXTERN_H
#define IT_EXTERN_H

#include <sys/socket.h>
#include "config.h"
#include "IT.define.h"
#include "libIT.h"

/* message queue buf definition */
/*
typedef struct _msgbuf {
   long mtype;
   char mtext[MSGSZ];
} MSGQ;
*/

/* create an array of hosts */
extern struct host_struct {
  	char 	name[80];
  	char 	ip[16];
	char	type[7];
	char 	company[10];
	int		timeout;
	int		attempt;
	char	ELevel[5];
	int		icontinue;
	long 	connport_time;	/* 21, 22 등 port 연결 확인 시간 */
	char 	notchkfrom[10];
	char	notchkto[10];
	char 	notchksyslog[5];
	char 	notchkperf[5];
	int		evt_lvl_mincnt; /* 이벤트 발생을 위한 연속 최소수 */
	int		evt_lvl_skipcnt;
	char	chkCrFile[5]; 	/* 파일 생성 점검 여부 */
	char	chkTimeSync[5];	/* 시간 점검 여부 */
	char	gapTimeSync[10]; /* 시간 점검시 허용 범위 지정 (기본 1분) */
	/*char	SyncTime[10];*/ 	/* 시간 차이 수정 ( min ) */
  	int 	num_err;
	int		wlog_sys01;
	int		wlog_sys03;
} *hosts;

extern struct router_struct {
  	char 	name[64];
  	char 	ip[20];
  	int 	num_err;
	char	type[7];
	char	company[10];
	int		timeout;
	int		attempt;
	char	ELevel[5];
	int		nwarning;	/* 연속 발생한 warning 수 */
	int		latency;	/* 지연시간 모니터링 임계치 */
	int		mon_daemon;	/* 모니터링 deamon 여부 ( 1: 모니터링 daemon, 0: 모니터령 deamon 아님 ) */
	char 	notchkfrom[10];
	char	notchkto[10];
	int		evt_lvl_mincnt; /* 이벤트 발생을 위한 연속 최소수 */
	int		evt_lvl_skipcnt;
} *routers;

/* create an array of defined syslog messages substring */
extern struct syslog_struct
{
  	char 	msgid[8];
  	char 	msgstr[256];
  	char 	msgchk[2];
  	char 	msgupper[2];
} *syslog_str;

extern struct syslog_occur_struct
{
  	char 	msgid[8];
  	char 	msgstr[256];
	time_t	starttime;
	time_t	lasttime;
	int		count;
} *syslog_occurs;


/* 사용자 정의한 process 구조체 */
extern struct define_process
{
  	char 	processName[256];
	char	processPattern[256];
  	char 	processDisplay[384];
  	char 	msgid[8];
  	char 	msgid_run[8];
	char	ftime[5];
	char	ttime[5];
  	int 	minRunCount;
	int		maxRunCount;
	char	autorestart[2];
	char	autocmd[256];
	char	autoaction[2];
	char	actioncmd[256];
	char	cluster[5];		/* Y/y/F/f : 파일시스템, I/i : IP address,  N : 설정되지 않음 */
	char	clustername[64];
	int		cluster_active; /* cluster 사용시 현재 상태 0:사용하지않음, 1:Active, 2: StandBy */
	time_t 	cluster_failtime;  /* cluster 사용시 Active/StandBy정보 가져오지 못한 마지막 시간 저장 */
	char	alias[128];
	char	owner[64];
	int		o_count;	/* occurrence count */
	int		err_down;	/* down error 발생 수 (o_count 연동됨) */
	int		err_run;	/* run error 발생 수 (o_count 연동됨) */
  	int 	num_err;
	char	ha_yn[5];	/* HA 여부 */
	time_t	downdumptm;	/* 현재 process down으로 마지막으로 dump한 시간 */
	int		downflag;	/* 마지막 점검시 down 여부 */
	char    pid_bracket[5]; /* aix [프로세스명] 으로 변경되는 경우 점검여부 */
	int     pid; /* pidbracket=Y 로 적용된 경우 프로세스의 pid가 저장됨 */
} *dProcess;

/* 시스템에서 수행되고 있는 process 저장 구조체 */
extern struct run_process
{
	int		pid;
	int		ppid;
	char	stat[5];
	char	processName[256];
	/* char	processName[1024];*/
	/* char	*processName; */
	char	owner[64];
} *rProcess;

/* 시스템에서 수행되고 있는 process 저장 구조체로 runcount min설정이 되어 있는 경우에 
   이벤트 발생시 down 된 프로세스명을 알기 위해 사용됨  */
extern struct acc_process_list
{
	int		pid;
	int		ppid;
	char	stat[5];
	char	processName[256];
	/* char	*processName; */
	char	owner[64];
} *aProcess_list;

/* 시스템에서 수행되고 있는 process cpu 저장 구조체 */
extern struct run_pcu
{
	char	processName[256];
	int		pid;
	int		ppid;
	char	owner[24];
	int		memory;
	int		sz;
	char	tty[24];
	char	state[16];
	char	stime[24];
	float	cpuusage;
	int		cputime;
} *runPcu;

extern struct def_pcu
{
	char	processName[256];
	char	uncheck[2];
	char	owner[24];
	int		memory;
	float	cpuusage;
	int		cputime;
	float	f_cpuusage;
	int		f_cputime;
	char	item[8];
	char	command[128];
	char	save[2];
	int		occurence;
	char	Level[2];
} *defPcu;

extern struct def_job
{
	char jobName[128];
	char cycle[10];
	char ftime[6];
	char fday[3];
	char fweek[3];
	char ttime[8];
	char tday[3];
	char tweek[3];
	char logPath[256];
	char logPath_org[256];
	char msgcode[8];
	char ELevel[2];
	long position;
	int	 chgmode; 	
			/* 		
				0: 변화없음, 	1:yyyymmdd, 	2:yyyymmdd-1, 	3:ddmmyyyy, 	4:ddmmyyyy-1,
				5: mmddyyyy, 	6:mmddyyyy-1, 	7:yymmdd, 		8:yymmdd-1,		9:mmdd,			10:mmdd-1
			*/
			/*
				추가
				11:yyyy.mm.dd, 12:yyyymmdd-hh, 13:yyyy-mm-dd, 14:mm-dd, 15:yyyymm, 16:yyyymmdd/yyyyymmdd,
				17:<dd>, 	18:yyyymmdd_hh, 19:yyyymmdd_h
			*/
	int  nlogPath; /* yyyymmdd 시작위치 */
	int  nftime; /* start check time*/
	int	 status;   
			/* 
				0:비수행, 1:작업시작, 2:에러(0상태중에러), 3:에러(1상태중에러), 
				3:10분이상 작업 시작 안됨, 4: 완료 
			*/
	int		openerr;	/* 파일 존재하는데 openerr 발생시 */
} *defJob;

extern struct def_log
{
	char	logName[128];
	char 	msgcode[8];
	char	ELevel[2];
	char 	logPath[256];
	char 	logPath_org[256];
	int		chgmode_new; /* <[yyyy]>,<[yy]>,<[mm]>,<[dd]>,<[dd-1]>,<[hh]>,<[h]> */
						 /* 0:변화없음,	1:<[yy]>/<[yyyy]>, 2:<[mm]>, 3:<[dd]>/<[dd-1]>, 4: <[hh]>/<[h]> */
	int		chgmode; 
			/* 		
				0: 변화없음, 	1:yyyymmdd, 	2:yyyymmdd-1, 	3:ddmmyyyy, 	4:ddmmyyyy-1,
				5: mmddyyyy, 	6:mmddyyyy-1, 	7:yymmdd, 		8:yymmdd-1,		9:mmdd,			10:mmdd-1
			*/
			/*
				추가
				11:yyyy.mm.dd, 12:yyyymmdd-hh, 13:yyyy-mm-dd, 14:mm-dd, 15:yyyymm, 16:yyyymmdd/yyyyymmdd
				17:<dd>, 	18:yyyymmdd_hh, 19:yyyymmdd_h
			*/
	int		chgmode_time; /* 0: 변화 없음,	1:hh.mi.ss,	2:hhmiss, 3: hhmi */
	long 	position;
	int 	nlogPath; /* yyyymmdd 시작위치 */
	int 	nlogPath_time; /* hhmiss 시작위치 */
	int		openerr;	/* 파일 존재하는데 openerr 발생시 */
	char	monfrom[5], monto[5]; 
	char 	monweek[8];
	char	filecheck1[5], filecheck2[5];
	char	allevent_yn[5];		/* 모든 라인 이벤트 발생 */
	char	newlogcheck[5]; /* 신규 로그 생성 유무 체크 여부 */
	int		newlogdelaytime; /* 신규 로그 미생성으로 간주되는 시간 (기본 30분) */
	char	newlogcheckaction[512]; 
	int 	isfileitv;	/* 파일 존재여부 interval */
	time_t	newloglasttime; /* 마지막으로 파일 읽은 시간 */
	time_t	newlogchecktime; /* 마지막 체크 시간 */
	char	newlogcheck_event[5];
	char	ispattern[5]; /* 패턴 설정이 존재하는지 여부 */
	time_t	filelasttime; /* 마지막 파일 시간(hhmiss 형태의 파일 존재시간 체크를 위해) */
	time_t  filechecktime; /*마지막 파일 존재 이벤트 시간(hhmiss 형태의 파일 존재시간 체크를 위해)  */
	char	filecheck_event[5]; /* 파일 존재 체크시 이벤트 발생 여부(hhmiss 형태의 파일 존재시간 체크를 위해)*/
	char 	charset[10]; /* 한양대의료원 마스터 임시 추가 ( 2022/10/05 ) */
	int		isfile; /* 2023/03/07 파일 존재여부 ( -1: 확인 전, 0:비존재, 1: 존재 ), 감시 파일이 없다가 추가되는 경우 처음부터 읽을지 여부를 확인을 위해 사용함  */
} *deflog;
 
extern struct def_jobpattern
{
	char	jobname[128];
	char 	msgcode[8];
	char	patterns[10][129];
	char	options[10][10]; /* and, or, except */
	char	svcname[128];
	int		mode;			/* 3:이상 발생시 한번, 2: 매 x건 마다 발생, 1: max count 이상시, default  */
	int		duration;
	int		max_count;
	long	lastevttime;	/* 마지막 발생한 이벤트 시간 (이상 발생시 한번 처리용) */
	long	lastactiontime; /* 마지막 action 실행한 시간 */
	char	actioncmd[256];	/* action script */
	char	msgupper[5]; /* 대소문자 구별없이 체크 여부 */
} *defJobPattern;

extern struct def_protocol
{
    int     port;
    int     warning;
    int     critical;
    int     establish;
    int     wait;								/* Establish status 외의 count */
    int     flag;								/* 현재 사용 안함 */
} *defProtocol;

extern struct def_network
{
	char service[32];
    char port[16];
    int warning;
    int critical;
	int	fatal;
    int establish;
    int wait;								/* Establish status 외의 count */
    int flag;								/* 현재 사용 안함 */
} *defNetwork;

extern struct allow_hostname
{
	char    hostname[51];
	char    co_code[6];
	long 	lastTmPAVI[10]; 	/* 01: Agent, 02: Oracle, 03: mssql, 04: tibero, 05: db2, 06: mariadb */
	char 	lastMsgPAVI[10][128];
	long 	lastTmPOSI[5]; 	/* 01 : os 정보 , 02 : h/w 정보 ( cpu/mem ) */
	char 	lastMsgPOSI[5][128];
} *allowHostname;

extern struct def_stddev
{
	char    item[8];
	float   avg;
	float   stddev;
} *defStddev;

extern struct def_sysmods
{
    char    sysmodsName[256];
	char    cycle[10];
	char    ftime[6];
	char    fday[3];
	char    fmonth[3];
	char    fyear[5];
	char    fweek[3];
	char    ttime[8];
	char	fhour[3];
	char	fmin[4];
	char    tday[3];
	char    tmonth[3];
	char    tyear[5];
	char    tweek[3];
	char	thour[3];
	char	tmin[3];
} *defSysmods;

extern struct def_securefile
{
	char	file[256];
	char	flag_size[2];
	int		uid;
	char	flag_uid[2];
	int		gid;
	char	flag_gid[2];
	char	perms[10];
	char	flag_perms[2];
	int		mtime;
	char	flag_mtime[2];
	_llInt_		size;		/* 2022/11/03 int -> _llInt_ */
	_llInt_		maxsize;	/* 2022/11/03 int -> _llInt_ */
	_llInt_ 	minsize;	/* 2022/11/03 int -> _llInt_ */
	int		type; 			/* 1: file, 2: directory */
	int 	maxcount;
	char	msgcode[10];
} *defSecureFile;

extern struct def_securefile_cmd
{
	char	file[256];
	int		uid;
	char	uid_name[25];
	int		gid;
	char	gid_name[25];
	char	perms[10];
	char	perms_char[6];
	int		type; 				/* 1: file, 2: directory */
	char	msgcode[10];
	int		level_int;			/* Directory check level : Full check of subfolders when not specified */
} *defSecureFileCmd;

extern struct run_mounted
{
    char    filesystem[128];
    char    mounted[128];
} *rMounted;

/* IT.wrtd에서 제외할 대상을 정의시 사용 */
extern struct def_except_host
{
    char name[64];
    char cocode[10];
    char perf_yn[10];
    char svr_dn_msg_yn[10];
    char svr_msg_yn[10];
	char tm_from[20];
	char tm_to[20];
}*defexcept_host;

/* IT.wrtd에서 허용할 대상을 정의시 사용 */
extern struct def_allow_host
{
    char name[64];
    char cocode[10];
	char is_reg[5];
	int  inew;	/* 정의한 위치 ( 0: 기존(파일 read한 대상), 1: 신규 ) */
}*defallow_host;

extern struct def_sysmods_lst
{
	char hostname[64];
	char cocode[10];
	char from[32];
	char to[32];
}*defsysmods_lst;

extern struct def_ha
{
	char ha_type[32];
	char ha_server_ip[32];
	char ha_server_host[64];
	char ha_filesystem[256];
	char ha_ipaddress[32];
	char ha_role[10];
	char status_set[32];  /* 설정상태 : ACTIVE/STANDBY/NODE */
	char status_cur[32];  /* 현재 점검 상태 : ACTIVE/STANDBY/NODE */
	char status_last[32]; /* 이전 점검 상태 : ACTIVE/STANDBY/NODE */
}*defha;

extern struct ha_list
{
	char    status[32];  /* ACTIVE/STANDBY/NODE */
} *halist;

extern struct def_s2oenv
{
    char env_home[256]; /* IT.cfg 파일의 위치 */
    char env_file[512]; /* IT.cfg path */
    char bin_home[256];
    char cfg_home[270];
    char log_home[270];
    char dat_home[270];
    char mode[5];
    char mainhost[50];
	char mainmaster_ip[32]; /*  sub master에서 main master를 설정할 때 사용*/
    char mainhost_nosend[10]; /* 이 경우 mainhost_ip 로만 전송 */
    char mainhost_ip[20];
    char company_code[10];
    char oracle_home[256];
    char s2o_host[80];
    char cmd_port[10];
    char upt_port[10];
    char ld_lib_path[256];
    char type[5];
    char pid_dir[300];
    char patch_dir[300];
    char patchbackup_dir[300];
    char patchfail_dir[300];
    char key_dir[270];
    char syspatch_yn[2];
	char upt_cu_system[2]; /* cu_system table update 여부 */
	int chkonly; /* 자산 스캔 점검만 */
} s2oenv;

extern char S2O_DAEMON[64];
extern char S2O_PIDFILE[256];
extern int IS_NOS2O_AGENT;
extern int IS_WLOG_LOGING; /* 1: wlog 발생시 loging으로 변경함 (DEBUG 용) */


/***********************************************************************/
/* exception check time 설정 */
/***********************************************************************/
extern struct except_check_time {
    char Item[64];
    char Subitem[256];
    char Cycle[10];
    char From[20];
    char From_week[20];
    char To[20];
    char To_week[20];
    char Apply[5];
    char Note[128];
    char Subitemplus[256];
} *stExceptChktime;
extern char    except_chktimecfg[256];
extern time_t  except_chktime_mtime;
extern int     cnt_except_chktime;
/***********************************************************************/


/***********************************************************************/
/* account 설정 */
/***********************************************************************/
extern struct account_struct {
    char name[128];
    char password[256];
    char uid[16];
    char gid[16];
    char home[256];
    char shell[64];
    char description[256];
    int passerr;
    int default_user;
    int LOCK;
    int NOPASS;
    int salt_fail;
    char last_time[20];
    char last_host[64];
    char last_pwchg[20];
    char last_loginget[5];
    char status[32];
    char expire_period[30];
    char expire_time[30];   /* yyyymmdd hh24:mi:ss */
    char expire_date[30];   /* yyyymmdd */
    int remain_expire;
    int sort_find;
    int maxday;
} *accounts;
extern int account_num;

extern struct acc_expire_check {
    char apply[5];
    int  hour;
    int  min;
    int warn;
    int crit;
    char lastchktime[20];
    char exclude_expired[5];
    char exclude_lock[5];
}acc_expire_chk;

extern struct acc_expire_except {
    char name[101];
}*acc_expire_exp;
extern int acc_expire_exp_cnt;
/***********************************************************************/

#endif

