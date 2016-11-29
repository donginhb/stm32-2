//file: menu.c

#include "includes.h"

#if LCM_GUI_EN>0

struct MenuItem  Null_MenuItem ;
/****************************************************
#########根目录， 主菜单*界面########
*装载介质				   馈送介质
*打印设置			辅助功能菜单
*继续/暂停打印		    取消打印
*切割								关于
*########################################
****************************************************/
struct MenuItem MainMenu[8];					 /*根目录， 主菜单*/
/*-------------------------------------------------------------------------------*/
//*****二级菜单*************************************************************
// MenuItem LoadMediumMenu[6];				/*根目录--装载介质菜单*/
/************************************************************
*######根目录--> 馈送介质子菜单*界面#######
*前进											后退
*
*
*												退出	
*##############################################
*************************************************************/
#define MENU_COUNT_FM 		3
struct  MenuItem FeedMediumMenu21[MENU_COUNT_FM];		/*根目录--馈送介质*/
/**************************************************************
#########根目录--> 打印设置子菜单*界面#######
*水平校准菜单				垂直校准菜单
*双向校准菜单				步进校准菜单
*打开自动切纸				     使用者设置
*										       退出	
*################################################
***************************************************************/
#define MENU_COUNT_PS   	7
struct  MenuItem PrintSetMenu22[MENU_COUNT_PS];	 		/*根目录--打印设置子菜单*/

/*#########根目录--> 辅助功能菜单*界面########
*清洗									取墨水匣
*打印测试页菜单						    抽墨

*											    退出	
*#################################################*/
#define MENU_COUNT_AF 		6
struct  MenuItem AssistantFunctionMenu23[MENU_COUNT_AF] ; 	/*根目录--辅助功能菜单*/
 											/*根目录--继续/暂停打印*/
											/*根目录--取消打印*/
 //MenuItem CutMenu[1] ;						/*根目录--切割*/
struct MenuItem SysInfoMenu27[4] ;			/*根目录--关于  info*/

//******三级菜单**********************************************************
#define  MENU_COUNT_LA     7
struct MenuItem LevelAdjustMenu2130[MENU_COUNT_LA]; 
struct MenuItem PlumbAdjustMenu2131[7]; 
struct MenuItem BidirectionAdjustMenu2132[7]; 
struct MenuItem StepperAdjustMenu2133[7]; 
//struct MenuItem OpenAutoCutPeperMenu2134[7]; 
/******************************************
*计量单位选择          	语言
*
*
*                      				退出
******************************************/
#define MENU_COUNT_US  3
struct MenuItem UserSetMenu2135[MENU_COUNT_US]; 
/******************************************
*中文          				 英文
*
*
*                      				 退出
******************************************/
#define MENU_COUNT_YY  3
struct MenuItem LanguageMenu213541[ MENU_COUNT_YY ]; 
/******************************************
*毫米          				英寸
*
*
*                      				 退出
******************************************/
#define MENU_COUNT_UN   3
struct MenuItem UnitMenu213540[MENU_COUNT_UN];

struct MenuItem AdjustMenu213040[5];
/*****************************************************************************
********打印测试页菜单************************************************
*打印喷嘴检测			综合测试页
*托架检测一			托架检测二
*托架检测三
*									  退出
*****************************************************************************/
#define MENU_COUNT_PTP 	 			6
struct MenuItem PrintTestPageMenu2230[MENU_COUNT_PTP];
#define MENU_COUNT_LAC       7
struct MenuItem LevelAdjustCyanMenu213040[MENU_COUNT_LAC];
//-------------------------------------------------------------------------
//struct MenuItem ClearIngMenu2330[5];
static LanguageSel_t LanguageVal  = CHINESE;/*当前语言设定值*/
//

void MenuMainInit(  LanguageSel_t  langval );
//*****二级菜单***********************************************************
void MenuFeedMedium21Init( LanguageSel_t  langval );
void MenuPrintSet22Init( LanguageSel_t  langval );
void MenuSysInfo27Init( LanguageSel_t  langval );
void MenuAssistantFunction23Init( LanguageSel_t  langval );
//******三级菜单**********************************************************
void MenuLevelAdjust2130Init( LanguageSel_t  langval );
void MenuPlumbAdjust2131Init( LanguageSel_t  langval );
void MenuBidirectionAdjust2132Init( LanguageSel_t  langval );
void MenuStepperAdjust2133Init( LanguageSel_t  langval );
//void OpenAutoCutPeperMenu2134Init( void );
void MenuUserSet2135Init( LanguageSel_t  langval );

void MenuPrintTestPage2230Init( LanguageSel_t  langval );
void MenuLevelAdjustCyan213040Init( LanguageSel_t  langval );
void MenuLanguage213541Init( LanguageSel_t  langval );

void MenuChangEnToCh(void);
void MenuChangChToEn(void);

void MenuUnit213540Init( LanguageSel_t  langval );
/*----------------------------------------------
*空函数
*----------------------------------------------*/
void NullSubs(void) 
{ 
	return ;
} 
#if 0
void LoadMediumMenuInit( void )
{

	MenuItem *m  = &LoadMediumMenu[0];

	m->MenuCount = 1; 
	m->DisplayString = ; 
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = MainMenu; 
	
	
}
#endif
/************************************************************
*######根目录--> 馈送介质子菜单*界面#######
*前进											后退
*
*
*												退出	
*##############################################
*************************************************************/
void MenuFeedMedium21Init( LanguageSel_t  langval )
{

	struct  MenuItem *m  = &FeedMediumMenu21[0];
	struct MenuItem *tParentMenus = MainMenu ;	
	u8 tMenuCount = MENU_COUNT_FM;
		
	StringArray_t Str[MENU_COUNT_FM];
	StringArray_t *tStr = Str ;
	u8 Index = 0;
	LanguageSel_t tlangval = langval ;
	
	if( tlangval == CHINESE )
	{
		//----------------line 0--------------------
		Str[Index].Str = "前进"; 
		Str[Index++].StrSize = sizeof( "前进" );	
		Str[Index].Str = "后退"; 
		Str[Index++].StrSize = sizeof( "后退");	
		//----------------line 3--------------------
		Str[Index].Str = "退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 
	}
	else
	{
		//----------------line 0--------------------
		Str[Index].Str = "Forward"; 
		Str[Index++].StrSize = sizeof( "Forward" );	
		Str[Index].Str = "Backward"; 
		Str[Index++].StrSize = sizeof( "Backward");	
		//----------------line 3--------------------
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 
	}
	//----------------line 0--------------------
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	#if 	STEPPER_EN>0
	m->Subs = API_StepperForward ; 
	#else
	m->Subs = NullSubs; 
	#endif
	m->ChildrenMenus = &Null_MenuItem ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	#if 	STEPPER_EN>0
	m->Subs = API_StepperBackward ; 
	#else
	m->Subs = NullSubs; 
	#endif
	m->ChildrenMenus = &Null_MenuItem ; 
	m->ParentMenus = tParentMenus; 
	
	m++;
	tStr++;
	//----------------line 3--------------------
	//R3
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 

}

