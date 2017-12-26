//file: lcm.c  for lcm gui
/*-----------------------------------------
*LCM 240 * 64 driver (T6963C)
*----------------------------------------*/

#include "includes.h"


#if LCM_GUI_EN>0

u8 DisBuf[DISBUF_SIZE];
struct MenuItem *MenuPoint = MainMenu; /*初始化，默认显示MainMenu菜单*/

void LCM_UpdataDisBuf( struct  MenuItem *MI  );

#endif //#if LCM_GUI_EN>0

static u8 text[11];
//unsigned char Cursor_X, Cursor_Y;        /*光标的坐标 */
/*******************************************************************************
* Function Name  : int2char
* Description    : This function convertes a int to a string
* Input          : u16 value
* Output         : None
* Return         : None
*******************************************************************************/
u8 *WordToChar(u16 value)
{ 

  u8 i;
  u8 bValue;
  u16 temp;  
  
 bmemset(text, 0, 5);
  
  temp = 10000;  
  for (i=0;i<5;i++)
  {
	bValue = (u8)(value/temp);
	text[i] = (u8)(bValue+0x30);
    
	value %= temp;
	temp /= 10;                
  }    
  return(text);
  
}
/*******************************************************************************
* Function Name  : int2char
* Description    : This function convertes a int to a string
* Input          : u16 value
* Output         : None
* Return         : None
*******************************************************************************/
u8 *DWordToChar(u32 value)
{ 

  u8 i;
  u32 bValue;
  u32 temp;  
  
 bmemset(text, 0, 10);
  
  temp = 1000000000;  
  for (i=0;i<10;i++)
  {
	bValue = (u8)(value/temp);
	text[i] = (u8)(bValue+0x30);
    
	value %= temp;
	temp /= 10;                
  }    
  return(text);
  
}

void LF_DataBusForLCM( )
{
	GPIO_ResetBits( GPIO_LCM_DATA_DIR_EN, LCM_DATA_OUT_EN_PIN ); //ENABLE hc245
}
void LF_DataBusForFPGA( )
{
	GPIO_SetBits( GPIO_LCM_DATA_DIR_EN, LCM_DATA_OUT_EN_PIN ); //ENABLE hc245
}

/*#################和mcu 有关的定义   开始......################*/
void Init_LFGpio( void )
{

	GPIO_InitTypeDef GPIO_InitStructure ;
	/*----- Configure IO connected to lcm ---------------*/
	 /* ------Enable GPIO_lcm  clock --------------------------*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_LCM_DATA_DIR_EN , ENABLE );
	
	GPIO_InitStructure.GPIO_Pin =  LCM_DATA_OUT_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_LCM_DATA_DIR_EN ;
	GPIO_Init( GPIO_LCM_DATA_DIR_EN , &GPIO_InitStructure );	  

	//data bus 8bit
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_LCM_DATA  , ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = LCM_DATA0_PIN |LCM_DATA1_PIN|LCM_DATA2_PIN|LCM_DATA3_PIN\
	  						|LCM_DATA4_PIN |LCM_DATA5_PIN|LCM_DATA6_PIN|LCM_DATA7_PIN ;	  
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP ;			 //GPIO_Mode_Out_PP ;/*pull up input*/
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_LCM_DATA ;
	GPIO_Init( GPIO_LCM_DATA , &GPIO_InitStructure );
	  
	GPIO_SetBits(GPIO_LCM_DATA ,  LCM_DATA0_PIN |LCM_DATA1_PIN|LCM_DATA2_PIN|LCM_DATA3_PIN\
	  						|LCM_DATA4_PIN |LCM_DATA5_PIN|LCM_DATA6_PIN|LCM_DATA7_PIN );

	
	LF_DataBusForFPGA( );
	
}
/*******************************************************************************
* Function Name  : LF_GPIO_WriteLow8Bit
* Description    : Writes data to the specified GPIO data port low 8bit.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  - PortVal: specifies the value to be written to the port output
*                    data register.
* Output         : None
* Return         : None
*******************************************************************************/
void LF_GPIO_WriteLow8Bit(GPIO_TypeDef* GPIOx, u8 data)
{

	  /* Check the parameters */
	  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	  GPIOx->ODR = ( u16 )data | (GPIOx->ODR & 0xff00);
	  
}

#if LCM_GUI_EN>0

