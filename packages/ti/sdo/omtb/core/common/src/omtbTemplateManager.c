/*
 * omtbTemplateManager.c
 *
 * This file isMainly responsible for template handling commands.
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

#include <stdio.h>
#include <string.h>

/* OMX standard header files */
#include "OMX_Component.h"
#include "OMX_Types.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"
#include "mxDbg.h"
#include "omtbCommon.h"
#include "omtbTemplateManager.h"
#include "omtbCmd.h"
#include "omtbAppInit.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


/******************************************************************************\
 *      Extern Object Definitions 
\******************************************************************************/

extern MX_DBG_CMD_MODE_T  mx_dbg_cmd_mode;  // parser debug mode

/* command table used for setp/getp/store cfg commands */
extern MX_DBG_CMD_TABLE_T   setpCmdTbl;


/******************************************************************************\
 *      Globals 
\******************************************************************************/

/* OMTB configuration templates */
OMTB_TEMPLATE_INFO  *omtbCfgTemplate[OMTB_MAX_TEMPLATE];


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
 *      OMTB_StoreCfg Function Definition
\******************************************************************************/
/*
 *
 *  @brief   
 *            This function copies the default values of specified template to
 *            file.
 *
 *  @param in:
 *            pTemplate: Pointer to OMTB_TEMPLATE_INFO structure
 *
 *            cfgFileName: Pointer to configuration file name
 *
 *            template: Template no for which cfg is to be stored
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            ERR_NOERR           successful,
 *
 *            ERR_INVNAME         Incorrect template number/file name.
 */

