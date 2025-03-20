#include <stdio.h>
#include <string.h>

/* base table */
const unsigned char en_atab[63] =
      "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const unsigned char en_btab[63] =
      "X1Hx6B2NcUYn9ibwCIhMuV7GtAa8WjQJmEyvlsTOgK50ZdkPoSe3DzpLf4FqRr";

/* extended table */
const unsigned char en_tab1[63] =
      "UXyDVxzdL1EeWKfowQMp3nv0RAa9CJmcNblFqTkrO2YIgBsZ8htS7j4u6PiH5G";
const unsigned char en_tab2[63] =
      "yDVzdL1EeWfQxMp3nBc0RgAaT9CJmI4NbGloFKqXvkrwO2YHUZ5htS7ju6Pi8s";
const unsigned char en_tab3[63] =
      "1Hx62NcUnibCIhMuV7GXtADyBaWjwJ8rfY9EvlsTOkK50dPQmoSe3Lgzp4ZFqR";
const unsigned char en_tab4[63] =
      "DzdL1EeWKfUmwQMp3nv0RAVao9CxJcNXb4lFHTykZrO2YI5gBGsq8htS7jPu6i";
const unsigned char en_tab5[63] =
      "Hx2NcUnbCIhM1u7GXt6ADiyBdaWjwJ8rfYvlsTOVk9K5R0PQmqoSeE3Lgzp4ZF";

int etc_subencrypt(char *src, char *dest);

int etc_encrypt(char *src, char *dest)
{
   char tbuf[256], tmpb[100];
   char *s1, *s2;
   int cflag, i, j, n, szlen;
   int value, value1, value2;
   int n_table, n_post, n_szlen;
   char s_table[3], s_post[3], s_szlen[3];

   n_szlen = strlen(src);
   if((n_szlen < 1) || (n_szlen > 30))
      return(-1);

   value = 0;
   s1 = src;
   while(*s1)
     {
      value = value + *s1;
      s1++;
     }

   value1 = value % 5;
   if(value1 == 0) n_post = 0;
   else if(value1 == 1) n_post = 6;
   else if(value1 == 2) n_post = 12;
   else if(value1 == 3) n_post = 18;
   else if(value1 == 4) n_post = 24;
   else n_post = 0;

   value2 = value % 3;
   if(value == 0) n_table = 0;
   else if(value == 1) n_table = 1;
   else if(value == 2) n_table = 2;
   else n_table = 0;

   /* src scramble  */
   i = 1;
   s1 = src;
   while(*s1)
     {
      n = i % 5;
      if(n == 0)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == en_atab[j])
               {
                *s1 = en_tab1[j];
                break;
               }
            }
        }
      if(n == 1)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == en_atab[j])
               {
                *s1 = en_tab2[j];
                break;
               }
            }
        }
      if(n == 2)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == en_atab[j])
               {
                *s1 = en_tab3[j];
                break;
               }
            }
        }
      if(n == 3)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == en_atab[j])
               {
                *s1 = en_tab4[j];
                break;
               }
            }
        }
      if(n == 4)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == en_atab[j])
               {
                *s1 = en_tab5[j];
                break;
               }
            }
        }
      s1++;
      i++;
     }

   memset(tbuf, 0, sizeof tbuf);
   strcpy(tbuf, src);
  
   if(n_table == 0)
      strncat(tbuf, en_tab1 + n_post, 30 - strlen(src) - 5);
   else if(n_table == 1)
      strncat(tbuf, en_tab2 + n_post, 30 - strlen(src) - 5);
   else if(n_table == 2)
      strncat(tbuf, en_tab3 + n_post, 30 - strlen(src) - 5);

   memset(tmpb, 0, sizeof tmpb);
   sprintf(tmpb, "%d%2.2d%2.2d", n_table, n_post, n_szlen);

   s1 = tmpb;
   i = 1;
   while(*s1)
     {
      n = i % 5;
      if(n == 0)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == en_atab[j])
               {
                *s1 = en_tab1[j];
                break;
               }
            }
        }
      if(n == 1)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == en_atab[j])
               {
                *s1 = en_tab2[j];
                break;
               }
            }
        }
      if(n == 2)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == en_atab[j])
               {
                *s1 = en_tab3[j];
                break;
               }
            }
        }
      if(n == 3)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == en_atab[j])
               {
                *s1 = en_tab4[j];
                break;
               }
            }
        }
      if(n == 4)
        {
         for(j = 0; j < 62; j++)
            {
             if(*s1 == en_atab[j])
               {
                *s1 = en_tab5[j];
                break;
               }
            }
        }
      s1++;
      i++;
     }

   strcat(tbuf, tmpb);

   if(etc_subencrypt(tbuf, dest) < 0)
      return(-1);
   return(0);
}


int etc_subencrypt(char *src, char *dest)
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
         if(*s1 == en_atab[i])
           {
            cflag++;
            *s1 = en_btab[i]; 
            break;
           }
        }
     if(cflag == 0) *s1 = '9';
     cflag = 0;
     s1++;
    }
  return(0);
}
