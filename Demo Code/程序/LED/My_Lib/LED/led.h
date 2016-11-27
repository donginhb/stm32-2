

#ifndef  _LED_H
#define  _LED_H

#define  LEDPort  GPIOD
#define  LEDPin   (1 << 7) 



void LED_Init(void);
void LED_ON(void);
void LED_OFF(void);


#endif
