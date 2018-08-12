#ifndef __LED_H
#define	__LED_H

#include "stm32f7xx.h"

//���Ŷ���
/*******************************************************/
//Сָʾ��
#define LED4_PIN                  GPIO_PIN_11                 
#define LED4_GPIO_PORT            GPIOD                       
#define LED4_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOD_CLK_ENABLE()
/************************************************************/

/** ����LED������ĺ꣬
	* LED�͵�ƽ��������ON=0��OFF=1
	* ��LED�ߵ�ƽ�����Ѻ����ó�ON=1 ��OFF=0 ����
	*/
#define ON  GPIO_PIN_RESET
#define OFF GPIO_PIN_SET

/* ���κ꣬��������������һ��ʹ�� */
#define LED4(a)	HAL_GPIO_WritePin(LED4_GPIO_PORT,LED4_PIN,a)

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)			{p->BSRR=i;}			  //����Ϊ�ߵ�ƽ		
#define digitalLo(p,i)			{p->BSRR=(uint32_t)i << 16;}				//����͵�ƽ
#define digitalToggle(p,i)		{p->ODR ^=i;}			//�����ת״̬

/* �������IO�ĺ� */
#define LED4_TOGGLE		digitalToggle(LED4_GPIO_PORT,LED4_PIN)
#define LED4_OFF		digitalHi(LED4_GPIO_PORT,LED4_PIN)
#define LED4_ON			digitalLo(LED4_GPIO_PORT,LED4_PIN)

void LED_GPIO_Config(void);

#endif /* __LED_H */
