/*
   $Id: msgid.h,v 1.7 2002/11/06 srp Exp $  

   Copyright (c) 2000, 2001, 2002 i-TOP System Inc.  All rights reserved.

   2002-09-30
     * Msgid ID Define include file.
	 * R : Real Time Performance data.
	   P : Performance data.(DB gathering data)
	 * First Number  : Machine type (
	 * Second Number : Use communication port(7703) 0: N 1: Y
	 * Third Number  : Messages sequence.
*/

/*
**	Define Message ID.				Last Update : 2002/10/01 -------------------
*/
#if defined(LINUX)
#define MSG_P_SWP00 	"PSWP100"
#define MSG_P_SWP10     "PSWP110"
#define MSG_P_SWP01 	"PSWP101"
#define MSG_P_SWP11     "PSWP111"
#define MSG_I_SWP11     "ISWP111"
#define MSG_W_SWP11     "WSWP111"
#define MSG_F_SWP11     "FSWP111"
#define MSG_C_SWP11     "CSWP111"
#define MSG_W_SWP12 	"WSWP112"
#define MSG_C_SWP12 	"CSWP112"
#define MSG_F_SWP12 	"FSWP112"
#define MSG_I_SWP12 	"ISWP112"		/* Swap 사용률 */
#define MSG_I_SWP13 	"ISWP113"		/* Swap 사용률 */
#define MSG_C_SWP14 	"CSWP114"		/* AIX Swap device(LV) open error */
#define MSG_P_TOP05     "PTOP105"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP106"       /* 설정된 프로세스 정보 저장 */
#define MSG_P_TOP07     "PTOP107"       /* mem Top 10 */
#define MSG_P_PRS00 	"PPRS100"		/* N: send process list */
#define MSG_P_PRS10 	"PPRS110"		/* Y: process_check가 uncheck로 setting시 */
#define MSG_I_PRS11 	"IPRS111"
#define MSG_C_PRS11 	"CPRS111"
#define MSG_I_PRS12 	"IPRS112"
#define MSG_C_PRS12 	"CPRS112"		
#define MSG_F_PRS12 	"FPRS112"		
#define MSG_C_PRS13 	"CPRS113"		
#define MSG_I_PRS14 	"IPRS114"		/* thread수 모니터링 */
#define MSG_C_PRS14 	"CPRS114"		/* thread수 모니터링 */
#define MSG_F_PRS14 	"FPRS114"		/* thread수 모니터링 */
#define MSG_I_PCU11 	"IPCU111"		/* process cpu usage check */
#define MSG_W_PCU11 	"WPCU111"
#define MSG_C_PCU11 	"CPCU111"
#define MSG_F_PCU11 	"FPCU111"
#define MSG_P_PCU11 	"PPCU111"
#define MSG_I_PCU12 	"IPCU112"		/* process memory check */
#define MSG_C_PCU12 	"CPCU112"
#define MSG_I_PCU13 	"IPCU113"		/* process owner check */
#define MSG_C_PCU13 	"CPCU113"
#define MSG_I_PCU14 	"IPCU114"		/* auto action command fail */
#define MSG_C_PCU14 	"CPCU114"		/* auto action command fail */
#define MSG_P_DSK00 	"PDSK100"		/* Disk 관련 Messaged Code */
#define MSG_P_DSK10     "PDSK110"		/* it_useporta = 'Y' */
#define MSG_I_DSK11     "IDSK111"
#define MSG_W_DSK11     "WDSK111"
#define MSG_C_DSK11     "CDSK111"
#define MSG_F_DSK11     "FDSK111"
#define MSG_C_DSK12     "CDSK112"		/* filesystem not fount */
#define MSG_W_DSK12     "WDSK112"		/* filesystem not fount */
#define MSG_C_DSK13     "CDSK113"		/* filesystem operation check */
#define MSG_C_DSK14     "CDSK114"		/* 파일시스템 설정 관련 */
#define MSG_C_DSK15     "CDSK115"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK116"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_W_DSK16     "WDSK116"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_I_DSK17     "IDSK117"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK117"
#define MSG_C_DSK17     "CDSK117"
#define MSG_P_DSI00 	"PDSI100"		/* Inodes 관련 Messaged Code */
#define MSG_P_DSI10     "PDSI110"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI111"
#define MSG_W_DSI11     "WDSI111"
#define MSG_C_DSI11     "CDSI111"
#define MSG_F_DSI11     "FDSI111"
#define MSG_C_DSI12     "CDSI112"
#define MSG_C_DSI14     "CDSI114"		/* Inodes 설정 파일  관련 message code */
#define MSG_W_DSI16     "WDSI116"		/* inodes check가 정상적으로 진행되지 않을 경우 */
#define MSG_P_HWC00 	"PHWC100"		/* 서버 Board별 Temperature */
#define MSG_P_HWC05 	"PHWC105"		/* Sun Enterprise 2.5.1 */
#define MSG_C_HWC01 	"CHWC101"		/* CPU online number */
#define MSG_W_HWC01 	"WHWC101"
#define MSG_I_HWC01 	"IHWC101"
#define MSG_C_HWC02 	"CHWC102"		/* MEMORY Physical size */
#define MSG_W_HWC02 	"WHWC102"		
#define MSG_I_HWC02 	"IHWC102"
#define MSG_F_HWC03 	"FHWC103"		/* Server board celsius */
#define MSG_C_HWC03 	"CHWC103"		/* Server board celsius */
#define MSG_W_HWC03 	"WHWC103"
#define MSG_I_HWC03 	"IHWC103"
#define MSG_P_OSI02		"POSI102"		/* CPU Count 전송 */
#define MSG_P_SYS01		"PSYS101"       /* os info */
#define MSG_P_SYS02		"PSYS102"       /* cpu info */
#define MSG_P_SYS03		"PSYS103"       /* mem info */
#define MSG_P_SYS04		"PSYS104"       /* ip address info */
#define MSG_P_SYS06		"PSYS106"       /* uptime */
#define MSG_P_SYS09		"PSYS109"       /* s2o license */
#define MSG_I_NET01		"INET101"       /* Session Established Connection */
#define MSG_F_NET01		"FNET101"       /* Session Established Connection */
#define MSG_C_NET01		"CNET101"       /* Session Established Connection */
#define MSG_W_NET01		"WNET101"       /* Session Established Connection */
#define MSG_I_NET02		"INET102"       /* Session Non-Established Connection */
#define MSG_F_NET02		"FNET102"       /* Session Non-Established Connection */
#define MSG_C_NET02		"CNET102"       /* Session Non-Established Connection */
#define MSG_W_NET02		"WNET102"       /* Session Non-Established Connection */
#define MSG_F_NET03		"FNET103"       /* protocol port check fatal */
#define MSG_C_NET03		"CNET103"       /* protocol port check critical */
#define MSG_W_NET03		"WNET103"       /* protocol port check warning */
#define MSG_I_NET03		"INET103"       /* protocol port check information */
#define MSG_P_NET03		"PNET103"       /* protocol port check capa save data */
#define MSG_C_SEC01		"CSEC101"       /* 무결성 파일 not found */
#define MSG_C_SEC02		"CSEC102"       
#define MSG_C_SEC11		"CSEC111"       /* 무결성 파일 not found */
#define MSG_C_SEC12		"CSEC112"       
#define MSG_I_SEC02		"ISEC102"       
#define MSG_P_NIC10		"PNIC110"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC111"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC111"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC111"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC111"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC112"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC112"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS17		"CSYS117"       /* omreport(dell서버-linux) */
#define MSG_C_TEP11		"CTEP111"		/* 온도 점검 - omreport (dell서버-linux) */
#define MSG_W_TEP11		"WTEP111"		/* 온도 점검 - omreport (dell서버-linux) */
#define MSG_I_TEP11		"ITEP111"		/* 온도 점검 - omreport (dell서버-linux) */
#define MSG_P_TEP10		"PTEP110"		/* 온도 점검 - omreport (dell서버-linux) */
#define MSG_C_BOT01		"CBOT111"		/* booting 시간 변경 알림 */
#define MSG_W_BOT01		"WBOT111"		/* booting 시간 변경 알림 */
#define MSG_C_ACC11     "CACC111"		/* OS 계정 만료 */
#define MSG_W_ACC11     "WACC111"		/* OS 계정 만료 */
#define MSG_I_ACC11     "IACC111"		/* OS 계정 만료 */
#define MSG_P_ACC11     "PACC111"		/* OS 계정 만료 */
#elif defined(AIX)					/* -------------------------------------------- */
#define MSG_P_SWP00 	"PSWP300"
#define MSG_P_SWP10     "PSWP310"
#define MSG_P_SWP01 	"PSWP301"
#define MSG_P_SWP11     "PSWP311"
#define MSG_I_SWP11     "ISWP311"
#define MSG_W_SWP11     "WSWP311"
#define MSG_F_SWP11     "FSWP311"
#define MSG_C_SWP11     "CSWP311"
#define MSG_I_SWP12 	"ISWP312"
#define MSG_W_SWP12 	"WSWP312"
#define MSG_C_SWP12 	"CSWP312"
#define MSG_F_SWP12 	"FSWP312"
#define MSG_I_SWP13 	"ISWP313"		/* Swap 사용률 */
#define MSG_C_SWP14 	"CSWP314"		/* AIX Swap device(LV) open error */

