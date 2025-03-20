#ifndef LIBIT_H
#define LIBIT_H

/*#include "IT.h"*/

#include "IT.define.h"

#include <sys/types.h>

extern int configSyslogSet(char *homedir, int *_iskip_info);
extern void daemonize(char *fname, int count, char* _DAEMON_VER);
extern int fcopy(char *src, char *dest, mode_t pmode);
extern int get_cfg(char* ENV, char* value);
extern int get_cfg2(char* config, char* ENV, char* value);
extern int getitem(int ch, char *src, char *dest, int seqitem);
extern int is_valid_msg(char *v_msg);
extern int it_loging(char *format,...);
extern int it_loging_f(char *_sub, char *format,...);
extern int readLinen(int fd, char* str, int length);
extern int rtrim(char* sbuf);
extern int size_check(char *file, int size);
extern void timestr(char *tim);
extern int wlog(char *mid, char *msg,...);
extern int wlog2(char *mid, char *company, char *host, char *msg,...);
extern int rcvd_local_write(char* ithome, int sockno, char *str);
extern int ping(char *host, int packetsize, int count, int *min, int *avg, int *max);
extern int connect_timeo(char *hostname, char *service, int nsec);
extern int connect_timeo3(char* checkhost, char *hostname, char *service, int nsec);
extern void Writen(int fd, void *ptr, size_t nbytes);
extern int Readable_timeo(int fd, int sec);
extern int connect_timeo(char *hostname, char *service, int nsec);
extern int configPcuSet(char *homedir);
extern int get_process();
extern int set_process(char *cfgname);
extern int is_valid_ip(char *str);
extern int runPcuGet(char* arg);
extern int dump_tempfile(char *dirpath);
extern int get_filesystem(char *cfgname);
extern int configNetwork(char *homedir);
extern int set_secure_file(char *cfgname);
extern int set_cfg(int ns, char *ENV1, char *value1, char *ENV2, char *value2); 
extern int is_valid_format(char *v_msg);
extern int get_chkpt(char *f_name);
extern int update_chkpt(char *f_name, int count);
extern int update_chkpt2(char *f_name, int count);
extern int search_point2(int ch, char *s, int post);
extern int getitemc(int ch, char *src);
extern int client3(char* hostname, char *service);
extern int local_write(char *file, char *str);
extern int readLine(int fd, char* str);
extern void agentver();
extern int get_chkrouter(char *config_fname);
extern int wlog_no_vsprintf(char *mid, char *msg);
extern int wlog2_no_vsprintf(char *mid, char *company, char *host, char *msg);
extern int wlog_direct(char *mid, char *tmsg);
extern int file_read(char *file, char *value);
extern int expand_env(char *src, char *dest);
extern int loging_f(char *fname, char *format,...);
extern int chkip(char *arg);
extern int change_token(char *src, char token, char dtoken);
extern int s2o_encrypt(char *type, char *src, char *dest);
extern int s2o_decrypt(char *type, char *src, char *dest);
extern int getitem_end(int ch, char *src, char *dest, int seqitem);
extern int set_cfgs(int ns, char ENV[10][256], char value[10][256], int itemnum);
extern int it_dmsloging(char *format,...);
extern int set_jobpattern(char *cfgname);
extern int set_job(char *cfgname);
extern int set_log(char *cfgname);
extern int datechg(char *_fname, char *_fname_org, int position, int _type, int _back, int _yesterday);
extern int changedate(char *fname, char* fname_org, int *position);
extern int ltrim(char *sbuf);
extern int loging(char *msg,...);
extern int lltrim(char* sbuf);
extern int ___it_debugloging(char* _daemon, int _debugtype, char *format,...);
extern int write_ver(char* _homedir, char* _version, char* _pgmname);
extern int get_s2opid(char* homedir, char *daemon, int seq_num);
extern int set_cfg3(char* program, char *config, char *ENV1, char *value1, char *ENV2, char *value2);
extern void date1(char* tim);
extern int get_s2o_hostname(char* _SERVER, char *_s2ohost, int _msg_force);
extern int connect_timeon(char *hostname, int port, int nsec);
extern char *strupr(char *string);
extern int wlog_fail(char *msg);
extern char* get_sock_errno(int err_no);
extern int get_linuxtype(char* _linuxtype, char* _detail);
extern int get_osrelease(char* _release);
extern int is_exclude_mounted(char* _mounted, char* _filesystem);
extern int get_config2(char *config, char *env, char *value);
extern int file_write(char *file, char *str, int mode);
extern int get_masterenv(char* _username, char* _passwd, char* _tnsname);
extern int get_masterenv2(char* _orahome, char* _oratnsadmin, char* _username, char* _passwd, char* _tnsname);
extern int check_lic2(char* _itcompany, int *_maxcnt);
extern int s2o_sha256_encrypt2(char* src, char* dest);
extern char *search_point(int ch, char *s, int post);
extern int it_call_loging(int _idebug_type, char *format,...);
extern int smconnect(char *host, int port);
extern int smsend(int s, char *sndbuf, char *code);
extern void mtrim(char *src);
extern int get_process_cnt(char* _prsname);
extern int get_process_cnt2(char* _prsname);
extern int get_process_cnt3(char* _prsname, char* _prsname2);
extern int get_process_cnt4(char* _prsname, char* _prsname2, char* _prsname3);
extern int get_bootmin(char *_uptime);
extern void sig_chld(int signo);
extern int s2oSeedDecrypt(char *pFileNm /*BYTE *pbData*/, char* _pdestFile );
extern void update_timezone(char *_timezone);
extern int datechg_onemin_ago(char* _daytime_aix);
extern int change_orac_auth(char* homedir, char* user);
extern int change_user_auth(char* homedir, char* user, char* daemon);
extern int save_rawdata(char* ithome, char *filename, char *format,...);
extern int get_masterenv_mariadb(char* _username, char* _passwd, char* _instance, char* _ip, char* _port, char* _database1, char* _database2);
extern long difftime_msg(char *msg_month, char* msg_day, char *msg_time);
extern int compare_s2opid();
extern int get_osuserinfo();
extern int set_account_expire(char* _SERVER, char* cfgname);
extern int compare_time(int type, char* time_from, char* time_to);
extern const char *llInt2comma(_llInt_ _num);
extern const char *int2comma(int _num);
extern int getDayIndexOfWeek( int _year, int _month, int _day);
extern int getDayIndexOfWeekString( int _year, int _month, int _week, int _dayth, char* _timestr);
extern int working_write(char* _file, char* _item, char* _msg);
extern void dump_user_wlog(int _argc,  char *_argv[]);
extern int set_except_chktime(char* _SERVER, char* cfgname, int _cnt_except_chktime);
extern int is_except_chktime(char* _SERVER, int _except_chktime_cnt, char* _item, char* _subitem, char* _subitemplus);
extern int get_itdev(char* _itdev, char* owner);
#endif
