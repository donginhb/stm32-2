#ifndef __LED103_H
#define __LED103_H

#include "stm32f10x_lib.h"
#include "platform_config.h"

#define  LED_OFF  Bit_RESET 
#define  LED_ON   Bit_SET

#define LED1  LED_PIN0
#define LED2  LED_PIN1


extern  void Init_LedGpio(void);
extern void Led( u16 ledno , BitAction onoff) ;
extern  void LedAutoOnOff( u16 ledno );
#endif //__LED_H


