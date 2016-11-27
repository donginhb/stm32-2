#include "stm32f10x.h"
#include "HT1621.h"


/*
__asm __INLINE void __nop() 
{ 
    nop.w
}*/
static void GpioConfigurationHT1621(void)
{
     GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* Enable the GPIO_LED Clock */
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	
	/* Configure the GPIO_LED pin */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	 GPIO_Init(GPIOB, &GPIO_InitStructure);  
}
static void Nop(unsigned char ucDat)
{
    while(ucDat--) {
	  __NOP(); __nop();__NOP(); __nop();

	}
}
static void WriteClockHt1621(void)
{
	Nop(10);
	RW_L(); Nop(10);
	RW_H();	Nop(10);	
}

static void WriteCommandHt1621(u8 FunctonCode)
{
   u8 Shift = 0x80; u8 i;
   Nop(10);
   CS_L();    Nop(10);
   DATA_H();  WriteClockHt1621();
   DATA_L();  WriteClockHt1621();
   DATA_L();  WriteClockHt1621();

   for(i = 0; i < 8; i++) {
   
	   if(Shift & FunctonCode) 	DATA_H(); 

	   else DATA_L();	  

	   WriteClockHt1621();

	   Shift = Shift >> 1;
   }
   DATA_L(); WriteClockHt1621();//发送一个 0 1621中最后一位 X
   CS_H(); Nop(10);		                    //CS 片选关  
   DATA_H(); Nop(10);
}
void WriteDateHt1621(u8 Addr,u8 Dat)
{
   u8 i; u8 Shift = 0x20; //屏蔽高3位 只用5位
   CS_L(); Nop(10);

   DATA_H();  WriteClockHt1621();  //101
   DATA_L();  WriteClockHt1621();
   DATA_H();  WriteClockHt1621();

   for( i = 0; i < 6; i++) {
   		 
		if (Addr & Shift) DATA_H(); 
		
		else  DATA_L();
		Nop(10);
		WriteClockHt1621();
		
		Shift = Shift >> 1; 
   }
   Shift = 0x01;

   for (i = 0; i < 4; i++) {

        if( Dat & Shift) DATA_H();
		 
   		else  DATA_L();
		Nop(10);
		WriteClockHt1621();

		Shift = Shift << 1;
   }
   
   CS_H();Nop(10);	                    //CS 片选关

   DATA_H(); Nop(10);
}
/*************************************************************************************/
void DisAll(u8 Dat)
{
     u8 i;
	 for(i = 0; i <= 34; i++) {
	 
	     WriteDateHt1621(i, Dat);
	 }
}
void DisSeg(void)
{
     u8 i,j;

	 for(i = 0; i <= 34; i++) {

	 	for(j = 0; j <= 0xff;) {

	     WriteDateHt1621(i, j); j <<= 1;  
		 
		 DelayLcd(0x54321);
		 }
	 }
}

void InitHT1621(void)
{
    GpioConfigurationHT1621();
    WriteCommandHt1621(OSC_ON);
    WriteCommandHt1621(DISP_ON);
    WriteCommandHt1621(COM_1_3__4);
 //   WriteCommandHt1621(BUZZ_ON);
//    WriteCommandHt1621(BUZZ_2KHZ);
}
