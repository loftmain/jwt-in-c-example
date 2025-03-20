   /************************************************************************/
   /*  FILENAME     : get_envhome.c                                    */
   /*  DISCRIPTION  :                                                      */
   /*  DATE         :                                                      */
   /*  WRITTEN      :                                                      */
   /*  MODIFIED     :                                                      */
   /************************************************************************/

#include "config.h"
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#ifdef AIX
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include "../IT.extern.h"

int get_envhome(char* _envhome)
{

	FILE *pfp;
	char cmdbuf[1024];
	char tbuf[1024];
	char tmpbuf[1024], tmpbuf2[1024];
	struct stat stbuf;
	char *sptr;
	int i =0;

	sprintf(_envhome, "/etc\0");
	return (1);

#if defined(__NOT_USE__)

#if defined(LINUX)

	if (stat(_DEF_RCFILE1_, &stbuf) != 0 && stat(_DEF_RCFILE2_, &stbuf) != 0) {
		it_loging("libIT.a(%s): get_envhome() Run script file does not exist.\n", S2O_DAEMON);
		return(-1);
	}

	for(i = 0; i < 2; i++) 
	{
		memset(cmdbuf, 0, sizeof cmdbuf);
		if (i == 0) {
			sprintf(cmdbuf, "grep S2O-SCN_CFG_HOME %s", _DEF_RCFILE1_);
		} else {
			sprintf(cmdbuf, "grep S2O-SCN_CFG_HOME %s", _DEF_RCFILE2_);
		}

    	if ((pfp=popen(cmdbuf, "r")) != NULL) {

			memset(tbuf, 0, sizeof tbuf);
        	while(fgets(tbuf, 1023,pfp) != NULL) {
	
            	if(tbuf[strlen(tbuf)-1] == '\n') tbuf[strlen(tbuf)-1] = '\0';

				sptr = (char*) strstr(tbuf, "S2O-SCN_CFG_HOME");

				if (sptr != NULL) {

					memset(tmpbuf, 0, sizeof tmpbuf);
					strcpy(tmpbuf, sptr);
	
					sptr = (char*)strchr(tmpbuf, '=');
					if (sptr != NULL) {
						memset(tbuf, 0, sizeof tbuf);
						sscanf(sptr+1, "%s", tbuf);
						*sptr = '\0';

						memset(tmpbuf2, 0, sizeof tmpbuf2);
						sscanf(tmpbuf, "%s", tmpbuf2);
						
						if (!strcmp(tmpbuf2, "S2O-SCN_CFG_HOME")) {
							pclose(pfp);
							if (stat(tbuf, &stbuf) == 0) {
								strcpy(_envhome, tbuf);
							}
							return 1;
						}
					}
				}
			
				memset(tbuf, 0, sizeof tbuf);
			}
			pclose(pfp);
		}
	}
	return 0;

#else

	if (stat(_DEF_RCFILE1_, &stbuf) != 0) {
		it_loging("libIT.a(%s): get_envhome() Run script file does not exist.\n", S2O_DAEMON);
		return(-1);
	}

	memset(cmdbuf, 0, sizeof cmdbuf);
	sprintf(cmdbuf, "grep S2O-SCN_CFG_HOME %s", _DEF_RCFILE1_);

    if ((pfp=popen(cmdbuf, "r")) != NULL) {

		memset(tbuf, 0, sizeof tbuf);
        while(fgets(tbuf, 1023,pfp) != NULL) {

            if(tbuf[strlen(tbuf)-1] == '\n') tbuf[strlen(tbuf)-1] = '\0';

			sptr = (char*) strstr(tbuf, "S2O-SCN_CFG_HOME");

			if (sptr != NULL) {

				memset(tmpbuf, 0, sizeof tmpbuf);
				strcpy(tmpbuf, sptr);
	
				sptr = (char*)strchr(tmpbuf, '=');
				if (sptr != NULL) {
					memset(tbuf, 0, sizeof tbuf);
					sscanf(sptr+1, "%s", tbuf);
					*sptr = '\0';

					memset(tmpbuf2, 0, sizeof tmpbuf2);
					sscanf(tmpbuf, "%s", tmpbuf2);
					
					if (!strcmp(tmpbuf2, "S2O-SCN_CFG_HOME")) {
						pclose(pfp);
						if (stat(tbuf, &stbuf) == 0) {
							strcpy(_envhome, tbuf);
						}
						return 1;
					}
				}
			}

			memset(tbuf, 0, sizeof tbuf);
		}
		pclose(pfp);
	}
	return 0;
#endif

#endif

}

