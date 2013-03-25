/*
 * omtbMain.c
 *
 * Initial initialization, parsing, template configuration and script handling
 * code.
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

/******************************************************************************\
 *      Standard Includes
\******************************************************************************/
//#undef USE_LIBEDIT 
#define OMTB_DEMO

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef OMTB_DEMO
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#endif

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
//#include "OMX_TI_Video.h"
#include "OMX_TI_Index.h"



/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"
#ifdef USE_LIBEDIT 
#include "readline.h"
#endif
#include "mxDbg.h"
#include "omtbMain.h"
#include "omtbCommon.h"
#include "omtbCmd.h"
#include "omtbAppInit.h"
#include "omtbTemplateManager.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


/******************************************************************************\
 *      Extern Object Definitions 
\******************************************************************************/

/* command table used for setp/getp/store cfg commands */
extern MX_DBG_CMD_TABLE_T   setpCmdTbl;

/* Template params */
extern OMTB_TEMPLATE_INFO *omtbCfgTemplate[OMTB_MAX_INS];

/* OMTB class array */
extern OMTB_COMP_HANDLE omtbClass[OMTB_MAX_CLASS];

#ifdef OMTB_DEMO
/* error number */
extern int errno;
#endif
/******************************************************************************\
 *      Globals 
\******************************************************************************/

/* Flag to toggle arm CPU load dispplay */
unsigned int armCpuLoadDispFlag = OMX_FALSE;

/* Flag to toggle component log dispplay */
int globDebugDisable = OMX_TRUE;

/* Flag to change OMTB debug log level */
unsigned int omtbDbgLogLevel = OMX_FALSE;

/* Flag to control ARMM CPU load display task exit */
unsigned int armCpuLoadDispTaskExitFlag = OMX_FALSE;

/* ARM CPU Load display thread ID */
void *cpuLoadDispThreadId = NULL;

/* End of Stream Semaphore */
void *gOmtbEofSem = NULL;

/*  Vdec Demo Semaphore */
volatile void *gOmtbVdecDemoSem = NULL;

/* Stop flag for Vdec demo*/
volatile OMX_BOOL gOmtbStopVdecDemoFlag = OMX_FALSE;

/*  Venc Demo Semaphore */
volatile void *gOmtbVencDemoSem = NULL;

/* Stop flag for Venc demo*/
volatile OMX_BOOL gOmtbStopVencDemoFlag = OMX_FALSE;

/* Buffer to store the commands */
char gInputCmd[4096][512] = {'\0'};

/* Flag to check if the command had to be copied or not */
volatile unsigned int gCopyCommand = OMX_FALSE;

/* No of valid command in the buffer */
int gCmdCount = 0;

/* no of iterations the commands should execute */
int gLoopCount = 0;
/******************************************************************************\
 *      Public Function Prototype
\******************************************************************************/


/******************************************************************************\
 *      Static Globals
\******************************************************************************/


/******************************************************************************\
 *      Private Function Declarations 
\******************************************************************************/

/******************************************************************************\
 *      OMTB_CpuLoadDispTask Function Definition
\******************************************************************************/
/*
 *
 *  @brief    
 *            This thread prints the CPU load once in a second.
 *
 *  @param in:
 *            threadArg: Thread arguments
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            None
 */

static void OMTB_CpuLoadDispTask(void *threadArg);


/******************************************************************************\
 *      OMTB_GetCpuStatsDuration Function Prototype
\******************************************************************************/
/*
 *
 * \brief 
 *    Displays the % of CPU usage once in a second for the duration of secs+1.
 * 
 *    This API reads the /proc/stat CPU usage and idle time between a second and
 *    calculates the the % of CPU usage.
 *    The first row of this file has the numbers identify the amount of time 
 *    the CPU has spent performing different kinds of work.
 *  
 *    The first four numbers of this row (except the string "CPU") is idetified 
 *    as follows.
 *      1. user: normal processes executing in user mode 
 *      2. nice: niced processes executing in user mode 
 *      3. system: processes executing in kernel mode 
 *      4. idle: twiddling thumbs 
 *
 * \param secs
 *        None - For OMTB_QNX and OMTB_LINUX
 *        secs - Number of seconds this function to display the CPU load.
 * \return 
 *        None
 */

#ifdef ARM_CPU_LOAD
static void OMTB_GetCpuStatsDuration(int secs);
#endif


