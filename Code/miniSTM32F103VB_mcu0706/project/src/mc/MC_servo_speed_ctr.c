/*MC_sevo_run_ctr.c
*描述: 主要完成速度控制, 具体: 加速--> 匀速-->减速过程控制;
*/

#include "includes.h"

#if SERVO_SPD_CTR_EN>0
#define SERVO_SE_SPEED_STEP_BASE_DEFAULT	((u16)(10))	/*加减速步进数值*/
#define SERVO_SE_TIME_STEP_BASE_DEFAULT    	  1			/*相邻两次加减速间隔时间*/
#define SERVO_SPEED_START_UP_DEFAULT   		((u16)(300))  	/* 200 mm/m   默认启动速度*/
void MC_SpdCtrModeAutoFun( FunctionalState NewState )
{
	ServoSpeedCtr_t  * s = &ServoSpeedCtrStructure;
	
	if(NewState == ENABLE )
		s->ServpSpeedCtrModeAutoFlag = TRUE ;
	else
		s->ServpSpeedCtrModeAutoFlag = FALSE ;
	
}
void MC_SpdCarSpdModeAutoStart(void )
{
	//ServoSpeedCtr_t  * s = &ServoSpeedCtrStructure;

	MC_SpdCtrModeAutoFun(ENABLE);
	//s->ServoSpeedStatus = S_INIT ;
		
}
bool MC_SpdCarSpdModeAutoStop(void )
{
	//ServoSpeedCtr_t  * s = &ServoSpeedCtrStructure;
	
	static  TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*初始化--1*/			
				
			TaskStatus = TASK_RUN;
		
			break;
			
		case TASK_RUN:
			
			TaskStatus = TASK_END ; //ack ok !
						
			break;
			
		case TASK_END:/*执行完毕*/	
			MC_SpdCtrModeAutoFun(DISABLE);	
			TaskStatus = TASK_INIT ; //ack ok !
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
	
        if(TaskStatus==TASK_INIT)
        {	   
		return TRUE;	
        }	
		
	return FALSE;/*该任务未执行完*/		

	
		
}
void MC_SpdCarSpdPassEndSet(PID_SpeedTYPEDEF *PID_Speed  , s16 EndSpeed )
 {
 	PID_SpeedTYPEDEF *p = PID_Speed ;

	p->EndRef = EndSpeed ;
 }
 /*******************************************************************************
* Function Name  : 
* Description    : 设定墨车速度
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/
void MC_SpdCarSpdPrintSet(PID_SpeedTYPEDEF *PID_Speed , PrintSpeedSetMode SpeedMode )
{
	PID_SpeedTYPEDEF *p = PID_Speed ;
	//PrintSpeedSetMode Sm = SpeedMode;

	ServoSpeedCtr_t  *s = &ServoSpeedCtrStructure ;
	ServoCarPosCtr_t *c = &ServoCarSportStructure ;	
	
	switch(c->PassMode)
	{
		case PASS1:
		case PASS2:
		case PASS3:
			switch(c->SpdMode)
			{
				case SPD_HIGH:
					p->Reference = p->DstRef  = 600 ; /* 可达到1m/s*/
					p->EndRef = 0 ;
					
					p->Kp = 15 ;
					p->Upper_Limit_Err = 600 ;
					p->Lower_Limit_Err = -600 ;
	
					 s->SpdStepDutyUpScale = 950;/*调整此值可以改变设定和目标速度匹配*/
					s->SpdStepDutyDownScale = 950;
					s->SpdStepDutyCntScale = 650;
					s->SpdStepDutyCntGoFarScale = 650;
					s->SpdStepDutyCntGoNearScale = 660;
					
					p->SrcRef = p->StaRef =  SERVO_SPEED_START_UP_DEFAULT  ;	
					s->SpeedStartDuty =(u32)p->StaRef * s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;
					
					s->SpeedStepUpBase = 12;		
					s->SpeedStepDownBase = 15;	
					s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV ;
					s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*s->SpdStepDutyDownScale/SPEED_DUTY_SCAlE_DIV ;
					
					break;
					
				case SPD_MIDDLE:
					
					p->Reference = p->DstRef  = 400 ; /**/
					p->EndRef = 0 ;
					
					p->Kp = 15 ;
					p->Upper_Limit_Err = 400 ;
					p->Lower_Limit_Err = -400 ;

					 s->SpdStepDutyUpScale = 950;
					s->SpdStepDutyDownScale = 1000;
					
					s->SpdStepDutyCntScale = 745;
					s->SpdStepDutyCntGoFarScale = 745;
					s->SpdStepDutyCntGoNearScale = 745;
					
					p->SrcRef = p->StaRef =  SERVO_SPEED_START_UP_DEFAULT  ;	
					s->SpeedStartDuty =(u32)p->StaRef * s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;	
					
					s->SpeedStepUpBase = 12;	
					s->SpeedStepDownBase = 15;	
					
					s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV ;						
					s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*s->SpdStepDutyDownScale/SPEED_DUTY_SCAlE_DIV ;
					
					break;
					
				case SPD_LOW:
					p->Reference = p->DstRef  = 300 ; /**/
					p->EndRef = 0 ;
					
					p->Kp = 15 ;
					p->Upper_Limit_Err = 600 ;
					p->Lower_Limit_Err =-600 ;

					 s->SpdStepDutyUpScale = 950;
					s->SpdStepDutyDownScale = 950;
					
					s->SpdStepDutyCntScale = 815;
					s->SpdStepDutyCntGoFarScale = 805;
					s->SpdStepDutyCntGoNearScale = 830;
					
					p->SrcRef = p->StaRef =  200  ;	
					s->SpeedStartDuty =(u32)p->StaRef * 1000/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;	
					
					s->SpeedStepUpBase = 10;	
					s->SpeedStepDownBase = 10;	
					
					s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV ;						
					s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*s->SpdStepDutyDownScale/SPEED_DUTY_SCAlE_DIV ;
					
					break;
			}
			s->StepNum = 200;/*pass1进纸数*/
			break;					
		case PASS4:
		case PASS5:
		case PASS6:
		case PASS7:
		case PASS8:
			switch(c->SpdMode)
			{
				case SPD_HIGH:
					p->Reference = p->DstRef  = 1300 ; /* 可达到1m/s*/
					p->EndRef = 0 ;
					
					p->Kp = 15 ;
					p->Upper_Limit_Err = 500 ;
					p->Lower_Limit_Err =-500 ;
				
					s->SpdStepDutyUpScale = 850;
					s->SpdStepDutyDownScale = 850;
					s->SpdStepDutyCntScale = 540;
					
					s->SpdStepDutyCntGoFarScale = 538;
					s->SpdStepDutyCntGoNearScale = 545;
					
					p->SrcRef = p->StaRef =  SERVO_SPEED_START_UP_DEFAULT  ;	
					s->SpeedStartDuty =(u32)p->StaRef * s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;
					
					s->SpeedStepUpBase = 6;						
					s->SpeedStepDownBase = 2;	
					s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV ;
					s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*s->SpdStepDutyDownScale/SPEED_DUTY_SCAlE_DIV ;
					
					break;
					
				case SPD_MIDDLE:
					p->Reference = p->DstRef  = 1000 ; /* 可达到1m/s*/
					p->EndRef = 0 ;
					
					p->Kp = 15 ;
					p->Upper_Limit_Err = 500 ;
					p->Lower_Limit_Err =-500 ;
				
					s->SpdStepDutyUpScale = 950;
					s->SpdStepDutyDownScale = 950;
					s->SpdStepDutyCntScale = 571;
					
					s->SpdStepDutyCntGoFarScale = 565;
					s->SpdStepDutyCntGoNearScale = 571;
					
					p->SrcRef = p->StaRef =  SERVO_SPEED_START_UP_DEFAULT  ;	
					s->SpeedStartDuty =(u32)p->StaRef * s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;
					
					s->SpeedStepUpBase = 11;						
					s->SpeedStepDownBase = 15;	
					s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV ;
					s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*s->SpdStepDutyDownScale/SPEED_DUTY_SCAlE_DIV ;
					
					break;
					
				case SPD_LOW:
					
					p->Reference = p->DstRef  = 800 ; /**/					
					p->EndRef = 0 ;
					
					p->Kp = 15 ;
					p->Upper_Limit_Err = 400 ;
					p->Lower_Limit_Err = -400 ;
					
					s->SpdStepDutyUpScale = 950;/*调整此值可以改变设定和目标速度匹配*/
					s->SpdStepDutyDownScale = 1000;
					s->SpdStepDutyCntScale = 600;

					s->SpdStepDutyCntGoFarScale = 600;
					s->SpdStepDutyCntGoNearScale = 600;
					
					p->SrcRef = p->StaRef =  SERVO_SPEED_START_UP_DEFAULT  ;	
				//	s->SpeedStartDuty =p->SrcRef = p->StaRef * s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;
					s->SpeedStartDuty =(u32)p->StaRef * SPEED_DUTY_SCAlE_DIV/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;
					s->SpeedStepUpBase = 12 ;		
					s->SpeedStepDownBase = 15;	
					s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV ;
					s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*s->SpdStepDutyDownScale/SPEED_DUTY_SCAlE_DIV ;
					
					break;
			}
			s->StepNum = 50;/*pass1进纸数*/
			break;			
		default:
			break;
	}
	
	
}
 #define CAR_SPEED_GO_ORGIN   300  /*小车归原点速度*/
 
