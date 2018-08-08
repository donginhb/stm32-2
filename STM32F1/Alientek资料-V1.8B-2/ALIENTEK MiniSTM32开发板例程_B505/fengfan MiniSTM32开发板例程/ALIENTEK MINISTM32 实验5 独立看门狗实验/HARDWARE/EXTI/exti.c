#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//Mini STM32¿ª·¢°å
//Íâ²¿ÖÐ¶Ï Çý¶¯´úÂ 
////////////////////////////////////////////////////////////////////////////////// 	  
 

//Íâ²¿ÖÐ¶Ï0·þÎñ³ÌÐò
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//Ïû¶¶
	if(KEY2==1)	 //°´¼ü2
	{
		LED0=!LED0;
		LED1=!LED1;	
	}		 
	EXTI->PR=1<<0;  //Çå³ýLINE0ÉÏµÄÖÐ¶Ï±êÖ¾Î»  
}

//Íâ²¿ÖÐ¶Ï15~10·þÎñ³ÌÐò
void EXTI15_10_IRQHandler(void)
{			
	delay_ms(10);    //Ïû¶¶			 
	if(KEY0==0)      //°´¼ü0
	{
		LED0=!LED0;
	}else if(KEY1==0)//°´¼ü1
	{
		LED1=!LED1;
	}
	EXTI->PR=1<<13;     //Çå³ýLINE13ÉÏµÄÖÐ¶Ï±êÖ¾Î»  
	EXTI->PR=1<<15;     //Çå³ýLINE15ÉÏµÄÖÐ¶Ï±êÖ¾Î»  
}
//Íâ²¿ÖÐ¶Ï³õÊ¼»¯³ÌÐò
//³õÊ¼»¯PA0,PA13,PA15ÎªÖÐ¶ÏÊäÈë.
void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<2;     //Ê¹ÄÜPORTAÊ±ÖÓ
	JTAG_Set(JTAG_SWD_DISABLE);//¹Ø±ÕJTAGºÍSWD   

	GPIOA->CRL&=0XFFFFFFF0;//PA0ÉèÖÃ³ÉÊäÈë	  
	GPIOA->CRL|=0X00000008;   
	GPIOA->CRH&=0X0F0FFFFF;//PA13,15ÉèÖÃ³ÉÊäÈë	  
	GPIOA->CRH|=0X80800000; 				   
	GPIOA->ODR|=1<<13;	   //PA13ÉÏÀ­,PA0Ä¬ÈÏÏÂÀ­
	GPIOA->ODR|=1<<15;	   //PA15ÉÏÀ­

	Ex_NVIC_Config(GPIO_A,0,RTIR); //ÉÏÉýÑØ´¥·¢
	Ex_NVIC_Config(GPIO_A,13,FTIR);//ÏÂ½µÑØ´¥·¢
	Ex_NVIC_Config(GPIO_A,15,FTIR);//ÏÂ½µÑØ´¥·¢

	MY_NVIC_Init(2,2,EXTI0_IRQChannel,2);    //ÇÀÕ¼2£¬×ÓÓÅÏÈ¼¶2£¬×é2
	MY_NVIC_Init(2,1,EXTI15_10_IRQChannel,2);//ÇÀÕ¼2£¬×ÓÓÅÏÈ¼¶1£¬×é2	   
}












