#include "config.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/param.h>

#if defined(HPUX)
#include <sys/unistd.h>     
#include <sys/pstat.h>
#define BURST ((size_t)10)
int get_hppsargs(char *fpath);
#endif

int prscnt(int flag, char *prs);
int ux_prscnt(int flag, char *prs);
int hp_prscnt(int flag, char *prs);

int prscnt(int flag, char *prs)
{
#if defined(HPUX)
   return(hp_prscnt(flag, prs));
#else
   return(ux_prscnt(flag, prs));
#endif
}

#define PSCMD "/usr/bin/ps -eo args"
int ux_prscnt(int flag, char *prs)
{
  FILE *pfp;
  char tbuf[1024], *sptr;
  int pcount = 0;

  memset(tbuf, 0, sizeof tbuf);
  sprintf(tbuf, "%s", PSCMD);

  if((pfp=popen(tbuf,"r")) == NULL)
    {
     printf("ps(%s) command error!\n", PSCMD);
     return(-1);
    }

  memset(tbuf, 0, sizeof tbuf);
  while(fgets(tbuf, 1024, pfp) != NULL)
   {
    if(flag == 0)
      {
       sptr = (char *)strstr(tbuf, prs);
       if(sptr != NULL)
          pcount++;
      }
    else
      {
#if defined(AIX)
       tbuf[strlen(tbuf) -2] = '\0';
#else
       tbuf[strlen(tbuf) -1] = '\0';
#endif
       if(!strcmp(prs, tbuf))
          pcount++;
      }
   }
  pclose(pfp);
  return(pcount);
}


int hp_prscnt(int flag, char *prs)
{
  int pcount = 0;
#if defined(HPUX)
  struct pst_status pst[BURST];
  int i, count;
  int idx = 0; /* index within the context */
  char *sptr;

  /* loop until count == 0, will occur all have been returned */
  while((count = pstat_getproc(pst, sizeof(pst[0]), BURST, idx)) > 0)
    {
     /* got count (max of BURST) this time.  process them */
     for(i = 0; i < count; i++)
       {
        if(flag == 0)
          {
           sptr = (char *)strstr(pst[i].pst_cmd, prs);
           if(sptr != NULL)
              pcount++;
          }
        else
          {
           if(!strcmp(prs, pst[i].pst_cmd))
              pcount++;
          }
       }

     /*
     * now go back and do it again, using the next index after
     * the current 'burst'
     */
     idx = pst[count-1].pst_idx + 1;
    }

  if(count == -1)
     return(-1);
#endif
  return(pcount);
}
