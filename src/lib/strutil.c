#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char *strupr(char *string)
{
      char *s;
      if (string)
      {
            for (s = string; *s; ++s)
                  *s = toupper(*s);
      }
      return string;
}

char *strlwr(char *string)
{
      char *s;
      if (string)
      {
            for (s = string; *s; ++s)
                  *s = tolower(*s);
      }
      return string;
}
