
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#include "stm32f10x.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

/*private IRQ functions*/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void TIM2_IRQHandler(void);
//void EXTI15_10_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);

void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif

