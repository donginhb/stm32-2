/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : MC_Globals.c
* Author             : IMS Systems Lab
* Date First Issued  : 21/11/07
* Description        : This file contains the declarations of the global 
*                      variables utilized by the motor control library
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
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
//#include "stm32f10x_MCconf.h"
//#include "MC_const.h"
#include "MC_type.h"
#include "MC_Globals.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Electrical, magnetic and mechanical variables*/
/*Variable of convenience*/

#ifdef FLUX_TORQUE_PIDs_TUNING
//volatile u32 wGlobal_Flags = FIRST_START;
#else
//volatile u32 wGlobal_Flags = FIRST_START | SPEED_CONTROL;
#endif

//volatile SystStatus_t State = INIT;

PID_SpeedTYPEDEF   PID_Speed_InitStructure;

ServoSpeedCtr_t ServoSpeedCtrStructure ;	/*伺服速度参数*/
ServoCarPosCtr_t ServoCarSportStructure;  /*伺服小车运动位置参数*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
