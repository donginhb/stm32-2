/*******************************************************************************
*file: MC_servo_pos_ctr.c
*�������� : ��������Ҫ����ƶ�λ�ƿ���
*
*******************************************************************************/
#include "includes.h"

#if SERVO_POS_CTR_EN > 0

#define SPORT_CTR_TIME_1ms    (u16)(1000 -1)
#define SPORT_CTR_TIME_2ms    (u16)(2000 -1)

#define SPORT_CTR_TIME  SPORT_CTR_TIME_1ms

/*��׽��դ���ܿ���*/
void MC_ServoCapPosFunSw(FunctionalState NewState)
{
	TIM_Cmd(POS_TIMER, NewState);  
	//TIM_ITConfig(POS_TIMER, TIM_IT_CC_POS , NewState );
}
#if 0
/*******************************************************************************
* Function Name  : MC_ServoCapPos_NVICInit
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MC_ServoCapPos_NVICInit( void )
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
	  /* Enable the TIM2 Update Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = CAP_POS_IRQChannel;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	  
}

/*******************************************************************************
* Function Name  : MC_ServoCapPos_TimInit
* Description    : TIM2 init  counter
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MC_ServoCapPos_TimInit( void )
{
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//	TIM_OCInitTypeDef  TIM_OCInitStructure;
	  /* ---------------------------------------------------------------
    CAP_POS_TIMER Configuration: generate 4 signals with 4 different delays:
    CAP_POS_TIMER = 36 MHz, Prescaler = 35999, CAP_POS_TIMER counter clock = 1 KHz   
  --------------------------------------------------------------- */
	   /* TIM2 clock source enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAP_POS_TIM ,  ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = SPORT_CTR_TIME;
  	TIM_TimeBaseStructure.TIM_Prescaler = 35;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(CAP_POS_TIMER, &TIM_TimeBaseStructure);

	TIM_ARRPreloadConfig(CAP_POS_TIMER, ENABLE);
	TIM_ITConfig(CAP_POS_TIMER, TIM_IT_Update, ENABLE);

	MC_ServoCapPosFunSw( DISABLE);  
  
}

//static volatile PosCapType_t PosCapType = CAP_PAPER_EDGE ; 

/*��ʱ��׽��դ���ж�*/
void CAP_POS_IRQHandler(void)
{
	if(hServoCarPosDelayNnms !=0)
		hServoCarPosDelayNnms--;
	
	MC_ServoCarPosCtr(&ServoSpeedCtrStructure,&PID_Speed_InitStructure,&ServoCarSportStructure);
	
	//MC_SpdCarSafeSpd(&ServoSpeedCtrStructure,&PID_Speed_InitStructure,&ServoCarSportStructure);

	CAP_POS_TIMER->SR = (u16)~TIM_IT_Update;	//TIM_ClearITPendingBit(CAP_POS_TIMER, TIM_IT_Update);	
	
}
#endif
static vu16 hServoCarPosDelayNnms = 500;
/*�жϵ���*/
void MC_PosCarBack(void)
{
	if(hServoCarPosDelayNnms !=0)
		hServoCarPosDelayNnms--;
	
	MC_ServoCarPosCtr(&ServoSpeedCtrStructure,&PID_Speed_InitStructure,&ServoCarSportStructure);
	
	//MC_SpdCarSafeSpd(&ServoSpeedCtrStructure,&PID_Speed_InitStructure,&ServoCarSportStructure);

	//CAP_POS_TIMER->SR = (u16)~TIM_IT_Update;	//TIM_ClearITPendingBit(CAP_POS_TIMER, TIM_IT_Update);	
	
}

#define CNT_SPEED_DEC_L_DEFAULT 	 1000	  /*���ٳ���*/
#define BRAKE_LEN_DEFAULT  			 25 		/*ɲ������*/

void MC_ServoPosDeInit(void )
{
	ServoCarPosCtr_t  *c = &ServoCarSportStructure ;

	c->RasterLen = 0 ;
	c->CurPos =  0 ;
	c->PrintOriginLen = 0 ;
	c->PriPicToPriOriginLen = 0 ;
	c->SpdDecL = CNT_SPEED_DEC_L_DEFAULT ;
	c->SpdIncL = CNT_SPEED_DEC_L_DEFAULT ;
	
	c->FarErr = 0 ;
	c->NearErr = 0 ;
	
	c->Dir  = GO_NEAR_DIR ;

	
	c->PrintOriginLen = PRINT_ORIGIN_DEFAULT_LEN_EDGE + ORIGIN_TO_INK_STOP_NEAR_LEN_EDGE;
	c->SafeDisFar = PRINT_AREA_LEN_EDGE + ORIGIN_TO_INK_STOP_NEAR_LEN_EDGE + INK_STOP_LEN_EDGE + (u16)FAR_SPEED_UP_AREA_LEN_EDGE/2;
	c->SafeDisNear = ORIGIN_TO_INK_STOP_NEAR_LEN_EDGE + 15000;
	
	c->SportMode = SPORT_WAIT;
	//MC_ServoCapPos_NVICInit();
	//MC_ServoCapPos_TimInit();
	
}

