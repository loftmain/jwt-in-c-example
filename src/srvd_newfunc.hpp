#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <time.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <openssl/hmac.h>

#include "IT.declare.h"

#define PGM_VER "2.0.1.0-20200916"
#define BACKLOG 	   10     /* how many pending connections queue will hold */
#define TRUE 	1
#define FALSE 	0

char it_home[256];
char it_itsm_ver[10];
char it_master[32];
char it_mainhost_ip[21];
char it_place[64];
char it_company[30];
char it_mode[5];
char it_data[256];
char *ipdot;
char login_user[51];
char host[101];
char buffer[4096];
char token[1024];

int maxlics2o = 0;
int ipport;
int time_gap = 0;
int ifilechkpt = -1;
int is_websocket = 0; // WebSocket 연결 여부를 저장할 플래그

long lfileposition = 0;

struct stat stbuf;
time_t readtime = 0;
time_t curtime = 0;
time_t g_tLMCnt;	/* 메세지 전송수 loging하기 위한 시간 관리 */
time_t g_tLastMsg;	/* 마지막 메세지 전송 시간 관리 */

struct  servent *servrec;       /* Service Entry Record */
struct  hostent *hostrec;       /* Host Entry Record */

/* socket variables */
int sockfd; /* listen on sock_fd, new connection on new_fd */
int new_fd; /* listen on sock_fd, new connection on new_fd */
int hostcount = 0;
socklen_t fromlen;
socklen_t peerlen;
struct sockaddr_in local;
struct sockaddr_in remote;
struct sockaddr_in peername;

FILE *fp = NULL;
/* 라이센스 수에 따라 제외되는 host */
struct lic_excepthost_struct{
	char hostname[80];
	char cocode[10];
} *plic_expthosts;

struct msgcnt_struct {
	int nT;		/* 전체 메세지수 */
	int nSI;	/* Console 전송 Information 수 */
	int nSC;	/* Console 전송 Critical 수 */
	int nSW;	/* Console 전송 Warning 수 */
	int nSP;	/* Console 전송 P 메세지 수 */
	int nSEtc;	/* Console 전송 기타 메세지 수 */
	int nFISYS;	/* Console 전송 예외된 ISYS 메세지 수(ISYS201 등) */
} g_pMCnt;		/* 메세지 전송수 저장에 사용됨 */

void exit_proc();
void rtn_sigpipe();
void send_to_console_nofilt(int sock);
int	 lost_chkpt(int sock); /* chkpt.cfg를 읽고 스위칭 되었으면 이전데이터 읽기 */
void freload(int sock);
void fcheck(int sock);
int is_AllowHost(char *v_rbuf);
char *generate_websocket_accept(const char *key);
int write_message(int fd, const char *message, int is_websocket_conn);

