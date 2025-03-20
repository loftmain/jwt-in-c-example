#include <stdio.h>
#include <string.h>
#include <ctype.h>

static char* kstrupr(char *str);
int ora_encrypt(char *name, char *passwd, char *answer);

int ora_encrypt(char *name, char *passwd, char *answer)
{
  char *upname, *uppasswd, *v_str, v_chr;
  int i;
  char I_offset, I_root, I_shift, I_char;
  int I_position;
  char I_answer[256];
  int value;

  if((strlen(name) < 3) || (strlen(passwd) > 30))
      return(-1);
  if((strlen(name) > 30) || (strlen(passwd) > 30))
      return(-2);

  upname = kstrupr(name);
  uppasswd = kstrupr(passwd);

  v_str = upname;
  while(*v_str)
    {
     if((*v_str < 65) || (*v_str > 90))
        *v_str = 65 + (*v_str % 24);
     v_str++; 
    }

  v_str = uppasswd;
  while(*v_str)
    {
     if((*v_str < 65) || (*v_str > 90))
        *v_str = 65 + (*v_str % 24);
     v_str++; 
    }

  I_offset = *(upname + 1);

  v_str = uppasswd;
  while(*v_str++) ;
  I_root = *(v_str - 2);

  v_str = upname;
  while(*v_str++) ;
  I_shift = *(v_str - 2);
  I_shift = I_shift % 13;

  memset(I_answer, 0, sizeof I_answer);
  strcpy(I_answer, upname);
  strcat(I_answer, uppasswd);
  
  I_position = 1;

  for(i = 1; i <= 30; i++)
    {
     if(strlen(I_answer) >= 30)
        break;
  
     value = I_shift + I_offset + i;
     if(value > 90)
       {
        value = value % 24;
        value = value + 65;
        I_shift = value;
       }
     else I_shift = value;

     I_char = I_shift;

     if(I_position == 1)
       {
        memset(answer, 0, sizeof answer);
        strcpy(answer, I_answer);
        answer[strlen(answer)] = I_char;
        memset(I_answer, 0, sizeof I_answer);
        strcpy(I_answer, answer);
        I_position = 0;
       }
     else
       {
        memset(answer, 0, sizeof answer);
        answer[0] = I_char;
        strcpy(answer+1, I_answer);
        memset(I_answer, 0, sizeof I_answer);
        strcpy(I_answer, answer);
        I_position = 1;
       }
    }

  i = 1;
  v_str = I_answer;
  while(*v_str)
    {
     value = *v_str + I_root + i;
     if(value > 90)
       {
        value = value % 24;
        value = value + 65;
        *v_str = value;
       }
     v_str++; 
     i++;
    }
  memset(answer, 0, sizeof answer);
  strcpy(answer, I_answer);
  return(0);
}

static char* kstrupr(char *str)
{
  int len, i;
  char *rtn;
  len=strlen(str);
  for(i=0; i<len; i++)
      str[i] = toupper(str[i]);
  return((char* )strdup(str));
}

