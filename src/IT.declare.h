#ifndef IT_DECLARE_H
#define IT_DECLARE_H

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
struct host_struct {
  	char 	name[80];
  	char 	ip[16];
	char	type[7];
	char 	company[10];
	int		timeout;
	int		attempt;
	char	ELevel[5];
	int		icontinue;
	long 	connport_time;	/* 21, 22 �� port ���� Ȯ�� �ð� */
	char 	notchkfrom[10];
	char	notchkto[10];
	char 	notchksyslog[5];
	char 	notchkperf[5];
	int		evt_lvl_mincnt; /* �̺�Ʈ �߻��� ���� ���� �ּҼ� */
	int		evt_lvl_skipcnt;
	char	chkCrFile[5]; 	/* ���� ���� ���� ���� */
	char	chkTimeSync[5];	/* �ð� ���� ���� */
	char	gapTimeSync[10]; /* �ð� ���˽� ��� ���� ���� (�⺻ 1��) */
	/*char	SyncTime[10];*/ 	/* �ð� ���� ���� ( min ) */
  	int 	num_err;
	int		wlog_sys01;
	int		wlog_sys03;
} *hosts;

struct router_struct {
  	char 	name[64];
  	char 	ip[20];
  	int 	num_err;
	char	type[7];
	char	company[10];
	int		timeout;
	int		attempt;
	char	ELevel[5];
	int		nwarning;	/* ���� �߻��� warning �� */
	int		latency;	/* �����ð� ����͸� �Ӱ�ġ */
	int		mon_daemon;	/* ����͸� deamon ���� ( 1: ����͸� daemon, 0: ����ͷ� deamon �ƴ� ) */
	char 	notchkfrom[10];
	char	notchkto[10];
	int		evt_lvl_mincnt; /* �̺�Ʈ �߻��� ���� ���� �ּҼ� */
	int		evt_lvl_skipcnt;
} *routers;

/* create an array of defined syslog messages substring */
struct syslog_struct
{
  	char 	msgid[8];
  	char 	msgstr[256];
  	char 	msgchk[2];
  	char 	msgupper[2];
} *syslog_str;

struct syslog_occur_struct
{
  	char 	msgid[8];
  	char 	msgstr[256];
	time_t	starttime;
	time_t	lasttime;
	int		count;
} *syslog_occurs;


/* ����� ������ process ����ü */
struct define_process
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
	char	cluster[5];		/* Y/y/F/f : ���Ͻý���, I/i : IP address,  N : �������� ���� */
	char	clustername[64];
	int		cluster_active; /* cluster ���� ���� ���� 0:�����������, 1:Active, 2: StandBy */
	time_t 	cluster_failtime;  /* cluster ���� Active/StandBy���� �������� ���� ������ �ð� ���� */
	char	alias[128];
	char	owner[64];
	int		o_count;	/* occurrence count */
	int		err_down;	/* down error �߻� �� (o_count ������) */
	int		err_run;	/* run error �߻� �� (o_count ������) */
  	int 	num_err;
	char	ha_yn[5];	/* HA ���� */
	time_t	downdumptm;	/* ���� process down���� ���������� dump�� �ð� */
	int		downflag;	/* ������ ���˽� down ���� */
	char	pid_bracket[5]; /* aix [���μ�����] ���� ����Ǵ� ��� ���˿��� */
	int		pid; /* pidbracket=Y �� ����� ��� ���μ����� pid�� ����� */
} *dProcess;

/* �ý��ۿ��� ����ǰ� �ִ� process ���� ����ü */
struct run_process
{
	int		pid;
	int		ppid;
	char	stat[5];
	char	processName[256];
	/* char	processName[1024];*/
	/* char	*processName; */
	char	owner[64];
} *rProcess;

/* �ý��ۿ��� ����ǰ� �ִ� process ���� ����ü�� runcount min������ �Ǿ� �ִ� ��쿡 
   �̺�Ʈ �߻��� down �� ���μ������� �˱� ���� ����  */
struct acc_process_list
{
	int		pid;
	int		ppid;
	char	stat[5];
	char	processName[256];
	/* char	*processName; */
	char	owner[64];
} *aProcess_list;

/* �ý��ۿ��� ����ǰ� �ִ� process cpu ���� ����ü */
struct run_pcu
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

struct def_pcu
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

