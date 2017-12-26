//file: stepper.h
#ifndef __STEPPER_TB6560_H
#define __STEPPER_TB6560_H

#include "stepper.h"

//----����---------------------------------------------
#define STEP_164_CW  	0 /*����*/
#define STEP_164_CCW  	1 /*����*/

//-----Decay-----pwm˥��-----------------------------
#define STEP_164_DCY_00 	(0x00<<2) 	/*Decay 0%*/
#define STEP_164_DCY_25	(0x01<<2)  	/*Decay 25%*/
#define STEP_164_DCY_50	(0x02<<2)  	/*Decay 50%*/
#define STEP_164_DCY_100	(0x03<<2)  	/*Decay 100%*/

//--torque settings ( curent value)--����ֵ�趨---------

#define STEP_164_TQ_100 	(0x00 <<4)	/*100%*/
#define STEP_164_TQ_75		(0x01 <<4)	/*75%*/
#define STEP_164_TQ_50		(0x02 <<4)	/*50%*/
#define STEP_164_TQ_20		(0x03 <<4)	/*20%*/

/*
*���ڲ�����������趨:
*1,  ����ʱ�������:50%, ����
*2,  ����ʱ, Ҫ���20% (����: 1,  ��ֹ�������ֽ2, ��С�������  )
*/

#define STEP_WORK_MODE_CUR 		STEP_164_TQ_50		/*Ĭ�Ϲ���ģʽ����*/
#define STEP_WEAK_MODE_CUR  		STEP_164_TQ_20		/*����ģʽ����ֵ*/


//--Excitation settings----M2 M1----ϸ��-----------------
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