#define MSG_P_TOP05     "PTOP305"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP306"       /* 설정된 프로세스 정보 저장 */
#define MSG_P_TOP07     "PTOP307"       /* mem Top 10 */
#define MSG_P_PRS00 	"PPRS300"
#define MSG_P_PRS10 	"PPRS310"
#define MSG_I_PRS11 	"IPRS311"
#define MSG_C_PRS11 	"CPRS311"
#define MSG_I_PRS12 	"IPRS312"
#define MSG_F_PRS12 	"FPRS312"
#define MSG_C_PRS12 	"CPRS312"
#define MSG_C_PRS13 	"CPRS313"		
#define MSG_I_PRS14 	"IPRS314"		/* thread수 모니터링 */
#define MSG_C_PRS14 	"CPRS314"		/* thread수 모니터링 */
#define MSG_F_PRS14 	"FPRS314"		/* thread수 모니터링 */	
#define MSG_I_PCU11 	"IPCU311"		/* process cpu usage check */
#define MSG_W_PCU11 	"WPCU311"
#define MSG_C_PCU11 	"CPCU311"
#define MSG_F_PCU11 	"FPCU311"
#define MSG_P_PCU11 	"PPCU311"
#define MSG_I_PCU12 	"IPCU312"		/* process memory check */
#define MSG_C_PCU12 	"CPCU312"
#define MSG_I_PCU13 	"IPCU313"		/* process owner check */
#define MSG_C_PCU13 	"CPCU313"
#define MSG_I_PCU14 	"IPCU314"		/* auto action command fail */
#define MSG_C_PCU14 	"CPCU314"		/* auto action command fail */
#define MSG_P_DSK00 	"PDSK300"
#define MSG_P_DSK10     "PDSK310"
#define MSG_I_DSK11     "IDSK311"
#define MSG_W_DSK11     "WDSK311"
#define MSG_C_DSK11     "CDSK311"
#define MSG_F_DSK11     "FDSK311"
#define MSG_C_DSK12     "CDSK312"		/* filesystem not fount */
#define MSG_W_DSK12     "WDSK312"		/* filesystem not fount */
#define MSG_C_DSK13     "CDSK313"		/* filesystem operation check */
#define MSG_C_DSK14     "CDSK314"		/* 파일시스템 설정 관련 */
#define MSG_C_DSK15     "CDSK315"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK316"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_W_DSK16     "WDSK316"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_I_DSK17     "IDSK317"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK317"
#define MSG_C_DSK17     "CDSK317"
#define MSG_P_DSI00 	"PDSI300"		/* Inodes 관련 Messaged Code */
#define MSG_P_DSI10     "PDSI310"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI311"
#define MSG_W_DSI11     "WDSI311"
#define MSG_C_DSI11     "CDSI311"
#define MSG_F_DSI11     "FDSI311"
#define MSG_C_DSI12     "CDSI312"
#define MSG_C_DSI14     "CDSI314"		/* Inodes 설정 파일  관련 message code */
#define MSG_W_DSI16     "WDSI316"		/* inodes check가 정상적으로 진행되지 않을 경우 */
/* H/W */
#define MSG_P_HWC00 	"PHWC300"		/* 서버 Board별 Temperature */
#define MSG_C_HWC01 	"CHWC301"		/* CPU online number */
#define MSG_W_HWC01 	"WHWC301"
#define MSG_I_HWC01 	"IHWC301"
#define MSG_C_HWC02 	"CHWC302"		/* MEMORY Physical size */
#define MSG_W_HWC02 	"WHWC302"		
#define MSG_I_HWC02 	"IHWC302"
#define MSG_F_HWC03 	"FHWC303"		/* Server board celsius */
#define MSG_C_HWC03 	"CHWC303"		/* Server board celsius */
#define MSG_W_HWC03 	"WHWC303"
#define MSG_I_HWC03 	"IHWC303"
/* O/S Information */
#define MSG_P_OSI02		"POSI302"		/* CPU Count 전송 */
#define MSG_P_SYS01		"PSYS301"       /* os info */
#define MSG_P_SYS02		"PSYS302"       /* cpu info */
#define MSG_P_SYS03		"PSYS303"       /* mem info */
#define MSG_P_SYS04		"PSYS304"       /* ip address info */
#define MSG_P_SYS06		"PSYS306"       /* uptime */
#define MSG_P_SYS09		"PSYS309"       /* s2o license */
#define MSG_I_NET01		"INET301"       /* Session Established Connection */
#define MSG_F_NET01		"FNET301"       /* Session Established Connection */
#define MSG_C_NET01		"CNET301"       /* Session Established Connection */
#define MSG_W_NET01		"WNET301"       /* Session Established Connection */
#define MSG_I_NET02		"INET302"       /* Session Non-Established Connection */
#define MSG_F_NET02		"FNET302"       /* Session Non-Established Connection */
#define MSG_C_NET02		"CNET302"       /* Session Non-Established Connection */
#define MSG_W_NET02		"WNET302"       /* Session Non-Established Connection */
#define MSG_F_NET03		"FNET303"       /* protocol port check fatal */
#define MSG_C_NET03		"CNET303"       /* protocol port check critical */
#define MSG_W_NET03		"WNET303"       /* protocol port check warning */
#define MSG_I_NET03		"INET303"       /* protocol port check information */
#define MSG_P_NET03		"PNET303"       /* protocol port check capa save data */
#define MSG_C_SEC01		"CSEC301"       /* 무결성 파일 not found */
#define MSG_C_SEC02		"CSEC302"       
#define MSG_C_SEC11		"CSEC311"       /* 무결성 파일 not found */
#define MSG_C_SEC12		"CSEC312"       
#define MSG_I_SEC02		"ISEC302"       
#define MSG_P_NIC10		"PNIC310"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC311"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC311"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC311"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC311"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC312"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC312"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS16     "CSYS316"		/* aix errpt 점검 code */
#define MSG_C_SYS17		"CSYS317"       /* omreport(del서버-linux) */
#define MSG_C_BOT01		"CBOT311"		/* booting 시간 변경 알림 */
#define MSG_W_BOT01		"WBOT311"		/* booting 시간 변경 알림 */
#define MSG_C_ACC11     "CACC311"		/* OS 계정 만료 */
#define MSG_W_ACC11     "WACC311"		/* OS 계정 만료 */
#define MSG_I_ACC11     "IACC311"		/* OS 계정 만료 */
#define MSG_P_ACC11     "PACC311"		/* OS 계정 만료 */
#elif defined(HPUX)					/* ----------------------------------------- */
#define MSG_P_SWP00 	"PSWP400"
#define MSG_P_SWP10     "PSWP410"
#define MSG_P_SWP01 	"PSWP401"
#define MSG_P_SWP11     "PSWP411"
#define MSG_I_SWP11     "ISWP411"
#define MSG_W_SWP11     "WSWP411"
#define MSG_F_SWP11     "FSWP411"
#define MSG_C_SWP11     "CSWP411"
#define MSG_I_SWP12 	"ISWP412"
#define MSG_W_SWP12 	"WSWP412"
#define MSG_C_SWP12 	"CSWP412"
#define MSG_F_SWP12 	"FSWP412"
#define MSG_I_SWP13 	"ISWP413"		/* Swap 사용률 */
#define MSG_C_SWP14 	"CSWP414"		/* AIX Swap device(LV) open error */

#define MSG_P_TOP05     "PTOP405"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP406"       /* 설정된 프로세스 정보 저장 */
#define MSG_P_TOP07     "PTOP407"       /* mem Top 10 */
#define MSG_P_PRS00 	"PPRS400"
#define MSG_P_PRS10 	"PPRS410"
#define MSG_I_PRS11 	"IPRS411"
#define MSG_C_PRS11 	"CPRS411"
#define MSG_I_PRS12 	"IPRS412"
#define MSG_F_PRS12 	"FPRS412"
#define MSG_C_PRS12 	"CPRS412"
#define MSG_C_PRS13 	"CPRS413"		
#define MSG_I_PRS14 	"IPRS414"		/* thread수 모니터링 */
#define MSG_C_PRS14 	"CPRS414"		/* thread수 모니터링 */	
#define MSG_F_PRS14 	"FPRS414"		/* thread수 모니터링 */	
#define MSG_I_PCU11 	"IPCU411"		/* process cpu usage check */
#define MSG_W_PCU11 	"WPCU411"
#define MSG_C_PCU11 	"CPCU411"
#define MSG_F_PCU11 	"FPCU411"
#define MSG_P_PCU11 	"PPCU411"
#define MSG_I_PCU12 	"IPCU412"		/* process memory check */
#define MSG_C_PCU12 	"CPCU412"
#define MSG_I_PCU13 	"IPCU413"		/* process owner check */
#define MSG_C_PCU13 	"CPCU413"
#define MSG_I_PCU14 	"IPCU414"		/* auto action command fail */
#define MSG_C_PCU14 	"CPCU414"		/* auto action command fail */
#define MSG_P_DSK00 	"PDSK400"
#define MSG_P_DSK10     "PDSK410"
#define MSG_I_DSK11     "IDSK411"
#define MSG_W_DSK11     "WDSK411"
#define MSG_C_DSK11     "CDSK411"
#define MSG_F_DSK11     "FDSK411"
#define MSG_C_DSK12     "CDSK412"		/* filesystem not fount */
#define MSG_W_DSK12     "WDSK412"		/* filesystem not fount */
#define MSG_C_DSK13     "CDSK413"		/* filesystem operation check */
#define MSG_C_DSK14     "CDSK414"		/* 파일시스템 설정 관련 */
#define MSG_C_DSK15     "CDSK415"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK416"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_W_DSK16     "WDSK416"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_I_DSK17     "IDSK417"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK417"
#define MSG_C_DSK17     "CDSK417"
#define MSG_P_DSI00 	"PDSI400"		/* Inodes 관련 Messaged Code */
#define MSG_P_DSI10     "PDSI410"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI411"
#define MSG_W_DSI11     "WDSI411"
#define MSG_C_DSI11     "CDSI411"
#define MSG_F_DSI11     "FDSI411"
#define MSG_C_DSI12     "CDSI412"
#define MSG_C_DSI14     "CDSI414"		/* Inodes 설정 파일  관련 message code */
#define MSG_W_DSI16     "WDSI416"		/* inodes check가 정상적으로 진행되지 않을 경우 */
/* H/W */
#define MSG_P_HWC00 	"PHWC400"		/* 서버 Board별 Temperature */
#define MSG_C_HWC01 	"CHWC401"		/* CPU online number */
#define MSG_W_HWC01 	"WHWC401"
#define MSG_I_HWC01 	"IHWC401"
#define MSG_C_HWC02 	"CHWC402"		/* MEMORY Physical size */
#define MSG_W_HWC02 	"WHWC402"		
#define MSG_I_HWC02 	"IHWC402"
#define MSG_F_HWC03 	"FHWC403"		/* Server board celsius */
#define MSG_C_HWC03 	"CHWC403"		/* Server board celsius */
#define MSG_W_HWC03 	"WHWC403"
#define MSG_I_HWC03 	"IHWC403"
/* O/S Information */
#define MSG_P_OSI02		"POSI402"		/* CPU Count 전송 */
#define MSG_P_SYS01		"PSYS401"       /* os info */
#define MSG_P_SYS02		"PSYS402"       /* cpu info */
#define MSG_P_SYS03		"PSYS403"       /* mem info */
#define MSG_P_SYS04		"PSYS404"       /* ip address info */
#define MSG_P_SYS06		"PSYS406"       /* uptime */
#define MSG_P_SYS09		"PSYS409"       /* s2o license */
#define MSG_I_NET01		"INET401"       /* Session Established Connection */
#define MSG_F_NET01		"FNET401"       /* Session Established Connection */
#define MSG_C_NET01		"CNET401"       /* Session Established Connection */
#define MSG_W_NET01		"WNET401"       /* Session Established Connection */
#define MSG_I_NET02		"INET402"       /* Session Non-Established Connection */
#define MSG_F_NET02		"FNET402"       /* Session Non-Established Connection */
#define MSG_C_NET02		"CNET402"       /* Session Non-Established Connection */
#define MSG_W_NET02		"WNET402"       /* Session Non-Established Connection */
#define MSG_F_NET03		"FNET403"       /* protocol port check fatal */
#define MSG_C_NET03		"CNET403"       /* protocol port check critical */
#define MSG_W_NET03		"WNET403"       /* protocol port check warning */
#define MSG_I_NET03		"INET403"       /* protocol port check information */
#define MSG_P_NET03		"PNET403"       /* protocol port check capa save data */
#define MSG_C_SEC01		"CSEC401"       /* 무결성 파일 not found */
#define MSG_C_SEC02		"CSEC402"       
#define MSG_C_SEC11		"CSEC411"       /* 무결성 파일 not found */
#define MSG_C_SEC12		"CSEC412"       
#define MSG_I_SEC02		"ISEC402"       
#define MSG_P_NIC10		"PNIC410"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC411"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC411"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC411"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC411"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC412"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC412"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS17		"CSYS417"       /* omreport(del서버-linux) */
#define MSG_C_BOT01		"CBOT411"		/* booting 시간 변경 알림 */
#define MSG_W_BOT01		"WBOT411"		/* booting 시간 변경 알림 */
#define MSG_C_ACC11     "CACC411"		/* OS 계정 만료 */
#define MSG_W_ACC11     "WACC411"		/* OS 계정 만료 */
#define MSG_I_ACC11     "IACC411"		/* OS 계정 만료 */
#define MSG_P_ACC11     "PACC411"		/* OS 계정 만료 */
#elif defined(NCRUX)				/* ------------------------------------------- */
#define MSG_P_SWP00 	"PSWP500"
#define MSG_P_SWP10     "PSWP510"
#define MSG_P_SWP01 	"PSWP501"
#define MSG_P_SWP11     "PSWP511"
#define MSG_I_SWP11     "ISWP511"
#define MSG_W_SWP11     "WSWP511"
#define MSG_F_SWP11     "FSWP511"
#define MSG_C_SWP11     "CSWP511"
#define MSG_I_SWP12 	"ISWP512"
#define MSG_W_SWP12 	"WSWP512"
#define MSG_C_SWP12 	"CSWP512"
#define MSG_F_SWP12 	"FSWP512"
#define MSG_I_SWP13 	"ISWP513"		/* Swap 사용률 */
#define MSG_C_SWP14 	"CSWP514"		/* AIX Swap device(LV) open error */

