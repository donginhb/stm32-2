/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_encoder.h
* Author             : IMS Systems Lab 
* Date First Issued  : 21/11/07
* Description        : This file contains the software implementation for the
*                      encoder position and speed reading.
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
#ifndef __STM32F10x_ENCODER_H
#define __STM32F10x_ENCODER_H

/* Private typedef -----------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

extern volatile s16 hCur_Speed;
/* Exported functions ------------------------------------------------------- */
extern void ENC_Init(void) ;

extern s16 ENC_Get_Electrical_Angle(void) ;
extern void ENC_Clear_Speed_Buffer(void) ;
extern void ENC_Calc_Average_Speed(void);
extern s16  ENC_Get_Mechanical_Speed(void);
extern void ENC_ParaOutTest( void ) ;
extern s16 ENC_Get_Speed(void) ;
//void TIM3_IRQHandler(void) ;
extern void ENC_Reset_Position(void);
extern void EncoderTest( void );
extern u16  ENC_Timer_Position_Get(void);

extern s16 ENC_TimerCntGet(void);


#endif  /*__STM32F10x_ENCODER_H*/
/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
