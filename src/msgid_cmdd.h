/*
   $Id: msgid.h,v 1.7 2002/09/30 srp Exp $

   Copyright (c) 2000, 2001, 2002 i-TOP System Inc.  All rights reserved.

   2002-09-30
     * Msgid ID Define include file.
	 * R : Real Time Performance data.
	   P : Performance data.(DB gathering data)
*/

/*
**	IT.cmdd Message ID 			Last Modfied : 2002-09-30 -------------------
*/
#if defined(LINUX)
#define MSGID_R_CPU 	"RCPU100"
#define MSGID_R_PCU 	"RPCU100"		/* Current process cpu usage 전송 */
#define MSGID_T_PCU 	"TPCU100"		/* Current process cpu usage 전송 */
#define MSGID_R_PEF		"RPEF100"		/* cpu, mem 전송*/
#define MSGID_D_PCU 	"DPCU100"		/* 서버에 저장된 proc_cpu.cfg 전송 */
#define MSGID_R_USR 	"RUSR100"		/* Current process cpu usage 전송 */
#define MSGID_R_MEM 	"RMEM100"
#define MSGID_R_LAD 	"RLAD100"
#define MSGID_R_PSA 	"RPSA100"		/* Active Server Process 정보 */
#define MSGID_R_PRS 	"RPRS100"
#define MSGID_R_PRS1 	"RPRS101"
#define MSGID_T_PRS1 	"TPRS101"
#define MSGID_D_PRS 	"DPRS100"		/* 서버에 저장된 process.cfg 내용전송 */
#define MSGID_R_DSK 	"RDSK100"		/* Current Disk space */
#define MSGID_D_DSK 	"DDSK100"		/* 서버에 저장된 disk.cfg 내용전송 */
#define MSGID_R_DSI 	"RDSI100"		/* Current Disk inode space */
#define MSGID_D_DSI 	"DDSI100"		/* 서버에 저장된 inodes.cfg 내용전송 */
#define MSG_W_CMD00 	"WCMD100"		/* Master Console Command */
#define MSG_W_CMD01 	"WCMD101"		/* pthread upload fail messages */
#define MSGID_R_SYS 	"RSYS100"		/* System Check Configuration */
#define MSGID_D_SYS 	"DSYS100"		
#define MSGID_D_SYS1 	"DSYS101"		
#define MSGID_D_SYS2 	"DSYS102"		
#define MSG_W_UPT32 	"WUPT132"		/* daemon sighup 관련 messages */
#define MSG_D_INF00 	"DINF100"		/* Agent hostname, company code 전송 */
#define MSG_D_S2O00		"DS2O100"		/* s2o montoring 설정파일 read. (master) */
#elif defined(AIX)
#define MSGID_R_CPU 	"RCPU300"
#define MSGID_R_PCU 	"RPCU300"		/* Current process cpu usage 전송 */
#define MSGID_T_PCU 	"TPCU300"		/* Current process cpu usage 전송 */
#define MSGID_R_PEF		"RPEF300"		/* cpu, mem 전송*/
#define MSGID_D_PCU 	"DPCU300"		/* 서버에 저장된 proc_cpu.cfg 전송 */
#define MSGID_R_USR 	"RUSR300"		/* Current process cpu usage 전송 */
#define MSGID_R_MEM 	"RMEM300"
#define MSGID_R_LAD 	"RLAD300"
#define MSGID_R_PSA 	"RPSA300"		/* Active Server Process 정보 */
#define MSGID_R_PRS 	"RPRS300"
#define MSGID_R_PRS1 	"RPRS301"
#define MSGID_T_PRS1 	"TPRS301"
#define MSGID_D_PRS 	"DPRS300"		/* 서버에 저장된 process */
#define MSGID_R_DSK 	"RDSK300"
#define MSGID_D_DSK 	"DDSK300"		/* 서버에 저장된 disk.cfg 내용전송 */
#define MSGID_R_DSI 	"RDSI300"		/* Current Disk inode space */
#define MSGID_D_DSI 	"DDSI300"		/* 서버에 저장된 inodes.cfg 내용전송 */
#define MSG_W_CMD00 	"WCMD300"
#define MSG_W_CMD01 	"WCMD301"
#define MSGID_R_SYS 	"RSYS300"		/* System Check Configuration */
#define MSGID_D_SYS 	"DSYS300"		
#define MSGID_D_SYS1 	"DSYS301"		
#define MSGID_D_SYS2 	"DSYS302"		
#define MSG_W_UPT32 	"WUPT332"		/* daemon sighup 관련 messages */
#define MSG_D_INF00 	"DINF300"		/* Agent hostname, company code 전송 */
#define MSG_D_S2O00		"DS2O300"		/* s2o montoring 설정파일 read. (master) */
#elif defined(HPUX)
#define MSGID_R_CPU 	"RCPU400"
#define MSGID_R_PCU 	"RPCU400"		/* Current process cpu usage 전송 */
#define MSGID_T_PCU 	"TPCU400"		/* Current process cpu usage 전송 */
#define MSGID_R_PEF		"RPEF400"		/* cpu, mem 전송*/
#define MSGID_D_PCU 	"DPCU400"		/* 서버에 저장된 proc_cpu.cfg 전송 */
#define MSGID_R_USR 	"RUSR400"		/* Current process cpu usage 전송 */
#define MSGID_R_MEM 	"RMEM400"
#define MSGID_R_LAD 	"RLAD400"
#define MSGID_R_PSA 	"RPSA400"		/* Active Server Process 정보 */
#define MSGID_R_PRS 	"RPRS400"
#define MSGID_R_PRS1 	"RPRS401"
#define MSGID_T_PRS1 	"TPRS401"
#define MSGID_D_PRS 	"DPRS400"		/* 서버에 저장된 process */
#define MSGID_R_DSK 	"RDSK400"
#define MSGID_D_DSK 	"DDSK400"		/* 서버에 저장된 disk.cfg 내용전송 */
#define MSGID_R_DSI 	"RDSI400"		/* Current Disk inode space */
#define MSGID_D_DSI 	"DDSI400"		/* 서버에 저장된 inodes.cfg 내용전송 */
#define MSG_W_CMD00 	"WCMD400"
#define MSG_W_CMD01 	"WCMD401"
#define MSGID_R_SYS 	"RSYS400"		/* System Check Configuration */
#define MSGID_D_SYS 	"DSYS400"		
#define MSGID_D_SYS1 	"DSYS401"		
#define MSGID_D_SYS2 	"DSYS402"		
#define MSG_W_UPT32 	"WUPT432"		/* daemon sighup 관련 messages */
#define MSG_D_INF00 	"DINF400"		/* Agent hostname, company code 전송 */
#define MSG_D_S2O00		"DS2O400"		/* s2o montoring 설정파일 read. (master) */
#elif defined(NCRUX)
#define MSGID_R_CPU 	"RCPU500"
#define MSGID_R_PCU 	"RPCU500"		/* Current process cpu usage 전송 */
#define MSGID_T_PCU 	"TPCU500"		/* Current process cpu usage 전송 */
#define MSGID_R_PEF		"RPEF500"		/* cpu, mem 전송*/
#define MSGID_D_PCU 	"DPCU500"		/* 서버에 저장된 proc_cpu.cfg 전송 */
#define MSGID_R_USR 	"RUSR500"		/* Current process cpu usage 전송 */
#define MSGID_R_MEM 	"RMEM500"
#define MSGID_R_LAD 	"RLAD500"
#define MSGID_R_PSA 	"RPSA500"		/* Active Server Process 정보 */
#define MSGID_R_PRS 	"RPRS500"
#define MSGID_R_PRS1 	"RPRS501"
#define MSGID_T_PRS1 	"TPRS501"
#define MSGID_D_PRS 	"DPRS500"		/* 서버에 저장된 process */
#define MSGID_R_DSK 	"RDSK500"
#define MSGID_D_DSK 	"DDSK500"		/* 서버에 저장된 disk.cfg 내용전송 */
#define MSGID_R_DSI 	"RDSI500"		/* Current Disk inode space */
#define MSGID_D_DSI 	"DDSI500"		/* 서버에 저장된 inodes.cfg 내용전송 */
#define MSG_W_CMD00 	"WCMD500"
#define MSG_W_CMD01 	"WCMD501"
#define MSGID_R_SYS 	"RSYS500"		/* System Check Configuration */
#define MSGID_D_SYS 	"DSYS500"		
#define MSGID_D_SYS1 	"DSYS501"		
#define MSGID_D_SYS2 	"DSYS502"		
#define MSG_W_UPT32 	"WUPT532"		/* daemon sighup 관련 messages */
#define MSG_D_INF00 	"DINF500"		/* Agent hostname, company code 전송 */
#define MSG_D_S2O00		"DS2O500"		/* s2o montoring 설정파일 read. (master) */
#elif defined(DGUX)
#define MSGID_R_CPU 	"RCPU700"
#define MSGID_R_PCU 	"RPCU700"		/* Current process cpu usage 전송 */
#define MSGID_T_PCU 	"TPCU700"		/* Current process cpu usage 전송 */
#define MSGID_R_PEF		"RPEF700"		/* cpu, mem 전송*/
#define MSGID_D_PCU 	"DPCU700"		/* 서버에 저장된 proc_cpu.cfg 전송 */
#define MSGID_R_USR 	"RUSR700"		/* Current process cpu usage 전송 */
#define MSGID_R_MEM 	"RMEM700"
#define MSGID_R_LAD 	"RLAD700"
#define MSGID_R_PSA 	"RPSA700"		/* Active Server Process 정보 */
#define MSGID_R_PRS 	"RPRS700"
#define MSGID_R_PRS1 	"RPRS701"
#define MSGID_T_PRS1 	"TPRS701"
#define MSGID_D_PRS 	"DPRS700"		/* 서버에 저장된 process */
#define MSGID_R_DSK 	"RDSK700"
#define MSGID_D_DSK 	"DDSK700"		/* 서버에 저장된 disk.cfg 내용전송 */
#define MSGID_R_DSI 	"RDSI700"		/* Current Disk inode space */
#define MSGID_D_DSI 	"DDSI700"		/* 서버에 저장된 inodes.cfg 내용전송 */
#define MSG_W_CMD00 	"WCMD700"
#define MSG_W_CMD01 	"WCMD701"
#define MSGID_R_SYS 	"RSYS700"		/* System Check Configuration */
#define MSGID_D_SYS 	"DSYS700"		
#define MSGID_D_SYS1 	"DSYS701"		
#define MSGID_D_SYS2 	"DSYS702"		
#define MSG_W_UPT32 	"WUPT732"		/* daemon sighup 관련 messages */
#define MSG_D_INF00 	"DINF700"		/* Agent hostname, company code 전송 */
#define MSG_D_S2O00		"DS2O700"		/* s2o montoring 설정파일 read. (master) */
#else		/* SUN2 */	
#define MSGID_R_CPU 	"RCPU200"
#define MSGID_R_PCU 	"RPCU200"		/* Current process cpu usage 전송 */
#define MSGID_T_PCU 	"TPCU200"		/* Current process cpu usage 전송 */
#define MSGID_R_PEF		"RPEF200"		/* cpu, mem 전송*/
#define MSGID_D_PCU 	"DPCU200"		/* 서버에 저장된 proc_cpu.cfg 전송 */
#define MSGID_R_USR 	"RUSR200"		/* Current process cpu usage 전송 */
#define MSGID_R_MEM 	"RMEM200"
#define MSGID_R_LAD 	"RLAD200"
#define MSGID_R_PSA 	"RPSA200"		/* Active Server Process 정보 */
#define MSGID_R_PRS1 	"RPRS201"
#define MSGID_T_PRS1 	"TPRS201"
#define MSGID_D_PRS 	"DPRS200"		/* 서버에 저장된 process */
#define MSGID_R_DSK 	"RDSK200"
#define MSGID_D_DSK 	"DDSK200"		/* 서버에 저장된 disk.cfg 내용전송 */
#define MSGID_R_DSI 	"RDSI200"		/* Current Disk inode space */
#define MSGID_D_DSI 	"DDSI200"		/* 서버에 저장된 inodes.cfg 내용전송 */
#define MSG_W_CMD00 	"WCMD200"
#define MSG_W_CMD01 	"WCMD201"
#define MSGID_R_SYS 	"RSYS200"		/* System Check Configuration */
#define MSGID_D_SYS 	"DSYS200"		
#define MSGID_D_SYS1 	"DSYS201"		
#define MSGID_D_SYS2 	"DSYS202"		
#define MSG_W_UPT32 	"WUPT232"		/* daemon sighup 관련 messages */
#define MSG_D_INF00 	"DINF200"		/* Agent hostname, company code 전송 */
#define MSG_D_S2O00		"DS2O200"		/* s2o montoring 설정파일 read. (master) */
#endif

#if defined(ENGLISH)
#define STR_W_CMD00	"Client(%s) issued command not authorized."
#define STR_W_CMD01	"upload pthread create fail."
#define STR_W_UPT32	"S2O Agent(%s) initial failed because agent is not executed."
#else
#define STR_W_CMD00	"Client(%s)로부터 발행된 command를 권한이 없어 거부하였습니다."
#define STR_W_CMD01	"실시간 성능 Upload 쓰레드 생성을 실패하였습니다"
#define STR_W_UPT32	"S2O Agent(%s)가 실행되고 있지 않아 초기화에 실패하였습니다."
#endif