MX_Result OMTB_StoreCfg( char *cfgFileName,
                         unsigned int template)
{
  OMTB_TEMPLATE_INFO *pTemplate = NULL;
  FILE *templateCfgFp = NULL;
  int i = 0, j = 0;
  void *paramLocation = NULL;
  MX_DBG_ENUM_ENTRY_T *enumTbl = NULL;
  MX_Result result = ERR_NOERR;
  
  if(OMTB_MAX_TEMPLATE <= template)
  {
    /* Invalid template */
    PRINT(PRINT_ERR_MSG, "Invalid template number %d -Valid range: <0 to %d>\n",
                          template, OMTB_MAX_TEMPLATE - 1);
    return ERR_INVNAME;
  }
  
  /* Allocate the template memory if it is not already allocated */
  result = OMTB_AddCfg(template);
  if(ERR_NOERR != result)
    return result;

  /* update the local copy of appropriate pointers */
  pTemplate = omtbCfgTemplate[template];
  
  /* Open the cfg file to write */
  templateCfgFp = fopen (cfgFileName, "wb");
  
  if(NULL == templateCfgFp)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error opening configuration file: %s\n",\
                                    __FUNCTION__, cfgFileName);
    return ERR_INVNAME;
  }

  /* Run the loop for available entries in SETP command table */
  for(i = 0; i < setpCmdTbl.max_entries - 1; i++)
  {
    int paramType = OMTB_INVALID_PARAM;
            
    /* Run the loop for available entries in algorithm configuration table */  
    for(j = 0; j < ((MX_DBG_CMD_TABLE_T*)setpCmdTbl.p_entries[i]->format)->max_entries - 1; j++)
    {
      fprintf(templateCfgFp, "%s ", setpCmdTbl.p_entries[i]->name);
      fprintf(templateCfgFp, "%s ", ((MX_DBG_CMD_TABLE_T*)setpCmdTbl.p_entries[i]->format)->p_entries[j]->name);
      
      if(NULL != ((MX_DBG_CMD_TABLE_T*)setpCmdTbl.p_entries[i]->format)->p_entries[j]->format)
      {
    	/* Used later for getting equivalent string for enum values */
    	paramType = MX_DBG_CMD_OPT_ENUM;
    	enumTbl = ((MX_DBG_CMD_TABLE_T*)setpCmdTbl.p_entries[i]->format)->p_entries[j]->format;
      }
      else
      {
    	paramType = ((MX_DBG_CMD_TABLE_T*)setpCmdTbl.p_entries[i]->format)->p_entries[j]->type;
      }
      
      /* Pointer to the configuration parameter */
      paramLocation = (void *)((UINT32)(pTemplate) + setpCmdTbl.p_entries[i]->location +
    		          (((MX_DBG_CMD_TABLE_T*)(setpCmdTbl.p_entries[i]->format)))->p_entries[j]->location);

#if 0  
case OMTB_H264_VDEC_CLASS:
          
          fprintf(templateCfgFp, "%s ", cmdEntryH264VdecConfig.name);
          fprintf(templateCfgFp, "%s ", cmdListH264VdecConfig[j]->name);
          
          /* Store the parameter type */
          if(NULL != cmdListH264VdecConfig[j]->format)
          {
            /* Used later for getting equivalent string for enum values */
            paramType = MX_DBG_CMD_OPT_ENUM;
            enumTbl = cmdListH264VdecConfig[j]->format;
          }
          else
            paramType = cmdListH264VdecConfig[j]->type;
            
          /* Pointer to the configuration parameter */
          paramLocation = (void *)((void *)h264VidDecCfg + 
                                    cmdListH264VdecConfig[j]->location);
          break;
#endif          
      
      /* Display the value according to the parameter type */
      switch(paramType)
      {

        case MX_DBG_CMD_TYPE_VAR_SINT8:
          {
            SINT8* pSint8 = (SINT8*)paramLocation;
            fprintf(templateCfgFp, "%d\n", *pSint8);
            break;
          }
          
        case MX_DBG_CMD_TYPE_VAR_SINT16:
          {
            SINT16* pSint16 = (SINT16*)paramLocation;
            fprintf(templateCfgFp, "%d\n", *pSint16);
            break;
          }
          
        case MX_DBG_CMD_TYPE_VAR_SINT32:
          {
            SINT32* pSint32 = (SINT32*)paramLocation;
            fprintf(templateCfgFp, "%d\n", *pSint32);
            break;
          }
          
        case MX_DBG_CMD_TYPE_VAR_UINT8:
          {
            UINT8* pUint8 = (UINT8*)paramLocation;
            fprintf(templateCfgFp, "%d\n", *pUint8);
            break;
          }
          
        case MX_DBG_CMD_TYPE_VAR_UINT16:
          {
            UINT16* pUint16 = (UINT16*)paramLocation;
            fprintf(templateCfgFp, "%d\n", *pUint16);
            break;
          }
          
        case MX_DBG_CMD_TYPE_VAR_UINT32:
          {
            UINT32* pUint32 = (UINT32*)paramLocation;
            fprintf(templateCfgFp, "%d\n", *pUint32);
            break;
          }
        
        case MX_DBG_CMD_TYPE_VAR_STR_BUF:
          {
            char *pStr = (char*)paramLocation;
            fprintf(templateCfgFp, "%s\n", pStr);
            break;
          }
        
        case MX_DBG_CMD_OPT_ENUM:
          {
            int enumCount = 0;
            UINT32* pUint32 = (UINT32*)paramLocation;
            
            /* Get the corresponding string for enum values from enum table */
            while(strcmp(enumTbl[enumCount].name , ""))
            {
              if( enumTbl[enumCount].value == *pUint32)
                break;
                
              enumCount++;
            }
            fprintf(templateCfgFp, "%s\n", enumTbl[enumCount].name);
            break;  
          }  
          
        case OMTB_INVALID_PARAM:
        default:
          fprintf(templateCfgFp, "\n");
          PRINT(PRINT_DEBUG_MESSAGE, "%s: Invalid parameter\n",\
                                    __FUNCTION__);                                    
          break;
          
      } // switch(paramType)
      
    } // for(j = 0; j < numEntries - 1; j++)
    
  } // for(i = 0; i < setpCmdTbl.max_entries - 1; i++)
  
  /* Close the cfg file */
  fclose(templateCfgFp);
  
  return ERR_NOERR;
}


/******************************************************************************\
 *      OMTB_LoadCfg Function Definition
\******************************************************************************/
/*
 *
 *  @brief    This function loads the configuration into specified template 
 *            from file.
 *
 *  @param in:
 *            cfgFileName: Pointer to configuration file name
 *
 *            template: Template no to which cfg is to be loaded
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            ERR_NOERR           successful,
 *
 *            ERR_INVNAME         Incorrect template number/file name.
 */

MX_Result OMTB_LoadCfg(char *cfgFileName,
                       unsigned int template)
{
  FILE *templateCfgFp = NULL;
  char inputCmdLine[OMTB_MAX_LEN] = {'\0'};
  unsigned int nBytes = 0;
  MX_Result result = ERR_NOERR;
  
  if(OMTB_MAX_TEMPLATE <= template)
  {
    /* Invalid template */
    PRINT(PRINT_ERR_MSG, "Invalid template number %d -Valid range: <0 to %d>\n",
                          template, OMTB_MAX_TEMPLATE - 1);
    return ERR_INVNAME;
  }
  
  /* Allocate the template memory if it is not already allocated */
  result = OMTB_AddCfg(template);
  
  if(ERR_NOERR != result)
    return result;

  /* Open the cfg file */
  templateCfgFp = fopen(cfgFileName, "rb");
  
  if(NULL == templateCfgFp)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in opening cfg file: %s\n",\
                                __FUNCTION__, cfgFileName);
    return ERR_INVNAME;
  }
  
  while(OMTB_LOOP)
  {
    /* required to load specific template */
    nBytes = sprintf(inputCmdLine, "omx setp %d ", template);

    if(OMX_FALSE >= nBytes)
    {
      PRINT(PRINT_ERR_MSG, "%s: Error in appending string to form command\n",\
                                __FUNCTION__);

      /* Close the cfg file */
      fclose(templateCfgFp);
      
      return ERR_INVNAME;
    }
    
    /* read the commands from the file */
    nBytes = OMTB_ReadScript(templateCfgFp, &(inputCmdLine[nBytes]));
    if(OMX_FALSE == nBytes)
    {
      break;
    }      
    else
    {
      /* Display the command on the command prompt */
      PRINT(PRINT_MUST, "\r     \nOMTB> %s\n", inputCmdLine);

      /* parse and process the command */
      procCmdLine(inputCmdLine);
      continue;
    }
    
  } // while(OMTB_LOOP)
  
  /* Close the cfg file */
  fclose(templateCfgFp);
  
  return ERR_NOERR;
}


/******************************************************************************\
 *      OMTB_SetTemplateDefVal Function Definition
\******************************************************************************/
/*
 *
 *  @brief    This function copies the default values in specified template.
 *
 *  @param in:
 *            template: Template no which is to be filled with default values
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

MX_Result OMTB_SetTemplateDefVal(unsigned int template)
{
  MX_Result result = ERR_NOERR;
  
  OMTB_TEMPLATE_INFO *pTemplate = NULL;
    
  if(OMTB_MAX_TEMPLATE <= template)
  {
    /* Invalid template */
    PRINT(PRINT_ERR_MSG, "Invalid template number %d -Valid range: <0 to %d>\n",
                          template, OMTB_MAX_TEMPLATE - 1);
    return ERR_INVNAME;
  }
  
  if(NULL == omtbCfgTemplate[template])
  {
    /* Allocate the template memory if it is not already allocated */
    result = OMTB_AddCfg(template);
    if(ERR_NOERR != result)
    {
      PRINT(PRINT_ERR_MSG, "%s: Memory for Template %d not allocated\n",\
                                  __FUNCTION__, template);
      return result;
    }
  }

  /* update the local copy of appropriate pointers */
  pTemplate = omtbCfgTemplate[template];
  
  OMTB_InitTemplates(pTemplate);
  
  return ERR_NOERR;
}


/******************************************************************************\
 *      OMTB_AddCfg Function Definition
\******************************************************************************/
/*
 *
 *  @brief    
 *            This function allocates the memory for the specified template.
 *
 *  @param in:
 *            template: Template no which is to be allocated.
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

MX_Result OMTB_AddCfg(unsigned int template)
{
  MX_Result result = ERR_NOERR;
  
  if(OMTB_MAX_TEMPLATE <= template)
  {
    /* Invalid template */
    PRINT(PRINT_ERR_MSG, "Invalid template number %d -Valid range: <0 to %d>\n",
                          template, OMTB_MAX_TEMPLATE - 1);
    return ERR_INVNAME;
  }
  
  /* Allocate the template memory if it is not already allocated */
  if(NULL == omtbCfgTemplate[template])
  {
    omtbCfgTemplate[template]= (OMTB_TEMPLATE_INFO*)
                  TIMM_OSAL_Malloc( sizeof(OMTB_TEMPLATE_INFO),
                                    TIMM_OSAL_TRUE,
                                    0,
                                    TIMMOSAL_MEM_SEGMENT_EXT);

    if(NULL == omtbCfgTemplate[template])
    {
      PRINT(PRINT_ERR_MSG, "%s: Error allocating config params memory\n",\
                                    __FUNCTION__);
      return ERR_INVNAME;
    }
    else
    {
      TIMM_OSAL_Memset(omtbCfgTemplate[template], 0, sizeof(OMTB_TEMPLATE_INFO));
	}
    PRINT(PRINT_DEBUG_MESSAGE, "%s: Template %d memory allocated\n", 
                                __FUNCTION__, template);
  }
  else
  {
    PRINT(PRINT_DEBUG_MESSAGE, "%s: Template %d memory already allocated\n", 
                                __FUNCTION__, template);
    return ERR_NOERR;
  }
  
  /* Set the template to default values */
  result = OMTB_SetTemplateDefVal(template);
  if(ERR_NOERR != result)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error configuring the template params\n",\
                                    __FUNCTION__);
    return (ERR_INVNAME);
  }
  
  return ERR_NOERR;
}


