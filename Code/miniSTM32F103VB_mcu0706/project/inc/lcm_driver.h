//file:lcm.h  240*64 dot  lcm driver  for lcm gui
#ifndef __LCM_H
#define __LCM_H

#include "includes.h"

#define StrNull  ' '

extern u8 * WordToChar(u16 value);
extern u8 * DWordToChar(u32 value);
extern void LF_GPIO_WriteLow8Bit(GPIO_TypeDef* GPIOx, u8 data);

extern void Init_LFGpio( void );
extern void LF_DataBusForFPGA( );
#if LCM_GUI_EN>0

//以8*8字符计算,显示屏横向、纵向可以显示的字符个数
#define LineChar 		8  //共8行
#define ColumnChar 	30  //总共16列

#define LCM_DATA_IN_MODE    0   /*LCD --> STM32f*/
#define LCM_DATA_OUT_MODE  1  /*LCD <-- STM32f*/

#define GPIO_IN_MODE   	0
#define GPIO_OUT_MODE 	1

//*LCM CMD*************************
#define LCM_CMD_TEXT_HOME_ADDR  		0x40  
#define LCM_CMD_TEXT_AREA  			0x41  
#define LCM_CMD_GRAPHIC_HOME_ADDR  	0x42  
#define LCM_CMD_GRAPHIC_AREA			0x43 

/************************************************************ 

                       指令代码定义 

************************************************************/ 
#define   CursorPointer    	0x21          /* 光标地址设置 */
#define   OffsetReg        	0x22          /* CGRAM偏移地址设置 */
#define   AddrSet          	0x24          /* 显示地址设置 */
#define   TextHomeAddr      0x40          /* 文本首地址 */
#define   TextArea         	0x41          /* 文本宽度设置 */
#define   GraHomeAddr       0x42          /* 图形首地址设置 */
#define   GraArea          	0x43          /* 图形宽度设置 */
#define   OrMode           	0x80          /* 或模式显示 */
#define   ExorMode         	0x81          /* 异或模式显示 */
#define   AndMode          	0x83          /* 与模式显示 */
#define   TextAttMode      	0x84          /* 文本属性模式 */
#define   InterCGROM       	0             /* 内部CGROM */
#define   ExCGRAM          	0x08          /* 外部CGRAM */
#define   DisplayOff       	0x90          /* 显示关闭 */
#define   CursorOn         	0x92          /* 光标显示，但不闪烁 */
#define   LCM_CURSOR_BLINK  0x93          /*光标闪烁 */
#define   LCM_TEXT_ON       0x94          /*文本模式打开 */
#define   GraOn           	0x98          /*图形模式打开 */
#define   TGAllOn          	0x9c          /*文本图形模式都打开*/
#define   DataAutoWrite     0xb0          /* 数据自动写 */
#define   DataAutoRead      0xb1          /* 数据自动读*/ 
#define   ExitAutoRW       	0xb2          /* 退出数据自动读写模式 */
#define   LCM_DATA_ADDR_INC 0xc0          /* 数据写，地址加1 */
#define   LCM_DATA_ADDR_DEC 0xc2          /* 数据写，地址减1 */
#define   DataWAddrNV       0xc4          /* 数据写，地址不变 */
#define   DataRAddrI      	0xc1          /* 数据读，地址加1 */
#define   DataRAddrD       	0xc3          /* 数据读，地址减1 */
#define   DataRAddrNV       0xc5          /* 数据读，地址不变 */
#define   ScreenPeek       	0xe0          /* 屏读 */
#define   ScreenCopy       	0xe1          /* 屏拷贝*/
#define   LCM_LINE_CHAR     4             /* one col = 4 * 16 = 64 dot */  
#define   LCM_COL_CHAR 			30		  /* one line 30 * 8  = 240 dot 设置宽度8*8 (每行显示30 个宽为8个点字符*/ 		
//#define  LCM_COL_CHAR_LEFT    	16					/*左边屏缓冲区*/
//#define  LCM_COL_CHAR_RIGHT   (LCM_COL_CHAR - 16)	/*右边屏缓冲区*/

typedef enum{

  LCM_DIS_LINE0,
  LCM_DIS_LINE1,
  LCM_DIS_LINE2,
  LCM_DIS_LINE3
  
} DisLineNum;

#define DISBUF_SIZE  (LCM_COL_CHAR*LCM_LINE_CHAR+1)

extern struct MenuItem *MenuPoint ; /*初始化，默认显示MainMenu菜单*/  
extern u8 DisBuf[DISBUF_SIZE];
extern void LCM_ShowMenu( struct  MenuItem *MI  ,u8 * dbuf  );
extern void LCM_DisplayFullScreen(u8 * buf );

extern void Init_LCMGpio( void ) ;
extern void Init_LCM( void );
extern void Init_LCMGUI( void );

#ifdef LCM_DUG
extern void LCM_test(void);
#endif //#ifdef LCM_DUG

#endif //#if LCM_GUI_EN>0
#endif // __LCM_H