#define MSG_P_TOP05     "PTOP505"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP506"       /* 설정된 프로세스 정보 저장 */
#define MSG_P_TOP07     "PTOP507"       /* mem Top 10 */
#define MSG_P_PRS00 	"PPRS500"
#define MSG_P_PRS10 	"PPRS510"
#define MSG_I_PRS11 	"IPRS511"
#define MSG_C_PRS11 	"CPRS511"
#define MSG_I_PRS12 	"IPRS512"
#define MSG_F_PRS12 	"FPRS512"
#define MSG_C_PRS12 	"CPRS512"
#define MSG_C_PRS13 	"CPRS513"		
#define MSG_I_PRS14 	"IPRS514"		/* thread수 모니터링 */
#define MSG_C_PRS14 	"CPRS514"		/* thread수 모니터링 */	
#define MSG_F_PRS14 	"FPRS514"		/* thread수 모니터링 */	
#define MSG_I_PCU11 	"IPCU511"		/* process cpu usage check */
#define MSG_W_PCU11 	"WPCU511"
#define MSG_C_PCU11 	"CPCU511"
#define MSG_F_PCU11 	"FPCU511"
#define MSG_P_PCU11 	"PPCU511"
#define MSG_I_PCU12 	"IPCU512"		/* process memory check */
#define MSG_C_PCU12 	"CPCU512"
#define MSG_I_PCU13 	"IPCU513"		/* process owner check */
#define MSG_C_PCU13 	"CPCU513"
#define MSG_I_PCU14 	"IPCU514"		/* auto action command fail */
#define MSG_C_PCU14 	"CPCU514"		/* auto action command fail */
#define MSG_P_DSK00 	"PDSK500"
#define MSG_P_DSK10     "PDSK510"
#define MSG_I_DSK11     "IDSK511"
#define MSG_W_DSK11     "WDSK511"
#define MSG_C_DSK11     "CDSK511"
#define MSG_F_DSK11     "FDSK511"
#define MSG_C_DSK12     "CDSK512"		/* filesystem not fount */
#define MSG_W_DSK12     "WDSK512"		/* filesystem not fount */
#define MSG_C_DSK13     "CDSK513"		/* filesystem operation check */
#define MSG_C_DSK14     "CDSK514"		/* 파일시스템 설정 관련 */
#define MSG_C_DSK15     "CDSK515"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK516"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_W_DSK16     "WDSK516"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_I_DSK17     "IDSK517"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK517"
#define MSG_C_DSK17     "CDSK517"
#define MSG_P_DSI00 	"PDSI500"		/* Inodes 관련 Messaged Code */
#define MSG_P_DSI10     "PDSI510"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI511"
#define MSG_W_DSI11     "WDSI511"
#define MSG_C_DSI11     "CDSI511"
#define MSG_F_DSI11     "FDSI511"
#define MSG_C_DSI12     "CDSI512"
#define MSG_C_DSI14     "CDSI514"		/* Inodes 설정 파일  관련 message code */
#define MSG_W_DSI16     "WDSI516"		/* inodes check가 정상적으로 진행되지 않을 경우 */
/* H/W */
#define MSG_P_HWC00 	"PHWC500"		/* 서버 Board별 Temperature */
#define MSG_C_HWC01 	"CHWC501"		/* CPU online number */
#define MSG_W_HWC01 	"WHWC501"
#define MSG_I_HWC01 	"IHWC501"
#define MSG_C_HWC02 	"CHWC502"		/* MEMORY Physical size */
#define MSG_W_HWC02 	"WHWC502"		
#define MSG_I_HWC02 	"IHWC502"
#define MSG_F_HWC03 	"FHWC503"		/* Server board celsius */
#define MSG_C_HWC03 	"CHWC503"		/* Server board celsius */
#define MSG_W_HWC03 	"WHWC503"
#define MSG_I_HWC03 	"IHWC503"
/* O/S Information */
#define MSG_P_OSI02		"POSI502"		/* CPU Count 전송 */
#define MSG_P_SYS01		"PSYS501"       /* os info */
#define MSG_P_SYS02		"PSYS502"       /* cpu info */
#define MSG_P_SYS03		"PSYS503"       /* mem info */
#define MSG_P_SYS04		"PSYS504"       /* ip address info */
#define MSG_P_SYS06		"PSYS506"       /* uptime */
#define MSG_P_SYS09		"PSYS509"       /* s2o license */
#define MSG_I_NET01		"INET501"       /* Session Established Connection */
#define MSG_F_NET01		"FNET501"       /* Session Established Connection */
#define MSG_C_NET01		"CNET501"       /* Session Established Connection */
#define MSG_W_NET01		"WNET501"       /* Session Established Connection */
#define MSG_I_NET02		"INET502"       /* Session Non-Established Connection */
#define MSG_F_NET02		"FNET502"       /* Session Non-Established Connection */
#define MSG_C_NET02		"CNET502"       /* Session Non-Established Connection */
#define MSG_W_NET02		"WNET502"       /* Session Non-Established Connection */
#define MSG_F_NET03		"FNET503"       /* protocol port check fatal */
#define MSG_C_NET03		"CNET503"       /* protocol port check critical */
#define MSG_W_NET03		"WNET503"       /* protocol port check warning */
#define MSG_I_NET03		"INET503"       /* protocol port check information */
#define MSG_P_NET03		"PNET503"       /* protocol port check capa save data */
#define MSG_C_SEC01		"CSEC501"       /* 무결성 파일 not found */
#define MSG_C_SEC02		"CSEC502"       
#define MSG_C_SEC11		"CSEC511"       /* 무결성 파일 not found */
#define MSG_C_SEC12		"CSEC512"       
#define MSG_I_SEC02		"ISEC502"       
#define MSG_P_NIC10		"PNIC510"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC511"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC511"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC511"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC511"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC512"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC512"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS17		"CSYS517"       /* omreport(del서버-linux) */
#define MSG_C_BOT01		"CBOT511"		/* booting 시간 변경 알림 */
#define MSG_W_BOT01		"WBOT511"		/* booting 시간 변경 알림 */
#define MSG_C_ACC11     "CACC511"		/* OS 계정 만료 */
#define MSG_W_ACC11     "WACC511"		/* OS 계정 만료 */
#define MSG_I_ACC11     "IACC511"		/* OS 계정 만료 */
#define MSG_P_ACC11     "PACC511"		/* OS 계정 만료 */
#elif defined(DGUX)					/* --------------------------------------------- */
#define MSG_P_SWP00 	"PSWP700"
#define MSG_P_SWP10     "PSWP710"
#define MSG_P_SWP01 	"PSWP701"
#define MSG_P_SWP11     "PSWP711"
#define MSG_I_SWP11     "ISWP711"
#define MSG_W_SWP11     "WSWP711"
#define MSG_F_SWP11     "FSWP711"
#define MSG_C_SWP11     "CSWP711"
#define MSG_I_SWP12 	"ISWP712"
#define MSG_I_SWP13 	"ISWP713"		/* Swap 사용률 */
#define MSG_W_SWP12 	"WSWP712"
#define MSG_C_SWP12 	"CSWP712"
#define MSG_F_SWP12 	"FSWP712"
#define MSG_C_SWP14 	"CSWP714"		/* AIX Swap device(LV) open error */

#define MSG_P_TOP05     "PTOP705"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP706"       /* 설정된 프로세스 정보 저장 */
#define MSG_P_TOP07     "PTOP707"       /* mem Top 10 */
#define MSG_P_PRS00 	"PPRS700"
#define MSG_P_PRS10 	"PPRS710"
#define MSG_I_PRS11 	"IPRS711"
#define MSG_C_PRS11 	"CPRS711"
#define MSG_I_PRS12 	"IPRS712"
#define MSG_F_PRS12 	"FPRS712"
#define MSG_C_PRS12 	"CPRS712"
#define MSG_C_PRS13 	"CPRS713"		
#define MSG_I_PRS14 	"IPRS714"		/* thread수 모니터링 */
#define MSG_C_PRS14 	"CPRS714"		/* thread수 모니터링 */	
#define MSG_F_PRS14 	"FPRS714"		/* thread수 모니터링 */	
#define MSG_I_PCU11 	"IPCU711"		/* process cpu usage check */
#define MSG_W_PCU11 	"WPCU711"
#define MSG_C_PCU11 	"CPCU711"
#define MSG_F_PCU11 	"FPCU711"
#define MSG_P_PCU11 	"PPCU711"
#define MSG_I_PCU12 	"IPCU712"		/* process memory check */
#define MSG_C_PCU12 	"CPCU712"
#define MSG_I_PCU13 	"IPCU713"		/* process owner check */
#define MSG_C_PCU13 	"CPCU713"
#define MSG_I_PCU14 	"IPCU714"		/* auto action command fail */
#define MSG_C_PCU14 	"CPCU714"		/* auto action command fail */
#define MSG_P_DSK00 	"PDSK700"
#define MSG_P_DSK10     "PDSK710"
#define MSG_I_DSK11     "IDSK711"
#define MSG_W_DSK11     "WDSK711"
#define MSG_C_DSK11     "CDSK711"
#define MSG_F_DSK11     "FDSK711"
#define MSG_C_DSK12     "CDSK712"		/* filesystem not fount */
#define MSG_W_DSK12     "WDSK712"		/* filesystem not fount */
#define MSG_C_DSK13     "CDSK713"		/* filesystem operation check */
#define MSG_C_DSK14     "CDSK714"		/* 파일시스템 설정 관련 */
#define MSG_C_DSK15     "CDSK715"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK716"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_W_DSK16     "WDSK716"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_I_DSK17     "IDSK717"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK717"
#define MSG_C_DSK17     "CDSK717"
#define MSG_P_DSI00 	"PDSI700"		/* Inodes 관련 Messaged Code */
#define MSG_P_DSI10     "PDSI710"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI711"
#define MSG_W_DSI11     "WDSI711"
#define MSG_C_DSI11     "CDSI711"
#define MSG_F_DSI11     "FDSI711"
#define MSG_C_DSI12     "CDSI712"
#define MSG_C_DSI14     "CDSI714"		/* Inodes 설정 파일  관련 message code */
#define MSG_W_DSI16     "WDSI716"		/* inodes check가 정상적으로 진행되지 않을 경우 */
/* H/W */
#define MSG_P_HWC00 	"PHWC700"		/* 서버 Board별 Temperature */
#define MSG_C_HWC01 	"CHWC701"		/* CPU online number */
#define MSG_W_HWC01 	"WHWC701"
#define MSG_I_HWC01 	"IHWC701"
#define MSG_C_HWC02 	"CHWC702"		/* MEMORY Physical size */
#define MSG_W_HWC02 	"WHWC702"		
#define MSG_I_HWC02 	"IHWC702"
#define MSG_F_HWC03 	"FHWC703"		/* Server board celsius */
#define MSG_C_HWC03 	"CHWC703"		/* Server board celsius */
#define MSG_W_HWC03 	"WHWC703"
#define MSG_I_HWC03 	"IHWC703"
/* O/S Information */
#define MSG_P_OSI02		"POSI702"		/* CPU Count 전송 */
#define MSG_P_SYS01		"PSYS701"       /* os info */
#define MSG_P_SYS02		"PSYS702"       /* cpu info */
#define MSG_P_SYS03		"PSYS703"       /* mem info */
#define MSG_P_SYS04		"PSYS704"       /* ip address info */
#define MSG_P_SYS06		"PSYS706"       /* uptime */
#define MSG_P_SYS09		"PSYS709"       /* s2o license */
#define MSG_I_NET01		"INET701"       /* Session Established Connection */
#define MSG_F_NET01		"FNET701"       /* Session Established Connection */
#define MSG_C_NET01		"CNET701"       /* Session Established Connection */
#define MSG_W_NET01		"WNET701"       /* Session Established Connection */
#define MSG_I_NET02		"INET702"       /* Session Non-Established Connection */
#define MSG_F_NET02		"FNET702"       /* Session Non-Established Connection */
#define MSG_C_NET02		"CNET702"       /* Session Non-Established Connection */
#define MSG_W_NET02		"WNET702"       /* Session Non-Established Connection */
#define MSG_F_NET03		"FNET703"       /* protocol port check fatal */
#define MSG_C_NET03		"CNET703"       /* protocol port check critical */
#define MSG_W_NET03		"WNET703"       /* protocol port check warning */
#define MSG_I_NET03		"INET703"       /* protocol port check information */
#define MSG_P_NET03		"PNET703"       /* protocol port check capa save data */
#define MSG_C_SEC01		"CSEC701"       /* 무결성 파일 not found */
#define MSG_C_SEC02		"CSEC702"       
#define MSG_C_SEC11		"CSEC711"       /* 무결성 파일 not found */
#define MSG_C_SEC12		"CSEC712"       
#define MSG_I_SEC02		"ISEC702" 
#define MSG_P_NIC10		"PNIC710"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC711"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC711"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC711"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC711"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC712"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC712"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS17		"CSYS717"       /* omreport(del서버-linux) */
#define MSG_C_BOT01		"CBOT711"		/* booting 시간 변경 알림 */
#define MSG_W_BOT01		"WBOT711"		/* booting 시간 변경 알림 */
#define MSG_C_ACC11     "CACC711"		/* OS 계정 만료 */
#define MSG_W_ACC11     "WACC711"		/* OS 계정 만료 */
#define MSG_I_ACC11     "IACC711"		/* OS 계정 만료 */
#define MSG_P_ACC11     "PACC711"		/* OS 계정 만료 */
#else		/* SUN2 */				/* ---------------------------------------------- */
#define MSG_P_SWP00 	"PSWP200"
#define MSG_P_SWP10     "PSWP210"
#define MSG_P_SWP01 	"PSWP201"
#define MSG_P_SWP11     "PSWP211"
#define MSG_I_SWP11     "ISWP211"
#define MSG_W_SWP11     "WSWP211"
#define MSG_F_SWP11     "FSWP211"
#define MSG_C_SWP11     "CSWP211"
#define MSG_I_SWP12 	"ISWP212"
#define MSG_W_SWP12 	"WSWP212"
#define MSG_W_SWP12 	"WSWP212"
#define MSG_C_SWP12 	"CSWP212"
#define MSG_F_SWP12 	"FSWP212"
#define MSG_I_SWP13     "ISWP213"       /* Swap 사용률 */
#define MSG_C_SWP14 	"CSWP214"		/* AIX Swap device(LV) open error */

