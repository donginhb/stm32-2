//file:menu.h  for lcm gui
#ifndef __MENU_H
#define __MENU_H

#include "stm32f10x_lib.h"
//#include "platform_config.h"
//#include "Functions.h" 
/**************************************************** 
* 支持库说明：提供了使用菜单的基本数据结构          * 
* 作者：      傻孩子                                * 
* 日期：      2005年6月9日                          * 
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
*    目录结构体定义   * 
**********************/ 
struct MenuItem{ 

    u8 MenuCount; 
    u8 *DisplayString; 
    u8 DisplayStringSize ;
    u8 PositionX;	/*本菜单的所处位置号 : 行号 0--15*/
    u8 PositionY ;	/*本菜单的所处位置号 : 列号 0--3*/
    u8 KeyVal;  	/*对应键值*/
    void (*Subs)(void);						/*Subs 要实现的功能*/
    struct  MenuItem *ChildrenMenus;	/*ChildrenMenus为下一级目录的地址*/
    struct  MenuItem  *ParentMenus;		/*ParentMenus为上层目录的地址*/
	
}; 

typedef struct _StringArray{
	u8 *Str;
	u8 StrSize;
}StringArray_t;

//extern struct MenuItem MenuItem  ;
extern struct MenuItem  Null_MenuItem ;

/**************************************************** 
*   使用说明：                                      * 
*      要定义一个菜单，需要做以下几步工作           * 
*      1、定义一个结构体数组                        * 
*      2、如果这个菜单是子菜单，那么把上级菜单的    * 
*         *ChildrenMenus指针指向该数组的首地址,     * 
*         并且设置ParentMenus为上层目录的地址       * 
*      3、如果这个菜单是跟菜单，那么直接将MenuPoint * 
*         指针指向该数组的首地址                    * 
*      4、通过写一个函数为该数组的每一个元素初始化  * 
*      5、如果菜单项是最终选项，那么将*ChildrenMenus* 
*         置为NULL，将函数指针*Subs指向实现功能的   * 
*         函数。                                    * 
****************************************************/ 
typedef enum{
	CHINESE,
	ENGLISH
}LanguageSel_t;

 extern struct MenuItem MainMenu[8];					 /*根目录， 主菜单*/

// MenuItem LoadMediumMenu[6];			/*根目录--装载介质菜单*/
 //extern struct  MenuItem FeedMediumMenu21[3];			/*根目录--馈送介质*/
 //extern struct MenuItem PrintSetMenu22[7];	 			/*根目录--打印设置子菜单*/
 //extern struct MenuItem AssistantFunctionMenu23[5] ; 	 	/*根目录--辅助功能菜单*/
 										/*根目录--继续/暂停打印*/
										/*根目录--取消打印*/
 //MenuItem CutMenu[1] ;					/*根目录--切割*/
 //extern struct  MenuItem SysInfoMenu27[4] ;				/*根目录--关于  info*/
//******三级菜单**********************************************************

// extern struct MenuItem LevelAdjustMenu2130[7]; 
// extern struct MenuItem PlumbAdjustMenu2131[7]; 
// extern struct MenuItem BidirectionAdjustMenu2132[7]; 
// extern struct MenuItem StepperAdjustMenu2133[7]; 
// extern struct MenuItem OpenAutoCutPeperMenu2134[7]; 
// extern struct MenuItem UserSetMenu2135[7]; 


/*********************** 
*     函 数 声 明 区   * 
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


