#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "stm32f10x.h"
#include "stm32f10x_usart.h"

void  USART_Configuration(void);

uint8_t MODE_Flag=0;


/**********IR01F �ײ�������� begin*****************/
typedef unsigned char UINT8;
typedef unsigned char kal_uint8;
extern void IR_Learn_Start(void);
extern kal_uint8	Get_Learn_Data(unsigned char*learn_data_out);
extern void IR01F_Init_Cfg(void);
extern void Send_IR_Data(char* data, UINT8 count);
extern UINT8 GetBUSYStatus(void);
/**********IR01F �ײ�������� end *****************/

unsigned char data_out[112]; //�������ݻ���

/***********************************************************
* ��    �ƣ� void ID_Delay_ms(unsigned long uldata)
* ��    �ܣ� ���� ��ʱ����
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void ID_Delay_ms(unsigned long uldata)
{
	unsigned int i;
	uint8_t j;
	for (i=uldata*100;i>0;i--);
		for (j=110;j>0;j--);
}
/***********************************************************
* ��    �ƣ�USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len) 
* ��    �ܣ����������ӡ 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len)
{ 
	uint16_t i;
	for(i=0; i<Len; i++)
	{
		USART_SendData(USARTx, Data[i]);    //���͵�������
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);// ���ָ����USART��־λ
																//����Ƿ�����ɼ�RESET��1ʱ�������
	}
}

/***********************************************************
* ��    �ƣ� �������
* ��    �ܣ� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 
	����˵����
	        ������ͨ������PB14���º�ʼ�������ѧϰ��ѧϰ
			�ɹ���ͨ�����ڴ�ӡ��112�ֽ�ѧϰ�������ݣ�ͬʱ����
			data_out�����У�����ֱ�ӵ��÷��ͺ����������ݷ��ͣ�
			����ͨ������ͷ�����߶��豸���п��ƣ�������֤�Ƿ�
			ѧϰ�ɹ���					 
**********************************************************/
int main(void)
{
	uint8_t Learn_Flag=0;//ѧϰ��־
	uint8_t Learn_data_flag=0;//ѧϰ��
	//���尴�� PB14
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	GPIO_SetBits(GPIOB, GPIO_Pin_14) ;

	USART_Configuration();

	IR01F_Init_Cfg(); //IR01F��ʼ��
		while(1)
		{
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0) //��������ѧϰ
				{
					ID_Delay_ms(20);
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)!=0);
					
						MODE_Flag++;
						if(MODE_Flag==2) MODE_Flag=0;
						switch(MODE_Flag)
						{
							case 0:	
							break;
							case 1:IR_Learn_Start();   //����ѧϰ��������ѧϰ
										 Learn_Flag=1;
							break;
						}
				}

				if(GetBUSYStatus()==1 && Learn_Flag==1)	//�ж��Ƿ�ѧϰ�꣬ѧϰ���BUSYΪ��
					{
						Learn_Flag=0;
	//					MODE_Flag=0;
						Learn_data_flag=1; //�Ѿ�ѧϰ�ɹ���־
						Get_Learn_Data(data_out);
						USART_OUT(USART1,data_out,112);
					}
				if(Learn_data_flag==1)   //����ѧϰ���ĺ����ź�
				{
					Send_IR_Data(data_out, 112);				
				}
		}
}

/***********************************************************
* ��    �ƣ�   void  USART_Configuration(void)
* ��    �ܣ���������
* ��ڲ�����  
* ���ڲ�����
* ˵    ����
* ���÷����� 
**********************************************************/ 
void  USART_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;	//��������USART_InitTypeDef���͵Ľṹ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO\
												  , ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         //USART1 TX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);		    //A�˿� 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         //USART1 RX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //���ÿ�©����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);		         //A�˿� 
	 
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_Mode =  USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //ʹ�ܽ��� �ж� 
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  //ʹ�ܷ��� �ж� 
  USART_Cmd(USART1, ENABLE);
}