#define MSG_P_TOP05     "PTOP205"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP206"       /* 설정된 프로세스 정보 저장 */
#define MSG_P_TOP07     "PTOP207"       /* top Top 10 */
#define MSG_P_PRS00 	"PPRS200"		/* USE_PORT = 'N' 일 경우 */
#define MSG_P_PRS10 	"PPRS210"
#define MSG_I_PRS11 	"IPRS211"
#define MSG_C_PRS11 	"CPRS211"
#define MSG_I_PRS12 	"IPRS212"
#define MSG_F_PRS12 	"FPRS212"
#define MSG_C_PRS12 	"CPRS212"
#define MSG_C_PRS13 	"CPRS213"
#define MSG_I_PRS14 	"IPRS214"		/* thread수 모니터링 */
#define MSG_C_PRS14 	"CPRS214"		/* thread수 모니터링 */	
#define MSG_F_PRS14 	"FPRS214"		/* thread수 모니터링 */	
#define MSG_I_PCU11 	"IPCU211"		/* process cpu usage check */
#define MSG_W_PCU11 	"WPCU211"
#define MSG_C_PCU11 	"CPCU211"
#define MSG_F_PCU11 	"FPCU211"
#define MSG_P_PCU11 	"PPCU211"
#define MSG_I_PCU12 	"IPCU212"		/* process memory check */
#define MSG_C_PCU12 	"CPCU212"
#define MSG_I_PCU13 	"IPCU213"		/* process owner check */
#define MSG_C_PCU13 	"CPCU213"
#define MSG_I_PCU14 	"IPCU214"		/* auto action command fail */
#define MSG_C_PCU14 	"CPCU214"		/* auto action command fail */
#define MSG_P_DSK00 	"PDSK200"
#define MSG_P_DSK10     "PDSK210"
#define MSG_I_DSK11     "IDSK211"
#define MSG_W_DSK11     "WDSK211"
#define MSG_C_DSK11     "CDSK211"
#define MSG_F_DSK11     "FDSK211"
#define MSG_C_DSK12     "CDSK212"		/* filesystem not fount */
#define MSG_W_DSK12     "WDSK212"		/* filesystem not fount */
#define MSG_C_DSK13     "CDSK213"		/* filesystem operation check */
#define MSG_C_DSK14     "CDSK214"		/* 파일시스템 설정관련 */
#define MSG_C_DSK15     "CDSK215"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK216"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_W_DSK16     "WDSK216"		/* disk check가 정상적으로 진행되지 않을 경우 (df -k 처리시 hang 발생) */
#define MSG_I_DSK17     "IDSK217"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK217"
#define MSG_C_DSK17     "CDSK217"
#define MSG_P_DSI00 	"PDSI200"		/* Inodes 관련 Messaged Code */
#define MSG_P_DSI10     "PDSI210"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI211"
#define MSG_W_DSI11     "WDSI211"
#define MSG_C_DSI11     "CDSI211"
#define MSG_F_DSI11     "FDSI211"
#define MSG_C_DSI12     "CDSI212"
#define MSG_C_DSI14     "CDSI214"		/* Inodes 설정 파일  관련 message code */
#define MSG_W_DSI16     "WDSI216"		/* inodes check가 정상적으로 진행되지 않을 경우 */
/* H/W */
#define MSG_P_HWC00 	"PHWC200"		/* 서버 Board별 Temperature */
#define MSG_P_HWC05 	"PHWC205"		/* Sun Enterprise 2.5.1 */
#define MSG_C_HWC01 	"CHWC201"		/* CPU online number */
#define MSG_W_HWC01 	"WHWC201"
#define MSG_I_HWC01 	"IHWC201"
#define MSG_C_HWC02 	"CHWC202"		/* MEMORY Physical size */
#define MSG_W_HWC02 	"WHWC202"		
#define MSG_I_HWC02 	"IHWC202"
#define MSG_F_HWC03 	"FHWC203"		/* Server board celsius */
#define MSG_C_HWC03 	"CHWC203"		/* Server board celsius */
#define MSG_W_HWC03 	"WHWC203"
#define MSG_I_HWC03 	"IHWC203"
/* O/S Information */
#define MSG_P_OSI02		"POSI202"		/* CPU Count 전송 */
#define MSG_P_SYS01		"PSYS201"       /* os info */
#define MSG_P_SYS02		"PSYS202"       /* cpu info */
#define MSG_P_SYS03		"PSYS203"       /* mem info */
#define MSG_P_SYS04		"PSYS204"       /* ip address info */
#define MSG_P_SYS06		"PSYS206"       /* uptime */
#define MSG_P_SYS09		"PSYS209"       /* s2o license */
#define MSG_I_NET01		"INET201"       /* Session Established Connection */
#define MSG_F_NET01		"FNET201"       /* Session Established Connection */
#define MSG_C_NET01		"CNET201"       /* Session Established Connection */
#define MSG_W_NET01		"WNET201"       /* Session Established Connection */
#define MSG_I_NET02		"INET202"       /* Session Non-Established Connection */
#define MSG_F_NET02		"FNET202"       /* Session Non-Established Connection */
#define MSG_C_NET02		"CNET202"       /* Session Non-Established Connection */
#define MSG_W_NET02		"WNET202"       /* Session Non-Established Connection */
#define MSG_F_NET03		"FNET203"       /* protocol port check fatal */
#define MSG_C_NET03		"CNET203"       /* protocol port check critical */
#define MSG_W_NET03		"WNET203"       /* protocol port check warning */
#define MSG_I_NET03		"INET203"       /* protocol port check information */
#define MSG_P_NET03		"PNET203"       /* protocol port check capa save data */
#define MSG_C_SEC01		"CSEC201"       /* 무결성 파일 not found */
#define MSG_C_SEC02		"CSEC202"       
#define MSG_C_SEC11		"CSEC211"       /* 무결성 파일 not found */
#define MSG_C_SEC12		"CSEC212"       
#define MSG_I_SEC02		"ISEC202" 
#define MSG_P_NIC10		"PNIC210"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC211"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC211"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC211"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC211"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC212"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC212"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS17		"CSYS217"       /* omreport(del서버-linux) */
#define MSG_C_BOT01		"CBOT211"		/* booting 시간 변경 알림 */
#define MSG_W_BOT01		"WBOT211"		/* booting 시간 변경 알림 */
#define MSG_C_ACC11     "CACC211"		/* OS 계정 만료 */
#define MSG_W_ACC11     "WACC211"		/* OS 계정 만료 */
#define MSG_I_ACC11     "IACC211"		/* OS 계정 만료 */
#define MSG_P_ACC11     "PACC211"		/* OS 계정 만료 */

#endif

