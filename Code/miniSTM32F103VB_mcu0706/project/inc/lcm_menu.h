//file:menu.h  for lcm gui
#ifndef __MENU_H
#define __MENU_H

#include "stm32f10x_lib.h"
//#include "platform_config.h"
//#include "Functions.h" 
/**************************************************** 
* ֧�ֿ�˵�����ṩ��ʹ�ò˵��Ļ������ݽṹ          * 
* ���ߣ�      ɵ����                                * 
* ���ڣ�      2005��6��9��                          * 
****************************************************/ 
#define LCM_LINE0_LEFT    	00
#define LCM_LINE0_RIGHT  	01
#define LCM_LINE1_LEFT		10
#define LCM_LINE1_RIGHT		11
#define LCM_LINE2_LEFT		20
#define LCM_LINE2_RIGHT 	21
#define LCM_LINE3_LEFT		30
#define LCM_LINE3_RIGHT		31
/*X0---->********************************************X*
Y0*00-KEY_LEFT1		01-KEY_RIGHT1
Y1*10-KEY_LEFT2		11-KEY_RIGHT2
Y2*20-KEY_LEFT3		21-KEY_RIGHT3
Y3*30-KEY_LEFT4		31-KEY_RIGHT4
*****************************************************/
/********************** 
*    Ŀ¼�ṹ�嶨��   * 
**********************/ 
struct MenuItem{ 

    u8 MenuCount; 
    u8 *DisplayString; 
    u8 DisplayStringSize ;
    u8 PositionX;	/*���˵�������λ�ú� : �к� 0--15*/
    u8 PositionY ;	/*���˵�������λ�ú� : �к� 0--3*/
    u8 KeyVal;  	/*��Ӧ��ֵ*/
    void (*Subs)(void);						/*Subs Ҫʵ�ֵĹ���*/
    struct  MenuItem *ChildrenMenus;	/*ChildrenMenusΪ��һ��Ŀ¼�ĵ�ַ*/
    struct  MenuItem  *ParentMenus;		/*ParentMenusΪ�ϲ�Ŀ¼�ĵ�ַ*/
	
}; 

typedef struct _StringArray{
	u8 *Str;
	u8 StrSize;
}StringArray_t;

//extern struct MenuItem MenuItem  ;
extern struct MenuItem  Null_MenuItem ;

/**************************************************** 
*   ʹ��˵����                                      * 
*      Ҫ����һ���˵�����Ҫ�����¼�������           * 
*      1������һ���ṹ������                        * 
*      2���������˵����Ӳ˵�����ô���ϼ��˵���    * 
*         *ChildrenMenusָ��ָ���������׵�ַ,     * 
*         ��������ParentMenusΪ�ϲ�Ŀ¼�ĵ�ַ       * 
*      3���������˵��Ǹ��˵�����ôֱ�ӽ�MenuPoint * 
*         ָ��ָ���������׵�ַ                    * 
*      4��ͨ��дһ������Ϊ�������ÿһ��Ԫ�س�ʼ��  * 
*      5������˵���������ѡ���ô��*ChildrenMenus* 
*         ��ΪNULL��������ָ��*Subsָ��ʵ�ֹ��ܵ�   * 
*         ������                                    * 
****************************************************/ 
typedef enum{
	CHINESE,
	ENGLISH
}LanguageSel_t;

 extern struct MenuItem MainMenu[8];					 /*��Ŀ¼�� ���˵�*/

// MenuItem LoadMediumMenu[6];			/*��Ŀ¼--װ�ؽ��ʲ˵�*/
 //extern struct  MenuItem FeedMediumMenu21[3];			/*��Ŀ¼--���ͽ���*/
 //extern struct MenuItem PrintSetMenu22[7];	 			/*��Ŀ¼--��ӡ�����Ӳ˵�*/
 //extern struct MenuItem AssistantFunctionMenu23[5] ; 	 	/*��Ŀ¼--�������ܲ˵�*/
 										/*��Ŀ¼--����/��ͣ��ӡ*/
										/*��Ŀ¼--ȡ����ӡ*/
 //MenuItem CutMenu[1] ;					/*��Ŀ¼--�и�*/
 //extern struct  MenuItem SysInfoMenu27[4] ;				/*��Ŀ¼--����  info*/
//******�����˵�**********************************************************

// extern struct MenuItem LevelAdjustMenu2130[7]; 
// extern struct MenuItem PlumbAdjustMenu2131[7]; 
// extern struct MenuItem BidirectionAdjustMenu2132[7]; 
// extern struct MenuItem StepperAdjustMenu2133[7]; 
// extern struct MenuItem OpenAutoCutPeperMenu2134[7]; 
// extern struct MenuItem UserSetMenu2135[7]; 


/*********************** 
*     �� �� �� �� ��   * 
***********************/ 
#if 0
extern void NullSubs(void) ;
 extern void MainMenuInit(void);
 extern void FeedMediumMenuInit( void );
 extern void PrintSetMenuInit(void) ;
 extern void SysInfoMenuInit( void );
 #endif
 extern void NullSubs(void) ;
 extern void MenuInit( LanguageSel_t  langval );

#endif // __MENU_H


