#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int getitem(int ch, char *src, char *dest, int seqitem)
{
  	char 	*sptr, *dptr, *s;
  	int 	cnt;

  	if (strlen(src) < 2)
     	return(-1);

  	sptr = src;
  	dptr = dest;

  	if (seqitem < 1)
    	return(-1);

  	cnt = 1;
  	while (*sptr && (cnt <= seqitem)) {
    	if ((*sptr == ch) || (*sptr == '\r') || (*sptr == '\n'))
       		cnt++, sptr++;
    	else {
       		while (*sptr && (cnt == seqitem)) {
         		if ((*sptr == ch) || (*sptr == '\r') || (*sptr == '\n'))
            		cnt++;
         	 	else
            		*dptr++ = *sptr++;
        	}
       		if (*sptr == (char) NULL)
          		break;
       		else
          		sptr++;
      	}
   	}
  	if (strlen(dest) == 0)
     	return(-1);
  	else
     	return(0);
}

int getitemc(int ch, char *src)
{
  	char 	*sptr, *s;
  	int 	cnt = 0;

  	if (strlen(src) < 2)
     	return(-1);

  	sptr = src;

  	while (*sptr) 
	{
    	if (*sptr == ch) 
       		cnt++, sptr++;
    	else 
			sptr++;
   	}
  	return(cnt);
}

int getitem_end(int ch, char *src, char *dest, int seqitem)
{
  	char 	*sptr, *s;
  	int 	cnt = 1;

	if (seqitem <= 1) strcpy(dest, src);

  	sptr = src;

  	while (*sptr) 
	{
    	if (*sptr == ch) {
       		cnt++, sptr++;
			if (cnt == seqitem) strcpy(dest, sptr);
    	} else {
			sptr++;
		}
   	}
  	return(cnt);
}