#if defined(ENGLISH)
#define STR_C_PCU11_0 "Process(%s,%d) CPU utilization(%4.2f%%) and CPU usage time(%dMin) reached the critical(set:CPU utilization(%d%%), CPU usage time(%dMin))"
#define STR_C_PCU11_1 "Process(%s,%d) CPU utilization(%4.2f%%) and CPU usage time(%dMin) reached the critical(set:CPU utilization(%4.2f%%), CPU usage time(%dMin))"
#define STR_I_PCU11_1 "Each process CPU utilization and CPU usage time check is normal"
#define STR_F_PCU11_2 "Process(%s,%d) MEMORY usage(%dKB) reached the fatal(set:%dKB)"
#define STR_C_PCU11_2 "Process(%s,%d) MEMORY usage(%dKB) reached the critical(set:%dKB)"
#define STR_W_PCU11_2 "Process(%s,%d) MEMORY usage(%dKB) reached the warning(set:%dKB)"
#define STR_C_PCU11_3 "Process(%s,%d) Owner(%s) is not same(set:%s)"
#define STR_C_PCU11_4 "Process(%s,%d) auto action command(%s) failed"
#define STR_I_PCU11_4 "Process(%s,%d) auto action command(%s) execute"
#define STR_F_DSK11_1 "File system(%s) free space reached the fatal(used:%d%%, free:%.fKBytes)"
#define STR_F_DSK11_1_1 "File system(%s) free space reached the fatal(used:%d%%, free:%.fKBytes, %s)"
#define STR_C_DSK11_1 "File system(%s) free space reached the critical(used:%d%%, free:%.fKBytes)"
#define STR_C_DSK11_1_1 "File system(%s) free space reached the critical(used:%d%%, free:%.fKBytes, %s)"
#define STR_W_DSK11_1 "File system(%s) free space reached the warning(used:%d%%, free:%.fKBytes)"
#define STR_W_DSK11_1_1 "File system(%s) free space reached the warning(used:%d%%, free:%.fKBytes, %s)"
#define STR_I_DSK11_1 "File system check is normal"
#define STR_C_DSK11_2 "The rate of change of File system(%s) free space reached the critical(old used:%d%%, used:%d%%, set:%d%%)"
#define STR_C_DSK11_2_1 "The rate of change of File system(%s) free space reached the critical(old used:%d%%, used:%d%%, set:%d%%, %s)"
#define STR_C_DSK11_3 "The rate of change of File system(%s) free space reached the critical(old used:%d%%, used:%d%%, set:%d%%)"
#define STR_C_DSK11_3_1 "The rate of change of File system(%s) free space reached the critical(old used:%d%%, used:%d%%, set:%d%%, %s)"
#define STR_C_DSK11_4 "The amount of change of File system(%s) free space reached the critical(old free:%.fKBytes, free:%.fKBytes, set:%dKbytes)"
#define STR_C_DSK11_4_1 "The amount of change of File system(%s) free space reached the critical(old free:%.fKBytes, free:%.fKBytes, set:%dKbytes, %s)"
#define STR_C_DSK11_5 "The amount of change of File system(%s) free space reached the critical(old free:%.fKBytes, free:%.fKBytes, set:%dKbytes)"
#define STR_C_DSK11_5_1 "The amount of change of File system(%s) free space reached the critical(old free:%.fKBytes, free:%.fKBytes, set:%dKbytes, %s)"
#define STR_C_DSK12_1 "File system(%s) is not mounted"
#define STR_C_DSK12_1_1 "File system(%s) is not mounted(%s)"
#define STR_C_DSK12_1_2 "The filesystem(%s,%s) under automatic monitoring does not exist on the server.(Elapsed deletion time=%dmin)"
#define STR_W_DSK12_1 "Failed to execute AUTO Action set in file system(%s). (%s)"
#define STR_W_DSK12_2 "AUTO Action set in the file system(%s) was executed. (%s)"
#define STR_C_DSK13_1 "File system(%s) temporary file read/write fail"
#define STR_C_DSK13_1_1 "File system(%s) temporary file read/write fail(%s)"
#define STR_C_DSK14_1 "File system configuration file is not found"
#define STR_C_DSK14_2 "File system configuration file is not correct"
#define STR_C_DSK14_3 "File system configuration file size 0"
#define STR_C_DSK15_1 "File system(%s) current LV Status is closed/syncd. Please check logical volume status."
#define STR_W_DSK16 "Monitoring of File system is fail. (confirm '%s')"
/*#define STR_W_DSK16_1 "FileSystem Monitoring Failure. (confirm 'df -k')"*/
/*#define STR_W_DSK16_2 "FileSystem Monitoring Failure. So, change the command. ('%s' -> '%s')"*/
#define STR_W_DSK16_3 "No file system collection results. (confirm '%s')"
#define STR_W_DSK16_4 "Filesystem monitoring is not performed because the command to check the number of filesystem commands failed. (ps -ef|grep '%s'|wc -l)"
#define STR_W_DSK16_5 "FileSystem Monitoring is not performed because %d filesystem commands exist. (%s)"
#define STR_W_DSK16_6 "No filesystem information is provided because the command to check the number of filesystem commands failed.  (ps -ef|grep '%s'|wc -l)"
#define STR_W_DSK16_7 "No filesystem information is provided because %d filesystem commands exist. (%s)"
#define STR_C_DSK17_2 "Can not collect Storage Node data. Check the result of the command(%s)."
#define STR_C_DSK17_1 "Storage Node(%s) free space reached the critical. ( Free:%dGB (%s))"
#define STR_W_DSK17_1 "Storage Node(%s) free space reached the warning. ( Free:%dGB (%s)) "
#define STR_I_DSK17 "Storage Node check is normal"
#define STR_F_DSI11_1 "File system(%s) inodes reached the fatal(set:%d%%, used:%d%%)"
#define STR_C_DSI11_1 "File system(%s) inodes reached the critical(set:%d%%, used:%d%%)"
#define STR_W_DSI11_1 "File system(%s) inodes reached the warning(set:%d%%, used:%d%%)"
#define STR_I_DSI11_1 "File system inodes check is normal"
#define STR_C_DSI12_1 "File system(%s) inodes is not mounted"
#define STR_C_DSI14_1 "Inodes configuration file is not found"
#define STR_C_DSI14_2 "Inodes configuration file is not correct"
#define STR_C_DSI14_3 "Inodes configuration file size 0"
#define STR_W_DSI16_1 "Monitoring file system inodes failed. (confirm '%s')"
#define STR_W_DSI16_2 "No file system inodes collection results."
#define STR_W_DSI16_3 "INODE monitoring is not performed because the command to check the number of INODE commands failed. (ps -ef|grep '%s'|wc -l)"
#define STR_W_DSI16_4 "INODE Monitoring is not performed because %d INODE commands exist.(%s)"
#define STR_W_DSI16_5 "No INODE information is provided because the command to check the number of INODE commands failed. (ps -ef|grep '%s'|wc -l)"
#define STR_W_DSI16_6 "No INODE information is provided because %d INODE commands exist.(%s)"
#define STR_C_PRS11_1 "Process is down(%s)"
#define STR_C_PRS11_1_1 "%s Process is down(%s)"
#define STR_C_PRS11_1_2 "There is no process running the same as the owner of the monitoring setting. ( %s,  %s )"
#define STR_C_PRS11_1_3 "There is no %s process running with the monitoring setting owner. ( %s,  %s )"
#define STR_I_PRS11_1 "Process has returned to normal(%s)"
#define STR_I_PRS11_1_1 "%s Process has returned to normal(%s)"
#define STR_C_PRS11_2 "Process auto restart failed(%s)"
#define STR_C_PRS11_2_1 "%s Process auto restart failed(%s)"
#define STR_I_PRS11_2 "Process auto restarted(%s)"
#define STR_I_PRS11_2_1 "%s Process auto restarted(%s)"
#define STR_C_PRS11_3_1 "%s Process daemon count is less than set value(%s, set:%d, now:%d)" 
#define STR_C_PRS11_3_1_1 "%s Process daemon count is less than set value(%s, set:%d, now:%d, process:%s)" 
#define STR_C_PRS11_3_2 "Process daemon count is less than set value(%s, set:%d, now:%d)" 
#define STR_C_PRS11_3_2_1 "Process daemon count is less than set value(%s, set:%d, now:%d, process:%s)" 
#define STR_C_PRS11_4 "Process daemon count is more than set value(%s, set:%d, now:%d)"
#define STR_C_PRS11_4_1 "%s Process daemon count is more than set value(%s, set:%d, now:%d)"
#define STR_I_PRS11_5 "All of the specified processes are running(set:%d, total:%d)"
#define STR_I_PRS11_6 "Process is not running, but it is normal.(%s)"
#define STR_I_PRS11_6_1 "%s Process is not running, but it is normal.(%s)"

#define STR_W_PRS11_7_1	"The Process(%s) changed status of clustering. (IP = %s, status = %s)"
#define STR_W_PRS11_7_2	"Process(%s) cluster failed. Failed to collect Ip Address information"
#define STR_W_PRS11_7_3	"%s Process(%s) cluster failed. Failed to collect Ip Address information"

#define STR_F_PRS12_1 "Number of total process is fatal(set:%d, now:%d)"
#define STR_C_PRS12_1 "Number of total process is critical(set:%d, now:%d)"
#define STR_I_PRS12_1 "Number of total process is normal(set:%d, now:%d)"
#define STR_I_PRS12_2 "Number of total process is normal(set:%d, now:%d)"
#define STR_C_PRS13_1 "Process configuration file is not found"
#define STR_C_PRS13_2 "Process configuration file is not correct"
#define STR_C_PRS13_3 "Process configuration file size 0"
#define STR_C_PRS13_4 "Reduced processes registered for monitoring. (%d -> %d)"
#define STR_C_PRS13_5 "No processes registered for monitoring."
#define STR_F_PRS14_1 "The total number of threads in the process is fatal(set:%d, now:%d)"
#define STR_C_PRS14_1 "The total number of threads in the process is critical(set:%d, now:%d)"
#define STR_I_PRS14_1 "The total number of threads in the process is normal(now:%d)"

#define STR_F_SWP11_1 "Free swap space reached the fatal(set:%dKBytes, now:%.fKBytes)"
#define STR_F_SWP11_2 "Free swap space reached the fatal for %d minute(s).(set:%dKBytes, now:%.fKBytes)"
#define STR_C_SWP11_1 "Free swap space reached the critical(set:%dKBytes, now:%.fKBytes)"
#define STR_C_SWP11_2 "Free swap space reached the critical for %d minute(s).(set:%dKBytes, now:%.fKBytes)"
#define STR_W_SWP11_1 "Free swap space reached the warning(set:%dKBytes, now:%.fKBytes)"
#define STR_W_SWP11_2 "Free swap space reached the warning for %d minute(s).(set:%dKBytes, now:%.fKBytes)"
#define STR_I_SWP11_1 "Free swap space is normal(now:%.fKBytes)"
#define STR_F_SWP12	"SWAP utilization reached the fatal(set:%d%%, now:%3.2f%%)"
#define STR_F_SWP12_2	"SWAP utilization reached the fatal for %d minute(s).(set:%d%%, now:%3.2f%%)"
#define STR_C_SWP12	"SWAP utilization reached the critical(set:%d%%, now:%3.2f%%)"
#define STR_C_SWP12_2	"SWAP utilization reached the critical for %d minute(s).(set:%d%%, now:%3.2f%%)"
#define STR_W_SWP12	"SWAP utilization reached the warning(set:%d%%, now:%3.2f%%)"
#define STR_W_SWP12_2	"SWAP utilization reached the warning for %d minute(s).(set:%d%%, now:%3.2f%%)"
#define STR_I_SWP12	"SWAP utilization went down under the normal(now:%3.2f%%)"
#define STR_I_SWP12_1	"SWAP utilization is normal(now:%3.2f%%)"

#define STR_C_SWP14	"SWAP Paging Space volume information open error. Please check Logical Volume status"
#define STR_I_NET01_1 "Session Established Connection count is normal.(now:%d)"
#define STR_F_NET01_1 "Session Established Connection count is fatal(set:%d, now:%d)"
#define STR_C_NET01_1 "Session Established Connection count is critical(set:%d, now:%d)"
#define STR_W_NET01_1 "Session Established Connection count is warning(set:%d, now:%d)"
#define STR_I_NET02_1 "Session Non-Established Connection count is normal.(now:%d)"
#define STR_F_NET02_1 "Session Non-Established Connection count is fatal(set:%d, now:%d)"
#define STR_C_NET02_1 "Session Non-Established Connection count is critical(set:%d, now:%d)"
#define STR_W_NET02_1 "Session Non-Established Connection count is warning(set:%d, now:%d)"
#define STR_F_NET03_1 "Number of established port(%s) sessions is fatal(set:%d, now:%d)"
#define STR_C_NET03_1 "Number of established port(%s) sessions is critical(set:%d, now:%d)"
#define STR_W_NET03_1 "Number of established port(%s) sessions is warning(set:%d, now:%d)"
#define STR_I_NET03_1 "Number of established port sessions socket is normal"
#define STR_I_NET03_2 "Number of established port sessions is normal"

/* NIC Traffic */
#define STR_F_NIC11_1 "Server's IN PACKETS per second reached fatal.(set:%dpackets, now:%.1fpackets)"
#define STR_C_NIC11_1 "Server's IN PACKETS per second reached critical.(set:%dpackets, now:%.1fpackets)"
#define STR_W_NIC11_1 "Server's IN PACKETS per second reached warning.(set:%dpackets, now:%.1fpackets)"
#define STR_F_NIC11_2 "Server's OUT PACKETS per second reached fatal.(set:%dpackets, now:%.1fpackets)"
#define STR_C_NIC11_2 "Server's OUT PACKETS per second reached critical.(set:%dpackets, now:%.1fpackets)"
#define STR_W_NIC11_2 "Server's OUT PACKETS per second reached warning.(set:%dpackets, now:%.1fpackets)"
#define STR_F_NIC11_3 "Server's IN BYTES per second reached fatal.(set:%dKbps, now:%.1fKbps)"
#define STR_C_NIC11_3 "Server's IN BYTES per second reached critical.(set:%dKbps, now:%.1fKbps)"
#define STR_W_NIC11_3 "Server's IN BYTES per second reached warning.(set:%dKbps, now:%.1fKbps)"
#define STR_F_NIC11_4 "Server's OUT BYTES per second reached fatal.(set:%dKbps, now:%.1fKbps)"
#define STR_C_NIC11_4 "Server's OUT BYTES per second reached critical.(set:%dKbps, now:%.1fKbps)"
#define STR_W_NIC11_4 "Server's OUT BYTES per second reached warning.(set:%dKbps, now:%.1fKbps)"
#define STR_I_NIC11_1 "Server's traffic per second is normal. IN(%.1fpackets, %.1fKbps), OUT(%.1fpackets, %.1fKbps)"
#define STR_I_NIC11_2 "Server's traffic per second is normal. IN(%.1fpackets), OUT(%.1fpackets)"
#define STR_C_NIC12_1 "Failed to perform AUTO ACTION COMMAND(%s) for server's Nic Traffic usage."
#define STR_I_NIC12_1 "AUTO ACTION COMMAND(%s) was performed on the server's Nic Traffic usage."

