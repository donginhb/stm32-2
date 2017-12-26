#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x_lib.h"
#include "platform_config.h"

extern void Delay(vu32 nCount);
extern void Delaynus(vu32 nus);

#endif
