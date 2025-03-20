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
#define MSG_I_SWP12 	"ISWP112"		/* Swap ���� */
#define MSG_I_SWP13 	"ISWP113"		/* Swap ���� */
#define MSG_C_SWP14 	"CSWP114"		/* AIX Swap device(LV) open error */
#define MSG_P_TOP05     "PTOP105"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP106"       /* ������ ���μ��� ���� ���� */
#define MSG_P_TOP07     "PTOP107"       /* mem Top 10 */
#define MSG_P_PRS00 	"PPRS100"		/* N: send process list */
#define MSG_P_PRS10 	"PPRS110"		/* Y: process_check�� uncheck�� setting�� */
#define MSG_I_PRS11 	"IPRS111"
#define MSG_C_PRS11 	"CPRS111"
#define MSG_I_PRS12 	"IPRS112"
#define MSG_C_PRS12 	"CPRS112"		
#define MSG_F_PRS12 	"FPRS112"		
#define MSG_C_PRS13 	"CPRS113"		
#define MSG_I_PRS14 	"IPRS114"		/* thread�� ����͸� */
#define MSG_C_PRS14 	"CPRS114"		/* thread�� ����͸� */
#define MSG_F_PRS14 	"FPRS114"		/* thread�� ����͸� */
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
#define MSG_P_DSK00 	"PDSK100"		/* Disk ���� Messaged Code */
#define MSG_P_DSK10     "PDSK110"		/* it_useporta = 'Y' */
#define MSG_I_DSK11     "IDSK111"
#define MSG_W_DSK11     "WDSK111"
#define MSG_C_DSK11     "CDSK111"
#define MSG_F_DSK11     "FDSK111"
#define MSG_C_DSK12     "CDSK112"		/* filesystem not fount */
#define MSG_W_DSK12     "WDSK112"		/* filesystem not fount */
#define MSG_C_DSK13     "CDSK113"		/* filesystem operation check */
#define MSG_C_DSK14     "CDSK114"		/* ���Ͻý��� ���� ���� */
#define MSG_C_DSK15     "CDSK115"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK116"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_W_DSK16     "WDSK116"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_I_DSK17     "IDSK117"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK117"
#define MSG_C_DSK17     "CDSK117"
#define MSG_P_DSI00 	"PDSI100"		/* Inodes ���� Messaged Code */
#define MSG_P_DSI10     "PDSI110"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI111"
#define MSG_W_DSI11     "WDSI111"
#define MSG_C_DSI11     "CDSI111"
#define MSG_F_DSI11     "FDSI111"
#define MSG_C_DSI12     "CDSI112"
#define MSG_C_DSI14     "CDSI114"		/* Inodes ���� ����  ���� message code */
#define MSG_W_DSI16     "WDSI116"		/* inodes check�� ���������� ������� ���� ��� */
#define MSG_P_HWC00 	"PHWC100"		/* ���� Board�� Temperature */
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
#define MSG_P_OSI02		"POSI102"		/* CPU Count ���� */
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
#define MSG_C_SEC01		"CSEC101"       /* ���Ἲ ���� not found */
#define MSG_C_SEC02		"CSEC102"       
#define MSG_C_SEC11		"CSEC111"       /* ���Ἲ ���� not found */
#define MSG_C_SEC12		"CSEC112"       
#define MSG_I_SEC02		"ISEC102"       
#define MSG_P_NIC10		"PNIC110"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC111"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC111"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC111"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC111"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC112"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC112"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS17		"CSYS117"       /* omreport(dell����-linux) */
#define MSG_C_TEP11		"CTEP111"		/* �µ� ���� - omreport (dell����-linux) */
#define MSG_W_TEP11		"WTEP111"		/* �µ� ���� - omreport (dell����-linux) */
#define MSG_I_TEP11		"ITEP111"		/* �µ� ���� - omreport (dell����-linux) */
#define MSG_P_TEP10		"PTEP110"		/* �µ� ���� - omreport (dell����-linux) */
#define MSG_C_BOT01		"CBOT111"		/* booting �ð� ���� �˸� */
#define MSG_W_BOT01		"WBOT111"		/* booting �ð� ���� �˸� */
#define MSG_C_ACC11     "CACC111"		/* OS ���� ���� */
#define MSG_W_ACC11     "WACC111"		/* OS ���� ���� */
#define MSG_I_ACC11     "IACC111"		/* OS ���� ���� */
#define MSG_P_ACC11     "PACC111"		/* OS ���� ���� */
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
#define MSG_I_SWP13 	"ISWP313"		/* Swap ���� */
#define MSG_C_SWP14 	"CSWP314"		/* AIX Swap device(LV) open error */

#define MSG_P_TOP05     "PTOP305"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP306"       /* ������ ���μ��� ���� ���� */
#define MSG_P_TOP07     "PTOP307"       /* mem Top 10 */
#define MSG_P_PRS00 	"PPRS300"
#define MSG_P_PRS10 	"PPRS310"
#define MSG_I_PRS11 	"IPRS311"
#define MSG_C_PRS11 	"CPRS311"
#define MSG_I_PRS12 	"IPRS312"
#define MSG_F_PRS12 	"FPRS312"
#define MSG_C_PRS12 	"CPRS312"
#define MSG_C_PRS13 	"CPRS313"		
#define MSG_I_PRS14 	"IPRS314"		/* thread�� ����͸� */
#define MSG_C_PRS14 	"CPRS314"		/* thread�� ����͸� */
#define MSG_F_PRS14 	"FPRS314"		/* thread�� ����͸� */	
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
#define MSG_C_DSK14     "CDSK314"		/* ���Ͻý��� ���� ���� */
#define MSG_C_DSK15     "CDSK315"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK316"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_W_DSK16     "WDSK316"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_I_DSK17     "IDSK317"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK317"
#define MSG_C_DSK17     "CDSK317"
#define MSG_P_DSI00 	"PDSI300"		/* Inodes ���� Messaged Code */
#define MSG_P_DSI10     "PDSI310"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI311"
#define MSG_W_DSI11     "WDSI311"
#define MSG_C_DSI11     "CDSI311"
#define MSG_F_DSI11     "FDSI311"
#define MSG_C_DSI12     "CDSI312"
#define MSG_C_DSI14     "CDSI314"		/* Inodes ���� ����  ���� message code */
#define MSG_W_DSI16     "WDSI316"		/* inodes check�� ���������� ������� ���� ��� */
/* H/W */
#define MSG_P_HWC00 	"PHWC300"		/* ���� Board�� Temperature */
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
#define MSG_P_OSI02		"POSI302"		/* CPU Count ���� */
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
#define MSG_C_SEC01		"CSEC301"       /* ���Ἲ ���� not found */
#define MSG_C_SEC02		"CSEC302"       
#define MSG_C_SEC11		"CSEC311"       /* ���Ἲ ���� not found */
#define MSG_C_SEC12		"CSEC312"       
#define MSG_I_SEC02		"ISEC302"       
#define MSG_P_NIC10		"PNIC310"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC311"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC311"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC311"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC311"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC312"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC312"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS16     "CSYS316"		/* aix errpt ���� code */
#define MSG_C_SYS17		"CSYS317"       /* omreport(del����-linux) */
#define MSG_C_BOT01		"CBOT311"		/* booting �ð� ���� �˸� */
#define MSG_W_BOT01		"WBOT311"		/* booting �ð� ���� �˸� */
#define MSG_C_ACC11     "CACC311"		/* OS ���� ���� */
#define MSG_W_ACC11     "WACC311"		/* OS ���� ���� */
#define MSG_I_ACC11     "IACC311"		/* OS ���� ���� */
#define MSG_P_ACC11     "PACC311"		/* OS ���� ���� */
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
#define MSG_I_SWP13 	"ISWP413"		/* Swap ���� */
#define MSG_C_SWP14 	"CSWP414"		/* AIX Swap device(LV) open error */

