#include "stm32f10x.h"
#include "SPFD5408.H"

void SPFD5408_WriteData(u16 data)
{
	Set_Rs;
	Set_nRd;
  	GPIOB->ODR = data;
	Clr_nWr;
	Set_nWr;
}
__inline void SPFD5408_WriteIndex(u16 idx)
{
    Clr_Rs;
	Set_nRd;
	GPIOB->ODR = idx;
	Clr_nWr;
	Set_nWr;
}

__inline void SPFD5408_WriteRegister(u16 index,u16 dat)
{
 /************************************************************************
  **                                                                    **
  ** nCS       ----\__________________________________________/-------  **
  ** RS        ------\____________/-----------------------------------  **
  ** nRD       -------------------------------------------------------  **
  ** nWR       --------\_______/--------\_____/-----------------------  **
  ** DB[0:15]  ---------[index]----------[data]-----------------------  **
  **                                                                    **
  ************************************************************************/
    Clr_Cs;
	SPFD5408_WriteIndex(index);      
	SPFD5408_WriteData(dat);    
	Set_Cs; 
}
__inline void SPFD5408_SetCursor(u16 x,u16 y)
{
	  	SPFD5408_WriteRegister(0x0020,y); // 行
  		SPFD5408_WriteRegister(0x0021,0x13f-x); // 列
}

void SPFD5408_Clear(u16 dat)
{
  u32  i;

  SPFD5408_SetCursor(0x0000, 0x0000);  
  Clr_Cs; 
  SPFD5408_WriteIndex(0x0022);    
  for(i=0;i<76800;i++)
  {
    SPFD5408_WriteData(dat);
  }
  Set_Cs;
}
void ConfigurationLCD(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 第1步：打开 RCC_APB2Periph_AFIO 的时钟	*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE); //JTAG 不使能 重映射为普通IO口(B口) 
	/*开启相应时钟 */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);
	 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	GPIOB ->ODR = 0XFFFF; 

		/*控制脚*/
    								 // CS         IOR        IOW         CMD/RS	 INT0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/*所有Lcd引脚配置为推挽输出*/
	/*16位数据低8位*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;//GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*16位数据高8位*/


}
void Init_SPFD5408(void)
{  	u16 i; 
     ConfigurationLCD(); 

  	   SPFD5408_WriteRegister(0x0000,0x0000); 
      SPFD5408_WriteRegister(0x0001,0x0100);     
       SPFD5408_WriteRegister(0x0002,0x0700);             //power on sequence                      
       SPFD5408_WriteRegister(0x0003,0x1020 );    //65K        (1<<12)|(1<<5)|(1<<4)
        SPFD5408_WriteRegister(0x0004,0x0000);                                   
        SPFD5408_WriteRegister(0x0008,0x0202);              
        SPFD5408_WriteRegister(0x0009,0x0000);         
        SPFD5408_WriteRegister(0x000a,0x0000);             //display setting          
       SPFD5408_WriteRegister(0x000c,0x0000);            //display setting           
       SPFD5408_WriteRegister(0x000d,0x0000);             //0f3c          
       SPFD5408_WriteRegister(0x000f,0x0000);
      SPFD5408_WriteRegister(0x0007,0x0000);
        //Power On sequence //
       SPFD5408_WriteRegister(0x0010,0x12b0);   
       SPFD5408_WriteRegister(0x0011,0x0007);
       SPFD5408_WriteRegister(0x0012,0x01bb);                                                                  
       SPFD5408_WriteRegister(0x0013,0x1c00);
      SPFD5408_WriteRegister(0x0017,0x0001); 

        SPFD5408_WriteRegister(0x0029,0x0009);
        SPFD5408_WriteRegister(0x002a,0x0009);
      SPFD5408_WriteRegister(0x00a4,0x0000);
        
      SPFD5408_WriteRegister(0x0050,0x0000);                                                             
       SPFD5408_WriteRegister(0x0051,0x00ef);           
       SPFD5408_WriteRegister(0x0052,0x0000);   
      SPFD5408_WriteRegister(0x0053,0x013f);
        SPFD5408_WriteRegister(0x0060,0x2700);
        SPFD5408_WriteRegister(0x0061,0x0001); 
        SPFD5408_WriteRegister(0x006a,0x0000);

       SPFD5408_WriteRegister(0x0080,0x0000);
       SPFD5408_WriteRegister(0x0081,0x0000);
       SPFD5408_WriteRegister(0x0082,0x0000);
       SPFD5408_WriteRegister(0x0083,0x0000);
       SPFD5408_WriteRegister(0x0084,0x0000);
        SPFD5408_WriteRegister(0x0085,0x0000);

        SPFD5408_WriteRegister(0x0090,0x0010);     
        SPFD5408_WriteRegister(0x0092,0x0000);  
        SPFD5408_WriteRegister(0x0093,0x0003);
        SPFD5408_WriteRegister(0x0095,0x0110);
      SPFD5408_WriteRegister(0x0097,0x0000);    
      SPFD5408_WriteRegister(0x0098,0x0000);
       SPFD5408_WriteRegister(0x0007,0x0173);   
      
    // SPFD5408_WriteIndex(0x0022); 
     SPFD5408_WriteRegister(0x0020,0x0000);
        SPFD5408_WriteRegister(0x0021,0x0000);
   for(i=50000;i>0;i--);
  SPFD5408_Clear(0x00f8);
  SPFD5408_Clear(0xf800); while(1);

}