/*#################和mcu 有关的定义   开始......################*/
void Init_LCMGpio( void )
{

	GPIO_InitTypeDef GPIO_InitStructure;
	/*----- Configure IO connected to lcm ---------------*/
	 /* ------Enable GPIO_lcm  clock --------------------------*/
	
	//RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_LCM_DATA  , ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_LCM_DATA_DIR_EN , ENABLE );		  
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_LCM_CTR, ENABLE );


	GPIO_InitStructure.GPIO_Pin = LCM_DATA_DIR_PIN | LCM_FS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_LCM_DATA_DIR_EN ;
	GPIO_Init( GPIO_LCM_DATA_DIR_EN , &GPIO_InitStructure );
	  
	GPIO_ResetBits( GPIO_LCM_DATA_DIR_EN,  LCM_DATA_DIR_PIN) ;// LCM_DATA_IN_MODE

	GPIO_InitStructure.GPIO_Pin = LCM_WR_PIN | LCM_RD_PIN | LCM_CD_PIN | LCM_CE_PIN ;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP ; 	//GPIO_Mode_Out_PP ;/*pull up input*/
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_LCM_CTR ;
	GPIO_Init( GPIO_LCM_CTR , &GPIO_InitStructure );
	GPIO_SetBits( GPIO_LCM_CTR ,  LCM_WR_PIN | LCM_RD_PIN | LCM_CD_PIN | LCM_CE_PIN | LCM_FS_PIN  );

	GPIO_InitStructure.GPIO_Pin = LCM_RST_PIN ;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP ; 	//GPIO_Mode_Out_PP ;/*pull up input*/
	GPIO_InitStructure.GPIO_Speed = GPIOA_SPEED_LCM_CTR ;
	GPIO_Init( GPIOA_LCM_CTR , &GPIO_InitStructure );
	GPIO_SetBits( GPIOA_LCM_CTR ,   LCM_RST_PIN );
		  
}
void LCM_Reset(void)
{
	GPIO_ResetBits( GPIOA_LCM_CTR ,   LCM_RST_PIN );
	Delaynus(50000);
	GPIO_SetBits( GPIOA_LCM_CTR ,   LCM_RST_PIN );
}
#if 1
void LCM_IODelay(u32 count)
{
	Delay(count);
}
#endif

void LCM_WDelay(  )
{
	Delay(4);
}
void LCM_RDelay(  )
{
	Delay(2);
}
/*
*CD  //CD = H , send CMD  mode ;  CD =L , send DATA mode 
RD  //read en
WR //write en
CE // cs
FS // font sel
DATA //data bus

*/

//信号管脚定义(全局变量）


void LCM_CD_HIGH() 	/*CD = H , send CMD  mode */
{

	GPIO_SetBits(GPIO_LCM_CTR, LCM_CD_PIN );
	
	
}
void LCM_CD_LOW() 	/*CD =L , send DATA mode */
{

	GPIO_ResetBits(GPIO_LCM_CTR, LCM_CD_PIN);
		
}

void  LCM_RD_HIGH() 	
{

	GPIO_SetBits(GPIO_LCM_CTR, LCM_RD_PIN );
		
}
void  LCM_RD_LOW() 	/*read  lcm mode*/
{
	GPIO_ResetBits(GPIO_LCM_CTR, LCM_RD_PIN);	
}

void  LCM_WR_HIGH()
{	

	GPIO_SetBits(GPIO_LCM_CTR, LCM_WR_PIN );	
		
}
void  LCM_WR_LOW() /*write  lcm mode*/
{	

	GPIO_ResetBits(GPIO_LCM_CTR, LCM_WR_PIN) ;	
		
}

void  LCM_CE_HIGH() /*chip ; disable , select  lcm*/
{	

	GPIO_SetBits(GPIO_LCM_CTR, LCM_CE_PIN ) ;		

}
void  LCM_CE_LOW() /*chip ; enable , select  lcm*/
{	
	
	GPIO_ResetBits(GPIO_LCM_CTR, LCM_CE_PIN) ;	

}

void  LCM_FS_HIGH() /* Font Select , H =  6x8 dot matrix ,  */
{	

	GPIO_SetBits(GPIO_LCM_CTR , LCM_FS_PIN ) ; 	
	
}
void  LCM_FS_LOW() /* Font Select , L =  8x8 dot matrix ,  */
{

	GPIO_ResetBits(GPIO_LCM_CTR , LCM_FS_PIN);	
	
}

