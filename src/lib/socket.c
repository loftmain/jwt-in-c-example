#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <setjmp.h>
#include <unistd.h>
#include <fcntl.h> 

#include "../IT.extern.h"

#if defined(HPUX)
#include <sys/time.h>
#else
#include <sys/time.h>
#include <sys/select.h>
#endif


static void connect_alarm(int);

struct servent *getservent();
struct hostent *gethostbyname();
char *inet_ntoa();

extern int it_loging(char *format,...);
extern int loging(char *msg,...);
extern char* get_sock_errno(int err_no);

int server1(sersock,portent)
int sersock;
char *portent;
{
   	int clisock;
  
   	struct sockaddr_in  Local;
   	struct sockaddr_in  Remote;
   	struct servent  *servrec;
   	struct hostent  *hostrec;
   
   	char host[64];
   	int len=0;

   	gethostname(host, sizeof(host));

  	/* Get Local Address  */
  	if((hostrec=gethostbyname(host)) == NULL) {
     	printf("[Server] Get Host failed.\n");
     	return(-1);
	}
   
  	/* Get Local Port Number defined in /etc/services */
  	if((servrec=getservbyname(portent, "tcp")) == NULL) {
     	printf("[Server] Get Service failed.\n");
     	return(-2);
	}

   	/* Initialize Local Socket structure */
   	Local.sin_port = servrec->s_port;           /* Service Port */
   	memcpy((char *)&Local.sin_addr,(char *)hostrec->h_addr, hostrec->h_length);
                                               /* Host Address */
   	Local.sin_family = hostrec->h_addrtype;     /* Address Type  */

  	if((sersock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
     	printf("[Server] Can't open stream socket.\n");
     	return(-3);
	}

  	if(bind(sersock, (struct sockaddr *)&Local, sizeof(Local)) < 0) {
     	printf("[Server] Can't bind local error.\n");
     	return(-4);
	}

  	if(listen(sersock, 5) < 0) {
     	printf("[Server] Listen error.\n");
     	return(-5);
	}
  	/* FD_SET(sersock,&allsock);  */
  	return(sersock);
}

int server2(clisock, portent)
int clisock;
char *portent;
{
   	int  sersock;
  
   	struct sockaddr_in  Local;
   	struct sockaddr_in  Remote;
   	struct servent  *servrec;
   	struct hostent  *hostrec;
   
   	char host[64];
   	int len=0;

   	gethostname(host, sizeof(host));

  	/* Get Local Address  */
  	if((hostrec=gethostbyname(host)) == NULL) {
     	printf("[Server] Get Host failed.\n");
     	return(-1);
	}
   
  	/* Get Local Port Number defined in /etc/services */
  	if((servrec=getservbyname(portent, "tcp")) == NULL) {
     	printf("[Server] Get Service failed.\n");
     	return(-2);
	}

   	/* Initialize Local Socket structure */
   	Local.sin_port = servrec->s_port;           /* Service Port */
   	memcpy((char *)&Local.sin_addr, (char *)hostrec->h_addr, hostrec->h_length);
                                               /* Host Address  */
   	Local.sin_family = hostrec->h_addrtype;     /* Address Type  */

  	if((sersock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
     	printf("[Server] Can't open stream socket.\n");
     	return(-3);
	}

  	if(bind(sersock, (struct sockaddr *)&Local, sizeof(Local)) < 0) {
     	printf("[Server] Can't bind local error.\n");
     	return(-4);
	}

  	if(listen(sersock, 5) < 0) {
     	printf("[Server] Listen error.\n");
     	return(-5);
	}

  	/* Initialize Remote address */
  	memset(&Remote, 0, sizeof(Remote));
  	len = sizeof(Remote);
  	clisock = accept(sersock, (struct sockaddr *)&Remote, &len);
  	if( clisock < 0) {
     	printf("[Server]Accept error.\n");
     	return(-6);
	}

  	return(sersock);
}


int client1(s,hostname, service)
int s;
char *hostname, *service;
{
   	struct sockaddr_in  remote;
   	struct servent  *servrec;
   	struct hostent  *hostrec;

  	if(( hostrec = gethostbyname(hostname)) == NULL) {
        loging("gethostbyname(): error occurred in socket.o!\n");
        return(-1);
	}
 
  	if ((servrec = getservbyname(service, "tcp")) == NULL) {
        loging("getserverbyname(): error occurred in socket.o!\n");
        return(-2);
	}

  	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        loging("socket(): error occurred in socket.o!\n");
        return(-3);
	}

  	remote.sin_port = servrec->s_port;       /* Service Port */
  	memcpy(&remote.sin_addr,hostrec -> h_addr, hostrec->h_length);
  	remote.sin_family = hostrec->h_addrtype; /* Address Type : AF_INET */

  	if(connect(s, (struct sockaddr *)&remote, sizeof(remote)) < 0) {
       loging("connect(): error occurred in socket.o!\n");
       return(-4);
	}
  	return(s);
}

int client3(hostname, service)
char *hostname, *service;
{
   	struct sockaddr_in  remote;
   	struct servent  	*servrec;
   	struct hostent  	*hostrec;
   	int 	s;
	/*struct linger solinger = { 1, 0 };*/

  	if ((hostrec = gethostbyname(hostname)) == NULL) {
        it_loging("libIT.a(%s): client3() socket gethostbyname(%s) error(%s)\n", S2O_DAEMON, hostname, get_sock_errno(errno));
        return(-1);
	}
  	if ((servrec = getservbyname(service, "tcp")) == NULL) {
        it_loging("libIT.a(%s): client3() socket getservbyname(%s) error(%s)\n", S2O_DAEMON, service, get_sock_errno(errno));
        return(-1);
	}
  	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        it_loging("libIT.a(%s): client3() socket error(%s), host(%s), port(%s)!\n", S2O_DAEMON, get_sock_errno(errno), hostname, service);
        return(-1);
	}

	/*setsockopt(s, SOL_SOCKET, SO_LINGER, &solinger, sizeof(struct linger));*/

  	remote.sin_port = servrec->s_port;       				/* Service Port */
  	memcpy(&remote.sin_addr,hostrec -> h_addr, hostrec->h_length);
  	remote.sin_family = hostrec->h_addrtype;  	  /* Address Type : AF_INET */

  	if (connect(s,(struct sockaddr *)&remote, sizeof(remote)) < 0) {
        it_loging("libIT.a(%s): client3() socket connect() error(%s), host(%s), port(%s)!\n", S2O_DAEMON, get_sock_errno(errno), hostname, service);
        close(s);
        return(-1);
	}
  	return(s);
}


