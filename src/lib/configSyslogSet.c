#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../IT.extern.h"

extern int it_loging(char *format,...);
extern int getitem(int ch, char *src, char *dest, int seqitem);
extern int getitemc(int ch, char *src);
extern int rtrim(char* sbuf);

int configSyslogSet(char *homedir, int *_iskip_info)
{
    FILE 	*fp;
	int		count = 0;
    char 	*s_ptr, tbuf[210], fname[256], linebuf[256];
	char 	msgid[8], msgstr[256], msgchk[2], msgupper[2];
	char	buf1[256];
	char	*sptr;

#if defined(LINUX)
    sprintf(fname, "%s/syslog_Linux.cfg", homedir);
#elif defined(AIX)
    sprintf(fname, "%s/syslog_AIX.cfg", homedir);
#elif defined(NCRUX)
    sprintf(fname, "%s/syslog_NCRUX.cfg", homedir);
#elif defined(HPUX)
    sprintf(fname, "%s/syslog_HPUX.cfg", homedir);
#elif defined(SUN2)
    sprintf(fname, "%s/syslog_SunOS.cfg", homedir);
#else
    sprintf(fname, "%s/syslog_Default.cfg", homedir);
#endif

	(*_iskip_info) = 0;

    if ((fp = fopen(fname, "r")) == NULL) {
        it_loging("libIT.a(%s): configSyslogSet() file(%s) open error.\n", S2O_DAEMON, fname);
        return(-1);
	}


    while ((fgets(linebuf, 255, fp)) != NULL) {
        if ((linebuf[0]=='\n') || (linebuf[0]==' ') || (linebuf[0]=='#')) {
			if ( linebuf[0]=='#' ) {
				if(!strncmp(linebuf, "#NOPATTERN_INFO_SKIP_YN", strlen("#NOPATTERN_INFO_SKIP_YN"))) {		
					memset(tbuf, 0, sizeof tbuf);
					getitem('=', linebuf, tbuf, 2);
					memset(buf1, 0, sizeof buf1);
					sscanf(tbuf, "%s", buf1);
					if ( buf1[0] == 'Y') (*_iskip_info) = 1;

				}
			}
          	continue;
		}

        s_ptr = (char *)strrchr(linebuf, '\n');
        if (s_ptr != NULL) *s_ptr = '\0';

        s_ptr = (char *)strrchr(linebuf, '\r');
        if (s_ptr != NULL) *s_ptr = '\0';

		memset(tbuf, 0x00, sizeof tbuf);
		memset(msgid, 0x00, sizeof msgid);
		memset(msgstr, 0x00, sizeof msgstr);
		memset(msgchk, 0x00, sizeof msgchk);
		memset(msgupper, 0x00, sizeof msgupper);

		getitem(';', linebuf, tbuf, 1);
		getitem(':', tbuf, msgid, 1);
		sptr = (char *)strchr(tbuf, ':');
		if (sptr != NULL){
			strcpy(msgstr,sptr+1);
		}
		/* getitem(':', tbuf, msgstr, 2); */
		getitem(';', linebuf, msgchk, 2);
		getitem(';', linebuf, msgupper, 3);

  		/* reallocate array to hold the new entry */
		syslog_str = (struct syslog_struct *) realloc (syslog_str, (count + 1) * sizeof (struct syslog_struct));

		if (syslog_str == NULL) {
			it_loging("libIT.a(%s): configSyslogSet() syslog_str rerealloc error\n", S2O_DAEMON);
    		fclose(fp);
  			return(-1);
		}

	    strcpy(syslog_str[count].msgid, msgid);
	    strcpy(syslog_str[count].msgstr, msgstr);
	    strcpy(syslog_str[count].msgchk, msgchk);
	    strcpy(syslog_str[count].msgupper, msgupper);
	    syslog_str[count].msgid[strlen(msgid)] = '\0';
	    syslog_str[count].msgstr[strlen(msgstr)] = '\0';
	    syslog_str[count].msgchk[strlen(msgchk)] = '\0';
	    syslog_str[count].msgupper[strlen(msgupper)] = '\0';
        count++;
	}
    fclose(fp);
    return(count);
}
