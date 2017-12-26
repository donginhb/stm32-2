//PID_regulate.h
#ifndef __MC_PID_REGULATE_H
#define __MC_PID_REGULATE_H


#define  PID_TIM_CCR1_VAL  2		/*ms , pid ��ʱ����ʱ�����趨��ʱ��Ϊ1ms*/
/*************************************************************************
*����PID_SPEED_SAMPLING_FREQ ˵�� :
*PID_TIM �ж�Ƶ��Ϊ(2*1000/PID_TIM_CCR1_VAL),
*����PID_SPEED_SAMPLING_FREQ Ϊ(2*1000/PID_TIM_CCR1_VAL)
**************************************************************************/
//#define PID_SPEED_SAMPLING_T  		(0.001*PID_TIM_CCR1_VAL/2) //PID_TIM_CCR1_VAL/2000
//#define PID_SPEED_SAMPLING_FREQ  	(u16)(2*1000/PID_TIM_CCR1_VAL)
#define SERVO_SPEED_DEFAULT   	100	  /*Ĭ���ŷ�ת��, ��λ:*/
#define SERVO_PWM_VAL_DEFAULT  2160  /*60% duty , 100*/

typedef enum{
	PID_DUTY_NO_ERR,
	PID_I_OVER_ERR ,
	DUTY_LOWER_OVER_ERR,
	DUTY_UPPER_OVER_ERR,
}PID_ERR_t;
//PID_SpeedTYPEDEF   PID_Speed_InitStructure;
extern PID_ERR_t PIDErr ;
extern s16 PID_SpeedErr ;
extern u16 PiduErrCnt ;
//extern s16 PIDExpSpeed ;

extern void Init_PID( void );
s16 PID_Speed_Regulator( s16 Speed );
//void  PID_Speed_Regulator(  PID_SpeedTYPEDEF *PID_Speed );
//`u16  PID_MCSpeedToPWMRegVal( PID_SpeedTYPEDEF *PID_Speed , s16 CurDuty);
u16  PID_MCSpeedToPWMRegVal( s16 SpeedErr , s16 CurDuty);
//extern void PID_SpeedRegAutoFun( FunctionalState NewState );
extern void PID_SpeedRegFun( FunctionalState NewState );
#endif //__MC_PID_REGULATE_H