int connect_timeo(char *hostname, char *service, int nsec)
{
	Sigfunc *sigfunc;

   	struct 	sockaddr_in  remote;
   	struct 	servent  *servrec;
   	struct 	hostent  *hostrec;
   	int 	n, s;

	if (strlen(hostname) == 0) {
        it_loging("%s: libIT.a: connect_timeo() hostname is null\n", S2O_DAEMON, hostname);
        return(-11);
	}

  	if (( hostrec = gethostbyname(hostname)) == NULL) {
        it_loging("%s: libIT.a: connect_timeo() socket gethostbyname(%s) error(%s).\n", S2O_DAEMON, hostname, get_sock_errno(errno));
        return(-11);
	}
  	if ((servrec = getservbyname(service, "tcp")) == NULL) {
        it_loging("%s: libIT.a: connect_timeo() socket getserverbyname(%s) error(%s).\n", S2O_DAEMON, service, get_sock_errno(errno));
        return(-12);
	}
  	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        it_loging("%s: libIT.a: connect_timeo() socket socket() error(%s).\n", S2O_DAEMON, get_sock_errno(errno));
        return(-13);
	}

  	remote.sin_port = servrec->s_port;       /* Service Port */
  	memcpy(&remote.sin_addr,hostrec -> h_addr, hostrec->h_length);
  	remote.sin_family = hostrec->h_addrtype; /* Address Type : AF_INET */

	sigfunc = Signal(SIGALRM, connect_alarm);
	if (alarm(nsec) != 0) {
		/* it_loging("%s: libIT.a: connect_timeo() connect_timeo alarm was already set.\n", S2O_DAEMON); */
		;
	}

  	if ((n = connect(s, (struct sockaddr *)&remote, sizeof(remote))) < 0) {
		close(s);
		if (errno == EINTR)
			errno = ETIMEDOUT;
       	it_loging("%s: libIT.a: connect_timeo() socket connect(%s, %s) error(%s).\n", S2O_DAEMON, hostname, service, get_sock_errno(errno));
	}

	alarm(0);					/* turn off the alarm */
	Signal(SIGALRM, sigfunc);	/* restore previous signal handler */
	
	if (n < 0)
		return(n);
	else
		return(s);
}