/**************************************************************
#########根目录--> 打印设置子菜单*界面#######
*水平校准菜单				垂直校准菜单
*双向校准菜单				步进校准菜单
*打开自动切纸				     使用者设置
*										       退出	
*################################################
***************************************************************/
/************************************************************** 
*  函数说明：打印设置子菜单                            		 * 
**************************************************************/ 
void MenuPrintSet22Init( LanguageSel_t  langval )
{ 
	
	struct MenuItem *m  = &PrintSetMenu22[0];
	struct MenuItem *tParentMenus = MainMenu ;	
	 u8 tMenuCount = MENU_COUNT_PS;		
	StringArray_t Str[MENU_COUNT_PS];
	StringArray_t *tStr = Str ;
	u8 Index = 0;  

	LanguageSel_t tlangval = langval ;
	
	if( tlangval == CHINESE )
	{
		//----------------line 0--------------------
		Str[Index].Str = "水平校准菜单"; 
		Str[Index++].StrSize = sizeof( "水平校准菜单");	
		Str[Index].Str = "垂直校准菜单"; 
		Str[Index++].StrSize = sizeof( "垂直校准菜单");	
		//----------------line 1--------------------
		Str[Index].Str = "双向校准菜单";
		Str[Index++].StrSize = sizeof( "双向校准菜单");
		Str[Index].Str =  "步进校准菜单"; 
		Str[Index++].StrSize = sizeof( "步进校准菜单" );
		//----------------line 2--------------------
		Str[Index].Str =  "打开自动切纸"; 
		Str[Index++].StrSize = sizeof( "打开自动切纸" );	
		Str[Index].Str =  "使用者设置"; 
		Str[Index++].StrSize = sizeof( "使用者设置" );
		//----------------line 3--------------------
		Str[Index].Str = "退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 
	}
	else
	{
		//----------------line 0--------------------
		Str[Index].Str = "LevelAdjMenu"; 
		Str[Index++].StrSize = sizeof( "LevelAdjMenu");	
		Str[Index].Str = "PlumbAdjMenu"; 
		Str[Index++].StrSize = sizeof( "PlumbAdjMenu");	
		//----------------line 1--------------------
		Str[Index].Str = "BidirAdjMenu";
		Str[Index++].StrSize = sizeof( "BidirAdjMenu");
		Str[Index].Str =  "StepperAdjMenu"; 
		Str[Index++].StrSize = sizeof( "StepperAdjMenu" );
		//----------------line 2--------------------
		Str[Index].Str =  "OpenAutoCut"; 
		Str[Index++].StrSize = sizeof( "OpenAutoCut" );	
		Str[Index].Str =  "UserSet"; 
		Str[Index++].StrSize = sizeof( "UserSet" );
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 
	}
	//----------------line 0--------------------
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = LevelAdjustMenu2130 ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = PlumbAdjustMenu2131; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//----------------line 1--------------------
	//L1
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = BidirectionAdjustMenu2132; 
	m->ParentMenus = tParentMenus; 
   
	m++;
	tStr++;
	//R1
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//----------------line 2--------------------
	//L2
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
	
	m++;
	tStr++;
	//R2
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = UserSetMenu2135; 
	m->ParentMenus = tParentMenus; 
	
	m++;
	tStr++;
	//----------------line 3--------------------
	//R3
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 
	   
} 
/*###根目录--> 辅助功能菜单--> 服务菜单######
*校准菜单					诊断菜单 	       	   
*墨水匣信息				 测试打印
*						     			     
*									   退出
################################################*/
#define MENU_COUNT_SM   			 5
struct MenuItem SeverMenu2336[MENU_COUNT_SM];
void MenuServer2336Init( LanguageSel_t  langval )
{
	
	struct MenuItem *m  = &SeverMenu2336[0];
	struct MenuItem *tParentMenus = AssistantFunctionMenu23 ;	
	
	u8 tMenuCount = MENU_COUNT_SM;
		
	StringArray_t  Str[MENU_COUNT_SM];
	StringArray_t  *tStr = Str ;
	u8 Index = 0;
	LanguageSel_t tlangval = langval ;
	
	if( tlangval == CHINESE )
	{
		//-------------line0--------------------------------
		Str[Index].Str = "校准菜单"; 
		Str[Index++].StrSize = sizeof( "校准菜单");
		Str[Index].Str = "诊断菜单"; 
		Str[Index++].StrSize = sizeof( "诊断菜单");
		//-------------line1--------------------------------
		Str[Index].Str = "墨水匣信息";
		Str[Index++].StrSize = sizeof( "墨水匣信息");
		Str[Index].Str =  "测试打印"; 
		Str[Index++].StrSize = sizeof(  "测试打印" );	
		//-------------line2--------------------------------	
		//-------------line3--------------------------------
		Str[Index].Str ="退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 		
	}
	else
	{
		//-------------line0--------------------------------
		Str[Index].Str = "Calibration Menu";
		Str[Index++].StrSize = sizeof( "Calibration Menu");
		Str[Index].Str = "Diagnostics Menu"; 
		Str[Index++].StrSize = sizeof( "Diagnostics Menu");
		//-------------line1--------------------------------
		Str[Index].Str = "Cartridge Info";
		Str[Index++].StrSize = sizeof( "Cartridge Info");
		Str[Index].Str =  "Test Print "; 
		Str[Index++].StrSize = sizeof(  "Test Print ");	
		//-------------line2--------------------------------			
		//-------------line3--------------------------------
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 
	}
	//-------------line0----------------------------
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//-------------line1-----------------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = PrintTestPageMenu2230; 
	m->ParentMenus = tParentMenus; 
   
	m++;
	tStr++;
	
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//-------------line2------------------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 
	
}



