/*
 * File:		uart.h
 * Purpose:     Provide common ColdFire UART routines for polled serial IO
 *
 * Notes:
 */

#ifndef __UART_H__
#define __UART_H__

#include "vectors.h"
#include "isr.h"
#include "common.h"

/* �����ײ��жϷ����ӳ��� */

//UARTģ���жϷ�����
//#undef  VECTOR_061
//#define VECTOR_061 UART_Isr
//#undef  VECTOR_063
//#define VECTOR_063 USART3_IRQHandlerֱ����vectors.c�����޸��ж϶���
//#undef  VECTOR_065
//#define VECTOR_065 UART_Isr
//#undef  VECTOR_067
//#define VECTOR_067 UART_Isr
//#undef  VECTOR_069
//#define VECTOR_069 UART_Isr
//#undef  VECTOR_071
//#define VECTOR_071 UART_Isr
//���º�����LPLD_Kinetis�ײ���������޸�
extern void LPLD_UART_Isr(void);

/*
 * UARTģ��
 *
 */
typedef enum UARTx
{
  UART0,
  UART1,
  UART2,
  UART3,
  UART4,
  UART5
}UARTx;

/********************************************************************/

void uart_init (UART_MemMapPtr uartch, int sysclk, int baud);
char uart_getchar (UART_MemMapPtr channel);
void uart_putchar (UART_MemMapPtr channel, char ch);
int uart_getchar_present (UART_MemMapPtr channel);


//UARTģ���жϻص���������
typedef void (*UART_ISR_CALLBACK)(void);

//UART�����ж�ʹ��
void uart_irq_EN(UART_MemMapPtr channel,uint8 UART_NUM);
//UART�����жϽ���
void uart_irq_DIS(UART_MemMapPtr channel,uint8 UART_NUM);
//UART�жϷ���
//void UART_Isr(void);

void USART3_IRQHandler(void);

/********************************************************************/

#endif /* __UART_H__ */