/*������µ�ǰС��λ��*/
u16 MC_PosCarCurPosGet(void)
{
			
	return ENC_Timer_Position_Get();	
	
}
/*С���Ƿ��ƶ����*/
/*******************************************************************************
* Function Name  : 
* Description    : None
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/
bool  MC_ServoCarPosChangeCheck( void )
{
	//ServoCarPosCtr_t  *c = &ServoCarSportStructure;
	static u16  pk, pk_1, pk_2  ;/*�ϴμ��С��λ��*/
	pk_2 = pk_1;
	pk_1 = pk;
	
	pk = MC_PosCarCurPosGet();//MC_ServoCurPosGet();
	
	
	if((pk_1 ==pk)&&( pk_2 == pk))		
		return TRUE;
	
	return FALSE;	
}


/*******************************************************************************
* Function Name  : 
* Description    : ī����īվ
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/
bool MC_ServoCarPosCarGoInkStop(ServoSpeedCtr_t * ServoSCP, PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos )
{
	PID_SpeedTYPEDEF *p = PID_Speed ;
	ServoCarPosCtr_t *c = CarPos ;
	ServoSpeedCtr_t *s =  ServoSCP;
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	u16 CurENC = 0 ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*��ʼ��--1*/
			//PID_SpeedRegAutoFun(DISABLE );
			MC_SpdCtrModeAutoFun( DISABLE );
			PID_SpeedRegFun(DISABLE);
		
			CurENC = MC_PosCarCurPosGet();
			if(CurENC > (ORIGIN_TO_INK_STOP_NEAR_LEN_EDGE+72) )/*����λ�ü��*/
			{
				MC_SpdCarDirSet(c , GO_NEAR_DIR);
				//MC_ServoCarPosDisSet(c , ENCODER_RASTER_T1T2_EDGE_NUM );
				MC_SpdCarSpdSet(p , S_GO_INK_STOP );
				TaskStatus = TASK_RUN;
			}
			else if(CurENC < (ORIGIN_TO_INK_STOP_NEAR_LEN_EDGE-72) )
			{
				MC_SpdCarDirSet(c , GO_FAR_DIR);
				//MC_ServoCarPosDisSet(c , ENCODER_RASTER_T1T2_EDGE_NUM );
				MC_SpdCarSpdSet(p , S_GO_ORIGIN );
				TaskStatus = TASK_RUN;
			}
			else
				TaskStatus = TASK_END ; //ack ok !	
				
			break;
			
		case TASK_RUN: 
			if(MC_SpdCarStartSpdup(s, p) == TRUE)		/*��������*/
			{
				TaskStatus = TASK_RUN1;
				TB_ServoCarPosDelayNms(5);
				//PID_SpeedRegFun(ENABLE);
			}

			break;
			
		case TASK_RUN1:
						
			if( TB_ServoCarPosDelayNms_IsElapsed( )==TRUE )
			{
								
				CurENC = MC_PosCarCurPosGet();
				if( (CurENC <= (ORIGIN_TO_INK_STOP_NEAR_LEN_EDGE+72) )&&(CurENC >= (ORIGIN_TO_INK_STOP_NEAR_LEN_EDGE-48) ) )/*����λ�ü��*/
				{	
					TaskStatus = TASK_RUN2 ; //ack ok !	
				}				
			}			

			break;

		case TASK_RUN2:
			
			if( MC_SpdCarStop( )== TRUE )
			{
				TaskStatus = TASK_END ; //ack ok !	
			}
			break;
			
		case TASK_END:/*ִ�����*/				
			
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
	
        if(TaskStatus==TASK_END)
        {	  
        	TaskStatus = TASK_INIT ; //ack ok !
		return TRUE;	
        }	
		
	return FALSE;/*������δִ����*/
	
}
/*******************************************************************************
* Function Name  : 
* Description    : ī����ԭ��, ȷ����ԭ���, ���κ�λ�ø���ī����
*ī����λ�ö�����, 
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/
bool MC_ServoCarPosCarGoOrgin(ServoSpeedCtr_t * ServoSCP, PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos )
{
	PID_SpeedTYPEDEF *p = PID_Speed ;
	ServoCarPosCtr_t *c = CarPos ;
	ServoSpeedCtr_t *s =  ServoSCP;
	
	static  TaskStatus_t  TaskStatus = TASK_INIT ;
	static u16 counter = 0 ;
	u16 CurENC = 0 ;
	static u16 TimeDelayCnt = 0 ;
	switch(TaskStatus)
	{
		case TASK_INIT:/*��ʼ��--1*/
			
			//PID_SpeedRegAutoFun(DISABLE );
			MC_SpdCtrModeAutoFun( DISABLE );
			PID_SpeedRegFun(DISABLE);
			
			MC_SpdCarDirSet(c , GO_NEAR_DIR);
			MC_SpdCarSpdSet(p , S_GO_ORIGIN );
			
			TaskStatus = TASK_RUN;
			break;
			
		case TASK_RUN: 
			if(MC_SpdCarStartSpdup(s, p) == TRUE)		/*��������*/
			{
				TaskStatus = TASK_RUN4;				
				TimeDelayCnt =  0 ; //TASK_TIME_Delay_100ms ;	
				
			}

			break;
			
		case TASK_RUN4:
			if( TimeDelayCnt != 0 )	
				TimeDelayCnt --;
			else
			{
				
				PID_SpeedRegFun(ENABLE);
				Led(LED2 , LED_ON);
				TaskStatus = TASK_RUN1;
				TimeDelayCnt =  0 ;
			}
			break;		
			
		case TASK_RUN1:
			if( TimeDelayCnt!= 0 )	
				TimeDelayCnt --;
			else			
			{
				 CurENC = MC_PosCarCurPosGet();
				 
				if((MC_ServoCarPosChangeCheck() == TRUE)&&((CurENC <= 8)||((CurENC >= ENCODER_RASTER_T1T2_EDGE_NUM-8))))	
				{
					
					counter++;
					if(counter<=1)
					{
						PID_SpeedRegFun(DISABLE);
						Led(LED2 , LED_OFF);
					}
					if(counter>2)
					{						
						TaskStatus  = TASK_RUN2;	
						counter = 0 ;
					}
				}
				else
				{
					ENC_Reset_Position();
					if(counter != 0 )
						counter -- ;
				}
				TimeDelayCnt = TASK_TIME_Delay_100ms ;	
				//TB_ServoCarPosDelayNms( 100);
				
			}
			
			
			break;
		case TASK_RUN2:	
			
			ENC_Reset_Position();	/*ȷ����ԭ���, ��ǰλ��Ϊԭ��*/

			TaskStatus  = TASK_RUN3;	
			break;
			
		case TASK_RUN3:	
			
			if(MC_ServoCarPosCarGoInkStop(s, p, c) == TRUE) /* ��վ*/
				TaskStatus = TASK_END;
				
			break;
			
		case TASK_END:	/*ִ�����*/	
			
				TaskStatus = TASK_INIT ;	 //ack ok !
			break;
		
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
        if(TaskStatus==TASK_END)
        {	
        	TaskStatus = TASK_INIT ;	 //ack ok !
		return TRUE;	
        }	
		
	return FALSE;	/*������δִ����*/
	
}
#if 0
/*���Թ�դ�ܳ���*/
bool MC_ServoCarPosTestRasterLen(ServoSpeedCtr_t * ServoSCP, PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos )
{
	PID_SpeedTYPEDEF *p = PID_Speed ;
	ServoCarPosCtr_t *c = CarPos ;
	ServoSpeedCtr_t *s =  ServoSCP;
	
	static  TaskStatus_t  TaskStatus = TASK_INIT ;
	static u16 counter = 0 ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:	/*��ʼ��--1*/
			//PID_SpeedRegAutoFun(DISABLE );
			MC_SpdCtrModeAutoFun( DISABLE );
			PID_SpeedRegFun(DISABLE);
			MC_SpdCarDirSet(c , GO_FAR_DIR);
			//MC_ServoCarPosDisSet(c , ENCODER_RASTER_T1T2_EDGE_NUM );
			MC_SpdCarSpdSet(p , S_MEA_RASTER_LEN , S_LOW);						
			
			TaskStatus = TASK_RUN;
			
			break;
		case TASK_RUN:
			if(MC_SpdCarStartSpdup(s, p) == TRUE)	 /*��������*/
			{
				
				TB_ServoCarPosDelayNms( 500);
				TaskStatus = TASK_RUN1;
			}
			break;
			
		case TASK_RUN1:
			 if((TB_ServoCarPosDelayNms_IsElapsed()==TRUE))
			{
				
				//c->CurPos = MC_PosCarCurPosGet();	
				if(MC_ServoCarPosChangeCheck() == TRUE)
				{
					counter ++;
					if(counter>7)
					{			
						c->RasterLen = MC_PosCarCurPosGet();					
						counter = 0 ;
						//if(MC_SpdCarStop() == TRUE)
						TaskStatus  = TASK_END;
									
					}
					else
						TB_ServoCarPosDelayNms( 100);
				}
				else
				{					
					if(counter != 0 )
						counter -- ;
				}						
			}
						
			break;
			
		case TASK_END:/*ִ�����*/	
						
			if((TB_ServoCarPosDelayNms_IsElapsed()==TRUE)&&(MC_ServoCarPosCarGoInkStop(s, p, c) == TRUE))				
			 {
			 	
				   TaskStatus = TASK_INIT ;
				   return TRUE;	
		        }
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
       
	/*������δִ����*/
	return FALSE;
}
#endif
/*ī���Ƿ���īվԭ��*/
bool MC_PosCarStop_IsElapsed(void)
{
	u16 ENCCur ;
	
	ENCCur = MC_PosCarCurPosGet();
	
	if( ENCCur <=(u16) ORIGIN_TO_INK_STOP_NEAR_LEN_EDGE)
		return TRUE;
	
	return FALSE;
}
#if 0
bool MC_PosCarCheckPos_IsElapsed(void)
{
	u8 Cnt_PaperExist = 0, Cnt_PaperNo = 0 ;
	u8 i ;
	for(i = 0 ; i < 100 ; i++)
	{
		if(PaperMeaCheck() == PAPER_EXIST)
			Cnt_PaperExist++;
		else
			Cnt_PaperNo++;
	}
	if(Cnt_PaperExist> 90)
		return TRUE;
	//else if(Cnt_PaperNo> 90)	
		return FALSE;
	
}
#endif

