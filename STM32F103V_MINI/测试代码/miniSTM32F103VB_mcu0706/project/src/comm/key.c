//file:key.c
/******************************
******************************/

#include "includes.h"

//#define KEY_TIME_SCAN     1

#if KEY_EN>0

static vu8  KeyVal = ERR_KEYVALUE;

void Key_GpioSetForRowScan( void);
/*******************************************************************************
* Function Name  : Key_GpioInit
* Description    : 
* Input             : 			    
* Output         : None
* Return         : None
*******************************************************************************/
void Key_GpioInit( void )
{

	  /* ------Enable GPIO_key2 * 4 clock ---------------------*/
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_KEY  , ENABLE );
	  /*----- Configure IO connected to key2 * 4 ----------------*/
	  Key_GpioSetForRowScan();
	
}
#endif //	#if KEY_EN>0

void Key_NVICInit( void )	
{

	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the TIM3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = KEYSCAN_IRQChannel ; //TIM3_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
	
}
#define   SAME_KEY_SCAN_TIME_1500MS   (u16)(1500/TIM_CCR_VAl_KEY_SCAN)
#define  SAME_KEY_SCAN_TIME 			SAME_KEY_SCAN_TIME_1500MS	  	/*相同键连击间隔时间*/

/*******************************************************************************
* Function Name  : Key_GpioInit
* Description    : 
* Input             : 			    
* Output         : None
* Return         : None
*******************************************************************************/
void Key_ScanTimeInit( void )
{

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	

	  /* TIM clock enable */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_KEY_TIM, ENABLE);

  /* ---------------------------------------------------------------
    TIM Configuration: Output Compare Inactive Mode:
    TIMCLK = 36 MHz, Prescaler = 35999, TIM counter clock = 10 KHz
    TIM update Period = ARR / TIM3 counter clock = 1 s 
    CC1 OC period = 10ms
  --------------------------------------------------------------- */
  /* Time base configuration tim counter clock*/
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = 35999;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(KEY_TIMER, &TIM_TimeBaseStructure);
 