/*******************************************************************************
* Function Name  : LCM_DataPortIOSet
* Description    : 驱动LCM 数据端口输入输出模式设定
* Input          : - InOutMode:
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_DataPortIOSet(u8 InOutMode)/*LCM D0--D7 ---MCU( PD0--PD7)  */
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	LF_DataBusForLCM();
	
	GPIO_InitStructure.GPIO_Pin = LCM_DATA0_PIN |LCM_DATA1_PIN|LCM_DATA2_PIN|LCM_DATA3_PIN\
	  						|LCM_DATA4_PIN |LCM_DATA5_PIN|LCM_DATA6_PIN|LCM_DATA7_PIN;	

	if( InOutMode == GPIO_IN_MODE )
	  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING ;		 //GPIO_Mode_Out_PP ;/*pull up input*/
	else if( InOutMode == GPIO_OUT_MODE  )
	  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP ;			 //GPIO_Mode_Out_PP ;/*pull up input*/
	else
		return;
	  
	  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_LCM_DATA ;
	  GPIO_Init( GPIO_LCM_DATA , &GPIO_InitStructure );
	  
}

/*******************************************************************************
* Function Name  : LCM_WriteDatabusByte
* Description    : write  lcd data bus
* Input          : - data:
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_WriteDatabusByte( u8 data)
{

	LCM_DataPortIOSet( GPIO_OUT_MODE );//
	
	GPIO_SetBits( GPIO_LCM_DATA_DIR_EN,  LCM_DATA_DIR_PIN) ;// write lcm
		
	LF_GPIO_WriteLow8Bit( GPIO_LCM_DATA ,  data ) ;
	
}
/*******************************************************************************
* Function Name  : LCM_ReadDatabusByte
* Description    : read  lcd data bus
* Input           :  None:
* Output         : None
* Return         : None
*******************************************************************************/
u8 LCM_ReadDatabusByte( void )
{

	u8 dat = 0 ;
	LCM_DataPortIOSet( GPIO_IN_MODE );//
	
	GPIO_ResetBits( GPIO_LCM_DATA_DIR_EN,  LCM_DATA_DIR_PIN) ;	// read lcm		
	
	dat = (u8)GPIO_ReadInputData( GPIO_LCM_DATA ) ;	
	
	return  dat;
	
}
#define CHECK_TIME_OUT  50  /*检测超时常数*/
/*################和mcu 有关的定义  结束!####################*/
/*******************************************************************************
* Function Name  : LCM_RWCheck
* Description    : 判断状态位STA1，STA0子程序（读写指令和读写数据状态），在写指令的读，
           写数据之前这两个标志位必须同时为1 
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_RWCheck()
{

  u8 dat;
  u8 TimeOutCnt;
  
      do{	  			 
	        LCM_CD_HIGH();			 
	        LCM_RD_LOW();		
		 LCM_RDelay();		 
	        dat = LCM_ReadDatabusByte();		 
		LCM_RD_HIGH();		
	        dat=0x03&dat;	/*STA0, STA1是否准备好*/			
		TimeOutCnt++;	
		if(TimeOutCnt >= CHECK_TIME_OUT)
			break;
	        
        }while(dat!=0x03);

}
/*******************************************************************************
* Function Name  : LCM_AutoRCheck
* Description    : 判断状态位STA2的子程序（数据自动读状态），
*			   该位在数据自动读操作过程中取代STA0和STA1有效。
*			   在连续读过程中每读一次之前都要确认STA2=1
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_AutoRCheck()
{
	u8  dat;
	u8 TimeOutCnt;
    do{

        LCM_CD_HIGH();

        LCM_RD_LOW();
		
	LCM_RDelay();	
	 
        dat = LCM_ReadDatabusByte();
		
		LCM_RD_HIGH();
		
        dat = 0x04 & dat;		/*STA2是否准备好*/
		
		TimeOutCnt++;	
		if(TimeOutCnt >= CHECK_TIME_OUT)
			break;
		
        }while(dat==0x00);
}
/*******************************************************************************
* Function Name  : 数据自动写状态检查
* Description    : 判断状态位STA3子程序（数据自动写状态）
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/

void LCM_AutoWCheck()
{

	u8 dat;
	 u8 TimeOutCnt;
    do{		
			 
		LCM_CD_HIGH();
		LCM_RD_LOW();	
		 
		LCM_RDelay();		
		 
		dat= LCM_ReadDatabusByte();

		LCM_RD_HIGH();
			
		dat = 0x08 & dat;	/*STA3是否准备好*/
				
		TimeOutCnt++;	
		if(TimeOutCnt >= CHECK_TIME_OUT)
			break;
		}while(dat==0x00);
	
}
/*******************************************************************************
* Function Name  : 读数据
* Description    : 
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/

u8  LCM_ReadDataByte( void )
{
	u8 dat;
	
	LCM_RWCheck();	
	LCM_CD_LOW();		
	LCM_RD_LOW();
	LCM_WDelay();		
	dat = LCM_ReadDatabusByte();	
	LCM_RD_HIGH();
	
	return (dat);
	
}

/*---------------------------------------------------------------------*/
/*------输入/出函数,与T6963通讯--------------------------------*/
/*---------------------------------------------------------------------*/
/*******************************************************************************
* Function Name  : LCM_WriteData
* Description    :  向数据口发Data
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_WriteData(u8 dat) 
{

	LCM_RWCheck();	
	LCM_CD_LOW();
	LCM_RD_HIGH();		
	LCM_WriteDatabusByte(dat);		
	LCM_WR_LOW();
	LCM_WDelay();
	LCM_WR_HIGH();	
}
/*******************************************************************************
* Function Name  : LCM_WriteCmd1
* Description    : 写有 1 个参数命* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_WriteCmd1(u8 command) 
{ 

	LCM_RWCheck(); 	
	LCM_CD_HIGH();		
	LCM_WriteDatabusByte(command);		
	LCM_WR_LOW();	
	LCM_WDelay();	
	LCM_WR_HIGH();
}

/*******************************************************************************
* Function Name  :LCM_WriteCmd2
* Description    : 写有 2 个参数命令
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/

void LCM_WriteCmd2(u8 dat, u8 command) 
{ 

	LCM_WriteData(dat); 
	LCM_WriteCmd1(command); 
	
}
/*******************************************************************************
* Function Name  : LCM_WriteCmd3
* Description    : 写有 3 个参数命令
* Input            : data1  :  参数1
*			 : data2 : 参数2
*			 : command: 命令
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_WriteCmd3(u8 data1, u8  data2, u8 command) 
{ 

	LCM_WriteData(data1);
	LCM_WriteData(data2); 
	LCM_WriteCmd1(command);
	
}
/*******************************************************************************
* Function Name  :LCM_ShowChar
* Description    : 显示8*16字符（8列16行）（图形显示方式）
* Input            : lin : 0 -3 ;
*			: column : 0 --;
			: ch : 字符代码库(标准ASCII 码)
* Output         : None
* Return         : None
*******************************************************************************/
#if 1
void LCM_ShowChar(u8 lin, u8 column, u8 ch)
{
	u8 i;
	u8 dat;
	u32 StartAddr;
	u8  k ;
	
	while(column>29)
	{
	     column=column-30;
	     lin=lin+1;
	}
	if (lin>3)  
	  return;
	//ASClen = sizeof(ASC_816)/sizeof(ASC_816[0]);
	
	for(k=0; k<ASCTable816Len ; k++)
	{
		if( ch == ASC_816[k].Index[0] )
			break;
	}
	if(k>=ASCTable816Len)
		return;	
	StartAddr=16*lin*LCM_COL_CHAR +  column;        //定位起始行
	for( i=0; i<16; i++ )
	{	
		dat = ASC_816[ k ].Msk[ i ] ;
		LCM_WriteCmd3( (u8)(StartAddr), (u8)(StartAddr>>8), 0x24 ); /* set address */
		LCM_WriteCmd2( dat, 0xc4 );

		StartAddr +=  LCM_COL_CHAR;	/*换行*/
		
	}
}

