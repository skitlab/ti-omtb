/*
 * omtbH264VencParser.c
 *
 * Component specific IL Client Implementation.
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

#include "omtbDebug.h"
/* OMX standard header files */
#include "OMX_Types.h"

/******************************************************************************\
 *      Local Defines
\******************************************************************************/
#define H264_START_CODE 0x000001
#define H264_NAL_TYPE_NON_IDR_SLICE 0x1
#define H264_NAL_TYPE_IDR_SLICE 0x5
#define H264_NAL_TYPE_SPS 0x7
#define H264_NAL_TYPE_PPS 0x8

/******************************************************************************\
 *      GetBits Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Reads bits from the bitstream buffer
 *
 *  @param in:
 *            buffer:containing VLC-coded data bits
 *            totbitoffset:bit offset from start of partition  
 *            bitcount:total bytes in bitstream
 *            numbits:number of bits to read
 *
 *  @param Out:
 *            info:returns value of the read bits
 *
 *  @return   absolute offset in bit from start of frame
 *
 */
int GetBits (unsigned char buffer[],unsigned int totbitoffset,unsigned char *info, int bitcount,
								unsigned int numbits)
{
  if ((totbitoffset + numbits ) > bitcount) 
  {
    return -1;
  }
  else
  {
    int bitoffset  = 7 - (totbitoffset & 0x07); // bit from start of byte
    int byteoffset = (totbitoffset >> 3); // byte from start of buffer
    int bitcounter = numbits;
    unsigned char *curbyte  = &(buffer[byteoffset]);
    unsigned char inf = 0;
    
	while (numbits--)
    {
	  inf <<=1;
	  inf |= ((*curbyte)>> (bitoffset--)) & 0x01;
	  if (bitoffset == -1 )
	  { //Move onto next byte to get all of numbits
        curbyte++;
        bitoffset = 7;
	  } 
    }

    *info = inf;
    return bitcounter;           // return absolute offset in bit from start of frame
  }
}

/******************************************************************************\
 *      h264_parse_nal Function Definition
\******************************************************************************/
/**
 *
 *  @brief    NAL Parser
 *
 *  @param in:
 *            buff:containing VLC-coded data bits
 *            nal_size:size of NAL packet
 *
 *  @param Out:
 *            
 *
 *  @return   NAL TYPE
 *
 */
unsigned char h264_parse_nal (unsigned char *buff, unsigned int nal_size)
{
  unsigned char nal_unit_type = 0;
  unsigned char value = 0;
  unsigned int bit_pos = 0;

  GetBits(buff,0,&value,nal_size,24);

  if(value == 0)
   bit_pos = 35; // StartCodePrefix= 0x00000001(32bits) + 2bits for nal_ref_idc
  else 
   bit_pos = 27; // StartCodePrefix= 0x000001(24bits) + 2bits for nal_ref_idc
	
  GetBits(buff, bit_pos, &nal_unit_type, nal_size, 5);

  return nal_unit_type;
}

/******************************************************************************\
 *      h264_find_next_start_code Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Find the start code
 *
 *  @param in:
 *            pBuf:containing VLC-coded data bits
 *            bufLen:buffer length
 *
 *  @param Out:
 *            
 *
 *  @return   NAL Packet Size
 *
 */
unsigned int h264_find_next_start_code (unsigned char *pBuf, unsigned int bufLen)
{
  unsigned int val;
  unsigned int offset=0;

  if (pBuf[0] == 0 && pBuf[1] == 0 && pBuf[2] == 0 && pBuf[3] == 1)
  {
    pBuf += 4;
    offset = 4;
  }
  else if (pBuf[0] == 0 && pBuf[1] == 0 && pBuf[2] == 1)
  {
    pBuf += 3;
    offset = 3;
  } 
  
  val = 0xffffffff;
  
  while (offset < bufLen - 3)
  {
    val <<= 8;
    val |= *pBuf++;
    offset++;
    if (val == H264_START_CODE)
    {
      return offset - 4;
    }
    
	if ((val & 0x00ffffff) == H264_START_CODE)
    {
     return offset - 3;
    }
  }
  
  return (offset+3);
}

