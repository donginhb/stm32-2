/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V1.0
* Date               : 10/08/2007
* Description        : Virtual Com Port Demo main file
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "stm32f10x_rcc.h"

#include "DES.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
u32 CpuID[3];


extern u32 count_out;
extern u32 count_in;
extern u8 buffer_out[VIRTUAL_COM_PORT_DATA_SIZE];

extern u8 SHUJU[]={"extern u32 count_out;"};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/


int main(void)
{
	unsigned char key[16][8];
	unsigned char text[10],detext[10];
	char szBuffer[64];
	u32		uTimes1 = 0;
	u32		uTimes2 = 0;
	u32 uFlashBaseAddr = 0x08027000 ;
	
	Init_System();//系统初始化
	
	
	Set_USBClock();//设置USB时钟
	USB_Interrupts_Config(); //配置USB中断
	
	USB_Init();//初始化USB 
	 
	RCC_HSICmd(ENABLE);	   //flash 时钟
 
    FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
  GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ); //关闭3个LED 


 	CpuID[0]=*(vu32*)(0x1ffff7e8);
	CpuID[1]=*(vu32*)(0x1ffff7ec);
	CpuID[2]=*(vu32*)(0x1ffff7f0);



  while (1)
  {
  	FLASH_Status status;
     memset( szBuffer , 0 , 64 );
	 uTimes1 ++;
	 if( uTimes1 > 1000000 )
	 {
	  	 sprintf( szBuffer , "waiting for command(%d):" ,0 );
	   	 USB_Send_Data(szBuffer , strlen(szBuffer) );
		 uTimes1 = 0;
	 }	 

	 //FLASH_ErasePage( uFlashBaseAddr );
//	 memcpy( text , "12345678" , 8 );
//	 status = Flash_Write(uFlashBaseAddr, text , 8 );
//	 Flash_Read( uFlashBaseAddr,detext,8);
//
// 		sprintf( szBuffer , "Read from flash detext(%d):\n", status );
//		USB_Send_Data(szBuffer , strlen(szBuffer) );
//		PrintBuffer( detext , 8 );	 
	 	

    if (count_out != 0)	//判断有无数据接收到
    {  
		uTimes1 = 0;

		if(buffer_out[0]==0x01)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_14 );
			USB_Send_Data("LED1 点亮\r\n", strlen("LED1 点亮\r\n"));
			count_out=0;
		}	//如果接收到的输出是0X01，点亮led1
		if(buffer_out[0]==0x02)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_12 );
			USB_Send_Data("LED2 点亮\r\n",strlen("LED2 点亮\r\n"));
			count_out=0;
		}	
		//如果接收到的输出是0X02，点亮led2
		if(buffer_out[0]==0x03)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_13 );
			USB_Send_Data("LED3 点亮\r\n", strlen("LED3 点亮\r\n"));
			count_out=0;
		}	
		//如果接收到的输出是0X03，点亮led3
		if(buffer_out[0]==0x04)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 );
			USB_Send_Data("LED 全灭\r\n",strlen("LED 全灭\r\n"));
			count_out=0;
		} //如果接收到的输出是0X04，//关闭3个LED  
		if( buffer_out[0] == '1' )
		{
		     memcpy(text,"012345678",8);     //text<-密码种子
		     deskey(text,key);              //key<-生成密钥
		     memcpy(detext,buffer_out,8);   //detext<-待加密明文
		     des(detext,key,EN_DES,text);   //text<-生成密文
		     memcpy(detext,"00000000",8);   //清除明文以便于测试
		     des(text,key,DE_DES,detext);   //detext<-解密后的明文
		
		   	 USB_Send_Data(detext , strlen(detext) );
			 USB_Send_Data("\n",1);
			count_out=0;
		}

		ParseCommand( buffer_out , count_out );


		count_out = 0;
    }	 //if (count_out != 0)
	else
	{
		//if( count_in == 0 )
		//	USB_Send_Data("\n",1);
	}
	
  }	  //while(1)
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while(1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/




