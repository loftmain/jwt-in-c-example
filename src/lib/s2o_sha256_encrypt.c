#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "KISA_SHA256.h"

void Char2Hex(unsigned char ch, char* szHex);
int s2o_sha256_encrypt(char* src, char* dest);

int s2o_sha256_encrypt(char* src, char* dest)
{
	char buf[1024], buf2[1024];
	int i;

	memset(buf, 0, sizeof buf);
	SHA256_Encrpyt((BYTE *)src, strlen(src), buf);
	strcpy(dest, buf);
	/*
	for(i = 0; i < strlen(buf); i++)  {
		memset(buf2, 0, sizeof buf2);
		Char2Hex(buf[i], buf2);
		strcat(dest, buf2);
	}
	*/
	return 1;
}

extern void Char2Hex(unsigned char ch, char* szHex);
