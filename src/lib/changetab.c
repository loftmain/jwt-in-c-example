    /*********************************************************************/
    /*  MODULE         : changetab.c                                     */
    /*  DESCRIPTION    : tab character�� space 4���� ��ġ                */
    /*  RETURN         : int                                             */
    /*                   0 : success                                     */
    /*                  -1 : error                                       */
    /*  DATE           : 1998. 02. 10                                    */
    /*********************************************************************/

#include <stdio.h>
#include <string.h>

/* string src���� tab character�� ã�Ƽ� space 4���� ��ü�Ͽ� */
/* dest�� �ִ´�.                                             */
int changetab(char *src, char *dest)
{
   int i;
   char *tmp;

   if(src == NULL)   /* src�� NULL �̸� error */
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
