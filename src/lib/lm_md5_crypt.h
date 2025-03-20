/* $Id: lm_md5_crypt.h,v 1.32 2005/08/06 04:40:42 ymir Exp $ */
/*
 * Copyright (c) 2002 RedGate Co. LTD. All rights reserved
 *
 * MD5 Crypt Library for Account Management (LINUX)
 */

#include "config.h"

#ifdef LINUX

#ifndef	LM_MD5_CRYPT_H
#define	LM_MD5_CRYPT_H

typedef unsigned int uint32;

struct MD5Context
{
	uint32 buf[4];
	uint32 bits[2];
	unsigned char in[64];
};

/*
 * This is needed to make RSAREF happy on some MS-DOS compilers.
 */

typedef struct MD5Context _MD5_CTX;


/*
void GoodMD5Init(struct MD5Context *);
void GoodMD5Update(struct MD5Context *, unsigned const char *, unsigned);
void GoodMD5Final(unsigned char digest[16], struct MD5Context *);
void GoodMD5Transform(uint32 buf[4], uint32 const in[16]);

void BrokenMD5Init(struct MD5Context *);
void BrokenMD5Update(struct MD5Context *, unsigned const char *, unsigned);
void BrokenMD5Final(unsigned char digest[16], struct MD5Context *);
void BrokenMD5Transform(uint32 buf[4], uint32 const in[16]);

char *Goodcrypt_md5(const char *pw, const char *salt);
char *Brokencrypt_md5(const char *pw, const char *salt);
*/

void _MD5Init(struct MD5Context *);
void _MD5Update(struct MD5Context *, unsigned const char *, unsigned);
void _MD5Final(unsigned char digest[16], struct MD5Context *);
void _MD5Transform(uint32 buf[4], uint32 const in[16]);

char *crypt_md5(const char *pw, const char *salt);

char *crypt_md5_wrapper(const char *pass_new);

#endif	/* LM_MD5_CRYPT_H */

#endif	/* LINUX */


