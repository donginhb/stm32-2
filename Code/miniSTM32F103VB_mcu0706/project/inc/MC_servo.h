#ifndef __MC_SERVO_H
#define __MC_SERVO_H

#include "com_pc_com.h"

#define SERVO_PWM_TIM                      TIM1
#define SERVO_PWM_TIM_CLK 			(72000000) 	/*72MHz--PWM TIM CLK*/

#define SERVO_PWM_PEROD_DEFAULT 			((u16)(SERVO_PWM_TIM_CLK/SERVO_PWM_FREQ_DEFAULT -1))		/*SERVO_PWM_FREQ Hz, PWM tim CCR1 val*/
#define SERVO_PWM_TIM_CCR_VAL_DEFAULT  	((u16)( ( SERVO_PWM_PEROD_DEFAULT +1)*SERVO_PWM_DUTY_SCALE_DEFAULT/100-1 ))   /*pwm tim HIGH set val*/


#define SERVO_PWM_DUTY_FULL	((u16)(SERVO_PWM_PEROD_DEFAULT))
#define  SERVO_PWM_DUTY_HALF	((u16)((SERVO_PWM_PEROD_DEFAULT+1)/2-1))

typedef enum { 

 SERVO_ANGLE = 1,
 SERVO_SPEED 
 	
}MEA_VAL_DEF_t;


/*dir*/
typedef enum { 

	DIR_T1 = 0 ,   /* 近端点--> 远端点*/
	DIR_T2 = !DIR_T1,  	 /*远端点--> 近端点, no use pid, 编码器*/

}SevroDir;
//GO_NEAR
//GO_FAR
typedef enum _SERVO_SPORT_STATUS{
	
	SERVO_SPEED_UP = 0 , 	/*加速*/
	SERVO_SPEED_FIX,		/*匀速*/
	SERVO_SPEED_DOWN ,	 /*减速*/
	SERVO_STOP,			/*停止*/
	SERVO_DIR_CHANGE,		/*换向*/

}ServoSprotStatus;


extern void Init_Servo(void);
extern void Init_ServoGpio( void );
extern void Init_ServoPWM( void ) ;
extern void ServoTest( void );
extern void ServoPWMDutyAdj(s16  RegVal);
extern s16 ServoPWMDutyAdjGet( void );
extern void MC_ServoPWM_Update_Value(u8 bVariable, s16 hValue);
extern void MC_ServoPWM_Update_Output(void);
extern void ServoSetDir(SevroDir dir);
//extern bool MC_Servo_Startup( void )    ;

#endif