/*******************************************************************************
* Function Name  : 
* Description    : 设定墨车速度
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/

void MC_SpdCarSpdSet(PID_SpeedTYPEDEF *PID_Speed , PrintSpeedSetMode SpeedMode )
{
	PID_SpeedTYPEDEF *p = PID_Speed ;
	PrintSpeedSetMode sm = SpeedMode;
	//Speed_HML_Mode shml = SpeedHML;
	ServoSpeedCtr_t  * s = &ServoSpeedCtrStructure ;

	switch(sm)
	{
	
		case S_GO_ORIGIN :			
		case S_MEA_RASTER_LEN:	
			p->Reference = p->DstRef  = 220;
			p->EndRef = 0 ;
			p->Kp = 60 ;
			p->Upper_Limit_Err =  100;
			p->Lower_Limit_Err = -100;
			
			 s->SpdStepDutyUpScale = 810;
			s->SpdStepDutyDownScale = 900;
			
			s->SpdStepDutyCntScale = 1000;	
			p->SrcRef = p->StaRef =  200  ;	
			s->SpeedStartDuty =(u32)p->StaRef *  s->SpdStepDutyUpScale /SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;	
					
			s->SpeedStepUpBase = 10;	
			s->SpeedStepDownBase = 10;	
					
			s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV ;						
			s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*s->SpdStepDutyDownScale/SPEED_DUTY_SCAlE_DIV ;
			
			break;
			
		case S_FATE:	
			p->Reference = p->DstRef  = 220;
			p->EndRef = 0 ;
			p->Kp = PID_SPEED_KP_DEFAULT ;
			p->Upper_Limit_Err =  UPPER_LIMIT_ERR_DEFAULT;
			p->Lower_Limit_Err = LOWER_LIMIT_ERR_DEFAULT;
			s->SpdStepDutyCntScale = s->SpdStepDutyUpScale = SPEED_DUTY_SCAlE;
			s->SpdStepDutyDownScale = SPEED_DUTY_SCAlE;
			
			p->SrcRef = p->StaRef =  SERVO_SPEED_START_UP_DEFAULT  ;	
			s->SpeedStartDuty =(u32)p->StaRef * s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;	
			
			s->SpeedStepUpBase = 5 ;	
			s->SpeedStepDownBase = 100;
			s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*SPEED_DUTY_SCAlE/SPEED_DUTY_SCAlE_DIV   ;			
			s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*SPEED_DUTY_SCAlE/SPEED_DUTY_SCAlE_DIV ;
			
			break;	

			
		case S_MEA_PAPER:
			p->Reference = p->DstRef  = 220;
			p->EndRef = 0 ;
			p->Kp = PID_SPEED_KP_DEFAULT ;
			p->Upper_Limit_Err =  UPPER_LIMIT_ERR_DEFAULT;
			p->Lower_Limit_Err = LOWER_LIMIT_ERR_DEFAULT;
			s->SpdStepDutyCntScale = s->SpdStepDutyUpScale = SPEED_DUTY_SCAlE;
			s->SpdStepDutyDownScale = SPEED_DUTY_SCAlE;
			
			p->SrcRef = p->StaRef =  SERVO_SPEED_START_UP_DEFAULT  ;				
			s->SpeedStartDuty =(u32)p->StaRef * s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;
			
			s->SpeedStepUpBase = 5 ;
			s->SpeedStepDownBase = 10 ;	
			s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*SPEED_DUTY_SCAlE/SPEED_DUTY_SCAlE_DIV   ;
			
			s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*SPEED_DUTY_SCAlE/SPEED_DUTY_SCAlE_DIV ;	
			break;
		
		case S_GO_INK_STOP :	
			p->Reference = p->DstRef  = 220 ;
			p->EndRef = 0 ;
			p->Kp = PID_SPEED_KP_DEFAULT ;
			p->Upper_Limit_Err =  UPPER_LIMIT_ERR_DEFAULT;
			p->Lower_Limit_Err = LOWER_LIMIT_ERR_DEFAULT;
			
			s->SpdStepDutyCntScale = s->SpdStepDutyUpScale = 900;
			s->SpdStepDutyDownScale = 1000;
			
			p->SrcRef = p->StaRef =  SERVO_SPEED_START_UP_DEFAULT  ;	
			s->SpeedStartDuty =(u32)p->StaRef * s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;
			
			s->SpeedStepUpBase = 5 ;	
			s->SpeedStepDownBase = 5;
			s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*SPEED_DUTY_SCAlE/SPEED_DUTY_SCAlE_DIV   ;			
			s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*SPEED_DUTY_SCAlE/SPEED_DUTY_SCAlE_DIV ;
			break;
							
		case S_PASS_PRI:
			MC_SpdCarSpdPrintSet( p , sm); 
			break;
						
		default:
			
			p->Reference = p->DstRef  = 0 ;
			p->Kp = PID_SPEED_KP_DEFAULT ;
			p->Lower_Limit_Err = LOWER_LIMIT_ERR_DEFAULT ;
			p->Upper_Limit_Err =UPPER_LIMIT_ERR_DEFAULT ;
			s->SpdStepDutyCntScale = s->SpdStepDutyUpScale = SPEED_DUTY_SCAlE;
			s->SpdStepDutyDownScale = SPEED_DUTY_SCAlE;
			p->SrcRef =  p->StaRef =  SERVO_SPEED_START_UP_DEFAULT  ;	
			s->SpeedStartDuty =(u32)p->StaRef * s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV  +SERVO_PWM_DUTY_HALF +1 ;
			
			break;			
	}
	
}

 
/*******************************************************************************
* Function Name  : 
* Description    : 设定墨车方向
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/
void MC_SpdCarDirSet(ServoCarPosCtr_t  *CarPos  , SevroDir Dir )
{
	ServoCarPosCtr_t *c= CarPos ;

	c->Dir = Dir;
}

/*
*初始化
*/
void MC_SpdCarParaInit(void )
{
	ServoSpeedCtr_t  * s = &ServoSpeedCtrStructure;
	PID_SpeedTYPEDEF *p = &PID_Speed_InitStructure;
	
	s->RunLen = 0 ;
	s->SpdStepDutyUpScale = SPEED_DUTY_SCAlE;
	s->SpdStepDutyDownScale = SPEED_DUTY_SCAlE;
	s->TimeNmsSetpBase = SERVO_SE_TIME_STEP_BASE_DEFAULT;	
	p->SrcRef = p->StaRef = s->SpeedStartRef = SERVO_SPEED_START_UP_DEFAULT;	
	p->Reference = s->SpeedDutyCur = s->SpeedStartDuty =(u32)SERVO_SPEED_START_UP_DEFAULT*SPEED_DUTY_SCAlE/SPEED_DUTY_SCAlE_DIV + SERVO_PWM_DUTY_HALF  +1 ;

	s->SpeedStepDownBase = SERVO_SE_SPEED_STEP_BASE_DEFAULT;
	s->SpeedStepUpBase = SERVO_SE_SPEED_STEP_BASE_DEFAULT ;

	s->SpeedStepDutyDownBase = (u32) s->SpeedStepDownBase*s->SpdStepDutyDownScale/SPEED_DUTY_SCAlE_DIV ;
	s->SpeedStepDutyUpBase = (u32)s->SpeedStepUpBase*s->SpdStepDutyUpScale /SPEED_DUTY_SCAlE_DIV   ;		
	
	//s->SpeedDutyScale = (u32)s->SpeedDutyDst/(SERVO_PWM_DUTY_FULL +1) ;

	s->Counter = 0 ;
	MC_SpdCtrModeAutoFun( DISABLE );
	//s->ServoSpeedStatus = S_WAIT ;
	s->ServoSpeedCtrUse = TRUE;	
	
}
#if 0
bool TaskSample(void )
{	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*初始化--1*/			
				
			TaskStatus = TASK_RUN;
		
			break;
			
		case TASK_RUN:
			
			TaskStatus = TASK_END ; 
						
			break;
			
		case TASK_END:/*执行完毕*/	
			
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
		
	return FALSE;/*该任务未执行完*/		
}	
#endif