#define MSG_P_TOP05     "PTOP405"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP406"       /* ������ ���μ��� ���� ���� */
#define MSG_P_TOP07     "PTOP407"       /* mem Top 10 */
#define MSG_P_PRS00 	"PPRS400"
#define MSG_P_PRS10 	"PPRS410"
#define MSG_I_PRS11 	"IPRS411"
#define MSG_C_PRS11 	"CPRS411"
#define MSG_I_PRS12 	"IPRS412"
#define MSG_F_PRS12 	"FPRS412"
#define MSG_C_PRS12 	"CPRS412"
#define MSG_C_PRS13 	"CPRS413"		
#define MSG_I_PRS14 	"IPRS414"		/* thread�� ����͸� */
#define MSG_C_PRS14 	"CPRS414"		/* thread�� ����͸� */	
#define MSG_F_PRS14 	"FPRS414"		/* thread�� ����͸� */	
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
#define MSG_C_DSK14     "CDSK414"		/* ���Ͻý��� ���� ���� */
#define MSG_C_DSK15     "CDSK415"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK416"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_W_DSK16     "WDSK416"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_I_DSK17     "IDSK417"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK417"
#define MSG_C_DSK17     "CDSK417"
#define MSG_P_DSI00 	"PDSI400"		/* Inodes ���� Messaged Code */
#define MSG_P_DSI10     "PDSI410"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI411"
#define MSG_W_DSI11     "WDSI411"
#define MSG_C_DSI11     "CDSI411"
#define MSG_F_DSI11     "FDSI411"
#define MSG_C_DSI12     "CDSI412"
#define MSG_C_DSI14     "CDSI414"		/* Inodes ���� ����  ���� message code */
#define MSG_W_DSI16     "WDSI416"		/* inodes check�� ���������� ������� ���� ��� */
/* H/W */
#define MSG_P_HWC00 	"PHWC400"		/* ���� Board�� Temperature */
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
#define MSG_P_OSI02		"POSI402"		/* CPU Count ���� */
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
#define MSG_C_SEC01		"CSEC401"       /* ���Ἲ ���� not found */
#define MSG_C_SEC02		"CSEC402"       
#define MSG_C_SEC11		"CSEC411"       /* ���Ἲ ���� not found */
#define MSG_C_SEC12		"CSEC412"       
#define MSG_I_SEC02		"ISEC402"       
#define MSG_P_NIC10		"PNIC410"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC411"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC411"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC411"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC411"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC412"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC412"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS17		"CSYS417"       /* omreport(del����-linux) */
#define MSG_C_BOT01		"CBOT411"		/* booting �ð� ���� �˸� */
#define MSG_W_BOT01		"WBOT411"		/* booting �ð� ���� �˸� */
#define MSG_C_ACC11     "CACC411"		/* OS ���� ���� */
#define MSG_W_ACC11     "WACC411"		/* OS ���� ���� */
#define MSG_I_ACC11     "IACC411"		/* OS ���� ���� */
#define MSG_P_ACC11     "PACC411"		/* OS ���� ���� */
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
#define MSG_I_SWP13 	"ISWP513"		/* Swap ���� */
#define MSG_C_SWP14 	"CSWP514"		/* AIX Swap device(LV) open error */

#define MSG_P_TOP05     "PTOP505"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP506"       /* ������ ���μ��� ���� ���� */
#define MSG_P_TOP07     "PTOP507"       /* mem Top 10 */
#define MSG_P_PRS00 	"PPRS500"
#define MSG_P_PRS10 	"PPRS510"
#define MSG_I_PRS11 	"IPRS511"
#define MSG_C_PRS11 	"CPRS511"
#define MSG_I_PRS12 	"IPRS512"
#define MSG_F_PRS12 	"FPRS512"
#define MSG_C_PRS12 	"CPRS512"
#define MSG_C_PRS13 	"CPRS513"		
#define MSG_I_PRS14 	"IPRS514"		/* thread�� ����͸� */
#define MSG_C_PRS14 	"CPRS514"		/* thread�� ����͸� */	
#define MSG_F_PRS14 	"FPRS514"		/* thread�� ����͸� */	
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
#define MSG_C_DSK14     "CDSK514"		/* ���Ͻý��� ���� ���� */
#define MSG_C_DSK15     "CDSK515"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK516"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_W_DSK16     "WDSK516"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_I_DSK17     "IDSK517"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK517"
#define MSG_C_DSK17     "CDSK517"
#define MSG_P_DSI00 	"PDSI500"		/* Inodes ���� Messaged Code */
#define MSG_P_DSI10     "PDSI510"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI511"
#define MSG_W_DSI11     "WDSI511"
#define MSG_C_DSI11     "CDSI511"
#define MSG_F_DSI11     "FDSI511"
#define MSG_C_DSI12     "CDSI512"
#define MSG_C_DSI14     "CDSI514"		/* Inodes ���� ����  ���� message code */
#define MSG_W_DSI16     "WDSI516"		/* inodes check�� ���������� ������� ���� ��� */
/* H/W */
#define MSG_P_HWC00 	"PHWC500"		/* ���� Board�� Temperature */
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
#define MSG_P_OSI02		"POSI502"		/* CPU Count ���� */
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
#define MSG_C_SEC01		"CSEC501"       /* ���Ἲ ���� not found */
#define MSG_C_SEC02		"CSEC502"       
#define MSG_C_SEC11		"CSEC511"       /* ���Ἲ ���� not found */
#define MSG_C_SEC12		"CSEC512"       
#define MSG_I_SEC02		"ISEC502"       
#define MSG_P_NIC10		"PNIC510"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC511"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC511"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC511"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC511"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC512"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC512"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS17		"CSYS517"       /* omreport(del����-linux) */
#define MSG_C_BOT01		"CBOT511"		/* booting �ð� ���� �˸� */
#define MSG_W_BOT01		"WBOT511"		/* booting �ð� ���� �˸� */
#define MSG_C_ACC11     "CACC511"		/* OS ���� ���� */
#define MSG_W_ACC11     "WACC511"		/* OS ���� ���� */
#define MSG_I_ACC11     "IACC511"		/* OS ���� ���� */
#define MSG_P_ACC11     "PACC511"		/* OS ���� ���� */
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
#define MSG_I_SWP13 	"ISWP713"		/* Swap ���� */
#define MSG_W_SWP12 	"WSWP712"
#define MSG_C_SWP12 	"CSWP712"
#define MSG_F_SWP12 	"FSWP712"
#define MSG_C_SWP14 	"CSWP714"		/* AIX Swap device(LV) open error */