int connect_timeon(char *hostname, int port, int nsec)
{
	Sigfunc *sigfunc;

   	struct 	sockaddr_in  remote;
   	struct 	servent  *servrec;
   	struct 	hostent  *hostrec;
   	int 	n, s;

  	if (( hostrec = gethostbyname(hostname)) == NULL) {
        it_loging("libIT.a(%s): connect_timeon()  socket gethostbyname(%s) error(%s).\n", S2O_DAEMON, hostname, get_sock_errno(errno));
        return(-11);
	}
  	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        it_loging("libIT.a(%s): connect_timeon() socket socket() error(%s).\n", S2O_DAEMON, get_sock_errno(errno));
        return(-13);
	}

  	remote.sin_port = htons(port);       /* Service Port */
  	memcpy(&remote.sin_addr,hostrec -> h_addr, hostrec->h_length);
  	remote.sin_family = hostrec->h_addrtype; /* Address Type : AF_INET */

	sigfunc = Signal(SIGALRM, connect_alarm);
	if (alarm(nsec) != 0) {
		/* it_loging("libIT.a(%s): connect_timeon() connect_timeo alarm was already set.\n", S2O_DAEMON); */
		;
	}

  	if ((n = connect(s, (struct sockaddr *)&remote, sizeof(remote))) < 0) {
		close(s);
		if (errno == EINTR)
			errno = ETIMEDOUT;
       	it_loging("libIT.a(%s): connect_timeon() socket connect(%s, %d) error(%s).\n", S2O_DAEMON, hostname, port, get_sock_errno(errno));
	}

	alarm(0);					/* turn off the alarm */
	Signal(SIGALRM, sigfunc);	/* restore previous signal handler */
	
	if (n < 0)
		return(n);
	else
		return(s);
}

static void
connect_alarm(int signo)
{
	return;     /* just interrupt the connect() */
}

static void
connect_alarm2(int signo)
{
	return;     /* just interrupt the connect() */
}

int connect_timeo2(char *hostname, char *service, int nsec)
{
	Sigfunc *sigfunc;

   	struct 	sockaddr_in  remote;
   	struct 	servent  *servrec;
   	struct 	hostent  *hostrec;
   	int 	n, s;

  	if (( hostrec = gethostbyname(hostname)) == NULL) {
        it_loging("libIT.a(%s): connect_timeo2() socket gethostbyname(%s) error(%s).\n", S2O_DAEMON, hostname, get_sock_errno(errno));
        return(-11);
	}
  	if ((servrec = getservbyname(service, "tcp")) == NULL) {
        it_loging("libIT.a(%s): connect_timeo2() socket getserverbyname(%s) error(%s).\n", S2O_DAEMON, service, get_sock_errno(errno));
        return(-12);
	}
  	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        it_loging("libIT.a(%s): connect_timeo2() socket socket() error(%s).\n", S2O_DAEMON, get_sock_errno(errno));
        return(-13);
	}

  	remote.sin_port = servrec->s_port;       /* Service Port */
  	memcpy(&remote.sin_addr,hostrec -> h_addr, hostrec->h_length);
  	remote.sin_family = hostrec->h_addrtype; /* Address Type : AF_INET */

	sigfunc = Signal(SIGALRM, connect_alarm2);
	if (alarm(nsec) != 0) {
		/* it_loging("libIT.a(%s): connect_timeo2() alarm was already set.\n", S2O_DAEMON); */
		;
	}

  	if ((n = connect(s, (struct sockaddr *)&remote, sizeof(remote))) < 0) {
		close(s);
		if (errno == EINTR)
			errno = ETIMEDOUT;
       	it_loging("libIT.a(%s): connect_timeo2() socket connect(%s, %s) error(%s).\n", S2O_DAEMON, hostname, service, get_sock_errno(errno));
	}

	alarm(0);					/* turn off the alarm */
	Signal(SIGALRM, sigfunc);	/* restore previous signal handler */
	
	if (n < 0)
		return(n);
	else
		return(s);
}

