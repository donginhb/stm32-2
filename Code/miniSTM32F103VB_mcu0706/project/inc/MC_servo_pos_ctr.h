//file:MC_servo_pos_ctr.h
#ifndef __MC_SERVO_POS_CTR_H
#define __MC_SERVO_POS_CTR_H


/*GO_NEAR_DIR开机小车运动方向， 改变此方向调整获得近端点*/
#define GO_NEAR_DIR  	DIR_T2 /*去近端点方向*/
#define GO_FAR_DIR  		 DIR_T1 
#define STOP_CAR 		GO_NEAR_DIR

typedef enum{
	CAP_PAPER_EDGE,
	CAP_CLOCE,
}PosCapType_t;

 #define TASK_TIME_Delay_10ms  	  (u8)(10) /*运动控制定时扫描翻转状态1ms*/
 #define TASK_TIME_Delay_100ms  (u8)(100)

//extern void MC_ServoPosInit(ServoCarPosCtr_t  *CarPos );
extern void MC_ServoPosDeInit( void );
extern s32 MC_ServoCurPosGet( void );
extern  s32 MC_ServoCurSGet( void );
extern bool  MC_ServoCarPosChangeCheck(void);
extern void MC_ServoCalCurS(ServoCarPosCtr_t  *CarPos );
extern s32 MC_ServoGetCurS(ServoCarPosCtr_t  *CarPos );
void MC_SpdCarSpdModeAutoStart(void );
extern void MC_ServoCapPosFunSw(FunctionalState NewState);
extern void PaperMeaWithExtiSet( FunctionalState NewStatus );
extern void MC_ServoCarPosCtr(ServoSpeedCtr_t * ServoSCP, PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos );
bool MC_PosMain(void );

extern void MC_PosCarBack(void);
#endif //__MC_SERVO_POS_CTR_H


