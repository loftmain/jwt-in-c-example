    /*********************************************************************/
    /*  MODULE         : changetab.c                                     */
    /*  DESCRIPTION    : tab character를 space 4개로 대치                */
    /*  RETURN         : int                                             */
    /*                   0 : success                                     */
    /*                  -1 : error                                       */
    /*  DATE           : 1998. 02. 10                                    */
    /*********************************************************************/

#include <stdio.h>
#include <string.h>

/* string src에서 tab character를 찾아서 space 4개로 교체하여 */
/* dest에 넣는다.                                             */
int changetab(char *src, char *dest)
{
   int i;
   char *tmp;

   if(src == NULL)   /* src가 NULL 이면 error */
     return(-1);
   tmp = dest;
   do{
      if(*src == '\t')
         for(i=0; i<4; i++)
            *tmp++ = ' ';
      else
         *tmp++ = *src;
     }while(*src++);   
   *tmp = '\0';
   return(0);
}

int change_token(char *src, char token, char dtoken)
{
	char *sptr, *tmp;

	if (src == NULL)  return(-1);

	sptr = (char *)strchr(src, token);
	if (sptr == NULL) return(-1);

	do {
		if(*src == token) *src = dtoken;
	}while(*src++);   
	return 0;
}
