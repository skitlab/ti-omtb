/*
 * omtbVideoM3Debug.h
 *
 * This file contains platform specific debug log levels, log display
 * defines and API timing calculation macros.
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

#ifndef __OMTB_DEBUG_H__
#define __OMTB_DEBUG_H__


/******************************************************************************\
*     Includes
\******************************************************************************/
//#define OMTB_OMX_API_TIMING_ENABLE 1
#include "omtbMain.h"
#if OMTB_OMX_API_TIMING_ENABLE == 1
#include <sys/time.h>
#endif

/******************************************************************************/
 
#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
*     Defines
\******************************************************************************/

#define APP_PRINT_LEVEL       (PRINT_NO_OUTPUT)
#define PRINT_NO_OUTPUT       (0x00)          /* Remove All Print Messages */
#define PRINT_SIMPLE_MESSAGE  (0x02)          /* Print Simple Message */
#define DEFAULT_MESSAGES      (0x04)          /* Print Default Message */
#define PRINT_FUNCTION_NAME   (0x08)          /* Print Function Name*/
#define PRINT_DEBUG_MESSAGE   (0x10)          /* Print Debug Mesaage */
#define PRINT_SET_PARAM       (0x20)          /* Print the info for Set Param / Set config */    
#define PRINT_GET_PARAM       (0x40)          /* Print the info for Get Param / Get config */
#define PRINT_MUST            (0x80)          /* Print Compulsary Mesaage */
#define PRINT_ERR_MSG         (0x80)          /* Print Error Mesaage */

#define PRINT_LEVEL           (APP_PRINT_LEVEL | PRINT_MUST | PRINT_ERR_MSG | PRINT_GET_PARAM)


/******************************************************************************\
*     Includes
\******************************************************************************/

/* Flag to change OMTB debug log level */
extern unsigned int omtbDbgLogLevel;


/******************************************************************************\
*     Data type definitions
\******************************************************************************/


/******************************************************************************\
*     Macros
\******************************************************************************/

#if PRINT_LEVEL > 0

  #define PRINT(n, args...) if ((PRINT_LEVEL | omtbDbgLogLevel) & (n))  \
                            {                                           \
                              fprintf(stdout, "OMTB-");                 \
                              fprintf(stdout, args);                    \
                            }

#else 

  #define PRINT(n, args...) if ((PRINT_LEVEL | omtbDbgLogLevel) & (n))  \
                            {                                           \
                              fprintf(stdout, "OMTB-");                 \
                              fprintf(stdout, args);                    \
                            }

#endif  // #if PRINT_LEVEL > 0

/* Macro to declare API timing calculation variables */
#if OMTB_OMX_API_TIMING_ENABLE == 1

  #define OMTB_OMX_API_TIMING_VAR_DECL                                  \
    struct timeval enteringAPI, leavingAPI;                             \
    OMX_U64 enteringTime = 0, leavingTime = 0, timingDifference = 0;

#else

  #define OMTB_OMX_API_TIMING_VAR_DECL 

#endif  // #if OMTB_OMX_API_TIMING_ENABLE == 1

/* Macro to get API Entering Time */

#if OMTB_OMX_API_TIMING_ENABLE == 1

  #define OMTB_OMX_API_ENTRY_TIME_CALC                                  \
  {                                                                     \
    gettimeofday(&enteringAPI, 0);                                      \
  }

#else

  #define OMTB_OMX_API_ENTRY_TIME_CALC 

#endif  // #if OMTB_OMX_API_TIMING_ENABLE == 1


/* Macro to get API Leaving Time and display the time taken by API */
#if OMTB_OMX_API_TIMING_ENABLE == 1

  #define OMTB_OMX_API_EXIT_TIME_CALC(__OMX_API_NAME__)                       \
  {                                                                           \
    gettimeofday(&leavingAPI,0);                                              \
    enteringTime = ((enteringAPI.tv_sec * 1000 * 1000) + enteringAPI.tv_usec);\
    leavingTime  = ((leavingAPI.tv_sec * 1000 * 1000) + leavingAPI.tv_usec);  \
    timingDifference = (leavingTime - enteringTime);                          \
    PRINT(PRINT_MUST,"Time Taken by %s: %llu usecs\n",                          \
                      __OMX_API_NAME__, timingDifference);                    \
  }

#else

  #define OMTB_OMX_API_EXIT_TIME_CALC(__OMX_API_NAME__)  

#endif  // #if OMTB_OMX_API_TIMING_ENABLE == 1


/******************************************************************************\
*     Globals
\******************************************************************************/


/******************************************************************************\
*     External Object Definitions 
\******************************************************************************/


/******************************************************************************\
*     Public Function Prototypes
\******************************************************************************/


#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file ------------------------------*/
