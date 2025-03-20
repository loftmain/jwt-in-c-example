/*
   $Id: fcopy.c,v 1.8 2003/11/26 srp Exp $

   Copyright (c) 2000, 2001, 2002
             i-TOP System Inc.  All rights reserved.
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int fcopy(char *src, char *dest, mode_t pmode)
{
  	int fdin, fdout, n;
  	char buf[1024];

  	if ((fdin = open(src, O_RDONLY)) == -1) 
     	return(-1);

  	if ((fdout = open(dest, O_WRONLY|O_CREAT|O_TRUNC, pmode)) == -1) {
		close(fdin);
     	return(-2);
	}
    
  	while ((n = read(fdin, buf, 1024)) > 0) {
     	if (write(fdout, buf, n) < 0) {     
  			close(fdin);
  			close(fdout);
        	return(-3);
        }
	}
  	chmod(dest, pmode); 
  	close(fdin);
  	close(fdout);
  	return(0);
}
