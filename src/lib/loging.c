   /************************************************************************/
   /*  FILENAME     : loging.c                                             */
   /*  DISCRIPTION  :                                                      */
   /*  DATE         : 2000. 08. 30                                         */
   /*  MODIFIED     : 2000. 08. 30                                         */
   /*  WRITTEN      : ywoopark                                             */
   /************************************************************************/

#include "config.h"
#include <sys/types.h>
#include <sys/param.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif
#include <signal.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include "../IT.extern.h"

int loging(char *msg,...);

int loging(char *msg,...)
{
  va_list argptr;	
  MSGQ sbuf;
  int msqid, i, flag=0;
  char tmsg[2048], *bmsg, mmsg[2048];

  if (IS_NOS2O_AGENT == 1) return 0;

  if((msqid=msgget(keyl, 0666)) <0)
    return(-2);

  memset(tmsg,0,sizeof tmsg);
  va_start(argptr,msg);
  vsprintf(tmsg,msg,argptr);
  va_end(argptr);

  /* \n delete */
  memset(mmsg,0,sizeof mmsg);
  bmsg = mmsg;
  for(i=0; i<strlen(tmsg); i++)
    {
     if(tmsg[i] != '\n')
       {
        *bmsg = tmsg[i];
        bmsg++;
       }
    }

  sbuf.mtype = 1;
  sprintf(sbuf.mtext,"%s\n",mmsg);
  if(msgsnd(msqid,&sbuf,strlen(sbuf.mtext) + 1,IPC_NOWAIT) < 0)
     return(-1);
  else return(0);
}
