//
/*******************************************************************************
*  函数功能：串口发送数据
*  编写时间：2010.12.22
*  作    者：张林
*******************************************************************************/

#include "stm32f10x_lib.h"

GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

/* 函数申明 -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART1_Configuration(void);
void USART2_Configuration(void);
void USART3_Configuration(void);
void USART4_Configuration(void);
void USART5_Configuration(void);
void WWDG_Configuration(void);
void Delay(u32 nTime);
void Delayms(vu32 m);  
/* 变量定义 ----------------------------------------------*/


/*
********************************************************************************
** 函数名称 ： main(void)
** 函数功能 ： 主函数
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
int main(void)
{
  
  RCC_Configuration();
  GPIO_Configuration();
  USART1_Configuration();
  USART2_Configuration();
  USART3_Configuration();
  //USART4_Configuration();  
  //USART5_Configuration();

  NVIC_Configuration();
 
  //WWDG_Configuration();
 
 
  while(1)
  {
		USART_SendData(USART1, 0x01);
		Delayms(10);
		USART_SendData(USART1, 0x02);
		Delayms(10);
		USART_SendData(USART1, 0x03);
		Delayms(10);
		USART_SendData(USART1, 0x04);
		Delayms(5);
		USART_SendData(USART2, 0x02);
		Delayms(5);
		USART_SendData(USART3, 0x03);
		Delayms(5);
		
		
  }
		     
}

/*
********************************************************************************
** 函数名称 ： RCC_Configuration(void)
** 函数功能 ： 时钟初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void RCC_Configuration(void)
{   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }  
}

/*
********************************************************************************
** 函数名称 ： GPIO_Configuration(void)
** 函数功能 ： 端口初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE  );
   /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //	选中管脚9
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // 选择A端口
    
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			  //选中管脚10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);				  //选择A端口

  /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //	选中管脚2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // 选择A端口
    
  /* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  //选中管脚3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);				  //选择A端口


  /* Configure USART3 Tx (PB.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //	选中管脚10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);				 // 选择B端口
    
  /* Configure USART3 Rx (PB.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			  //选中管脚11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);				  //选择B端口

   /* Configure USART4 Tx (PC.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //	选中管脚10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				 // 选择C端口
    
  /* Configure USART4 Rx (PC.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			  //选中管脚11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);				  //选择C端口

   /* Configure USART5 Tx (PC.12) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //	选中管脚12
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				 // 选择C端口
    
  /* Configure USART5 Rx (PD.2) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			  //选中管脚2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
  GPIO_Init(GPIOD, &GPIO_InitStructure);				  //选择D端口


}

/*
********************************************************************************
** 函数名称 ： USART1_Configuration(void)
** 函数功能 ： 串口1初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void USART1_Configuration(void)
{

USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef  USART_ClockInitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 |RCC_APB2Periph_USART1, ENABLE  );

USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;			// 时钟低电平活动
USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;				// 时钟低电平
USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;				// 时钟第二个边沿进行数据捕获
USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;		// 最后一位数据的时钟脉冲不从SCLK输出
/* Configure the USART1 synchronous paramters */
USART_ClockInit(USART1, &USART_ClockInitStructure);					// 时钟参数初始化设置
																	 
USART_InitStructure.USART_BaudRate = 115200;						  // 波特率为：115200
USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8位数据
USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // 在帧结尾传输1个停止位
USART_InitStructure.USART_Parity = USART_Parity_No ;				  // 奇偶失能
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制失能

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // 发送使能+接收使能
/* Configure USART1 basic and asynchronous paramters */
USART_Init(USART1, &USART_InitStructure);
    
  /* Enable USART1 */
USART_ClearFlag(USART1, USART_IT_RXNE); 			//清中断，以免一启用中断后立即产生中断
USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);		//使能USART1中断源
USART_Cmd(USART1, ENABLE);							//USART1总开关：开启 
}

/*
********************************************************************************
** 函数名称 ： USART2_Configuration(void)
** 函数功能 ： 串口2初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void USART2_Configuration(void)
{

USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef  USART_ClockInitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE  );

USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;			// 时钟低电平活动
USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;				// 时钟低电平
USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;				// 时钟第二个边沿进行数据捕获
USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;		// 最后一位数据的时钟脉冲不从SCLK输出
/* Configure the USART1 synchronous paramters */
USART_ClockInit(USART2, &USART_ClockInitStructure);					// 时钟参数初始化设置
																	 
USART_InitStructure.USART_BaudRate = 115200;						  // 波特率为：115200
USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8位数据
USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // 在帧结尾传输1个停止位
USART_InitStructure.USART_Parity = USART_Parity_No ;				  // 奇偶失能
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制失能

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // 发送使能+接收使能
/* Configure USART1 basic and asynchronous paramters */
USART_Init(USART2, &USART_InitStructure);
    
  /* Enable USART1 */
