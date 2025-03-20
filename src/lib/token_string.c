#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int token_string(char *src, char *var, char *val);

/* 소스(src)에서 변수(var)의 값을 분리하여 val에 return */
/* return code : error    -1 */
/*               no value 0  */
/*               normal   1  */

int token_string(char *src, char *var, char *val)
{
  char *sptr, *ptr;
  char tsrc[256], tbuf[256];

  if(strlen(src) < 3)
     return(-1);

  memset(tsrc, 0, sizeof tsrc);
  strcpy(tsrc, src);
  sptr = (char *)strchr(tsrc, '=');
  if(sptr == NULL) return(-1);

  memset(var, 0, sizeof var);
  sscanf(sptr + 1, "%s", var);
  if(strlen(var) == 0) return(-1);

  memset(val, 0, sizeof val);
  sscanf(sptr+1, "%s", val);
  if(val[0] == 0) return(0);

  if(val[0] != '"')
    {
     if(val[strlen(val) - 1] != '"') return(1);
     else return(-1);
    }
  else
    {
     ptr = (char *)strchr(sptr+1, '"');
     if(ptr == NULL) return(-1);

     memset(tbuf, 0, sizeof tbuf);
     strcpy(tbuf, ptr+1);

     ptr = (char *)strchr(tbuf, '"');
     if(ptr == NULL) return(-1);

     *ptr = '\0';

     memset(val, 0, sizeof val);
     strcpy(val, tbuf);
     return(1);
    }
}

