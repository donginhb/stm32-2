/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : MC_Control_Param.h
* Author             : IMS Systems Lab 
* Date First Issued  : 21/11/07
* Description        : This file gathers parameters related to:
*                      power devices, speed regulation frequency, PID controllers
*                      setpoints and constants, start-up ramp, lowest values for
*                      speed reading validation.
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
#ifndef __MC_CONTROL_PARAM_H
#define __MC_CONTROL_PARAM_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/*********************** POWER DEVICES PARAMETERS ******************************/
/*
*kp  过大为出现振动
*ki过小，震荡
*/
/****	Power devices switching frequency  ****/
//#define PWM_FREQ ((u16) 14400) // in Hz  (N.b.: pattern type is center aligned)
#define SERVO_PWM_FREQ_DEFAULT  	((u16)32000 )		 /* UINT : Hz -- set pwm freq*/
#define SERVO_PWM_DUTY_SCALE_DEFAULT	((u8)50)       /*%  -- default duty clcty */

/****    Deadtime Value   ****/
//#define DEADTIME_NS	((u16) 800)  //in nsec; range is [0...3500] 
                                                                    
/****      Uncomment the Max modulation index     ****/ 
/**** corresponding to the selected PWM frequency ****/
//#define MAX_MODULATION_100_PER_CENT     // up to 11.4 kHz PWM frequency 
//#define MAX_MODULATION_99_PER_CENT      // up to 11.8 kHz
//#define MAX_MODULATION_98_PER_CENT      // up to 12.2 kHz  
//#define MAX_MODULATION_97_PER_CENT      // up to 12.9 kHz  
//#define MAX_MODULATION_96_PER_CENT      // up to 14.4 kHz  
//#define MAX_MODULATION_95_PER_CENT      // up to 14.8 kHz
//#define MAX_MODULATION_94_PER_CENT      // up to 15.2 kHz  
//#define MAX_MODULATION_93_PER_CENT      // up to 16.7 kHz
//#define MAX_MODULATION_92_PER_CENT      // up to 17.1 kHz
//#define MAX_MODULATION_91_PER_CENT      // up to 17.5 kHz

/*********************** CURRENT REGULATION PARAMETERS ************************/

/****	ADC IRQ-HANDLER frequency, related to PWM  ****/
//#define REP_RATE (1)  // (N.b): Internal current loop is performed every 
                      //             (REP_RATE + 1)/(2*PWM_FREQ) seconds.
                      // REP_RATE has to be an odd number in case of three-shunt
                      // current reading; this limitation doesn't apply to ICS

//Not to be modified
//#define SAMPLING_FREQ   ((u16)PWM_FREQ/((REP_RATE+1)/2))   // Resolution: 1Hz

/********************** POWER BOARD PROTECTIONS THRESHOLDS ********************/


/*********************** SPEED LOOP SAMPLING TIME *****************************/
//Not to be modified
#define PID_SPEED_SAMPLING_500us     ((u8) (0))     // min 500usec
#define PID_SPEED_SAMPLING_1ms       ((u8) (1))
#define PID_SPEED_SAMPLING_2ms        ((u8)(3))     // (3+1)*500usec = 2msec
#define PID_SPEED_SAMPLING_5ms       ( (u8)(9)	)	// (9+1)*500usec = 5msec		
#define PID_SPEED_SAMPLING_10ms     ((u8)(19))	// (19+1)*500usec = 10msec
#define PID_SPEED_SAMPLING_20ms       ((u8)(39))	// (39+1)*500usec = 20msec
#define PID_SPEED_SAMPLING_100ms     ((u8) (199))	// (39+1)*500usec = 20msec
#define PID_SPEED_SAMPLING_127ms     ((u8) (255))  // max (255-1)*500us = 127 ms


//Not to be modified
#define SPEED_CTR_500us    PID_SPEED_SAMPLING_500us
#define SPEED_CTR_1ms       PID_SPEED_SAMPLING_1ms
#define SPEED_CTR_2ms       PID_SPEED_SAMPLING_2ms     // (3+1)*500usec = 2msec
#define SPEED_CTR_5ms       PID_SPEED_SAMPLING_5ms		// (9+1)*500usec = 5msec		
#define SPEED_CTR_10ms     PID_SPEED_SAMPLING_10ms	// (19+1)*500usec = 10msec
#define SPEED_CTR_20ms     PID_SPEED_SAMPLING_20ms	// (39+1)*500usec = 20msec
#define SPEED_CTR_100ms   PID_SPEED_SAMPLING_100ms	// (39+1)*500usec = 20msec
#define SPEED_CTR_127ms   PID_SPEED_SAMPLING_127ms   // max (255-1)*500us = 127 ms

