#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* nnn.nnn.nnn.nnn format check */
int is_valid_ip(char *str)
{
  int point = 0, n;
  char tmps[10];
  char *ptr;

  memset(tmps, 0, sizeof tmps);
  ptr = tmps;
  while(*str)
    {
     if(!isdigit(*str)) /* 숫자가 아니면 */
       {
  	if(*str == '.')
          {
           if(tmps[0] != 0) /* tmps에 data가 있으면 */
             {
   	      n = atoi(tmps);
              if((n < 0) || (n > 255)) return(-1); /*ip의 각 field는 0 - 255*/      
             }
           memset(tmps, 0, sizeof tmps);
           ptr = tmps;
           point++;  /* .의 갯수가 3 인지를 check하기 위해 */
          }
	else return(-1);
       }
     else *ptr++ = *str;
     str++;
    }	
  if(point != 3) return(-1);
  if(tmps[0] != 0) /* tmps에 data가 있으면 */
    {
     n = atoi(tmps);
     if((n < 0) || (n > 255)) return(-1);	       
    }
  return(0);
}
