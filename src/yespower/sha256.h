/*-
 * Copyright 2005-2016 Colin Percival
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _SHA256_H_
#define _SHA256_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SHA256_Init libcperciva_SHA256_Init
#define SHA256_Update libcperciva_SHA256_Update
#define SHA256_Final libcperciva_SHA256_Final
#define SHA256_Buf libcperciva_SHA256_Buf
#define SHA256_CTX libcperciva_SHA256_CTX
#define HMAC_SHA256_Init libcperciva_HMAC_SHA256_Init
#define HMAC_SHA256_Update libcperciva_HMAC_SHA256_Update
#define HMAC_SHA256_Final libcperciva_HMAC_SHA256_Final
#define HMAC_SHA256_Buf libcperciva_HMAC_SHA256_Buf
#define HMAC_SHA256_CTX libcperciva_HMAC_SHA256_CTX

typedef struct {
    uint32_t state[8];
    uint64_t count;
    uint8_t buf[64];
} SHA256_CTX;

void SHA256_Init(SHA256_CTX*);

void SHA256_Update(SHA256_CTX*, const void*, size_t);

void SHA256_Final(uint8_t[32], SHA256_CTX*);

void SHA256_Buf(const void*, size_t, uint8_t[32]);

typedef struct {
    SHA256_CTX ictx;
    SHA256_CTX octx;
} HMAC_SHA256_CTX;

void HMAC_SHA256_Init(HMAC_SHA256_CTX*, const void*, size_t);

void HMAC_SHA256_Update(HMAC_SHA256_CTX*, const void*, size_t);

void HMAC_SHA256_Final(uint8_t[32], HMAC_SHA256_CTX*);

void HMAC_SHA256_Buf(const void*, size_t, const void*, size_t, uint8_t[32]);

void PBKDF2_SHA256(const uint8_t*, size_t, const uint8_t*, size_t, uint64_t, uint8_t*, size_t);

#ifdef __cplusplus
}
#endif

#endif
