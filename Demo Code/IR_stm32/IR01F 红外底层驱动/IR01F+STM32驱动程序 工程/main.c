#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "stm32f10x.h"
#include "stm32f10x_usart.h"

void  USART_Configuration(void);

uint8_t MODE_Flag=0;


/**********IR01F 底层驱动相关 begin*****************/
typedef unsigned char UINT8;
typedef unsigned char kal_uint8;
extern void IR_Learn_Start(void);
extern kal_uint8	Get_Learn_Data(unsigned char*learn_data_out);
extern void IR01F_Init_Cfg(void);
extern void Send_IR_Data(char* data, UINT8 count);
extern UINT8 GetBUSYStatus(void);
/**********IR01F 底层驱动相关 end *****************/

unsigned char data_out[112]; //红外数据缓存

/***********************************************************
* 名    称： void ID_Delay_ms(unsigned long uldata)
* 功    能： 粗略 延时函数
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void ID_Delay_ms(unsigned long uldata)
{
	unsigned int i;
	uint8_t j;
	for (i=uldata*100;i>0;i--);
		for (j=110;j>0;j--);
}
/***********************************************************
* 名    称：USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len) 
* 功    能：串口输出打印 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len)
{ 
	uint16_t i;
	for(i=0; i<Len; i++)
	{
		USART_SendData(USARTx, Data[i]);    //发送单个数据
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);// 检查指定的USART标志位
																//检查是否发送完成即RESET＝1时发送完成
	}
}

/***********************************************************
* 名    称： 程序入口
* 功    能： 
* 入口参数： 无 
* 出口参数：无
* 说    明： 
	功能说明：
	        本程序通过按键PB14按下后开始进入红外学习，学习
			成功后通过串口打印出112字节学习到的数据，同时存入
			data_out数组中，接着直接调用发送函数进行数据发送，
			可以通过摄像头看或者对设备进行控制，进行验证是否
			学习成功！					 
**********************************************************/
int main(void)
{
	uint8_t Learn_Flag=0;//学习标志
	uint8_t Learn_data_flag=0;//学习完
	//定义按键 PB14
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	GPIO_SetBits(GPIOB, GPIO_Pin_14) ;

	USART_Configuration();

	IR01F_Init_Cfg(); //IR01F初始化
		while(1)
		{
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0) //按键触发学习
				{
					ID_Delay_ms(20);
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)!=0);
					
						MODE_Flag++;
						if(MODE_Flag==2) MODE_Flag=0;
						switch(MODE_Flag)
						{
							case 0:	
							break;
							case 1:IR_Learn_Start();   //调用学习函数进行学习
										 Learn_Flag=1;
							break;
						}
				}

				if(GetBUSYStatus()==1 && Learn_Flag==1)	//判断是否学习完，学习完后BUSY为高
					{
						Learn_Flag=0;
	//					MODE_Flag=0;
						Learn_data_flag=1; //已经学习成功标志
						Get_Learn_Data(data_out);
						USART_OUT(USART1,data_out,112);
					}
				if(Learn_data_flag==1)   //发送学习到的红外信号
				{
					Send_IR_Data(data_out, 112);				
				}
		}
}

/***********************************************************
* 名    称：   void  USART_Configuration(void)
* 功    能：串口配置
* 入口参数：  
* 出口参数：
* 说    明：
* 调用方法： 
**********************************************************/ 
void  USART_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;	//定义属于USART_InitTypeDef类型的结构体
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO\
												  , ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         //USART1 TX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);		    //A端口 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         //USART1 RX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //复用开漏输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);		         //A端口 
	 
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_Mode =  USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //使能接收 中断 
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  //使能发送 中断 
  USART_Cmd(USART1, ENABLE);
}
