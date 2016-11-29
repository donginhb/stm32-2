/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : MC_encoder_param.h
* Author             : IMS Systems Lab 
* Date First Issued  : 21/11/07
* Description        : Contains the list of project specific parameters related
*                      to the encoder speed and position feedback.
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
#ifndef __MC_ENCODER_PARAM_H
#define __MC_ENCODER_PARAM_H

//#include "STM32F10x_MCconf.h"

/* PERIPHERAL SET-UP ---------------------------------------------------------*/
#if ((defined ENCODER)||(defined VIEW_ENCODER_FEEDBACK))
/* Define here the 16-bit timer chosen to handle encoder feedback */
/*TIMER 2 is the mandatory selection when using STM32MC-KIT */
#define TIMER2_HANDLES_ENCODER
//#define TIMER3_HANDLES_ENCODER
//#define TIMER4_HANDLES_ENCODER
#endif  // ENCODER

#if 0
#if defined(TIMER2_HANDLES_ENCODER)
#define ENCODER_TIMER         TIM2          // Encoder unit connected to TIM2
#elif defined(TIMER3_HANDLES_ENCODER)
#define ENCODER_TIMER         TIM3          // Encoder unit connected to TIM3
#else // TIMER4_HANDLES_ENCODER
#define ENCODER_TIMER         TIM4          // Encoder unit connected to TIM4
#endif
#endif
/*****************************  Encoder settings ******************************/
#define ENCODER_RASTER_LMM  (1800)
#define ENCODER_PPR           (u16)(150)   // number of pulses per inch
#define ENCODER_PPR_LINE  (u16)(4*ENCODER_PPR)

#define Uint_MmToRasterNum(x)  ((ENCODER_PPR * x *10/254 )) 	 /* nmm ”–∂‡…Ÿ∏ˆπ‚’§∏Ò ˝*/
#define ENCODER_RASTERT1T2EdgeNum	((long)(4*(ENCODER_PPR * ENCODER_RASTER_LMM *10/254 ))) 	/* nmm ”–∂‡…Ÿ∏ˆT1T2π‚’§±ﬂ—ÿ ˝*/
#define Uint_RasterNumToMm(x)  (( x *10/254 )) 	 /* nmm ”–∂‡…Ÿ∏ˆπ‚’§∏Ò ˝*/

#define ENCODER_RASTER_PANE_NUM  			(u16)Uint_MmToRasterNum(ENCODER_RASTER_LMM)	/*1.8m π‚’§∏Ò ˝*/
#define ENCODER_RASTER_T1T2_EDGE_NUM  	((long)(4*(ENCODER_PPR * ENCODER_RASTER_LMM *10/254 )))  /*1.8m π‚’§±∂∆µ±ﬂ—ÿ ˝: 42519.68*/

/* Define here the absolute value of the application minimum and maximum speed in rpm unit*/
#define MINIMUM_MECHANICAL_SPEED_RPM  (u32)60   //rpm
#define MAXIMUM_MECHANICAL_SPEED_RPM  (u32)4000 //rpm

/* Define here the number of consecutive error measurement to be detected 
   before going into FAULT state */
#define MAXIMUM_ERROR_NUMBER (u8)25
/* Computation Parameter*/
//Number of averaged speed measurement
#define SPEED_BUFFER_SIZE   8   // power of 2 required to ease computations

/*************************** Alignment settings *******************************/
//Alignemnt duration
#define T_ALIGNMENT           (u16) 700    // Alignment time in ms

#define ALIGNMENT_ANGLE       (u16) 90 //Degrees [0..359]  


// With MB459 and ALIGNMENT_ANGLE equal to 90∞ 
//final alignment phase current = (I_ALIGNMENT * 0.64)/(32767 * Rshunt) 
#define I_ALIGNMENT           (u16) 22000  

//Do not be modified
#define T_ALIGNMENT_PWM_STEPS     (u32) ((T_ALIGNMENT * PWM_FREQ)/1000) 
#define ALIGNMENT_ANGLE_S16       (s16)((s32)(ALIGNMENT_ANGLE) * 65536/360)
#define MINIMUM_MECHANICAL_SPEED  (u16)(MINIMUM_MECHANICAL_SPEED_RPM/6)
#define MAXIMUM_MECHANICAL_SPEED  (u16)(MAXIMUM_MECHANICAL_SPEED_RPM/6)
#endif  /*__MC_ENCODER_PARAM_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/

