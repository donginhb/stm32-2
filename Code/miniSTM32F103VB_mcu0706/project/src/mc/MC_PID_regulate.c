/*--------------------------------------------------------------------
*file:PID_regulate.c
* pid ����������pwm
----------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "platform_config.h"

#include "includes.h"

#if PID_REG_EN>0

#define PID_SPEED_REFERENCE  (s16)(PID_SPEED_REFERENCE_RPM) /*�趨ת�٣� ��λ: ת/10�룬 0.1Hz rec    */

static void Init_PIDPara( void )
{
	
	  /**************************************************/
	  /************PID Speed Regulator members*************/
	  /**************************************************/
	PID_SpeedTYPEDEF *p = &PID_Speed_InitStructure;

	  p->PID_Reg_Use = FALSE;
	  p->PID_Reg_EN = FALSE ;
	  p->Reference = PID_SPEED_REFERENCE;
	  p->DstRef = PID_SPEED_REFERENCE;

	  p->Kp = PID_SPEED_KP_DEFAULT;
	  
#if 0
	  p->Ki = PID_SPEED_KI_DEFAULT;
#endif

#ifdef SPEED_DIFFERENTIAL_TERM_ENABLED
	  p->Kd = PID_SPEED_KD_DEFAULT;
#endif


	p->Lower_Limit_Err = (s16)( LOWER_LIMIT_ERR_DEFAULT );    //Lower Limit for Output limitation	
	p->Upper_Limit_Err=(s16) ( UPPER_LIMIT_ERR_DEFAULT );       //Upper Limit for Output limitation



}
#if 0
void PID_SpeedRegAutoFun( FunctionalState NewState )
{
	PID_SpeedTYPEDEF *p = &PID_Speed_InitStructure;
	if(NewState == ENABLE )
		p->PID_Reg_Use = TRUE ;
	else
		p->PID_Reg_Use = FALSE ;
	
}
#endif
void PID_SpeedRegFun( FunctionalState NewState )
{
	PID_SpeedTYPEDEF *p = &PID_Speed_InitStructure;
	if(NewState == ENABLE )
		p->PID_Reg_EN = TRUE ;
	else
		p->PID_Reg_EN = FALSE ;
	
}
//PID_ERR_t PIDErr  = PID_DUTY_NO_ERR ;
//u16 PiduErrCnt = 0 ;
/*---------------------------------------------------------------------
*function: PID_DltDuty
*����: PID ����
*input : E ת�ٵ����ֵ, ����
*return : ��Ҫ�������ӵ�ռ�ձ���
*����:
*���ַ����㷨
*       {  1          Mn >= Mn_HLM �� Mn <= Mn_LLM
* Nk =  |                 
*       {  0          Mn_LLM <  Mn < Mn_HLM
	//Ki = Kp*Ts/Ti; Kd = Kp * Td/Ts ,	(Ts �������ڣ� Ti ����ʱ�䳣���� Td ΢��ʱ�䳣��)
	//A=Kp(1+T/Ti+Td/T)= Kp + Ki + Kd ,  B=-Kp(1+2Td/T)= -Kp-2Kd,  C = Kd
	//kp(Ek-Ek_1) + KiEk + Kd(Ek-2Ek_1+Ek_2)	
	//p->PErr = (p->Kp) * (p->Ek - p->Ek_1) ;	//����������ʽ	
*ע��: stm32f10x_timebase.c��:
	if(NewSpeed<0) //������ת����˴���
			NewSpeed= -NewSpeed;
-----------------------------------------------------------------------*/
s16  PID_Speed_Regulator( s16 Speed )
//void  PID_Speed_Regulator(  PID_SpeedTYPEDEF *PID_Speed  )
{
#if 1
	PID_SpeedTYPEDEF *p = &PID_Speed_InitStructure;
	static s32 tSpeedErr ;
	static s32 Ek = 0  ;
	static s32 Ek_1 = 0  ;
	//static s32 Ek_2 = 0  ;
	 s32 Err = 0 ;
	//u8 Nk = 0 ;
        #ifdef SPEED_DIFFERENTIAL_TERM_ENABLED

        #endif
	s32 PErr= 0 ;  
	#if 0
		static s32 IErr = 0 ;		
	#endif
	
       #ifdef SPEED_DIFFERENTIAL_TERM_ENABLED
	static s32 DErr = 0 ;
      #endif	
	
	#ifdef SPEED_DIFFERENTIAL_TERM_ENABLED
	
	#endif
	//Ek_2 = Ek_1 ;
	Ek_1 = Ek;
	#if 0
	// error computation ��ǰ���ֵ/*speed Ϊ��ֵ�Ժ���*/
	if (( Speed>  p->Upper_Limit_Err )||(Speed<  p->Lower_Limit_Err )||(Speed==0))/*���ַ���*/
	{
		//PIDErr = PID_I_OVER_ERR ;
		//PiduErrCnt++;
		//Nk = 0;
	}
	else
		//Nk = 1;
	#endif
	
	Err  =(s32) (p->Reference - Speed);
	#if 0
	if ( Err >  p->Upper_Limit_Err )/*�޷�*/
	{
		Err = p->Upper_Limit_Err ;

	}
	else if( Err <  p->Lower_Limit_Err )
	{
		Err = p->Lower_Limit_Err  ; 
	}
	#endif
	
	Ek =  Err ;	
		
	PErr = (s32)(p->Kp) * (Ek -Ek_1) ;	/*����������ʽ*/	
	
#if 0
	if(Nk ==1)/*���ַ���*/
		IErr =(s32) p->Ki * Ek;   /* Integral term computation*/
	else
		IErr = IErr ;
#endif

#if 1
	//#if PID_PC_CONST_EN
        #ifdef SPEED_DIFFERENTIAL_TERM_ENABLED
		DErr =(s32)(Ek - 2 * Ek_1) + Ek_2 ;
		
		tSpeedErr =(s32) ( PErr/SP_KPDIV + IErr/SP_KIDIV + DErr/SP_KDDIV ) ;	
         #else
		//tSpeedErr =(s32) ( PID_SPEED_KA_DEFAULT*Ek/SP_KADIV + PID_SPEED_KB_DEFAULT*Ek_1/SP_KBDIV ) ;
		//tSpeedErr =(s32)  ( PErr/SP_KPDIV + IErr/SP_KIDIV ) ;
		tSpeedErr =(s32)  ( PErr/SP_KPDIV  ) ;
         #endif
#else
	  if(Nk == 1)
		tSpeedErr =(long) (Ek ) ;
#endif
	#if 1
	if ( tSpeedErr > 0 )/*�޷�*/
	{
		if( tSpeedErr >p->Upper_Limit_Err)
			tSpeedErr = p->Upper_Limit_Err ;

	}
	else if( tSpeedErr < 0 )
	{
		if(tSpeedErr < p->Lower_Limit_Err)
			tSpeedErr = p->Lower_Limit_Err  ; 
	}
	#endif
	return (s32) tSpeedErr ;  /*����ʽpid�㷨*/
	
#endif
}

