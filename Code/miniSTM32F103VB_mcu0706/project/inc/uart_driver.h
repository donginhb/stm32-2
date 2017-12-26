#ifndef __UART_DRIVER_H
#define  __UART_DRIVER_H

extern void USART_AppInit(void);
extern void USART_Send(USART_TypeDef* USARTx, u8* str , u8 Nb_bytes);
extern void USART_SendString(USART_TypeDef* USARTx, u8* str );

#endif//__UART_DRIVER_H

