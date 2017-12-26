//file: menu.c

#include "includes.h"

#if LCM_GUI_EN>0

struct MenuItem  Null_MenuItem ;
/****************************************************
#########��Ŀ¼�� ���˵�*����########
*װ�ؽ���				   ���ͽ���
*��ӡ����			�������ܲ˵�
*����/��ͣ��ӡ		    ȡ����ӡ
*�и�								����
*########################################
****************************************************/
struct MenuItem MainMenu[8];					 /*��Ŀ¼�� ���˵�*/
/*-------------------------------------------------------------------------------*/
//*****�����˵�*************************************************************
// MenuItem LoadMediumMenu[6];				/*��Ŀ¼--װ�ؽ��ʲ˵�*/
/************************************************************
*######��Ŀ¼--> ���ͽ����Ӳ˵�*����#######
*ǰ��											����
*
*
*												�˳�	
*##############################################
*************************************************************/
#define MENU_COUNT_FM 		3
struct  MenuItem FeedMediumMenu21[MENU_COUNT_FM];		/*��Ŀ¼--���ͽ���*/
/**************************************************************
#########��Ŀ¼--> ��ӡ�����Ӳ˵�*����#######
*ˮƽУ׼�˵�				��ֱУ׼�˵�
*˫��У׼�˵�				����У׼�˵�
*���Զ���ֽ				     ʹ��������
*										       �˳�	
*################################################
***************************************************************/
#define MENU_COUNT_PS   	7
struct  MenuItem PrintSetMenu22[MENU_COUNT_PS];	 		/*��Ŀ¼--��ӡ�����Ӳ˵�*/

/*#########��Ŀ¼--> �������ܲ˵�*����########
*��ϴ									ȡīˮϻ
*��ӡ����ҳ�˵�						    ��ī

*											    �˳�	
*#################################################*/
#define MENU_COUNT_AF 		6
struct  MenuItem AssistantFunctionMenu23[MENU_COUNT_AF] ; 	/*��Ŀ¼--�������ܲ˵�*/
 											/*��Ŀ¼--����/��ͣ��ӡ*/
											/*��Ŀ¼--ȡ����ӡ*/
 //MenuItem CutMenu[1] ;						/*��Ŀ¼--�и�*/
struct MenuItem SysInfoMenu27[4] ;			/*��Ŀ¼--����  info*/

//******�����˵�**********************************************************
#define  MENU_COUNT_LA     7
struct MenuItem LevelAdjustMenu2130[MENU_COUNT_LA]; 
struct MenuItem PlumbAdjustMenu2131[7]; 
struct MenuItem BidirectionAdjustMenu2132[7]; 
struct MenuItem StepperAdjustMenu2133[7]; 
//struct MenuItem OpenAutoCutPeperMenu2134[7]; 
/******************************************
*������λѡ��          	����
*
*
*                      				�˳�
******************************************/
#define MENU_COUNT_US  3
struct MenuItem UserSetMenu2135[MENU_COUNT_US]; 
/******************************************
*����          				 Ӣ��
*
*
*                      				 �˳�
******************************************/
#define MENU_COUNT_YY  3
struct MenuItem LanguageMenu213541[ MENU_COUNT_YY ]; 
/******************************************
*����          				Ӣ��
*
*
*                      				 �˳�
******************************************/
#define MENU_COUNT_UN   3
struct MenuItem UnitMenu213540[MENU_COUNT_UN];

struct MenuItem AdjustMenu213040[5];
/*****************************************************************************
********��ӡ����ҳ�˵�************************************************
*��ӡ������			�ۺϲ���ҳ
*�мܼ��һ			�мܼ���
*�мܼ����
*									  �˳�
*****************************************************************************/
#define MENU_COUNT_PTP 	 			6
struct MenuItem PrintTestPageMenu2230[MENU_COUNT_PTP];
#define MENU_COUNT_LAC       7
struct MenuItem LevelAdjustCyanMenu213040[MENU_COUNT_LAC];
//-------------------------------------------------------------------------
//struct MenuItem ClearIngMenu2330[5];
static LanguageSel_t LanguageVal  = CHINESE;/*��ǰ�����趨ֵ*/
//