struct def_job
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
				0: ��ȭ����, 	1:yyyymmdd, 	2:yyyymmdd-1, 	3:ddmmyyyy, 	4:ddmmyyyy-1,
				5: mmddyyyy, 	6:mmddyyyy-1, 	7:yymmdd, 		8:yymmdd-1,		9:mmdd,			10:mmdd-1
			*/
			/*
				�߰�
				11:yyyy.mm.dd, 12:yyyymmdd-hh, 13:yyyy-mm-dd, 14:mm-dd, 15:yyyymm, 16:yyyymmdd/yyyyymmdd,
				17:<dd>, 	18:yyyymmdd_hh, 19:yyyymmdd_h
			*/
	int  nlogPath; /* yyyymmdd ������ġ */
	int  nftime; /* start check time*/
	int	 status;   
			/* 
				0:�����, 1:�۾�����, 2:����(0�����߿���), 3:����(1�����߿���), 
				3:10���̻� �۾� ���� �ȵ�, 4: �Ϸ� 
			*/
	int		openerr;	/* ���� �����ϴµ� openerr �߻��� */
} *defJob;

struct def_log
{
	char	logName[128];
	char 	msgcode[8];
	char	ELevel[2];
	char 	logPath[256];
	char 	logPath_org[256];
	int		chgmode_new; /* <[yyyy]>,<[yy]>,<[mm]>,<[dd]>,<[dd-1]>,<[hh]>,<[h]> */
						 /* 0:��ȭ����,	1:<[yy]>/<[yyyy]>, 2:<[mm]>, 3:<[dd]>/<[dd-1]>, 4: <[hh]>/<[h]> */
	int		chgmode; 
			/* 		
				0: ��ȭ����, 	1:yyyymmdd, 	2:yyyymmdd-1, 	3:ddmmyyyy, 	4:ddmmyyyy-1,
				5: mmddyyyy, 	6:mmddyyyy-1, 	7:yymmdd, 		8:yymmdd-1,		9:mmdd,			10:mmdd-1
			*/
			/*
				�߰�
				11:yyyy.mm.dd, 12:yyyymmdd-hh, 13:yyyy-mm-dd, 14:mm-dd, 15:yyyymm, 16:yyyymmdd/yyyyymmdd
				17:<dd>, 	18:yyyymmdd_hh, 19:yyyymmdd_h
			*/
	int		chgmode_time; /* 0: ��ȭ ����,	1:hh.mi.ss,	2:hhmiss, 3: hhmi */
	long 	position;
	int 	nlogPath; /* yyyymmdd ������ġ */
	int 	nlogPath_time; /* hhmiss ������ġ */
	int		openerr;	/* ���� �����ϴµ� openerr �߻��� */
	char	monfrom[5], monto[5]; 
	char 	monweek[8];
	char	filecheck1[5], filecheck2[5];
	char	allevent_yn[5];		/* ��� ���� �̺�Ʈ �߻� */
	char	newlogcheck[5]; /* �ű� �α� ���� ���� üũ ���� */
	int		newlogdelaytime; /* �ű� �α� �̻������� ���ֵǴ� �ð� (�⺻ 30��) */
	char	newlogcheckaction[512]; 
	int 	isfileitv;	/* ���� ���翩�� interval */
	time_t	newloglasttime; /* ���������� ���� ���� �ð� */
	time_t	newlogchecktime; /* ������ üũ �ð� */
	char	newlogcheck_event[5];
	char	ispattern[5]; /* ���� ������ �����ϴ��� ���� */
	time_t	filelasttime; /* ������ ���� �ð�(hhmiss ������ ���� ����ð� üũ�� ����) */
	time_t  filechecktime; /*������ ���� ���� �̺�Ʈ �ð�(hhmiss ������ ���� ����ð� üũ�� ����)  */
	char	filecheck_event[5]; /* ���� ���� üũ�� �̺�Ʈ �߻� ����(hhmiss ������ ���� ����ð� üũ�� ����)*/
	char 	charset[10]; /* �Ѿ���Ƿ�� ������ �ӽ� �߰� ( 2022/10/05 ) */
	int		isfile; /* 2023/03/07 ���� ���翩�� ( -1: Ȯ�� ��, 0:������, 1: ���� ), ���� ������ ���ٰ� �߰��Ǵ� ��� ó������ ������ ���θ� Ȯ���� ���� �����  */
} *deflog;
 
struct def_jobpattern
{
	char	jobname[128];
	char 	msgcode[8];
	char	patterns[10][129];
	char	options[10][10]; /* and, or, except */
	char	svcname[128];
	int		mode;			/* 3:�̻� �߻��� �ѹ�, 2: �� x�� ���� �߻�, 1: max count �̻��, default  */
	int		duration;
	int		max_count;
	long	lastevttime;	/* ������ �߻��� �̺�Ʈ �ð� (�̻� �߻��� �ѹ� ó����) */
	long	lastactiontime; /* ������ action ������ �ð� */
	char	actioncmd[256];	/* action script */
	char	msgupper[5]; /* ��ҹ��� �������� üũ ���� */
} *defJobPattern;

