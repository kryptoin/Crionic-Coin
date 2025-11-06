/*-
 * Copyright 2009 Colin Percival
 * Copyright 2013-2018 Alexander Peslyak
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
 *
 * This file was originally written by Colin Percival as part of the Tarsnap
 * online backup system.
 */

#ifndef _YESPOWER_H_
#define _YESPOWER_H_

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void *base, *aligned;
    size_t base_size, aligned_size;
} yespower_region_t;

typedef yespower_region_t yespower_local_t;

typedef enum { YESPOWER_0_5 = 5,
    YESPOWER_1_0 = 10 } yespower_version_t;

typedef struct {
    yespower_version_t version;
    uint32_t N, r;
    const uint8_t* pers;
    size_t perslen;
} yespower_params_t;

typedef struct {
    unsigned char uc[32];
} yespower_binary_t;

extern int yespower_init_local(yespower_local_t* local);

extern int yespower_free_local(yespower_local_t* local);

extern int yespower(yespower_local_t* local,
    const uint8_t* src,
    size_t srclen,
    const yespower_params_t* params,
    yespower_binary_t* dst);

extern int yespower_tls(const uint8_t* src, size_t srclen, const yespower_params_t* params, yespower_binary_t* dst);

#ifdef __cplusplus
}
#endif

#endif
