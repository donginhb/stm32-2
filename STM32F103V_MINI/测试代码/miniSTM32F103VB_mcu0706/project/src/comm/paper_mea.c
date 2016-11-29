//paper_mea.c

#include "includes.h"

#if PAPER_MEA_EN>0

static  PrintPaper_t PrintPaperStructure;

/*******************************************************************************
* Function Name  : Init_PaperGpio
* Description    : None
* Input             :None 			    
* Output         : None
* Return         : None
*******************************************************************************/
void Init_PaperGpio(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
	//#############################################
	  /* Configure IO connected to buz *********************/
	  /* Enable GPIO_PAPER_SENSOR clock */
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_PAPER_SENSOR , ENABLE );

	  GPIO_InitStructure.GPIO_Pin = PAPER_SENSOR_MEA_WITH_PIN | PAPER_SENSOR_SPY_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_PAPER_SENSOR;
	  GPIO_Init( GPIO_PAPER_SENSOR , &GPIO_InitStructure );
  	
}
/*双边沿测试纸边中断*/
void Init_PaperExtiSet( FunctionalState NewStatus )
{
	EXTI_InitTypeDef EXTI_InitStructure;

	if (NewStatus != DISABLE)
	{
		/* Connect Key Button EXTI Line to Key Button GPIO Pin */
		GPIO_EXTILineConfig( GPIO_PortSourceGPIOA,  PAPER_SENSOR_MEA_WITH_PINSource);

		/* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
		EXTI_InitStructure.EXTI_Line = PAPER_SENSOR_MEA_WITH_PIN_EXTI_Line ;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling ;
	}
	
	EXTI_InitStructure.EXTI_LineCmd = NewStatus;
	EXTI_Init(&EXTI_InitStructure);
	
}
	
void Init_PaperExtiNVIC( FunctionalState NewStatus )
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
    if (NewStatus != DISABLE)
    {
		 /* Enable the EXTI9_5 Interrupt PA0*/
		NVIC_InitStructure.NVIC_IRQChannel = PAPER_SENSOR_MEA_WITH_PIN_EXTI_IRQChannel ;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2 ;
    	}
	NVIC_InitStructure.NVIC_IRQChannelCmd = NewStatus;
	NVIC_Init(&NVIC_InitStructure);
	
}
void PrintPaperStructure_Init(void)
{
	 PrintPaper_t *pp = &PrintPaperStructure;
	pp->FarDist = pp->NearDist = 0;
	pp->MeaPaperEdgeFlag = FALSE;
	pp->With = 0 ;
}
void PaperMeaWithExtiSet( FunctionalState NewStatus )
{
	Init_PaperExtiSet( NewStatus);
	Init_PaperExtiNVIC(NewStatus);
}
#define PAPER_WITH_FAR_NEAR_SIMPLE   6 
static  u16 Ppbuf[PAPER_WITH_FAR_NEAR_SIMPLE];
static  u8 PpIndex = 0 ;
void Init_PaperMea(void)
{

	Init_PaperGpio();
	PaperMeaWithExtiSet(DISABLE);	
	PrintPaperStructure_Init();
	PaperMeaPaperEdgeFlagClear();
	bmemset((u8 * )&Ppbuf, 0x00, PAPER_WITH_FAR_NEAR_SIMPLE*2);
	PpIndex = 0 ;
	
}

//static bool bIs_First_Measurement = TRUE;
void PaperMeaReset(void)
{
	//bIs_First_Measurement = TRUE;
	//PpIndex = 0 ;
	Init_PaperMea();
	//bmemset((u8 * )&Ppbuf, 0x00, PAPER_WITH_FAR_NEAR_SIMPLE*2);
}
/*
*采集纸边位置
*void EXTI9_5_IRQHandler(void)中调用
*/
void PaperEdgeGet(void)
{	
	vu16 CurDist = 0 ;
	CurDist = ENC_Timer_Position_Get();
		
	if(CurDist > INK_STOP_LEN_EDGE) /*大于墨盒长度*/
	{
		PrintPaperStructure.MeaPaperEdgeFlag = TRUE;	
		Ppbuf[PpIndex] = CurDist; 		
					
		PpIndex++;
		 if( PpIndex>=( PAPER_WITH_FAR_NEAR_SIMPLE+1 ) )
			PpIndex = 0 ;
	}
	
}

/*清除测到纸边标志*/
void PaperMeaPaperEdgeFlagClear(void)
{

	PrintPaperStructure.MeaPaperEdgeFlag = FALSE ;
	
}
/*是否侧到纸边*/
bool PaperMeaEdge_IsElapsed(void)
{

	if( PrintPaperStructure.MeaPaperEdgeFlag == TRUE)		
	{	
		//PrintPaperStructure.MeaPaperEdgeFlag = FALSE ;
		return TRUE;
	}
	return FALSE;
}
#if 0
void PaperNoteEdgeNear(void)
{
	PrintPaperStructure.NearDist = PrintPaperStructure.CurDist;
}
void PaperNoteEdgeFar(void)
{
	PrintPaperStructure.FarDist = PrintPaperStructure.CurDist;
}
#endif
/*计算纸宽*/
bool PaperCalWith(void)
{
	//u16 NearDist = 0 , FarDist = 0 ;
        #if 1
	PrintPaperStructure.NearDist = (u32)((Ppbuf[0]+Ppbuf[1]+Ppbuf[2])/3);
	PrintPaperStructure.FarDist = (u32)((Ppbuf[3]+Ppbuf[4]+Ppbuf[5])/3);        
	#endif
	
        
	if(PrintPaperStructure.FarDist - PrintPaperStructure.NearDist >0)
	{
		PrintPaperStructure.With =(long long )(PrintPaperStructure.FarDist - PrintPaperStructure.NearDist)*254/(ENCODER_PPR_LINE*10);
		//bmemset((u8 * )&Ppbuf, 0x00, PAPER_WITH_FAR_NEAR_SIMPLE*2);
                return TRUE;
	}
	
        return FALSE;
}
#if 0
/*纸张探测，有纸和无纸*/
PaperFlag PaperMeaCheck(void)
{

	return(PaperFlag)GPIO_ReadInputDataBit(GPIO_PAPER_SENSOR , PAPER_SENSOR_MEA_WITH_PIN);

}
#endif
/*纸张探测，有纸和无纸*/
PaperFlag PaperSpyCheck(void)
{

	return(PaperFlag)GPIO_ReadInputDataBit(GPIO_PAPER_SENSOR , PAPER_SENSOR_SPY_PIN);

}
/*获得纸宽*/
u16 PaperWithGet(void)
{
	return PrintPaperStructure.With;
}

#endif //#if PID_REG_EN>0

