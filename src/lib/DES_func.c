/**************************************************************
 *   작성자 : Seok-jun Bae
 *   날  자 : 2001. 4. 28.
 *   내  용 : DES 암호화 복호화 프로그램  
 *   E-mail : www@qprk.pe.kr
 *   
 *   이 소스코드에 대한 어떠한 보증도 없습니다. 
 *   이 소스를 수정 배포할수 있지만 다른곳에 배포할 경우
 *   이 문장이 포함되어야 합니다.
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>
/*#include <conio.h>*/
#include <string.h>


#define P2C 1			/* 평문을 암호로 */
#define C2P 2			/* 암호를 평문으로 */
#define BUFFSIZE 20500		/* 20KByte */
#define RWSIZE   20000

void keyGenerate(char *);
void startDes(int, int, char *, char *);
void desRound(int *, int *);
void char2binary(int *, char *, int);
char binary2char(int *);
void swap32bit(int *, int *, int *);


void keyProc(char *keySrc);
int DES_proc(int jobType, char *passWord, char *srcBuf, char *destBuf);
extern int get_config2(char *config, char *env, char *value);




int MAT_IP[64]={58, 50, 42, 34, 26 ,18 ,10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};

int MAT_IP_1[64]={40, 8, 48, 16, 56, 24, 64, 32,
		  39, 7, 47, 15, 55, 23, 63, 31,
		  38, 6, 46, 14, 54, 22, 62, 30,
		  37, 5, 45, 13, 53, 21, 61, 29,
		  36, 4, 44, 12, 52, 20, 60, 28,
		  35, 3, 43, 11, 51, 19, 59, 27,
		  34, 2, 42, 10, 50, 18, 58, 26,
		  33, 1, 41, 9, 49, 17, 57, 25};

int MAT_EXP[48]={32, 1, 2, 3, 4, 5,
		 4, 5, 6, 7, 8, 9,
		 8, 9, 10, 11, 12, 13,
		 12, 13, 14, 15, 16, 17,
		 16, 17, 18, 19, 20, 21,
		 20, 21, 22, 23, 24, 25,
		 24, 25, 26, 27, 28, 29,
		 28, 29, 30, 31, 32, 1};

int MAT_PERMU[32]={16, 7, 20, 21, 29, 12, 28, 17,
		   1, 15, 23, 26, 5, 18, 31, 10,
		   2, 8, 24, 14, 32, 27, 3, 9,
		   19, 13, 30, 6, 22, 11, 4, 25};

