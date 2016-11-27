/*硬件相关的宏定义*/
/********************************************************************************/
#define Set_Cs  GPIO_SetBits(GPIOC,GPIO_Pin_4);//GPIOC->BSRR  = 0x00000010;
#define Clr_Cs  GPIO_ResetBits(GPIOC,GPIO_Pin_4);//GPIOC->BRR   = 0x00000010;

#define Set_Rs  GPIO_SetBits(GPIOA,GPIO_Pin_3);	//GPIOC->BSRR  = 0x00002000;
#define Clr_Rs  GPIO_ResetBits(GPIOA,GPIO_Pin_3);//GPIOC->BRR   = 0x00002000;

#define Set_nWr GPIO_SetBits(GPIOC,GPIO_Pin_7);	//GPIOC->BSRR  = 0x00004000;
#define Clr_nWr GPIO_ResetBits(GPIOC,GPIO_Pin_7);//GPIOC->BRR   = 0x00004000;

#define Set_nRd GPIO_SetBits(GPIOC,GPIO_Pin_6);	//GPIOC->BSRR  = 0x00008000;
#define Clr_nRd GPIO_ResetBits(GPIOC,GPIO_Pin_6);//GPIOC->BRR   = 0x00008000;
/********************************************************************************/


/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0
