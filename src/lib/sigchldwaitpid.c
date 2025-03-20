#include <sys/types.h>
#include <sys/wait.h>

void
sig_chld(int signo)
{
    pid_t   pid;
    int     stat;

    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) {
		;
        /* it_loging("libIT.a(%s): sig_chld() child %d terminated\n", S2O_DAEMON, pid); */
	}
    return;
}