#define MSG_P_TOP05     "PTOP705"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP706"       /* ������ ���μ��� ���� ���� */
#define MSG_P_TOP07     "PTOP707"       /* mem Top 10 */
#define MSG_P_PRS00 	"PPRS700"
#define MSG_P_PRS10 	"PPRS710"
#define MSG_I_PRS11 	"IPRS711"
#define MSG_C_PRS11 	"CPRS711"
#define MSG_I_PRS12 	"IPRS712"
#define MSG_F_PRS12 	"FPRS712"
#define MSG_C_PRS12 	"CPRS712"
#define MSG_C_PRS13 	"CPRS713"		
#define MSG_I_PRS14 	"IPRS714"		/* thread�� ����͸� */
#define MSG_C_PRS14 	"CPRS714"		/* thread�� ����͸� */	
#define MSG_F_PRS14 	"FPRS714"		/* thread�� ����͸� */	
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
#define MSG_C_DSK14     "CDSK714"		/* ���Ͻý��� ���� ���� */
#define MSG_C_DSK15     "CDSK715"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK716"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_W_DSK16     "WDSK716"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_I_DSK17     "IDSK717"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK717"
#define MSG_C_DSK17     "CDSK717"
#define MSG_P_DSI00 	"PDSI700"		/* Inodes ���� Messaged Code */
#define MSG_P_DSI10     "PDSI710"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI711"
#define MSG_W_DSI11     "WDSI711"
#define MSG_C_DSI11     "CDSI711"
#define MSG_F_DSI11     "FDSI711"
#define MSG_C_DSI12     "CDSI712"
#define MSG_C_DSI14     "CDSI714"		/* Inodes ���� ����  ���� message code */
#define MSG_W_DSI16     "WDSI716"		/* inodes check�� ���������� ������� ���� ��� */
/* H/W */
#define MSG_P_HWC00 	"PHWC700"		/* ���� Board�� Temperature */
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
#define MSG_P_OSI02		"POSI702"		/* CPU Count ���� */
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
#define MSG_C_SEC01		"CSEC701"       /* ���Ἲ ���� not found */
#define MSG_C_SEC02		"CSEC702"       
#define MSG_C_SEC11		"CSEC711"       /* ���Ἲ ���� not found */
#define MSG_C_SEC12		"CSEC712"       
#define MSG_I_SEC02		"ISEC702" 
#define MSG_P_NIC10		"PNIC710"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC711"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC711"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC711"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC711"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC712"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC712"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS17		"CSYS717"       /* omreport(del����-linux) */
#define MSG_C_BOT01		"CBOT711"		/* booting �ð� ���� �˸� */
#define MSG_W_BOT01		"WBOT711"		/* booting �ð� ���� �˸� */
#define MSG_C_ACC11     "CACC711"		/* OS ���� ���� */
#define MSG_W_ACC11     "WACC711"		/* OS ���� ���� */
#define MSG_I_ACC11     "IACC711"		/* OS ���� ���� */
#define MSG_P_ACC11     "PACC711"		/* OS ���� ���� */
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
#define MSG_I_SWP13     "ISWP213"       /* Swap ���� */
#define MSG_C_SWP14 	"CSWP214"		/* AIX Swap device(LV) open error */