/******************************************************************************\
 *      OMTB_ReadScript Function Definition
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
 *            nBytes : # of bytes read, -1 if blank line and 0 if EOF 
 *
 */
extern char omtbScript[2000][128];

int OMTB_ReadScript(FILE *fp, char *line)
{
  int nBytes = 0;
  char *buff = NULL;

#ifndef USE_SCRIPT  
  static int scriptIndex = 0;
#endif
  
#ifdef USE_SCRIPT
  /* Read one line from the specified file */
  buff = fgets(line, OMTB_MAX_LEN, fp);
  
  if (NULL == buff && feof(fp))
  {
    nBytes = OMX_FALSE;
  }
  /* Hash # is used as character for comments */
  else if(NULL == buff)
  {
    nBytes = -1;
  }
  else if(NULL != buff && feof(fp))
  {
    nBytes = strlen(buff);
    buff[nBytes] = 0;
  }
  else
  {
    /* Decrease string length by one to exclude new line character and replace 
       it by NULL */
    nBytes = strlen(buff) - 1;
    buff[nBytes] = 0;
  }
#else

  /* Read one line from the buffer */
  buff = strcpy(line, omtbScript[scriptIndex]);
  
  nBytes = strlen(buff);
  
  /* To Handle the blank Lines*/
  if(NULL == nBytes)
    nBytes = -1;
    
  /* Increment the script index*/
  scriptIndex++;
 
 #endif  
  return nBytes;
}


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

