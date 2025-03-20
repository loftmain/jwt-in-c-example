      /*----------------------------------------------------------------
      *  function name: search_space()
      *  description  : n���� space���� �ǳ� �� �� ������ ���ڿ��� 
      *                 return  
      *  history     :
      *        2000. 04. 17  initial program
      *----------------------------------------------------------------*/

#include <stdio.h>

char *search_point(int ch, char *s, int post)  /* Linux2.6.18 x86_64 IT.wrtd���� ���� �߻� */
{
  	int chr = 0, cnt = 0;

  	while(*s) {
    	if(*s == ch) {
       		if(chr == 1) {
          		cnt++;
          		chr = 0;
         	}
      	} else {
      		chr = 1;
      		if(cnt == post)
         	return(s);
     	}
   		s++;
   	}
  	return(NULL);
}

int search_point2(int ch, char *s, int post)
{
  	int chr = 0, cnt = 0;
	int num = 0;

  	while(*s) {
    	if(*s == ch) {
       		if(chr == 1) {
          		cnt++;
          		chr = 0;
         	}
      	} else {
      		chr = 1;
      		if(cnt == post) return(num);
     	}
   		s++;
		num++;
   	}
  	return(-1);
}