#define MSG_P_TOP05     "PTOP205"       /* cpu Top 10 */
#define MSG_P_TOP06     "PTOP206"       /* ������ ���μ��� ���� ���� */
#define MSG_P_TOP07     "PTOP207"       /* top Top 10 */
#define MSG_P_PRS00 	"PPRS200"		/* USE_PORT = 'N' �� ��� */
#define MSG_P_PRS10 	"PPRS210"
#define MSG_I_PRS11 	"IPRS211"
#define MSG_C_PRS11 	"CPRS211"
#define MSG_I_PRS12 	"IPRS212"
#define MSG_F_PRS12 	"FPRS212"
#define MSG_C_PRS12 	"CPRS212"
#define MSG_C_PRS13 	"CPRS213"
#define MSG_I_PRS14 	"IPRS214"		/* thread�� ����͸� */
#define MSG_C_PRS14 	"CPRS214"		/* thread�� ����͸� */	
#define MSG_F_PRS14 	"FPRS214"		/* thread�� ����͸� */	
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
#define MSG_C_DSK14     "CDSK214"		/* ���Ͻý��� �������� */
#define MSG_C_DSK15     "CDSK215"		/* Aix Logical Volume status */
#define MSG_C_DSK16     "CDSK216"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_W_DSK16     "WDSK216"		/* disk check�� ���������� ������� ���� ��� (df -k ó���� hang �߻�) */
#define MSG_I_DSK17     "IDSK217"		/* vmmon storage node */
#define MSG_W_DSK17     "WDSK217"
#define MSG_C_DSK17     "CDSK217"
#define MSG_P_DSI00 	"PDSI200"		/* Inodes ���� Messaged Code */
#define MSG_P_DSI10     "PDSI210"		/* it_useport = 'Y' */
#define MSG_I_DSI11     "IDSI211"
#define MSG_W_DSI11     "WDSI211"
#define MSG_C_DSI11     "CDSI211"
#define MSG_F_DSI11     "FDSI211"
#define MSG_C_DSI12     "CDSI212"
#define MSG_C_DSI14     "CDSI214"		/* Inodes ���� ����  ���� message code */
#define MSG_W_DSI16     "WDSI216"		/* inodes check�� ���������� ������� ���� ��� */
/* H/W */
#define MSG_P_HWC00 	"PHWC200"		/* ���� Board�� Temperature */
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
#define MSG_P_OSI02		"POSI202"		/* CPU Count ���� */
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
#define MSG_C_SEC01		"CSEC201"       /* ���Ἲ ���� not found */
#define MSG_C_SEC02		"CSEC202"       
#define MSG_C_SEC11		"CSEC211"       /* ���Ἲ ���� not found */
#define MSG_C_SEC12		"CSEC212"       
#define MSG_I_SEC02		"ISEC202" 
#define MSG_P_NIC10		"PNIC210"		/* NIC Traffic Packet */
#define MSG_F_NIC11		"FNIC211"		/* NIC Traffic Packet */
#define MSG_C_NIC11		"CNIC211"		/* NIC Traffic Packet */
#define MSG_W_NIC11		"WNIC211"		/* NIC Traffic Packet */
#define MSG_I_NIC11		"INIC211"		/* NIC Traffic Packet */
#define MSG_C_NIC12		"CNIC212"		/* NIC Traffic Packet - Auto Action */
#define MSG_I_NIC12		"INIC212"		/* NIC Traffic Packet - Auto Action */
#define MSG_C_SYS17		"CSYS217"       /* omreport(del����-linux) */
#define MSG_C_BOT01		"CBOT211"		/* booting �ð� ���� �˸� */
#define MSG_W_BOT01		"WBOT211"		/* booting �ð� ���� �˸� */
#define MSG_C_ACC11     "CACC211"		/* OS ���� ���� */
#define MSG_W_ACC11     "WACC211"		/* OS ���� ���� */
#define MSG_I_ACC11     "IACC211"		/* OS ���� ���� */
#define MSG_P_ACC11     "PACC211"		/* OS ���� ���� */

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
#define STR_C_PCU11_0 "���ô�� ���μ���(%s,%d)�� CPU ����(%4.2f%%)��CPU ���ð�(%dMin)�� ������ �Ӱ�ġ(����:%d%%, ���ð�:%dMin)���� �����ϴ�"
#define STR_C_PCU11_1 "���ô�� ���μ���(%s,%d)�� CPU ����(%4.2f%%)��CPU ���ð�(%dMin)�� ������ �Ӱ�ġ(����:%4.2f%%, ���ð�:%dMin)���� �����ϴ�"
#define STR_I_PCU11_1 "���μ����� CPU ������ ���� ���ð� ���ð� ���������� ����Ǿ����ϴ�"
#define STR_F_PCU11_2 "���ô�� ���μ���(%s,%d)�� �޸� ��뷮(%dKB)�� fatal ����(%dKB)�� �����Ͽ����ϴ�."
#define STR_C_PCU11_2 "���ô�� ���μ���(%s,%d)�� �޸� ��뷮(%dKB)�� ���� ����(%dKB)�� �����Ͽ����ϴ�."
#define STR_W_PCU11_2 "���ô�� ���μ���(%s,%d)�� �޸� ��뷮(%dKB)�� ��� ����(%dKB)�� �����Ͽ����ϴ�."
#define STR_C_PCU11_3 "���ô�� ���μ���(%s,%d)�� Owner(%s)�� ������ Owner(%s)�� ���� �ʽ��ϴ�"
#define STR_C_PCU11_4 "���ô�� ���μ���(%s,%d)�� ���� AUTO ACTION COMMAND(%s) ������ �����Ͽ����ϴ�"
#define STR_I_PCU11_4 "���ô�� ���μ���(%s,%d)�� ���� AUTO ACTION COMMAND(%s)�� �����Ͽ����ϴ�"
#define STR_F_DSK11_1 "���Ͻý���(%s)�� ��������� Fatal���ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%.fKBytes)"
#define STR_F_DSK11_1_1 "���Ͻý���(%s)�� ��������� Fatal���ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%.fKBytes, %s)"
#define STR_C_DSK11_1 "���Ͻý���(%s)�� ��������� ������ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%.fKBytes)"
#define STR_C_DSK11_1_1 "���Ͻý���(%s)�� ��������� ������ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%.fKBytes, %s)"
#define STR_W_DSK11_1 "���Ͻý���(%s)�� ��������� �����ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%.fKBytes)"
#define STR_W_DSK11_1_1 "���Ͻý���(%s)�� ��������� �����ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%.fKBytes, %s)"
#define STR_I_DSK11_1 "��� ���Ͻý��� ��������� �Ӱ�ġ ���Ϸ� ���� ��ǰ� �ֽ��ϴ�"
#define STR_C_DSK11_2 "���Ͻý���(%s)�� ��ȭ���� ���� �����̻� �����Ͽ����ϴ�(�����ð���:%d%%, ����:%d%%, �Ӱ�ġ:%d%%)"
#define STR_C_DSK11_2_1 "���Ͻý���(%s)�� ��ȭ���� ���� �����̻� �����Ͽ����ϴ�(�����ð���:%d%%, ����:%d%%, �Ӱ�ġ:%d%%, %s)"
#define STR_C_DSK11_3 "���Ͻý���(%s)�� ��ȭ���� ���� �����̻� �����Ͽ����ϴ�(�����ð���:%d%%, ����:%d%%, �Ӱ�ġ:%d%%)"
#define STR_C_DSK11_3_1 "���Ͻý���(%s)�� ��ȭ���� ���� �����̻� �����Ͽ����ϴ�(�����ð���:%d%%, ����:%d%%, �Ӱ�ġ:%d%%, %s)"
#define STR_C_DSK11_4 "���Ͻý���(%s)�� ���� ������ ���� �����̻� �����Ͽ����ϴ�(�����ð���:%.fKBytes, ����:%.fKBytes, �Ӱ�ġ:%dKBytes)"
#define STR_C_DSK11_4_1 "���Ͻý���(%s)�� ���� ������ ���� �����̻� �����Ͽ����ϴ�(�����ð���:%.fKBytes, ����:%.fKBytes, �Ӱ�ġ:%dKBytes, %s)"
#define STR_C_DSK11_5 "���Ͻý���(%s)�� ���� ������ ���� �����̻� �����Ͽ����ϴ�(�����ð���:%.fKBytes, ����:%.fKBytes, �Ӱ�ġ:%dKBytes)"
#define STR_C_DSK11_5_1 "���Ͻý���(%s)�� ���� ������ ���� �����̻� �����Ͽ����ϴ�(�����ð���:%.fKBytes, ����:%.fKBytes, �Ӱ�ġ:%dKBytes, %s)"
#define STR_C_DSK12_1 "���ô�� ���Ͻý���(%s)�� ������ �������� �ʽ��ϴ�"
#define STR_C_DSK12_1_1 "���ô�� ���Ͻý���(%s)�� ������ �������� �ʽ��ϴ�(%s)"
#define STR_C_DSK12_1_2 "�ڵ� ����͸����� ���Ͻý���(%s, %s)�� ������ �������� �ʽ��ϴ�. (Elapsed deletion time=%dmin)"
#define STR_W_DSK12_1 "���Ͻý���(%s)�� ������ AUTO Action ���࿡ �����Ͽ����ϴ�(%s)"
#define STR_W_DSK12_2 "���Ͻý���(%s)�� ������ AUTO Action�� �����Ͽ����ϴ�(%s)"
#define STR_C_DSK13_1 "���Ͻý���(%s)�� �ӽ����� ���� �˻縦 �����Ͽ����ϴ�"
#define STR_C_DSK13_1_1 "���Ͻý���(%s)�� �ӽ����� ���� �˻縦 �����Ͽ����ϴ�(%s)"
#define STR_C_DSK14_1 "���Ͻý��� �Ӱ�ġ ���� ������ �������� �ʽ��ϴ�"
#define STR_C_DSK14_2 "���Ͻý��� ���� ���� size üũ�� �̻��� �ֽ��ϴ�"
#define STR_C_DSK14_3 "���Ͻý��� ���� ���� size�� 0Bytes�Դϴ�"
#define STR_C_DSK15_1 "���Ͻý���(%s)�� LV Status�� closed/syncd�Դϴ�. Logical Volume status�� Ȯ�ιٶ��ϴ�"
#define STR_W_DSK16 "���Ͻý��� ����͸��� �����Ͽ����ϴ�.('%s' Ȯ�� �ʿ�)"
/*#define STR_W_DSK16_1 "���Ͻý��� ����͸��� �����Ͽ����ϴ�.('df -k' Ȯ�� �ʿ�)"*/
/*#define STR_W_DSK16_2 "���Ͻý��� ����͸��� �����Ͽ� ��ɾ �����մϴ�. (%s -> %s)"*/
#define STR_W_DSK16_3 "���� �ý��� ���� ����� �����ϴ�.('%s' Ȯ�� �ʿ�)"
#define STR_W_DSK16_4 "���Ͻý��� ��ɾ� ���� Ȯ���ϴ� ��ɾ �����Ͽ� ���Ͻý��� ����͸��� �������� �ʽ��ϴ�. (ps -ef|grep '%s' |wc -l)"
#define STR_W_DSK16_5 "���Ͻý��� ��ɾ %d�� �����Ͽ� ���Ͻý��� ����͸��� �������� �ʽ��ϴ�. (%s)"
#define STR_W_DSK16_6 "���Ͻý��� ��ɾ� ���� Ȯ���ϴ� ��ɾ �����Ͽ� ���Ͻý��� ������ �������� �ʽ��ϴ�. (ps -ef|grep '%s' |wc -l)"
#define STR_W_DSK16_7 "���Ͻý��� ��ɾ %d�� �����Ͽ� ���Ͻý��� ������ �������� �ʽ��ϴ�. (%s)"
#define STR_C_DSK17_2 "Storage Node ������ ������ �����Ͽ����ϴ�. ��ɾ�(%s)�� ����� Ȯ���� �ּ���."
#define STR_C_DSK17_1 "Storage Node(%s)�� ��������� ���� �����Դϴ�. ( Free:%dGB (%s))"
#define STR_W_DSK17_1 "Storage Node(%s)�� ��������� ��� �����Դϴ�. ( Free:%dGB (%s))"
#define STR_I_DSK17 "��� Storage Node �� ��������� �����Դϴ�."
#define STR_F_DSI11_1 "���Ͻý���(%s)�� Inodes�� Fatal ���ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%d%%)"
#define STR_C_DSI11_1 "���Ͻý���(%s)�� Inodes�� ������ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%d%%)"
#define STR_W_DSI11_1 "���Ͻý���(%s)�� Inodes�� �����ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%d%%)"
#define STR_I_DSI11_1 "��� ���Ͻý��� Inodes�� �Ӱ�ġ ���Ϸ� ���� ��ǰ� �ֽ��ϴ�"
#define STR_C_DSI12_1 "���ô�� ���Ͻý���(%s) Inodes�� ������ �������� �ʽ��ϴ�"
#define STR_C_DSI14_1 "Inodes �Ӱ�ġ ���� ������ �������� �ʽ��ϴ�"
#define STR_C_DSI14_2 "Inodes ���� ���� size üũ�� �̻��� �ֽ��ϴ�"
#define STR_C_DSI14_3 "Inodes ���� ���� size�� 0Bytes�Դϴ�"
#define STR_W_DSI16_1 "���Ͻý��� Inodes ����͸��� �����Ͽ����ϴ�.('%s' Ȯ�� �ʿ�)"
#define STR_W_DSI16_2 "���� �ý��� inode ���� ����� �����ϴ�"
#define STR_W_DSI16_3 "INODE ��ɾ� ���� Ȯ���ϴ� ��ɾ �����Ͽ� INODE ����͸��� �������� �ʽ��ϴ�. (ps -ef|grep '%s' |wc -l)"
#define STR_W_DSI16_4 "INODE ��ɾ %d�� �����Ͽ� INODE ����͸��� �������� �ʽ��ϴ�. (%s)"
#define STR_W_DSI16_5 "INODE ��ɾ� ���� Ȯ���ϴ� ��ɾ �����Ͽ� INODE ������ �������� �ʽ��ϴ�. (ps -ef|grep '%s' |wc -l)"
#define STR_W_DSI16_6 "INODE ��ɾ %d�� �����Ͽ� INODE ������ �������� �ʽ��ϴ�. (%s)"
#define STR_C_PRS11_1 "���� ���μ����� DOWN�Ǿ����ϴ�(%s)"
#define STR_C_PRS11_1_1 "���� %s ���μ����� DOWN�Ǿ����ϴ�(%s)"
#define STR_C_PRS11_1_2 "����͸� ���� owner�� �����ϰ� �������� ���μ����� �������� �ʽ��ϴ�. ( %s,  %s )"
#define STR_C_PRS11_1_3 "����͸� ���� owner�� �����ϰ� �������� %s ���μ����� �������� �ʽ��ϴ�. ( %s,  %s )"
#define STR_I_PRS11_1 "���� ���μ����� �������� ���͵Ǿ����ϴ�(%s)"
#define STR_I_PRS11_1_1 "���� %s ���μ����� �������� ���͵Ǿ����ϴ�(%s)"
#define STR_C_PRS11_2 "���� ���μ��� AUTO RESTART�� �����Ͽ����ϴ�(%s)"
#define STR_C_PRS11_2_1 "���� %s ���μ��� AUTO RESTART�� �����Ͽ����ϴ�(%s)"
#define STR_I_PRS11_2 "���� ���μ����� AUTO RESTART�Ͽ����ϴ�(%s)"
#define STR_I_PRS11_2_1 "���� %s ���μ����� AUTO RESTART�Ͽ����ϴ�(%s)"
#define STR_C_PRS11_3_1 "���� %s ���μ����� DAEMON���� ���� �� ���� �۽��ϴ�(%s, ����:%d, ����:%d)"
#define STR_C_PRS11_3_1_1 "���� %s ���μ����� DAEMON���� ���� �� ���� �۽��ϴ�(%s, ����:%d, ����:%d, ���μ�����:%s)"
#define STR_C_PRS11_3_2 "���� ���μ����� DAEMON���� ���� �� ���� �۽��ϴ�(%s, ����:%d, ����:%d)"
#define STR_C_PRS11_3_2_1 "���� ���μ����� DAEMON���� ���� �� ���� �۽��ϴ�(%s, ����:%d, ����:%d, ���μ�����:%s)"
#define STR_C_PRS11_4 "���� ���μ����� DAEMON���� ���� ������ �����ϴ�(%s,����:%d, ����:%d)"
#define STR_C_PRS11_4_1 "���� %s ���μ����� DAEMON���� ���� ������ �����ϴ�(%s, ����:%d, ����:%d)"
#define STR_I_PRS11_5 "������ ���ô�� ���μ����� ���������� ����ǰ� �ֽ��ϴ�(����:%d��, ��ü:%d��)"
#define STR_I_PRS11_6 "���� ���μ����� ���� �⵿������ ������ �����Դϴ�.(%s)"
#define STR_I_PRS11_6_1 "���� %s ���μ����� ���� �⵿������ ������ �����Դϴ�.(%s)"
#define STR_W_PRS11_7_1	"���μ���(%s)�� ���� Ŭ�����͸� ���� �����(IP = %s, ���� = %s)"
#define STR_W_PRS11_7_2	"���ô�� ���μ���(%s)�� Cluster�� Active ����(IP Address)�� �������µ� �����Ͽ����ϴ�."
#define STR_W_PRS11_7_3	"���ô�� %s���μ���(%s)�� Cluster�� Active ����(IP Address)�� �������µ� �����Ͽ����ϴ�."
#define STR_F_PRS12_1 "��ü ���μ��� ���� Fatal �����Դϴ�(����:%d��, ����:%d��)"
#define STR_C_PRS12_1 "��ü ���μ��� ���� ���� �����Դϴ�(����:%d��, ����:%d��)"
#define STR_I_PRS12_1 "��ü ���μ��� ���� �������� ���͵Ǿ����ϴ�(����:%d��, ����:%d��)"
#define STR_I_PRS12_2 "��ü ���μ��� ���� �����Դϴ�.(����:%d��, ����:%d��)"
#define STR_C_PRS13_1 "���μ��� ���� ������ �������� �ʽ��ϴ�"
#define STR_C_PRS13_2 "���μ��� ���� ���� size üũ�� �̻��� �ֽ��ϴ�"
#define STR_C_PRS13_3 "���μ��� ���� ���� size�� 0�Դϴ�"
#define STR_C_PRS13_4 "����͸��� ���� ��ϵ� ���μ����� �����Ͽ����ϴ�. (%d -> %d)"
#define STR_C_PRS13_5 "����͸��� ���� ��ϵ� ���μ����� �����ϴ�."
#define STR_F_PRS14_1 "��ü ���μ����� ������ ���� Fatal �����Դϴ�.(����:%d��, ����:%d��)"
#define STR_C_PRS14_1 "��ü ���μ����� ������ ���� ���� �����Դϴ�.(����:%d��, ����:%d��)"
#define STR_I_PRS14_1 "��ü ���μ����� ������ ���� �������Դϴ�.(����:%d��)"
#define STR_F_SWP11_1 "FREE SWAP ������ Fatal ���ؿ� �����Ͽ����ϴ�(����:%dKBytes,����:%.fKBytes)"
#define STR_F_SWP11_2 "FREE SWAP ������ %d�� ���� Fatal ���ؿ� �����Ͽ����ϴ�(����:%dKBytes,����:%.fKBytes)"
#define STR_C_SWP11_1 "FREE SWAP ������ ������ؿ� �����Ͽ����ϴ�(����:%dKBytes,����:%.fKBytes)"
#define STR_C_SWP11_2 "FREE SWAP ������ %d�� ���� ������ؿ� �����Ͽ����ϴ�(����:%dKBytes,����:%.fKBytes)"
#define STR_W_SWP11_1 "FREE SWAP ������ �����ؿ� �����Ͽ����ϴ�(����:%dKBytes, ����:%.fKBytes)"
#define STR_W_SWP11_2 "FREE SWAP ������ %d�� ���� �����ؿ� �����Ͽ����ϴ�(����:%dKBytes, ����:%.fKBytes)"
#define STR_I_SWP11_1 "FREE SWAP ������ ���� �Ӱ�ġ ���Ϸ� �����Դϴ�(����:%.fKBytes)"
#define STR_F_SWP12	"SWAP ������ Fatal ���ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%3.2f%%)"
#define STR_F_SWP12_2	"SWAP ������ %d�� ���� Fatal ���ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%3.2f%%)"
#define STR_C_SWP12	"SWAP ������ ���� ���ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%3.2f%%)"
#define STR_C_SWP12_2	"SWAP ������ %d�� ���� ���� ���ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%3.2f%%)"
#define STR_W_SWP12	"SWAP ������ ��� ���ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%3.2f%%)"
#define STR_W_SWP12_2	"SWAP ������ %d�� ���� ��� ���ؿ� �����Ͽ����ϴ�(����:%d%%, ����:%3.2f%%)"
#define STR_I_SWP12	"SWAP ������ ���� �Ӱ�ġ ���Ϸ� ���͵Ǿ����ϴ�(����:%3.2f%%)"
#define STR_I_SWP12_1	"SWAP ������ ���� �Ӱ�ġ ���Ϸ� �����Դϴ�(����:%3.2f%%)"
#define STR_C_SWP14	"SWAP Paging Space ������ read �� �� �����ϴ�. Logical Volume ���¸� Ȯ���Ͽ� �ֽñ� �ٶ��ϴ�"

