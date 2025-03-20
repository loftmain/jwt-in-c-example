   /************************************************************************/
   /*  FILENAME     : store_errmsg.c                                       */
   /*  DISCRIPTION  : IT TOOL 에서 check 할 문자열을 얻는다.               */ 
   /*  DATE         : 2000. 08. 29                                         */
   /*  WRITTEN      : ywoopark                                             */
   /************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libuncs.h"

void store_errmsg()
{
	
   FILE *cmpbuf;
   char errbuf[256];
   count = 0;

   memset(errbuf, 0, sizeof errbuf);
   if((cmpbuf = fopen(CHKSTRING, "r")) == NULL) 
     {
      printf("File(%s) open error!!\n",CHKSTRING);
      exit(1);
      }
   while ((fgets(errbuf, 100, cmpbuf)) != NULL) 
     {
      sscanf(errbuf,"%s%s",errid[count],errmsg[count]);
      count++;
      }
   fclose(cmpbuf);
}
