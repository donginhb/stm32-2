//mp_out.c

#include "includes.h"

#if MP_EN>0

void Init_MpGpio(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
	//#############################################
	  /* Configure IO connected to buz *********************/
	  /* Enable GPIO_buz clock */
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_MP , ENABLE );

	  GPIO_InitStructure.GPIO_Pin = MP1_FAN_PIN | MP2_FAN_PIN |MP3_FAN_PWR_PIN|MP4_PUMP_PIN ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init( GPIO_MP , &GPIO_InitStructure );

	//buz off**********************
  	GPIO_SetBits(GPIO_MP , MP1_FAN_PIN);
	GPIO_SetBits(GPIO_MP , MP2_FAN_PIN);
	GPIO_SetBits(GPIO_MP , MP3_FAN_PWR_PIN);
	GPIO_SetBits(GPIO_MP , MP4_PUMP_PIN);
}

void Init_Mp(void)
{
	Init_MpGpio();
}

void Mp_Fan1(BitAction OnOff)	
{
	if(OnOff == MP_ON)
		GPIO_SetBits(GPIO_MP, MP1_FAN_PIN);
	else		
		GPIO_ResetBits(GPIO_MP, MP1_FAN_PIN);
}

void Mp_Fan2(BitAction OnOff)	
{
	if(OnOff == MP_ON)
		GPIO_SetBits(GPIO_MP, MP2_FAN_PIN);
	else	
		GPIO_ResetBits(GPIO_MP, MP2_FAN_PIN);
}

void Mp_Fan12(BitAction OnOff)	
{
	Mp_Fan2(OnOff);
	Mp_Fan1(OnOff);
}


#ifdef MP_DUB

void Mp_test(void)
{
	
	GPIO_SetBits(GPIO_MP, MP1_FAN_PIN);
	GPIO_ResetBits(GPIO_MP, MP1_FAN_PIN);
	
	GPIO_SetBits(GPIO_MP, MP2_FAN_PIN);
	GPIO_ResetBits(GPIO_MP, MP2_FAN_PIN);
	
	GPIO_SetBits(GPIO_MP, MP3_FAN_PWR_PIN);
	GPIO_ResetBits(GPIO_MP, MP3_FAN_PWR_PIN);
	
	GPIO_SetBits(GPIO_MP, MP4_PUMP_PIN);
	GPIO_ResetBits(GPIO_MP, MP4_PUMP_PIN);
}

#endif //MP_DUB


#endif //#if MP_EN>0