#define STR_I_NET01_1 "Session Established Connection���� �Ӱ�ġ ���Ϸ� �����Դϴ�. (����:%d)"
#define STR_F_NET01_1 "Session Established Connection���� Fatal ���ؿ� �����Ͽ����ϴ�.(����:%d, ����:%d)"
#define STR_C_NET01_1 "Session Established Connection���� ���� ���ؿ� �����Ͽ����ϴ�.(����:%d, ����:%d)"
#define STR_W_NET01_1 "Session Established Connection���� ��� ���ؿ� �����Ͽ����ϴ�.(����:%d, ����:%d)"
#define STR_I_NET02_1 "Session Non-Established Connection���� �Ӱ�ġ ���Ϸ� �����Դϴ�. (����:%d)"
#define STR_F_NET02_1 "Session Non-Established Connection���� Fatal ���ؿ� �����Ͽ����ϴ�.(����:%d, ����:%d)"
#define STR_C_NET02_1 "Session Non-Established Connection���� ���� ���ؿ� �����Ͽ����ϴ�.(����:%d, ����:%d)"
#define STR_W_NET02_1 "Session Non-Established Connection���� ��� ���ؿ� �����Ͽ����ϴ�.(����:%d, ����:%d)"
#define STR_F_NET03_1 "Established port(%s) session���� Fatal ���ؿ� �����Ͽ����ϴ�(����:%d, ����:%d)"
#define STR_C_NET03_1 "Established port(%s) session���� ���� ���ؿ� �����Ͽ����ϴ�(����:%d, ����:%d)"
#define STR_W_NET03_1 "Established port(%s) session���� ��� ���ؿ� �����Ͽ����ϴ�(����:%d, ����:%d)"
#define STR_I_NET03_1 "Established port session���� �Ӱ�ġ ���Ϸ� ���͵Ǿ����ϴ�"
#define STR_I_NET03_2 "Established port session���� �Ӱ�ġ ���Ϸ� �����Դϴ�"

