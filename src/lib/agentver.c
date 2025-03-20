#include "config.h"
#include <stdio.h>
#include <sys/errno.h>
#include "../IT.extern.h"
#if defined(SUN2)
#include <sys/systeminfo.h>
#endif

/*
 * usage - print the command line args options
 */
void agentver()
{
	int 	long ret;
	char 	buf[256], si_machine[10];

#if defined (LINUX)
	sprintf(buf, "$Id: S2O(Linux) Agent Version %s srp Exp $", S2O_VERSION);
#elif defined (SUN2)
	if (( ret = sysinfo(SI_MACHINE, si_machine, sizeof(si_machine))) == -1) {
		sprintf(si_machine, "SunOS");
	}
	sprintf(buf, "$Id: S2O(%s) Agent Version %s srp Exp $", si_machine, S2O_VERSION);
#elif defined (AIX)
	sprintf(buf, "$Id: S2O(AIX) Agent Version %s srp Exp $", S2O_VERSION);
#elif defined (HPUX)
	sprintf(buf, "$Id: S2O(HP-UX) Agent Version %s srp Exp $", S2O_VERSION);
#elif defined (NCRUX)
	sprintf(buf, "$Id: S2O(UNIX_SV) Agent Version %s srp Exp $", S2O_VERSION);
#elif defined (DGUX)
	sprintf(buf, "$Id: S2O(OSF1) Agent Version %s srp Exp $", S2O_VERSION);
#endif
	fprintf(stderr, "Version: %s\n", buf);
}
