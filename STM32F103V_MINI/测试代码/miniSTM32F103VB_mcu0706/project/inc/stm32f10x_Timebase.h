/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_Timebase.h
* Author             : IMS Systems Lab 
* Date First Issued  : 21/11/07
* Description        : Contains the prototypes of the time base module related
*                      functions.
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


#ifndef __STM32F10x_TIMEBASE_H
#define __STM32F10x_TIMEBASE_H

extern void TB_Init(void);
extern void TB_Delay_nms(u16);
extern bool TB_Delay_IsElapsed(void);
extern void TB_LCMDisplayDelayNms(u16 nms);
extern bool TB_LCMDisplayDelayNms_IsElapsed(void);
extern void TB_ServoDelayNms(u16 nms);
extern bool TB_ServoDelayNms_IsElapsed(void);

extern void TB_ServoStatusRepDelayNms(u16 nms);
//extern void TB_ServoStatusRepDelayNms_IsElapsed(void);
extern bool TB_ServoStatusRepDelayNms_IsElapsed(void);

extern void TB_ServoCarPosDelayNms(u16 nms);
extern bool TB_ServoCarPosDelayNms_IsElapsed(void);

extern volatile u16  DutyClcyleRegVal;

#endif //__STM32F10x_TIMEBASE_H

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