/*
*PID�������ֵת����PWM �趨ֵ
*/
//u16  PID_MCSpeedToPWMRegVal( PID_SpeedTYPEDEF *PID_Speed , s16 CurDuty)
u16  PID_MCSpeedToPWMRegVal( s16 SpeedErr , s16 CurDuty)
{
	s32 tNewDuty ;		/*�µ�PWM�Ĵ����趨ֵ*/	
	ServoSpeedCtr_t  *s = &ServoSpeedCtrStructure ;
	PID_SpeedTYPEDEF *p = &PID_Speed_InitStructure;
	//tNewDuty =(s32)( SpeedErr * s->SpdStepDutyCntScale/SPEED_DUTY_SCAlE_DIV ) +  CurDuty ;
	tNewDuty =(s32)( SpeedErr + p->Reference)* s->SpdStepDutyCntScale/SPEED_DUTY_SCAlE_DIV +SERVO_PWM_DUTY_HALF + 1 ; 
	if( tNewDuty < 0)
	{

		tNewDuty = CurDuty ;
	}
	
	else if ( tNewDuty > SERVO_PWM_DUTY_FULL )
	{
		tNewDuty =CurDuty ;

	}
	
	return(u16) tNewDuty;
}


/*******************************************************************************
* Function Name  : 
* Description    : 
* Input             : 			    
* Output         : None
* Return         : None
*******************************************************************************/
void Init_PID( void )
{

	Init_PIDPara();	
	
}

#if 0
/*------------------------------------------------------------------------
*function : �������ڶ�ʱ���жϺ���, ��ʱ����Tsmp = 5ms, 
-------------------------------------------------------------------------*/
void PID_TIM_IRQHandler( void )
{

}
#endif

#endif //#if PID_REG_EN>0

