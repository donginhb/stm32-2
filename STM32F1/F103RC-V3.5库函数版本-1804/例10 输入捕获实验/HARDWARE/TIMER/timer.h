#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com **************/



void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM5_Cap_Init(u16 arr,u16 psc);


#endif
