//file: COM_pc_com.c
#include "stm32f10x_lib.h"

#include "includes.h"
#if 0
void bmemcpy(u8 *dst , u8  *src , u16 size);
void bmemset(u8 *dst , u8 data , u16 size );

  void bmemcpy(u8 *dst , u8  *src , u16 size)
{
	u8 *tdst = dst;
	u8 *tsrc = src;
	u16 i ;
	for ( i = 0 ; i < size ; i ++)
		*(tdst++) = *(tsrc++);
	
}
void bmemset(u8 *dst , u8 data , u16 size )
{
	u8 *tdst = dst;
	u16 i ;
	for ( i = 0 ; i < size ; i ++)
		*(tdst++) = data ;
	
}
#endif
/*******************************************************************************
* Function Name  : CheckXor
* Description    : ���У��
* Input          : - buf : ����
*             	--size : ���ݳ���  
* Output         :  None	
* Return         :���У���
*******************************************************************************/
u8 CheckXor(u8 *buf , u16 size)
{
	u16 i;
	u8 sum; 
	u8 *ptr = buf;
	
	sum= *ptr ;
	for(i = 1 ; i < size ; i++) 
	{ 
		sum^=*(ptr+i); 
	} 
	
	return sum ;
}
/*******************************************************************************
* Function Name  : UsbPCCmdRec
* Description    : ����pc ������������
* Input          : - buf : ���յ�������
*             	--Hdr :���������              
* Output         :  None	
* Return         :���յ��������Ƿ���Ч
*******************************************************************************/
bool ComPCCmdRec(u8 *buf , u16 size)
{
	Cmd_HDR_t *h = (Cmd_HDR_t *)buf ;	
	
	if((h->Header == COM_PC_CMD_HDR )&&( h->HDRLen != 0 ))
	{	

		return TRUE;
		
	}	
	return FALSE ;
}


void ComMCUACKSend(u8 *buf , u16 size)
{
	
	u8 tbuf[64] ;
	Cmd_HDR_t  *h = (Cmd_HDR_t  *)tbuf ;

	h->Header = COM_MCU_ACK_HDR ;
	h->HDRLen = size + sizeof(Cmd_HDR_t) ;	
	
	bmemcpy(tbuf + sizeof(Cmd_HDR_t) , buf, size);
	
	//tbuf[size+3] = CheckXor(tbuf , 3)^CheckXor(buf , size);
	//tbuf[size+4] = ~tbuf[3];

	//COM_Send_Data(buf, size );	/*����ֻ����pc����������*/
	//USB_Send_Data(tbuf, size + sizeof(Cmd_HDR_t) );/*���ش�֡ͷ��У���ack*/
}
void ComSendString(u8 *str )
#if 1
{
				u8 tbuf[64];	
				u8 *tptr = tbuf;			 
				u8  sbufCounter =  0;
				while(*str!='\0')
				{
					*(tptr++) = *(str++);
					sbufCounter++;
				}
			//	UsbMCUACKSend(tbuf , sbufCounter );	
}
#endif
	

void ComSendStringInt(u8 *str , u16 val )
{
#if 1
	u8 tbuf[64];	
	u8 *tptr = tbuf;			 
	u8  sbufCounter =  0;
	u16 	tCnt = val ;
				
	while(*str!='\0')
	{
		*(tptr++) = *(str++);
		sbufCounter++;
	}					
	tptr = WordToChar(tCnt) ;		
	bmemcpy( tbuf + sbufCounter , tptr , 5);
	sbufCounter += 5 ;

	tptr = "\n" ;		
	bmemcpy( tbuf + sbufCounter , tptr , 1);
	sbufCounter += 1 ;

		
	//UsbMCUACKSend(tbuf , sbufCounter );	

#endif
}


