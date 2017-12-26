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

//��8*8�ַ�����,��ʾ���������������ʾ���ַ�����
#define LineChar 		8  //��8��
#define ColumnChar 	30  //�ܹ�16��

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

                       ָ����붨�� 

************************************************************/ 
#define   CursorPointer    	0x21          /* ����ַ���� */
#define   OffsetReg        	0x22          /* CGRAMƫ�Ƶ�ַ���� */
#define   AddrSet          	0x24          /* ��ʾ��ַ���� */
#define   TextHomeAddr      0x40          /* �ı��׵�ַ */
#define   TextArea         	0x41          /* �ı�������� */
#define   GraHomeAddr       0x42          /* ͼ���׵�ַ���� */
#define   GraArea          	0x43          /* ͼ�ο������ */
#define   OrMode           	0x80          /* ��ģʽ��ʾ */
#define   ExorMode         	0x81          /* ���ģʽ��ʾ */
#define   AndMode          	0x83          /* ��ģʽ��ʾ */
#define   TextAttMode      	0x84          /* �ı�����ģʽ */
#define   InterCGROM       	0             /* �ڲ�CGROM */
#define   ExCGRAM          	0x08          /* �ⲿCGRAM */
#define   DisplayOff       	0x90          /* ��ʾ�ر� */
#define   CursorOn         	0x92          /* �����ʾ��������˸ */
#define   LCM_CURSOR_BLINK  0x93          /*�����˸ */
#define   LCM_TEXT_ON       0x94          /*�ı�ģʽ�� */
#define   GraOn           	0x98          /*ͼ��ģʽ�� */
#define   TGAllOn          	0x9c          /*�ı�ͼ��ģʽ����*/
#define   DataAutoWrite     0xb0          /* �����Զ�д */
#define   DataAutoRead      0xb1          /* �����Զ���*/ 
#define   ExitAutoRW       	0xb2          /* �˳������Զ���дģʽ */
#define   LCM_DATA_ADDR_INC 0xc0          /* ����д����ַ��1 */
#define   LCM_DATA_ADDR_DEC 0xc2          /* ����д����ַ��1 */
#define   DataWAddrNV       0xc4          /* ����д����ַ���� */
#define   DataRAddrI      	0xc1          /* ���ݶ�����ַ��1 */
#define   DataRAddrD       	0xc3          /* ���ݶ�����ַ��1 */
#define   DataRAddrNV       0xc5          /* ���ݶ�����ַ���� */
#define   ScreenPeek       	0xe0          /* ���� */
#define   ScreenCopy       	0xe1          /* ������*/
#define   LCM_LINE_CHAR     4             /* one col = 4 * 16 = 64 dot */  
#define   LCM_COL_CHAR 			30		  /* one line 30 * 8  = 240 dot ���ÿ��8*8 (ÿ����ʾ30 ����Ϊ8�����ַ�*/ 		
//#define  LCM_COL_CHAR_LEFT    	16					/*�����������*/
//#define  LCM_COL_CHAR_RIGHT   (LCM_COL_CHAR - 16)	/*�ұ���������*/

typedef enum{

  LCM_DIS_LINE0,
  LCM_DIS_LINE1,
  LCM_DIS_LINE2,
  LCM_DIS_LINE3
  
} DisLineNum;

#define DISBUF_SIZE  (LCM_COL_CHAR*LCM_LINE_CHAR+1)

extern struct MenuItem *MenuPoint ; /*��ʼ����Ĭ����ʾMainMenu�˵�*/  
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

