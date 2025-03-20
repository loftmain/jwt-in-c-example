#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int getitem(int ch, char *src, char *dest, int seqitem);

int configNetwork(char *homedir)
{
    FILE *fp;

    char *s_ptr, tbuf[210], fname[256], linebuf[256];
	int	count = 0, k;
	char service[32], port[16];
	int warning, critical, fatal;

    sprintf(fname, "%s/cfg/network.cfg", homedir);

    if ((fp = fopen(fname, "r")) == NULL) {
		it_loging("libIT.a(%s): configNetwork() file(%s) open error.\n", S2O_DAEMON, fname);
        return(-1);
	}

    while ((fgets(linebuf, 255, fp)) != NULL) {
        if ((linebuf[0]=='\n') || (linebuf[0]==' ') || (linebuf[0]=='#')) {
          	continue;
		}

        s_ptr = (char *)strrchr(linebuf, '\n');
        if (s_ptr != NULL)
           	*s_ptr = '\0';

		memset(service, 0x00, sizeof service);
		getitem(';', linebuf, service, 1);

		memset(tbuf, 0x00, sizeof tbuf);
		if (getitem(';', linebuf, tbuf, 2) < 0)
			warning = 0;
		else 
			warning = atoi(tbuf);

		memset(tbuf, 0x00, sizeof tbuf);
		if (getitem(';', linebuf, tbuf, 3) < 0)
			critical = 0;
		else 
			critical = atoi(tbuf);

		memset(port, 0x00, sizeof port);
		getitem(';', linebuf, port, 4);
		if(strlen(port) == 0)
			strcpy(port, service);

		memset(tbuf, 0x00, sizeof tbuf);
		if (getitem(';', linebuf, tbuf, 5) < 0)
			fatal = 0;
		else 
			fatal = atoi(tbuf);

  		/* reallocate array to hold the new entry */
		defNetwork = (struct def_network *) realloc (defNetwork, (count + 1) * sizeof (struct def_network));

		if (defNetwork == NULL) {
			it_loging("libIT.a(%s): configNetwork() def_network realloc error\n", S2O_DAEMON);
    		fclose(fp);
  			return(-1);
		}

		strcpy(defNetwork[count].service, service);
		strcpy(defNetwork[count].port, port);
		defNetwork[count].warning = warning;
		defNetwork[count].critical = critical;
		defNetwork[count].fatal = fatal;
		defNetwork[count].establish = 0;
		defNetwork[count].wait = 0;
		defNetwork[count].flag = 0;

        count++;
	}
    fclose(fp);

    return(count);
}
