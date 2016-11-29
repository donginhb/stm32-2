//file: stepper.h
#ifndef __STEPPER_TB6560_H
#define __STEPPER_TB6560_H

#include "stepper.h"

//----方向---------------------------------------------
#define STEP_164_CW  	0 /*正向*/
#define STEP_164_CCW  	1 /*反向*/

//-----Decay-----pwm衰减-----------------------------
#define STEP_164_DCY_00 	(0x00<<2) 	/*Decay 0%*/
#define STEP_164_DCY_25	(0x01<<2)  	/*Decay 25%*/
#define STEP_164_DCY_50	(0x02<<2)  	/*Decay 50%*/
#define STEP_164_DCY_100	(0x03<<2)  	/*Decay 100%*/

//--torque settings ( curent value)--电流值设定---------

#define STEP_164_TQ_100 	(0x00 <<4)	/*100%*/
#define STEP_164_TQ_75		(0x01 <<4)	/*75%*/
#define STEP_164_TQ_50		(0x02 <<4)	/*50%*/
#define STEP_164_TQ_20		(0x03 <<4)	/*20%*/

/*
*关于步进电机电流设定:
*1,  工作时可以设成:50%, 以上
*2,  保持时, 要设成20% (作用: 1,  防止振动误进退纸2, 减小电机自振  )
*/

#define STEP_WORK_MODE_CUR 		STEP_164_TQ_50		/*默认工作模式电流*/
#define STEP_WEAK_MODE_CUR  		STEP_164_TQ_20		/*保持模式电流值*/


//--Excitation settings----M2 M1----细分-----------------
#define STEP_164_EXC_PHASE_2		(0x00<<6) 	/*one setp*/
#define STEP_164_EXC_PHASE_12		(0x01<<6)		/*1/2 setp*/
#define STEP_164_EXC_PHASE_W12	(0x02<<6)		/*1/4 setp*/
#define STEP_164_EXC_PHASE_2W12	(0x03<<6)		/*1/8 setp*/

//**************************************************8


extern void Stepper_InitTB6560(void);
extern void Stepper_ModeSetTB6560(SetpperCurMode mode, SetpperDir run_dir);
extern void Stepper_SetDirTB6560( SetpperDir dir );
extern void Stepper_SetCurTB6560(SetpperCurMode mode);
extern void Stepper_StepTB6560( u16 num );

#endif //__STEPPER_TB6560_H

