#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* base table */
const unsigned char atab[63] =
      "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const unsigned char btab[63] =
      "X1Hx6B2NcUYn9ibwCIhMuV7GtAa8WjQJmEyvlsTOgK50ZdkPoSe3DzpLf4FqRr";

/* extended table */
const unsigned char tab1[63] =
      "UXyDVxzdL1EeWKfowQMp3nv0RAa9CJmcNblFqTkrO2YIgBsZ8htS7j4u6PiH5G";
const unsigned char tab2[63] =
      "yDVzdL1EeWfQxMp3nBc0RgAaT9CJmI4NbGloFKqXvkrwO2YHUZ5htS7ju6Pi8s";
const unsigned char tab3[63] =
      "1Hx62NcUnibCIhMuV7GXtADyBaWjwJ8rfY9EvlsTOkK50dPQmoSe3Lgzp4ZFqR";
const unsigned char tab4[63] =
      "DzdL1EeWKfUmwQMp3nv0RAVao9CxJcNXb4lFHTykZrO2YI5gBGsq8htS7jPu6i";
const unsigned char tab5[63] =
      "Hx2NcUnbCIhM1u7GXt6ADiyBdaWjwJ8rfYvlsTOVk9K5R0PQmqoSeE3Lgzp4ZF";

int etc_subdecrypt(char *src, char *dest);

int etc_decrypt(char *src, char *dest)
{
   char tbuf[256], tmpb[100];
   char *s1, *s2;
   int cflag, i, j, n, szlen;
   int value, value1, value2;
   int n_table, n_post, n_szlen;
   char s_table[3], s_post[3], s_szlen[3];

   szlen = strlen(src);
   if(szlen != 30) return(-1);

   memset(tbuf, 0, sizeof tbuf);
   if(etc_subdecrypt(src, tbuf) < 0)
      return(-1);

   memset(tmpb, 0, sizeof tmpb);
   strncpy(tmpb, tbuf+25, 5);
   s1 = tmpb;
   i = 1;
   while(*s1)
     {
      n = i % 5;
      if(n == 0)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == tab1[j])
               {
                *s1 = atab[j];
                break;
               }
            }
        }
      if(n == 1)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == tab2[j])
               {
                *s1 = atab[j];
                break;
               }
            }
        }
      if(n == 2)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == tab3[j])
               {
                *s1 = atab[j];
                break;
               }
            }
        }
      if(n == 3)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == tab4[j])
               {
                *s1 = atab[j];
                break;
               }
            }
        }
      if(n == 4)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == tab5[j])
               {
                *s1 = atab[j];
                break;
               }
            }
        }
      s1++;
      i++;
     }

   memset(s_szlen, 0, sizeof s_szlen);
   strncpy(s_szlen, tmpb+3, 2);
   n_szlen = atoi(s_szlen);

   strncpy(dest, tbuf, n_szlen);
   s1 = dest;
   i = 1;
   while(*s1)
     {
      n = i % 5;
      if(n == 0)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == tab1[j])
               {
                *s1 = atab[j];
                break;
               }
            }
        }
      if(n == 1)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == tab2[j])
               {
                *s1 = atab[j];
                break;
               }
            }
        }
      if(n == 2)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == tab3[j])
               {
                *s1 = atab[j];
                break;
               }
            }
        }
      if(n == 3)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == tab4[j])
               {
                *s1 = atab[j];
                break;
               }
            }
        }
      if(n == 4)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == tab5[j])
               {
                *s1 = atab[j];
                break;
               }
            }
        }
      s1++;
      i++;
     }
   return(0);
}

int etc_subdecrypt(char *src, char *dest)
{
   char tbuf[256];
   char *s1, *s2;
   int cflag, i;

   strcpy(dest, src);
   s1 = dest;
   cflag = 0;
   while(*s1)
    {
     for(i = 0; i < 62; i++)
        {
         if(*s1 == btab[i])
           {
            cflag++;
            *s1 = atab[i]; 
            break;
           }
        }
     if(cflag == 0) *s1 = '9';
     cflag = 0;
     s1++;
    }
  return(0);
}