int connect_timeo3(char* checkhost, char *hostname, char *service, int nsec)
{
	Sigfunc *sigfunc;

   	struct 	sockaddr_in  remote;
   	struct 	servent  *servrec;
   	struct 	hostent  *hostrec;
   	int 	n, s;
	/*struct linger solinger = { 1, 0 };*/

  	if (( hostrec = gethostbyname(hostname)) == NULL) {
        it_loging("libIT.a(%s): connect_timeo3() <%s> socket gethostbyname(%s) error(%s).\n", S2O_DAEMON, checkhost, hostname, get_sock_errno(errno));
        return(-11);
	}
  	if ((servrec = getservbyname(service, "tcp")) == NULL) {
        it_loging("libIT.a(%s): connect_timeo3() <%s> socket getserverbyname(%s) error(%s).\n", S2O_DAEMON, checkhost, service, get_sock_errno(errno));
        return(-12);
	}
  	/*if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {*/
  	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        it_loging("libIT.a(%s): connect_timeo3() <%s> socket socket() error(%s).\n", S2O_DAEMON, checkhost, get_sock_errno(errno));
        return(-13);
	}

	/*setsockopt(s, SOL_SOCKET, SO_LINGER, &solinger, sizeof(struct linger));*/

  	remote.sin_port = servrec->s_port;       /* Service Port */
  	memcpy(&remote.sin_addr,hostrec -> h_addr, hostrec->h_length);
  	remote.sin_family = hostrec->h_addrtype; /* Address Type : AF_INET */

	sigfunc = Signal(SIGALRM, connect_alarm);
	if (alarm(nsec) != 0) {
		/* it_loging("libIt.a(%s): connect_timeo3() <%s> connect_timeo alarm was already set.\n", S2O_DAEMON); */
		;
	}

  	if ((n = connect(s, (struct sockaddr *)&remote, sizeof(remote))) < 0) {
		close(s);
		if (errno == EINTR)
			errno = ETIMEDOUT;
       	it_loging("libIT.a(%s): connect_timeo3() <%s> socket connect(%s, %s) error(%s).\n", S2O_DAEMON, checkhost, hostname, service, get_sock_errno(errno));
	}

	alarm(0);					/* turn off the alarm */
	Signal(SIGALRM, sigfunc);	/* restore previous signal handler */
	
	if (n < 0)
		return(n);
	else
		return(s);
}

