/*
 * omtbMain.h
 *
 * This file includes data types, defines etc for OMTB core files.
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

#ifndef __OMTB_MAIN_H__
#define __OMTB_MAIN_H__


/******************************************************************************\
*     Includes
\******************************************************************************/

#include <stdio.h>
#include "mxDbg.h"


/******************************************************************************/
 
#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
*     Defines
\******************************************************************************/

#define OMTB_BS_CHAR                    (0x8)
#define OMTB_SPACE_CHAR                 (" ")
#define OMTB_MAX_LEN                    (512)
#define OMTB_MAX_FRM_SZ_BYTES           (10)  /* Required for video decoders */
#define OMTB_LOOP                       (OMX_TRUE)
#define OMTB_PROMPT                     ("OMTB> ")
#define OMTB_APP_EXIT_CMD_STR           ("exit")
#define OMTB_KHRONOS_TS_CMD_STR         ("omx conf")
#define OMTB_MAX_INS                    (16)
#define OMTB_MAX_TUNNELS                (16)
#define OMTB_MAX_TEMPLATE               (10)
#define OMTB_MAX_FRAME                  (5000)
#define OMTB_INVALID_PARAM              (-1)
#define OMTB_OMX_CMD_STR                ("omx")
#define OMTB_APP_HELP_CMD_STR           ("help")
#define OMTB_APP_SLEEP_CMD_STR          ("sleep")
#define OMTB_APP_COMMENT_CMD_STR        ("#")  
#define OMTB_APP_WAITFOREOS_CMD_STR     ("waitforeos")  
#define OMTB_APP_EOS_CMD_STR            ("eos")  
#define OMTB_SEM_TIMEOUT                (10000)
#define OMTB_DEMO_CMD                   ("omtbdemo")
#define OMTB_RUN_DEMO_TIME              (10000)
/* Max data types limits */

#define OMTB_MIN_VAL_S8                 (-128)
#define OMTB_MAX_VAL_S8                 (0x7F)
#define OMTB_MIN_VAL_U8                 (0)
#define OMTB_MAX_VAL_U8                 (0xFF)

#define OMTB_MIN_VAL_S16                (-32768)
#define OMTB_MAX_VAL_S16                (0x7FFF)
#define OMTB_MIN_VAL_U16                (0)
#define OMTB_MAX_VAL_U16                (0xFFFF)

#define OMTB_MIN_VAL_S32                (-2147483648)
#define OMTB_MAX_VAL_S32                (0x7FFFFFFF)
#define OMTB_MIN_VAL_U32                (0)
#define OMTB_MAX_VAL_U32                (0xFFFFFFFF)


/* OMTB script handling related defines */
#define OMTB_SCRIPT_CMD_LINE_ARG_CNT    (3)
#define OMTB_SCRIPT_OPTION              ("-s")
#define OMTB_SCRIPT_OPTION_IDX          (1)
#define OMTB_SCRIPT_NAME_IDX            (2)

/* OMTB Application Version Number */
#define OMTB_REL_INFO_STRING            ("OMTB_v01.00.01.05")

#define OMTB_ARM_LOAD_GROUP_PRIORITY    (2)         /* Task group priority */
#define OMTB_ARM_LOAD_TSK_STACK_SIZE    (30 * 1024) /* Task stack size */

/******************************************************************************\
*     Data type definitions
\******************************************************************************/

 /* Enum for OMTB Return Values */
typedef enum OmtbRet
{
  OMTB_NOT_SUPPORTED          = -3, /* Not supported */
  OMTB_INSUFFICIENT_RESOURCES = -2, /* Insufficient resources */
  OMTB_FAIL                   = -1, /* Error */
  OMTB_SUCCESS                =  0, /* Success */
  OMTB_NOTSUPPORTED
}OmtbRet;

/* Enum for selecting I/P or O/P mode */
typedef enum OmtbDataMode
{
  OMTB_FILE,
  OMTB_DRIVER,
  OMTB_NONE
} OmtbDataMode;
 
/******************************************************************************\
*     Macros
\******************************************************************************/


/******************************************************************************\
*     Globals
\******************************************************************************/


/******************************************************************************\
*     External Object Definitions 
\******************************************************************************/


/******************************************************************************\
*     Public Function Prototypes
\******************************************************************************/

/******************************************************************************\
 *      OMTB_Main Function Definition
\******************************************************************************/
/*
 *
 *  @brief    This function is the entry point of program 
 *
 *  @param in:
 *            argc: No of arguments  
 *            argv: Array of pointers containing the strings enetered 
 *                  through command line
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            OMTB_SUCESS
 *            OMTB_FAIL
 *
 */

int OMTB_Main (int argc, char ** argv);

/******************************************************************************\
 *      OMTB_RunScript Function Prototype
\******************************************************************************/
/*
 *
 *  @brief   
 *            This function runs the DVS script containing set of commands.
 *
 *  @param in:
 *            scriptFileName: Pointer to script file name
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            ERR_NOERR           successful,
 *
 *            ERR_INVNAME         Incorrect template number/Memory allocation 
 *                                error.
 */

MX_Result OMTB_RunScript( char *scriptFileName);


/******************************************************************************\
 *      OMTB_CmdParse Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    This function copies the content from command line into a local
 *            buffer and send it for further parsing 
 *
 *  @param in:
 *            argc: No of arguments  
 *            argv: Array of pointers containing the strings enetered 
 *                  through command line
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            None
 */

void OMTB_CmdParse (int argc, char ** argv);


/******************************************************************************\
 *      procCmdLine Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    
 *            This function processes OMTB commands and parses the command 
 *            into tokens.
 *
 *  @param in:
 *            cmdStrPtr: Pointer to input command string
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            ERR_NOERR           successful,
 *
 *            ERR_INVNAME         Incorrect template number/file name.
 */

/* This function is defined in cmdLine.c file but declaration is added here to 
   avoid separate header file for the single function of the command parser */
void procCmdLine(char *cmdStrPtr);


/******************************************************************************\
 *      OMTB_ReadScript Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    This function reads one line from the file and store it in buff
 *            component 
 *
 *  @param in:
 *            fp: Script file pointer
 *
 *            line: character Pointer for storing the read line
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            nBytes : No of bytes read
 *
 */

int OMTB_ReadScript(FILE *fp, char *line);


#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file ------------------------------*/
