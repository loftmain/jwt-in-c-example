   /************************************************************************/
   /*  FILENAME     : error_log.c                                          */
   /*  DISCRIPTION  : error logging                                        */
   /*  DATE         : 1997. 05. 19                                         */
   /*  WRITTEN      : stmpywb                                              */
   /************************************************************************/

#include <stdio.h>

void error_log(char *msg)
{
  FILE *fp;
  if((fp=fopen("/var/IT.log","a")) == NULL)
     {
      fprintf(stderr,"file(/var/IT.log) open error!\n");
  	fprintf(fp,"%s\n",msg);
  fclose(fp);
      return;
     }
  fprintf(fp,"%s\n",msg);
  fclose(fp);
}
