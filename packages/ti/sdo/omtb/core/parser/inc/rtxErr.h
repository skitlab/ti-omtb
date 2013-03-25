/*
 * rtxerr.h
 *
 * Definitions for system error codes.
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

#ifndef _RTX_ERR_H_
#define _RTX_ERR_H_

/*******************************************************************************
 * DATA PURPOSE:  Define System Error Codes
 *
 * DESCRIPTION:   Following are the system error codes returned by the 
 *      system calls 
 ******************************************************************************/

enum MX_Result_e {
  ERR_NOERR      = 0,    /* no error occurred */
  ERR_INVNAME    = 1u,   /* no match for the given name */
  ERR_TIMEOUT    = 2u,   /* specified time elasped for system call */
  ERR_ASGN       = 3u,   /* the given name is already assigned */
                        
  ERR_NOTCB      = 4u,   /* no available Task Control Blocks */
  ERR_TIDINV     = 5u,   /* given task identifier is invalid */
  ERR_PRIINV     = 6u,   /* given priority level is out of range */
                        
  ERR_NOQCB      = 7u,   /* no available Queue Control Blocks */
  ERR_QIDINV     = 8u,   /* given queue identifier is invalid */
  ERR_QFULL      = 9u,   /* cannot post, the target queue is full */
  ERR_QEMPTY     = 10u,  /* requested queue is empty */
  ERR_QUNASGN    = 11u,  /* The QCB was either not assigned or deleted */
                
  ERR_NOEVT      = 12u,  /* requested event condition not met */
  ERR_DELETED    = 13u,  /* queue synched to this event was deleted */
                
  ERR_NOSCB      = 14u,  /* no available Semaphore Control Blocks */
  ERR_SIDINV     = 15u,  /* given semaphore identifier is invalid */
  ERR_NOSEM      = 16u,  /* requested semaphore is unavailable */
  ERR_SUNASGN    = 17u,  /* The SCB was either not assigned or deleted */

  ERR_NOMEM      = 18u,  /* not enough memory to satisfy the request */
  ERR_PPRIVATE   = 19u,  /* cannot allocate from private partition */
  ERR_NOSEG      = 20u,  /* no available Segment Control Blocks */
  ERR_SEGINV     = 21u,  /* given segment identifier is invalid */
  ERR_FREE       = 22u,  /* attempt to free an already free block */
  ERR_INVBLK     = 23u,  /* given block address is out of range */
  ERR_PARTINV    = 24u,  /* given partition ID is invalid */


  ERR_NOTMR      = 25u,  /* no available Timer Control Blocks */
  ERR_TMRINV     = 26u,  /* given timer identifier is invalid */
  ERR_TMREXP     = 27u,  /* timer expired */
  ERR_TMRIDLE    = 28,   /* attempt to abort an idle timer */
  ERR_TMRACTIVE  = 29,   /* attempt to start an active timer */
  ERR_NULLPTR    = 30,   /* NULL pointer passed as a parameter to 
                           Xspy or sprintf*/

  /* fatal error definitions */
  SYS_CONFIG_ERR                  = 31,
  SYS_MEM_CORRUPT                 = 32,
  SYS_NO_SUPPORT                  = 33,
  SYS_CRITICAL_SECTION_OVERFLOW   = 34,  /* exceeded max. nesting */
  SYS_CRITICAL_SECTION_UNDERFLOW  = 35,  /* tried to end > started  */
  SYS_ILLEGAL_REQUEST             = 36,  /* Too many timer requests */

  ERR_NOICB             = 37, /* GlobalAlloc for XiCreate failed */
                                
  ERR_NOSQCB            = 38, /* no available Sorted Queue Control Blocks */
  ERR_SQIDINV           = 39, /* given sorted queue identifier is invalid */
  ERR_SQFULL            = 40, /* cannot post, the target sorted queue is full */
  ERR_SQEMPTY           = 41, /* requested sorted queue is empty */
  ERR_SQUNASGN          = 42, /* The SQCB was either not assigned or deleted */
  ERR_INTR_NESTING      = 43, /* XiEnter & XiExit not balanced */
  ERR_HOST_API          = 44, /* Host OS API Call failed unexpectedly */
  ERR_RETURN_FROM_TASK  = 45, /* Task Function Returned */
  ERR_INV_HANDLE        = 46, /* Invalid Handle for other object type clk etc */
  ERR_INV_THREAD_FUNC   = 47, /* Invalid Thread Function specified */
  ERR_BLOCK_THREAD      = 48, /* Can't block a thread */
  ERR_NONTASK           = 49, /* Function or mode not supported in 
                              ** nontask model or mode */
  ERR_PRI_LIMIT         = 50, /* thread run hit priority limit */
  ERR_RUN_LIMIT         = 51, /* thread run hit count limit */
  ERR_TASK_THREAD_RUN   = 52, /* thread run encounted a task */ 
  ERR_ALREADY_SLEEPING  = 53, /* thread already sleeping with
                              ** a sleep done function */
  ERR_NOT_DBG_TASK      = 54, /* A Debug Task API was called from
                              ** another task */

  /* Debug Command Enhancement Error Definitions */
  ERR_END_OF_CMD        = 55,
  ERR_NUM_ENUM                  /* Marker for the last error + 1 */
};

typedef enum MX_Result_e MX_Result;

typedef MX_Result MX_ErrorCode;
extern MX_Result XdbgPutS (char *strPtr);
extern int Xsprintf(char *str, char *fmt, ...);

#endif /* !defined(_RTX_ERR_H_) */