#if PAPER_MEA_EN >0
/*------------------------------------------------------------
*��ֽ�߲���
*·��: Near --> Far   --> Near    --->Far		
*                          ����      ����-->
*
*FAR�˵�	Զֽ��		��ֽ��		NEAR�˵�
*    | 	    |			1	X<--|<----------------	|		
*    |  	    |			       |-->|-->S	2			|
* 4 |  S<--|<---------3---<--|<--|		       	|
*    |  |-->|-->S  5								|
* 6 |  S<--|<--|									|
*    |  |---------------------------------------->|
*-----------------------------------------------------------*/
bool MC_PosCarMeaPaperEdgeNearFar(ServoSpeedCtr_t * ServoSCP, PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos )
{	

	PID_SpeedTYPEDEF *p = PID_Speed ;
	ServoCarPosCtr_t *c = CarPos ;
	ServoSpeedCtr_t *s =  ServoSCP;
	static vu8 EdgeCnt = 0 ;
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	static vu16 TimeDelayCnt = 0 ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*��ʼ��--1*/			

			MC_SpdCarDirSet(c , GO_FAR_DIR);
			MC_SpdCarSpdSet( p , S_MEA_PAPER  );
						
			TaskStatus = TASK_RUN;
		
			break;
			
		case TASK_INIT1:/*��ʼ��--1*/			

			MC_SpdCarDirSet( c , GO_NEAR_DIR );
			MC_SpdCarSpdSet( p , S_MEA_PAPER  );						
			TaskStatus = TASK_RUN;
		
			break;	
			
		case TASK_RUN:
			
			if(MC_SpdCarStartSpdup(s, p) == TRUE)	 /*��������*/
			{
				
				//TB_ServoCarPosDelayNms( 500);
				TimeDelayCnt = TASK_TIME_Delay_100ms * 5;
				PaperMeaPaperEdgeFlagClear();
				TaskStatus = TASK_RUN1;
			}		
									
			break;
			
		case TASK_RUN1:
			
			//if(TB_ServoCarPosDelayNms_IsElapsed()==TRUE)		
			if( TimeDelayCnt != 0 )
				TimeDelayCnt--;
			else
			{				
				if(PaperMeaEdge_IsElapsed( ) == TRUE) /*�Ƿ�ൽ��ֽ��*/
				{	
					PaperMeaPaperEdgeFlagClear();
					{
						EdgeCnt ++;
						switch(EdgeCnt)
						{
							case 1:
							case 2:
							case 4:
							case 5:
							case 6:
								TaskStatus = TASK_RUN2;	/*speed down stop*/						
								break;
							case 3:
								break;						
						}	
					}  
					
					//TB_ServoCarPosDelayNms(450);
					TimeDelayCnt = TASK_TIME_Delay_10ms * 45 ;
				}
				//else
				//	TB_ServoCarPosDelayNms(5);				
				
			}		
			break;		
			
		case TASK_RUN2:	

			if( MC_SpdCarSpddownStop(s, p) == TRUE )	 /*����ֹͣ*/
			{
				switch(EdgeCnt)
				{
					case 1:
					case 4:						
						TaskStatus = TASK_INIT1;  /*����  FAR-- chang dir-->NEAR */
						break;
						
					case 2:
					case 5:
						TaskStatus = TASK_INIT ;  /*����  NEAR-- chang dir-->FAR */
						break;
						
					case 6:
						
						PaperMeaWithExtiSet(DISABLE);	
						EdgeCnt = 0 ;
						TaskStatus = TASK_RUN3 ; //Mea Paper edge ok!
						break;						
				}				
			}
			
			break;
			
		case TASK_RUN3:
			if(MC_ServoCarPosCarGoInkStop(s, p, c) == TRUE) /* ��վ*/
				TaskStatus = TASK_END;
			
			break;
			
		case TASK_END:/*ִ�����*/				
						
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
	
        if((TaskStatus==TASK_END))
        {
        
       	TaskStatus = TASK_INIT ; //ack ok !
       	
		return TRUE;			
        }	
		
	return FALSE;/*������δִ����*/		
}

 /*����ֽ��*/
