/*
 * omtbCortexA8Main.c
 *
 * Platform specific main and entry task definition.
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
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* OMX standard header files */
#include <xdc/std.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/System.h>

#include <xdc/runtime/Timestamp.h>
//#include <xdc/cfg/global.h>
#include <ti/ipc/Ipc.h>
#include <xdc/runtime/knl/Thread.h>

#include "omtbMain.h"
#define USE_SCRIPT
extern void platform_init();
extern void platform_deinit();


/** 
 *  DUCATI_APP_TASK_SLEEP_DURATION, the Test Application sleeps for this 
 *  duration before verifying the indication for application termination.
 *  This value is in ms.
*/
#define  DUCATI_APP_TASK_SLEEP_DURATION (10000u)

#define Global_appTerminate 0


/* set to omtbArgc = 1 for BIOS, BIOS doesn't counts executable name for cmd line args */
static int omtbArgc = 0;
static char *omtbArgv[OMTB_SCRIPT_CMD_LINE_ARG_CNT] =
                                        {NULL, OMTB_SCRIPT_OPTION, NULL};

void OMTB_CotexA8Task (int argc, char *argv[])
{
  int inMode = 0;
  char scriptName[OMTB_MAX_LEN] = {'\0'};
  char scriptModeFlag = {'\0'};
  OmtbRet result = OMTB_SUCCESS;
   
  do
  {
    if(OMTB_SCRIPT_CMD_LINE_ARG_CNT != omtbArgc)
    {
#ifdef USE_SCRIPT
      /* select the input mode */
#if 0	  
      printf("Select Script Mode(1)/Cmd Line Mode(2): ");
      scanf("%d", &inMode);
      fflush(stdin);
#endif	 
      inMode = 2; 
      if(1 == inMode)
      {
        /* read the script file name for script mode */
       
	    printf("Enter the script file name including path: ");
        fflush(stdout);
        fgets(scriptName, OMTB_MAX_LEN, stdin);
        fflush(stdin);
        omtbArgv[OMTB_SCRIPT_NAME_IDX] = scriptName;		
       
        printf("Script name: %s\n", omtbArgv[OMTB_SCRIPT_NAME_IDX]);
        omtbArgc = OMTB_SCRIPT_CMD_LINE_ARG_CNT;
      }
      else
      {
        /* set the argc count to zero for cmd line mode */
        omtbArgc = 0;
      }
#else
      strcpy(scriptName, "./omtb_dss.oms");
      omtbArgv[OMTB_SCRIPT_NAME_IDX] = scriptName;
      printf("Script name: %s\n", omtbArgv[OMTB_SCRIPT_NAME_IDX]);
      omtbArgc = OMTB_SCRIPT_CMD_LINE_ARG_CNT;
#endif
    } // if(0 == omtbArgc)

    /* Invoke OMTB entry function */
    result = (OmtbRet)OMTB_Main(omtbArgc, omtbArgv);

    if(OMTB_SUCCESS != result)
    {
      printf("Error returned from OMTB_Main(): %d\n", result);
    }
#ifdef USE_SCRIPT
    /* ask for continue*/
    //printf("Do you want to continue (y/n): ");
    //scanf("%c", &scriptModeFlag);
    scriptModeFlag = 'n';	
#else
    scriptModeFlag = 'n';
#endif
    if('n' == scriptModeFlag)
    {
      /* Exit the loop */
      break;
    }
    else
    {
      omtbArgc = 1;
      continue;
    }

  }while((1 != inMode) || (2 != inMode));
  
  printf("Leaving <Function:%s>\n", __FUNCTION__);  
}


/*
 * ===  FUNCTION  ==============================================================
 *         Name:  main
 *  Description:  Main entry for Ducati Video M3 subsystem
 * =============================================================================
 */
int main(int argc, char ** argv)
{
  int i = 0, j = 0;
  
  Thread_start(NULL);
  platform_init();

  if (argc > OMTB_SCRIPT_OPTION_IDX)
  {
    /* increment the argc count to add -s option */  
    if (0 != strcmp((char *)argv[OMTB_SCRIPT_OPTION_IDX], OMTB_SCRIPT_OPTION))
	{
      argc++;
	}   
  }
  
  if(OMTB_SCRIPT_CMD_LINE_ARG_CNT <= argc)
  {
    /* added count as BIOS doesn't counts executable name for cmd line args */
    omtbArgc += argc;
    for(i = 1, j = 1; i < argc; i++)
    {
      if (0 != strcmp((char *)argv[OMTB_SCRIPT_OPTION_IDX], OMTB_SCRIPT_OPTION) && (i == OMTB_SCRIPT_OPTION_IDX))
        omtbArgv[i] = OMTB_SCRIPT_OPTION;  	  
	  else 
	  {
        omtbArgv[i] = argv[j];
	    j++;
	  } 
    }
  }
  
  OMTB_CotexA8Task(argc, argv);

  platform_deinit ();
  exit (0);
}/* main */

/*------------------------------ end of file ---------------------------------*/

