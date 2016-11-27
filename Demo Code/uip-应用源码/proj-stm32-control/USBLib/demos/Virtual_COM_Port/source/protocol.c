#include "protocol.h"
#include "DES.h"

extern u32 CpuID[3];

void PrintBuffer( u8* Buffer , u32 uCount )
{
	char szBuffer[64];
    int i = 0; 
  	for( i = 0 ; i < uCount; i ++ )
	{
	   sprintf( szBuffer , "%02x " , Buffer[i] );
	   USB_Send_Data(szBuffer, strlen(szBuffer));
	}
  	USB_Send_Data("\n",1);	
}

void Proc_CPUID()
{
	u32 CpuID[3];
	u8	Buffer[64];
	LPFRAMEHEAD head = (LPFRAMEHEAD)Buffer;

	memset( Buffer , 0 , 64 );

	CpuID[0]=*(vu32*)(0x1ffff7e8);
	CpuID[1]=*(vu32*)(0x1ffff7ec);
	CpuID[2]=*(vu32*)(0x1ffff7f0);

	head->uSynHead = 0x5AA5;
	head->uCommand = 0x12;
	head->uLength = 12;

	memcpy( Buffer+4 , CpuID , 12 );

	USB_Send_Data( Buffer ,16 );

	return;
}

void ParseCommand(u8* bufCommand, u32 nLength  )
{
	LPFRAMEHEAD head = (LPFRAMEHEAD)bufCommand;

	if( head->uSynHead != 0x5AA5 )
	{
		//这里可以返回invalid frame字符串信息给上位机
		return;
	}

	switch( head->uCommand )
	{
		case 0x11:		  //获取CPUID
		{
			Proc_CPUID();
		}
		break;
		case 0x13:		  //请求初始化识别库
		{
			LPRECLIB_INIT_REQ pBody =  (LPRECLIB_INIT_REQ)(bufCommand+sizeof(FRAMEHEAD));
			RecLib_Init( bufCommand+8 , pBody->nOffset , head->uLength-4 );
		}
		break;
		case 0x15:		  //请求下载识别库
		break;
		case 0x17:		  //控制指示灯
		break;
		case 0x21:		  //参数相关
		break;
		default:
		break;
	}

	return;
}


void RecLib_Init(u8* Buffer , u32 nOffset , u8 uCount )
{
/********************************************************************
0xasdfasdfad    存放原始识别库的MD5值 8字节
0x08007000-0x08025FFF    存放原始识别库   100k字节
0x08026000-0x08026FFF	 存放重要的数据（4K字节），特别是原始识别库的MD5值
0x08027000-0x0803FFFF    存放加密后的识别库  100k字节
********************************************************************/
	int i=0;
	char szBuffer[64];
	unsigned char key[16][8];
	u32	reg_key[2];
	int nRet ;
	u16 nError=0;
	unsigned char text[10],detext[10],entext[10];
	u32 uFlashBaseAddr = 0x08027000+nOffset;	

	reg_key[0] = (CpuID[0]>>1)+(CpuID[1]>>2)+(CpuID[2]>>3);
	reg_key[1] = 0x5AA50120;

	deskey((unsigned char *)reg_key,key);              //key<-生成密钥
	for( i = 0 ; i < uCount; i += 8 )
	{
//		sprintf( szBuffer , "org text:\n" );
//		USB_Send_Data(szBuffer , strlen(szBuffer) );
//		PrintBuffer( Buffer+i , 8 );

		//des( Buffer+i ,key,EN_DES,entext);   //text<-生成密文

		WriteToFlash(uFlashBaseAddr+i, Buffer+i , 8 );//写入flash

//		sprintf( szBuffer , "Crypt text:\n" );
//		USB_Send_Data(szBuffer , strlen(szBuffer) );
//		PrintBuffer( text , 8 );
		
		ReadFromFlash( uFlashBaseAddr+i , detext , 8 );//读出


		//des(detext,key,DE_DES,text);   //text<-解密后的明文

// 		sprintf( szBuffer , "Read from flash detext:\n" );
//		USB_Send_Data(szBuffer , strlen(szBuffer) );
//		PrintBuffer( detext , 8 );

		nRet = memcmp( detext , Buffer+i , 8 );			  //打印比较结果
		if( nRet ) 
		{
			nError ++;
//	 		sprintf( szBuffer , "Read from flash detext:\n" );
//			USB_Send_Data(szBuffer , strlen(szBuffer) );
//			PrintBuffer( detext , 8 );
		}
//		sprintf( szBuffer , "memcmp result: %d ,address=0x%x\n" , nRet,uFlashBaseAddr+i );	
//		USB_Send_Data(szBuffer , strlen(szBuffer) );
	}
	{
		//sprintf( szBuffer , "finished！ offset=%d ,address=0x%x, nError=%d\n" , nOffset,uFlashBaseAddr+i,nError );	
		//USB_Send_Data(szBuffer , strlen(szBuffer) );

		LPFRAMEHEAD 		head = (LPFRAMEHEAD)szBuffer;
		LPRECLIB_INIT_RES 	body = (LPRECLIB_INIT_RES)( szBuffer + sizeof(FRAMEHEAD) );

		head->uSynHead = 0x5AA5;
		head->uCommand = 0x14;
		head->uLength = sizeof(RECLIB_INIT_RES);
		body->nStatus = 0;
		body->nError = nError;
		body->nFlashAddr = uFlashBaseAddr;
		if( nError>0 )
		{
			memcpy( szBuffer+sizeof(FRAMEHEAD)+sizeof(RECLIB_INIT_RES),Buffer+i-8,8); 
			memcpy( szBuffer+sizeof(FRAMEHEAD)+sizeof(RECLIB_INIT_RES)+8,detext,8); 
			USB_Send_Data(szBuffer , sizeof(FRAMEHEAD)+sizeof(RECLIB_INIT_RES)+16 );
		}
		else
			USB_Send_Data(szBuffer , sizeof(FRAMEHEAD)+sizeof(RECLIB_INIT_RES) );
	}

}