#define STR_F_NIC11_1 "������ �ʴ� IN PACKETS ���� FATAL ���ؿ� �����Ͽ����ϴ�.(����:%dpackets, ����:%.1fpackets)"
#define STR_C_NIC11_1 "������ �ʴ� IN PACKETS ���� ���� ���ؿ� �����Ͽ����ϴ�.(����:%dpackets, ����:%.1fpackets)"
#define STR_W_NIC11_1 "������ �ʴ� IN PACKETS ���� ��� ���ؿ� �����Ͽ����ϴ�.(����:%dpackets, ����:%.1fpackets)"
#define STR_F_NIC11_2 "������ �ʴ� OUT PACKETS ���� FATAL ���ؿ� �����Ͽ����ϴ�.(����:%dpackets, ����:%.1fpackets)"
#define STR_C_NIC11_2 "������ �ʴ� OUT PACKETS ���� ���� ���ؿ� �����Ͽ����ϴ�.(����:%dpackets, ����:%.1fpackets)"
#define STR_W_NIC11_2 "������ �ʴ� OUT PACKETS ���� ��� ���ؿ� �����Ͽ����ϴ�.(����:%dpackets, ����:%.1fpackets)"
#define STR_F_NIC11_3 "������ �ʴ� IN BYTES ���� FATAL ���ؿ� �����Ͽ����ϴ�.(����:%dKbps, ����:%.1fKbps)"
#define STR_C_NIC11_3 "������ �ʴ� IN BYTES ���� ���� ���ؿ� �����Ͽ����ϴ�.(����:%dKbps, ����:%.1fKbps)"
#define STR_W_NIC11_3 "������ �ʴ� IN BYTES���� ��� ���ؿ� �����Ͽ����ϴ�.(����:%dKbps, ����:%.1fKbps)"
#define STR_F_NIC11_4 "������ �ʴ� OUT BYTES ���� FATAL ���ؿ� �����Ͽ����ϴ�.(����:%dKbps, ����:%.1fKbps)"
#define STR_C_NIC11_4 "������ �ʴ� OUT BYTES ���� ���� ���ؿ� �����Ͽ����ϴ�.(����:%dKbps, ����:%.1fKbps)"
#define STR_W_NIC11_4 "������ �ʴ� OUT BYTES���� ��� ���ؿ� �����Ͽ����ϴ�.(����:%dKbps, ����:%.1fKbps)"
#define STR_I_NIC11_1 "������ �ʴ� Ʈ������ �Ӱ�ġ ���Ϸ� �����Դϴ�. IN(%.1fpackets, %.1fKbps), OUT(%.1fpackets, %.1fKbps)"
#define STR_I_NIC11_2 "������ �ʴ� Ʈ������ �Ӱ�ġ ���Ϸ� �����Դϴ�. IN(%.1fpackets), OUT(%.1fpackets)"
#define STR_C_NIC12_1 "������ Nic Traffic ��뷮�� ���� AUTO ACTION COMMAND(%s) ������ �����Ͽ����ϴ�"
#define STR_I_NIC12_1 "������ Nic Traffic ��뷮�� ���� AUTO ACTION COMMAND(%s)�� �����Ͽ����ϴ�"
#define STR_C_HWC01_1 "������ �¶��� CPU���� ���� �ʽ��ϴ�. (Logical<����:%dEa, ����:%dEa>)"
#define STR_C_HWC01_1_2 "������ �¶��� CPU���� ���� �ʽ��ϴ�. (Logical<����:%dEa, ����:%dEa>, Physical:%dEa)"
#define STR_C_HWC01_1_3_2 "������ �¶��� CPU���� �����Ͽ����ϴ�. (Logical<����:%dEa, ����:%dEa>, Physical:%dEa)"
#define STR_C_HWC01_1_3_2_1 "������ �¶��� CPU���� �����Ͽ����ϴ�. (Logical<����:%d~%dEa, ����:%dEa>, Physical:%dEa)"
#define STR_C_HWC01_1_3_1 "������ �¶��� CPU���� �����Ͽ����ϴ�. (Logical<����:%dEa, ����:%dEa>)"
#define STR_C_HWC01_1_3_1_1 "������ �¶��� CPU���� �����Ͽ����ϴ�. (Logical<����:%d~%dEa, ����:%dEa>)"
#define STR_W_HWC01_1_4_2 "������ �¶��� CPU���� �����Ͽ����ϴ�. (Logical<����:%dEa, ����:%dEa>, Physical:%dEa). ����͸� setting ���� �ڵ� �����մϴ�."
#define STR_W_HWC01_1_4_2_1 "������ �¶��� CPU���� �����Ͽ����ϴ�. (Logical<����:%d~%dEa, ����:%dEa>, Physical:%dEa). ����͸� setting ���� �ڵ� �����մϴ�."
#define STR_W_HWC01_1_4_1 "������ �¶��� CPU���� �����Ͽ����ϴ�. (Logical<����:%dEa, ����:%dEa>). ����͸� setting ���� �ڵ� �����մϴ�."
#define STR_W_HWC01_1_4_1_1 "������ �¶��� CPU���� �����Ͽ����ϴ�. (Logical<����:%d~%dEa, ����:%dEa>), ����͸� setting ���� �ڵ� �����մϴ�."
#define STR_W_HWC01_1_5 "������ �¶��� CPU�� ����͸��� �����Ͽ����ϴ�.('%s' Ȯ�� �ʿ�)"
#define STR_I_HWC01_1 "���� ���� H/W ���°� �����Դϴ�. (PROCESSOR<Logical>:%dEa, MEMORY:%dMBytes, ����µ�: %d��)"
#define STR_I_HWC01_1_2 "���� ���� H/W ���°� �����Դϴ�. (PROCESSOR<Logical/Physical>:%dEa/%dEa, MEMORY:%dMBytes, ����µ�: %d��)"
#define STR_I_HWC01_2 "���� ���� H/W ���°� �����Դϴ�. (PROCESSOR<Logical>:%dEa, MEMORY:%dMBytes)"
#define STR_I_HWC01_2_2 "���� ���� H/W ���°� �����Դϴ�. (PROCESSOR<Logical/Physical>:%dEa/%dEa, MEMORY:%dMBytes)"
/*#define STR_C_HWC02_1 "������ �������� MEMORY ����� ���� �ʽ��ϴ�(����:%d, ����:%d)"*/
#define STR_C_HWC02_1_1 "������ �������� MEMORY ����� �����Ͽ����ϴ�.(����:%dMBytes, ����:%dMBytes)"
#define STR_C_HWC02_1_2 "������ �������� MEMORY ����� �����Ͽ����ϴ�.(����:%d~%dMBytes, ����:%dMBytes)"
#define STR_W_HWC02_1_3 "������ �������� MEMORY ����� �����Ͽ����ϴ�(����:%dMBytes, ����:%dMBytes). ����͸� setting ���� �ڵ� �����մϴ�."
#define STR_W_HWC02_1_4 "������ �������� MEMORY ����� �����Ͽ����ϴ�(����:%d~%dMBytes, ����:%dMBytes). ����͸� setting ���� �ڵ� �����մϴ�."
#define STR_F_HWC03_1 "���� ���� �µ��� Fatal �����Դϴ�(����: %d��, ����: %d��)"
#define STR_C_HWC03_1 "���� ���� �µ��� ���� �����Դϴ�(����: %d��, ����: %d��)"
#define STR_W_HWC03_1 "���� ���� �µ��� ��� �����Դϴ�(����: %d��, ����: %d��)"