/*#########根目录--> 辅助功能菜单*界面########
*清洗									取墨水匣
*打印测试页菜单						    抽墨
*服务菜单
*											    退出	
*#################################################*/
void MenuAssistantFunction23Init( LanguageSel_t  langval )
{
	
	struct MenuItem *m  = &AssistantFunctionMenu23[0];
	struct MenuItem *tParentMenus = MainMenu ;	
	
	u8 tMenuCount = MENU_COUNT_AF;
		
	StringArray_t Str[MENU_COUNT_AF];
	StringArray_t *tStr = Str ;
	u8 Index = 0;
	LanguageSel_t tlangval = langval ;
	
	if( tlangval == CHINESE )
	{
		//-------------line0--------------------------------
		Str[Index].Str = "清洗"; 
		Str[Index++].StrSize = sizeof( "清洗");
		Str[Index].Str = "存取墨水匣"; 
		Str[Index++].StrSize = sizeof( "存取墨水匣");
		//-------------line1--------------------------------
		Str[Index].Str = "打印测试页菜单";
		Str[Index++].StrSize = sizeof( "打印测试页菜单");
		Str[Index].Str =  "抽墨"; 
		Str[Index++].StrSize = sizeof(  "抽墨" );	
		//-------------line2--------------------------------
		Str[Index].Str =  "服务菜单"; 
		Str[Index++].StrSize = sizeof(  "服务菜单" );
		//-------------line3--------------------------------
		Str[Index].Str ="退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 		
	}
	else
	{
		//-------------line0--------------------------------
		Str[Index].Str = "Clear";
		Str[Index++].StrSize = sizeof( "Clear");
		Str[Index].Str = "存取墨水匣"; 
		Str[Index++].StrSize = sizeof( "存取墨水匣");
		//-------------line1--------------------------------
		Str[Index].Str = "PrintTestMenu";
		Str[Index++].StrSize = sizeof( "PrintTestMenu");
		Str[Index].Str =  "InkPumping "; 
		Str[Index++].StrSize = sizeof(  "InkPumping " );	
		//-------------line2--------------------------------			
		Str[Index].Str =  "ServerMenu"; 
		Str[Index++].StrSize = sizeof(  "ServerMenu" );
		//-------------line3--------------------------------
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 
	}
	//-------------line0----------------------------
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//-------------line1-----------------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = PrintTestPageMenu2230; 
	m->ParentMenus = tParentMenus; 
   
	m++;
	tStr++;
	
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//-------------line2------------------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 
	
}
/*******************************************
********打印测试页菜单**************
*打印喷嘴检测			综合测试页
*托架检测一			托架检测二
*托架检测三
*				退出
********************************************/
/*******************************************
*说明: 暂无下一级菜单
*******************************************/
void MenuPrintTestPage2230Init( LanguageSel_t  langval )
{
	
	struct MenuItem *m  = &PrintTestPageMenu2230[0];
	struct MenuItem *tParentMenus = AssistantFunctionMenu23 ;	
	u8 tMenuCount = MENU_COUNT_PTP;
	
	StringArray_t Str[MENU_COUNT_PTP];
	StringArray_t *tStr = Str ;
	u8 Index = 0;
	LanguageSel_t tlangval = langval ;
	
	if( tlangval == CHINESE )
	{
		//-------------line 0 -------------------------
		Str[Index].Str = "打印喷嘴检测"; 
		Str[Index++].StrSize = sizeof( "打印喷嘴检测");
		Str[Index].Str = "综合测试页"; 
		Str[Index++].StrSize = sizeof( "综合测试页");
		//-------------line 1 -------------------------
		Str[Index].Str = "托架检测一";
		Str[Index++].StrSize = sizeof( "托架检测一");
		Str[Index].Str =  "托架检测二"; 
		Str[Index++].StrSize = sizeof(  "托架检测二" );	
		//-------------line 2 -------------------------
		Str[Index].Str =  "托架检测三"; 
		Str[Index++].StrSize = sizeof(  "托架检测三" );	
		//-------------line 3 -------------------------
		Str[Index].Str ="退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 
	}
	else
	{
		//-------------line 0 -------------------------
		Str[Index].Str = "打印喷嘴检测"; 
		Str[Index++].StrSize = sizeof( "打印喷嘴检测");
		Str[Index].Str = "综合测试页"; 
		Str[Index++].StrSize = sizeof( "综合测试页");
		//-------------line 1 -------------------------
		Str[Index].Str = "托架检测一";
		Str[Index++].StrSize = sizeof( "托架检测一");
		Str[Index].Str =  "托架检测二"; 
		Str[Index++].StrSize = sizeof(  "托架检测二" );	
		//-------------line 2 -------------------------
		Str[Index].Str =  "托架检测三"; 
		Str[Index++].StrSize = sizeof(  "托架检测三" );	
		//-------------line 3 -------------------------
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 
	}
	//-------------line 0 -------------------------
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//-------------line 1 -------------------------
	//L1
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
   
	m++;
	tStr++;
	//R1
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//-------------line 2 -------------------------
	//L2
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
	
	m++;
	tStr++;
	//-------------line 3 -------------------------
	//R3
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 
	
}

 /*********根目录--> 打印设置子菜单*********
***********垂直校准菜单 *界面*****************
*青色水平校准			品红水平校准
*黄色水平校准			浅清水平校准
*浅品水平校准			
*校准打印测试						退出		
*****************************************************/
void MenuLevelAdjust2130Init( LanguageSel_t  langval )
{	
	struct MenuItem *m  = &LevelAdjustMenu2130[0];
	struct MenuItem *tParentMenus = PrintSetMenu22 ;	
	 u8 tMenuCount = MENU_COUNT_LA;		
	StringArray_t Str[MENU_COUNT_LA];
	StringArray_t *tStr = Str ;
	u8 Index = 0;  

	LanguageSel_t tlangval = langval ;
	
	if( tlangval == CHINESE )
	{
		//----------------line 0--------------------
		Str[Index].Str = "青色水平校准"; 
		Str[Index++].StrSize = sizeof( "青色水平校准");	
		Str[Index].Str = "品红水平校准"; 
		Str[Index++].StrSize = sizeof( "品红水平校准");	
		//----------------line 1--------------------
		Str[Index].Str = "黄色水平校准";
		Str[Index++].StrSize = sizeof( "黄色水平校准");
		Str[Index].Str =  "浅清水平校准"; 
		Str[Index++].StrSize = sizeof( "浅清水平校准");
		//----------------line 2--------------------
		Str[Index].Str =  "浅品水平校准"; 
		Str[Index++].StrSize = sizeof( "浅品水平校准" );	
		Str[Index].Str =  "校准打印测试"; 
		Str[Index++].StrSize = sizeof( "校准打印测试" );
		//----------------line 3--------------------
		Str[Index].Str = "退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 
	}
	else
	{
		//----------------line 0--------------------
		Str[Index].Str = "YLevelAdj"; 
		Str[Index++].StrSize = sizeof( "YLevelAdj");	
		Str[Index].Str = "MLevelAdj"; 
		Str[Index++].StrSize = sizeof( "MLevelAdj");	
		//----------------line 1--------------------
		Str[Index].Str = "CLevelAdj";
		Str[Index++].StrSize = sizeof( "CLevelAdj");
		Str[Index].Str =  "LCLevelAdj"; 
		Str[Index++].StrSize = sizeof( "LCLevelAdj" );
		//----------------line 2--------------------
		Str[Index].Str =  "LMLevelAdj"; 
		Str[Index++].StrSize = sizeof( "LMLevelAdj" );	
		Str[Index].Str =  "AdjPrintTest"; 
		Str[Index++].StrSize = sizeof( "AdjPrintTest" );
		//---------------line 3----------------------
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 
	}
	//----------------line 0--------------------
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = LevelAdjustCyanMenu213040; 
	m->ParentMenus = tParentMenus; 
	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//----------------line1--------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
   
	m++;
	tStr++;
	
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;	
	//----------------line 2--------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
		
	m++;
	tStr++;
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX =  LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus;

	m++;
	tStr++;
	//----------------line 3--------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 
	
}
 /*######根目录--> 打印设置子菜单*********
***********垂直校准菜单 *界面############
*青色垂直校准			品红垂直校准
*黄色垂直校准			浅清垂直校准
*浅品垂直校准			
*校准打印测试			退出		
*########################################*/
#define MENU_COUNT_PA 7
void MenuPlumbAdjust2131Init( LanguageSel_t  langval )
{
	struct MenuItem *m  = &PlumbAdjustMenu2131[0];
	struct MenuItem *tParentMenus =PrintSetMenu22;
	u8 tMenuCount = MENU_COUNT_PA;		
	StringArray_t Str[MENU_COUNT_PA];
	StringArray_t *tStr = Str ;
	u8 Index = 0;  

	LanguageSel_t tlangval = langval ;
	
	if( tlangval == CHINESE )
	{
		//----------------line 0--------------------
		Str[Index].Str = "青色垂直校准"; 
		Str[Index++].StrSize = sizeof( "青色垂直校准");	
		Str[Index].Str = "品红垂直校准"; 
		Str[Index++].StrSize = sizeof( "品红垂直校准");	
		//----------------line 1--------------------
		Str[Index].Str = "黄色垂直校准";
		Str[Index++].StrSize = sizeof( "黄色垂直校准");
		Str[Index].Str =  "浅清垂直校准"; 
		Str[Index++].StrSize = sizeof( "浅清垂直校准");
		//----------------line 2--------------------
		Str[Index].Str =  "浅品垂直校准"; 
		Str[Index++].StrSize = sizeof( "浅品垂直校准" );	
		Str[Index].Str =  "校准打印测试"; 
		Str[Index++].StrSize = sizeof( "校准打印测试" );
		//----------------line 3--------------------
		Str[Index].Str = "退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 
	}
	else
	{
		//----------------line 0--------------------
		Str[Index].Str = "YPlumbAdj"; 
		Str[Index++].StrSize = sizeof( "YPlumbAdj");	
		Str[Index].Str = "MPlumbAdj"; 
		Str[Index++].StrSize = sizeof( "MPlumbAdj");	
		//----------------line 1--------------------
		Str[Index].Str = "CPlumbAdj";
		Str[Index++].StrSize = sizeof( "CPlumbAdj");
		Str[Index].Str =  "LCPlumbAdj"; 
		Str[Index++].StrSize = sizeof( "LCPlumbAdj" );
		//----------------line 2--------------------
		Str[Index].Str =  "LMPlumbAdj"; 
		Str[Index++].StrSize = sizeof( "LMPlumbAdj" );	
		Str[Index].Str =  "AdjPrintTest"; 
		Str[Index++].StrSize = sizeof( "AdjPrintTest" );
		//---------------line 3----------------------
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 
	}
	//----------------line 0--------------------
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//----------------line1--------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
   
	m++;
	tStr++;
	
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;	
	//----------------line 2--------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
		
	m++;
	tStr++;
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = 0  ;
	m->KeyVal = KEY_RIGHT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus;

	m++;
	tStr++;
	//----------------line 3--------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 	
	
}
 /*######根目录--> 打印设置子菜单*********
********* ***双向校准菜单 *界面###
*青色双向校准			品红双向校准
*黄色双向校准			浅清双向校准
*浅品双向校准			
*校准打印测试			退出		
*########################################*/
void MenuBidirectionAdjust2132Init( LanguageSel_t  langval )
{
	struct MenuItem *m  = &BidirectionAdjustMenu2132[0];
	struct MenuItem *tParentMenus = PrintSetMenu22 ;
	u8 tMenuCount = MENU_COUNT_PA;		
	StringArray_t Str[MENU_COUNT_PA];
	StringArray_t *tStr = Str ;
	u8 Index = 0;  

	LanguageSel_t tlangval = langval ;
	
	if( tlangval == CHINESE )
	{
		//----------------line 0--------------------
		Str[Index].Str = "青色双向校准"; 
		Str[Index++].StrSize = sizeof( "青色双向校准");	
		Str[Index].Str = "品红双向校准"; 
		Str[Index++].StrSize = sizeof( "品红双向校准");	
		//----------------line 1--------------------
		Str[Index].Str = "黄色双向校准";
		Str[Index++].StrSize = sizeof( "黄色双向校准");
		Str[Index].Str =  "浅清双向校准"; 
		Str[Index++].StrSize = sizeof( "浅清双向校准");
		//----------------line 2--------------------
		Str[Index].Str =  "浅品双向校准"; 
		Str[Index++].StrSize = sizeof( "浅品双向校准" );	
		Str[Index].Str =  "校准打印测试"; 
		Str[Index++].StrSize = sizeof( "校准打印测试" );
		//----------------line 3--------------------
		Str[Index].Str = "退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 
	}
	else
	{
		//----------------line 0--------------------
		Str[Index].Str = "YBidirAdj"; 
		Str[Index++].StrSize = sizeof( "YBidirAdj");	
		Str[Index].Str = "MBidirAdj"; 
		Str[Index++].StrSize = sizeof( "MBidirAdj");	
		//----------------line 1--------------------
		Str[Index].Str = "CBidirAdj";
		Str[Index++].StrSize = sizeof( "CBidirAdj");
		Str[Index].Str =  "LCBidirAdj"; 
		Str[Index++].StrSize = sizeof( "LCBidirAdj" );
		//----------------line 2--------------------
		Str[Index].Str =  "LMBidirAdj"; 
		Str[Index++].StrSize = sizeof( "LMBidirAdj" );	
		Str[Index].Str =  "AdjPrintTest"; 
		Str[Index++].StrSize = sizeof( "AdjPrintTest" );
		//---------------line 3----------------------
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 
	}
	//----------------line 0--------------------
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//----------------line1--------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
   
	m++;
	tStr++;
	
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;	
	//----------------line 2--------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
		
	m++;
	tStr++;
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = 0  ;
	m->KeyVal = KEY_RIGHT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus;

	m++;
	tStr++;
	//----------------line 3--------------------
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 	
	
}
static u8 DataAdjustBuf[3] = {' ', '0', '0'};
static u8 DataAdjustVal = 0 ;
/********青色水平校准---菜单*******************
*青色水平校准				确定
*           加				4 PASS  高速
*           00
*           减						取消
*******************************************************/
void LCM_APIAdjustValChToStr( u8 val , u8 * buf )
{	
		u8 temp = val ;
		u8 *tbuf = buf ;		
		tbuf[1] = temp%10 + 48 ;
		temp /= 10;
		tbuf[0] = temp%10 + 48 ;
}
void LCM_APILevelAdjustAdd( ) //加
{
	
	if( DataAdjustVal == 0 )		
		DataAdjustBuf[0] = '+' ;
	else if( DataAdjustVal == 99 )
		DataAdjustVal = 0 ;
	
	if( DataAdjustBuf[0] == '+' )
		DataAdjustVal++;
	else
		DataAdjustVal--;
	LCM_APIAdjustValChToStr(DataAdjustVal , DataAdjustBuf+1 );	
	
}
void LCM_APILevelAdjustDec( )//减
{
	if(DataAdjustVal == 0)		
		DataAdjustBuf[0] = '-' ;
	else if( DataAdjustVal == 99 )
		DataAdjustVal = 0 ;
	
	if(  DataAdjustBuf[0] == '-' )
		DataAdjustVal++;
	else
		DataAdjustVal--;
	
	LCM_APIAdjustValChToStr(DataAdjustVal , DataAdjustBuf+1 );	
}
void LCM_APIConfirmSlavePara( )
{

	DataAdjustVal = 0 ;
	DataAdjustBuf[0] = ' ' ;
	DataAdjustBuf[1] = '0' ;
	DataAdjustBuf[2] = '0' ;
	MenuLevelAdjustCyan213040Init(LanguageVal);
	//bmemset(DataAdjustBuf , 3 , ' ');
}
//#define MENU_COUNT_LAC       7
/******************************************************
*青色水平校准				确定
*           加				4 PASS  高速
*           00
*           减						取消
*******************************************************/
void MenuLevelAdjustCyan213040Init( LanguageSel_t  langval )
{
	
	struct MenuItem *m  = &LevelAdjustCyanMenu213040[0];	
	struct MenuItem *tParentMenus = LevelAdjustMenu2130 ;	/*父菜单*/
	u8 tMenuCount = MENU_COUNT_LAC;	
	StringArray_t Str[MENU_COUNT_LAC];
	StringArray_t *tStr = Str ;
	u8 Index = 0;
	LanguageSel_t tlangval = langval ;
	
	if( tlangval == CHINESE )
	{
		//-------------line 0 -------------------------
		Str[Index].Str = "青色水平校准"; 
		Str[Index++].StrSize = sizeof( "青色水平校准");
		Str[Index].Str = "确定"; 
		Str[Index++].StrSize = sizeof( "确定");
		//-------------line 1 -------------------------
		Str[Index].Str = "加";
		Str[Index++].StrSize = sizeof( "加");
		Str[Index].Str =  "4 PASS  高速"; 
		Str[Index++].StrSize = sizeof(  "4 PASS  高速" );	
		//-------------line 2 -------------------------
		Str[Index].Str = DataAdjustBuf ;// "00";		 /*变项*/
		Str[Index++].StrSize = sizeof( DataAdjustBuf ) + 1;	
		
		Str[Index].Str =  " 减"; 
		Str[Index++].StrSize = sizeof(  " 减" );	
		//-------------line 3 -------------------------
		Str[Index].Str = "取消"; 
		Str[Index++].StrSize = sizeof("取消");	 
	}
	else
	{
		//-------------line 0 -------------------------
		Str[Index].Str = "YLevelAdjust"; 
		Str[Index++].StrSize = sizeof( "YLevelAdjust");
		Str[Index].Str = "Confirm"; 
		Str[Index++].StrSize = sizeof( "Confirm");
		//-------------line 1 -------------------------
		Str[Index].Str = "Add";
		Str[Index++].StrSize = sizeof( "Add");
		Str[Index].Str =  "4 PassHighSpeed"; 
		Str[Index++].StrSize = sizeof( "4 PassHighSpeed" );	
		//-------------line 2 -------------------------
		Str[Index].Str = DataAdjustBuf ;// "00";		 /*变项*/
		Str[Index++].StrSize = sizeof( DataAdjustBuf ) + 1;	
		//-------------line 3 -------------------------
		Str[Index].Str =  " Dec"; 
		Str[Index++].StrSize = sizeof(  " Dec" );	

		Str[Index].Str = "Cancel"; 
		Str[Index++].StrSize = sizeof("Cancel");	 
	}
	//-------------line 0 -------------------------
	//L0 //调整参数名
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus =&Null_MenuItem ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//R0  //确定键，subs 更改参数
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = LCM_APIConfirmSlavePara; 
	m->ChildrenMenus =   tParentMenus ; //&Null_MenuItem; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//-------------line 1 -------------------------
	//L1     //加
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1;
	m->PositionX = 4  ;
	m->KeyVal = KEY_LEFT1 ;
	m->Subs = LCM_APILevelAdjustAdd; 
	m->ChildrenMenus = LevelAdjustCyanMenu213040; 
	m->ParentMenus = tParentMenus; 
   
	m++;
	tStr++;
	//R1  //调整参数子名
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = LevelAdjustCyanMenu213040; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//-------------line 2-------------------------
	//L2   //数字
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX = 3  ;
	m->KeyVal = KEY_LEFT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; 
	m->ParentMenus = tParentMenus; 
	
	m++;
	tStr++;
	//-------------line 3 -------------------------
	//L3  // 减
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = 3 ;
	m->KeyVal = KEY_LEFT3 ;
	m->Subs = LCM_APILevelAdjustDec; 
	m->ChildrenMenus = LevelAdjustCyanMenu213040; 
	m->ParentMenus = tParentMenus; 
	
	m++;
	tStr++;	
	//R3
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 
	
}