USART_ClearFlag(USART2, USART_IT_RXNE); 			//清中断，以免一启用中断后立即产生中断
USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);		//使能USART2中断源
USART_Cmd(USART2, ENABLE);							//USART2总开关：开启 
}


/*
********************************************************************************
** 函数名称 ： USART3_Configuration(void)
** 函数功能 ： 串口3初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void USART3_Configuration(void)
{

USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef  USART_ClockInitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE  );

USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;			// 时钟低电平活动
USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;				// 时钟低电平
USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;				// 时钟第二个边沿进行数据捕获
USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;		// 最后一位数据的时钟脉冲不从SCLK输出
/* Configure the USART1 synchronous paramters */
USART_ClockInit(USART3, &USART_ClockInitStructure);					// 时钟参数初始化设置
																	 
USART_InitStructure.USART_BaudRate = 115200;						  // 波特率为：57600
USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8位数据
USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // 在帧结尾传输1个停止位
USART_InitStructure.USART_Parity = USART_Parity_No ;				  // 奇偶失能
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制失能

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // 发送使能+接收使能
/* Configure USART3 basic and asynchronous paramters */
USART_Init(USART3, &USART_InitStructure);
    
  /* Enable USART3 */
USART_ClearFlag(USART3, USART_IT_RXNE); 			//清中断，以免一启用中断后立即产生中断
USART_ITConfig(USART3,USART_IT_RXNE, ENABLE);		//使能USART3中断源
USART_Cmd(USART3, ENABLE);							//USART3总开关：开启 
}

/*
********************************************************************************
** 函数名称 ： USART4_Configuration(void)
** 函数功能 ： 串口4初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/

void USART4_Configuration(void)
{

	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE  );
													 
	USART_InitStructure.USART_BaudRate = 115200;						  // 波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // 在帧结尾传输1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;				  // 奇偶失能
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制失能
	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // 发送使能+接收使能
	
	USART_Init(UART4, &USART_InitStructure);
	    
	 
	USART_ClearFlag(UART4, USART_IT_RXNE); 			//清中断，以免一启用中断后立即产生中断
	USART_ITConfig(UART4,USART_IT_RXNE, ENABLE);		//使能USART4中断源
	USART_Cmd(UART4, ENABLE);							//USART4总开关：开启 

 
}

/*
********************************************************************************
** 函数名称 ： USART4_Configuration(void)
** 函数功能 ： 串口4初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/

void USART5_Configuration(void)
{

	
	USART_InitTypeDef USART_InitStructure;
    //USART_ClockInitTypeDef  USART_ClockInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE  );
													 
	USART_InitStructure.USART_BaudRate =115200;						  // 波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // 在帧结尾传输1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;				  // 奇偶失能
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制失能
	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // 发送使能+接收使能
	
	USART_Init(UART5, &USART_InitStructure);
	    
	 
	USART_ClearFlag(UART5, USART_IT_RXNE); 			//清中断，以免一启用中断后立即产生中断
	USART_ITConfig(UART5,USART_IT_RXNE, ENABLE);		//使能USART5中断源
	USART_Cmd(UART5, ENABLE);							//USART5总开关：开启 

}




/*
********************************************************************************
** 函数名称 ： NVIC_Configuration(void)
** 函数功能 ： 中断初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void NVIC_Configuration(void)
{ 
  NVIC_InitTypeDef NVIC_InitStructure;  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 
 
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_Init(&NVIC_InitStructure);

}

 /*
********************************************************************************
** 函数名称 ： WWDG_Configuration(void)
** 函数功能 ： 看门狗初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void WWDG_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	
  WWDG_SetPrescaler(WWDG_Prescaler_8);	              //  WWDG clock counter = (PCLK1/4096)/8 = 244 Hz (~4 ms)  
  WWDG_SetWindowValue(0x41);		                 // Set Window value to 0x41
  WWDG_Enable(0x50);		       // Enable WWDG and set counter value to 0x7F, WWDG timeout = ~4 ms * 64 = 262 ms 
  WWDG_ClearFlag();			       // Clear EWI flag
  WWDG_EnableIT();			       // Enable EW interrupt
}

/*
********************************************************************************
** 函数名称 ： Delay(vu32 nCount)
** 函数功能 ： 延时函数
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
 void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

/*
********************************************************************************
** 函数名称 ： void Delayms(vu32 m)
** 函数功能 ： 长延时函数	 m=1,延时1ms
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
 void Delayms(vu32 m)
{
  u32 i;
  
  for(; m != 0; m--)	
       for (i=0; i<50000; i++);
}





/*
********************************************************************************
** 函数名称 ： WWDG_IRQHandler(void)
** 函数功能 ： 窗口提前唤醒中断
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/ 

void WWDG_IRQHandler(void)
{
  /* Update WWDG counter */
  WWDG_SetCounter(0x50);
	
  /* Clear EWI flag */
  WWDG_ClearFlag();
  
}

/*************结束***************/
