#include "sys.h"
#include "delay.h"
#include "usart.h"

void IO_Init(void);

int main(void)
{
		delay_init();//延时函数初始
		IO_Init();
	
		GPIOA->ODR=0XFFFF;
		GPIOB->ODR=0XFFFF;
		GPIOC->ODR=0XFFFF;
		GPIOD->ODR=0XFFFF;
		GPIOE->ODR=0XFFFF;
		GPIOF->ODR=0XFFFF;
		GPIOG->ODR=0XFFFF;
		delay_ms(300);
	
		GPIOA->ODR=0X0000;
		GPIOB->ODR=0X0000;
		GPIOC->ODR=0X0000;
		GPIOD->ODR=0X0000;
		GPIOE->ODR=0X0000;
		GPIOF->ODR=0X0000;
		GPIOG->ODR=0X0000;
		delay_ms(300);
}

void IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;				 //
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 
	GPIO_Init(GPIOF, &GPIO_InitStructure);					 
	GPIO_Init(GPIOG, &GPIO_InitStructure);		
}