void MenuMainInit(  LanguageSel_t  langval );
//*****�����˵�***********************************************************
void MenuFeedMedium21Init( LanguageSel_t  langval );
void MenuPrintSet22Init( LanguageSel_t  langval );
void MenuSysInfo27Init( LanguageSel_t  langval );
void MenuAssistantFunction23Init( LanguageSel_t  langval );
//******�����˵�**********************************************************
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
*�պ���
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
*######��Ŀ¼--> ���ͽ����Ӳ˵�*����#######
*ǰ��											����
*
*
*												�˳�	
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
		Str[Index].Str = "ǰ��"; 
		Str[Index++].StrSize = sizeof( "ǰ��" );	
		Str[Index].Str = "����"; 
		Str[Index++].StrSize = sizeof( "����");	
		//----------------line 3--------------------
		Str[Index].Str = "�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 
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
#########��Ŀ¼--> ��ӡ�����Ӳ˵�*����#######
*ˮƽУ׼�˵�				��ֱУ׼�˵�
*˫��У׼�˵�				����У׼�˵�
*���Զ���ֽ				     ʹ��������
*										       �˳�	
*################################################
***************************************************************/
/************************************************************** 
*  ����˵������ӡ�����Ӳ˵�                            		 * 
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
		Str[Index].Str = "ˮƽУ׼�˵�"; 
		Str[Index++].StrSize = sizeof( "ˮƽУ׼�˵�");	
		Str[Index].Str = "��ֱУ׼�˵�"; 
		Str[Index++].StrSize = sizeof( "��ֱУ׼�˵�");	
		//----------------line 1--------------------
		Str[Index].Str = "˫��У׼�˵�";
		Str[Index++].StrSize = sizeof( "˫��У׼�˵�");
		Str[Index].Str =  "����У׼�˵�"; 
		Str[Index++].StrSize = sizeof( "����У׼�˵�" );
		//----------------line 2--------------------
		Str[Index].Str =  "���Զ���ֽ"; 
		Str[Index++].StrSize = sizeof( "���Զ���ֽ" );	
		Str[Index].Str =  "ʹ��������"; 
		Str[Index++].StrSize = sizeof( "ʹ��������" );
		//----------------line 3--------------------
		Str[Index].Str = "�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 
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
/*###��Ŀ¼--> �������ܲ˵�--> ����˵�######
*У׼�˵�					��ϲ˵� 	       	   
*īˮϻ��Ϣ				 ���Դ�ӡ
*						     			     
*									   �˳�
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
		Str[Index].Str = "У׼�˵�"; 
		Str[Index++].StrSize = sizeof( "У׼�˵�");
		Str[Index].Str = "��ϲ˵�"; 
		Str[Index++].StrSize = sizeof( "��ϲ˵�");
		//-------------line1--------------------------------
		Str[Index].Str = "īˮϻ��Ϣ";
		Str[Index++].StrSize = sizeof( "īˮϻ��Ϣ");
		Str[Index].Str =  "���Դ�ӡ"; 
		Str[Index++].StrSize = sizeof(  "���Դ�ӡ" );	
		//-------------line2--------------------------------	
		//-------------line3--------------------------------
		Str[Index].Str ="�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 		
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



/*#########��Ŀ¼--> �������ܲ˵�*����########
*��ϴ									ȡīˮϻ
*��ӡ����ҳ�˵�						    ��ī
*����˵�
*											    �˳�	
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
		Str[Index].Str = "��ϴ"; 
		Str[Index++].StrSize = sizeof( "��ϴ");
		Str[Index].Str = "��ȡīˮϻ"; 
		Str[Index++].StrSize = sizeof( "��ȡīˮϻ");
		//-------------line1--------------------------------
		Str[Index].Str = "��ӡ����ҳ�˵�";
		Str[Index++].StrSize = sizeof( "��ӡ����ҳ�˵�");
		Str[Index].Str =  "��ī"; 
		Str[Index++].StrSize = sizeof(  "��ī" );	
		//-------------line2--------------------------------
		Str[Index].Str =  "����˵�"; 
		Str[Index++].StrSize = sizeof(  "����˵�" );
		//-------------line3--------------------------------
		Str[Index].Str ="�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 		
	}
	else
	{
		//-------------line0--------------------------------
		Str[Index].Str = "Clear";
		Str[Index++].StrSize = sizeof( "Clear");
		Str[Index].Str = "��ȡīˮϻ"; 
		Str[Index++].StrSize = sizeof( "��ȡīˮϻ");
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
********��ӡ����ҳ�˵�**************
*��ӡ������			�ۺϲ���ҳ
*�мܼ��һ			�мܼ���
*�мܼ����
*				�˳�
********************************************/
/*******************************************
*˵��: ������һ���˵�
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
		Str[Index].Str = "��ӡ������"; 
		Str[Index++].StrSize = sizeof( "��ӡ������");
		Str[Index].Str = "�ۺϲ���ҳ"; 
		Str[Index++].StrSize = sizeof( "�ۺϲ���ҳ");
		//-------------line 1 -------------------------
		Str[Index].Str = "�мܼ��һ";
		Str[Index++].StrSize = sizeof( "�мܼ��һ");
		Str[Index].Str =  "�мܼ���"; 
		Str[Index++].StrSize = sizeof(  "�мܼ���" );	
		//-------------line 2 -------------------------
		Str[Index].Str =  "�мܼ����"; 
		Str[Index++].StrSize = sizeof(  "�мܼ����" );	
		//-------------line 3 -------------------------
		Str[Index].Str ="�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 
	}
	else
	{
		//-------------line 0 -------------------------
		Str[Index].Str = "��ӡ������"; 
		Str[Index++].StrSize = sizeof( "��ӡ������");
		Str[Index].Str = "�ۺϲ���ҳ"; 
		Str[Index++].StrSize = sizeof( "�ۺϲ���ҳ");
		//-------------line 1 -------------------------
		Str[Index].Str = "�мܼ��һ";
		Str[Index++].StrSize = sizeof( "�мܼ��һ");
		Str[Index].Str =  "�мܼ���"; 
		Str[Index++].StrSize = sizeof(  "�мܼ���" );	
		//-------------line 2 -------------------------
		Str[Index].Str =  "�мܼ����"; 
		Str[Index++].StrSize = sizeof(  "�мܼ����" );	
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

 /*********��Ŀ¼--> ��ӡ�����Ӳ˵�*********
***********��ֱУ׼�˵� *����*****************
*��ɫˮƽУ׼			Ʒ��ˮƽУ׼
*��ɫˮƽУ׼			ǳ��ˮƽУ׼
*ǳƷˮƽУ׼			
*У׼��ӡ����						�˳�		
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
		Str[Index].Str = "��ɫˮƽУ׼"; 
		Str[Index++].StrSize = sizeof( "��ɫˮƽУ׼");	
		Str[Index].Str = "Ʒ��ˮƽУ׼"; 
		Str[Index++].StrSize = sizeof( "Ʒ��ˮƽУ׼");	
		//----------------line 1--------------------
		Str[Index].Str = "��ɫˮƽУ׼";
		Str[Index++].StrSize = sizeof( "��ɫˮƽУ׼");
		Str[Index].Str =  "ǳ��ˮƽУ׼"; 
		Str[Index++].StrSize = sizeof( "ǳ��ˮƽУ׼");
		//----------------line 2--------------------
		Str[Index].Str =  "ǳƷˮƽУ׼"; 
		Str[Index++].StrSize = sizeof( "ǳƷˮƽУ׼" );	
		Str[Index].Str =  "У׼��ӡ����"; 
		Str[Index++].StrSize = sizeof( "У׼��ӡ����" );
		//----------------line 3--------------------
		Str[Index].Str = "�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 
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
 /*######��Ŀ¼--> ��ӡ�����Ӳ˵�*********
***********��ֱУ׼�˵� *����############
*��ɫ��ֱУ׼			Ʒ�촹ֱУ׼
*��ɫ��ֱУ׼			ǳ�崹ֱУ׼
*ǳƷ��ֱУ׼			
*У׼��ӡ����			�˳�		
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
		Str[Index].Str = "��ɫ��ֱУ׼"; 
		Str[Index++].StrSize = sizeof( "��ɫ��ֱУ׼");	
		Str[Index].Str = "Ʒ�촹ֱУ׼"; 
		Str[Index++].StrSize = sizeof( "Ʒ�촹ֱУ׼");	
		//----------------line 1--------------------
		Str[Index].Str = "��ɫ��ֱУ׼";
		Str[Index++].StrSize = sizeof( "��ɫ��ֱУ׼");
		Str[Index].Str =  "ǳ�崹ֱУ׼"; 
		Str[Index++].StrSize = sizeof( "ǳ�崹ֱУ׼");
		//----------------line 2--------------------
		Str[Index].Str =  "ǳƷ��ֱУ׼"; 
		Str[Index++].StrSize = sizeof( "ǳƷ��ֱУ׼" );	
		Str[Index].Str =  "У׼��ӡ����"; 
		Str[Index++].StrSize = sizeof( "У׼��ӡ����" );
		//----------------line 3--------------------
		Str[Index].Str = "�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 
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
 /*######��Ŀ¼--> ��ӡ�����Ӳ˵�*********
********* ***˫��У׼�˵� *����###
*��ɫ˫��У׼			Ʒ��˫��У׼
*��ɫ˫��У׼			ǳ��˫��У׼
*ǳƷ˫��У׼			
*У׼��ӡ����			�˳�		
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
		Str[Index].Str = "��ɫ˫��У׼"; 
		Str[Index++].StrSize = sizeof( "��ɫ˫��У׼");	
		Str[Index].Str = "Ʒ��˫��У׼"; 
		Str[Index++].StrSize = sizeof( "Ʒ��˫��У׼");	
		//----------------line 1--------------------
		Str[Index].Str = "��ɫ˫��У׼";
		Str[Index++].StrSize = sizeof( "��ɫ˫��У׼");
		Str[Index].Str =  "ǳ��˫��У׼"; 
		Str[Index++].StrSize = sizeof( "ǳ��˫��У׼");
		//----------------line 2--------------------
		Str[Index].Str =  "ǳƷ˫��У׼"; 
		Str[Index++].StrSize = sizeof( "ǳƷ˫��У׼" );	
		Str[Index].Str =  "У׼��ӡ����"; 
		Str[Index++].StrSize = sizeof( "У׼��ӡ����" );
		//----------------line 3--------------------
		Str[Index].Str = "�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 
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
/********��ɫˮƽУ׼---�˵�*******************
*��ɫˮƽУ׼				ȷ��
*           ��				4 PASS  ����
*           00
*           ��						ȡ��
*******************************************************/
void LCM_APIAdjustValChToStr( u8 val , u8 * buf )
{	
		u8 temp = val ;
		u8 *tbuf = buf ;		
		tbuf[1] = temp%10 + 48 ;
		temp /= 10;
		tbuf[0] = temp%10 + 48 ;
}
void LCM_APILevelAdjustAdd( ) //��
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
void LCM_APILevelAdjustDec( )//��
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
*��ɫˮƽУ׼				ȷ��
*           ��				4 PASS  ����
*           00
*           ��						ȡ��
*******************************************************/
void MenuLevelAdjustCyan213040Init( LanguageSel_t  langval )
{
	
	struct MenuItem *m  = &LevelAdjustCyanMenu213040[0];	
	struct MenuItem *tParentMenus = LevelAdjustMenu2130 ;	/*���˵�*/
	u8 tMenuCount = MENU_COUNT_LAC;	
	StringArray_t Str[MENU_COUNT_LAC];
	StringArray_t *tStr = Str ;
	u8 Index = 0;
	LanguageSel_t tlangval = langval ;
	
	if( tlangval == CHINESE )
	{
		//-------------line 0 -------------------------
		Str[Index].Str = "��ɫˮƽУ׼"; 
		Str[Index++].StrSize = sizeof( "��ɫˮƽУ׼");
		Str[Index].Str = "ȷ��"; 
		Str[Index++].StrSize = sizeof( "ȷ��");
		//-------------line 1 -------------------------
		Str[Index].Str = "��";
		Str[Index++].StrSize = sizeof( "��");
		Str[Index].Str =  "4 PASS  ����"; 
		Str[Index++].StrSize = sizeof(  "4 PASS  ����" );	
		//-------------line 2 -------------------------
		Str[Index].Str = DataAdjustBuf ;// "00";		 /*����*/
		Str[Index++].StrSize = sizeof( DataAdjustBuf ) + 1;	
		
		Str[Index].Str =  " ��"; 
		Str[Index++].StrSize = sizeof(  " ��" );	
		//-------------line 3 -------------------------
		Str[Index].Str = "ȡ��"; 
		Str[Index++].StrSize = sizeof("ȡ��");	 
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
		Str[Index].Str = DataAdjustBuf ;// "00";		 /*����*/
		Str[Index++].StrSize = sizeof( DataAdjustBuf ) + 1;	
		//-------------line 3 -------------------------
		Str[Index].Str =  " Dec"; 
		Str[Index++].StrSize = sizeof(  " Dec" );	

		Str[Index].Str = "Cancel"; 
		Str[Index++].StrSize = sizeof("Cancel");	 
	}
	//-------------line 0 -------------------------
	//L0 //����������
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
	//R0  //ȷ������subs ���Ĳ���
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
	//L1     //��
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
	//R1  //������������
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
	//L2   //����
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
	//L3  // ��
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
*��������				Ӣ��
*		
*
*							�˳�
***********************************************/
/***********************************************
*�˵��ɸ�Ϊ����
************************************************/
void MenuChangChToEn(void)
{
	LanguageVal = ENGLISH  ;
	MenuInit( LanguageVal );
}
/***
*�˵������ĸ�ΪӢ��
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
		Str[Index].Str = "��������"; 
		Str[Index++].StrSize = sizeof( "��������");
		
		Str[Index].Str = "Ӣ��"; 
		Str[Index++].StrSize = sizeof( "Ӣ��");	
		//----------------line 3------------------------------
		Str[Index].Str ="�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 
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
*����							Ӣ��
*		
*
*								�˳�
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
		Str[Index].Str = "����"; 
		Str[Index++].StrSize = sizeof( "����");
		
		Str[Index].Str = "Ӣ��"; 
		Str[Index++].StrSize = sizeof( "Ӣ��");	
		//----------------line 3------------------------------
		Str[Index].Str ="�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 
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
*������λѡ��           		����
*
*
*                     				 	�˳�
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
		Str[Index].Str = "������λѡ��"; 
		Str[Index++].StrSize = sizeof( "������λѡ��");
		
		Str[Index].Str = "����"; 
		Str[Index++].StrSize = sizeof( "����");	
		//----------------line 3------------------------------
		Str[Index].Str ="�˳�"; 
		Str[Index++].StrSize = sizeof( "�˳�");	 
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

/*#########��Ŀ¼--> �����Ӳ˵�*����###
*��ӭʹ���ֲ� д���
*�Ƽ�ʹ���ֲ���ͷ. �ֲ�īˮ
*��ѷ�������: 400-717-6789
*��ַ��WWW.LECAIPRINTING.COM
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
		Str[Index].Str = "��ӭʹ���ֲ�д���";
		Str[Index++].StrSize = sizeof( "��ӭʹ���ֲ�д���");
		//----------------line 1------------------------------
		Str[Index].Str =  "�Ƽ�ʹ���ֲ���ͷ. �ֲ�īˮ";
		Str[Index++].StrSize = sizeof( "�Ƽ�ʹ���ֲ���ͷ. �ֲ�īˮ");
		//----------------line 2------------------------------
		Str[Index].Str = "��ѷ�������: 400-717-6789";
		Str[Index++].StrSize = sizeof( "��ѷ�������: 400-717-6789");
		//----------------line 3------------------------------
		Str[Index].Str = "��ַ: www.lecaiprinting.com";
		Str[Index++].StrSize = sizeof( "��ַ: www.lecaiprinting.com");

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
#########��Ŀ¼�� ���˵�*����########
*װ�ؽ���				   ���ͽ���
*��ӡ����			�������ܲ˵�
*����/��ͣ��ӡ		    ȡ����ӡ
*�и�								����
*########################################
****************************************************/
/***************************************************
*  ����˵������Ŀ¼��ʼ��                         * 
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
		Str[Index].Str = "װ�ؽ���";
		Str[Index++].StrSize = sizeof("װ�ؽ���");
		Str[Index].Str ="���ͽ���";
		Str[Index++].StrSize = sizeof("���ͽ���");
		//------------line 1------------------------------
		Str[Index].Str = "��ӡ����";
		Str[Index++].StrSize = sizeof( "��ӡ����");
		Str[Index].Str = "�������ܲ˵�";
		Str[Index++].StrSize = sizeof( "�������ܲ˵�" );
		//------------line 2------------------------------
		Str[Index].Str ="������ӡ";
		Str[Index++].StrSize = sizeof ( "������ӡ" );	 	
		Str[Index].Str = "ȡ����ӡ";
		Str[Index++].StrSize = sizeof ("ȡ����ӡ");
		//------------line 3------------------------------
		Str[Index].Str ="�и�";
		Str[Index++].StrSize = sizeof ( "�и�");
		Str[Index].Str ="����";
		Str[Index++].StrSize = sizeof("����");	 
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
	m->Subs = NullSubs; /*��ֽ����*/
	m->ChildrenMenus = &Null_MenuItem;      
	m->ParentMenus = &Null_MenuItem; 
	
	m++;
	tStr++;
	
	/*���һ��һ�㶼��*/
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
	 //******�����˵�*******************
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