#endif
/*******************************************************************************
* Function Name  :LCM_ShowHZ
* Description    : 显示一个汉字(16*16点阵) (图形方式显示)
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/
/*----------------------------------------------------------------------------------------------*/
/*
*
*lin:行(0-3), column: 列(0-15)
*hzcode: 汉字代码(自定义的)
*/
#if 1
void LCM_ShowHZ(u8 lin, u8 column, u8 *hz)
{
	u8 i;
	u32 StartAddr;
	u16  k ;
	//u16 HzTableLen = sizeof(HzTable1616)/sizeof(HzTable1616[0]);
	while(column > 29)
	{
	     column=column-30;
	     lin=lin+1;
	}
	
	//if (column<0) 
	//	column=0;
	
	if (lin>3) 
	  return;

	for(k=0; k<HZTable1616Len; k++)
	{
		if( (hz[0] == HzTable1616[k].Index[0] )&& (hz[1] == HzTable1616[k].Index[1]))
			break;
	}
	
	if(k>=HZTable1616Len)
		return;
	//StartAddr = (lin<<8)+column; /*	定位起始行(括号中相当于lin*ColumnChar*16)		*/
	
	StartAddr=16*lin*LCM_COL_CHAR +  column;        //定位起始行
	
	for(i=0; i<16; i++)
	{
		LCM_WriteCmd3( (u8)(StartAddr), (u8)(StartAddr>>8), 0x24);
		LCM_WriteCmd2( HzTable1616[k].Msk[i*2], 0xc0); 	/*左半部 地址加一*/
		LCM_WriteCmd2( HzTable1616[k].Msk[i*2+1], 0xc4); 	/*右半部 字模地址加一*/	

		StartAddr += LCM_COL_CHAR ;	/*换行*/
	}
}
#endif
void LCM_DispStr(u8 lin, u8 column, u8 *p, u8 size)
{
	
	u8  j  , k ;
	while(column > 29)
	{
		column=column-30;
		lin=lin+1;
	}
	
	if ( lin > 3 )  
	  return;		/*看首行是否超出屏幕*/
	
	for (k=column, j=0; j < size ; j++)
	{
		if(p[j] <= 0 ) /* p[j] == "\0"  */
			return ;
		
		else if(p[j] < 128)	
		{	
		
			LCM_ShowChar( lin, k, p[j]);	/*字母  ascii码表从0x20开始*/	
				
		}
		else /*汉字 , 汉字从0x80开始，包括0x80*/
		{
		
			LCM_ShowHZ( lin, k , &p[j]);
			j++ ;
			k++;
		}	
		k++ ;

	}
}
/*******************************************************************************
* Function Name  :LCM_ReverseShowChar
* Description    : 反显一个字符
* Input            :* Input            : lin : 0 -3,
*			: column : 0 --
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_ReverseShowChar(u8 lin,u8 column)
{

	u8 i;
	u8 dat;
	u32 StartAddr;

	StartAddr=(lin<<8) +column; /*定位起始行*/

	for(i=0;i<16;i++)
	{
		LCM_WriteCmd3( (unsigned char)(StartAddr), (unsigned char)(StartAddr>>8), 0x24); /*set address*/
		LCM_WriteCmd1( 0xc5 );		 /*数据一次读，地址不变*/
		dat = LCM_ReadDataByte(); 	/*读入数据*/
		dat = ~dat; 	/*取反*/
		LCM_WriteCmd2( dat, 0xc4); 	/*送回*/

		StartAddr=StartAddr+ LCM_COL_CHAR ;
	}
	
}
/*******************************************************************************
* Function Name  :LCM_ReverseShowHZ
* Description    : 反显一个汉字
* Input            : lin : 0 -3,
*			: column : 0 --
* Output         : None
* Return         : None
*******************************************************************************/
//lin:行(0-3), column: 列(0-15)
void LCM_ReverseShowHZ(u8 lin , u8 column)
{

	LCM_ReverseShowChar(lin,column);
	LCM_ReverseShowChar(lin,column+1);
	
}
/*******************************************************************************
* Function Name  :LCM_ReverseShowLine
* Description    : 反显一行汉字
* Input            : lin : 0--3 
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_ReverseShowLine(u8 lin)
{

	u8 column;
	if (lin>3)  
		return;
	for(column=0; column< LCM_COL_CHAR; column++) 
		LCM_ReverseShowChar(lin,column);

}
/*******************************************************************************
* Function Name  :LCM_ClearScreen
* Description    : //清屏
* Input            : ram  0 --0x2000
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_ClearScreen(u16 ram)
{

	u32 i;
	// 清显示 RAM 区 0000h--2000h (8k)
	LCM_WriteCmd3(0x00,0x00,0x24); /*设置指针地址0000H*/

	LCM_WriteCmd1(0xb0); /*设置自动写状态*/
	
	for(i=0;i<ram ;i++) 
	{
		LCM_AutoWCheck();
		LCM_WriteData(0x00);
	} // data=0;
	LCM_AutoWCheck();/*是否需要？？*/
	LCM_WriteCmd1(0xb2); /* 自动写结束*/
	
}
/*******************************************************************************
* Function Name  :LCM_FillScreen
* Description    : data
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_FillScreen(u8 data)
{
	u32 i;
	u8 temp = data;
	// 清显示 RAM 区 0000h--2000h (8k)
	LCM_WriteCmd3(0x00, 0x00, 0x24); /*设置指针地址0000H*/

	LCM_WriteCmd1(0xb0); /*设置自动写状态*/
	
	for(i=0;i<0x2000;i++) 
	{
		LCM_AutoWCheck();
		LCM_WriteData(temp);
	} // data=0;
	LCM_AutoWCheck();/*是否需要？？*/
	LCM_WriteCmd1(0xb2); /* 自动写结束*/
}
/********************************************************************************
函数原型: void LCM_DrawDot(x,y)
功     能; T6963屏上打点
入口参数: 横坐标（x），枞坐标（y）
出口参数: 
********************************************************************************/ 
void LCM_DrawDot( u8 x, u8 y, u8 mode )
{

	u8 dat11,dat22;
	u8 n,t;

	dat11=(y*32)%256 +x/8; 
	dat22=(y*32)/256;
   
	LCM_WriteCmd3(dat11,dat22,0x24);
	if(mode)  
		n=0xf8;
	else       
		n=0xf0; 
	t=n|((~(x%8))&0x07);
	
	LCM_WriteCmd1(t);
	
}
//-------------------------------------------------------------20081108add-----start---

