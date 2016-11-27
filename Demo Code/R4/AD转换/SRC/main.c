//
/*******************************************************************************
*  函数功能：AD转换
*  编写时间：2010.12.23
*  作    者：雁翎电子
*******************************************************************************/

#include "stm32f10x_lib.h"

#define ADC1_DR_Address    ((u32)0x4001244C)
ErrorStatus HSEStartUpStatus;

/* 函数申明 -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void ADC1_Configuration(void);
void USART1_Configuration(void);
void WWDG_Configuration(void);
void Delay(vu32 nCount); 
void Delayms (vu32 m); 

/* 变量定义 ----------------------------------------------*/

vu16 ADC_ConvertedValue;
u8 data_temp;
u16 AD_value;
 
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
  ADC1_Configuration();  
  USART1_Configuration(); 
  NVIC_Configuration();			   	 
  while(1)
  {
   AD_value=ADC_GetConversionValue(ADC1);  // 返回最近一次ADCx规则组的转换结果 
   Delayms(300);

   USART_SendData(USART1, (0xff00&AD_value)>>4);
   USART_SendData(USART1, 0x00ff&AD_value);
    


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

  /* Configure PC.04 (ADC Channel—14) as analog input*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				// 选中管脚4
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			// 模拟输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);				//选择C端口
}

/*
********************************************************************************
** 函数名称 ： ADC1_Configuration(void)
** 函数功能 ： ADC1初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void ADC1_Configuration(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );
   /* Time Base configuration */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立工作模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//扫描方式
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//连续转换
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发禁止
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = 1;//用于转换的通道数
  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);	//采样时间为55.5周期 
  ADC_DMACmd(ADC1, ENABLE);	   //  使能 ADC1 DMA
  ADC_Cmd(ADC1, ENABLE);       //  使能 ADC1
  ADC_ResetCalibration(ADC1);  // 重置指定的ADC的校准寄存器

  while(ADC_GetResetCalibrationStatus(ADC1)); // Check the end of ADC1 reset calibration register
  ADC_StartCalibration(ADC1); // Start ADC1 calibaration
  while(ADC_GetCalibrationStatus(ADC1)); //	Check the end of ADC1 calibration
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);//Start ADC1 Software Conversion 

  
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
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE  );

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
 
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;		  //更新事件
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  //抢占优先级0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		  //响应优先级5
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断
  NVIC_Init(&NVIC_InitStructure);							  //写入设置

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
** 函数功能 ： 短延时函数	  i=1;40us延时
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
