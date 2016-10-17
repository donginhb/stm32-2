#define BSP_GLOBALS
#include "includes.h"

static volatile ErrorStatus HSEStartUpStatus = SUCCESS;

static void SysTick_Config(void);
void GPIO_Config(void);
void NVIC_Config(void);
void Interrupt_Config(void);

/**************************************************************************/
void BSP_Init(void)
{
    RCC_DeInit();

    RCC_HSEConfig(RCC_HSE_ON);
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if(HSEStartUpStatus == SUCCESS)
    {
      FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
      FLASH_SetLatency(FLASH_Latency_2);
      RCC_HCLKConfig(RCC_SYSCLK_Div1);
      RCC_PCLK2Config(RCC_HCLK_Div1);
      RCC_PCLK1Config(RCC_HCLK_Div2);
      RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);

      RCC_PLLCmd(ENABLE);

      while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
      {
       }

      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
      
      while(RCC_GetSYSCLKSource() != 0x08)
      {
       }
      
     }
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //根据使用的引脚修改

    GPIO_Config();
    Interrupt_Config();
    SysTick_Config();
}

static void SysTick_Config(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    u32  cnts;

    RCC_GetClocksFreq(&rcc_clocks);
    
    cnts = (u32)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;

    SysTick_SetReload(cnts);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_CounterCmd(SysTick_Counter_Enable);
    SysTick_ITConfig(ENABLE);
}

void GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);	 //释放JTAG脚作为普通IO口
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //根据使用的引脚修改 

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_8;	//根据使用的引脚修改
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);				 //根据使用的引脚修改


}

void Interrupt_Config(void)
{
    //NVIC_InitTypeDef NVIC_InitStruct;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick,0,0);

}