#define STR_C_HWC01_1 "Number of online CPU is not corrected. (Logical<set:%dEa, now:%dEa>)"
#define STR_C_HWC01_1_2 "Number of online CPU is not corrected. (Logical<set:%dEa, now:%dEa>, Physical:%dEa)"
#define STR_C_HWC01_1_3_2 "Reduced number of online CPU on the server. (Logical<set:%dEa, now:%dEa>, Physical:%dEa)"
#define STR_C_HWC01_1_3_2_1 "Reduced number of online CPU on the server. (Logical<set:%d~%dEa, now:%dEa>, Physical:%dEa)"
#define STR_C_HWC01_1_3_1 "Reduced number of online CPU on the server. (Logical<set:%dEa, now:%dEa>)"
#define STR_C_HWC01_1_3_1_1 "Reduced number of online CPU on the server. (Logical<set:%d~%dEa, now:%dEa>)"
#define STR_W_HWC01_1_4_2 "Increased the number of online CPU on the server. (Logical<set:%dEa, now:%dEa>, Physical:%dEa). The monitoring setting value changes automatically."
#define STR_W_HWC01_1_4_2_1 "Increased the number of online CPU on the server. (Logical<set:%d~%dEa, now:%dEa>, Physical:%dEa). The monitoring setting value changes automatically."
#define STR_W_HWC01_1_4_1 "Increased the number of online CPU on the server. (Logical<set:%dEa, now:%dEa>), The monitoring setting value changes automatically."
#define STR_W_HWC01_1_4_1_1 "Increased the number of online CPU on the server. (Logical<set:%d~%dEa, now:%dEa>), The monitoring setting value changes automatically."
#define STR_W_HWC01_1_5 "Monitoring of the number of online CPU has failed. (confirm '%s')"
#define STR_I_HWC01_1 "Current H/W status is normal. (PROCESSOR<Logical):%dEa, MEMORY:%dMBytes, board temperature: %d Cels)"
#define STR_I_HWC01_1_2 "Current H/W status is normal. (PROCESSOR<Logical/Physical>:%dEa/%dEa, MEMORY:%dMBytes, board temperature: %d Cels)"
#define STR_I_HWC01_2 "Current H/W status is normal. (PROCESSOR<Logical>:%dEa, MEMORY:%dMBytes)"
#define STR_I_HWC01_2_2 "Current H/W status is normal. (PROCESSOR<Logical/Physical>:%dEa/%dEa, MEMORY:%dMBytes)"
/*#define STR_C_HWC02_1 "Size of physical MEMORY is not corrected(set:%d, now:%d)"*/
#define STR_C_HWC02_1_1 "Reduced size of physical MEMORY on the server.(set:%dMBytes, now:%dMBytes)."
#define STR_C_HWC02_1_2 "Reduced size of physical MEMORY on the server.(set:%d~%dMBytes, now:%dMBytes)."
#define STR_W_HWC02_1_3 "Increased size of physical MEMORY on the server (set:%dMBytes, now:%dMBytes). The monitoring setting value changes automatically."
#define STR_W_HWC02_1_4 "Increased size of physical MEMORY on the server (set:%d~%dMBytes, now:%dMBytes). The monitoring setting value changes automatically."
#define STR_F_HWC03_1 "Temperature of server board is fatal(set:%d Cels, current:%d Cels)"
#define STR_C_HWC03_1 "Temperature of server board is critical(set:%d Cels, current:%d Cels)"
#define STR_W_HWC03_1 "Temperature of server board is warning(set:%d Cels, current:%d Cels)"
#define STR_C_SEC01_1 "Integrity watchdog target set file/directory(%s) does not exist"
#define STR_C_SEC11_1 "Integrity watchdog command target set file/directory(%s) does not exist"
#define STR_C_SEC02_1 "Integrity check file(%s) size is modified(set:%s Bytes, current:%s Bytes)"
#define STR_C_SEC02_1_1 "Integrity check directory(%s) size is modified(set:%s Kbytes, current:%s Kbytes)"
#define STR_C_SEC02_2 "Integrity check file(%s) owner is modified(set:%s, current:%s)"
#define STR_C_SEC02_2_1 "Integrity check directory(%s) owner is modified(set:%s, current:%s)"
#define STR_C_SEC02_3 "Integrity check file(%s) group is modified(set:%s, current:%s)"
#define STR_C_SEC02_3_1 "Integrity check directory(%s) group is modified(set:%s, current:%s)"
#define STR_C_SEC02_4 "Integrity check file(%s) mode is modified(set:%s, current:%s)"
#define STR_C_SEC02_4_1 "Integrity check directory(%s) mode is modified(set:%s, current:%s)"
#define STR_C_SEC02_5 "Integrity check file(%s) last modified date is modified(set:%s, current:%s)"
#define STR_C_SEC02_5_1 "Integrity check directory(%s) last modified date is modified(set:%s, current:%s)"
#define STR_C_SEC02_6 "The size of the set file(%s) is greater than the maximum setting. (set:%s Bytes, current:%s Bytes)"
#define STR_C_SEC02_6_1 "The size of the set directory(%s) is greater than the maximum setting. (set:%s Kbytes, current:%s Kbytes)"
#define STR_C_SEC02_6_2 "The size of the set file(%s) is less than the minimum setting. (set:%s Bytes, current:%s Bytes)"
#define STR_C_SEC02_6_3 "The size of the set directory(%s) is less than the minimum setting. (set:%s Kbytes, current:%s Kbytes)"
/*#define STR_C_SEC02_6 "Integrity check file(%s) size reached the critcal(set:%d Bytes, current:%d Bytes)"*/
/*#define STR_C_SEC02_6_1 "Integrity check directory(%s) size reached the critcal(set:%d Kbytes, current:%d Kbytes)"*/
#define STR_C_SEC02_7_1 "File count of Integrity check directory(%s) reached the critcal(set:%d count, current:%ld count)"
#define STR_I_SEC02_1 "Integrity check file status is normal(set:%d)"
#define STR_C_TEP11_1	"The temperature status of the peripheral devices (CPU% d Temp) is %s. (Probe Name=%s)"
#define STR_C_TEP11_2	"The temperature of the peripheral devices (CPU %d Temp) on the server is currently %.1fCels dangerous. (Probe Name=%s)"
#define STR_W_TEP11		"The temperature of the peripheral devices (CPU %d Temp) on the server is currently %.1fCels for warning level. (Probe Name=%s)"
#define STR_I_TEP11		"The temperature of the peripheral devices on the server is normal."

#define STR_C_BOT01		"The server's last boot time is %s. ( Based on '%s' command )"

/*#define STR_C_ACC11_1	"Password expiration date for OS account %s is %d days %.1f hours left"*/
/*#define STR_C_ACC11_2	"Password expiration date for OS account %s has passed %d days %.1f hours."*/
/*#define STR_W_ACC11		"Password expiration date for OS account %s is %d days %.1f hours left (Warning)" */

#define STR_C_ACC11_1	"%s_Password_will_be_expired_@%s"
#define STR_C_ACC11_2	"%s_Password_has_expired_@%s"
#define STR_W_ACC11		"%s_Password_will_be_expired_@%s"
#define STR_I_ACC11		"Password expiration date for all accounts in the OS is normal. (target=%d, active=%d, total=%d), (warn=%dday, crit=%dday)"

