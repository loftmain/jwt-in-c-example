#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int expand_env(char *src, char *dest);
int expand_sub_env(char *src, char *dest);

extern int getitem(int ch, char *src, char *dest, int seqitem);

/* DESC: /usr/lib:$ORACLE_HOME/bin....  형태의 value에서 */
/*       $ORACLE_HOME을 원래의 값으로 변환               */
int expand_env(char *src, char *dest)
{
  char tsrc[2048], tdest[2048], tbuf[2100];
  int i;

  for(i = 1; ; i++)
   {
    memset(tsrc, 0, sizeof tsrc);
    if(getitem(':', src, tsrc, i) < 0) break;
    if(tsrc[0] == '$')
      {
       memset(tdest, 0, sizeof tdest);
       if(expand_sub_env(tsrc + 1, tdest) < 0)
          continue;
       if(dest[0] == 0) strcpy(dest, tdest);
       else 
         {
          memset(tbuf, 0, sizeof tbuf);
          sprintf(tbuf, ":%s", tdest);
          strcat(dest, tbuf);
         }
      }
    else
      {
       if(dest[0] == 0) strcpy(dest, tsrc);
       else 
         {
          memset(tbuf, 0, sizeof tbuf);
          sprintf(tbuf, ":%s", tsrc);
          strcat(dest, tbuf);
         }
      }
   }
  return(0);
}

int expand_sub_env(char *src, char *dest)
{
  char tbuf[1024];
  char *s, *tmp, *d, *tenv;
  int enable = 1;

  tmp = tbuf;
  memset(tbuf, 0, sizeof tbuf);

  d = dest;
  s = src;
  while(*s)
   {
    if(*s == '/')
      {
       enable = 0;
       if(tbuf[0] != 0)
         {
          tenv = getenv(tbuf);
          if(tenv == NULL) return(-1);
          while(*tenv) *d++ = *tenv++;
          memset(tbuf, 0, sizeof tbuf);
         }
       *d++ = *s;
      }
    else
      {
       if(enable == 1) *tmp++ = *s;
       else *d++ = *s;
      }
    s++;
   }
  return(0);
}
