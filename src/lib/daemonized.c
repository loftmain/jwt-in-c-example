/*
   $Id: daemonize.c,v 1.7 2003/05/28 srp Exp $

   Copyright (c) 2000, 2001, 2002, 2003
             i-TOP System Inc.  All rights reserved.

   2002-05-28
*/
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

void daemonized()
{
	int 	i;
	int ret;

	if (getppid() == 1) return; 			/* already a daemon */
	i = fork();
	if (i < 0) exit(1); 					/* fork error */
	if (i > 0) exit(0); 					/* parent exits */

	/* child (daemon) continues */
	setsid(); 								/* obtain a new process group */
	for (i = getdtablesize(); i >= 0; --i) close(i); /* close all descriptors */
	i = open("/dev/null", O_RDWR); ret=dup(i); ret=dup(i); 	 /* handle standart I/O */
	umask(027); 					/* set newly created file permissions */
	ret=chdir("/"); 					/* change running directory */
}

/* EOF */