#else  /* ------------------------------------------------------------------ */
#define STR_C_PCU11_0 "감시대상 프로세스(%s,%d)의 CPU 사용률(%4.2f%%)과CPU 사용시간(%dMin)이 지정한 임계치(사용률:%d%%, 사용시간:%dMin)보다 높습니다"
#define STR_C_PCU11_1 "감시대상 프로세스(%s,%d)의 CPU 사용률(%4.2f%%)과CPU 사용시간(%dMin)이 지정한 임계치(사용률:%4.2f%%, 사용시간:%dMin)보다 높습니다"
#define STR_I_PCU11_1 "프로세스별 CPU 사용률과 누적 사용시간 감시가 정상적으로 수행되었습니다"
#define STR_F_PCU11_2 "감시대상 프로세스(%s,%d)의 메모리 사용량(%dKB)이 fatal 수준(%dKB)에 도달하였습니다."
#define STR_C_PCU11_2 "감시대상 프로세스(%s,%d)의 메모리 사용량(%dKB)이 위험 수준(%dKB)에 도달하였습니다."
#define STR_W_PCU11_2 "감시대상 프로세스(%s,%d)의 메모리 사용량(%dKB)이 경고 수준(%dKB)에 도달하였습니다."
#define STR_C_PCU11_3 "감시대상 프로세스(%s,%d)의 Owner(%s)가 지정한 Owner(%s)와 같지 않습니다"
#define STR_C_PCU11_4 "감시대상 프로세스(%s,%d)에 대한 AUTO ACTION COMMAND(%s) 수행을 실패하였습니다"
#define STR_I_PCU11_4 "감시대상 프로세스(%s,%d)에 대한 AUTO ACTION COMMAND(%s)를 수행하였습니다"
#define STR_F_DSK11_1 "파일시스템(%s)의 가용공간이 Fatal수준에 도달하였습니다(사용률:%d%%, 가용:%.fKBytes)"
#define STR_F_DSK11_1_1 "파일시스템(%s)의 가용공간이 Fatal수준에 도달하였습니다(사용률:%d%%, 가용:%.fKBytes, %s)"
#define STR_C_DSK11_1 "파일시스템(%s)의 가용공간이 위험수준에 도달하였습니다(사용률:%d%%, 가용:%.fKBytes)"
#define STR_C_DSK11_1_1 "파일시스템(%s)의 가용공간이 위험수준에 도달하였습니다(사용률:%d%%, 가용:%.fKBytes, %s)"
#define STR_W_DSK11_1 "파일시스템(%s)의 가용공간이 경고수준에 도달하였습니다(사용률:%d%%, 가용:%.fKBytes)"
#define STR_W_DSK11_1_1 "파일시스템(%s)의 가용공간이 경고수준에 도달하였습니다(사용률:%d%%, 가용:%.fKBytes, %s)"
#define STR_I_DSK11_1 "모든 파일시스템 가용공간이 임계치 이하로 정상 운영되고 있습니다"
#define STR_C_DSK11_2 "파일시스템(%s)의 변화률이 위험 수준이상 감소하였습니다(이전시간대:%d%%, 현재:%d%%, 임계치:%d%%)"
#define STR_C_DSK11_2_1 "파일시스템(%s)의 변화률이 위험 수준이상 감소하였습니다(이전시간대:%d%%, 현재:%d%%, 임계치:%d%%, %s)"
#define STR_C_DSK11_3 "파일시스템(%s)의 변화률이 위험 수준이상 증가하였습니다(이전시간대:%d%%, 현재:%d%%, 임계치:%d%%)"
#define STR_C_DSK11_3_1 "파일시스템(%s)의 변화률이 위험 수준이상 증가하였습니다(이전시간대:%d%%, 현재:%d%%, 임계치:%d%%, %s)"
#define STR_C_DSK11_4 "파일시스템(%s)의 가용 공간이 위험 수준이상 감소하였습니다(이전시간대:%.fKBytes, 현재:%.fKBytes, 임계치:%dKBytes)"
#define STR_C_DSK11_4_1 "파일시스템(%s)의 가용 공간이 위험 수준이상 감소하였습니다(이전시간대:%.fKBytes, 현재:%.fKBytes, 임계치:%dKBytes, %s)"
#define STR_C_DSK11_5 "파일시스템(%s)의 가용 공간이 위험 수준이상 증가하였습니다(이전시간대:%.fKBytes, 현재:%.fKBytes, 임계치:%dKBytes)"
#define STR_C_DSK11_5_1 "파일시스템(%s)의 가용 공간이 위험 수준이상 증가하였습니다(이전시간대:%.fKBytes, 현재:%.fKBytes, 임계치:%dKBytes, %s)"
#define STR_C_DSK12_1 "감시대상 파일시스템(%s)이 서버에 존재하지 않습니다"
#define STR_C_DSK12_1_1 "감시대상 파일시스템(%s)이 서버에 존재하지 않습니다(%s)"
#define STR_C_DSK12_1_2 "자동 모니터링중인 파일시스템(%s, %s)이 서버에 존재하지 않습니다. (Elapsed deletion time=%dmin)"
#define STR_W_DSK12_1 "파일시스템(%s)에 설정된 AUTO Action 실행에 실패하였습니다(%s)"
#define STR_W_DSK12_2 "파일시스템(%s)에 설정된 AUTO Action을 실행하였습니다(%s)"
#define STR_C_DSK13_1 "파일시스템(%s)에 임시파일 쓰기 검사를 실패하였습니다"
#define STR_C_DSK13_1_1 "파일시스템(%s)에 임시파일 쓰기 검사를 실패하였습니다(%s)"
#define STR_C_DSK14_1 "파일시스템 임계치 설정 파일이 존재하지 않습니다"
#define STR_C_DSK14_2 "파일시스템 설정 파일 size 체크에 이상이 있습니다"
#define STR_C_DSK14_3 "파일시스템 설정 파일 size가 0Bytes입니다"
#define STR_C_DSK15_1 "파일시스템(%s)의 LV Status가 closed/syncd입니다. Logical Volume status를 확인바랍니다"
#define STR_W_DSK16 "파일시스템 모니터링을 실패하였습니다.('%s' 확인 필요)"
/*#define STR_W_DSK16_1 "파일시스템 모니터링을 실패하였습니다.('df -k' 확인 필요)"*/
/*#define STR_W_DSK16_2 "파일시스템 모니터링에 실패하여 명령어를 변경합니다. (%s -> %s)"*/
#define STR_W_DSK16_3 "파일 시스템 수집 결과가 없습니다.('%s' 확인 필요)"
#define STR_W_DSK16_4 "파일시스템 명령어 수를 확인하는 명령어에 실패하여 파일시스템 모니터링은 수행하지 않습니다. (ps -ef|grep '%s' |wc -l)"
#define STR_W_DSK16_5 "파일시스템 명령어가 %d건 존재하여 파일시스템 모니터링은 수행하지 않습니다. (%s)"
#define STR_W_DSK16_6 "파일시스템 명령어 수를 확인하는 명령어에 실패하여 파일시스템 정보를 제공하지 않습니다. (ps -ef|grep '%s' |wc -l)"
#define STR_W_DSK16_7 "파일시스템 명령어가 %d건 존재하여 파일시스템 정보를 제공하지 않습니다. (%s)"
#define STR_C_DSK17_2 "Storage Node 데이터 수집에 실패하였습니다. 명령어(%s)의 결과를 확인해 주세요."
#define STR_C_DSK17_1 "Storage Node(%s)의 가용공간이 위험 수준입니다. ( Free:%dGB (%s))"
#define STR_W_DSK17_1 "Storage Node(%s)의 가용공간이 경고 수준입니다. ( Free:%dGB (%s))"
#define STR_I_DSK17 "모든 Storage Node 의 가용공간이 정상입니다."
#define STR_F_DSI11_1 "파일시스템(%s)의 Inodes가 Fatal 수준에 도달하였습니다(설정:%d%%, 현재:%d%%)"
#define STR_C_DSI11_1 "파일시스템(%s)의 Inodes가 위험수준에 도달하였습니다(설정:%d%%, 현재:%d%%)"
#define STR_W_DSI11_1 "파일시스템(%s)의 Inodes가 경고수준에 도달하였습니다(설정:%d%%, 현재:%d%%)"
#define STR_I_DSI11_1 "모든 파일시스템 Inodes가 임계치 이하로 정상 운영되고 있습니다"
#define STR_C_DSI12_1 "감시대상 파일시스템(%s) Inodes가 서버에 존재하지 않습니다"
#define STR_C_DSI14_1 "Inodes 임계치 설정 파일이 존재하지 않습니다"
#define STR_C_DSI14_2 "Inodes 설정 파일 size 체크에 이상이 있습니다"
#define STR_C_DSI14_3 "Inodes 설정 파일 size가 0Bytes입니다"
#define STR_W_DSI16_1 "파일시스템 Inodes 모니터링을 실패하였습니다.('%s' 확인 필요)"
#define STR_W_DSI16_2 "파일 시스템 inode 수집 결과가 없습니다"
#define STR_W_DSI16_3 "INODE 명령어 수를 확인하는 명령어에 실패하여 INODE 모니터링은 수행하지 않습니다. (ps -ef|grep '%s' |wc -l)"
#define STR_W_DSI16_4 "INODE 명령어가 %d건 존재하여 INODE 모니터링은 수행하지 않습니다. (%s)"
#define STR_W_DSI16_5 "INODE 명령어 수를 확인하는 명령어에 실패하여 INODE 정보를 제공하지 않습니다. (ps -ef|grep '%s' |wc -l)"
#define STR_W_DSI16_6 "INODE 명령어가 %d건 존재하여 INODE 정보를 제공하지 않습니다. (%s)"
#define STR_C_PRS11_1 "감시 프로세스가 DOWN되었습니다(%s)"
#define STR_C_PRS11_1_1 "감시 %s 프로세스가 DOWN되었습니다(%s)"
#define STR_C_PRS11_1_2 "모니터링 설정 owner와 동일하게 실행중인 프로세스는 존재하지 않습니다. ( %s,  %s )"
#define STR_C_PRS11_1_3 "모니터링 설정 owner와 동일하게 실행중인 %s 프로세스는 존재하지 않습니다. ( %s,  %s )"
#define STR_I_PRS11_1 "감시 프로세스가 정상으로 복귀되었습니다(%s)"
#define STR_I_PRS11_1_1 "감시 %s 프로세스가 정상으로 복귀되었습니다(%s)"
#define STR_C_PRS11_2 "감시 프로세스 AUTO RESTART를 실패하였습니다(%s)"
#define STR_C_PRS11_2_1 "감시 %s 프로세스 AUTO RESTART를 실패하였습니다(%s)"
#define STR_I_PRS11_2 "감시 프로세스를 AUTO RESTART하였습니다(%s)"
#define STR_I_PRS11_2_1 "감시 %s 프로세스를 AUTO RESTART하였습니다(%s)"
#define STR_C_PRS11_3_1 "감시 %s 프로세스의 DAEMON수가 설정 값 보다 작습니다(%s, 설정:%d, 현재:%d)"
#define STR_C_PRS11_3_1_1 "감시 %s 프로세스의 DAEMON수가 설정 값 보다 작습니다(%s, 설정:%d, 현재:%d, 프로세스명:%s)"
#define STR_C_PRS11_3_2 "감시 프로세스의 DAEMON수가 설정 값 보다 작습니다(%s, 설정:%d, 현재:%d)"
#define STR_C_PRS11_3_2_1 "감시 프로세스의 DAEMON수가 설정 값 보다 작습니다(%s, 설정:%d, 현재:%d, 프로세스명:%s)"
#define STR_C_PRS11_4 "감시 프로세스의 DAEMON수가 설정 값보다 높습니다(%s,설정:%d, 현재:%d)"
#define STR_C_PRS11_4_1 "감시 %s 프로세스의 DAEMON수가 설정 값보다 높습니다(%s, 설정:%d, 현재:%d)"
#define STR_I_PRS11_5 "설정된 감시대상 프로세스가 정상적으로 수행되고 있습니다(감시:%d개, 전체:%d개)"
#define STR_I_PRS11_6 "감시 프로세스는 현재 기동중이지 않으나 정상입니다.(%s)"
#define STR_I_PRS11_6_1 "감시 %s 프로세스는 현재 기동중이지 않으나 정상입니다.(%s)"
#define STR_W_PRS11_7_1	"프로세스(%s)의 현재 클러스터링 상태 변경됨(IP = %s, 상태 = %s)"
#define STR_W_PRS11_7_2	"감시대상 프로세스(%s)의 Cluster의 Active 정보(IP Address)를 가져오는데 실패하였습니다."
#define STR_W_PRS11_7_3	"감시대상 %s프로세스(%s)의 Cluster의 Active 정보(IP Address)를 가져오는데 실패하였습니다."
#define STR_F_PRS12_1 "전체 프로세스 수가 Fatal 수준입니다(설정:%d개, 현재:%d개)"
#define STR_C_PRS12_1 "전체 프로세스 수가 위험 수준입니다(설정:%d개, 현재:%d개)"
#define STR_I_PRS12_1 "전체 프로세스 수가 정상으로 복귀되었습니다(설정:%d개, 현재:%d개)"
#define STR_I_PRS12_2 "전체 프로세스 수가 정상입니다.(설정:%d개, 현재:%d개)"
#define STR_C_PRS13_1 "프로세스 설정 파일이 존재하지 않습니다"
#define STR_C_PRS13_2 "프로세스 설정 파일 size 체크가 이상이 있습니다"
#define STR_C_PRS13_3 "프로세스 설정 파일 size가 0입니다"
#define STR_C_PRS13_4 "모니터링을 위해 등록된 프로세스가 감소하였습니다. (%d -> %d)"
#define STR_C_PRS13_5 "모니터링을 위해 등록된 프로세스가 없습니다."
#define STR_F_PRS14_1 "전체 프로세스의 쓰레드 수가 Fatal 수준입니다.(설정:%d개, 현재:%d개)"
#define STR_C_PRS14_1 "전체 프로세스의 쓰레드 수가 위험 수준입니다.(설정:%d개, 현재:%d개)"
#define STR_I_PRS14_1 "전체 프로세스의 쓰레드 수는 정상적입니다.(현재:%d개)"
#define STR_F_SWP11_1 "FREE SWAP 공간이 Fatal 수준에 도달하였습니다(설정:%dKBytes,가용:%.fKBytes)"
#define STR_F_SWP11_2 "FREE SWAP 공간이 %d분 지속 Fatal 수준에 도달하였습니다(설정:%dKBytes,가용:%.fKBytes)"
#define STR_C_SWP11_1 "FREE SWAP 공간이 위험수준에 도달하였습니다(설정:%dKBytes,가용:%.fKBytes)"
#define STR_C_SWP11_2 "FREE SWAP 공간이 %d분 지속 위험수준에 도달하였습니다(설정:%dKBytes,가용:%.fKBytes)"
#define STR_W_SWP11_1 "FREE SWAP 공간이 경고수준에 도달하였습니다(설정:%dKBytes, 가용:%.fKBytes)"
#define STR_W_SWP11_2 "FREE SWAP 공간이 %d분 지속 경고수준에 도달하였습니다(설정:%dKBytes, 가용:%.fKBytes)"
#define STR_I_SWP11_1 "FREE SWAP 공간의 현재 임계치 이하로 정상입니다(가용:%.fKBytes)"
#define STR_F_SWP12	"SWAP 사용률이 Fatal 수준에 도달하였습니다(설정:%d%%, 현재:%3.2f%%)"
#define STR_F_SWP12_2	"SWAP 사용률이 %d분 지속 Fatal 수준에 도달하였습니다(설정:%d%%, 현재:%3.2f%%)"
#define STR_C_SWP12	"SWAP 사용률이 위험 수준에 도달하였습니다(설정:%d%%, 현재:%3.2f%%)"
#define STR_C_SWP12_2	"SWAP 사용률이 %d분 지속 위험 수준에 도달하였습니다(설정:%d%%, 현재:%3.2f%%)"
#define STR_W_SWP12	"SWAP 사용률이 경고 수준에 도달하였습니다(설정:%d%%, 현재:%3.2f%%)"
#define STR_W_SWP12_2	"SWAP 사용률이 %d분 지속 경고 수준에 도달하였습니다(설정:%d%%, 현재:%3.2f%%)"
#define STR_I_SWP12	"SWAP 사용률이 현재 임계치 이하로 복귀되었습니다(현재:%3.2f%%)"
#define STR_I_SWP12_1	"SWAP 사용률이 현재 임계치 이하로 정상입니다(현재:%3.2f%%)"
#define STR_C_SWP14	"SWAP Paging Space 정보를 read 할 수 없습니다. Logical Volume 상태를 확인하여 주시기 바랍니다"

#define STR_I_NET01_1 "Session Established Connection수가 임계치 이하로 정상입니다. (현재:%d)"
#define STR_F_NET01_1 "Session Established Connection수가 Fatal 수준에 도달하였습니다.(설정:%d, 현재:%d)"
#define STR_C_NET01_1 "Session Established Connection수가 위험 수준에 도달하였습니다.(설정:%d, 현재:%d)"
#define STR_W_NET01_1 "Session Established Connection수가 경고 수준에 도달하였습니다.(설정:%d, 현재:%d)"
#define STR_I_NET02_1 "Session Non-Established Connection수가 임계치 이하로 정상입니다. (현재:%d)"
#define STR_F_NET02_1 "Session Non-Established Connection수가 Fatal 수준에 도달하였습니다.(설정:%d, 현재:%d)"
#define STR_C_NET02_1 "Session Non-Established Connection수가 위험 수준에 도달하였습니다.(설정:%d, 현재:%d)"
#define STR_W_NET02_1 "Session Non-Established Connection수가 경고 수준에 도달하였습니다.(설정:%d, 현재:%d)"
#define STR_F_NET03_1 "Established port(%s) session수가 Fatal 수준에 도달하였습니다(설정:%d, 현재:%d)"
#define STR_C_NET03_1 "Established port(%s) session수가 위험 수준에 도달하였습니다(설정:%d, 현재:%d)"
#define STR_W_NET03_1 "Established port(%s) session수가 경고 수준에 도달하였습니다(설정:%d, 현재:%d)"
#define STR_I_NET03_1 "Established port session수가 임계치 이하로 복귀되었습니다"
#define STR_I_NET03_2 "Established port session수가 임계치 이하로 정상입니다"