int OMTB_Main (int argc, char ** argv)
{
  unsigned int useScript = FALSE;
  int i = 0, j = 0;
  unsigned int template = 0;
  char inputCmdLine[OMTB_MAX_LEN] = {'\0'};
#ifdef USE_LIBEDIT  
  char *buff = NULL;
#endif
  char *script = NULL;
  MX_Result result = ERR_NOERR;
  int threadRes = TIMM_OSAL_ERR_NONE;
  OmtbRet omtbRetCode = OMTB_SUCCESS;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function:%s>\n", __FUNCTION__);
  
  /* OMTB application platform specific initialization */
  OMTB_AppInit();
  
  /* Reset all available template pointers */
  for (i = 0; i < OMTB_MAX_TEMPLATE; i++)
    omtbCfgTemplate[i] = NULL;

  /* Reset all the handle pointers */
  for(i = 0; i < OMTB_MAX_CLASS - 1; i++)
  {
    for(j = 0; j < OMTB_MAX_INS; j++)
      omtbClass[i].handle[j] = NULL;

  }

  /* Allocate the default configuration template */
  result = OMTB_AddCfg(template);
  if(ERR_NOERR != result)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error adding the template memory\n",\
                                    __FUNCTION__);
    return (OMTB_FAIL);
  }

  /* Default template is 0 */
  omtbCfgTemplate[template]->currTemplate = template;
  
  /* Reset CPU load task exit flag */
  armCpuLoadDispTaskExitFlag = OMX_FALSE;

  /* Create the thread to display ARM CPU load per second */
  threadRes = TIMM_OSAL_CreateTask(
                        (void *)&cpuLoadDispThreadId,
                        (TIMM_OSAL_TaskProc)OMTB_CpuLoadDispTask,
                        0,
                        NULL,
                        OMTB_ARM_LOAD_TSK_STACK_SIZE,
                        OMTB_ARM_LOAD_GROUP_PRIORITY,
                        (signed char*)"ARM_CPU_LOAD_CALC_TSK");
  
  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG, "Unable to start CPU load display task\n");  
  }
  
  /* create a semaphore to handle EOS for proprietary tunnelling */
  TIMM_OSAL_SemaphoreCreate(&gOmtbEofSem, 0);

  /* oms script input */
  if (OMTB_SCRIPT_CMD_LINE_ARG_CNT <= argc)
  {
    if (0 == strcmp((char *)argv[OMTB_SCRIPT_OPTION_IDX], OMTB_SCRIPT_OPTION))
    {
      script = (char *)argv[OMTB_SCRIPT_NAME_IDX];
      useScript = OMX_TRUE;
    }

    if (useScript)
    {
      /* run the script */
      result = OMTB_RunScript(script);
	  
      /* Set the ARM CPU load task exit flag */
      armCpuLoadDispTaskExitFlag = OMX_TRUE;
      
      if(ERR_NOERR != result)
      {
        PRINT(PRINT_ERR_MSG, "Error in opening script file %s\n",\
                              script);

        omtbRetCode = OMTB_FAIL;

      }  // if(ERR_NOERR != result)
      else
      {
        omtbRetCode = OMTB_SUCCESS;
      }

    }   // if (useScript)
    
  }   // if (argc >= 3)
  else 
  {
    /* Command line input - With/without libedit library */
    
#ifndef USE_LIBEDIT  /* If libedit library is not used */
    while(OMTB_LOOP)
    {
      /* OMTB command prompt */
      printf("\n");
      printf("%s", OMTB_PROMPT);
      fflush(stdout);
        
      /* read the input from the command line */
      gets(inputCmdLine);

      /* exit the application */
      if(0 == strcmp(inputCmdLine, OMTB_APP_EXIT_CMD_STR))
      {
        /* Set the ARM CPU load task exit flag */
        armCpuLoadDispTaskExitFlag = OMX_TRUE;
        
        PRINT(PRINT_MUST,"OMTB application finished\n");
        break;
      }
      /* switch to Khronos OMX Conformance Test Suite */
      else if(0 == strcmp(inputCmdLine, OMTB_KHRONOS_TS_CMD_STR))
      {
        PRINT(PRINT_MUST, "OMX Conformance Test Bench Start\n");
//        omx_conformance_main(1, NULL);
        PRINT(PRINT_MUST, "OMX Conformance Test Bench Exit\n");
      }
	  
      else
      {
        /* parse and process the command */
        procCmdLine(inputCmdLine);
      }
    }   // while(OMTB_LOOP)
    
#else             /* If libedit library is used */

    while(OMTB_LOOP)
    {
      printf("\n");

      /* read input from the command line */
      buff = readline((const char *)OMTB_PROMPT); 
      
      if(NULL == buff)
      {
        /* Set the ARM CPU load task exit flag */
        armCpuLoadDispTaskExitFlag = OMX_TRUE;
        
        omtbRetCode = OMTB_FAIL;
        break;
      }

      /* copy the command into local string variable */
      strcpy(inputCmdLine, buff);

      /* add the command to history */
      add_history(inputCmdLine);
      
      /* exit the application */
      if(0 == strcmp(inputCmdLine, OMTB_APP_EXIT_CMD_STR))
      {
        /* Set the ARM CPU load task exit flag */
        armCpuLoadDispTaskExitFlag = OMX_TRUE;
        
        PRINT(PRINT_MUST, "OMTB Exit\n");
        break;
      }
      /* switch to Khronos OMX Conformance Test Suite */
      else if(0 == strcmp(inputCmdLine, OMTB_KHRONOS_TS_CMD_STR))
      {
        PRINT(PRINT_MUST, "OMX Conformance Test Bench Start\n");
//        omx_conformance_main(1, NULL);
        PRINT(PRINT_MUST, "OMX Conformance Test Bench Exit\n");
      }
      else
      {
        /* parse and process the command */
        procCmdLine(inputCmdLine);
      }
      
    }   // while(OMTB_LOOP)
    
#endif
  }   /* if (argc >= 3) ... else ... */
 
  /* delete a semaphore used to handle EOS for proprietary tunnelling */
  TIMM_OSAL_SemaphoreDelete(gOmtbEofSem);
	  
  // Release the template memory if allocated
  for (i = 0; i < OMTB_MAX_TEMPLATE; i++)
  {
    if(NULL != omtbCfgTemplate[i])
    {
      result = OMTB_RemoveCfg(i);
      if(ERR_NOERR != result)
        omtbRetCode = OMTB_FAIL;
    }
      
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function:%s>\n", __FUNCTION__);
  
  return omtbRetCode;
}


/******************************************************************************\
 *      OMTB_RunScript Function Definition
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

MX_Result OMTB_RunScript( char *scriptFileName)
{
  FILE *scriptFp = NULL;
  char inputCmdLine[OMTB_MAX_LEN] = {'\0'};
  int nBytes = 0;

  /* open the script file */
#ifdef USE_SCRIPT  
  scriptFp = fopen(scriptFileName, "rb");
  
  if(NULL == scriptFp)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in opening script file %s\n",\
                                __FUNCTION__, scriptFileName);
    return ERR_INVNAME;
  }
