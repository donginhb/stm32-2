/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : MC_PMSM_motor_param.h
* Author             : IMS Systems Lab 
* Date First Issued  : 21/11/07
* Description        : This file contains the PM motor parameters.
********************************************************************************
* History:
* 21/11/07 v1.0
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTOR_PARAM_H
#define __MOTOR_PARAM_H

// Number of motor pair of poles
//#define	POLE_PAIR_NUM 	(u8)2        /* Number of motor pole pairs */
//#define RS               0.35            /* Stator resistance , ohm*/ 
//#define LS               0.0006        /* Stator inductance , H */

// When using Id = 0, NOMINAL_CURRENT is utilized to saturate the output of the 
// PID for speed regulation (i.e. reference torque). 
// Whit MB459 board, the value must be calculated accordingly with formula:
// NOMINAL_CURRENT = (Nominal phase current (A, 0-to-peak)*32767* Rshunt) /0.64

#define MOTOR_RATED_SPEED_RPM  	(u32)3800	
#define MOTOR_VOLTAGE_CONSTANT      4   //Volts RMS ph-ph /kRPM
#define EXT_SPEED_RANGE             	(1.09)

/*not to be modified*/
//#define MAX_BEMF_VOLTAGE  (u16)((MOTOR_RATED_SPEED_RPM*EXT_SPEED_RANGE*\
//                           MOTOR_VOLTAGE_CONSTANT*SQRT_2)/(1000*SQRT_3))
#define MOTOR_MAX_SPEED_RPM	 (u32)(MOTOR_RATED_SPEED_RPM*EXT_SPEED_RANGE)
#define MAX_FREQ_INCR 			(u32)((MOTOR_MAX_SPEED_RPM - MOTOR_RATED_SPEED_RPM +1)*100)

#define MOTOR_MAX_SPEED_HZ 	(u16)((MOTOR_MAX_SPEED_RPM*10)/60)

//#define NOMINAL_CURRENT       		(s16)23727	
/*inch/m, max = 4000*32mm/(25.4mm) = 5040
*750伺服电机皮带轮直径10.2mm，周长: 10.2*3.14 = 32.028mm
*PID 设定参考值， 数量* 6 = , 认为电机速度为inch/m(每分钟多少英尺),
*
*/
#define LOWER_LIMIT_ERR_DEFAULT   (s16)(-60)//(s32)(-MOTOR_RATED_SPEED_RPM*32/(60))  // (SERVO_PWM_PEROD_DEFAULT/2-1)  /*50%*/
#define UPPER_LIMIT_ERR_DEFAULT    (s16)(60)//(s32)(MOTOR_RATED_SPEED_RPM*32/(60))  //(SERVO_PWM_PEROD_DEFAULT -1)  /*100%*/

//#define LOWER_LIMIT_ERR_DEFAULT (s32)(-MOTOR_RATED_SPEED_RPM*32/(60))  // (SERVO_PWM_PEROD_DEFAULT/2-1)  /*50%*/
//#define UPPER_LIMIT_ERR_DEFAULT  (s32)(MOTOR_RATED_SPEED_RPM*32/(60))  //(SERVO_PWM_PEROD_DEFAULT -1)  /*100%*/


#endif /*__MC_PMSM_MOTOR_PARAM_H*/
/**************** (c) 2007  STMicroelectronics ********************************/