void ReadFromFlash( u32 BaseAddr , u8* Buffer , u32 uCount )
{
	int i = 0;
	for( i = 0 ; i < uCount ; i += 2 )
	{
		*(u16*)(Buffer+i) = *(u16*)( BaseAddr+i);
	}
		
}

FLASH_Status WriteToFlash(u32 BaseAddr, u8* Buffer , u32 uCount )
{
	int nTimes = 0;
	int i = 0;
	u16		nTemp;
	FLASH_Status status;


	for( i = 0 ; i < uCount ; i += 2 )
	{
		if( ((BaseAddr+i) & 0x7FF) == 0 )
			FLASH_ErasePage( BaseAddr+i ); 

		do
		{
			status = FLASH_ProgramHalfWord( BaseAddr+i, *(u16*)(Buffer+i) );
			nTemp = *(u16*)( BaseAddr+i);
			nTimes ++;
		}
		while( nTemp != *(u16*)(Buffer+i) && nTimes < 5 );
	}

	return status;
}


int Flash_Read(u32 iAddress, u8 *buf, u32 iNbrToRead) 
{
        int i = 0;
        while(i < iNbrToRead ) 
		{
           *(buf + i) = *(u8*) iAddress++;
           i++;
        }
        return i;
}

u16 Flash_Write_Without_check(u32 iAddress, u8 *buf, u16 iNumByteToWrite) 
{
	u16 i;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
	i = 0;
	
	//    FLASH_UnlockBank1();
	while((i < iNumByteToWrite) && (FLASHStatus == FLASH_COMPLETE))
	{
		FLASHStatus = FLASH_ProgramHalfWord(iAddress, *(u16*)buf);
		i = i+2;
		iAddress = iAddress + 2;
		buf = buf + 2;
	}
	
	return iNumByteToWrite;
}

int Flash_Write(u32 iAddress, u8 *buf, u32 iNbrToWrite) 
{
	/* Unlock the Flash Bank1 Program Erase controller */
	u32 secpos;
	u32 iNumByteToWrite = iNbrToWrite;
	u16 secoff;
	u16 secremain;  
	u16 i = 0;    
	u8 tmp[FLASH_PAGE_SIZE];
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
        
	FLASH_Unlock();
	secpos=iAddress & (~(FLASH_PAGE_SIZE -1 )) ;//扇区地址 
	secoff=iAddress & (FLASH_PAGE_SIZE -1);     //在扇区内的偏移
	secremain=FLASH_PAGE_SIZE-secoff;           //扇区剩余空间大小 
	
	
	if(iNumByteToWrite<=secremain) 
		secremain = iNumByteToWrite;//不大于4096个字节
        
	while( 1 )
	{
		Flash_Read(secpos, tmp, FLASH_PAGE_SIZE);   //读出整个扇区
		for(i=0;i<secremain;i++) 
		{       //校验数据
			if(tmp[secoff+i]!=0XFF)
				break;       //需要擦除 
		}
		if(i<secremain) 
		{  
			//需要擦除
			FLASHStatus = FLASH_ErasePage(secpos); //擦除这个扇区
			if(FLASHStatus != FLASH_COMPLETE)
				return -1;
			for(i=0;i<secremain;i++) 
			{   //复制
				tmp[i+secoff]=buf[i];   
			}
			Flash_Write_Without_check(secpos ,tmp ,FLASH_PAGE_SIZE);//写入整个扇区  
		} 
		else 
		{
			Flash_Write_Without_check(iAddress,buf,secremain);//写已经擦除了的,直接写入扇区剩余区间.
		}
            
        if(iNumByteToWrite==secremain) //写入结束了
            break;
        else 
		{
            secpos += FLASH_PAGE_SIZE;
            secoff = 0;//偏移位置为0 
            buf += secremain;  //指针偏移
            iAddress += secremain;//写地址偏移    
            iNumByteToWrite -= secremain;  //字节数递减
            if(iNumByteToWrite>FLASH_PAGE_SIZE) 
				secremain=FLASH_PAGE_SIZE;//下一个扇区还是写不完
            else 
				secremain = iNumByteToWrite;  //下一个扇区可以写完了
        }
            
	}
	
	FLASH_Lock();
	return iNbrToWrite; 
}