bool MC_ServoCarPosTestPaperWith(ServoSpeedCtr_t * ServoSCP, PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos )
{
	PID_SpeedTYPEDEF *p = PID_Speed ;
	ServoCarPosCtr_t *c = CarPos ;
	ServoSpeedCtr_t *s =  ServoSCP;
	
	static  TaskStatus_t  TaskStatus = TASK_INIT ;
	
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*��ʼ��--1*/
						
			//PID_SpeedRegAutoFun(DISABLE );
			MC_SpdCtrModeAutoFun( DISABLE );
			PID_SpeedRegFun(DISABLE);
			
			PaperMeaReset();
			
			Mp_Fan12(MP_ON);
			
			if(MC_PosCarStop_IsElapsed() == TRUE)	/*ī���Ƿ���īվ*/
			{
				TaskStatus = TASK_RUN1; 		/*��īվ��ԭ��, ���в�ֽ*/
				PaperMeaWithExtiSet(ENABLE);	
			}
			else
				TaskStatus = TASK_RUN; /*����, ��վ*/
			
			break;
			
		case TASK_RUN:

			if(MC_ServoCarPosCarGoInkStop(s, p, c) == TRUE) /* ��վ*/
			{
					
				TaskStatus = TASK_RUN1;
				PaperMeaWithExtiSet(ENABLE);	
			}
			break;
						
		case TASK_RUN1:
			
			if(MC_PosCarMeaPaperEdgeNearFar(s, p, c) == TRUE)
				TaskStatus = TASK_RUN2;
			
			break;
			
		case TASK_RUN2:
			
			Mp_Fan12(MP_OFF);
			if(PaperCalWith()== TRUE)	
			{
				TaskStatus  = TASK_END;
				//UsbSendStringInt("\nPaper With:", PaperWithGet( ));
			}
			else
			{
				TaskStatus = TASK_END;
				//UsbSendString("\n ��ֽ�����!\n" );	
			}
			
			break;
				
		case TASK_END:/*ִ�����*/	
			TaskStatus = TASK_INIT;
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
	
        if( TaskStatus==TASK_END )
        {
        	TaskStatus = TASK_INIT;   
		return TRUE;	
        }	
	return FALSE;/*������δִ����*/
	
}
 #endif
 #define SIMPLE_CNT 10
 static u16 CarSpeed[SIMPLE_CNT];
 static u8 CarSpeedChar[SIMPLE_CNT*5+SIMPLE_CNT+2 ];
 void WordBufToCharBuf(u16 *SrcBuf , u8 *DstBuf , u16  SrcSize)
{
	u16 *Sptr = SrcBuf;
	u8 *Dptr = DstBuf;
	u8 *tptr ;
	u16 i ,j ;	
	for(i = 0 ; i < SrcSize ; i ++ )
	{
		tptr = WordToChar(*Sptr++) ;
		for( j = 0 ; j <5 ; j++)
			*Dptr++ = *(tptr+j);
		*Dptr++ = ',';
	}
	*Dptr++ = '\n';
}
/*˫���˶�*/
bool MC_PosCarPassPrintCtrOdd(ServoSpeedCtr_t * ServoSCP, PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos )
{	
	PID_SpeedTYPEDEF *p = PID_Speed ;
	ServoCarPosCtr_t *c = CarPos ;
	ServoSpeedCtr_t *s =  ServoSCP;
	//PrintPaper_t *pp = &PrintPaperStructure;
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	static u16 TimeDelayCnt = 0 ;
	static u8 i = 0 ;
	s16 temp ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*��ʼ��--1*/			

			MC_SpdCarDirSet(c , GO_FAR_DIR);
			//DirFlag = TRUE;
			/*ͣ�����趨*/
			{
				/*����ͼ���� */
				u16 PaperWith = 1200 ;		/*��ӡֽ��*/
				u16 PageEdge = 10*2 ; 	/*ҳ�߾�*/
				c->PictureWith =(u32)( (PaperWith - PageEdge) * ENCODER_PPR_LINE*10/( 254) ) ;
				c->PriPicToPaperEdgeLen =(u32) 5 * ENCODER_PPR_LINE*10/( 254);
				c->PriPicToPriOriginLen =(u32) 10 * ENCODER_PPR_LINE*10/( 254);
				c->PaperEdgeErr = (u32) 25 * ENCODER_PPR_LINE*10/( 254);
				c->DecSpdNear =  c->PaperEdgeErr + STOP_NEAR_TO_INK_STOP_LEN_EDGE + ORIGIN_TO_INK_STOP_NEAR_LEN_EDGE; /* ���˼��ٵ�*/
				c->DecSpdFar =  c->PriPicToPaperEdgeLen + c->PictureWith \
								+ c->PriPicToPaperEdgeLen +  c->DecSpdNear ;	/* Զ�˼��ٵ�*/
			}
			/*�ٶ��趨*/
			{
				c->PassMode =  PASS1;	
				c->SpdMode = SPD_LOW ; //; //SPD_HIGH  ;SPD_MIDDLE ;SPD_LOW;
				MC_SpdCarSpdSet( p , S_PASS_PRI);
			}
			
			#if STEPPER_EN>0
			{/*��ֽ��ʼ��*/
				MC_StepperNumClear();
				//Stepper_ModeSet( STEP_CUR_WORK_MODE , STEP_DIR_CCW );
				
			}
			#endif
			
			c->PrintStatus = PS_RUN;	/*����������ӡ*/
			
			TaskStatus = TASK_RUN;
			TimeDelayCnt = 0;
			break;		
			
		case TASK_RUN:
			if( TimeDelayCnt!= 0 )	
			{
				TimeDelayCnt --;
				//if(TimeDelayCnt == 800 )			
			}
			else
			{	
				if(MC_SpdCarStartSpdup(s, p) == TRUE)	 /*��������*/
				{				

					//TimeDelayCnt = 8*TASK_TIME_Delay_100ms ;				
					TaskStatus = TASK_RUN6 ;
					
				}	
			}
									
			break;
		case TASK_RUN6:	
			temp = ENC_Get_Mechanical_Speed();
			if (temp<0)
				temp = -temp;	
			if(temp >=( p->DstRef-(u16)p->Upper_Limit_Err/4))
			{
				PID_SpeedRegFun(ENABLE);
				Led(LED2 , LED_ON);
				TaskStatus = TASK_RUN1 ;
				TimeDelayCnt = 0 ;	
			}
		
			break;
		case TASK_RUN1:
			{
				static u16 SimpleCnt =  0 ;				
				SimpleCnt++;
				if(SimpleCnt%100 == 0 )
				{					
					if(i<= SIMPLE_CNT)
					{
						temp = ENC_Get_Mechanical_Speed();
						if (temp<0)
							temp = -temp;
						CarSpeed[i++] = temp;
					}
					else
						i = 0 ;
											 						
				}
			}

			if( TimeDelayCnt!= 0 )	
				TimeDelayCnt --;
			else
			{	
				vu16 EncCur;
				EncCur = MC_PosCarCurPosGet();
				if( ((EncCur>=c->DecSpdFar)&&(c->Dir == GO_FAR_DIR))\
					||((EncCur<=c->DecSpdNear)&&(c->Dir == GO_NEAR_DIR)) )
				{	
				
					TaskStatus = TASK_RUN2;	/*speed down stop*/	
					PID_SpeedRegFun(DISABLE);
					Led(LED2 , LED_OFF);
				}  				
			 }			
					
			break;		
			
		case TASK_RUN2:	

			if( MC_SpdCarSpddownStop(s, p) == TRUE )	 /*����--> ֹͣ*/
			{
				//WordBufToCharBuf(CarSpeed , CarSpeedChar , SIMPLE_CNT);
				//ComSendString(CarSpeedChar);
				
				switch( c->PrintStatus )
				{
					case PS_RUN:
						{								
							#if 0
								static bool DirFlag = TRUE ;
								if(DirFlag == TRUE)
								{
									s->SpdStepDutyCntScale = s->SpdStepDutyCntGoNearScale ;
				
									MC_SpdCarDirSet(c , GO_NEAR_DIR);				
									TaskStatus = TASK_RUN;  /*����  FAR-- chang dir-->NEAR */
									TimeDelayCnt = 3*TASK_TIME_Delay_100ms;
									
									#if STEPPER_EN>0
									StepperPrintFeedPaper(s->StepNum);
									#endif
									DirFlag = FALSE ;
								}
								else
								{
							
									s->SpdStepDutyCntScale = s->SpdStepDutyCntGoFarScale ;
															
									MC_SpdCarDirSet(c , GO_FAR_DIR);
									TaskStatus = TASK_RUN ;  /*����  NEAR-- chang dir-->FAR */
									TimeDelayCnt =  3*TASK_TIME_Delay_100ms;
									#if STEPPER_EN>0
									StepperPrintFeedPaper(s->StepNum);
									#endif		
									DirFlag = TRUE;
								}					
							#else
							switch( c->Dir )
							{							
								case GO_FAR_DIR:						
								{								
									MC_SpdCarDirSet(c , GO_NEAR_DIR);				
									TaskStatus = TASK_RUN;  /*����  FAR-- chang dir-->NEAR */
									TimeDelayCnt = 3*TASK_TIME_Delay_100ms;
										
									#if STEPPER_EN>0
									StepperPrintFeedPaper(s->StepNum);
									#endif			
									s->SpdStepDutyCntScale = s->SpdStepDutyCntGoNearScale ;
								}	
								break;									
									
								case GO_NEAR_DIR:		
								{
									MC_SpdCarDirSet(c , GO_FAR_DIR);
									TaskStatus = TASK_RUN ;  /*����  NEAR-- chang dir-->FAR */
									TimeDelayCnt =  3*TASK_TIME_Delay_100ms;
									#if STEPPER_EN>0
									StepperPrintFeedPaper(s->StepNum);
									#endif	
								
									s->SpdStepDutyCntScale = s->SpdStepDutyCntGoFarScale ;
								}
								break;
									
								default:						
									TaskStatus = TASK_RUN3 ; //Mea Paper edge ok!
									break;										

								}	
							#endif
						}
						break;
	
					case PS_PAUSE:
					case PS_CANSE:	
					case PS_END:		
						TaskStatus = TASK_RUN3 ;
						PID_SpeedRegFun(DISABLE);
						break;
						
					default:
						TaskStatus = TASK_END ;
						break;
				}
				
			}
			
			break;
			
		case TASK_RUN3:	/*��īվ*/
			
			if( MC_ServoCarPosCarGoInkStop( s , p , c ) == TRUE )				
				TaskStatus = TASK_RUN4 ;
			break;
			
		case TASK_RUN4:	/*�ж��Ǵ�ӡ������ȡ��������ͣ*/
			
			if( c->PrintStatus == PS_PAUSE )
				TaskStatus = TASK_RUN5 ;	
			else
				TaskStatus = TASK_END ;
			break;
			
		case TASK_RUN5:/*�ȴ����ռ�����ӡָ��*/
			
			if( c->PrintStatus == PS_RUN )
				TaskStatus = TASK_RUN;
			
			break;
			
		case TASK_END:/*ִ�����*/				
			TaskStatus = TASK_INIT ;		
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
	
        if(TaskStatus==TASK_END)
        {	
        	TaskStatus = TASK_INIT ;
		return TRUE;			
        }	
		
	return FALSE;/*������δִ����*/		
}
/****�˶�����������*****MC_PosCarBack �ڶ�ʱ�ж���ʹ��
*��������:
*1����ԭ��
*2�����ӡ������
*3����ֽ��
*4��˫���˶�
*5����ֽ
*6��
*7��
*8��
**********************************************/
void MC_ServoCarPosCtr(ServoSpeedCtr_t * ServoSCP, PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos )
{
	PID_SpeedTYPEDEF *p = PID_Speed ;
	ServoCarPosCtr_t *c = CarPos ;	
	ServoSpeedCtr_t *s =  ServoSCP;
	static u16 TimeDelayCnt = 0 ;
	switch(c->SportMode)
	{
		case SPORT_FIND_ORIGIN:			
			
			if(MC_ServoCarPosCarGoOrgin(s, p , c) == TRUE)			
			{							
				//ENC_Reset_Position();
				TimeDelayCnt = 2* TASK_TIME_Delay_100ms ;
				//c->SportMode = SPORT_WAIT;
		
				#if PAPER_MEA_EN>0
				c->SportMode = SPORT_MEA_PAPER_WITH;
				#else
				c->SportMode = SPORT_ODD ;
				#endif
				
			}
			break;
#if 0		
		case SPORT_MEA_RASTER_LEN:
			
			if(MC_ServoCarPosTestRasterLen(s , p , c) == TRUE)
			{
								
				UsbSendStringInt("\nTest  RasterLen:", c->RasterLen );	

				c->SportMode = SPORT_MEA_PAPER_WITH;				
			}
			break;
#endif

	#if PAPER_MEA_EN>0
		case SPORT_MEA_PAPER_WITH:
			if( TimeDelayCnt!= 0 )	
				TimeDelayCnt --;
			else
			{			
				if(MC_ServoCarPosTestPaperWith(s, p,c)== TRUE)
				{
					c->SportMode = SPORT_ODD;
					TimeDelayCnt = 5 * TASK_TIME_Delay_100ms ;
				}
			}
			break;
		
	#endif	//#if PAPER_MEA_EN>0	
	
		case SPORT_ODD:/*˫��*/
			if( TimeDelayCnt !=  0 )	
				TimeDelayCnt --;
			else
			{
				if(MC_PosCarPassPrintCtrOdd(s, p , c) == TRUE)
					c->SportMode = SPORT_WAIT ;
			}
			break;
			
		case SPORT_EVEN:
			c->SportMode = SPORT_WAIT ;
			break;
			
		case SPORT_WAIT:
			
			if(TB_ServoCarPosDelayNms_IsElapsed()==TRUE)
			{
					
					
					c->SportMode = SPORT_FAULT;
					TB_ServoCarPosDelayNms(1000);
			}
			
			break;
			
		case SPORT_FAULT:
			
			if(TB_ServoCarPosDelayNms_IsElapsed()==TRUE)
				c->SportMode = SPORT_FIND_ORIGIN;
			
			break;
		case SPORT_IDLE:
			
			break;
		
	}
		
}

