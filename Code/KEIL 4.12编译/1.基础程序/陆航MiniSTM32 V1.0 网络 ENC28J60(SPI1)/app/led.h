#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

#define ON	0
#define OFF	1

#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_10)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_11)

#define LED3(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_12)

void LED_GPIO_Config(void);

#endif /* __LED_H */