/******************************************************************************\
 *      OMTB_RemoveCfg Function Definition
\******************************************************************************/
/*
 *
 *  @brief    
 *            This function releases the memory of the specified template.
 *
 *  @param in:
 *            template: Template no which is to be removed from memory
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            ERR_NOERR           successful,
 *
 *            ERR_INVNAME         Incorrect template number/file name.
 */

MX_Result OMTB_RemoveCfg(unsigned int template)
{
  if(OMTB_MAX_TEMPLATE <= template)
  {
    PRINT(PRINT_ERR_MSG, "Invalid template number %d -Valid range: <0 to %d>\n",
                          template, OMTB_MAX_TEMPLATE - 1);
    return ERR_INVNAME;
  }
  
  /* Release the memory allocated for the specified template */
  if(NULL != omtbCfgTemplate[template])
  {
    TIMM_OSAL_Free(omtbCfgTemplate[template]);
    omtbCfgTemplate[template] = NULL;
    PRINT(PRINT_DEBUG_MESSAGE, "%s: Template %d memory released\n", __FUNCTION__,
                                template);
  }
  
  return ERR_NOERR;
}


/******************************************************************************\
 *      OMTB_CmdTemplateProcess Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function is used to set/show the comamnd in/from the 
 *            selected template
 *
 *  @param    pContext   : Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            pCmdEntry : Pointer to MX_DBG_CMD_Entry_T structure
 *            ppCmdLine : Character Double Pointer containing the command
 *            pTemplate      : Pointer to template
 *            template    : Template No
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */


PRIVATE MX_Result
OMTB_CmdTemplateProcess(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine,
  void*                   pTemplate,
  UINT32                  template
)
{
  char                    pStr[OMTB_MAX_LEN] = {"\0"};
  char*                   pLine = NULL;
  MX_Result               result = ERR_NOERR;

  /* Push the pointer to the configuration template on the stack */
  if (ERR_NOERR != XdbgContextPush(pContext, pTemplate)) 
  {
    XdbgPrintf("%s: PUSH failed: context stack is full.\n", pCmdEntry->name);
    return ((MX_Result)ERR_END_OF_CMD);
  }

  if (
      (MX_DBG_CMD_MODE_SET    == mx_dbg_cmd_mode) ||
      (MX_DBG_CMD_MODE_RESET  == mx_dbg_cmd_mode)
     )

  {
    if (MX_DBG_CMD_MODE_RESET == mx_dbg_cmd_mode)
    {
      result = OMTB_DimtSkipWhiteSpace(pContext, pCmdEntry, ppCmdLine);
      if (ERR_NOERR != result)
      {
        return XdbgCmdExec(pContext, ppCmdLine);
      }
    }

    /* Continue parsing the rest of the line */
    result = XdbgCmdParse(pContext, pCmdEntry, ppCmdLine);
    if (ERR_NOERR != result)
    {
      return result;
    }

    return ((MX_Result)ERR_NOERR);
  }

  if (MX_DBG_CMD_MODE_SHOW == mx_dbg_cmd_mode)
  {
    Xsprintf(pStr, "");
  }
  else
  {
    Xsprintf(pStr, "dimt set %s %d", pCmdEntry->name, template);
  }

  pLine = pStr;
  result = XdbgCmdParseShow(pContext, pCmdEntry, ppCmdLine, &pLine);
  if (ERR_NOERR != result)
  {
    return result;
  }

  return ((MX_Result)ERR_NOERR);
}