/******************************************************************************\
 *      OMTB_H264CopySpsPps Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Copy the SPS and PPS Hdr
 *
 *  @param in:
 *            pBufIn:containing VLC-coded data bits
 *            bufLen:buffer length
 *            pBufOut:output buffer
 *
 *  @param Out:
 *            
 *
 *  @return   size of SPS and PPS Hdr
 *
 */
int OMTB_H264CopySpsPps(char *pBufIn,int bufLen, char *pBufOut)
{
  unsigned int bufferOffset=0, nalPackSize = 0;
  unsigned int nal_type = 0;
  int findSpsPps = 0;
  int sizeSpsPps = 0;
  
  while((bufferOffset < bufLen) && ((H264_NAL_TYPE_SPS | H264_NAL_TYPE_PPS) != findSpsPps))	  
  { 
    nalPackSize = h264_find_next_start_code ((pBufIn+bufferOffset), bufLen);
    	
    if (((nalPackSize) > 3))		
    {
      nal_type = h264_parse_nal((pBufIn + bufferOffset), (nalPackSize*8));	
    }
    else		
      return sizeSpsPps;	
	
    switch(nal_type)	
    {
	  case H264_NAL_TYPE_SPS:
	    PRINT(PRINT_DEBUG_MESSAGE, "NAL_TYPE: SPS \n");
		memcpy(pBufOut, (pBufIn + bufferOffset), nalPackSize);
        findSpsPps |=  H264_NAL_TYPE_SPS;	
		sizeSpsPps += nalPackSize;
		pBufOut += nalPackSize;
	   break;
    
	  case H264_NAL_TYPE_PPS:
	    PRINT(PRINT_DEBUG_MESSAGE, "NAL_TYPE: PPS \n");		
		memcpy(pBufOut, (pBufIn + bufferOffset), nalPackSize);		
		findSpsPps |= H264_NAL_TYPE_PPS;
		sizeSpsPps += nalPackSize;	
		pBufOut += nalPackSize;		
		break;

      default:
	    PRINT(PRINT_DEBUG_MESSAGE, "NAL_TYPE: INVALID IN FIND SPS AND PPS \n");		
	   break;	
    }
	 
    bufferOffset += nalPackSize;
  } 

  return sizeSpsPps;
}

/******************************************************************************\
 *      OMTB_H264IsIDRFrame Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Find if the frame is IDR
 *
 *  @param in:
 *            pBufIn:containing VLC-coded data bits
 *            bufLen:buffer length
 *
 *  @param Out:
 *            
 *
 *  @return   OMX_TRUE: if the frame is IDR
 *
 */
OMX_BOOL OMTB_H264IsIDRFrame(char *pBufIn, int bufLen)
{
  unsigned int bufferOffset=0, nalPackSize = 0;
  unsigned int nal_type = 0;
  OMX_BOOL findIDR = OMX_FALSE;
  
  while(bufferOffset < bufLen && (OMX_FALSE == findIDR))	  
  { 
    nalPackSize = h264_find_next_start_code ((pBufIn + bufferOffset), bufLen);
    	
    if (((nalPackSize) > 3))		
    {
      nal_type = h264_parse_nal((pBufIn + bufferOffset), (nalPackSize*8));	
    }
    else		
     return;	
	
    switch(nal_type)	
    {
	  case H264_NAL_TYPE_IDR_SLICE:
	   findIDR = OMX_TRUE;
       PRINT(PRINT_DEBUG_MESSAGE, "NAL_TYPE: IDR \n");			   
	  break;
       
	  default:
	   PRINT(PRINT_DEBUG_MESSAGE, "NAL_TYPE: INVALID IN FIND IDR \n");		
	  break;	
    }
	 
    bufferOffset += nalPackSize;
  } 
  
  return findIDR;
}
