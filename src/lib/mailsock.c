#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

void socket_close();
extern int Readable_timeo(int fd, int sec);
extern int it_loging(char *format,...);
extern char S2O_DAEMON[64];

int smconnect(char *host, int port)
{
	int s, n, str_len;
	char recvbuf[2048], return_code[50] /* return_code[4] */ ;
	char tmp_recvbuf[2048];
	char tmp_return_code[128];

    struct sockaddr_in remote;
	struct hostent *he;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		it_loging("libIT.a(%s): smconnect() host(%s,%d) - socket create fail.\n", S2O_DAEMON, host, port); 
		return (-1);
	}

	remote.sin_port = htons(port);
	remote.sin_family = AF_INET;

	if ((he = gethostbyname(host)) == NULL) {
		it_loging("libIT.a(%s): smconnect() host(%s,%d) - gethostbyname fail.\n", S2O_DAEMON, host, port); 
		return (-1);
	}
	/*remote.sin_addr.s_addr = inet_addr(host);*/
	remote.sin_addr =*((struct in_addr *)he->h_addr);

	if ((n = connect(s, (struct sockaddr *) &remote,sizeof(remote))) < 0) {
		it_loging("libIT.a(%s): smconnect() host(%s,%d) - connect fail.\n", S2O_DAEMON, host, port); 
		return (-1);
	}

    if (Readable_timeo(s, 12) < 0) { /* SBW recv 값이 늦는error로 추가 */
		it_loging("libIT.a(%s): smconnect() host(%s,%d) - Readable_timeo fail.\n", S2O_DAEMON, host, port); 
        close(s);
        return(-1);
    }

	/*signal(SIGALRM, socket_close);*/

	memset(tmp_recvbuf, 0, sizeof tmp_recvbuf);
	memset(return_code, 0, sizeof return_code);
	
	while (1) {
		signal(SIGALRM, socket_close);
		alarm(2);
		memset(recvbuf, 0x00, sizeof recvbuf);
		str_len = recv(s, recvbuf, 2047, 0);
		memset(tmp_return_code, 0, sizeof tmp_return_code);
		sscanf(recvbuf, "%s", tmp_return_code);
		/*it_loging("libIT.a(%s): smconnect() mailsock recvbuf -> %s: (%d), %s\n", S2O_DAEMON, tmp_return_code, str_len, recvbuf); */
		if (str_len <= 0) {
			alarm(0);
			break;
		}

		alarm(0);

		if ( strlen(tmp_return_code) > 0) {
			memset(return_code, 0, sizeof return_code);
			strcpy(return_code, tmp_return_code);
			memset(tmp_recvbuf, 0, sizeof tmp_recvbuf);
			strcpy(tmp_recvbuf, recvbuf);
			if(tmp_recvbuf[strlen(tmp_recvbuf)] == '\n') tmp_recvbuf[strlen(tmp_recvbuf)] = '\0';
		}
	}

    if (strncmp(return_code, "220", 3)) {
		it_loging("libIT.a(%s) : smconnect() mailsock recv code error. recvbuf -> %s\n", S2O_DAEMON, tmp_recvbuf); 
		close(s);
		return (-1);
	}
	
	return s;
}

int smsend(int s, char *sndbuf, char *code)
{
	int str_len;
	int cnt = 0; 
	char recvbuf[2048], return_code[50]/*return_code[4]*/;
	char tmp_return_code[128];
	char tmp_recvbuf[2048];

	if (send(s, sndbuf, strlen(sndbuf), 0) == -1) {
		it_loging("libIT.a(%s): smsend() - send fail.\n", S2O_DAEMON); 
		return -1;
	}

    if (Readable_timeo(s, 10) < 0) { /* SBW recv 값이 늦는error로 추가 */
        /*close(s);*/
		it_loging("libIT.a(%s): smsend() - Readable_timeo fail.\n", S2O_DAEMON); 
        return(-1);
    }

	/* signal(SIGALRM, socket_close); */

/*
	속도 향상이 필요한 경우 return_code와 code 가 동일한 경우 break 필요
*/
	
	memset(tmp_recvbuf, 0, sizeof tmp_recvbuf);
	memset(return_code, 0, sizeof return_code);
	while (1) {
		signal(SIGALRM, socket_close); 
		if (!strncmp(return_code, code, 3)) {
			alarm(1);
		} else {
			alarm(2);
		}
		memset(recvbuf, 0x00, sizeof recvbuf);
		str_len = recv(s, recvbuf, 2047, 0);
		memset(tmp_return_code, 0, sizeof tmp_return_code);
		sscanf(recvbuf, "%s", tmp_return_code);
		/*it_loging("libIT.a(%s): smsend() recvbuf -> %s: (%d), %s\n", S2O_DAEMON, tmp_return_code, str_len,recvbuf);*/
		if (str_len <= 0) {
			alarm(0);
			if (cnt == 0) { /* 메세지가 delay되는 경우가 발생하여 1초 sleep 후 다시 확인하도록 추가 */
				sleep(1);
				cnt++;
				continue;
			} else {
				break;
			}
		}
		alarm(0);

		if ( strlen(tmp_return_code) > 0) {
			memset(return_code, 0, sizeof return_code);
			strcpy(return_code, tmp_return_code);
			memset(tmp_recvbuf, 0, sizeof tmp_recvbuf);
			strcpy(tmp_recvbuf, recvbuf);
			if(tmp_recvbuf[strlen(tmp_recvbuf)] == '\n') tmp_recvbuf[strlen(tmp_recvbuf)] = '\0';
			/* 속도향상을 위해 여기서 break 할수 도 있음 */
			break;
		}
	}

	if (strncmp(return_code, code, 3)) {
		it_loging("libIT.a(%s): smsend() recv code error -> (retcode:%s, setcode:%s), recvbuf :%s\n", S2O_DAEMON, return_code, code, tmp_recvbuf); 
		return -1;
	}

	return 0;
}

void socket_close()
{
	/* it_loging("libIT.a(%s): socket_close() sock_close\n", S2O_DAEMON);*/
	;
}