int srvd_newfunct() 
{
    int	ret = 0;
    char tmsg[256];
    char *msg = "ERR:S2O V1.0 >> Sorry! your IP address NOT permitted. <<\n";
    char timezone[64];

    // S2O_DAEMON = 데몬명
    memset(S2O_DAEMON, 0, sizeof(S2O_DAEMON));
    sprintf(S2O_DAEMON, "%s", SERVER);

    memset(timezone, 0, sizeof(timezone));
    update_timezone(timezone);

    if (!strcmp(timezone, "KST")) {
        it_loging("%s: daemon is started! (TIMEZONE=%s)\n", SERVER, timezone);
	} else if ( strlen(timezone) > 0) {
		it_loging("%s: daemon is started! (TIMEZONE=%s)\n", S2O_DAEMON, timezone);
    } else {
        it_loging("%s: daemon is started!\n", SERVER);
    }

    if (get_cfg("IT_HOME", it_home) < 0) {
        it_loging("%s: parameter(IT_HOME) read error!\n", SERVER);
        exit(1);
    }


    memset(it_itsm_ver, 0, sizeof it_itsm_ver);
    if (get_cfg("ITSM_VER", it_itsm_ver) < 0) {
        it_loging("%s: parameter(ITSM_VER) read error!\n", SERVER);
    }

    memset(it_master, 0, sizeof it_master);
    if (get_cfg("IT_MASTER", it_master) < 0) {   /* reserved */
        it_loging("%s: parameter(IT_MASTER) get error.\n", SERVER);
    }

    get_cfg("IT_MAINHOST_IP", it_mainhost_ip);

    memset(it_place, 0, sizeof it_place);
    if (get_cfg("IT_PLACE", it_place) < 0) {   /* reserved */
        it_loging("%s: parameter(IT_PLACE) get error.\n", SERVER);
    }

    if (get_cfg("IT_COMPANY_CODE", it_company) < 0) {
        it_loging("%s: get parameter(IT_COMPANY_CODE) error!\n", SERVER);
        exit(1);
    }

    /* license 확인 */
    ret = check_lic2(it_company, &maxlics2o);
    if ( ret < 0 ) {
        it_loging("%s: sorry, license expired!\n", SERVER);
        /*exit(1);*/
    } else if ( ret > 0 ) {
        /* 일: (ret/3600)/24, 시: (ret/3600)%24, 분: (ret%3600)/60 */
        it_loging("%s: The license will expire after %d days.\n", SERVER, (ret/3600)/24);
    }

    memset(it_mode, 0, sizeof it_mode);
    if (get_cfg("IT_MODE", it_mode) < 0) {
        it_loging("%s: parameter(IT_MODE) get error.\n", SERVER);
        exit(1);
    }

    if (strcmp(it_mode, "1"))  {
        it_loging("%s: agent is not master mode\n", SERVER);
		return(-1);
	}

    sprintf(it_data, "%s/IT.dat", it_home);

	it_loging("%s: ITSM_VER = %s\n", SERVER, it_itsm_ver);

	daemonize(SERVER, 1, PGM_VER);

    #if defined(DGUX)
        bsd_signal(SIGCHLD, SIG_IGN);
        bsd_signal(SIGINT, SIG_IGN);
        bsd_signal(SIGTERM, exit_proc);
        bsd_signal(SIGKILL, exit_proc);
        bsd_signal(SIGABRT, exit_proc);
        bsd_signal(SIGQUIT, exit_proc);
    #elif defined(LINUX)
        Signal(SIGCHLD, sig_chld);  
        signal(SIGINT, SIG_IGN);
        signal(SIGTERM, exit_proc);
        signal(SIGKILL, exit_proc);
        signal(SIGABRT, exit_proc);
        signal(SIGQUIT, exit_proc);
    #else
        signal(SIGCHLD, SIG_IGN);
        signal(SIGINT, SIG_IGN);
        signal(SIGTERM, exit_proc);
        signal(SIGKILL, exit_proc);
        signal(SIGABRT, exit_proc);
        signal(SIGQUIT, exit_proc);
    #endif
    signal(SIGPIPE, rtn_sigpipe);       /* main server의 IT.srvd가 KILL되거나  */
                                        /* LAN이 disconnect 되었을 경우        */
    
    gethostname(host, sizeof(host));
   	if ((hostrec = gethostbyname(host)) == NULL) {
      	it_loging("%s: gethostbyname host(%s) unknown!\n",SERVER,host);
      	exit(1);
    }

   	if ((servrec = getservbyname(PORT, "tcp")) == NULL) {
      	it_loging("%s: getserverbyname() error!\n", SERVER);
      	exit(1);
    }

   	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      	it_loging("%s: socket() create error!\n", SERVER);
      	exit(1);
    }

    /* socket port reuse if port waiting */
    {
        int one=1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(one));
    }

    local.sin_port = servrec->s_port;       				 /* Service Port */
   	memcpy(&local.sin_addr,hostrec -> h_addr, hostrec->h_length);
   	local.sin_family = hostrec->h_addrtype; 	   /* Address Type : AF_INET */
	local.sin_addr.s_addr = INADDR_ANY; 	/* automatically fill with my IP */

    if (bind(sockfd, (struct sockaddr *)&local, sizeof(local)) < 0) {
        it_loging("%s: bind() error!\n", SERVER);
        exit(1);
    }

    if (listen(sockfd, BACKLOG) < 0) {
        it_loging("%s: listen() error!\n", SERVER);
        exit(1);
    }

    plic_expthosts= (struct lic_excepthost_struct *) malloc (sizeof (struct lic_excepthost_struct));
    if (plic_expthosts == NULL) {
        it_loging("%s: plic_expthosts malloc error.\n", SERVER);
        exit(-1);
    }


    while (1) {
        memset(&remote, 0, sizeof(remote));
      	fromlen = sizeof(remote);
      	if ((new_fd = accept(sockfd, (struct sockaddr *)&remote, &fromlen)) < 0) {
         	it_loging("%s: <pid:%d> accept() error!\n", SERVER, getpid());
         	close(new_fd);
         	sleep(2);
         	continue;
        }

        ipdot = (char *) inet_ntoa(remote.sin_addr);
        ipport = ntohs(remote.sin_port);
        it_loging("%s: <pid:%d> Connect from client(%s:%d)\n", S2O_DAEMON, getpid(), ipdot, ipport);

        #ifdef DEBUG
        it_loging("%s: accepted\n", SERVER);
        #endif

        if (fork() == 0) { /* processor 가 child 이면 */
            close(sockfd);
            dup2(new_fd, 1);
            /* dup2(new_fd, 2); */

            /* license check  */
            ret = check_lic2(it_company, &maxlics2o);
			if ( ret < 0 ) {
				it_loging("%s: PID(%d) client(%s:%d) - sorry, license expired!\n", SERVER, getpid(), ipdot, ipport);
           		sprintf(tmsg, "ERR:sorry, license expired!\n");
           		write(1, tmsg, strlen(tmsg));
				sleep(1);
         		close(new_fd);
				exit(1);
			} else if ( ret > 0 ) {
				if ( (ret/3600)/24  < 30) {
					it_loging("%s: PID(%d) client(%s:%d) - The license will expire after %d days.\n", SERVER, getpid(), ipdot, ipport, (ret/3600)/24);
				}
			}

            // WebSocket 핸드세이크 확인 및 처리
            ssize_t n = recv(new_fd, buffer, sizeof(buffer) - 1, 0);
            if (n > 0) {
                buffer[n] = '\0';

                // WebSocket 요청인지 확인
				if (strstr(buffer, "Upgrade: websocket") && strstr(buffer, "Sec-WebSocket-Key:")) {
                    // JWT 프로토콜 추출
                    char * protocol_header = strstr(buffer, "Sec-WebSocket-Protocol: ");
                    if (protocol_header) {
                        sscanf(protocol_header + 24, "%s\r\n", token);
                        it_loging("Received JWT from Protocol: %s\n", token);

                        // JWT 토큰 검증
                        // 여기에 JWT 검증 로직 추가
                    } else {
                        // 프로토콜 헤더가 없을 경우 연결 거부
                        char *unauthorized_response = "HTTP/1.1 401 Unauthorized\r\n\r\n";
                        write(1, unauthorized_response, strlen(unauthorized_response));
                        it_loging("WebSocket Protocol (JWT) missing in WebSocket request.\n");
                        close(new_fd);
                        exit(1);
                    }

                    char *key_start = strstr(buffer, "Sec-WebSocket-Key:") + 19;
					char key[24];
					sscanf(key_start, "%s\r\n", key);
					it_loging("Received WebSocket Key: %s\n", key);

                    // WebSocket 키를 generate_websocket_accept 함수로 변환
					char *accept_key = generate_websocket_accept(key);

					// WebSocket 응답 생성 (Sec-WebSocket-Protocol 헤더 추가)
					char response[1024];
                    sprintf(response,
                            "HTTP/1.1 101 Switching Protocols\r\n"
                            "Upgrade: websocket\r\n"
                            "Connection: Upgrade\r\n"
                            "Sec-WebSocket-Accept: %s\r\n"
                            "Sec-WebSocket-Protocol: chat\r\n"
                            "\r\n", // 확장 비활성화
                            accept_key);

					// 핸드셰이크 응답 전송
					write(1, response, strlen(response));
					it_loging("%s: WebSocket handshake completed with protocol 'jwt'\n", SERVER);
					is_websocket = 1; // WebSocket 연결 플래그 설정
                }
            }

            memset(&peername, 0, sizeof(peername));
         	peerlen = sizeof(peername);
         	if (getpeername(new_fd,(struct sockaddr *)&peername,&peerlen) < 0) {
            	write(1, msg, strlen(msg));
            	close(new_fd);
            	it_loging("%s: PID(%d) client(%s:%d) - connection refused!\n", SERVER, getpid(), ipdot, ipport);
            	exit(1);
           	} else {
            	ipdot = (char *)inet_ntoa(peername.sin_addr);
				ipport = ntohs(peername.sin_port);
            	if (chkip(ipdot) < 0) {
               		write(1, msg, strlen(msg));
               		close(new_fd);
               		it_loging("%s: PID(%d), client(%s:%d) - Connection refused!\n", SERVER, getpid(), ipdot, ipport);
               		exit(1);
              	} else {
               		it_loging("%s: PID(%d), client(%s:%d) - Connection succeeded!\n", SERVER, getpid(), ipdot, ipport);
              	}
           	}

            #ifdef DEBUG
            it_loging("%s: PID(%d), client(%s:%d) - login_checking\n", SERVER, getpid(), ipdot, ipport);
            #endif

            it_loging("%s: PID(%d), client(%s:%d), id(%s) - console(nofilter) connection success!\n", SERVER, getpid(), ipdot, ipport, login_user); 
            send_to_console_nofilt(new_fd);

            close(new_fd);
        } else {
            close(new_fd);
        }

        /* clean up all child processes */
        while(waitpid(-1, NULL, WNOHANG) > 0);
    }


    return 0;
}

