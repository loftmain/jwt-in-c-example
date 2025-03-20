#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

char TYPE1PASS[64] =  "027115318";
char TYPE2PASS[64] =  "7115318";

int s2o_encrypt(char *type, char *src, char *dest);
int s2o_decrypt(char *type, char *src, char *dest);
int decrypt_file(char* file, char *type, char* dest);

extern char S2O_DAEMON[64];
extern int DES_proc(int jobType, char *passWord, char *srcBuf, char *destBuf);
extern int it_loging(char *format,...);

int s2o_encrypt(char *type, char *src, char *dest)
{
	if (strcmp(type, "1") == 0)
		return DES_proc(1, TYPE1PASS, src, dest);
	else 
		return DES_proc(1, type, src, dest);
}

int s2o_decrypt(char *type, char *src, char *dest)
{
	
	if (strcmp(type,"1") == 0)
		return DES_proc(2, TYPE1PASS, src, dest);
	else 
		return DES_proc(2, type, src, dest);
}

int encrypt_file(char* file, char *type, char* src)
{
	struct stat stbuf;
	int ret;
	char dest[2048];
	FILE *fp;

	ret = stat(file, &stbuf);
	if ( ret == 0) {
		it_loging("libIT.a(%s): encrypt_file()The encryption file(%s) for encryption already exist.\n", S2O_DAEMON, file);
		return 0;
	}

	memset(dest, 0, sizeof dest);

	if (strcmp(type, "1") == 0)
		DES_proc(1, TYPE1PASS, src, dest);
	else if (strcmp(type, "2") == 0)
		DES_proc(1, TYPE2PASS, src, dest);
	else {
		it_loging("libIT.a(%s): encrypt_file() encryption type error. file = %s\n", S2O_DAEMON, file);
		return -101;
	}
	
	if (strlen(dest) == 0 || !strcmp(src, dest)) {
		it_loging("libIT.a(%s): encrypt_file() encryption error. file = %s\n", S2O_DAEMON, file);
		return -102;
	}

	if ((fp = fopen(file, "w")) == NULL) {
		it_loging("libIT.a(%s): encrypt_file() The encryption file(%s) open error.\n", S2O_DAEMON, file);
		return -103;
	}

	fputs(dest, fp);
	fclose(fp);

	memset(dest, 0, sizeof dest);

	ret = decrypt_file(file, type, dest);

	if ( ret < 0 ) return ret;

	if (strcmp(src, dest)) {
		it_loging("libIT.a(%s): encrypt_file() The decryption result is different from the original value. file=%s\n", S2O_DAEMON, file);
		return -105;
	}

	return 1;
}

int decrypt_file(char* file, char *type, char* dest)
{
	struct stat stbuf;
	int ret;
	char src[2048];
	FILE *fp;
	size_t icount;

	ret = stat(file, &stbuf);
	if ( ret == -1) {
		it_loging("libIT.a(%s): decrypt_file() The encryption file(%s) for decryption does not exist.\n", S2O_DAEMON, file);
		return -201;
	}

	if ((fp = fopen(file, "r")) == NULL) {
		it_loging("libIT.a(%s): decrypt_file() The encryption file(%s) for decryption open error.\n", S2O_DAEMON, file);
		return -203;
	}

	icount = fread(src, 2047, 1, fp);
	fclose(fp);

	if (strcmp(type,"1") == 0)
		DES_proc(2, TYPE1PASS, src, dest);
	else if (strcmp(type,"2") == 0)
		DES_proc(2, TYPE2PASS, src, dest);
	else {
		it_loging("libIT.a(%s): decrypt_file() Decryption type error. file = %s\n", S2O_DAEMON, file);
		return -202;
	}

	return 1;
}