//-------------------------------------------------------------20081108add-----end---
/*******************************************************************************
* Function Name  :Init_LCM
* Description    : 初始化LCD
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/
void Init_LCM( void )
{

	Init_LCMGpio( ) ;		/*初始化GPIO 口*/
	LCM_Reset();
	
	LCM_CD_HIGH();
	LCM_WR_HIGH();
	LCM_RD_HIGH();
	LCM_CE_LOW() ;
	LCM_FS_LOW();

	LCM_WriteCmd3( 0x00, 0x00, 0x40 );   			/*文本首地址*/
	LCM_WriteCmd3( LCM_COL_CHAR, 0x00, 0x41 );   /*文本宽度设置*/
	LCM_WriteCmd3( 0x00, 0x00 , 0x42 ); 			/*设置图形显示区域首地址GraphAddr*/
	LCM_WriteCmd3( LCM_COL_CHAR , 0x00 , 0x43 ); /*设置图形显示区域宽度: 0x1e = 240/8	fs = 8*8 */

	LCM_WriteCmd1(0xa7);	 /*设置光标形状 cursor size 8x8（好像无用）*/
	LCM_WriteCmd1(0x80); 	/*设置显示方式: CGROM方式 文本\图形 "或"*/
	LCM_WriteCmd1(0x98); 	/*设置显示开关: 1001 1000 只开图形显示*/

	LCM_ClearScreen(0x2000); /*clear 8k ram*/
	
}