#if 1
  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM_CCR_VAl_KEY_SCAN;
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(KEY_TIMER, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig( KEY_TIMER, TIM_OCPreload_Disable );  
  #endif
  
#if 1
  /* Output Compare Active Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM_CCR_VAl_SYS_POS_CTR;

  TIM_OC2Init(POS_TIMER, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(POS_TIMER, TIM_OCPreload_Disable);
  #endif
  
#if 1
  /* Output Compare Active Mode configuration: Channel3*/
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM_CCR_VAl_P_MOTOR_SENSOR_SAMPLEING;

  TIM_OC3Init(PM_TIMER, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(PM_TIMER, TIM_OCPreload_Disable);
  #endif
  
  /* TIM IT enable */
  TIM_ITConfig(KEY_TIMER, TIM_IT_CC_KEY| TIM_IT_CC_POS|TIM_IT_CC_PM , ENABLE );
// | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);

  /* TIM enable counter */
 TIM_Cmd(KEY_TIMER, ENABLE);
 // TIM_Cmd(KEY_TIMER, DISABLE);	/*开关被MC_ServoCapPosFunSw() 函数控制*/
  
}


void Init_KeyPosPMTime(void)
{
	Key_NVICInit();	
	Key_ScanTimeInit( ) ;
	//TIM_Cmd( KEY_TIMER, ENABLE );  
}

#if KEY_EN>0

/*******************************************************************************
* Function Name  : KeyScan
* Description    : 
* Input             : 			    
* Output         : None
* Return         : None
*******************************************************************************/
void Init_Key( void )
{
	
	Key_GpioInit( );
	
}

void Key_GpioSetForRowScan( void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	  /*----- Configure IO connected to key2 * 4 ----------------*/
	
	GPIO_InitStructure.GPIO_Pin = KEY_PIN2 |KEY_PIN3 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIO_KEY , &GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = KEY_PIN4 |KEY_PIN5 | KEY_PIN6 |KEY_PIN7  ;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU ; //GPIO_Mode_Out_PP ;/*pull up input*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init( GPIO_KEY , &GPIO_InitStructure );

	//gpio**********************
	GPIO_ResetBits(GPIO_KEY , KEY_PIN2);	/* Low*/
	GPIO_ResetBits(GPIO_KEY , KEY_PIN3);  /* Low*/
	
}

void Key_GpioSetForColScan(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	 GPIO_InitStructure.GPIO_Pin = KEY_PIN2 |KEY_PIN3 ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 	/*pull up input*/
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init( GPIO_KEY , &GPIO_InitStructure );

	  GPIO_InitStructure.GPIO_Pin = KEY_PIN4 |KEY_PIN5 | KEY_PIN6 |KEY_PIN7  ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	  GPIO_Init( GPIO_KEY , &GPIO_InitStructure );
	
	//**********************************
  	GPIO_ResetBits(GPIO_KEY , KEY_PIN4);
	GPIO_ResetBits(GPIO_KEY , KEY_PIN5);
	GPIO_ResetBits(GPIO_KEY , KEY_PIN6);
	GPIO_ResetBits(GPIO_KEY , KEY_PIN7);	
	
}
/*******************************************************************************
* Function Name  : KeyScan
* Description    : 
* Input             : 			    
* Output         : None
* Return         : None
*other:
*scan order: row-->col
*******************************************************************************/
u8  KeyScan( void )
{

    u8 ttkeyval = ERR_KEYVALUE ;
	//-----------------------------------------------------------------
	//scan row
	{
		if( !GPIO_ReadInputDataBit(GPIO_KEY , KEY_PIN4) )
			ttkeyval = 0x40;
		
		else if(  !GPIO_ReadInputDataBit(GPIO_KEY , KEY_PIN5) )
			ttkeyval = 0x50;
		
		else if(  !GPIO_ReadInputDataBit(GPIO_KEY , KEY_PIN6) )
			ttkeyval = 0x60;
		
		else if(  !GPIO_ReadInputDataBit(GPIO_KEY , KEY_PIN7) )
			ttkeyval = 0x70;
		
		else 
			return  ERR_KEYVALUE ; 	//EER 
		
	}
	//----scan col-----------------------------------------------------	
	 Key_GpioSetForColScan();
	
	{
		
		if( !GPIO_ReadInputDataBit(GPIO_KEY , KEY_PIN2) )
			ttkeyval  |= 0x02;
		else if( !GPIO_ReadInputDataBit(GPIO_KEY , KEY_PIN3) )
			ttkeyval  |= 0x03;
		else 
			return  ERR_KEYVALUE  ;		//EER 
		
	}	
	//----init gpio----for next key scan--------------------------------
	  Key_GpioSetForRowScan();
	//if( ttkeyval !=  ERR_KEYVALUE)
		
	return ttkeyval ;		
}

/*中断调用函数*/
void KeyScanBack(void)
{	
	static  u8  KeyValk_1 = 0 ; 	/*上次按键键值*/
	static  u8 KeyValk = ERR_KEYVALUE ;		/*本次按键键值*/
	static  u16 KeyValSameCnt = 0 ;/*相同按键连击计数器*/
	#if 1 //KEY_TIME_SCAN> 0	
		   KeyValk_1 = KeyValk;
			/*采集键值*/			
			KeyValk =  KeyScan();	
			/*键值处理*/
			 if( (KeyValk_1 == KeyValk)&&( KeyValk !=  ERR_KEYVALUE) )/*防抖*/
			 {			 	
				 KeyValSameCnt ++;
				 if(KeyValSameCnt<=2*SAME_KEY_SCAN_TIME) /*单击*/
				{
					 if( (KeyValSameCnt == 1)||(KeyValSameCnt == SAME_KEY_SCAN_TIME)||(KeyValSameCnt == 2*SAME_KEY_SCAN_TIME) )/*按住一个键一秒以上认为连击*/
					 {
					 	KeyVal = KeyValk ;						
					 }
				 }
				 else if((KeyValSameCnt-2*SAME_KEY_SCAN_TIME )%20 ==0)/*按住一个按键3秒以后不放，就每隔20*10ms 认为连击*/
				{
					 KeyVal = KeyValk ;					
				}
				if(KeyValSameCnt>=U16_MAX)
				 	KeyValSameCnt = 2*SAME_KEY_SCAN_TIME;
			 }
			 else if(  ( KeyValk_1 != KeyValk ) )		/*抬起处理*/		 
			 {     
				 KeyValSameCnt = 0 ;
			 }	
                
	#endif		
}

u8 Key_ValGet(void)
{
	return (u8) KeyVal;
}
void Key_ValClear(void)
{
	KeyVal = ERR_KEYVALUE;
}
			  
void key_test( )
{
#if 0
	u8 KeyValTmp = ERR_KEYVALUE;
	while(1)
	{
#if 0
	//***test gpio********************
	GPIO_ResetBits(GPIO_KEY , KEY_PIN2);
	GPIO_ResetBits(GPIO_KEY , KEY_PIN3);
	GPIO_ResetBits(GPIO_KEY , KEY_PIN4);
	GPIO_ResetBits(GPIO_KEY , KEY_PIN5);
	GPIO_ResetBits(GPIO_KEY , KEY_PIN6);
	GPIO_ResetBits(GPIO_KEY , KEY_PIN7);
	
	GPIO_SetBits(GPIO_KEY , KEY_PIN2);
	GPIO_SetBits(GPIO_KEY , KEY_PIN3);
	GPIO_SetBits(GPIO_KEY , KEY_PIN4);
	GPIO_SetBits(GPIO_KEY , KEY_PIN5);
	GPIO_SetBits(GPIO_KEY , KEY_PIN6);
	GPIO_SetBits(GPIO_KEY , KEY_PIN7);
#else
 //****test key val***************
	#if KEY_TIME_SCAN> 0
		 KeyValTmp = KeyVal ;
	#else
       	 KeyValTmp = KeyScan();
	
	#endif
        if (KeyValTmp !=  ERR_KEYVALUE)
    	{
            switch( KeyVal )
    		{
                case KEY_LEFT1:
                                  KeyVal = 0 ;
            		break;
                case KEY_LEFT2:
                                    KeyVal = 0 ;
            		break;
                case KEY_LEFT3:
                                    KeyVal = 0 ;
            		break;
                case KEY_LEFT0:
                                    KeyVal = 0 ;
            		break;
                case KEY_RIGHT1:
                                    KeyVal = 0 ;
            		break;
                case KEY_RIGHT2:
                                    KeyVal = 0 ;
            		break;
                case KEY_RIGHT3:
                                    KeyVal = 0 ;
            		break;
                case KEY_RIGHT0:
                                    KeyVal = 0 ;
            		break;
                default :
                    break;//Err key value
        			
    		}
		KeyValTmp = KeyVal = ERR_KEYVALUE ;
    		
    	}
  #endif
	}
	
#endif
}

#endif //#if KEY_EN>0