//User should make his choice here below  
/*采样周期*/
#define PID_SPEED_SAMPLING_TIME   (u8)(PID_SPEED_SAMPLING_1ms) /*use in time_base.c counter*/

#define SPEED_SAMPLING_TIME	     (u8)(PID_SPEED_SAMPLING_1ms) /*use in time_base.c counter*/
#define SPEED_SAMPLING_FREQ		(u16)(2000/(SPEED_SAMPLING_TIME+1))  		/*use in encoder.c 计算转速中*/

#define PID_SPEED_SAMPLING_T   (1/SPEED_SAMPLING_FREQ)  	/*use pid 计算中uint: s  */


/*速度控制变化时基*/
#define SPEED_CTR_TIME_BASE  SPEED_CTR_1ms
/******************** SPEED PID-CONTROLLER INIT VALUES************************/
/* default values for Speed control loop */

/******************************************************
//Ki = Kp*Ts/Ti; Kd = Kp * Td/Ts ,	(Ts 采样周期， Ti 积分时间常数， Td 微分时间常数)
△U(k)=Ae(k)-Be(k-1)+Ce(k-2)
   A=Kp(1+T/Ti+Td/T)
   B=Kp(1+2Td/T)
   C=KpTd/T
   T采样周期 Td微分时间 Ti积分时间

   用上面的算法可以构造自己的PID算法。
U（K）=U（K-1）+△U（K） 
---------------------------------------------------------
*Ki = Kp*T/Ti 为积分系数; 
*Kd = Kp*Td/T 为微分系数
*
*△U(k)=Kp(Ek - Ek_1) + KiEk + Kd(Ek - 2Ek_1 + Ek_2)
*************************************************************/

#define Ts 	PID_SPEED_SAMPLING_T  /*采样周期*/
#define PID_Kp 	(2)		/*比例项系数*/
#define PID_Ti	(0.018)	/*积分时间常数*/
#define PID_Td 	(0)		/*微分时间常数*/
/*	速度: 200 --400--600--800--1000--1200--1400 mm/s		*/
/*		*/

#define DLT_DTY_TCK    			(2)	 /*光栅尺每增加一英尺，PWM 设定值增加量*/

//#define PID_SPEED_REFERENCE_RPM   (s16)(1600)		/*默认转速设定速度， 单位: 英尺/分,  */
#define SPEED_REFERENCE_RPM   (s16)(220)	/*uint : mm/s*/

#define PID_SPEED_REFERENCE_RPM   SPEED_REFERENCE_RPM 

#define SPEED_DUTY_SCAlE 	(1100)	//(1150)	/*速度到占空比转化系数*/
#define SPEED_DUTY_SCAlE_DIV    (1000)	/*速度到占空比转化分系数*/

#if 1
#define PID_SPEED_KP_DEFAULT     (u8)(100)	 
#define PID_SPEED_KI_DEFAULT     (u8)(46)	// PID_SPEED_KI_DEFAULT = ((100*PID_Kp* Ts/PID_Ti))
#define PID_SPEED_KD_DEFAULT     (u8)( 0)	//PID_SPEED_KD_DEFAULT=Kd(Ek - 2Ek_1 + Ek_2)	
#else

#define PID_SPEED_KP_DEFAULT      (s16)1000
#define PID_SPEED_KI_DEFAULT      (s16)30
#define PID_SPEED_KD_DEFAULT      (s16)800
#endif
#if 0
#define PID_SPEED_KA_DEFAULT 	(s16)(240)	 //PID_KP*(1+ PID_T/Ti)
#define PID_SPEED_KB_DEFAULT 	(s16)(-200)	// - PID_KP ;
#define PID_SPEED_KC_DEFAULT 	(s16)(10)	 // (  PID_TD /PID_T)
#endif
// Speed PID parameter dividers
#if 0
#define SP_KPDIV ((s16)(2000))
#define SP_KIDIV ((s16)(4069))
#define SP_KDDIV ((s16)100)
#else
#define SP_KSDIV ((1000))
#define SP_KPDIV ((u8)(100))
#define SP_KIDIV ((u8)(100))
#define SP_KDDIV ((u8)100)
#endif
#if 0
// Speed PID parameter dividers
#define SP_KADIV ((s16)(100))
#define SP_KBDIV ((s16)(100))
#define SP_KCDIV ((s16)100)
#endif
/*
*K_PID_PWM_SCALE =100 * 转速(转/分)/(NewDutyRegVal - SERVO_PWM_DUTY_HALF) 
*/
//#define K_PID_PWM_SCALE		((s16)(88))   /*速度值换算成pwm值的折算系数*/
//#define K_PID_PWM_SCALEDIV	((s16)100)	
/* Define here below the period of the square waved reference torque generated
 when FLUX_TORQUE_PIDs_TUNING is uncommented in STM32F10x_MCconf.h          */
