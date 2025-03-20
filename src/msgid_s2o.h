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
#define MSG_C_S2O01		"CS2O101"		/* S2O DAEMON Resource 사용량이 높은 경우 */
#define MSG_W_S2O11 	"WCFG101"		/* Config 파일 저장 관련 */
#define MSG_I_S2O02 	"IS2O102"		/* 제외된 syslog 메세지 알림 ( 10분이상시 마다 초당 1건이상시에만 발생) */
#define MSG_W_S2O03     "WS2O103"		/* Agent 동작 여부 점검 */
#define MSG_W_S2O05		"WS2O105"		/* 체크 서버 설정 */
#define MSG_W_S2O06		"WS2O106"		/* SYSLOG 체크 데이터 확인 */
#define MSG_I_S2O06		"IS2O106"		/* SYSLOG 체크 데이터 확인 */
#define MSG_W_S2O07     "WS2O107"		/* S2O 재기동 */
#define MSG_W_S2O08		"WS2O108"		/* 성능 체크 데이터 확인 */
#define MSG_I_S2O08		"IS2O108"		/* 성능 체크 데이터 확인 */
#define MSG_W_S2O09		"WS2O109"		/* 시스템 체크 데이터 확인 */
#define MSG_I_S2O09		"IS2O109"		/* 시스템 체크 데이터 확인 */
#define MSG_W_HAC01 	"WHAC101"		/* HA 모니터링이 시작 또는 HA 모니터링이 시작중인 경우(Agent 기동시) */
#define MSG_W_HAC02 	"WHAC102"		/* HA 모니터링이 종료 또는 HA 모니터링이 종료중인 경우(Agent 기동시) */
#define MSG_C_HAC03 	"CHAC103"		/* HA 모니터링이 제거 */
#define MSG_C_HAC04 	"CHAC104"		/* HA 모니터링 설정 오류 */
#define MSG_W_HAC04 	"WHAC104"		/* HA 모니터링 설정에 오류가 있는 경우 (Agent 기동시) */
#define MSG_C_HAC05 	"CHAC105"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC105"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC106"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC106"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC107"		/* HA 단위 모니터링이 시작 */
#define MSG_W_HAC08 	"WHAC108"		/* HA 단위 모니터링이 종료 */
#elif defined(AIX)
#define MSG_C_S2O01		"CS2O301"		/* S2O DAEMON Resource 사용량이 높은 경우 */
#define MSG_W_S2O11 	"WCFG301"		/* Config 파일 저장 관련 */
#define MSG_I_S2O02 	"IS2O302"		/* 제외된 syslog 메세지 알림 ( 10분이상시 마다 초당 1건이상시에만 발생) */
#define MSG_W_S2O03     "WS2O303"		/* Agent 동작 여부 점검 */
#define MSG_W_S2O05		"WS2O305"		/* 체크 서버 설정 */
#define MSG_W_S2O06		"WS2O306"		/* SYSLOG 체크 데이터 확인 */
#define MSG_I_S2O06		"IS2O306"		/* SYSLOG 체크 데이터 확인 */
#define MSG_W_S2O07     "WS2O307"		/* S2O 재기동 */
#define MSG_W_S2O08		"WS2O308"		/* 성능 체크 데이터 확인 */
#define MSG_I_S2O08		"IS2O308"		/* 성능 체크 데이터 확인 */
#define MSG_W_S2O09		"WS2O309"		/* 시스템 체크 데이터 확인 */
#define MSG_I_S2O09		"IS2O309"		/* 시스템 체크 데이터 확인 */
#define MSG_W_HAC01 	"WHAC301"		/* HA 모니터링이 시작 또는 HA 모니터링이 시작중인 경우(Agent 기동시) */
#define MSG_W_HAC02 	"WHAC302"		/* HA 모니터링이 종료 또는 HA 모니터링이 종료중인 경우((Agent 기동시) */
#define MSG_C_HAC03 	"CHAC303"		/* HA 모니터링이 제거 */
#define MSG_C_HAC04 	"CHAC304"		/* HA 모니터링 설정 오류 */
#define MSG_W_HAC04 	"WHAC304"		/* HA 모니터링 설정에 오류가 있는 경우 (Agent 기동시) */
#define MSG_C_HAC05 	"CHAC305"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC305"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC306"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC306"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC307"		/* HA 단위 모니터링이 시작 */
#define MSG_W_HAC08 	"WHAC308"		/* HA 단위 모니터링이 종료 */
#elif defined(HPUX)
#define MSG_C_S2O01		"CS2O401"		/* S2O DAEMON Resource 사용량이 높은 경우 */
#define MSG_W_S2O11 	"WCFG401"		/* Config 파일 저장 관련 */
#define MSG_I_S2O02 	"IS2O402"		/* 제외된 syslog 메세지 알림 ( 10분이상시 마다 초당 1건이상시에만 발생) */
#define MSG_W_S2O03     "WS2O403"		/* Agent 동작 여부 점검 */
#define MSG_W_S2O05		"WS2O405"		/* 체크 서버 설정 */
#define MSG_W_S2O06		"WS2O406"		/* SYSLOG 체크 데이터 확인 */
#define MSG_I_S2O06		"IS2O406"		/* SYSLOG 체크 데이터 확인 */
#define MSG_W_S2O07     "WS2O407"		/* S2O 재기동 */
#define MSG_W_S2O08		"WS2O408"		/* 성능 체크 데이터 확인 */
#define MSG_I_S2O08		"IS2O408"		/* 성능 체크 데이터 확인 */
#define MSG_W_S2O09		"WS2O409"		/* 시스템 체크 데이터 확인 */
#define MSG_I_S2O09		"IS2O409"		/* 시스템 체크 데이터 확인 */
#define MSG_W_HAC01 	"WHAC401"		/* HA 모니터링이 시작 또는 HA 모니터링이 시작중인 경우(Agent 기동시) */
#define MSG_W_HAC02 	"WHAC402"		/* HA 모니터링이 종료 또는 HA 모니터링이 종료중인 경우((Agent 기동시) */
#define MSG_C_HAC03 	"CHAC403"		/* HA 모니터링이 제거 */
#define MSG_C_HAC04 	"CHAC404"		/* HA 모니터링 설정 오류 */
#define MSG_W_HAC04 	"WHAC404"		/* HA 모니터링 설정에 오류가 있는 경우 (Agent 기동시) */
#define MSG_C_HAC05 	"CHAC405"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC405"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC406"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC406"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC407"		/* HA 단위 모니터링이 시작 */
#define MSG_W_HAC08 	"WHAC408"		/* HA 단위 모니터링이 종료 */
#elif defined(NCRUX)
#define MSG_C_S2O01		"CS2O501"		/* S2O DAEMON Resource 사용량이 높은 경우 */
#define MSG_W_S2O11 	"WCFG501"		/* Config 파일 저장 관련 */
#define MSG_I_S2O02 	"IS2O502"		/* 제외된 syslog 메세지 알림 ( 10분이상시 마다 초당 1건이상시에만 발생) */
#define MSG_W_S2O03     "WS2O503"		/* Agent 동작 여부 점검 */
#define MSG_W_S2O05		"WS2O505"		/* 체크 서버 설정 */
#define MSG_W_S2O06		"WS2O506"		/* SYSLOG 체크 데이터 확인 */
#define MSG_I_S2O06		"IS2O506"		/* SYSLOG 체크 데이터 확인 */
#define MSG_W_S2O07     "WS2O507"		/* S2O 재기동 */
#define MSG_W_S2O08		"WS2O508"		/* 성능 체크 데이터 확인 */
#define MSG_I_S2O08		"IS2O508"		/* 성능 체크 데이터 확인 */
#define MSG_W_S2O09		"WS2O509"		/* 시스템 체크 데이터 확인 */
#define MSG_I_S2O09		"IS2O509"		/* 시스템 체크 데이터 확인 */
#define MSG_W_HAC01 	"WHAC501"		/* HA 모니터링이 시작 또는 HA 모니터링이 시작중인 경우(Agent 기동시) */
#define MSG_W_HAC02 	"WHAC502"		/* HA 모니터링이 종료 또는 HA 모니터링이 종료중인 경우((Agent 기동시) */
#define MSG_C_HAC03 	"CHAC503"		/* HA 모니터링이 제거 */
#define MSG_C_HAC04 	"CHAC504"		/* HA 모니터링 설정 오류 */
#define MSG_W_HAC04 	"WHAC504"		/* HA 모니터링 설정에 오류가 있는 경우 (Agent 기동시) */
#define MSG_C_HAC05 	"CHAC505"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC505"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC506"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC506"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC507"		/* HA 단위 모니터링이 시작 */
#define MSG_W_HAC08 	"WHAC508"		/* HA 단위 모니터링이 종료 */
#elif defined(DGUX)
#define MSG_C_S2O01		"CS2O701"		/* S2O DAEMON Resource 사용량이 높은 경우 */
#define MSG_W_S2O11 	"WCFG701"		/* Config 파일 저장 관련 */
#define MSG_I_S2O02 	"IS2O702"		/* 제외된 syslog 메세지 알림 ( 10분이상시 마다 초당 1건이상시에만 발생) */
#define MSG_W_S2O03     "WS2O703"		/* Agent 동작 여부 점검 */
#define MSG_W_S2O05		"WS2O705"		/* 체크 서버 설정 */
#define MSG_W_S2O06		"WS2O706"		/* SYSLOG 체크 데이터 확인 */
#define MSG_I_S2O06		"IS2O706"		/* SYSLOG 체크 데이터 확인 */
#define MSG_W_S2O07     "WS2O707"		/* S2O 재기동 */
#define MSG_W_S2O08		"WS2O708"		/* 성능 체크 데이터 확인 */
#define MSG_I_S2O08		"IS2O708"		/* 성능 체크 데이터 확인 */
#define MSG_W_S2O09		"WS2O709"		/* 시스템 체크 데이터 확인 */
#define MSG_I_S2O09		"IS2O709"		/* 시스템 체크 데이터 확인 */
#define MSG_W_HAC01 	"WHAC701"		/* HA 모니터링이 시작 또는 HA 모니터링이 시작중인 경우(Agent 기동시) */
#define MSG_W_HAC02 	"WHAC702"		/* HA 모니터링이 종료 또는 HA 모니터링이 종료중인 경우((Agent 기동시) */
#define MSG_C_HAC03 	"CHAC703"		/* HA 모니터링이 제거 */
#define MSG_C_HAC04 	"CHAC704"		/* HA 모니터링 설정 오류 */
#define MSG_W_HAC04 	"WHAC704"		/* HA 모니터링 설정에 오류가 있는 경우 (Agent 기동시) */
#define MSG_C_HAC05 	"CHAC705"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC705"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC706"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC706"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC707"		/* HA 단위 모니터링이 시작 */
#define MSG_W_HAC08 	"WHAC708"		/* HA 단위 모니터링이 종료 */
#else		/* SUN2 */	
#define MSG_C_S2O01		"CS2O201"		/* S2O DAEMON Resource 사용량이 높은 경우 */
#define MSG_W_S2O11 	"WCFG201"		/* Config 파일 저장 관련 */
#define MSG_W_S2O11 	"WCFG201"		/* Config 파일 저장 관련 */
#define MSG_I_S2O02 	"IS2O202"		/* 제외된 syslog 메세지 알림 ( 10분이상시 마다 초당 1건이상시에만 발생) */
#define MSG_W_S2O03     "WS2O203"		/* Agent 동작 여부 점검 */
#define MSG_W_S2O05		"WS2O205"		/* 체크 서버 설정 */
#define MSG_W_S2O06		"WS2O206"		/* SYSLOG 체크 데이터 확인 */
#define MSG_I_S2O06		"IS2O206"		/* SYSLOG 체크 데이터 확인 */
#define MSG_W_S2O07     "WS2O207"		/* S2O 재기동 */
#define MSG_W_S2O08		"WS2O208"		/* 성능 체크 데이터 확인 */
#define MSG_I_S2O08		"IS2O208"		/* 성능 체크 데이터 확인 */
#define MSG_W_S2O09		"WS2O209"		/* 시스템 체크 데이터 확인 */
#define MSG_I_S2O09		"IS2O209"		/* 시스템 체크 데이터 확인 */
#define MSG_W_HAC01 	"WHAC201"		/* HA 모니터링이 시작 또는 HA 모니터링이 시작중인 경우(Agent 기동시) */
#define MSG_W_HAC02 	"WHAC202"		/* HA 모니터링이 종료 또는 HA 모니터링이 종료중인 경우((Agent 기동시) */
#define MSG_C_HAC03 	"CHAC203"		/* HA 모니터링이 제거 */
#define MSG_C_HAC04 	"CHAC204"		/* HA 모니터링 설정 오류 */
#define MSG_W_HAC04 	"WHAC204"		/* HA 모니터링 설정에 오류가 있는 경우 (Agent 기동시) */
#define MSG_C_HAC05 	"CHAC205"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC205"		/* HA 모니터링 전환 필요 (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC206"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC206"		/* HA 모니터링 전환 필요 (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC207"		/* HA 단위 모니터링이 시작 */
#define MSG_W_HAC08 	"WHAC208"		/* HA 단위 모니터링이 종료 */
#endif

