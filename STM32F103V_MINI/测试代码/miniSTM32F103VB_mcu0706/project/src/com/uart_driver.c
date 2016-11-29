//uart_driver.c
#include"includes.h"
#if UART_DRIVER_EN > 0
//
void USART_GpioInit(void);
void USART_DefaultSet(void);
void USART_NVIC_Configuration(void );

/* Private functions ---------------------------------------------------------*/
void USART_GpioInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	  
  /* Enable USART1, GPIOA, GPIOx and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA  , ENABLE);
  /* Enable USART2 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
 /* Configure USART2 Rx  (PA.03)as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure USART2 Tx (PA.02)as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
}
void USART_DefaultSet(void)
{
	USART_InitTypeDef USART_InitStructure;

	/* USART1 and USART2 configuration -------------------*/
	/* USART and USART2 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
	*/
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USART1 */
	USART_Init(USART1, &USART_InitStructure);
	/* Configure USART2 */
	USART_Init(USART2, &USART_InitStructure);
  
	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

	/* Enable USART2 Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	// USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);
	/* Enable the USART2 */
	USART_Cmd(USART2, ENABLE);
	
}
void USART_NVIC_Configuration(void)
{

	  NVIC_InitTypeDef NVIC_InitStructure;
	  
	  /* Configure the NVIC Preemption Priority Bits */  
	  /* Enable the USART1 Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	  
	  /* Enable the USART2 Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	  
}
//
void USART_AppInit(void)
{	

	USART_GpioInit();
	USART_DefaultSet();
	USART_NVIC_Configuration( );
	//USART_SendString( USART1 , " USART1 & USART2 App Init OK!"  );
	
}
/*******************************************************************************
* Function Name  : USART_Send.
* Description    : send the received data from USB to the UART 0.
* Input          : data_buffer: data address.
                   Nb_bytes: number of bytes to send.
                   USART1: debug;
                   USART2: com--usb
* Return         : none.
*******************************************************************************/
void USART_Send(USART_TypeDef* USARTx, u8* str , u8 Nb_bytes)
{

	u8 i;
	for (i = 0; i < Nb_bytes; i++)
	{
		USART_SendData( USARTx , *(str + i));
		while(USART_GetFlagStatus( USARTx, USART_FLAG_TXE) == RESET); 
	}
	
}
/*******************************************************************************
* Function Name  : USB_To_UART_Send_Data.
* Description    : send the received data from USB to the UART 0.
* Input          : data_buffer: data address.
                   Nb_bytes: number of bytes to send.
                   USART1: debug;
                   USART2: com--usb
* Return         : none.
*******************************************************************************/
void USART_SendString(USART_TypeDef* USARTx, u8* str )
{
  while( * str != '\0' )
  {
	 USART_SendData( USARTx , *(str ++) );
	 while(USART_GetFlagStatus( USARTx, USART_FLAG_TXE ) == RESET ); 
  }  
}
#else
/*******************************************************************************
* Function Name  : USART_Send.
* Description    : send the received data from USB to the UART 0.
* Input          : data_buffer: data address.
                   Nb_bytes: number of bytes to send.
                   USART1: debug;
                   USART2: com--usb
* Return         : none.
*******************************************************************************/
void USART_Send(USART_TypeDef* USARTx, u8* str , u8 Nb_bytes)
{
}
/*******************************************************************************
* Function Name  : USB_To_UART_Send_Data.
* Description    : send the received data from USB to the UART 0.
* Input          : data_buffer: data address.
                   Nb_bytes: number of bytes to send.
                   USART1: debug;
                   USART2: com--usb
* Return         : none.
*******************************************************************************/
void USART_SendString(USART_TypeDef* USARTx, u8* str )
{
}

#endif //#if UART_DRIVER_EN > 0
//end