#define SQUARE_WAVE_PERIOD   (u16)2000 //in msec 

/*******           Ki, Kp, Kd COEFFICIENT CALCULATION       ********************/
/*******           		Speed control operation		     ***********************
		

              /|\               /
               |               /
  	       |	      /
               |             /
               |   _________/  
               |  /
               | /
	       |/_________________________\ 
	   Fmin   F_1      F_2  Fmax      /
				
		                                                                

We assume a linear variation of Ki, Kp, Kd coefficients following
the motor speed. 2 intermediate frequencies ar set (see definition here after)
and 3 terms (Ki,Kp,Kd) associated with Fmin, F_1, F_2, Fmax 
(total: 4+4+4 terms); following linear coefficients are used to compute each term.

Example: 

Fmin = 500  <->	50 Hz 	(reminder -> mechanical frequency with 0.1 Hz resolution!)
Ki_min = 20	Kp_min = 40       Kd_min = 500 

F_1 = 2000 <->	200 Hz 	
Ki_1 = 80	Kp_1 = 1000        Kd_1 = 260 

then:
alpha_Ki_1 = (Ki_1-Ki_Fmin)/(F_1-Fmin) = 60/1500 = 0.04
alpha_Kp_1 = (Kp_1-Kp_Fmin)/(F_1-Fmin) = 960/1500 = 0.64
alpha_Kd_1 = (Kd_1-Kd_Fmin)/(F_1-Fmin) = -240/1500 = -0.16

** Result **
From Freq_Min to F_1, Ki, Kp, Kd will then obey to:
Ki = Ki_Fmin + alpha_Ki_1*(Freq_motor-Freq_Min)
Kp = Kp_Fmin + alpha_Kp_1*(Freq_motor-Freq_Min)
Kd = Kd_Fmin + alpha_Kd_1*(Freq_motor-Freq_Min)

		                                                                
*********************************************************************************/
//Settings for min frequency
#define Freq_Min         (u16)10 // 1 Hz mechanical
#define Ki_Fmin          (u16)1000 // Frequency min coefficient settings
#define Kp_Fmin          (u16)2000
#define Kd_Fmin          (u16)0

//Settings for intermediate frequency 1
#define F_1              (u16)50 // 5 Hz mechanical
#define Ki_F_1           (u16)2000 // Intermediate frequency 1 coefficient settings
#define Kp_F_1           (u16)1000
#define Kd_F_1           (u16)0

//Settings for intermediate frequency 2
#define F_2              (u16)200 // 20 Hz mechanical
#define Ki_F_2           (u16)1000 // Intermediate frequency 2 coefficient settings
#define Kp_F_2           (u16)750
#define Kd_F_2           (u16)0

//Settings for max frequency
#define Freq_Max         (u16)500 // 50 Hz mechanical
#define Ki_Fmax          (u16)500 // Frequency max coefficient settings
#define Kp_Fmax          (u16)500
#define Kd_Fmax          (u16)0
                                                                             
/********************************************************************************/      
/* Do not modify */
/* linear coefficients */                                                                             
#define alpha_Ki_1		(s32)( ((s32)((s16)Ki_F_1-(s16)Ki_Fmin)*1024) / (s32)(F_1-Freq_Min) )
#define alpha_Kp_1		(s32)( ((s32)((s16)Kp_F_1-(s16)Kp_Fmin)*1024) / (s32)(F_1-Freq_Min) )
#define alpha_Kd_1		(s32)( ((s32)((s16)Kd_F_1-(s16)Kd_Fmin)*1024) / (s32)(F_1-Freq_Min) )

#define alpha_Ki_2		(s32)( ((s32)((s16)Ki_F_2-(s16)Ki_F_1)*1024) / (s32)(F_2-F_1) )
#define alpha_Kp_2		(s32)( ((s32)((s16)Kp_F_2-(s16)Kp_F_1)*1024) / (s32)(F_2-F_1) )
#define alpha_Kd_2		(s32)( ((s32)((s16)Kd_F_2-(s16)Kd_F_1)*1024) / (s32)(F_2-F_1) )

#define alpha_Ki_3		(s32)( ((s32)((s16)Ki_Fmax-(s16)Ki_F_2)*1024) / (s32)(Freq_Max-F_2) )
#define alpha_Kp_3		(s32)( ((s32)((s16)Kp_Fmax-(s16)Kp_F_2)*1024) / (s32)(Freq_Max-F_2) )
#define alpha_Kd_3		(s32)( ((s32)((s16)Kd_Fmax-(s16)Kd_F_2)*1024) / (s32)(Freq_Max-F_2) )


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#endif /* __MC_CONTROL_PARAM_H */
/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/