#define MSG_W_S2O04     "WS2O004" 		/* IT.dat(숫자) 파일 감시 */
#define MSG_I_S2O04     "IS2O004" 		/* IT.dat(숫자) 파일 감시 */
#define MSG_W_S2O10		"WS2O010"		/* IT.숫자 DB 저장 skip 된 경우 알림 */

#if defined(ENGLISH)
#define STR_W_S2O11_1 	"Agent configuration file do not saved. because of unstable master console connection. Please retry."
#define STR_I_S2O02_1 	"S2O: during the last %d seconds, %ld cases of undefined syslog messages was excluded from the monitoring."
#define STR_W_S2O03 	"Agent(%s) do not performed %d minutes over. Agent(%s) restart"
#define STR_W_S2O03_2   "Since Accept Error occurred %d times in a row, Agent(%s) will be restarted."
#define STR_W_S2O03_3   "Since Accept Error occurred %d times in a row, Agent(%s) is terminated."
/*#define STR_I_S2O02_1 	"S2O: during the last %d seconds, %ld cases of undefined info level syslog messages was excluded from the monitoring."*/
#define STR_W_S2O04_1 	"A lot of '%s' equipment messages have occurred. File(%s), Cur(%d%%:%dcnt), Set(%d%%:%dcnt))"
#define STR_W_S2O04_2 	"Message analysis of '%s' file failed."
#define STR_I_S2O04_1	"The message overload analysis of the file(%s) is completed normally."
#define STR_W_S2O05_1	"Added '%s' to server status check settings. (%s/%s/%s)"
#define STR_W_S2O05_2	"Failed to add '%s' to server status check settings. (%s/%s/%s)"
#define STR_W_S2O05_3	"Changed '%s' in server status check settings. (%s/%s/%s)"
#define STR_W_S2O05_4	"Failed to change '%s' in server status check setting. (%s/%s/%s)"
#define STR_W_S2O05_5	"Removed '%s' from server status check settings. (%s/%s/%s)"
#define STR_W_S2O05_6	"Failed to remove '%s' from server status check settings. (%s/%s/%s)"
#define STR_W_S2O05_7	"There is no target for '%s' removal in the server status check settings. (%s/%s/%s)"
#define STR_W_S2O05_8	"There is no target for '%s' change in server status check setting. (%s/%s/%s)"
#define STR_W_S2O05_9	"The '%s' has already been added to the server status check settings. (%s/%s/%s)"
#define STR_W_S2O06_1	"Syslog check data could not be checked more than %d minutes. SIGHUP requested to syslogd."
#define STR_W_S2O06_2	"Syslog occurrence hostname(%s) and server hostname(%s) are different. (If necessary, set IT_SYSLOGHOST_USEHOSTNAME = Y in the /etc/IT.cfg file.)"
#define STR_W_S2O06_3	"Failed to receive Syslog data for %d minutes. Syslog restart was requested."
#define STR_W_S2O06_3_1 "Syslog check data could not be checked more than %d minutes. Syslog restart was requested."
#define STR_W_S2O06_4   "Syslog check data could not be checked more than %d minutes. Send a test message to Syslog."
#define STR_I_S2O06		"Syslog check data was normally received."
#define STR_W_S2O07_1	"S2O restart has been started."
#define STR_W_S2O07_2	"S2O restart has ended."
#define STR_W_S2O07_3	"S2O restart cannot proceed. (%s)"
#define STR_W_S2O08		"Failed to check performance check data more than %d minutes. Restarted IT.perf."
#define STR_I_S2O08		"Performance check data was normally received."
#define STR_W_S2O09		"Failed to check system check data more than %d minutes. Restarted IT.schd."
#define STR_I_S2O09		"System check data was normally received."
#define STR_W_S2O10_1	"Due to delays in DB processing, saving performance data in the IT.% file was skipped. Skipped performance items vary by daemon."
#define STR_W_HAC01_2   "S2O HA monitoring started in Active mode Please check the S2O monitoring settings."
#define STR_W_HAC01_2_1	"S2O HA monitoring has started in active mode, but there are no Oracle monitoring settings enabled."
#define STR_W_HAC01_1   "S2O HA monitoring mode is operating in Active state." /* 데몬 재기동시 메세지(ACTIVE인 경우) */
#define STR_W_HAC02_2   "S2O HA monitoring started in Standby mode Please check the S2O monitoring settings."
#define STR_W_HAC02_1   "S2O HA monitoring mode is operating in Standby state."     /* 데몬 재기동시 메세지(STANDBY인 경우) */
#define STR_C_HAC03_1 	"HA monitoring has been deleted"
#define STR_C_HAC04_1	"HA monitoring settings error"
#define STR_W_HAC04_1   "There is something wrong with the HA status monitoring. Please check the monitoring settings."
#define STR_C_HAC05_1   "Server HA mode is Active. If  do not manually enter S2O HA setup mode, S2O is not monitoring. (HA Monitoring Status: Standby)"
#define STR_W_HAC05_2   "Before switching the S2O HA monitoring state from Active to Standby, the HA state was returned to Active."
#define STR_C_HAC06_1   "Server HA mode is Standby. Please manually switch to S2O HA setting mode. (HA Monitoring Status: Active)"
#define STR_W_HAC06_2   "Before switching the S2O HA monitoring state from Standby to Active, the HA state was returned to Standby."
#define STR_W_HAC07_1   "S2O HA Process monitoring is Active."
#define STR_W_HAC07_2   "S2O HA Filesystem monitoring is Active."
#define STR_W_HAC07_3   "S2O HA Oracle monitoring is Active."
#define STR_W_HAC07_3_1	"S2O HA Oracle monitoring is Active, but there are no Oracle monitoring settings enabled."
#define STR_W_HAC07_4   "S2O HA File System Inode monitoring is Active."
#define STR_W_HAC08_1   "S2O HA Process monitoring is Standby."
#define STR_W_HAC08_2   "S2O HA Filesystem monitoring is Standby."
#define STR_W_HAC08_3   "S2O HA Oracle monitoring is Standby."
#define STR_W_HAC08_4   "S2O HA File System Inode monitoring is Standby."
#define STR_C_S2O01		"S2O daemon(%s) has high resource usage. (CPU:%.f%%, VSZ:%.fKB)"