#if 1
  /*******************************************************************************
* Function Name  :LCM_UpdataDisBuf
* Description    : LCM 填充lcm 缓冲区,
				左屏按8个汉字算，右边按7个汉字算,	显示不够填充空白；
* Input            : MI : 将要显示的菜单
* Output         : None
* Return         : None
*******************************************************************************/
void LCM_UpdataDisBuf( struct  MenuItem *MI  )
  {
  
  	u8 *sbuf = &DisBuf[0];
	//u8 *bufend = &DisBuf[DISBUF_SIZE];
	struct  MenuItem *m = MI;	/*将要显示的菜单*/       
	u8 StrSize; 		/*屏要显示str size*/
	u8 tMenuCount = m->MenuCount ;/**/
	u8 i ;
	u8 TPositionXY = 0 ;
	//LCM_ClearScreen(0x2000); /*clear 8k ram*/
	bmemset( sbuf ,  StrNull ,  DISBUF_SIZE );/*清空缓冲区，防止不显示的地方保留以前的状态*/

	//-LCM line0-3-----------------------------
	for( i = 0 ; i < tMenuCount ; i ++ )
	{
	
		TPositionXY = m->PositionY * LCM_COL_CHAR + m->PositionX  ;		
		StrSize =  m->DisplayStringSize ;			
		bmemcpy(sbuf + TPositionXY , m->DisplayString, StrSize) ;		
		m++;	
	}	
  }

