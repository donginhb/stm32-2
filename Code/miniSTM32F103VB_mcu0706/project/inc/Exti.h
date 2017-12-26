//File:exti.h

#ifndef __EXTI_H
#define __EXTI_H

extern int PluseCnt;

#if 0
#define GPIO_PIN_KEY_BUTTON               GPIO_Pin_0
#define GPIO_KEY_BUTTON                   GPIOC    
#define RCC_APB2Periph_GPIO_KEY_BUTTON    RCC_APB2Periph_GPIOC

#define EXTI_LINE_KEY_BUTTON              EXTI_Line0
#define GPIO_PORT_SOURCE_KEY_BUTTON       GPIO_PortSourceGPIOC
#define GPIO_PIN_SOURCE_KEY_BUTTON        GPIO_PinSource0
 #endif
 
extern void ExtiTest(void);

 
#endif //__EXTI_H


