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
#define MSG_C_S2O01		"CS2O101"		/* S2O DAEMON Resource ��뷮�� ���� ��� */
#define MSG_W_S2O11 	"WCFG101"		/* Config ���� ���� ���� */
#define MSG_I_S2O02 	"IS2O102"		/* ���ܵ� syslog �޼��� �˸� ( 10���̻�� ���� �ʴ� 1���̻�ÿ��� �߻�) */
#define MSG_W_S2O03     "WS2O103"		/* Agent ���� ���� ���� */
#define MSG_W_S2O05		"WS2O105"		/* üũ ���� ���� */
#define MSG_W_S2O06		"WS2O106"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_I_S2O06		"IS2O106"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_W_S2O07     "WS2O107"		/* S2O ��⵿ */
#define MSG_W_S2O08		"WS2O108"		/* ���� üũ ������ Ȯ�� */
#define MSG_I_S2O08		"IS2O108"		/* ���� üũ ������ Ȯ�� */
#define MSG_W_S2O09		"WS2O109"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_I_S2O09		"IS2O109"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_W_HAC01 	"WHAC101"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���(Agent �⵿��) */
#define MSG_W_HAC02 	"WHAC102"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���(Agent �⵿��) */
#define MSG_C_HAC03 	"CHAC103"		/* HA ����͸��� ���� */
#define MSG_C_HAC04 	"CHAC104"		/* HA ����͸� ���� ���� */
#define MSG_W_HAC04 	"WHAC104"		/* HA ����͸� ������ ������ �ִ� ��� (Agent �⵿��) */
#define MSG_C_HAC05 	"CHAC105"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC105"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC106"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC106"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC107"		/* HA ���� ����͸��� ���� */
#define MSG_W_HAC08 	"WHAC108"		/* HA ���� ����͸��� ���� */
#elif defined(AIX)
#define MSG_C_S2O01		"CS2O301"		/* S2O DAEMON Resource ��뷮�� ���� ��� */
#define MSG_W_S2O11 	"WCFG301"		/* Config ���� ���� ���� */
#define MSG_I_S2O02 	"IS2O302"		/* ���ܵ� syslog �޼��� �˸� ( 10���̻�� ���� �ʴ� 1���̻�ÿ��� �߻�) */
#define MSG_W_S2O03     "WS2O303"		/* Agent ���� ���� ���� */
#define MSG_W_S2O05		"WS2O305"		/* üũ ���� ���� */
#define MSG_W_S2O06		"WS2O306"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_I_S2O06		"IS2O306"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_W_S2O07     "WS2O307"		/* S2O ��⵿ */
#define MSG_W_S2O08		"WS2O308"		/* ���� üũ ������ Ȯ�� */
#define MSG_I_S2O08		"IS2O308"		/* ���� üũ ������ Ȯ�� */
#define MSG_W_S2O09		"WS2O309"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_I_S2O09		"IS2O309"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_W_HAC01 	"WHAC301"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���(Agent �⵿��) */
#define MSG_W_HAC02 	"WHAC302"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���((Agent �⵿��) */
#define MSG_C_HAC03 	"CHAC303"		/* HA ����͸��� ���� */
#define MSG_C_HAC04 	"CHAC304"		/* HA ����͸� ���� ���� */
#define MSG_W_HAC04 	"WHAC304"		/* HA ����͸� ������ ������ �ִ� ��� (Agent �⵿��) */
#define MSG_C_HAC05 	"CHAC305"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC305"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC306"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC306"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC307"		/* HA ���� ����͸��� ���� */
#define MSG_W_HAC08 	"WHAC308"		/* HA ���� ����͸��� ���� */
#elif defined(HPUX)
#define MSG_C_S2O01		"CS2O401"		/* S2O DAEMON Resource ��뷮�� ���� ��� */
#define MSG_W_S2O11 	"WCFG401"		/* Config ���� ���� ���� */
#define MSG_I_S2O02 	"IS2O402"		/* ���ܵ� syslog �޼��� �˸� ( 10���̻�� ���� �ʴ� 1���̻�ÿ��� �߻�) */
#define MSG_W_S2O03     "WS2O403"		/* Agent ���� ���� ���� */
#define MSG_W_S2O05		"WS2O405"		/* üũ ���� ���� */
#define MSG_W_S2O06		"WS2O406"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_I_S2O06		"IS2O406"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_W_S2O07     "WS2O407"		/* S2O ��⵿ */
#define MSG_W_S2O08		"WS2O408"		/* ���� üũ ������ Ȯ�� */
#define MSG_I_S2O08		"IS2O408"		/* ���� üũ ������ Ȯ�� */
#define MSG_W_S2O09		"WS2O409"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_I_S2O09		"IS2O409"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_W_HAC01 	"WHAC401"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���(Agent �⵿��) */
#define MSG_W_HAC02 	"WHAC402"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���((Agent �⵿��) */
#define MSG_C_HAC03 	"CHAC403"		/* HA ����͸��� ���� */
#define MSG_C_HAC04 	"CHAC404"		/* HA ����͸� ���� ���� */
#define MSG_W_HAC04 	"WHAC404"		/* HA ����͸� ������ ������ �ִ� ��� (Agent �⵿��) */
#define MSG_C_HAC05 	"CHAC405"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC405"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC406"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC406"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC407"		/* HA ���� ����͸��� ���� */
#define MSG_W_HAC08 	"WHAC408"		/* HA ���� ����͸��� ���� */
#elif defined(NCRUX)
#define MSG_C_S2O01		"CS2O501"		/* S2O DAEMON Resource ��뷮�� ���� ��� */
#define MSG_W_S2O11 	"WCFG501"		/* Config ���� ���� ���� */
#define MSG_I_S2O02 	"IS2O502"		/* ���ܵ� syslog �޼��� �˸� ( 10���̻�� ���� �ʴ� 1���̻�ÿ��� �߻�) */
#define MSG_W_S2O03     "WS2O503"		/* Agent ���� ���� ���� */
#define MSG_W_S2O05		"WS2O505"		/* üũ ���� ���� */
#define MSG_W_S2O06		"WS2O506"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_I_S2O06		"IS2O506"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_W_S2O07     "WS2O507"		/* S2O ��⵿ */
#define MSG_W_S2O08		"WS2O508"		/* ���� üũ ������ Ȯ�� */
#define MSG_I_S2O08		"IS2O508"		/* ���� üũ ������ Ȯ�� */
#define MSG_W_S2O09		"WS2O509"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_I_S2O09		"IS2O509"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_W_HAC01 	"WHAC501"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���(Agent �⵿��) */
#define MSG_W_HAC02 	"WHAC502"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���((Agent �⵿��) */
#define MSG_C_HAC03 	"CHAC503"		/* HA ����͸��� ���� */
#define MSG_C_HAC04 	"CHAC504"		/* HA ����͸� ���� ���� */
#define MSG_W_HAC04 	"WHAC504"		/* HA ����͸� ������ ������ �ִ� ��� (Agent �⵿��) */
#define MSG_C_HAC05 	"CHAC505"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC505"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC506"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC506"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC507"		/* HA ���� ����͸��� ���� */
#define MSG_W_HAC08 	"WHAC508"		/* HA ���� ����͸��� ���� */
#elif defined(DGUX)
#define MSG_C_S2O01		"CS2O701"		/* S2O DAEMON Resource ��뷮�� ���� ��� */
#define MSG_W_S2O11 	"WCFG701"		/* Config ���� ���� ���� */
#define MSG_I_S2O02 	"IS2O702"		/* ���ܵ� syslog �޼��� �˸� ( 10���̻�� ���� �ʴ� 1���̻�ÿ��� �߻�) */
#define MSG_W_S2O03     "WS2O703"		/* Agent ���� ���� ���� */
#define MSG_W_S2O05		"WS2O705"		/* üũ ���� ���� */
#define MSG_W_S2O06		"WS2O706"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_I_S2O06		"IS2O706"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_W_S2O07     "WS2O707"		/* S2O ��⵿ */
#define MSG_W_S2O08		"WS2O708"		/* ���� üũ ������ Ȯ�� */
#define MSG_I_S2O08		"IS2O708"		/* ���� üũ ������ Ȯ�� */
#define MSG_W_S2O09		"WS2O709"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_I_S2O09		"IS2O709"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_W_HAC01 	"WHAC701"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���(Agent �⵿��) */
#define MSG_W_HAC02 	"WHAC702"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���((Agent �⵿��) */
#define MSG_C_HAC03 	"CHAC703"		/* HA ����͸��� ���� */
#define MSG_C_HAC04 	"CHAC704"		/* HA ����͸� ���� ���� */
#define MSG_W_HAC04 	"WHAC704"		/* HA ����͸� ������ ������ �ִ� ��� (Agent �⵿��) */
#define MSG_C_HAC05 	"CHAC705"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC705"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC706"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC706"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC707"		/* HA ���� ����͸��� ���� */
#define MSG_W_HAC08 	"WHAC708"		/* HA ���� ����͸��� ���� */
#else		/* SUN2 */	
#define MSG_C_S2O01		"CS2O201"		/* S2O DAEMON Resource ��뷮�� ���� ��� */
#define MSG_W_S2O11 	"WCFG201"		/* Config ���� ���� ���� */
#define MSG_W_S2O11 	"WCFG201"		/* Config ���� ���� ���� */
#define MSG_I_S2O02 	"IS2O202"		/* ���ܵ� syslog �޼��� �˸� ( 10���̻�� ���� �ʴ� 1���̻�ÿ��� �߻�) */
#define MSG_W_S2O03     "WS2O203"		/* Agent ���� ���� ���� */
#define MSG_W_S2O05		"WS2O205"		/* üũ ���� ���� */
#define MSG_W_S2O06		"WS2O206"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_I_S2O06		"IS2O206"		/* SYSLOG üũ ������ Ȯ�� */
#define MSG_W_S2O07     "WS2O207"		/* S2O ��⵿ */
#define MSG_W_S2O08		"WS2O208"		/* ���� üũ ������ Ȯ�� */
#define MSG_I_S2O08		"IS2O208"		/* ���� üũ ������ Ȯ�� */
#define MSG_W_S2O09		"WS2O209"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_I_S2O09		"IS2O209"		/* �ý��� üũ ������ Ȯ�� */
#define MSG_W_HAC01 	"WHAC201"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���(Agent �⵿��) */
#define MSG_W_HAC02 	"WHAC202"		/* HA ����͸��� ���� �Ǵ� HA ����͸��� �������� ���((Agent �⵿��) */
#define MSG_C_HAC03 	"CHAC203"		/* HA ����͸��� ���� */
#define MSG_C_HAC04 	"CHAC204"		/* HA ����͸� ���� ���� */
#define MSG_W_HAC04 	"WHAC204"		/* HA ����͸� ������ ������ �ִ� ��� (Agent �⵿��) */
#define MSG_C_HAC05 	"CHAC205"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_W_HAC05 	"WHAC205"		/* HA ����͸� ��ȯ �ʿ� (STANDBY -> ACTIVE) */
#define MSG_C_HAC06 	"CHAC206"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC06 	"WHAC206"		/* HA ����͸� ��ȯ �ʿ� (ACTIVE -> STANDBY) */
#define MSG_W_HAC07 	"WHAC207"		/* HA ���� ����͸��� ���� */
#define MSG_W_HAC08 	"WHAC208"		/* HA ���� ����͸��� ���� */
#endif

#define MSG_W_S2O04     "WS2O004" 		/* IT.dat(����) ���� ���� */
#define MSG_I_S2O04     "IS2O004" 		/* IT.dat(����) ���� ���� */
#define MSG_W_S2O10		"WS2O010"		/* IT.���� DB ���� skip �� ��� �˸� */

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
#define STR_W_HAC01_1   "S2O HA monitoring mode is operating in Active state." /* ���� ��⵿�� �޼���(ACTIVE�� ���) */
#define STR_W_HAC02_2   "S2O HA monitoring started in Standby mode Please check the S2O monitoring settings."
#define STR_W_HAC02_1   "S2O HA monitoring mode is operating in Standby state."     /* ���� ��⵿�� �޼���(STANDBY�� ���) */
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
#define STR_W_S2O11_1 	"Agent ȯ������ ���� �� �������ְܼ� ������ �Ҿ����Ͽ� �����Ͽ����ϴ�. �ٽ� �õ��Ͽ� �ֽñ� �ٶ��ϴ�."
#define STR_I_S2O02_1 	"S2O: �ֱ� %d�� ���� ���ǵ��� ���� syslog �޼��� %ld���� ����͸����� ���ܵǾ����ϴ�."
#define STR_W_S2O03		"Agent(%s)�� %d�� �̻� �۵����� �ʰ� �ֽ��ϴ�. Agent(%s)�� restart�մϴ�."
#define STR_W_S2O03_2	"Accept Error �� %dȸ �������� �߻��Ͽ��� ������ Agent(%s)�� ����۵˴ϴ�."
#define STR_W_S2O03_3	"Accept Error �� %dȸ �������� �߻��Ͽ��� ������ Agent(%s)�� �����մϴ�."
#define STR_W_S2O04_1	"'%s' ���� �޼����� ���� �߻��߽��ϴ�. ����(%s), ����(%d%%:%dcnt), ����(%d%%:%dcnt))"
#define STR_W_S2O04_2	"'%s' ������ �޼��� �м��� �����߽��ϴ�."
#define STR_I_S2O04_1	"����(%s)�� �޼��� ������ �м��� ���������� �Ϸ�Ǿ����ϴ�."
#define STR_W_S2O05_1	"����üũ ������ host �� �߰��Ͽ����ϴ�. (%s/%s/%s)"
#define STR_W_S2O05_2	"����üũ ������ host �� �߰��ϴµ� �����Ͽ����ϴ�. (%s/%s/%s)"
#define STR_W_S2O05_3	"����üũ �������� host �� �����Ͽ����ϴ�. (%s/%s/%s)"
#define STR_W_S2O05_4	"����üũ �������� host �� �����ϴµ� �����Ͽ����ϴ�. (%s/%s/%s)"
#define STR_W_S2O05_5	"����üũ �������� host �� �����Ͽ����ϴ�. (%s/%s/%s)"
#define STR_W_S2O05_6	"����üũ �������� host �� �����ϴµ� �����Ͽ����ϴ�. (%s/%s/%s)"
#define STR_W_S2O05_7	"����üũ �������� host ���Ÿ� ���� ����� �������� �ʽ��ϴ�. (%s/%s/%s)"
#define STR_W_S2O05_8	"����üũ �������� host ���渦 ���� ����� �������� �ʽ��ϴ�. (%s/%s/%s)"
#define STR_W_S2O05_9	"����üũ ������ host �� �̹� �߰��Ǿ� �ֽ��ϴ�. (%s/%s/%s)"
#define STR_W_S2O06_1	"Syslog üũ �����͸� %d�� �̻� Ȯ������ ���߽��ϴ�. syslogd�� SIGHUP�� ��û�߽��ϴ�."
#define STR_W_S2O06_2	"Syslog �߻� hostname(%s)�� server hostname(%s)�� �ٸ��ϴ�.  ( �ʿ�� /etc/IT.cfg ���Ͽ� IT_SYSLOGHOST_USEHOSTNAME = Y ���� �ٶ��ϴ�. )"
#define STR_W_S2O06_3	"%d�� ���� Syslog �����͸� �������� ���߽��ϴ�. syslog ������� ��û�Ǿ����ϴ�."
#define STR_W_S2O06_3_1 "Syslog üũ �����͸� %d�� �̻� Ȯ������ ���߽��ϴ�. Syslog ������� ��û�Ǿ����ϴ�."
#define STR_W_S2O06_4   "Syslog üũ �����͸� %d�� �̻� Ȯ������ ���߽��ϴ�. Syslog�� �׽�Ʈ �޼����� �����մϴ�."
#define STR_I_S2O06		"Syslog üũ �����͸� ���������� �����Ͽ����ϴ�."
#define STR_W_S2O07_1	"S2O ��⵿�� ���۵Ǿ����ϴ�."
#define STR_W_S2O07_2	"S2O ��⵿�� ����Ǿ����ϴ�."
#define STR_W_S2O07_3	"S2O ��⵿�� ������ �� �����ϴ�. (%s)"
#define STR_W_S2O08		"���� üũ �����͸� %d�� �̻� Ȯ������ ���߽��ϴ�. IT.perf�� restart�߽��ϴ�."
#define STR_I_S2O08		"���� üũ �����͸� ���������� �����Ͽ����ϴ�."
#define STR_W_S2O09		"�ý��� üũ �����͸� %d�� �̻� Ȯ������ ���߽��ϴ�. IT.schd�� restart�߽��ϴ�."
#define STR_I_S2O09		"�ý��� üũ �����͸� ���������� �����Ͽ����ϴ�."
#define STR_W_S2O10_1	"DB ó�� �������� IT.% ������ ���� ������ ������ skip �Ǿ����ϴ�. skip�� ���� �׸��� ���󺰷� �ٸ��ϴ�."
#define STR_W_HAC01_2   "S2O HA ����͸��� Active ���� ���۵Ǿ����ϴ� S2O ����͸� ������ Ȯ���� �ֽñ� �ٶ��ϴ�."
#define STR_W_HAC01_2_1	"S2O HA ����͸��� Active ��忡�� ���۵Ǿ����� Ȱ��ȭ�� Oracle ����͸� ������ �����ϴ�."
#define STR_W_HAC01_1   "S2O HA ����͸� ��尡  Active ���·� � ���Դϴ�."  /* ���� ��⵿�� �޼���(ACTIVE�� ���) */
#define STR_W_HAC02_2   "S2O HA ����͸��� Standby ���� ���۵Ǿ����ϴ� S2O ����͸� ������ Ȯ���� �ֽñ� �ٶ��ϴ�."
#define STR_W_HAC02_1   "S2O HA ����͸� ��尡  Standby ���·� � ���Դϴ�."  /* ���� ��⵿�� �޼���(STANDBY�� ���) */
#define STR_C_HAC03_1	"HA ����͸��� ���� �Ǿ����ϴ�."
#define STR_C_HAC04_1	"HA ����͸� ������ ������ �ֽ��ϴ�."
#define STR_W_HAC04_1   "HA ���� ����͸��� ������ �ֽ��ϴ�. ����͸� ������ Ȯ���� �ֽñ� �ٶ��ϴ�."
#define STR_C_HAC05_1   "���� HA ��尡 Active�Դϴ�. S2O HA ���� ��� ��ȯ�� �������� ���� ��� ����͸��� �ȵ˴ϴ�.(HA ����͸� ���� : Standby)"
#define STR_W_HAC05_2   "S2O HA ����͸� ���¸� Active���� Standby�� ��ȯ���� HA ���´� Active�� �ٽ� ���� �Ǿ����ϴ�."
#define STR_C_HAC06_1   "���� HA ��尡 Standby�Դϴ�. S2O HA ���� ��� ��ȯ�� �������� ������ �ּ���. (HA ����͸� ���� : Active)"
#define STR_W_HAC06_2   "S2O HA ����͸� ���¸� Standby���� Active�� ��ȯ���� HA ���´� Standby�� �ٽ� ���� �Ǿ����ϴ�."
#define STR_W_HAC07_1   "S2O HA ���μ��� ����͸��� Active �����Դϴ�."
#define STR_W_HAC07_2   "S2O HA ���Ͻý��� ����͸��� Active �����Դϴ�."
#define STR_W_HAC07_3   "S2O HA ����Ŭ ����͸��� Active �����Դϴ�."
#define STR_W_HAC07_3_1	"S2O HA ����Ŭ ����͸��� Active ���������� Ȱ��ȭ�� Oracle ����͸� ������ �����ϴ�."
#define STR_W_HAC07_4   "S2O HA File System Inode ����͸��� Active �����Դϴ�."
#define STR_W_HAC08_1   "S2O HA ���μ��� ����͸��� Standby �����Դϴ�."
#define STR_W_HAC08_2   "S2O HA ���Ͻý��� ����͸��� Standby �����Դϴ�."
#define STR_W_HAC08_3   "S2O HA ����Ŭ ����͸��� Standby �����Դϴ�."
#define STR_W_HAC08_4   "S2O HA File System Inode ����͸��� Standby �����Դϴ�."
#define STR_C_S2O01		"S2O ����(%s)�� ���ҽ� ��뷮�� �����ϴ�. (CPU:%.f%%, VSZ:%.fKB)"
#endif

