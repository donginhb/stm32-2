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
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
extern u32 count_out;
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
  Init_System();//ϵͳ��ʼ��
  
  Set_USBClock();//����USBʱ��
  USB_Interrupts_Config(); //����USB�ж�
  
  USB_Init();//��ʼ��USB  
  
  
	
   GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ); //�ر�3��LED 
   
  while (1)
  {
   	 
    if (count_out != 0)	//�ж��������ݽ��յ�
    {  
	  
      
	  if(buffer_out[0]==0x01){GPIO_ResetBits(GPIOB, GPIO_Pin_14 );
	                          USB_Send_Data("LED1 ����\r\n");
							  count_out=0;
							 }	//������յ��������0X01������led1
	  if(buffer_out[0]==0x02){GPIO_ResetBits(GPIOB, GPIO_Pin_12 );
	                          USB_Send_Data("LED2 ����\r\n");
							  count_out=0;
							  }	
							  //������յ��������0X02������led2
	  if(buffer_out[0]==0x03){GPIO_ResetBits(GPIOB, GPIO_Pin_13 );
	                          USB_Send_Data("LED3 ����\r\n");
							  count_out=0;
							  }	
							  //������յ��������0X03������led3
	  if(buffer_out[0]==0x04){GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 );
	                          USB_Send_Data("LED ȫ��\r\n");
							  count_out=0;
							  } //������յ��������0X04��//�ر�3��LED  
    }
	
  }
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