#endif
  /*******************************************************************************
* Function Name  :LCM_DisplayFullScreen
* Description    : LCM 整屏显示，buf 的尺寸为 LCM_COL_CHAR*LCM_LINE_CHAR
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/

void LCM_DisplayFullScreen(u8 * buf )
{
	LCM_DispStr( LCM_DIS_LINE0 , 0 , buf,  					LCM_COL_CHAR ); /*LCM line 0*/
	LCM_DispStr( LCM_DIS_LINE1 , 0 , buf + LCM_COL_CHAR ,  	LCM_COL_CHAR ); /*LCM line 1*/
	LCM_DispStr( LCM_DIS_LINE2 , 0 , buf + 2* LCM_COL_CHAR ,  LCM_COL_CHAR ); /*LCM line 2*/
	LCM_DispStr( LCM_DIS_LINE3 , 0 , buf + 3* LCM_COL_CHAR ,  LCM_COL_CHAR ); /*LCM line 3*/
}


void LCM_ShowMenu( struct  MenuItem *MI  , u8 * dbuf  )
{

	LCM_UpdataDisBuf( MI );
	LCM_DisplayFullScreen(  dbuf );
	
}

void Init_LCMGUI( void )
{

	Init_LCM();
	MenuInit( CHINESE );
	  
}

/*******************************************************************************
* Function Name  : int2char
* Description    : This function convertes a int to a string
* Input          : u16 value
* Output         : None
* Return         : None
*******************************************************************************/
u8 * int2char(u16 value)
{ 

  u8 i;
  u8 bValue;
  u16 temp;  
  
  temp = 1000;  
  for (i=0;i<4;i++)
  {
	bValue = (u8)(value/temp);
	text[i] = (u8)(bValue+0x30);
    
	value %= temp;
	temp /= 10;                
  }    
  return(text);
  
}

#ifdef LCM_DUG
//测试程序
void LCM_test(void)
{ 
#if 1
      u8 status =0  ; 
	Init_LCM();    

      MenuInit(CHINESE);
	LCM_ShowMenu( MenuPoint , DisBuf) ;
	while(1)
	{	

		switch(status)
		{
			case 0:
				MenuPoint = MainMenu;
				status++;
				break;
			case 1:
				MenuPoint = FeedMediumMenu21 ;
				status++;
				break;
			case 2:
				MenuPoint = PrintSetMenu22;
				status++;
				break;
			case 3:
				MenuPoint = SysInfoMenu27 ;
				status = 0;
				break;
			default:
				MenuPoint = MainMenu;
				status = 0;
				break;
							
		}
		
		LCM_ShowMenu( MenuPoint , DisBuf) ;
		Delaynus(1000000);
		///LCM_ClearScreen(0x2000); 
#endif		
	}
    #if 0
	while(1)
	{
		
		//-----lcd gpio test----------
		LCM_CD_HIGH();
		LCM_CD_LOW();
		
		LCM_WR_HIGH();
		LCM_WR_LOW();
		
		LCM_RD_HIGH();
		LCM_RD_LOW();

		LCM_CE_HIGH();
		LCM_CE_LOW();

		LCM_FS_HIGH();
		LCM_FS_LOW();

		GPIO_SetBits( GPIO_LCM_DATA_DIR_EN,  LCM_DATA_DIR_PIN) ;// LCM_DATA_IN_MODE
		GPIO_ResetBits( GPIO_LCM_DATA_DIR_EN,  LCM_DATA_DIR_PIN) ;// LCM_DATA_IN_MODE
		
		GPIO_SetBits( GPIO_LCM_DATA_DIR_EN, LCM_DATA_OUT_EN_PIN ); //ENABLE hc245	
		GPIO_ResetBits( GPIO_LCM_DATA_DIR_EN, LCM_DATA_OUT_EN_PIN ); //ENABLE hc245	
		
		LCM_WriteDatabusByte(0xff);
		LCM_WriteDatabusByte(0);

		LCM_ReadDatabusByte();

		
	} 	  	
	#endif

}
#endif //#ifdef LCM_DUG


#endif//#if LCM_GUI_EN>0