#if defined(__TEST__)
int ConnectWait( char *hostname, char *service, int nsec)
{ 
	/* 정확히 작동되지 않음 */

    int newSockStat; 
    int orgSockStat; 
    int res, n; 
    fd_set  rset, wset; 
    struct timeval tval; 
 
    int error = 0; 
    int esize; 
   	struct 	sockaddr_in  remote;
   	struct 	servent  *servrec;
   	struct 	hostent  *hostrec;
	int sockfd;

  	if (( hostrec = gethostbyname(hostname)) == NULL) {
        it_loging("libIT.a(%s): ConnectWait() %s - socket gethostbyname(%s) error(%s).\n", S2O_DAEMON, hostname, hostname, get_sock_errno(errno));
        return(-11);
	}
  	if ((servrec = getservbyname(service, "tcp")) == NULL) {
        it_loging("libIT.a(%s): ConnectWait() %s - socket getserverbyname(%s) error(%s).\n", S2O_DAEMON, hostname, service, get_sock_errno(errno));
        return(-12);
	}
  	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        it_loging("libIT.a(%s): ConnectWait() %s - socket socket() error(%s).\n", S2O_DAEMON, hostname, get_sock_errno(errno));
        return(-13);
	}

  	remote.sin_port = servrec->s_port;       /* Service Port */
  	memcpy(&remote.sin_addr,hostrec -> h_addr, hostrec->h_length);
  	remote.sin_family = hostrec->h_addrtype; /* Address Type : AF_INET */
 
    if ( (newSockStat = fcntl(sockfd, F_GETFL, NULL)) < 0 )  
    { 
        it_loging("libIT.a(%s): ConnectWait() %s - F_GETFL error(%s)\n", S2O_DAEMON, hostname, get_sock_errno(errno)); 
        return -1; 
    } 
 
    orgSockStat = newSockStat; 
    newSockStat |= O_NONBLOCK; 
 
    /* Non blocking 상태로 만든다.  */
    if(fcntl(sockfd, F_SETFL, newSockStat) < 0) 
    { 
        it_loging("libIT.a(%s): ConnectWait() %s - F_SETLF error(%s)\n", S2O_DAEMON, hostname, get_sock_errno(errno)); 
        return -1; 
    } 
 
    /* 연결을 기다린다. */
    /* Non blocking 상태이므로 바로 리턴한다. */
    if((res = connect(sockfd, (struct sockaddr *)&remote, sizeof(remote))) < 0) 
    { 
        if (errno != EINPROGRESS) {
			close(sockfd);
			it_loging("libIT.a(%s): ConnectWait() %s - EINPROGRESS. error(%s)\n", S2O_DAEMON, hostname, get_sock_errno(errno));
			return -1; 
		}
    } 
 
    it_loging("libIT.a(%s): ConnectWait() %s - socket(%d) RES : %d\n", S2O_DAEMON, hostname, sockfd, res); 
    /* 즉시 연결이 성공했을 경우 소켓을 원래 상태로 되돌리고 리턴한다.  */
    if (res == 0) 
    { 
        it_loging("libIT.a(%s): ConnectWait() %s - Connect Success. error(%s)\n", S2O_DAEMON, hostname, get_sock_errno(errno)); 
        fcntl(sockfd, F_SETFL, orgSockStat); 
        return 1; 
    } 
 
    FD_ZERO(&rset); 
    FD_SET(sockfd, &rset); 
    wset = rset; 
 
    tval.tv_sec    = nsec;     
    tval.tv_usec    = 0; 
 
	usleep(10000);

	it_loging("libIT.a(%s): ConnectWait() %s - socket(%d) timeout begin.(%s)\n", S2O_DAEMON, hostname, sockfd, get_sock_errno(errno));
   /* if ( (n = select((sockfd), &rset, &wset, NULL, &tval)) == 0) */
    /* if ( (n = select((sockfd)+1, &rset, &wset, NULL, NULL)) == 0) */
    if ( (n = select((sockfd)+1, &rset, &wset, NULL, &tval)) == 0) 
    { 
        /* timeout */
        errno = ETIMEDOUT;     
		close(sockfd);
		it_loging("libIT.a(%s): ConnectWait() %s - ETIMEDOUT. error(%s)\n", S2O_DAEMON, hostname,get_sock_errno(errno));
        return -1; 
    } 
 
    /* 읽거나 쓴 데이터가 있는지 검사한다.  */
    if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset) ) 
    { 
        esize = sizeof(int); 
		usleep(10000);
        if ((n = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&esize)) < 0)  {
			close(sockfd);
			it_loging("libIT.a(%s): ConnectWait() %s - getsockopt error(%s)\n", S2O_DAEMON, hostname, get_sock_errno(errno));
            return -1; 
		}
    	it_loging("libIT.a(%s): ConnectWait() %s - Read data error(%d,%d). error(%s)\n", S2O_DAEMON, hostname, error, errno, get_sock_errno(errno)); 

		if ( error == 0) {
			usleep(100000);
        	if ((n = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&esize)) < 0)  {
				close(sockfd);
				it_loging("libIT.a(%s): ConnectWait() %s - getsockopt error(%s)\n", S2O_DAEMON, hostname, get_sock_errno(errno));
           	 return -1; 
			}
    		it_loging("libIT.a(%s): ConnectWait() %s - Read data error(%d,%d). error(%s)\n", S2O_DAEMON, hostname, error, errno, get_sock_errno(errno)); 
		}
    } 
    else 
    { 
		close(sockfd);
        it_loging("libIT.a(%s): ConnectWait() %s - Socket Not Set. error(%s)\n", S2O_DAEMON, hostname, get_sock_errno(errno)); 
        return -1; 
    } 
 
    fcntl(sockfd, F_SETFL, orgSockStat); 
    if(error) 
    { 
        errno = error; 
		close(sockfd);
        it_loging("libIT.a(%s): ConnectWait() %s - Socket fcntl error(%s)\n", S2O_DAEMON, hostname, get_sock_errno(errno)); 
        return -1; 
    } 
	return sockfd; 
    /* return 1; */
} 
#endif
