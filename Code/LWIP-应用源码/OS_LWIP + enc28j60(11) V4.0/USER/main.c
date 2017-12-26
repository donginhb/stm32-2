/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The RTC application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-10-30
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "RTC_Time.h" 
#include <stdio.h>

#include "spi.h"
#include "err.h"
#include "etharp.h"
#include "Dhcp.h"

//#include "stm32f10x_map.h"
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);
void USART_Configuration(void);

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
EXTI_InitTypeDef EXTI_InitStructure;
void NVIC_Configuration(void);

void EXIT_Interrupt_Configuration( void )
{

	RCC->APB2ENR|=1<<2|1<<4;     //使能PORTA/C时钟
  	RCC->APB2ENR|=1<<0;     //复用重映射	 必须要 否则不产生中断	 RCC_APB2ENR_AFIOEN	 RCC_APB2ENR_IOPCEN
RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
NVIC_Configuration(); 

  /* Connect Key Button EXTI Line to Key Button GPIO Pin */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);

  /* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
 
  EXTI_GenerateSWInterrupt( EXTI_Line1 ); 
}

static System_Setup( void )
{	SystemInit();
	GPIO_Configuration();
	USART_Configuration();

	printf("\r\n");

	printf("LWIP NO_SYS   ");		printf("Can ping\r\n");

//PC8 = 0; PC9 = 0; PC10 = 0; PC11 = 0;	
//	RTC_Init();
 /*
RCC->APB2ENR|=1<<5;    //使能PORTD时钟	
GPIOD->CRH|=3|(3<<4)|(3<<8)|(3<<12);//设定GPIOD 8,9,10,11,为输出模式，最大时钟50M
GPIOD->CRH&=~(  (3<<2)|(3<<6)|(3<<10)|(3<<14)  );//推挽输出

	EXIT_Interrupt_Configuration();
   if (SysTick_Config(SystemCoreClock / 1000))
  { 
    // Capture error  
   // while (1);
  }	
*/
	SPInet_Init(); //初始化 以太网SPI接口  
}
void delay(unsigned int dly)
{
     while( dly--);
}
/*****************************************************************************************************************************/
//void dhcp_fine_tmr(void);  void dhcp_fine_tmr(void); 
void LwIP_Init( void );   void httpd_init( void );


 void TCP_Client_Init(void);void UDP_Test_Init(void); void UDP_send( void ); void HelloWorld_init(void); void http_init(void);

void tcp_tmr(void);
int main(void)
{ extern struct netif netif;	err_t  ethernetif_input(struct netif *netif); 
static unsigned long Time_Count;	static unsigned long TCP_Count;	 static unsigned int  Ethernetif_input;

static unsigned long Flag;
 err_t err;	
  /* Setup STM32 system (clocks, Ethernet, GPIO, NVIC) and STM3210C-EVAL resources */
    System_Setup();

  /* Initilaize the LwIP satck */
  LwIP_Init();
ethernetif_input(&netif);
 http_init();
                                            /* Initilaize the webserver module */
                                             // httpd_init();
  /* Initilaize the HelloWorld module */
 // HelloWorld_init();
                                               //	LwIPEntry(NULL);
   //Test_UDP(); 
 // UDP_Test_Init(); //UDP 服务器
//delay(0x65432);
ethernetif_input(&netif);
    /* Infinite loop */
    while ( 1 ){	 

		  if( Ethernetif_input ++> 500 ) {
		    /* Read a received packet from the Ethernet buffers and send it to the lwIP for handling */
          err = ethernetif_input(&netif);

		  Ethernetif_input =0;
		  }


	      if( TCP_Count ++> 100000 ) { 
 // 	   
	          tcp_tmr();
		      TCP_Count = 0;	
          }
	   

		     if ( Time_Count++ > 60000*20 )  { //TCP_Client_Init();
		  	//   err = ethernetif_input(&netif);
			    etharp_tmr(); 
		 	 // UDP_send();
		       Time_Count = 0;		    
				  
			//	 dhcp_fine_tmr(); 
			//	  dhcp_coarse_tmr();
				 }
			if (ERR_OK == err ) {
			
			   // printf("Recive Data Fram ");
			}
         	  
    }
}
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the EXTI1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configure GPIO Pin
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 						 
/**
 *	LED -> PB1
 */					 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configure USART1 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_Configuration(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
  /*
  *  USART1_TX -> PA9 , USART1_RX ->	PA10
  */				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);		   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 
  USART_Init(USART1, &USART_InitStructure); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  USART_Cmd(USART1, ENABLE); 
}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
   static FunctionalState Display;
   if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
    /* Clear the RTC Second interrupt */
    RTC_ClearITPendingBit(RTC_IT_SEC);
	/*====LED=======*/
	if( Display == ENABLE ) { GPIO_ResetBits(GPIOB , GPIO_Pin_1); Display = DISABLE; //Display=~Display; 
	}  
	else { GPIO_SetBits(GPIOB , GPIO_Pin_1); Display = ENABLE;//Display=~Display; 
	}  

    Time_Display();
  }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