void exit_proc()
{	
	char	pidfile[256];

  	close(new_fd);
  	close(sockfd);
  	if (fp != NULL) 
		fclose(fp);

	sprintf(pidfile, "%s/pid/%s.pid", it_home, SERVER);
    unlink(pidfile);

  	it_loging("%s: PID(%d), client(%s:%d), id(%s) - daemon is terminated! (exit_proc())\n", SERVER, getpid(), ipdot, ipport, login_user);
  	exit(0);
}

void rtn_sigpipe()                                   /* signal SIGPIPE 처리  */
{
   	if (fp != NULL) fclose(fp);

   	it_loging("%s: PID(%d), client(%s:%d), id(%s) - connection closed!\n", SERVER, getpid(),ipdot, ipport, login_user);

   	exit(1);
}

/* mode : Console -> 모든 메세지가 Console로 send 됨.             */
/* type : type 1 ->  모든 회사 의 메세지가 filtering 없이 전송 됨 */
void send_to_console_nofilt(int sock)
{
  	int wn;
  	char v_rbuf[MSGSZ];
    time_t last_socket_check = 0;
  
  	if ((fp = fopen(it_data, "r")) == NULL)  {
     	it_loging("%s: PID(%d), client(%s:%d), id(%s) - send_to_console_nofilt() file(%s) open error!\n", SERVER, getpid(), ipdot, ipport, login_user, it_data);
     	close(sock);
     	return;
    }

    it_loging("%s: PID(%d), client(%s:%d), id(%s) - send_to_console_nofilt() file(%s) open success!\n", SERVER, getpid(), ipdot, ipport, login_user, it_data);

	lost_chkpt(sock);

  	fseek(fp, -2048, 2);
  	fgets(v_rbuf, 2047, fp);

	lfileposition = ftell(fp);

  	readtime = curtime = time(0);
    last_socket_check = time(0);
    
  	for ( ; ; ) {
		fseek(fp, lfileposition, SEEK_SET);
     	while (fgets(v_rbuf, MSGSZ-1, fp) != NULL) {
        	readtime = time(0);
			/*
        	stat(it_data, &stbuf);
        	f_size = stbuf.st_size;
			*/

			lfileposition = ftell(fp);

#ifdef DEBUG
			it_loging("%s: PID(%d), client(%s:%d) - send_to_console_nofilt() %s\n", SERVER, getpid(), ipdot, ipport, v_rbuf); 
#endif
			/* Incident messages일 경우 skip */
			/*
			if ((v_rbuf[0] == 'F') || (v_rbuf[0] == 'G'))
				continue;
			*/

			if (v_rbuf[0] == 'G') continue;

			/* it_useport = 'Y' 인 성능데이터 skip */
			if ((v_rbuf[0] == 'P') && (v_rbuf[5] == '1')) continue;
			if ((v_rbuf[0] == 'P') && (strncmp(v_rbuf, "PAVI", 4) && strncmp(v_rbuf, "POSI", 4))) continue;

			if (strlen(v_rbuf) > 2046 ) {
				v_rbuf[2046]='\n';
				v_rbuf[2047]='\0';
			}

            // WebSocket 연결 시, 메세지 전송
        	//wn = write(1, v_rbuf, strlen(v_rbuf));
            wn = write_message(1, v_rbuf, is_websocket);
        	if (wn < 0) { 
           		fclose(fp);
           		close(sock);
           		it_loging("%s: PID(%d), client(%s:%d), id(%s) - send_to_console_nofilt() connection closed!\n", SERVER, getpid(), ipdot, ipport, login_user);
           		exit(1);
          	}
            
            // 10초마다 소켓 상태 확인
            if (time(0) - last_socket_check >= 10) {
                char ping_buf[1] = {0};
                if (send(sock, ping_buf, 0, MSG_NOSIGNAL) < 0) {
                    fclose(fp);
                    close(sock);
                    it_loging("%s: PID(%d), client(%s:%d), id(%s) - send_to_console_nofilt() connection lost (socket check)!\n", 
                        SERVER, getpid(), ipdot, ipport, login_user);
                    exit(1);
                }
                last_socket_check = time(0);
            }
       	}

      	/* IT.dat의 size가 0으로 바뀔경우 fp point가 lost되는 */
      	/* 현상을 check함 */
      	curtime = time(0);
      	time_gap = curtime - readtime;

      	if (time_gap > 240) {
         	it_loging("%s: PID(%d), client(%s:%d) - TIME GAP 4분에 돌입함.\n", SERVER, getpid(), ipdot, ipport);
         	if (stat(it_data, &stbuf) == 0) {
            	time_gap = curtime - stbuf.st_mtime;
            	if(time_gap <= 240) {
               		readtime = curtime;
               		/*f_size = 0;*/
               		it_loging("%s: PID(%d), client(%s:%d), id(%s) - send_to_console_nofilt() 4분동안 input data를 읽지 못하여 freload()를 call함.\n", SERVER, getpid(), ipdot, ipport, login_user);
               		freload(sock);
              	}
           	} else {
            	readtime = curtime;
            	/*f_size = 0;*/
            	it_loging("%s: PID(%d), client(%s:%d), id(%s) - send_to_console_nofilt() 4분동안 input data를 읽지 못하여 freload() 를 call함.\n", SERVER, getpid(), ipdot, ipport, login_user);
            	freload(sock);
           	}
		} else 
			fcheck(sock);
        
        // 소켓 상태 추가 확인
      	if (time(0) - last_socket_check >= 10) {
            char ping_buf[1] = {0};
            if (send(sock, ping_buf, 0, MSG_NOSIGNAL) < 0) {
                fclose(fp);
                close(sock);
                it_loging("%s: PID(%d), client(%s:%d), id(%s) - send_to_console_nofilt() connection lost (socket check)!\n", 
                    SERVER, getpid(), ipdot, ipport, login_user);
                exit(1);
            }
            last_socket_check = time(0);
        }
        
      	sleep(1);
    }  /* read for end */ 
}

