#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__
#include "stm32f10x_lib.h"

//0x08026000
typedef struct _tagRecLibInfo
{
	u32		uSynFlag; //0x5AA50120,若该值存在，表示已经经过了初始化。
	u32		uRecLibMD5;


}RECLIB_INFO,*LPRECLIB_INFO;


typedef struct _tagFrameHead
{
  u16	uSynHead;
  u8	uCommand;
  u8	uLength;
}FRAMEHEAD,*LPFRAMEHEAD;


typedef struct _tagRecLibInitReq
{
	//u16 nTotalLen;
	u32 nOffset;
	//u8* pPayLoad;
}RECLIB_INIT_REQ,*LPRECLIB_INIT_REQ;

typedef struct _tagRecLibInitRes
{
	u32	nStatus;
	u32	nError;
	u32 nFlashAddr;
}RECLIB_INIT_RES,*LPRECLIB_INIT_RES;


void PrintBuffer( u8* Buffer , u32 uCount );
void ParseCommand(u8* bufCommand, u32 nLength  );

void RecLib_Init(u8* Buffer , u32 nOffset , u8 uCount );
void ReadFromFlash( u32 BaseAddr , u8* Buffer , u32 uCount );
FLASH_Status WriteToFlash(u32 BaseAddr, u8* Buffer , u32 uCount );

 #define FLASH_PAGE_SIZE    ((u16)0x800)
int Flash_Read(u32 iAddress, u8 *buf, u32 iNbrToRead) ;
int Flash_Write(u32 iAddress, u8 *buf, u32 iNbrToWrite);

#endif //__PROTOCOL_H__