#define STR_F_NIC11_1 "서버의 초당 IN PACKETS 량이 FATAL 수준에 도달하였습니다.(설정:%dpackets, 현재:%.1fpackets)"
#define STR_C_NIC11_1 "서버의 초당 IN PACKETS 량이 위험 수준에 도달하였습니다.(설정:%dpackets, 현재:%.1fpackets)"
#define STR_W_NIC11_1 "서버의 초당 IN PACKETS 량이 경고 수준에 도달하였습니다.(설정:%dpackets, 현재:%.1fpackets)"
#define STR_F_NIC11_2 "서버의 초당 OUT PACKETS 량이 FATAL 수준에 도달하였습니다.(설정:%dpackets, 현재:%.1fpackets)"
#define STR_C_NIC11_2 "서버의 초당 OUT PACKETS 량이 위험 수준에 도달하였습니다.(설정:%dpackets, 현재:%.1fpackets)"
#define STR_W_NIC11_2 "서버의 초당 OUT PACKETS 량이 경고 수준에 도달하였습니다.(설정:%dpackets, 현재:%.1fpackets)"
#define STR_F_NIC11_3 "서버의 초당 IN BYTES 량이 FATAL 수준에 도달하였습니다.(설정:%dKbps, 현재:%.1fKbps)"
#define STR_C_NIC11_3 "서버의 초당 IN BYTES 량이 위험 수준에 도달하였습니다.(설정:%dKbps, 현재:%.1fKbps)"
#define STR_W_NIC11_3 "서버의 초당 IN BYTES량이 경고 수준에 도달하였습니다.(설정:%dKbps, 현재:%.1fKbps)"
#define STR_F_NIC11_4 "서버의 초당 OUT BYTES 량이 FATAL 수준에 도달하였습니다.(설정:%dKbps, 현재:%.1fKbps)"
#define STR_C_NIC11_4 "서버의 초당 OUT BYTES 량이 위험 수준에 도달하였습니다.(설정:%dKbps, 현재:%.1fKbps)"
#define STR_W_NIC11_4 "서버의 초당 OUT BYTES량이 경고 수준에 도달하였습니다.(설정:%dKbps, 현재:%.1fKbps)"
#define STR_I_NIC11_1 "서버의 초당 트래픽은 임계치 이하로 정상입니다. IN(%.1fpackets, %.1fKbps), OUT(%.1fpackets, %.1fKbps)"
#define STR_I_NIC11_2 "서버의 초당 트래픽은 임계치 이하로 정상입니다. IN(%.1fpackets), OUT(%.1fpackets)"
#define STR_C_NIC12_1 "서버의 Nic Traffic 사용량에 대한 AUTO ACTION COMMAND(%s) 수행을 실패하였습니다"
#define STR_I_NIC12_1 "서버의 Nic Traffic 사용량에 대한 AUTO ACTION COMMAND(%s)를 수행하였습니다"
#define STR_C_HWC01_1 "서버의 온라인 CPU수가 맞지 않습니다. (Logical<설정:%dEa, 현재:%dEa>)"
#define STR_C_HWC01_1_2 "서버의 온라인 CPU수가 맞지 않습니다. (Logical<설정:%dEa, 현재:%dEa>, Physical:%dEa)"
#define STR_C_HWC01_1_3_2 "서버의 온라인 CPU수가 감소하였습니다. (Logical<설정:%dEa, 현재:%dEa>, Physical:%dEa)"
#define STR_C_HWC01_1_3_2_1 "서버의 온라인 CPU수가 감소하였습니다. (Logical<설정:%d~%dEa, 현재:%dEa>, Physical:%dEa)"
#define STR_C_HWC01_1_3_1 "서버의 온라인 CPU수가 감소하였습니다. (Logical<설정:%dEa, 현재:%dEa>)"
#define STR_C_HWC01_1_3_1_1 "서버의 온라인 CPU수가 감소하였습니다. (Logical<설정:%d~%dEa, 현재:%dEa>)"
#define STR_W_HWC01_1_4_2 "서버의 온라인 CPU수가 증가하였습니다. (Logical<설정:%dEa, 현재:%dEa>, Physical:%dEa). 모니터링 setting 값을 자동 변경합니다."
#define STR_W_HWC01_1_4_2_1 "서버의 온라인 CPU수가 증가하였습니다. (Logical<설정:%d~%dEa, 현재:%dEa>, Physical:%dEa). 모니터링 setting 값을 자동 변경합니다."
#define STR_W_HWC01_1_4_1 "서버의 온라인 CPU수가 증가하였습니다. (Logical<설정:%dEa, 현재:%dEa>). 모니터링 setting 값을 자동 변경합니다."
#define STR_W_HWC01_1_4_1_1 "서버의 온라인 CPU수가 증가하였습니다. (Logical<설정:%d~%dEa, 현재:%dEa>), 모니터링 setting 값을 자동 변경합니다."
#define STR_W_HWC01_1_5 "서버의 온라인 CPU수 모니터링을 실패하였습니다.('%s' 확인 필요)"
#define STR_I_HWC01_1 "현재 서버 H/W 상태가 정상입니다. (PROCESSOR<Logical>:%dEa, MEMORY:%dMBytes, 보드온도: %d℃)"
#define STR_I_HWC01_1_2 "현재 서버 H/W 상태가 정상입니다. (PROCESSOR<Logical/Physical>:%dEa/%dEa, MEMORY:%dMBytes, 보드온도: %d℃)"
#define STR_I_HWC01_2 "현재 서버 H/W 상태가 정상입니다. (PROCESSOR<Logical>:%dEa, MEMORY:%dMBytes)"
#define STR_I_HWC01_2_2 "현재 서버 H/W 상태가 정상입니다. (PROCESSOR<Logical/Physical>:%dEa/%dEa, MEMORY:%dMBytes)"
/*#define STR_C_HWC02_1 "서버의 물리적인 MEMORY 사이즈가 맞지 않습니다(설정:%d, 현재:%d)"*/
#define STR_C_HWC02_1_1 "서버의 물리적인 MEMORY 사이즈가 감소하였습니다.(설정:%dMBytes, 현재:%dMBytes)"
#define STR_C_HWC02_1_2 "서버의 물리적인 MEMORY 사이즈가 감소하였습니다.(설정:%d~%dMBytes, 현재:%dMBytes)"
#define STR_W_HWC02_1_3 "서버의 물리적인 MEMORY 사이즈가 증가하였습니다(설정:%dMBytes, 현재:%dMBytes). 모니터링 setting 값을 자동 변경합니다."
#define STR_W_HWC02_1_4 "서버의 물리적인 MEMORY 사이즈가 증가하였습니다(설정:%d~%dMBytes, 현재:%dMBytes). 모니터링 setting 값을 자동 변경합니다."
#define STR_F_HWC03_1 "서버 보드 온도가 Fatal 수준입니다(설정: %d℃, 현재: %d℃)"
#define STR_C_HWC03_1 "서버 보드 온도가 위험 수준입니다(설정: %d℃, 현재: %d℃)"
#define STR_W_HWC03_1 "서버 보드 온도가 경고 수준입니다(설정: %d℃, 현재: %d℃)"

#define STR_C_SEC01_1 "무결성 감시 대상 살정 파일/디렉토리(%s)가 존재하지 않습니다"
#define STR_C_SEC11_1 "무결성 감시 Command 대상 설정 파일/디렉토리(%s)가 존재하지 않거나 모드 설정이 잘못되었습니다"
#define STR_C_SEC02_1 "무결성 감시 대상 파일(%s)의 SIZE가 변경되었습니다(설정:%s Bytes, 현재:%s Bytes)" 
#define STR_C_SEC02_1_1 "무결성 감시 대상 디렉토리(%s)의 SIZE가 변경되었습니다(설정:%s Kbytes, 현재:%s Kbytes)" 
#define STR_C_SEC02_2 "무결성 감시 대상 파일(%s)의 OWNER가 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC12_2 "무결성 감시 Command 대상 파일(%s)의 OWNER가 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC02_2_1 "무결성 감시 대상 디렉토리(%s)의 OWNER가 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC12_2_1 "무결성 감시 Command 대상 디렉토리(%s)의 OWNER가 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC02_3 "무결성 감시 대상 파일(%s)의 GROUP이 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC12_3 "무결성 감시 Command 대상 파일(%s)의 GROUP이 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC02_3_1 "무결성 감시 대상 디렉토리(%s)의 GROUP이 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC12_3_1 "무결성 감시 Command 대상 디렉토리(%s)의 GROUP이 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC02_4 "무결성 감시 대상 파일(%s)의 모드가 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC12_4 "무결성 감시 Command 대상 파일(%s)의 모드가 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC02_4_1 "무결성 감시 대상 디렉토리(%s)의 모드가 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC12_4_1 "무결성 감시 Command 대상 디렉토리(%s)의 모드가 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC02_5 "무결성 감시 대상 파일(%s)의 마지막 수정일이 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC02_5_1 "무결성 감시 대상 디렉토리(%s)의 마지막 수정일이 변경되었습니다(설정:%s, 현재:%s)"
#define STR_C_SEC02_6 "설정한 파일(%s)의 Size가 최대 설정값 보다 큽습니다. (설정:%s Bytes, 현재:%s Bytes)"
#define STR_C_SEC02_6_1 "설정한 디렉터리(%s)의 Size가 최대 설정값 보다 큽습니다. (설정:%s Kbytes, 현재:%s Kbytes)"
#define STR_C_SEC02_6_2 "설정한 파일(%s)의 Size가 최소 설정값 보다 작습니다. (설정:%s Bytes, 현재:%s Bytes)"
#define STR_C_SEC02_6_3 "설정한 디렉터리(%s)의 Size가 최소 설정값 보다 작습니다. (설정:%s Kbytes, 현재:%s Kbytes)"
/*#define STR_C_SEC02_6 "무결성 감시 대상 파일(%s)의 SIZE가 위험 수준에 도달하였습니다.(설정:%d Bytes, 현재:%d Bytes)" */
/*#define STR_C_SEC02_6_1 "무결성 감시 대상 디렉토리(%s)의 SIZE가 위험 수준에 도달하였습니다.(설정:%d Kbytes, 현재:%d Kbytes)" */
#define STR_C_SEC02_7_1 "무결성 감시 대상 디렉토리(%s)의 File count가 위험 수준에 도달하였습니다.(설정:%d 개, 현재:%ld 개)" 
#define STR_I_SEC02_1 "파일/디렉토리 무결성 check가 정상 수행되었습니다(설정:%d)"
#define STR_C_TEP11_1	"서버의 주변 장치(CPU %d Temp)의 온도 상태가 %s입니다. (Probe Name=%s)"
#define STR_C_TEP11_2	"서버의 주변 장치(CPU %d Temp)의 온도가 현재 %.1f℃로 위험합니다. (Probe Name=%s)"
#define STR_W_TEP11		"서버의 주변 장치(CPU %d Temp)의 온도가 현재 %.1f℃로 경고수준입니다. (Probe Name=%s)"
#define STR_I_TEP11		"서버의 주변 장치의 온도가 정상입니다."

#define STR_C_BOT01		"서버의 마지막 부팅 시간은 %s 입니다. ( '%s' 명령어 기준 )"

/*#define STR_C_ACC11_1	"OS 계정 %s의 패스워드 만료일은 %d일 %.1f시간 남았습니다."*/
/*#define STR_C_ACC11_2	"OS 계정 %s의 패스워드 만료일은 %d일 %.1f시간 지났습니다."*/
/*#define STR_W_ACC11		"OS 계정 %s의 패스워드 만료일은 %d일 %.1f시간 남았습니다.(경고)"*/
#define STR_C_ACC11_1	"%s_Password_will_be_expired_@%s"
#define STR_C_ACC11_2	"%s_Password_has_expired_@%s"
#define STR_W_ACC11		"%s_Password_will_be_expired_@%s"
#define STR_I_ACC11		"OS의 모든 계정의 패스워드 만료일은 정상입니다. (target=%d, active=%d, total=%d), (warn=%dday, crit=%dday)"


#endif