#define STR_C_SEC01_1 "���Ἲ ���� ��� ���� ����/���丮(%s)�� �������� �ʽ��ϴ�"
#define STR_C_SEC11_1 "���Ἲ ���� Command ��� ���� ����/���丮(%s)�� �������� �ʰų� ��� ������ �߸��Ǿ����ϴ�"
#define STR_C_SEC02_1 "���Ἲ ���� ��� ����(%s)�� SIZE�� ����Ǿ����ϴ�(����:%s Bytes, ����:%s Bytes)" 
#define STR_C_SEC02_1_1 "���Ἲ ���� ��� ���丮(%s)�� SIZE�� ����Ǿ����ϴ�(����:%s Kbytes, ����:%s Kbytes)" 
#define STR_C_SEC02_2 "���Ἲ ���� ��� ����(%s)�� OWNER�� ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC12_2 "���Ἲ ���� Command ��� ����(%s)�� OWNER�� ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC02_2_1 "���Ἲ ���� ��� ���丮(%s)�� OWNER�� ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC12_2_1 "���Ἲ ���� Command ��� ���丮(%s)�� OWNER�� ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC02_3 "���Ἲ ���� ��� ����(%s)�� GROUP�� ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC12_3 "���Ἲ ���� Command ��� ����(%s)�� GROUP�� ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC02_3_1 "���Ἲ ���� ��� ���丮(%s)�� GROUP�� ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC12_3_1 "���Ἲ ���� Command ��� ���丮(%s)�� GROUP�� ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC02_4 "���Ἲ ���� ��� ����(%s)�� ��尡 ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC12_4 "���Ἲ ���� Command ��� ����(%s)�� ��尡 ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC02_4_1 "���Ἲ ���� ��� ���丮(%s)�� ��尡 ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC12_4_1 "���Ἲ ���� Command ��� ���丮(%s)�� ��尡 ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC02_5 "���Ἲ ���� ��� ����(%s)�� ������ �������� ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC02_5_1 "���Ἲ ���� ��� ���丮(%s)�� ������ �������� ����Ǿ����ϴ�(����:%s, ����:%s)"
#define STR_C_SEC02_6 "������ ����(%s)�� Size�� �ִ� ������ ���� Ů���ϴ�. (����:%s Bytes, ����:%s Bytes)"
#define STR_C_SEC02_6_1 "������ ���͸�(%s)�� Size�� �ִ� ������ ���� Ů���ϴ�. (����:%s Kbytes, ����:%s Kbytes)"
#define STR_C_SEC02_6_2 "������ ����(%s)�� Size�� �ּ� ������ ���� �۽��ϴ�. (����:%s Bytes, ����:%s Bytes)"
#define STR_C_SEC02_6_3 "������ ���͸�(%s)�� Size�� �ּ� ������ ���� �۽��ϴ�. (����:%s Kbytes, ����:%s Kbytes)"
/*#define STR_C_SEC02_6 "���Ἲ ���� ��� ����(%s)�� SIZE�� ���� ���ؿ� �����Ͽ����ϴ�.(����:%d Bytes, ����:%d Bytes)" */
/*#define STR_C_SEC02_6_1 "���Ἲ ���� ��� ���丮(%s)�� SIZE�� ���� ���ؿ� �����Ͽ����ϴ�.(����:%d Kbytes, ����:%d Kbytes)" */
#define STR_C_SEC02_7_1 "���Ἲ ���� ��� ���丮(%s)�� File count�� ���� ���ؿ� �����Ͽ����ϴ�.(����:%d ��, ����:%ld ��)" 
#define STR_I_SEC02_1 "����/���丮 ���Ἲ check�� ���� ����Ǿ����ϴ�(����:%d)"
#define STR_C_TEP11_1	"������ �ֺ� ��ġ(CPU %d Temp)�� �µ� ���°� %s�Դϴ�. (Probe Name=%s)"
#define STR_C_TEP11_2	"������ �ֺ� ��ġ(CPU %d Temp)�� �µ��� ���� %.1f�ɷ� �����մϴ�. (Probe Name=%s)"
#define STR_W_TEP11		"������ �ֺ� ��ġ(CPU %d Temp)�� �µ��� ���� %.1f�ɷ� �������Դϴ�. (Probe Name=%s)"
#define STR_I_TEP11		"������ �ֺ� ��ġ�� �µ��� �����Դϴ�."

#define STR_C_BOT01		"������ ������ ���� �ð��� %s �Դϴ�. ( '%s' ��ɾ� ���� )"

/*#define STR_C_ACC11_1	"OS ���� %s�� �н����� �������� %d�� %.1f�ð� ���ҽ��ϴ�."*/
/*#define STR_C_ACC11_2	"OS ���� %s�� �н����� �������� %d�� %.1f�ð� �������ϴ�."*/
/*#define STR_W_ACC11		"OS ���� %s�� �н����� �������� %d�� %.1f�ð� ���ҽ��ϴ�.(���)"*/
#define STR_C_ACC11_1	"%s_Password_will_be_expired_@%s"
#define STR_C_ACC11_2	"%s_Password_has_expired_@%s"
#define STR_W_ACC11		"%s_Password_will_be_expired_@%s"
#define STR_I_ACC11		"OS�� ��� ������ �н����� �������� �����Դϴ�. (target=%d, active=%d, total=%d), (warn=%dday, crit=%dday)"


#endif
