/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.2.1
* Date               : 09/22/2008
* Description        : Virtual Com Port Demo main file
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "includes.h"

#if COM_EN>0

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
//ErrorStatus HSEStartUpStatus;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void PC_CMD_HXJQProcess(Cmd_Data_t *RecCD);
void PC_CMD_VXJQProcess(Cmd_Data_t *RecCD);
void PC_CMD_PProcess(Cmd_Data_t *RecCD);
void PC_CMD_SpeedProcess(Cmd_Data_t *RecCD);
void PC_CMD_ClearProcess(Cmd_Data_t *RecCD);
void PC_CMD_MotorProcess(Cmd_Data_t *RecCD);
void PC_CMD_ServoProcess(Cmd_Data_t *RecCD);
void PC_CMD_StepperProcess(Cmd_Data_t *RecCD);
void Com_Init(void)
{

	//UsbGpioInit();
	// Set_USBClock();
	// USB_Interrupts_Config();
	// USB_Init();
	 
}
/*******************************************************************************
* Function Name  : Com_test.
* Description    : Com_test routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int Com_test(void)
{
	
  return 0;
}
/*第一级命令执行函数*/
void PC_CMD_HXJQProcess(Cmd_Data_t *RecCD)
{
	
}

void PC_CMD_VXJQProcess(Cmd_Data_t *RecCD)
{
	
}
void PC_CMD_PProcess(Cmd_Data_t *RecCD)
{
	//Cmd_Data_t *cd = RecCD;

}

void PC_CMD_SpeedProcess(Cmd_Data_t *RecCD)
{

}

void PC_CMD_ClearProcess(Cmd_Data_t *RecCD)
{
	
}

void PC_CMD_MotorProcess(Cmd_Data_t *RecCD)
{
	
}

void PC_CMD_ServoProcess(Cmd_Data_t *RecCD)
{
	Cmd_Data_t *cd = RecCD;		
      // u8 tstate ;
	//ServoSpeedCtr_t *s=&ServoSpeedCtrStructure;
	
	switch(cd->CmdSub)
	{
		case SERVO_CMD_STOP:
				
			break;

		case SERVO_CMD_START:	
			
			break;
			
		case SERVO_CMD_PID_PARA_SET:
			
			break;
			
		case SERVO_CMD_PID_PARA_GET:			
			
			break;
			
		case SERVO_CMD_STATE_GET:
					
			break;
			
		default:
		  break;
	}
}
#endif

void PC_CMD_StepperProcess(Cmd_Data_t *RecCD)
{
	Cmd_Data_t *cd = RecCD;	

	switch(cd->CmdSub)
	{
		case PAPER_FEED:	/*进纸*/
			
			break;
			
		case PAPER_UNFEED:	/*退纸*/
			
			break;		
	}
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