void MenuStepperAdjust2133Init( LanguageSel_t  langval )
{
	//struct MenuItem *m  = &StepperAdjustMenu2133[0];
	//struct MenuItem *tParentMenus = PrintSetMenu22 ;
	
}
/***********************************************
*简体中文				英语
*		
*
*							退出
***********************************************/
/***********************************************
*菜单由改为中文
************************************************/
void MenuChangChToEn(void)
{
	LanguageVal = ENGLISH  ;
	MenuInit( LanguageVal );
}
/***
*菜单由中文改为英文
***/
void MenuChangEnToCh(void)
{
	LanguageVal = CHINESE ;
	MenuInit( LanguageVal);
}
void MenuLanguage213541Init( LanguageSel_t  langval )
{
	struct MenuItem *m  = &LanguageMenu213541[0];
	struct MenuItem *tParentMenus =UserSetMenu2135 ;		
	u8 tMenuCount = MENU_COUNT_YY ;		
	StringArray_t Str[ MENU_COUNT_YY ];
	StringArray_t *tStr = Str ;
	u8 Index = 0;
	LanguageSel_t tlangval = langval ;
	if( tlangval == CHINESE )
	{
		
		//----------------line 0------------------------------
		Str[Index].Str = "简体中文"; 
		Str[Index++].StrSize = sizeof( "简体中文");
		
		Str[Index].Str = "英语"; 
		Str[Index++].StrSize = sizeof( "英语");	
		//----------------line 3------------------------------
		Str[Index].Str ="退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 
	}
	else
	{
		//----------------line 0------------------------------
		Str[Index].Str = "SimpleChinese" ;
		Str[Index++].StrSize = sizeof( "SimpleChinese");
		
		Str[Index].Str = "EngLish"; 
		Str[Index++].StrSize = sizeof( "EngLish");	
		//----------------line 3------------------------------
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 
	}
	//--------------line 0 ------------------------------	
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = MenuChangEnToCh; 
	m->ChildrenMenus = LanguageMenu213541 ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = MenuChangChToEn; 
	m->ChildrenMenus = LanguageMenu213541 ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//--------------line 3 ------------------------------	
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 
}
/***********************************************
*毫米							英寸
*		
*
*								退出
***********************************************/
void MenuChangInchToMM()
{
	
}
void MenuChangMMToInch()
{
	
}
void MenuUnit213540Init( LanguageSel_t  langval )
{
	struct MenuItem *m  = &UnitMenu213540[0];
	struct MenuItem *tParentMenus = UserSetMenu2135 ;		
	u8 tMenuCount = MENU_COUNT_YY ;		
	StringArray_t Str[ MENU_COUNT_YY ];
	StringArray_t *tStr = Str ;
	u8 Index = 0;
	LanguageSel_t tlangval = langval ;
	if( tlangval == CHINESE )
	{
		
		//----------------line 0------------------------------
		Str[Index].Str = "毫米"; 
		Str[Index++].StrSize = sizeof( "毫米");
		
		Str[Index].Str = "英寸"; 
		Str[Index++].StrSize = sizeof( "英寸");	
		//----------------line 3------------------------------
		Str[Index].Str ="退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 
	}
	else
	{
		//----------------line 0------------------------------
		Str[Index].Str = "Millimeter" ;
		Str[Index++].StrSize = sizeof( "Millimeter");
		
		Str[Index].Str = "Inch"; 
		Str[Index++].StrSize = sizeof( "Inch");	
		//----------------line 3------------------------------
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 
	}
	//--------------line 0 ------------------------------	
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = MenuChangInchToMM; 
	m->ChildrenMenus = UnitMenu213540 ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = MenuChangMMToInch; 
	m->ChildrenMenus = UnitMenu213540 ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//--------------line 3 ------------------------------	
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 
}
/******************************************
*计量单位选择           		语言
*
*
*                     				 	退出
******************************************/
void MenuUserSet2135Init( LanguageSel_t  langval )
{

	struct MenuItem *m  = &UserSetMenu2135[0];
	struct MenuItem *tParentMenus =PrintSetMenu22 ;		
	u8 tMenuCount = MENU_COUNT_US ;
		
	StringArray_t Str[ MENU_COUNT_US ];
	StringArray_t *tStr = Str ;
	u8 Index = 0;
	LanguageSel_t tlangval = langval ;
	if( tlangval == CHINESE )
	{
		//----------------line 0------------------------------
		Str[Index].Str = "计量单位选择"; 
		Str[Index++].StrSize = sizeof( "计量单位选择");
		
		Str[Index].Str = "语言"; 
		Str[Index++].StrSize = sizeof( "语言");	
		//----------------line 3------------------------------
		Str[Index].Str ="退出"; 
		Str[Index++].StrSize = sizeof( "退出");	 
	}
	else
	{
		//----------------line 0------------------------------
		Str[Index].Str = "Unit"; 
		Str[Index++].StrSize = sizeof( "Unit");
		
		Str[Index].Str = "Language" ; 
		Str[Index++].StrSize = sizeof( "Language") ;	
		//----------------line 3------------------------------
		Str[Index].Str ="Exit"; 
		Str[Index++].StrSize = sizeof( "Exit");	 			
	}
	//--------------line 0 ------------------------------
	//L0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = UnitMenu213540 ; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//R0
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = LanguageMenu213541; 
	m->ParentMenus = tParentMenus; 

	m++;
	tStr++;
	//--------------line 3 ------------------------------	
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = tParentMenus; 
	m->ParentMenus = tParentMenus; 
	
}