struct def_protocol
{
    int     port;
    int     warning;
    int     critical;
    int     establish;
    int     wait;								/* Establish status ���� count */
    int     flag;								/* ���� ��� ���� */
} *defProtocol;

struct def_network
{
	char service[32];
    char port[16];
    int warning;
    int critical;
	int	fatal;
    int establish;
    int wait;								/* Establish status ���� count */
    int flag;								/* ���� ��� ���� */
} *defNetwork;

struct allow_hostname
{
	char    hostname[51];
	char    co_code[6];
	long 	lastTmPAVI[10]; 	/* 01: Agent, 02: Oracle, 03: mssql, 04: tibero, 05: db2, 06: mariadb */
	char 	lastMsgPAVI[10][128];
	long 	lastTmPOSI[5]; 	/* 01 : os ���� , 02 : h/w ���� ( cpu/mem ) */
	char 	lastMsgPOSI[5][128];
} *allowHostname;

struct def_stddev
{
	char    item[8];
	float   avg;
	float   stddev;
} *defStddev;

struct def_sysmods
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

struct def_securefile
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

struct def_securefile_cmd
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

struct run_mounted
{
    char    filesystem[128];
    char    mounted[128];
} *rMounted;

/* IT.wrtd���� ������ ����� ���ǽ� ��� */
struct def_except_host
{
    char name[64];
    char cocode[10];
    char perf_yn[10];
    char svr_dn_msg_yn[10];
    char svr_msg_yn[10];
	char tm_from[20];
	char tm_to[20];
}*defexcept_host;

/* IT.wrtd���� ����� ����� ���ǽ� ��� */
struct def_allow_host
{
    char name[64];
    char cocode[10];
	char is_reg[5];
	int  inew;	/* ������ ��ġ ( 0: ����(���� read�� ���), 1: �ű� ) */
}*defallow_host;

struct def_sysmods_lst
{
	char hostname[64];
	char cocode[10];
	char from[32];
	char to[32];
}*defsysmods_lst;

struct def_ha
{
	char ha_type[32];
	char ha_server_ip[32];
	char ha_server_host[64];
	char ha_filesystem[256];
	char ha_ipaddress[32];
	char ha_role[10];
	char status_set[32];  /* �������� : ACTIVE/STANDBY/NODE */
	char status_cur[32];  /* ���� ���� ���� : ACTIVE/STANDBY/NODE */
	char status_last[32]; /* ���� ���� ���� : ACTIVE/STANDBY/NODE */
}*defha;

struct ha_list
{
	char    status[32];  /* ACTIVE/STANDBY/NODE */
} *halist;

struct def_s2oenv
{
    char env_home[256]; /* IT.cfg ������ ��ġ */
    char env_file[512]; /* IT.cfg path */
    char bin_home[256];
    char cfg_home[270];
    char log_home[270];
    char dat_home[270];
    char mode[5];
    char mainhost[50];
	char mainmaster_ip[32]; /*  sub master���� main master�� ������ �� ���*/
    char mainhost_nosend[10]; /* �� ��� mainhost_ip �θ� ���� */
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
	char upt_cu_system[2]; /* cu_system table update ���� */
	int chkonly; /* �ڻ� ��ĵ ���˸� */
} s2oenv;

char S2O_DAEMON[64];
char S2O_PIDFILE[256];
int IS_NOS2O_AGENT;
int IS_WLOG_LOGING; /* 1: wlog �߻��� loging���� ������ (DEBUG ��) */


/***********************************************************************/
/* exception check time ���� */
/***********************************************************************/
struct except_check_time {
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
char    except_chktimecfg[256];
time_t  except_chktime_mtime;
int     cnt_except_chktime;
/***********************************************************************/


/***********************************************************************/
/* account ���� */
/***********************************************************************/
struct account_struct {
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
int account_num;

struct acc_expire_check {
    char apply[5];
    int  hour;
    int  min;
    int warn;
    int crit;
    char lastchktime[20];
    char exclude_expired[5];
    char exclude_lock[5];
}acc_expire_chk;

struct acc_expire_except {
    char name[101];
}*acc_expire_exp;
int acc_expire_exp_cnt;
/***********************************************************************/

#endif