/*启动*/
bool MC_SpdCarStartup( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed ) 
{
	ServoSpeedCtr_t  * s = ServoSCP;		
	//PID_SpeedTYPEDEF *p = PID_Speed;
	ServoCarPosCtr_t  *c = &ServoCarSportStructure;
	static  TaskStatus_t  TaskStatus = TASK_INIT ;
	static u8 DelayCnt  ;
	static vu16 tStaDuty ;
	switch(TaskStatus)
	{
		case TASK_INIT:/*初始化--1*/	
			PID_SpeedRegFun(DISABLE);
			ServoSetDir(c->Dir) ;
			{				
				MC_ServoPWM_Update_Value( SERVO_SPEED , SERVO_PWM_DUTY_HALF  +1);
				TIM_CtrlPWMOutputs( SERVO_PWM_TIM, ENABLE );/*启动Servo*/
				
				TaskStatus = TASK_RUN;
				DelayCnt = 2;
				tStaDuty = s->SpeedStartDuty ;
			}
			break;
		case TASK_RUN:
			if(DelayCnt!=0)
				DelayCnt--;
			else
			{
				MC_ServoPWM_Update_Value( SERVO_SPEED , tStaDuty );
				TaskStatus = TASK_RUN1 ;
				DelayCnt = 50;
			}
			break;
		case TASK_RUN1:
			if(DelayCnt!=0)
				DelayCnt--;
			else
			{
				tStaDuty += 2;
				if(tStaDuty >(u32)(SERVO_PWM_DUTY_FULL*60/100))
				{
					TaskStatus = TASK_END ; 
					MC_ServoPWM_Update_Value( SERVO_SPEED , SERVO_PWM_DUTY_HALF  +1);
				}
				MC_ServoPWM_Update_Value( SERVO_SPEED , tStaDuty );
			}
			if(ENC_Get_Mechanical_Speed() !=  0 )			
			{			
				TaskStatus = TASK_END ; //ack ok !
			}	
			
			break;
			
		case TASK_END:/*执行完毕*/				
			TaskStatus = TASK_INIT ; //ack ok !
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
	return FALSE;/*该任务未执行完*/	
	
}
/*停止*/
bool MC_SpdCarStop( void )    
{
	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	static u8 DelayCnt = 0;  	
	switch(TaskStatus)
	{
		case TASK_INIT:/*初始化--1*/	
			PID_SpeedRegFun(DISABLE);			
		  	MC_ServoPWM_Update_Value( SERVO_SPEED ,   SERVO_PWM_DUTY_HALF+1);
			//TIM_CtrlPWMOutputs( SERVO_PWM_TIM, DISABLE );/*stop Servo*/
			//ServoSetDir( STOP_CAR ) ; /*刹车*/
			DelayCnt = 25;	
			TaskStatus = TASK_RUN;
			
			break;
			
		case TASK_RUN:	
			if(DelayCnt != 0)
            	         	DelayCnt--;
			else
			{
				TIM_CtrlPWMOutputs( SERVO_PWM_TIM, DISABLE );/*stop Servo*/
				ServoSetDir( STOP_CAR ) ; /*刹车*/
				TaskStatus = TASK_END ;      
			}
                      if(ENC_Get_Mechanical_Speed() ==0)
			{		
                          	TaskStatus = TASK_END ;                         
			}
                                 
			break;
			
		case TASK_END:/*执行完毕*/	
			
			//TaskStatus = TASK_INIT ;
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
        
        if(TaskStatus == TASK_END)
        {	   
        	TaskStatus = TASK_INIT ;
		return TRUE;	
        }	
		
	return FALSE;/*该任务未执行完*/	
}

/*加速*/
//注: 要想速度改变有效，调用之前请改变s->SpeedDutyDst值
bool MC_SpdCarSpdup( ServoSpeedCtr_t  *ServoSCP, PID_SpeedTYPEDEF *PID_Speed )  
{
	ServoSpeedCtr_t  *s = ServoSCP;
	PID_SpeedTYPEDEF *p = PID_Speed;
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	
	
	
	switch(TaskStatus)
	{
		case TASK_INIT:	/*初始化--1*/	
			PID_SpeedRegFun(DISABLE);
			{
				u16 temp = 0 ;
				if(p->DstRef > p->SrcRef)
				{
					s->SpeedDutyUpCur = (u32)p->SrcRef * s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV  + SERVO_PWM_DUTY_HALF +1 ; 
					
					temp = (p->DstRef - p->SrcRef) ;					
					temp =(u32) temp* s->SpdStepDutyUpScale/SPEED_DUTY_SCAlE_DIV ; 
					
					s->SpeedStepUpNum = (u32)temp/(s->SpeedStepDutyUpBase) ;

					TaskStatus = TASK_RUN1;
				}
				else
					TaskStatus = TASK_END;
				
			}
			break;
		case TASK_RUN1:
			MC_ServoPWM_Update_Value( SERVO_SPEED ,  s->SpeedDutyUpCur);	
			TaskStatus = TASK_RUN;
			break;
		case TASK_RUN:
	
			if(s->SpeedStepUpNum > 0)
			{
				s->SpeedStepUpNum--;
				s->SpeedDutyUpCur += s->SpeedStepDutyUpBase ;
				
				if(s->SpeedDutyUpCur>SERVO_PWM_DUTY_FULL)
				{
					s->SpeedDutyUpCur=SERVO_PWM_DUTY_FULL;
					TaskStatus = TASK_END ; 		
					
				}				
				MC_ServoPWM_Update_Value( SERVO_SPEED ,  s->SpeedDutyUpCur);								
				
			}
			else
			{			
				TaskStatus = TASK_END ; 		
			}			
			
			break;

		case TASK_END:	/*执行完毕*/	
				
			TaskStatus = TASK_INIT ; //ack ok !
			
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
	return FALSE;/*该任务未执行完*/	
	
}

#define END_PWM_VAL  (u16)((SERVO_PWM_DUTY_FULL + 1)*10/100)

#if  1
/*-----------------------------------------------------------------------
*函数描述: 减速
*注: 要想速度改变有效，调用之前, p->EndRef 必须小于p->DstRef 
*----------------------------------------------------------------------*/
bool MC_SpdCarSpddown( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed )//, PID_SpeedTYPEDEF *PID_Speed )       
{
	ServoSpeedCtr_t  *s = ServoSCP;
	PID_SpeedTYPEDEF *p = PID_Speed;	
	static vu8 Cnt = 0 ;		
	static  TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*初始化--1*/	
			PID_SpeedRegFun(DISABLE);
			{
				u16 temp = 0 ;
				if(p->DstRef > p->EndRef)
				{
					temp = p->DstRef - p->EndRef ;
					temp = (u32)temp * s->SpdStepDutyDownScale/SPEED_DUTY_SCAlE_DIV  + SERVO_PWM_DUTY_HALF +1;	

					s->SpeedStepDownNum = (u32)temp/s->SpeedStepDutyDownBase ;
					
					if(temp%s->SpeedStepDutyDownBase!=0)
						s->SpeedStepDownNum ++;
					
					TaskStatus = TASK_RUN;
				}
				else
					TaskStatus = TASK_END;
				
			}
		
			break;
			
		case TASK_RUN:

				if(s->SpeedStepUpNum > 0  )				
				{						
					
					if((Cnt%2)==0)
					{
						s->SpeedStepUpNum--;
						s->SpeedDutyDownCur  -= s->SpeedStepDownBase ;		
						if(s->SpeedDutyDownCur <(SERVO_PWM_DUTY_HALF))
							s->SpeedDutyDownCur =SERVO_PWM_DUTY_HALF ;	
						
						MC_ServoPWM_Update_Value( SERVO_SPEED ,  s->SpeedDutyDownCur);
						ServoSetDir( ServoCarSportStructure.Dir) ; 
						
					}
					else 
					{						
						MC_ServoPWM_Update_Value( SERVO_SPEED ,  s->SpeedDutyDownCur );
						if(ServoCarSportStructure.Dir == GO_FAR_DIR)
							ServoSetDir( GO_NEAR_DIR) ; 
						else
							ServoSetDir( GO_FAR_DIR) ; 
						
					}
					Cnt ++;
					if(Cnt >= 253)
						Cnt = 0 ;	
						
				 }
				else	
				{
					ServoSetDir( ServoCarSportStructure.Dir) ; 
					TaskStatus = TASK_END ; 	
				}
						
			break;
			
		case TASK_END:/*执行完毕*/	
			
			TaskStatus = TASK_INIT ; //ack ok !

			break;
			
		default:
			TaskStatus = TASK_INIT ;

			break;
	}
	
        if(TaskStatus==TASK_INIT)
        {	   

		return TRUE;	
        }	
		
	return FALSE;/*该任务未执行完*/		
}
#endif
/*
*启动和加速连动
*1， 启动；
*2,     加速
*/
bool MC_SpdCarStartSpdup( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed ) 
{	
	ServoSpeedCtr_t  *s = ServoSCP;
	PID_SpeedTYPEDEF *p = PID_Speed;
	
	static  TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:	/*初始化--1*/	
			PID_SpeedRegFun(DISABLE);
			TaskStatus = TASK_RUN;
		
			break;
		case TASK_RUN:
			
			if(MC_SpdCarStartup(s,p) == TRUE)	
				TaskStatus = TASK_RUN1;
			
			break;
			
		case TASK_RUN1:
			
			if( MC_SpdCarSpdup(s,p) == TRUE )	
				TaskStatus = TASK_END ; //ack ok !
						
			break;
			
		case TASK_END:/*执行完毕*/	
			
			//TaskStatus = TASK_INIT ; //ack ok !
			
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
		
	return FALSE;/*该任务未执行完*/		
}
/*
*减速和停止组合
*1, 减速
*2, 停止
*/
bool MC_SpdCarSpddownStop( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed ) 
{	
	ServoSpeedCtr_t  *s = ServoSCP;
	PID_SpeedTYPEDEF *p = PID_Speed;
	
	static  TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*初始化--1*/		
			PID_SpeedRegFun(DISABLE);
			TaskStatus = TASK_RUN;	
				
			break;
	
		case TASK_RUN:
			if( MC_SpdCarSpddown(s, p) == TRUE )	
				TaskStatus = TASK_RUN1 ; //ack ok !
						
			break;	
		case TASK_RUN1:
			
			if( MC_SpdCarStop() == TRUE )	
				TaskStatus = TASK_END ; //ack ok !
						
			break;		
		case TASK_END:/*执行完毕*/	
			
			TaskStatus = TASK_INIT ; //ack ok !
			
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
		
	return FALSE;/*该任务未执行完*/		
}
bool MC_SpdCarAvoidBumpCar(ServoCarPosCtr_t  *CarPos )
{
	//ServoCarPosCtr_t  *c = CarPos ;
	static u8 truncnt = 0 ;
	{
						
		if(MC_ServoCarPosChangeCheck() == TRUE)/* car stop, 到两端*/
		{
			truncnt++;											
		}
		else
		{
			if(truncnt>0)
				truncnt --;
			else
				truncnt = 0;
							
		}
		if(truncnt>=10)
		{
			truncnt = 0 ;
			
			return TRUE;
		}
		return FALSE ;
	}
}

//bool PosOutDataUpdataFlag = FALSE ;
//#define  PosOutDataNum  5
//u16 PosOutData[10] ;

/*调整到安全速度*/
bool MC_SpdDownSafeRun( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed )
{	
	ServoSpeedCtr_t  *s = ServoSCP;
	PID_SpeedTYPEDEF *p = PID_Speed;
	
	static  TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*初始化--1*/	
			
			PID_SpeedRegFun(DISABLE );
			
			if(PID_Speed_InitStructure.DstRef > 400)
			{
				MC_SpdCarSpdSet(p , S_FATE );	
				TaskStatus = TASK_END ; //ack ok !
			}
			else
				TaskStatus = TASK_RUN;	
			
		
			break;
			
		case TASK_RUN:
			if( MC_SpdCarSpddown(s, p) == TRUE )	
				TaskStatus = TASK_END ; //ack ok !
						
			break;
			
		case TASK_END:/*执行完毕*/	
			
			TaskStatus = TASK_INIT ; //ack ok !
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
	
        if(TaskStatus==TASK_INIT)
        {	   
		return TRUE;	
        }	
		
	return FALSE;	/*该任务未执行完*/		
}

void MC_SpdCarSafeSpd( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos  )
{
	//ServoSpeedCtr_t  *s = ServoSCP;
	//PID_SpeedTYPEDEF *p = PID_Speed;
	ServoCarPosCtr_t  *c = CarPos;		

	#if 1
	/***小车运行到两端限速点检测位置，刹车 !******/		
	{
		c->CurPos = ENC_Timer_Position_Get(); 
		if((( c->CurPos<=c->SafeDisNear )&&(c->Dir == GO_NEAR_DIR))\
			||( c->CurPos>=c->SafeDisFar)&&(c->Dir ==GO_FAR_DIR))
		{

			if(PID_Speed->PID_Reg_EN == TRUE)
			{
				PID_Speed->PID_Reg_EN= FALSE ; 															
			}
			
				MC_SpdDownSafeRun( ServoSCP, PID_Speed );
			
		}	
	}
	#endif
	
}
#if 0
/*----------------------------------------------
*启动--> 加速--> 匀速-->减速--> 停止
*----------------------------------------------*/
#endif

#endif //#if PID_REG_EN>0