int MAT_SBOX[8][4][16]={{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
			 {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
			 {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
			 {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 2, 14, 10, 0, 6, 13}},
  
			{{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
			 {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
			 {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
			 {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

			{{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
			 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
			 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
			 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

			{{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
			 {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
			 {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
			 {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
	    
			{{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
			 {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
			 {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
			 {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

			{{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
			 {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
			 {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
			 {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

			{{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
			 {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
			 {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
			 {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

			{{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
			 {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
			 {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
			 {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

int MAT_PC_1[56]={57, 49, 41, 33, 25, 17, 9,
		  1, 58, 50, 42, 34, 26, 18,
		  10, 2, 59, 51, 43, 35, 27,
		  19, 11, 3, 60, 52, 44, 36,
		  63, 55, 47, 39, 31, 23, 15,
		  7, 62, 54, 46, 38, 30, 22,
		  14, 6, 61, 53, 45, 37, 29,
		  21, 13, 5, 28, 20, 12, 4};

int MAT_PC_2[48]={14, 17, 11, 24, 1, 5, 3, 28,
		  15, 6, 21, 10, 23, 19, 12, 4,
		  26, 8, 16, 7, 27, 20, 13, 2,
		  41, 52, 31, 37, 47, 55, 30, 40,
		  51, 45, 33, 48, 44, 49, 39, 56,
		  34, 53, 46, 42, 50, 36, 29, 32};

int KEY[16][48];

/*
int main(int argc, char **argv)
{
	char srcBuf[1024], tmpBuf[1024], destBuf[1024];
	char srcBuf2[1024], tmpBuf2[1024], destBuf2[1024];
	char Buf[256];
	char filename[128];
	char passwd[32];

	FILE *fp;

	memset(srcBuf, 0, sizeof srcBuf);
	memset(tmpBuf, 0, sizeof tmpBuf);
	memset(destBuf, 0, sizeof destBuf);
	memset(srcBuf2, 0, sizeof srcBuf2);
	memset(tmpBuf2, 0, sizeof tmpBuf2);
	memset(passwd, 0, sizeof passwd);


	strcpy(srcBuf, "ksie1!@#$%^dd&*()_+|}{>?<:1~2345");
	strcpy(srcBuf2, "itopsmgr");
	strcpy(passwd, "12345");

	strcpy(filename, "124.txt");

	if( (fp = fopen( filename, "w" )) == NULL )
	{
		printf("Target file open error!!!! -123.txt- \n");
		exit(0);
	}

	desproc(P2C, passwd, srcBuf, tmpBuf);
	desproc(P2C, passwd, srcBuf2, tmpBuf2);

	memset(Buf, 0, sizeof Buf);
	sprintf(Buf, "TEST1 = %s\n", tmpBuf);
	fputs(Buf, fp);

	memset(Buf, 0, sizeof Buf);
	sprintf(Buf, "TEST2 = %s\n", tmpBuf2);
	fputs(Buf, fp);

	fclose(fp);

	printf("\n\n");

	memset(tmpBuf, 0, sizeof tmpBuf);
	memset(destBuf, 0, sizeof destBuf);
	get_config2(filename, "TEST1", tmpBuf);	
	desproc(C2P, passwd, tmpBuf,  destBuf);

	printf("[%s]", destBuf);
	printf("\n\n");

	memset(tmpBuf, 0, sizeof tmpBuf);
	memset(destBuf, 0, sizeof destBuf);
	get_config2(filename, "TEST2", tmpBuf);
	desproc(C2P, passwd, tmpBuf,  destBuf);
	
	printf("[%s]", destBuf);
	printf("\n\n");
	return 0;
}
*/

int DES_proc(int jobType, char *passWord, char *srcBuf, char *destBuf)
{
	int tempKey[16][48];
	long int dataSize;
	long int readSize, writeSize;
	char nameTemp[100]={0,};
	char qprkDes[100]={0,};
	int i,j;

	/* //////////////////////////////////////////////////////// */
	keyGenerate(passWord);	/* DES에 사용할 Key 생성 */
	/* ////////////////////////////////////////////////////// */

	if(jobType == C2P)
	{			/* C2P일경우 key를 역순으로 나열 */
		for(i=0; i<16; i++)
		{
			for(j=0; j<48; j++)
			{
				tempKey[15-i][j] = KEY[i][j];
			}
		}
		for(i=0; i<16; i++)
			for(j=0; j<48; j++)

		KEY[i][j] = tempKey[i][j];
	}
	dataSize = strlen(srcBuf) + 1;
	startDes(jobType, dataSize, srcBuf, destBuf);
	return 1;
}

void startDes(int jobType, int dataSize, char *srcData, char *tgtData )
{
	int srcBinary[64]={0,}, tgtBinary[64]={0,}, binaryBuff[64]={0,};
	int leftData[32]={0,}, rightData[32]={0,}, swapBuff[32]={0,};
	int tgtIndex=0;
	char textBuff[9]={'\0',};
	int i, j, k;

	for(i=0, tgtIndex=0; i<dataSize; i++)
	{ /* Data의 끝까지 가면서 암호화, 복호화 한다 */
		memset(textBuff, 0, 9);
		memcpy(textBuff, (srcData + tgtIndex), 8);	/* srcData에서 8자씩 textBuff로복사 */

		char2binary(binaryBuff, textBuff, 8); /* textBuff를 binary로   */

		for(j=0; j<64; j++)		/* Initial Permutation */
			srcBinary[j] = binaryBuff[ MAT_IP[j]-1 ];

		if(jobType == P2C) 
		{
			for(j=0; j<32; j++)
			{	/* 하나의 64bit를 둘의 left, right data 로 나눈다*/
				leftData[j] = srcBinary[j];
				rightData[j] = srcBinary[j+32];
			}
		}
		else
		{	/* 복호화 할경우 left data와 right data의 위치를 바꾼다 */
			for(j=0; j<32; j++)
			{	/* 하나의 64bit를 둘의 left, right data 로 나눈다*/
				rightData[j] = srcBinary[j];
				leftData[j] = srcBinary[j+32];
			}
		}

	/* //////////////////////////////////////////////////////////////////////// */
		desRound(leftData, rightData);
	/* //////////////////////////////////////////////////////////////////////// */

		if(jobType == P2C) 
			swap32bit(leftData, rightData, swapBuff);	/* 32bit swap */

		for(j=0; j<32; j++)
		{	/* 둘의 left, right data 를 하나의 64bit로 합한다 */
			binaryBuff[j] = rightData[j]; /* 또한 32bit swap을 한다 */
			binaryBuff[j+32] = leftData[j];
		}

		for(j=0; j<64; j++)		/* Inverse Initial Permutation */
			tgtBinary[j] = binaryBuff[ MAT_IP_1[j]-1 ];

		memset(textBuff, 0, 9);

		for(j=0,k=0; j<64; j+=8, k++) /* tgtBinary를 ascii로 변형후 textBuff에 저장 */
			textBuff[k] = binary2char(&tgtBinary[j]);

		memcpy((tgtData + tgtIndex), textBuff, 8);	/* textBuff의 내용을 tgtData로 복사 */

		/* strncpy는 없어질수 있지 않나? */
		tgtIndex += 8;
	}
}

/**************************************************************
 * Round
 **************************************************************/
void desRound(int *leftData, int *rightData)
{
	int sboxOut[32]={0,}, leftFinal[32]={0,}, permuOut[32]={0,};
	int eBuff[48]={0,}, eBuffOut[48]={0,};
	int sboxRow, sboxCol, sboxValue;
	int i, j, k, keyIndex;

	for(keyIndex=0; keyIndex<16; keyIndex++)
	{	/* 16번의 round를 거친다 */

		for(i=0; i<32; i++)		/* 써먹을때가 있다 */
			leftFinal[i] = *(rightData+i);

		for(i=0; i<48; i++)
		{		/* E table 적용 */
			eBuff[i] = *(rightData + (MAT_EXP[i] -1));
		}


		for(i=0; i<48; i++)
		{		/* eBuff xor key */
			eBuffOut[i] = eBuff[i] ^ KEY[keyIndex][i];
		}

		for(i=0, j=0, k=0; i<8; i++)
		{	/* sBox 적용 */
			sboxRow = (eBuffOut[j+0] * 2) + eBuffOut[j+5];
			sboxCol = (eBuffOut[j+1] * 8) + (eBuffOut[j+2] * 4) + (eBuffOut[j+3] * 2) + eBuffOut[j+4];
			sboxValue = MAT_SBOX[i][sboxRow][sboxCol];
			sboxOut[k]   = ((sboxValue & 8)  ? 1:0 );
			sboxOut[k+1] = ((sboxValue & 4)  ? 1:0 );
			sboxOut[k+2] = ((sboxValue & 2)  ? 1:0 );
			sboxOut[k+3] = sboxValue & 1;	
			j += 6;
			k += 4;
		}

		for(i=0; i<32; i++)		/* sboxOut 에 p table적용 */
			permuOut[i] = sboxOut[ MAT_PERMU[i]-1 ];  

		for(i=0; i<32; i++)
		{		/* permuOut xor leftData 를 rightData에 저장*/
			*(rightData+i) = *(leftData+i) ^ permuOut[i];
		}

		for(i=0; i<32; i++)		/* 첨에 복사한 leftFinal을 leftData에 복사 */
			*(leftData+i) = leftFinal[i];
	}
}
/*
int get_config2(char *config, char *env, char *value)
{
	FILE *fp;
	char rbuf[1025], chkbuf[1025];
	char value_tmp[1025];
	char *s;
	char *a;

	if ((fp=fopen(config, "r")) == NULL)
	{
		printf("file(%s) open error.\n", config);
		return -1;
	}

	memset(rbuf, 0, sizeof rbuf);
	while (fgets(rbuf, 1024, fp) != NULL)
	{
		if ((rbuf[0] == '#') || (rbuf[0] == '\n'))
		{
			memset(rbuf, 0, sizeof rbuf);
			continue;
		}
		memset(chkbuf, 0, sizeof chkbuf);
		sscanf(rbuf, "%s", chkbuf);
		s = (char *)strchr(chkbuf, '=');
		if (s != NULL)
			*s = '\0';

		if (!strcmp(env, chkbuf))
		{
			s = (char *)strchr(rbuf, '=');
			if (s != NULL)
			{
				memset(value_tmp, 0, sizeof value_tmp);
				s = s + 1;
				while(*s == ' ')
				{
					s = s+1;
				}

				a = (char *)strchr(s, '\n');
				*a = '\0';
				strcpy(value, s);
				fclose(fp);
				return 0;
			}
			else
			{
				memset(rbuf, 0, sizeof rbuf);
				continue;
			}
		}
		else
		{
			memset(rbuf, 0, sizeof rbuf);
			continue;
		}
	}
	fclose(fp);
	return -1;
}
*/

/**************************************************************
 * 32bit swap
 **************************************************************/
void swap32bit(int *leftBit, int *rightBit, int *buffBit)
{
	int i;

	for(i=0; i<32; i++)
		buffBit[i] = leftBit[i];

	for(i=0; i<32; i++)
		leftBit[i] = rightBit[i];

	for(i=0; i<32; i++)
		rightBit[i] = buffBit[i];

}


/**************************************************************
 * 16개 키 만들기
 * key의 입력 재한은 없지만 내부적으로 8Byte만 사용한다.
 **************************************************************/
void keyGenerate(char *keySrc)
{
	int keySchedule[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	int binaryKey[64] = {0,};
	int pc1[56]={0,};
	char tempKey[9];
	int i, j, k, l, tmp1, tmp2, srcLen;

	if( (strlen(keySrc))>8 )	/* 입력된 암호의 길이가 8자 이상이면 */
		keyProc(keySrc);

	strncpy(tempKey, keySrc, 8);
	tempKey[8] = '\0';
	srcLen = strlen( tempKey);
	char2binary(binaryKey, tempKey, srcLen);
	memset(tempKey, 0, 8);

	for(i=0; i<56; i++)		/* 64bit를 56bit로 줄이는거 */
		pc1[i] = binaryKey[ MAT_PC_1[i]-1 ];

	for(i=0; i<16; i++)
	{
		for(j=0; j<keySchedule[i]; j++)
		{ /* left shift */
			tmp1 = pc1[0];
			tmp2 = pc1[28];
			for(k=1; k<28; k++)
			{
				pc1[k-1] = pc1[k];
				pc1[k+27] = pc1[k+28];
			}
			pc1[27] = tmp1;
			pc1[55] = tmp2;
		}

		for(j=0; j<48; j++)		/* 56bit 를 48bit로 줄여서 저장 - 최종 key */
			KEY[i][j] = pc1[ MAT_PC_2[j]-1 ];
	}

}

/**************************************************************
 * 길이가 긴 key를 8char로 줄이기
 * 12345678에서 1234는 keySrc의 문자열에서 마지막부터 뒤로저장
 * 5678은 keySrc의 첫번째부터 저장
 * 저장 방법은 keySrc의 문자 수를 4로 나눈 몫만큼 
 * 앞이나 뒤로 이동
 **************************************************************/
void keyProc(char *keySrc)
{
	char *temp;
	int srcLen=0, dev4;
	int i,j;

	srcLen = strlen(keySrc);
	temp = (char *)malloc(srcLen+1);
	memset(temp, 0, srcLen +1);
	strcpy(temp, keySrc);
	memset(keySrc, 0, srcLen);

	dev4 = srcLen / 4;

	srcLen-- ;

	for(i=0,j=0;i<4;i++,j+=dev4)
	{
		*(keySrc+i)   = *(temp+srcLen-j);
		*(keySrc+i+4) = *(temp+j);
	}
}

/**************************************************************
 * char를 2진수 코드로 만들기
 * target : 2진수 코드가 저장될 배열
 * char   : 2진수로 만들 문자열
 * srcLen : 2진수로 만들 문자열의 길이
 **************************************************************/
void char2binary(int *target, char *src, int srcLen)
{
	int targetIndex=0, i, j;
	char oneChar,temp1, temp2;


	for(i=0 ; i<srcLen; i++)
	{
		oneChar=*(src+i);
		for(j=7; j>=0; j--)
		{
			  temp1 = oneChar >> j;
			  temp2 = temp1 & 0x0001;
			  *(target+targetIndex) = (temp2 == 1 ? 1:0);
			  targetIndex++;
		}
	}
}


/**************************************************************
 * 8개의 2진수를 하나의 char로 만들기
 * src : 8개의 2진 코드
 * return : 만들어진 하나의 char
 **************************************************************/
char binary2char(int *src)
{
	char temp;
	int i,j,inTemp=1, chTemp=0;

	for(i=0; i<8; i++)
	{
		inTemp=1;
		if( *(src+i))
		{
			for(j=7; j>i; j--)
				inTemp *= 2;

			chTemp += inTemp;
		}
	}

	temp=chTemp;
	return temp;
}
