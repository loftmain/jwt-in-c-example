    /*********************************************************************/
    /*  MODULE         : chkip.c                                         */
    /*  DESCRIPTION    : client의 ip permission을 체크한다.              */
    /*  NOTICE         : 이 함수는 $IT_HOME/ipallow.cfg가 필요함.        */
    /*  RETURN         : int                                             */
    /*                   0 : permission OK.                              */
    /*                  -1 : permission ERROR.                           */
    /*  DATE           : 1998. 02. 03                                    */
    /*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>

extern int get_cfg(char* ENV, char* value);
extern int loging(char *msg,...);

int chkip(char *arg)
{
   char *s;
   char buf[256];
   char it_home[100], it_ipconf[150];
   FILE *kfp;
   int kflag=0;
   
   memset(it_home,0,sizeof(it_home));
   if(get_cfg("IT_HOME", it_home) < 0)
     {
      loging("chkip(): parameter(IT_HOME) error!\n");
      exit(1);
      }

   memset(it_ipconf,0,sizeof(it_ipconf));
   sprintf(it_ipconf,"%s/ipallow.cfg",it_home);

   if(arg == NULL)
     return(-1);
   if((kfp = fopen(it_ipconf,"r")) == NULL)
     {
      loging("file(%s) open error!\n",it_ipconf);
      return(-1);    /* file 이 없을 경우  */
      }
   else
     {
      memset(buf,0,sizeof buf);
      while(fgets(buf,256,kfp) != NULL)
        {
         if((buf[0] == '#') || (buf[0] == '\n') || (buf[0] == ' '))
           continue;
         if(buf[0] == '*')
           {
            fclose(kfp);
            return(0);
           }
         s = (char *)strrchr(buf,'\n');
         if(s != NULL)
           *s = '\0';
         if(!strncmp(buf,arg, strlen(buf)))
           ++kflag;
         memset(buf,0,sizeof buf);
         }
      fclose(kfp);
      if(kflag != 0)
        return(0);
      else
        return(-1);
      }
}
