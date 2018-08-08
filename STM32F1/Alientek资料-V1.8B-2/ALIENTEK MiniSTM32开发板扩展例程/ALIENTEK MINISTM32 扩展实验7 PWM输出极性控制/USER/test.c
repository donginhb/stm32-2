#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"	 	 
//Mini STM32开发板扩展实例 7
//PWM输出 实验
//正点原子@ALIENTEK
//2010.12.25	
   

int main(void)
{				 
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口
	PWM_Init(90,0);	 //不分频。PWM频率=72000/900=8Khz
   	//可以通过注释：TIM3->CCER|=1<<5;这句，来观看结果，此结果完全软件仿真即可看到。
	//在波形观察里面新建一个PORTA.7的信号，就能看到修改TIM3->CCER第5位的值产生的结果了。
	while(1)
	{	
		TIM3->CCER|=1<<5;   //低电平有效						 
 		delay_ms(10);	 	  					 
		LED0_PWM_VAL=45;	   
 		delay_ms(10);	 
 		LED0_PWM_VAL=0;	  
		delay_ms(10);	 
		LED0_PWM_VAL=45;	   
		delay_ms(10);	 
 		LED0_PWM_VAL=0;	   
		TIM3->CCER&=~(1<<5);//高电平有效 						 
 		delay_ms(10);	 	  					 
		LED0_PWM_VAL=45;	   
 		delay_ms(10);	 
 		LED0_PWM_VAL=0;	  
		delay_ms(10);	 
		LED0_PWM_VAL=45;	   
		delay_ms(10);	 
 		LED0_PWM_VAL=0;	
	}	 
}

