/******************************************************************************\
 *      OMTB_CmdTemplate Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function is used to select the template to be used
 *
 *  @param    pContext   : Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            pCmdEntry : Pointer to MX_DBG_CMD_Entry_T structure
 *            ppCmdLine : Character Double Pointer containing the command
 *
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */


PRIVATE MX_Result
OMTB_CmdTemplate(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  UINT16                  template = 0;
  UINT32                  arg = 0;
  OMTB_TEMPLATE_INFO*     pTemplate = NULL;
  MX_Result               result = ERR_NOERR;

  /* Read template number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, &arg);
  if (ERR_NOERR != result)
  {
    return result;
  }
  template = (UINT16)arg;
  
  if(OMTB_MAX_TEMPLATE <= template)
  {
    /* Invalid template */
    XdbgPrintf("Invalid Template number %d - Valid range: <0 to %d>\n",
                template, OMTB_MAX_TEMPLATE - 1);
    return ((MX_Result)ERR_INVNAME);
  }

  /* Add the specified template if doesn't exist */
  if(NULL == omtbCfgTemplate[template])
  {
    result = OMTB_AddCfg(template);
  
    if(ERR_NOERR != result)
    {
      PRINT(PRINT_ERR_MSG, "%s: Error allocating config params memory\n", 
                            __FUNCTION__);
      return result;
    }
  }

  /* Set template to be used for OMTB configuration parameters, The last 
   * template id in which parameters were changed will be used regardless 
   * any error occured.
   */
  if(MX_DBG_CMD_MODE_SET == mx_dbg_cmd_mode)
  {
    omtbCfgTemplate[template]->currTemplate = template; 
  }

  /* Update the template pointer to be passed for further processing */
  pTemplate  = omtbCfgTemplate[template];

  if (
      (MX_DBG_CMD_MODE_SHOW == mx_dbg_cmd_mode)  ||
      (MX_DBG_CMD_MODE_LIST == mx_dbg_cmd_mode)
     )
  {
    XdbgPrintf("\nTemplate %d:", template);
    XdbgPutS("\n");
  }

  return OMTB_CmdTemplateProcess(pContext, pCmdEntry, ppCmdLine, 
                                 (void*)pTemplate, (UINT32)template); 
}


/******************************************************************************\
 *      OMTB_CmdSetTemplate Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function is a wrapper on top of OMTB_CmdTemplate and is 
 *            called if user wants to set parameter in the template
 *
 *  @param    pContext   : Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            pCmdEntry :Pointer to MX_DBG_CMD_Entry_T structure
 *            ppCmdLine :Character Double Pointer containing the command
 *
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_CmdSetTemplate(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  /* Set the appropriate ommand and invok the template processing function */
  mx_dbg_cmd_mode = (MX_DBG_CMD_MODE_T)MX_DBG_CMD_MODE_SET;

  return OMTB_CmdTemplate(pContext, pCmdEntry, ppCmdLine);
}


/******************************************************************************\
 *      OMTB_CmdShowTemplate Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function is a wrapper on top of OMTB_CmdTemplate and is 
 *            called if user wants to display the parameter present in the
 *            template
 *
 *  @param    pContext   : Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            pCmdEntry :Pointer to MX_DBG_CMD_Entry_T structure
 *            ppCmdLine :Character Double Pointer containing the command
 *
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_CmdShowTemplate(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  /* Set the appropriate ommand and invok the template processing function */
  mx_dbg_cmd_mode = (MX_DBG_CMD_MODE_T)MX_DBG_CMD_MODE_SHOW;

  return OMTB_CmdTemplate(pContext, pCmdEntry, ppCmdLine);
}


/******************************************************************************\
 *      OMTB_CmdResetTemplate Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function is a wrapper on top of OMTB_CmdTemplate and is 
 *            called if user wants to reset the parameter present in the
 *            template
 *
 *  @param    pContext   : Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            pCmdEntry :Pointer to MX_DBG_CMD_Entry_T structure
 *            ppCmdLine :Character Double Pointer containing the command
 *
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_CmdResetTemplate(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  /* Set the appropriate ommand and invok the template processing function */
  mx_dbg_cmd_mode = (MX_DBG_CMD_MODE_T)MX_DBG_CMD_MODE_RESET;

  return OMTB_CmdTemplate(pContext, pCmdEntry, ppCmdLine);
}


/*----------------------------- end of file ---------------------------------*/
