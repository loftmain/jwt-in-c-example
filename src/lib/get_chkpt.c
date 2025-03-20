   /************************************************************************/
   /*  FILENAME     : get_chkpt.c                                          */
   /*  DISCRIPTION  : arg에서 chk를 읽어서 return                          */
   /*  DATE         : 1998. 12. 28                                         */
   /*  WRITTEN      : ywoopark                                             */
   /*  MODIFIED     : ywoopark , 1998. 12. 28                              */
   /************************************************************************/

#include "config.h"
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include "../IT.extern.h"

extern int loging(char *msg,...);

int get_chkpt(char *f_name)
{
   FILE *fp;
   int sernum;
   int ret;

   if((fp=fopen(f_name,"r")) == NULL)
     {
      loging("file(%s) open error!\n",f_name);
      return(-1);
     }
   ret = fscanf(fp,"%d", &sernum);
   fclose(fp);
   if(sernum < 0)
      return(-1);
   return(sernum);
}