#endif  
  while(OMTB_LOOP)
  {
    nBytes = 0;

    /* read the commands from the script */
    nBytes = OMTB_ReadScript(scriptFp, &(inputCmdLine[nBytes]));
    if(OMX_FALSE == nBytes)
    {
      /* Exit the loop when there is no data available from the file */
      break;
    }
    else if(OMTB_INVALID_PARAM == nBytes)
    {
      /* received the blank line, continue reading next line */
      continue;
    }
    else
    {
      PRINT(PRINT_MUST, "\r     \nOMTB> %s\n", inputCmdLine);
      procCmdLine(inputCmdLine);
      continue;
    }
    
  } // while(OMTB_LOOP)
#ifdef USE_SCRIPT
  /* Close the script file */
  fclose(scriptFp);
#endif
  return ERR_NOERR;
}

/******************************************************************************\
 *      OMTB_RunDemo Function Definition
\******************************************************************************/
/*
 *
 *  @brief    This function handles the  demo
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
#ifdef OMTB_DEMO	 
void OMTB_RunDemo (int argc, char ** argv)
{ 
  FILE * ps_ups_fp = NULL;
  int ps_cmd_recvd = 0;
  int size_read = 0;
  char ps_ups_cmd[2] ={0, 0};
  int np = 0;
  int i = 0;
  unsigned int omtbRunDemoTime = OMTB_RUN_DEMO_TIME;
  char omtbNamedPipe[OMTB_MAX_LEN]={0};
  
  /*Set the default value */
  strcpy(omtbNamedPipe, "./pu_pipe");
  
  /* copy the values from args */
  for(i = 1; i <argc; i++)
  {
    /* copy the values from Args */  
    if(0 == strncmp("t", argv[i], 1)) 
	{
      omtbRunDemoTime = atoi(argv[i+1]); 
	  i++;
	}
	else if(0 == strncmp("p", argv[i], 1)) 
	{
      strcpy(omtbNamedPipe, argv[i+1]);
	  i++;
	}
    else	
     PRINT(PRINT_ERR_MSG, "Invalid Arg:%s\n", argv[i]);	
  }
  
  /* create a semaphore to handle Unpause of Demo */
  /* create semaphore for the first time/only once */
  if(NULL == gOmtbVdecDemoSem)
    TIMM_OSAL_SemaphoreCreate(&gOmtbVdecDemoSem, 0);	
  
  if(NULL == gOmtbVencDemoSem)
    TIMM_OSAL_SemaphoreCreate(&gOmtbVencDemoSem, 0);		
					 
  /*Stop the demo which was already running*/
  gOmtbStopVdecDemoFlag = OMX_TRUE;
  gOmtbStopVencDemoFlag = OMX_TRUE;
		 
  /* Create the named pipe */
  np = mkfifo (omtbNamedPipe, 0644);

  if (np != 0)
  {
    if(EEXIST != errno)
	{  
     PRINT(PRINT_ERR_MSG, "Unable to create Named PIPE:%s\n", omtbNamedPipe);
     return;	
	}
	else
     PRINT(PRINT_DEBUG_MESSAGE, "PIPE already exists:%s\n", omtbNamedPipe);	
  } 
		
  /* Open the named pipe */
  ps_ups_fp = fopen (omtbNamedPipe, "r");
  if (NULL == ps_ups_fp)
  {
    PRINT(PRINT_ERR_MSG, "Unable to open named pipe for reading\n");
    return;	
  }	  	  

  /*OMTB loop controls the demo*/
  while(OMTB_LOOP)
  {
    /*Wait for the unpuase command from the controller */
    ps_cmd_recvd = 0;
    while(ps_cmd_recvd == 0)
    {
      size_read = fread(ps_ups_cmd, 1, sizeof(ps_ups_cmd), ps_ups_fp);
      
	  for (i = 0; i<size_read; i++)
      {
        PRINT(PRINT_DEBUG_MESSAGE, "%c\n", ps_ups_cmd[i]);
      }
        
      if(size_read > 0)
      {
        if(strncmp ("P", ps_ups_cmd, 1) == 0)
        {
          PRINT(PRINT_DEBUG_MESSAGE, "Selection: Pause\n");
        }
        else if (strncmp("U", ps_ups_cmd, 1) == 0)
        {
          PRINT(PRINT_DEBUG_MESSAGE, "Selection: UnPause\n");
          ps_cmd_recvd = 1;
        }
        else
        {
           PRINT(PRINT_ERR_MSG, "Unknown Selection\n");
        }
      }
	  else
      {
        /* Polling every 200 ms */
        TIMM_OSAL_SleepTask (200);
      }
    }
		  
    /*Start/Stop the demo*/
    {
      /* Release the semaphore to start the vdec demo*/
      TIMM_OSAL_SemaphoreRelease(gOmtbVdecDemoSem);

      /* Release the semaphore to start the venc demo*/
      TIMM_OSAL_SemaphoreRelease(gOmtbVencDemoSem);
	  	  
      PRINT(PRINT_MUST, "Sleep for %d milli seconds\n", omtbRunDemoTime);			
      TIMM_OSAL_SleepTask (omtbRunDemoTime);	

      /* Stop the demo*/ 
	  gOmtbStopVdecDemoFlag = OMX_TRUE; 			
	  gOmtbStopVencDemoFlag = OMX_TRUE; 
    } 	  
  }
  
  /* Delete the semaphore */
  TIMM_OSAL_SemaphoreDelete(gOmtbVdecDemoSem);  
  TIMM_OSAL_SemaphoreDelete(gOmtbVencDemoSem);  
}		
#endif

