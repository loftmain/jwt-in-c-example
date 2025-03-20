   /************************************************************************/
   /*  FILENAME     : size_check.c                                         */
   /*  DISCRIPTION  : file size check.                                     */
   /*  DATE         : 2000. 08. 29                                         */
   /*  WRITTEN      : ywoopark                                             */
   /************************************************************************/


#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

extern int loging(char *msg,...);
int file_create(char *file);

int size_check(char *file, int size)
{
  	struct stat stbuf;
  	int ret;

  	if (stat(file, &stbuf) == -1) {      /* file이 존재하지 않으면 NULL file 생성*/ 
     	file_create(file);
     	return(0);
    }

  	if (stbuf.st_size > size) 
		return(-1);
  	else 
		return(0);
}

int file_create(char *file)
{
  	FILE *fp;
	int ret;

  	if ((fp = fopen(file, "w")) == NULL) {
     	loging("libIT.a: file(%s) creation error!\n", file);
     	return(-1);
    }
   	fclose(fp);
	if (!strcmp(file, "IT.log")) {
   		chmod(file, 00644);
		ret = chown(file, 0, 3);
	}
   	return(0);
}
