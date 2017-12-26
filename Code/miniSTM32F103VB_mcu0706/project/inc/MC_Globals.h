/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : MC_Globals.h
* Author             : IMS Systems Lab  
* Date First Issued  : 21/11/07
* Description        : This file contains the declarations of the exported 
*                      variables of module "MC_globals.c".
********************************************************************************
* History:
* 21/11/07 1.0
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MC_GLOBALS_H
#define __MC_GLOBALS_H
/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_lib.h"
#include "MC_type.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

/*Electrical, magnetic and mechanical variables*/
/*Variable of convenience*/

//extern volatile SystStatus_t State;
extern PID_SpeedTYPEDEF  PID_Speed_InitStructure;
extern ServoSpeedCtr_t  ServoSpeedCtrStructure ;
extern ServoCarPosCtr_t  ServoCarSportStructure; 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#endif /* __MC_GLOBALS_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