/*#########根目录--> 关于子菜单*界面###
*欢迎使用乐彩 写真机
*推荐使用乐彩喷头. 乐彩墨水
*免费服务热线: 400-717-6789
*网址：WWW.LECAIPRINTING.COM
*########################################*/

void MenuSysInfo27Init( LanguageSel_t  langval )
{
	
	struct MenuItem *m  = &SysInfoMenu27[0];
	struct MenuItem *tParentMenus =MainMenu;
	#define MENU_COUNT_SI    4
	StringArray_t Str[MENU_COUNT_SI];
	StringArray_t *tStr = Str ;
	u8 tMenuCount = MENU_COUNT_SI ;
	u8 Index = 0;
	LanguageSel_t  tlangval = langval;
	if( tlangval == CHINESE )
	{
		//----------------line 0------------------------------
		Str[Index].Str = "欢迎使用乐彩写真机";
		Str[Index++].StrSize = sizeof( "欢迎使用乐彩写真机");
		//----------------line 1------------------------------
		Str[Index].Str =  "推荐使用乐彩喷头. 乐彩墨水";
		Str[Index++].StrSize = sizeof( "推荐使用乐彩喷头. 乐彩墨水");
		//----------------line 2------------------------------
		Str[Index].Str = "免费服务热线: 400-717-6789";
		Str[Index++].StrSize = sizeof( "免费服务热线: 400-717-6789");
		//----------------line 3------------------------------
		Str[Index].Str = "网址: www.lecaiprinting.com";
		Str[Index++].StrSize = sizeof( "网址: www.lecaiprinting.com");

	}
	else
	{
		//----------------line 0------------------------------
		Str[Index].Str = "Welcome to use LeCai Printer";
		Str[Index++].StrSize = sizeof( "Welcome to use LeCai Printer");
		//----------------line 1------------------------------
		Str[Index].Str =  "Recommend to use LeCai Ink";
		Str[Index++].StrSize = sizeof( "Recommend to use LeCai Ink");
		//----------------line 2------------------------------
		Str[Index].Str = "Free Tel: 400-717-6789";
		Str[Index++].StrSize = sizeof( "Free Tel: 400-717-6789");
		//----------------line 3------------------------------
		Str[Index].Str = "URL:www.lecaiprinting.com";
		Str[Index++].StrSize = sizeof( "URL:www.lecaiprinting.com");
	}
	//----------------line 0------------------------------
	/*LR0*/
	m->MenuCount = tMenuCount;
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 2 ;
	m->KeyVal = KEY_NULL ;
	m->Subs = NullSubs;
	m->ChildrenMenus = &Null_MenuItem ;
	m->ParentMenus = tParentMenus ;
	
	m ++;
	tStr++;
	//----------------line 1------------------------------
	/*LR1*/
	m->MenuCount = tMenuCount ;
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = 2 ;
	m->KeyVal = KEY_NULL;
	m->Subs = NullSubs;
	m->ChildrenMenus = &Null_MenuItem ;
	m->ParentMenus = tParentMenus ;

	m ++;
	tStr++;
	//----------------line 2------------------------------
	/*LR2*/
	m->MenuCount = tMenuCount ;
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX = 2  ;
	m->KeyVal = KEY_NULL;
	m->Subs = NullSubs;
	m->ChildrenMenus = &Null_MenuItem ;
	m->ParentMenus = tParentMenus ;

	m ++;
	tStr++;
	//----------------line 3------------------------------
	/*LR3*/
	m->MenuCount = tMenuCount ;
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize = tStr->StrSize - 1 ; 
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = 2  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs;
	m->ChildrenMenus = tParentMenus ;//&Null_MenuItem ;
	m->ParentMenus = tParentMenus ;
	
}
 
