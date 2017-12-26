/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : Main program body.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);

#if LCM_GUI_EN>0
#ifdef LCM_KEY_DUG	 	
bool KeyLCMDis(void );
#endif //#ifdef LCM_KEY_DUG	 	
#endif

void Init_Sys( void );

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{	
	#ifdef DEBUG
	  debug();
	#endif

  /* System Clocks Configuration **********************************************/
	RCC_Configuration();   

  /* NVIC Configuration *******************************************************/
	NVIC_Configuration();

    /* GPIO Configuration */
	GPIO_Configuration();
	
	/*所用的模块初始化*/
	Init_Sys();	
	
	#if LCM_GUI_EN>0
	#ifdef LCM_KEY_DUG	
	//LCM_ShowMenu(MenuPoint , DisBuf);	
	#endif
	#endif		
	while (1)
	{  	
		LedAutoOnOff(LED1);
		USART_SendString( USART1 , "\n USART1 Test Proc!\n"  );
		USART_SendString( USART2 , "\n USART2 Test Proc!\n"  );
		Delaynus(3000000);
		LedAutoOnOff(LED2);
		USART_SendString( USART1 , "\n USART1 Test Proc!\n"  );
		USART_SendString( USART2 , "\n USART2 Test Proc!\n"  );
		Delaynus(3000000);		
		//-----lcd display test---------
		#ifdef LCM_DUG
		LCM_test();			
		#endif

		#ifdef EXTI_DUG
		 ExtiTest();
		#endif  //#ifdef EXTI_DUG
			
		#if LCM_GUI_EN>0
		#ifdef LCM_KEY_DUG	 		
		KeyLCMDis();		
		#endif 
		#endif

		#if COM_EN>0
		#ifdef COM_DUB
		Com_test();
		#endif		
		#endif
		
		#if SPI_FLASH_EN >0
		#ifdef SPI_FLASH_DUB
		spif_test();
		#endif
		#endif
		
	}
}
/*******************************************************************************
* Function Name  : Init_Sys
* Description    :
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void Init_Sys( void )
{
	
	#if UART_DRIVER_EN > 0
	USART_AppInit();	
	USART_SendString( USART1 , "\n USART1 Test Proc!\n"  );
	#endif	//UART_DRIVER_EN>0
	
	#if LED103_EN > 0
	Init_LedGpio();
	#endif
		

	#if ENCODER_EN>0
	ENC_Init( );
	#endif
	

	#if KEY_EN>0
	Init_Key() ;
	#endif
	
	TB_Init();  
		
	/*按键扫描和运动控制状态反转使用同一个定时器
	必须在开启定器之前初始化MC_ServoPosDeInit ， MC_SpdCarParaInit*/
	#if (KEY_EN>0)
	Init_KeyPosPMTime();
	#endif
	
	#if LCM_GUI_EN>0
	Init_LCMGUI( );  /*加入lcm程序，必须插lcm，否则程序通不过忙检测*/
	#endif
	
	
}
/*******************************************************************************
* Function Name  : KeyLCMDis
* Description    :
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
#if LCM_GUI_EN>0
#ifdef LCM_KEY_DUG	 	
bool KeyLCMDis(void )
{
	 u8 MenuChangFlag = FALSE ;
	 s8 KeyValTmp = 0 ;
	 vu8 tKeyVal= ERR_KEYVALUE;
	 u8 i ;
	struct MenuItem *m  ;
	tKeyVal = Key_ValGet() ;
	if (tKeyVal != ERR_KEYVALUE)
	{		
		//LedAutoOnOff(LED1);
		m= MenuPoint;
		KeyValTmp = tKeyVal ;
		for(i = 0 ; i < m->MenuCount ; i ++)
		{
			if(KeyValTmp == m->KeyVal)
			{
				//键值函数
				if(m->Subs != NullSubs )
				{
					(*m->Subs)( );/*执行按键功能函数*/
				}
				//键子菜单
				{
					if(m->ChildrenMenus != &Null_MenuItem)
					{
						MenuPoint = m->ChildrenMenus ;
						MenuChangFlag = TRUE ;
					}
					else
						MenuChangFlag = FALSE ;
				}				
				break;
			}				
			m++;				
		}                   			
		if(MenuChangFlag == TRUE)
              {         
			LCM_ShowMenu(MenuPoint , DisBuf);					
              } 
		 Key_ValClear();
		return TRUE ;								
	}
	return FALSE ;
}
#endif //#ifdef LCM_KEY_DUG	 	
#endif //#if LCM_GUI_EN>0

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{   
  ErrorStatus HSEStartUpStatus;
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 	
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);
    
    /* ADCCLK = PCLK2/6 */
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    
    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    { }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  //
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB
   							|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD
   							|RCC_APB2Periph_GPIOE ,  ENABLE ) ;
   
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{

	//NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM  
	  /* Set the Vector Table base location at 0x20000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
	  /* Set the Vector Table base location at 0x08000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif

	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

}
/*****************************************************************************
* Function Name  : GPIO Configuration ()
* Description    : gpio config 
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void   GPIO_Configuration(void)
{	

	  GPIO_InitTypeDef GPIO_InitStructure;
	 //#############################################
	  /* Configure IO  *********************/
	  GPIO_InitStructure.GPIO_Pin = 0xffff ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;	  
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
	  GPIO_Init(GPIOE, &GPIO_InitStructure);
	  
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
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
