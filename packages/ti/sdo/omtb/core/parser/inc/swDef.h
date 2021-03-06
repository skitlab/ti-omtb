/*
 * swDef.h
 *
 * Define Standard Types not already defined.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef _SWDEF_H_
#define _SWDEF_H_

#ifndef CHAR
#define CHAR   char
#endif

#ifndef SINT
#define SINT   int
#endif

#ifndef UINT
#define UINT   unsigned int
#endif

/* These are required in 4.2 Builds */
#ifndef SINT8
#define SINT8   signed char
#endif

#ifndef UINT8
#define UINT8   unsigned char
#endif

#ifndef SINT16
#define SINT16  short
#endif

#ifndef UINT16
#define UINT16  unsigned short
#endif

#ifndef SINT32
#define SINT32  int
#endif

#ifndef UINT32
#define UINT32  unsigned int
#endif

#ifndef BOOL
#define BOOL    int
#endif

#ifndef TRUE
#define TRUE    (1U)
#endif

#ifndef FALSE
#define FALSE   (!TRUE)
#endif

#ifndef SUCCESS
#define SUCCESS (1U)
#endif

#ifndef FAIL
#define FAIL    (!SUCCESS)
#endif

#define PRIVATE         static
#define VOLATILE        volatile
#define CONST           const

#define DIM(array)      (sizeof(array)/sizeof(array[0]))

#define FIELDOFFSET(type,field)     ((int)((size_t)&(((type*)0)->field)))

#define MAX(a,b)        ((a) > (b) ? (a) : (b))
#define MIN(a,b)        ((a) < (b) ? (a) : (b))

#ifndef INT16
#define INT16 short
#endif

#endif  /* _SWDEF_H_ */