#else
#define STR_W_S2O11_1 	"Agent 환경파일 저장 중 마스터콘솔과 연결이 불안정하여 실패하였습니다. 다시 시도하여 주시기 바랍니다."
#define STR_I_S2O02_1 	"S2O: 최근 %d초 동안 정의되지 않은 syslog 메세지 %ld건이 모니터링에서 제외되었습니다."
#define STR_W_S2O03		"Agent(%s)가 %d분 이상 작동하지 않고 있습니다. Agent(%s)를 restart합니다."
#define STR_W_S2O03_2	"Accept Error 가 %d회 연속으로 발생하였기 때문에 Agent(%s)를 재시작됩니다."
#define STR_W_S2O03_3	"Accept Error 가 %d회 연속으로 발생하였기 때문에 Agent(%s)를 종료합니다."
#define STR_W_S2O04_1	"'%s' 장비는 메세지가 많이 발생했습니다. 파일(%s), 현재(%d%%:%dcnt), 설정(%d%%:%dcnt))"
#define STR_W_S2O04_2	"'%s' 파일의 메세지 분석에 실패했습니다."
#define STR_I_S2O04_1	"파일(%s)의 메세지 과부하 분석이 정상적으로 완료되었습니다."
#define STR_W_S2O05_1	"서버체크 설정에 host 를 추가하였습니다. (%s/%s/%s)"
#define STR_W_S2O05_2	"서버체크 설정에 host 를 추가하는데 실패하였습니다. (%s/%s/%s)"
#define STR_W_S2O05_3	"서버체크 설정에서 host 를 변경하였습니다. (%s/%s/%s)"
#define STR_W_S2O05_4	"서버체크 설정에서 host 를 변경하는데 실패하였습니다. (%s/%s/%s)"
#define STR_W_S2O05_5	"서버체크 설정에서 host 를 제거하였습니다. (%s/%s/%s)"
#define STR_W_S2O05_6	"서버체크 설정에서 host 를 제거하는데 실패하였습니다. (%s/%s/%s)"
#define STR_W_S2O05_7	"서버체크 설정에서 host 제거를 위한 대상이 존재하지 않습니다. (%s/%s/%s)"
#define STR_W_S2O05_8	"서버체크 설정에서 host 변경를 위한 대상이 존재하지 않습니다. (%s/%s/%s)"
#define STR_W_S2O05_9	"서버체크 설정에 host 가 이미 추가되어 있습니다. (%s/%s/%s)"
#define STR_W_S2O06_1	"Syslog 체크 데이터를 %d분 이상 확인하지 못했습니다. syslogd에 SIGHUP를 요청했습니다."
#define STR_W_S2O06_2	"Syslog 발생 hostname(%s)과 server hostname(%s)이 다릅니다.  ( 필요시 /etc/IT.cfg 파일에 IT_SYSLOGHOST_USEHOSTNAME = Y 설정 바랍니다. )"
#define STR_W_S2O06_3	"%d분 동안 Syslog 데이터를 수신하지 못했습니다. syslog 재시작이 요청되었습니다."
#define STR_W_S2O06_3_1 "Syslog 체크 데이터를 %d분 이상 확인하지 못했습니다. Syslog 재시작이 요청되었습니다."
#define STR_W_S2O06_4   "Syslog 체크 데이터를 %d분 이상 확인하지 못했습니다. Syslog로 테스트 메세지를 전송합니다."
#define STR_I_S2O06		"Syslog 체크 데이터를 정상적으로 수신하였습니다."
#define STR_W_S2O07_1	"S2O 재기동이 사작되었습니다."
#define STR_W_S2O07_2	"S2O 재기동이 종료되었습니다."
#define STR_W_S2O07_3	"S2O 재기동을 진행할 수 없습니다. (%s)"
#define STR_W_S2O08		"성능 체크 데이터를 %d분 이상 확인하지 못했습니다. IT.perf를 restart했습니다."
#define STR_I_S2O08		"성능 체크 데이터를 정상적으로 수신하였습니다."
#define STR_W_S2O09		"시스템 체크 데이터를 %d분 이상 확인하지 못했습니다. IT.schd를 restart했습니다."
#define STR_I_S2O09		"시스템 체크 데이터를 정상적으로 수신하였습니다."
#define STR_W_S2O10_1	"DB 처리 지연으로 IT.% 파일의 성능 데이터 저장이 skip 되었습니다. skip된 성능 항목은 데몬별로 다릅니다."
#define STR_W_HAC01_2   "S2O HA 모니터링이 Active 모드로 시작되었습니다 S2O 모니터링 설정을 확인해 주시기 바랍니다."
#define STR_W_HAC01_2_1	"S2O HA 모니터링이 Active 모드에서 시작되었지만 활성화된 Oracle 모니터링 설정은 없습니다."
#define STR_W_HAC01_1   "S2O HA 모니터링 모드가  Active 상태로 운영 중입니다."  /* 데몬 재기동시 메세지(ACTIVE인 경우) */
#define STR_W_HAC02_2   "S2O HA 모니터링이 Standby 모드로 시작되었습니다 S2O 모니터링 설정을 확인해 주시기 바랍니다."
#define STR_W_HAC02_1   "S2O HA 모니터링 모드가  Standby 상태로 운영 중입니다."  /* 데몬 재기동시 메세지(STANDBY인 경우) */
#define STR_C_HAC03_1	"HA 모니터링이 제거 되었습니다."
#define STR_C_HAC04_1	"HA 모니터링 설정에 오류가 있습니다."
#define STR_W_HAC04_1   "HA 상태 모니터링에 문제가 있습니다. 모니터링 설정을 확인해 주시기 바랍니다."
#define STR_C_HAC05_1   "서버 HA 모드가 Active입니다. S2O HA 설정 모드 전환을 수동으로 안할 경우 모니터링이 안됩니다.(HA 모니터링 상태 : Standby)"
#define STR_W_HAC05_2   "S2O HA 모니터링 상태를 Active에서 Standby로 전환전에 HA 상태는 Active로 다시 복귀 되었습니다."
#define STR_C_HAC06_1   "서버 HA 모드가 Standby입니다. S2O HA 설정 모드 전환을 수동으로 진행해 주세요. (HA 모니터링 상태 : Active)"
#define STR_W_HAC06_2   "S2O HA 모니터링 상태를 Standby에서 Active로 전환전에 HA 상태는 Standby로 다시 복귀 되었습니다."
#define STR_W_HAC07_1   "S2O HA 프로세스 모니터링이 Active 상태입니다."
#define STR_W_HAC07_2   "S2O HA 파일시스템 모니터링이 Active 상태입니다."
#define STR_W_HAC07_3   "S2O HA 오라클 모니터링이 Active 상태입니다."
#define STR_W_HAC07_3_1	"S2O HA 오라클 모니터링이 Active 상태이지만 활성화된 Oracle 모니터링 설정은 없습니다."
#define STR_W_HAC07_4   "S2O HA File System Inode 모니터링이 Active 상태입니다."
#define STR_W_HAC08_1   "S2O HA 프로세스 모니터링이 Standby 상태입니다."
#define STR_W_HAC08_2   "S2O HA 파일시스템 모니터링이 Standby 상태입니다."
#define STR_W_HAC08_3   "S2O HA 오라클 모니터링이 Standby 상태입니다."
#define STR_W_HAC08_4   "S2O HA File System Inode 모니터링이 Standby 상태입니다."
#define STR_C_S2O01		"S2O 데몬(%s)의 리소스 사용량이 높습니다. (CPU:%.f%%, VSZ:%.fKB)"
#endif