/****************************************************
#########根目录， 主菜单*界面########
*装载介质				   馈送介质
*打印设置			辅助功能菜单
*继续/暂停打印		    取消打印
*切割								关于
*########################################
****************************************************/
/***************************************************
*  函数说明：根目录初始化                         * 
****************************************************/ 
void MenuMainInit( LanguageSel_t  langval ) 
{ 
	struct MenuItem *m  = &MainMenu[0];	
	#define MAIN_MENU_COUNT 8
	StringArray_t Str[MAIN_MENU_COUNT];
	StringArray_t *tStr = Str ;
	u8 tMenuCount = MAIN_MENU_COUNT ;
	u8 Index = 0;
	LanguageSel_t  tlangval = langval;
	if( tlangval == CHINESE )
	{
		//------------line 0------------------------------
		Str[Index].Str = "装载介质";
		Str[Index++].StrSize = sizeof("装载介质");
		Str[Index].Str ="馈送介质";
		Str[Index++].StrSize = sizeof("馈送介质");
		//------------line 1------------------------------
		Str[Index].Str = "打印设置";
		Str[Index++].StrSize = sizeof( "打印设置");
		Str[Index].Str = "辅助功能菜单";
		Str[Index++].StrSize = sizeof( "辅助功能菜单" );
		//------------line 2------------------------------
		Str[Index].Str ="继续打印";
		Str[Index++].StrSize = sizeof ( "继续打印" );	 	
		Str[Index].Str = "取消打印";
		Str[Index++].StrSize = sizeof ("取消打印");
		//------------line 3------------------------------
		Str[Index].Str ="切割";
		Str[Index++].StrSize = sizeof ( "切割");
		Str[Index].Str ="关于";
		Str[Index++].StrSize = sizeof("关于");	 
	}
	else if( tlangval == ENGLISH)
	{
		//------------line 0------------------------------
		Str[Index].Str = "Load " ;
		Str[Index++].StrSize = sizeof( "Load" );
		Str[Index].Str = "Feed" ;
		Str[Index++].StrSize = sizeof( "Feed" );
		//------------line 1------------------------------
		Str[Index].Str = "PrintSet";
		Str[Index++].StrSize = sizeof( "PrintSet");
		Str[Index].Str = "AssistantMenu";
		Str[Index++].StrSize = sizeof( "AssistantMenu" );
		//------------line 2------------------------------
		Str[Index].Str ="ContinuePrint";
		Str[Index++].StrSize = sizeof ( "ContinuePrint");	 	
		Str[Index].Str = "CancelPrint";
		Str[Index++].StrSize = sizeof ("CancelPrint");
		//------------line 3------------------------------
		Str[Index].Str ="Cut";
		Str[Index++].StrSize = sizeof ( "Cut");
		Str[Index].Str ="Info";
		Str[Index++].StrSize = sizeof("Info");	 
	}
	//------------line 0------------------------------
	/*L0*/
	m->MenuCount = tMenuCount; 
	m->DisplayString = tStr ->Str ; 
	m->DisplayStringSize =  tStr ->StrSize -1;
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem; /**/
	m->ParentMenus = &Null_MenuItem; 	
	
	m++;	
	tStr++;

	/*R0*/
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize =  tStr ->StrSize -1;
	m->PositionY = LCM_DIS_LINE0 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT0 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = FeedMediumMenu21;      
	m->ParentMenus = &Null_MenuItem; 
	
	m++;
	tStr++;
	//------------line 1------------------------------
	/*L1*/
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize =  tStr ->StrSize -1;
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = PrintSetMenu22 ; 
	m->ParentMenus = &Null_MenuItem; 

	m++;
	tStr++;
	
	/*R1*/
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize = tStr ->StrSize -1;
	m->PositionY = LCM_DIS_LINE1 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT1 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = AssistantFunctionMenu23;      
	m->ParentMenus = &Null_MenuItem; 	
	
   	m++;
	tStr++;
	//------------line 2------------------------------
	/*L2*/
	m->MenuCount =tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize =  tStr ->StrSize -1;
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX = 0  ;
	m->KeyVal = KEY_LEFT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem;      
	m->ParentMenus = &Null_MenuItem; 

	m++;
	tStr++;
	
	/*R2*/
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize =  tStr ->StrSize -1;
	m->PositionY = LCM_DIS_LINE2 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT2 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = &Null_MenuItem;      
	m->ParentMenus = &Null_MenuItem; 

	m++;
	tStr++;
	//------------line 3------------------------------
	/*L3*/
	m->MenuCount = tMenuCount; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize =  tStr ->StrSize -1;
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = 0 ;
	m->KeyVal = KEY_LEFT3 ;
	m->Subs = NullSubs; /*切纸函数*/
	m->ChildrenMenus = &Null_MenuItem;      
	m->ParentMenus = &Null_MenuItem; 
	
	m++;
	tStr++;
	
	/*最后一项一般都有*/
	/*R3*/
	m->MenuCount = MAIN_MENU_COUNT; 
	m->DisplayString =  tStr ->Str ; 
	m->DisplayStringSize =  tStr ->StrSize -1;
	m->PositionY = LCM_DIS_LINE3 ;
	m->PositionX = LCM_COL_CHAR -  m->DisplayStringSize  ;
	m->KeyVal = KEY_RIGHT3 ;
	m->Subs = NullSubs; 
	m->ChildrenMenus = SysInfoMenu27 ;      
	m->ParentMenus = &Null_MenuItem; 
	
} 

void MenuInit( LanguageSel_t  langval )
{

	LanguageSel_t  tlangval = langval;
	 MenuMainInit( tlangval );
	 MenuFeedMedium21Init( tlangval );
	 MenuPrintSet22Init( tlangval );
	 MenuSysInfo27Init( tlangval );
	 //******三级菜单*******************
	 MenuLevelAdjust2130Init( tlangval );
	 MenuPlumbAdjust2131Init( tlangval );
	 MenuBidirectionAdjust2132Init( tlangval );
	 MenuAssistantFunction23Init ( tlangval );
	MenuLevelAdjustCyan213040Init( tlangval );
        MenuPrintTestPage2230Init( tlangval );
	 //MenuStepperAdjust2133Init( tlangval );
	 //OpenAutoCutPeperMenu2134Init( tlangval );
	 MenuUserSet2135Init( tlangval );
	 MenuLanguage213541Init( tlangval );
	 MenuUnit213540Init( tlangval );
	 
}

#endif //#if LCM_GUI_EN>0

