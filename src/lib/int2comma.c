#include <stdio.h>
#include <string.h>
#include "../IT.extern.h"

const char *int2comma(int _num)
{
    static char comma_str[64];
    char   str[64];
    int    idx, len, cidx = 0, mod;
    
    sprintf(str, "%d", _num);
    len = strlen(str);
    mod = len % 3;
    
    for(idx = 0; idx < len; idx++) {
        if(idx != 0 && (idx) % 3 == mod) {
            comma_str[cidx++] = ',';
        }
        comma_str[cidx++] = str[idx];
    }
    
    comma_str[cidx] = 0x00;
    return comma_str;
}

const char *llInt2comma(_llInt_ _num)
{
    static char comma_str[64];
    char   str[64];
    int    idx, len, cidx = 0, mod;
    
    sprintf(str, "%lld", _num);
    len = strlen(str);
    mod = len % 3;
    
    for(idx = 0; idx < len; idx++) {
        if(idx != 0 && (idx) % 3 == mod) {
            comma_str[cidx++] = ',';
        }
        comma_str[cidx++] = str[idx];
    }
    
    comma_str[cidx] = 0x00;
    return comma_str;
}