/******************************************************************************\
 *      OMTB_CmdParse Function Definition
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

void OMTB_CmdParse (int argc, char ** argv)
{
  int i = 0;
  char  *pStr = NULL;
  int sleepTime = 10000;
  
  if(1u > argc)
  {
    return;
  }  

#ifdef OMTB_DEMO	 
  if(0 == strcmp(argv[0], OMTB_DEMO_CMD))
  {
    OMTB_RunDemo(argc, (char **)argv);
	return;
  }  
#endif

  /* Reconstruct the command line from the (argc, argv[]) format */
  for( i = 0; i < (argc - 1u); i++ )
  {
    pStr = argv[i];
    pStr[strlen((char *)pStr)] = ' ';
  }  // for( i = 0; i < (argc - 1u); i++ )

  pStr = argv[i];
  pStr[strlen((char *)pStr)] = '\0';
  pStr = argv[1];
  
  
  /* Copy all the commands if the flag is enabled*/
  if(gCopyCommand == OMX_TRUE)
  {
    /* Copy the commands to the buffer*/
	strncpy(gInputCmd[gCmdCount], argv[0], (strlen(argv[0]) + 1));
    gCmdCount++; 
  }  
  
  if (0 == memcmp(argv[0], OMTB_OMX_CMD_STR, strlen(OMTB_OMX_CMD_STR)))
  {
    /* Invoke the omx command processing function */
    OMTB_CmdParseOmx(argc, (char **)argv);
  }
  else if(0 == memcmp(argv[0], OMTB_APP_HELP_CMD_STR, 
          strlen(OMTB_APP_HELP_CMD_STR)))
  {
    /* Invoke the omx command processing function */
    OMTB_CmdParseOmx(argc, (char **)argv);
  }
  else if(0 == memcmp(argv[0], OMTB_APP_SLEEP_CMD_STR,
          strlen(OMTB_APP_SLEEP_CMD_STR)))
  {
    PRINT(PRINT_MUST, "OMTB script reading task sleeping for %d msecs\n", atoi(argv[1]));
#ifndef WTSD_TEMP // To avoid TIMM OSAL build issues    
    sleepTime = atoi(argv[1]);
    TIMM_OSAL_SleepTask(sleepTime);
#endif
    PRINT(PRINT_MUST, "OMTB script reading task resumed from sleep\n");
  }
  else if(0 == memcmp(argv[0], OMTB_APP_COMMENT_CMD_STR,
          strlen(OMTB_APP_COMMENT_CMD_STR)))
  {
  	/* Do nothing:Ignore the command*/
  }
  else if(0 == memcmp(argv[0], OMTB_APP_WAITFOREOS_CMD_STR,
          strlen(OMTB_APP_WAITFOREOS_CMD_STR)))
  {
    /* Wait for EOS */

    TIMM_OSAL_SemaphoreObtain(gOmtbEofSem, TIMM_OSAL_SUSPEND);
  }
  else
  {
    PRINT(PRINT_MUST, "Unknown command : %s\n", argv[0]);
    PRINT(PRINT_MUST, "Enter \'help\' or \'omx\' for more info...\n");
  }
  return;
}


/******************************************************************************\
 *      OMTB_CpuLoadDispTask Function Definition
\******************************************************************************/
/*
 *
 *  @brief    
 *            This thread prints the CPU load once in a second.
 *
 *  @param in:
 *            threadArg: Thread arguments
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            None
 */