int lost_chkpt(int sock) /* chkpt.cfg를 읽고 스위칭 되었으면 이전데이터 읽기 */
{
	char tmpname[128];
	int seq_num;
	int row_num = 0;
	char file[128];
	char v_rbuf[MSGSZ];
  	int  i,	wn, send_flag = FALSE;
	int cnt_send = 0;
	int chgpt = 0;

	FILE *tfp;

	if (get_cfg("IT_SYSLOG_CHKPT", tmpname) < 0)
	{
		it_loging("%s: PID(%d), client(%s:%d), id(%s) - lost_chkpt() parameter(IT_SYSLOG_CHKPT) get error!\n", SERVER, getpid(), ipdot, ipport, login_user);
		ifilechkpt = - 1;
		return(-1);
	}

    seq_num = get_chkpt(tmpname);
    if(seq_num < 0) {
		it_loging("%s: PID(%d), client(%s:%d), id(%s) - get_chkpt() error!\n", SERVER, getpid(), ipdot, ipport, login_user);
		ifilechkpt = - 1;
		return(-1);
	}

	if(seq_num != ifilechkpt) /* 스위칭 되었는지 확인 */
	{
		if (ifilechkpt > -1) { /* 프로그램 실행시가 아니면 이전 데이터 읽기 */
			if ( lfileposition > 0 )
			{
                sleep(3);
                memset(file, 0, sizeof file);
                sprintf(file ,"%s/IT.%d", it_home, ifilechkpt);
                if ((tfp = fopen(file, "r")) == NULL) {
                    it_loging("%s: PID(%d), client(%s:%d), id(%s) - lost_chkpt() file(%s) open error!\n", SERVER, getpid(), ipdot, ipport, login_user, file);
                    return(2);
                } else {
					chgpt = 1;
                    it_loging("%s: PID(%d), client(%s:%d), id(%s) - lost_chkpt() file(%s) read start(%ld)\n", SERVER, getpid(), ipdot, ipport, login_user, file,lfileposition);
                    fseek(tfp, lfileposition, SEEK_SET);
                    while (fgets(v_rbuf, MSGSZ - 1, tfp) != NULL) {
                        /*
                        ** 'Information', 'Alarm stop'  messages skip check.
                        ** 'A', 'T' incident alarm stop messages.
                        ** 'Z' 마스터 콘솔 이벤트 clear.
                        */
                        row_num++;

						g_pMCnt.nT = 0;

            			/* Incident messages일 경우 skip */
            			/*
            				if (v_rbuf[0] == 'F' || v_rbuf[0] == 'G') continue;
            			*/

            			if (v_rbuf[0] == 'G') continue;

            			/* it_useport = 'Y' 인 성능데이터 skip */
            			if ((v_rbuf[0] == 'P') && (v_rbuf[5] == '1')) continue;
						if ((v_rbuf[0] == 'P') && (strncmp(v_rbuf, "PAVI", 4) && strncmp(v_rbuf, "POSI", 4))) continue;
						/*
            			if (!strncmp(v_rbuf, "PAVI", 4) || !strncmp(v_rbuf, "POSI", 4)) {
                			send_flag = TRUE;
            			} else {
						*/

							if ( is_valid_format(v_rbuf) < 0 ) continue;			
						
							send_flag = is_AllowHost(v_rbuf);
							
							/*

							memset(v_cocode, 0, sizeof v_cocode);
							memset(v_hostname, 0, sizeof v_hostname);

                			sscanf(v_rbuf, "%*s %s %*s %*s %*s %s", v_cocode, v_hostname);

                			send_flag = FALSE;
							if ((!strncmp(v_rbuf, "PAVI", 4) || !strncmp(v_rbuf, "POSI", 4))&&(!strcmp(v_cocode, it_company))) {
								send_flag = TRUE;
							} else {
                				for (i = 0; i < hostcount; i++) {
                    				if (!strcmp(v_hostname, allowHostname[i].hostname) &&
                        				!strcmp(v_cocode, allowHostname[i].co_code)) {
                        					send_flag = TRUE;
                        					break;
                    				}
								}
                			}
							*/
						/*
            			}
						*/

            			if (send_flag == FALSE) continue;
						if (strlen(v_rbuf) > 2047 ) v_rbuf[2047]='\0';

#ifdef DEBUG_WORK
			if ( !strncmp(v_rbuf, "ISYS", 4)) {
				if ( IS_IMPORT_ISYS(v_rbuf) == 0) {
					g_pMCnt.nFISYS = g_pMCnt.nFISYS+1;	
					continue;
				}
			}
#endif

						if ( v_rbuf[0] == 'I') g_pMCnt.nSI = g_pMCnt.nSI + 1;
						else if ( v_rbuf[0] == 'C') g_pMCnt.nSC = g_pMCnt.nSC + 1;
						else if ( v_rbuf[0] == 'W') g_pMCnt.nSW = g_pMCnt.nSW + 1;
						else if ( v_rbuf[0] == 'P') g_pMCnt.nSP = g_pMCnt.nSP + 1;
						else  g_pMCnt.nSEtc = g_pMCnt.nSEtc + 1;

            			wn = write(1, v_rbuf, strlen(v_rbuf));
            			if (wn < 1) {
                			fclose(fp);
                			close(sock);
                			it_loging("%s: PID(%d), client(%s:%d), id(%s) - lost_chkpt() connection closed!\n", SERVER, getpid(), ipdot, ipport, login_user);
                			exit(1);
            			}

						cnt_send++;

#ifdef DEBUG_WORK
						if ( time(0) - g_tLMCnt >= 5 * 60) {
#else
						if ( time(0) - g_tLMCnt >= 30 * 60) {
#endif
            				it_loging("%s: PID(%d), client(%s:%d), id(%s) - lost_chkpt() MSGCNT(%dsec) ( READ:%d, EXCEPT(ISYS):%d, SEND:%d - INFO:%d, CRITICAL:%d, WARNING:%d, P:%d, ETC:%d) \n", 
													SERVER, getpid(), ipdot, ipport, login_user, time(0) - g_tLMCnt,
													g_pMCnt.nT, g_pMCnt.nFISYS, g_pMCnt.nSI+g_pMCnt.nSC+g_pMCnt.nSW+g_pMCnt.nSP+g_pMCnt.nSEtc, 
													g_pMCnt.nSI, g_pMCnt.nSC, g_pMCnt.nSW, g_pMCnt.nSP, g_pMCnt.nSEtc);

							g_tLMCnt = time(0);
							g_pMCnt.nT = 0;
            				g_pMCnt.nSI = 0;
            				g_pMCnt.nSC = 0;
            				g_pMCnt.nSW = 0;
            				g_pMCnt.nSP = 0;
            				g_pMCnt.nSEtc = 0;	
            				g_pMCnt.nFISYS = 0;	
						}
                    }
                    it_loging("%s: PID(%d), client(%s:%d), id(%s) - lost_chkpt() file(%s) read end(%d)\n", SERVER, getpid(), ipdot, ipport, login_user, file, row_num);
                    fclose(tfp);

					if ( cnt_send > 0) g_tLastMsg= time(0);

                }
            } else {
                it_loging("%s: PID(%d), client(%s:%d), id(%s) - lost_chkpt() switch size error (%ld)\n", SERVER, getpid(), ipdot, ipport, login_user, lfileposition);
            }
        }
        ifilechkpt = seq_num;
        it_loging("%s: PID(%d), client(%s:%d), id(%s) - lost_chkpt() chkpt = %d\n", SERVER, getpid(), ipdot, ipport, login_user, ifilechkpt);
    }
	return(chgpt);
}

void freload(int sock)
{
    long file_size = 0;
	int chgpt = 0;

    fclose(fp);

    chgpt = lost_chkpt(sock); /* IT.dat가 switch 되었을 경우 이전 데이터 읽기 */

    if ((fp = fopen(it_data, "r")) == NULL)
    {
        it_loging("%s: PID(%d), client(%s:%d), id(%s) - freload() file(%s) open error! (freload())\n",SERVER, getpid(), ipdot, ipport, login_user, it_data);
        exit(1);
    }

	if(stat(it_data,&stbuf) == 0)
    {
        file_size = stbuf.st_size;
    }

    if ( file_size - lfileposition >= 0 ) {
        it_loging("%s: PID(%d), client(%s:%d), id(%s) - freload() It is determined that the IT.dat file has been regenerated, so an attempt is made to read the IT.dat file from the beginning, but the current size is larger than the last read size, so the program terminates. (file size : %ldB, read size %ldB)\n", SERVER, getpid(), ipdot, ipport, login_user,file_size, lfileposition);
        exit(1);
    } else if ( chgpt < 1 && file_size > 2000000) { /* 5000000:5MB, 2000000:2000KB */
        it_loging("%s: PID(%d), client(%s:%d), id(%s) - freload() It is determined that the IT.dat file has been recreated, so an attempt is made to read the IT.dat file from the beginning, but the program terminates because the size of the IT.dat file is over 2MB. (file size : %ldB, read size %ldB)\n", SERVER, getpid(), ipdot, ipport, login_user,file_size, lfileposition);
        exit(1);
    }

	lfileposition = 0;
	it_loging("%s: PID(%d), client(%s:%d), id(%s) - freload() file(%s) RE-open success.  (file size : %ldB, read size %ldB)\n", SERVER, getpid(), ipdot, ipport, login_user, it_data, file_size, lfileposition);
}

void fcheck(int sock)
{
	if (stat(it_data,&stbuf) == 0) {
      	/*if (f_size > stbuf.st_size) */
      	if (lfileposition > stbuf.st_size)
			freload(sock);
	}
   	else freload(sock);
}

int is_AllowHost(char *v_rbuf)
{
	int i;
	int seqnum;
	char *sptr;
  	char v_hostname[128], v_cocode[32];
	char tmpbuf[512];

	memset(v_cocode, 0, sizeof v_cocode);
	memset(v_hostname, 0, sizeof v_hostname);

	sscanf(v_rbuf, "%*s %s %*s %*s %*s %s", v_cocode, v_hostname);

	for (i = 0; i < hostcount; i++) {
		if (!strcmp(v_hostname, allowHostname[i].hostname) && !strcmp(v_cocode, allowHostname[i].co_code)) {
			if (!strncmp(v_rbuf, "PAVI", 4)) {
				tmpbuf[0] = v_rbuf[6];
				tmpbuf[1] = '\0';
				seqnum = atoi(tmpbuf);
				if (seqnum > -1 && seqnum < 10) {
					if (abs(time(0) - allowHostname[i].lastTmPAVI[seqnum]) >= 60 *60) {
						allowHostname[i].lastTmPAVI[seqnum] = time(0);
						return TRUE;
					} else {
						memset(tmpbuf, 0, sizeof tmpbuf);
						sscanf(v_rbuf, "%*s %*s %*s %*s %*s %*s %127c", tmpbuf);
						sptr = (char*)strchr(tmpbuf, '\n');	
						if (sptr != NULL) *sptr = '\0';
						sptr = (char*)strchr(tmpbuf, '\r');	
						if (sptr != NULL) *sptr = '\0';
						if (strcmp(tmpbuf, allowHostname[i].lastMsgPAVI[seqnum])) {
							allowHostname[i].lastTmPAVI[seqnum] = time(0);
							sprintf(allowHostname[i].lastMsgPAVI[seqnum], "%s\0", tmpbuf);
							return TRUE;
						}
					}
				}
			} else if ( !strncmp(v_rbuf, "POSI", 4)) {
				tmpbuf[0] = v_rbuf[6];
				tmpbuf[1] = '\0';
				seqnum = atoi(tmpbuf);
				if (seqnum > -1 && seqnum < 10) {
					if (abs(time(0) - allowHostname[i].lastTmPOSI[seqnum]) >= 60 *60) {
						allowHostname[i].lastTmPOSI[seqnum] = time(0);
						return TRUE;
					} else {
						memset(tmpbuf, 0, sizeof tmpbuf);
						sscanf(v_rbuf, "%*s %*s %*s %*s %*s %*s %127c", tmpbuf);
						sptr = (char*)strchr(tmpbuf, '\n');	
						if (sptr != NULL) *sptr = '\0';
						sptr = (char*)strchr(tmpbuf, '\r');	
						if (sptr != NULL) *sptr = '\0';
						sptr = (char*)strchr(tmpbuf, '#'); /* Linux itops05 2.4.20-8smp #1 SMP Thu Mar 13 17:45:54 EST 2003 i686 i686 i386 GNU/Linux */
						if (sptr != NULL) *sptr = '\0';  
						
						if (strcmp(tmpbuf, allowHostname[i].lastMsgPOSI[seqnum])) {
							allowHostname[i].lastTmPOSI[seqnum] = time(0);
							sprintf(allowHostname[i].lastMsgPOSI[seqnum], "%s\0", tmpbuf);
							return TRUE;
						}
					}
				}
			} else {
				return TRUE;
			}
			break;
		}
	}
	return FALSE;
}

char *generate_websocket_accept(const char *key)
{
	if (!key)
	{
		it_loging("%s: WebSocket key is NULL\n", SERVER);
		return NULL;
	}

	// 상수 정의
	static const char *GUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
	static const int SHA1_LENGTH = 20;

	// 메모리 할당
	char input[128] = {0}; // 키 + GUID를 저장할 충분한 공간
	unsigned char hash[SHA1_LENGTH];
	static char accept[29]; // Base64 인코딩된 결과 (24바이트) + null 종료자

	// 키와 GUID 결합
	if (snprintf(input, sizeof(input), "%s%s", key, GUID) >= sizeof(input))
	{
		it_loging("%s: WebSocket key too long\n", SERVER);
		return NULL;
	}

	// SHA1 해시 생성
	SHA1((unsigned char *)input, strlen(input), hash);

	// Base64 인코딩
	if (EVP_EncodeBlock((unsigned char *)accept, hash, SHA1_LENGTH) != 28)
	{
		it_loging("%s: Base64 encoding failed\n", SERVER);
		return NULL;
	}
	accept[28] = '\0'; // null 종료자 추가

#ifdef DEBUG
	it_loging("%s: WebSocket accept key generated: %s\n", SERVER, accept);
#endif

	return accept;
}

// WebSocket 메시지 전송 함수 추가
int write_message(int fd, const char *message, int is_websocket_conn)
{
	if (is_websocket_conn)
	{
		// 빈 라인이나 줄바꿈만 있는 라인 무시
		if (strlen(message) <= 1 || message[0] == '\n' || message[0] == '\r')
		{
			return 0;
		}

		// WebSocket 프레임 헤더 추가
		unsigned char frame[14]; // 최대 프레임 헤더 크기
		char websocket_msg[4096];
		int frame_size;
		int payload_len;
		char clean_msg[4096];

		// 줄바꿈 문자 제거
		strncpy(clean_msg, message, sizeof(clean_msg));
		clean_msg[strcspn(clean_msg, "\r\n")] = 0;

		// JSON 메시지 생성
		snprintf(websocket_msg, sizeof(websocket_msg),
				 "{\"type\":\"newLog\",\"data\":\"%s\"}", clean_msg);

		payload_len = strlen(websocket_msg);

		// 1. 기본 프레임 헤더 설정
		frame[0] = 0x81; // FIN(1) + RSV(000) + Opcode(0001 = text)

		// 2. 마스킹 비트는 0으로 설정 (서버에서 클라이언트로 보내는 메시지)
		if (payload_len <= 125)
		{
			frame[1] = payload_len;
			frame_size = 2;
		}
		else if (payload_len <= 65535)
		{
			frame[1] = 126;
			frame[2] = (payload_len >> 8) & 0xFF;
			frame[3] = payload_len & 0xFF;
			frame_size = 4;
		}
		else
		{
			frame[1] = 127;
			frame[2] = 0;
			frame[3] = 0;
			frame[4] = 0;
			frame[5] = 0;
			frame[6] = (payload_len >> 24) & 0xFF;
			frame[7] = (payload_len >> 16) & 0xFF;
			frame[8] = (payload_len >> 8) & 0xFF;
			frame[9] = payload_len & 0xFF;
			frame_size = 10;
		}

#ifdef DEBUG
		it_loging("%s: Sending WebSocket frame, payload length: %d\n",
				  SERVER, payload_len);
#endif

		// 프레임 헤더 전송
		if (write(fd, frame, frame_size) != frame_size)
		{
			it_loging("%s: Failed to write WebSocket frame header\n", SERVER);
			return -1;
		}

		// 페이로드 전송
		return write(fd, websocket_msg, payload_len);
	}
	else
	{
		return write(fd, message, strlen(message));
	}
}