/*******************************************************************************
* Function Name  : TB_ServoStatusRepDelayNms
* Description    : Set Delay utilized by main.c module.
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void TB_ServoCarPosMainDelayNms(u16 nms)
{
	hServoCarPosDelayNnms  = nms;
}  

/*******************************************************************************
* Function Name  : TB_ServoStatusRepDelayNms_IsElapsed
* Description    : Check if the delay set by TB_Set_DisplayDelay_500us is elapsed.   
* Input          : None
* Output         : True if delay is elapsed, false otherwise 
* Return         : None
*******************************************************************************/
bool TB_ServoCarPosMainDelayNms_IsElapsed(void)
{
	if (hServoCarPosDelayNnms != 0)
	{
		return (FALSE);
	}
	else 
	{
		return (TRUE);
	}
} 

#if 1
bool MC_PosMain(void )
{	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	ServoCarPosCtr_t *c = &ServoCarSportStructure ;
	//static u16 TimeDelayCnt = 0 ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*��ʼ��--1*/	
			MC_ServoCapPosFunSw(ENABLE);
			c->SportMode = SPORT_FIND_ORIGIN;				
			TB_ServoCarPosMainDelayNms(500);
			TaskStatus = TASK_RUN;

			break;
			
		case TASK_RUN:
			
			if(TB_ServoCarPosMainDelayNms_IsElapsed() == TRUE)
			{
				LedAutoOnOff(LED2);	
				TB_ServoCarPosMainDelayNms(500);
			}						
			break;
			
		case TASK_END:/*ִ�����*/	
			
		
			TaskStatus = TASK_INIT ; //ack ok !
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
	
        if(TaskStatus==TASK_END)
        {	
        
		return TRUE;	
		
        }	
		
	return FALSE;/*������δִ����*/		
}	
#endif

/*******************************************************************************
* Function Name  : 
* Description    : None
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/
#endif //#if PID_REG_EN>0