static void OMTB_CpuLoadDispTask(void *threadArg)
{

  PRINT(PRINT_DEBUG_MESSAGE,
                 "Entering %s thread\n", __FUNCTION__);

  while (OMX_FALSE == armCpuLoadDispTaskExitFlag) 
  {
    if (armCpuLoadDispFlag) 
    {
#ifdef ARM_CPU_LOAD    
        OMTB_GetCpuStatsDuration(0);
#endif        /* #ifdef ARM_CPU_LOAD */
    }
    else 
    {
#ifndef WTSD_TEMP // To avoid build issues for TIMM OSAL
       TIMM_OSAL_SleepTask (1);
#endif       
    }
    
  } // while(OMTB_LOOP)

  PRINT(PRINT_DEBUG_MESSAGE,
                 "Leaving %s thread\n", __FUNCTION__);

  /* exit the thread */
#ifdef WTSD_TEMP
  TIMM_OSAL_DeleteTask(cpuLoadDispThreadId);
#else
  TIMM_OSAL_ExitTask(cpuLoadDispThreadId, NULL);
#endif
}


/******************************************************************************\
 *      OMTB_GetCpuStatsDuration Function Definition
\******************************************************************************/
/*
 *
 * \brief 
 *    Displays the % of CPU usage once in a second for the duration of secs+1.
 * 
 *    This API reads the /proc/stat CPU usage and idle time between a second and
 *    calculates the the % of CPU usage.
 *    The first row of this file has the numbers identify the amount of time 
 *    the CPU has spent performing different kinds of work.
 *  
 *    The first four numbers of this row (except the string "CPU") is idetified 
 *    as follows.
 *      1. user: normal processes executing in user mode 
 *      2. nice: niced processes executing in user mode 
 *      3. system: processes executing in kernel mode 
 *      4. idle: twiddling thumbs 
 *
 * \param secs
 *        None - For OMTB_QNX and OMTB_LINUX
 *        secs - Number of seconds this function to display the CPU load.
 * \return 
 *        None
 */

#ifdef ARM_CPU_LOAD

static void OMTB_GetCpuStatsDuration(int secs)
{
  static FILE *fp = NULL;
  unsigned int u1,n1,s1,i1,w1,x1,y1, tUsage, tIdle;
  unsigned int u2,n2,s2,i2,w2,x2,y2;
  int num;
  /* enough for a /proc/stat CPU line (not the intr line) */
  char buf[50];

  do 
  {
    if (!fp) 
    {
  
      if (!(fp = fopen("/proc/stat", "r"))) 
      {
        PRINT(PRINT_MUST, "Failed /proc/stat open: %s", strerror(errno));  
        /* note: we allocate one more CPU_t than Cpu_tot so that the last slot*/
        /* can hold tics representing the /proc/stat cpu summary (the first   */
        /* line read) -- that slot supports our View_CPUSUM toggle            */
           
        TIMM_OSAL_SleepTask(secs);

        return;
      }
    }
  
    rewind(fp);
    fflush(fp);
    
    /* first value the last slot with the cpu summary line */
    if (!fgets(buf, sizeof(buf), fp))
    {
      fprintf(stderr, "failed /proc/stat read");
    }
    num = sscanf(buf, "cpu %u %u %u %u %u %u %u",
           &u1,
           &n1,
           &s1,
           &i1,
           &w1,
           &x1,
           &y1
           );
    if (num < 4)
    {
      fprintf(stderr, "failed /proc/stat read");
    }
  
    TIMM_OSAL_SleepTask(1);
      
    rewind(fp);
    fflush(fp);
    
    /* first value the last slot with the cpu summary line */
    if (!fgets(buf, sizeof(buf), fp))
    {
      fprintf(stderr, "failed /proc/stat read");
    }
    num = sscanf(buf, "cpu %u %u %u %u %u %u %u",
           &u2,
           &n2,
           &s2,
           &i2,
           &w2,
           &x2,
           &y2
           );
    if (4 > num)
    {
      fprintf(stderr, "failed /proc/stat read");
    }
  
    tUsage = (u2 - u1) + (n2 - n1) + (s2 - s1);
  
    tIdle = (i2 - i1);
  
    PRINT(PRINT_MUST,
               "ARM Cpu Usage %.2f\n", (double)(tUsage * 100) / (tUsage+tIdle));
  
    
  } while(secs--);

  fclose(fp);
}

#endif


/*----------------------------- end of file ---------------------------------*/
