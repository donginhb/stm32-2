#ifndef __PRINTER_CONFIG_H
#define __PRINTER_CONFIG_H

#ifdef VECT_TAB_RAM
#define DELAY_EN 			1
#define KEY_EN 				0
#define LED103_EN 			1
#define LCM_GUI_EN 			0
#define COM_EN  			       0

#define ENCODER_EN			0

#define UART_DRIVER_EN        1
#define SPI_FLASH_EN  		0
#define EXTI_EN				0
/******************************/
//***ram**dug************************
/* Private functions ------------------------*/
#define SERVO_DUG_N		/* �ŷ�����*/
#define LCM_KEY_DUG_N		/*LCM gui ����*/

#define FPGA_DUG_N 			/*fpga �ӿڵ���*/
#define EXTI_DUG_N			/*�ⲿ�жϽŲ���*/
#define ENCODER_DUG_N 	 	/*�ŷ�PID������������*/
//#define VCP_DUB_N			/*���⴮�ڳ���*/
#define COM_DUB_N			/*���ڳ���*/
#define STEPPER_DUB_N		 /*����*/
#define SERVO_POS_DUB_N	/*С���˶�����*/
#define SPI_FLASH_DUB_N	  /*25LC640 spi flash */
#define MP_DUB_N			/*��ֽ����*/
#define LP_DUB_N			/*�շ�ֽ*/
#else //****flash define**********************
#define BUZ_EN 				0
#define DELAY_EN 			1
#define KEY_EN 				0
#define LED103_EN 			1
#define LCM_GUI_EN 			0
#define COM_EN  			       0
#define ENCODER_EN		       0

#define UART_DRIVER_EN        1
#define SPI_FLASH_EN  		0
#define EXTI_EN				0
/******************************/
//*********flash dug*******
/* Private functions ---------------------------------*/
#define LCM_KEY_DUG_N 	/*LCM gui ����*/
#define FPGA_DUG_N

#define EXTI_DUG_N		/*�ⲿ�жϽŲ���*/
#define ENCODER_DUG_N  	/*�ŷ�PID������������*/
//#define VCP_DUB_N			/*���⴮�ڳ���*/
#define COM_DUB_N			/*���ڳ���*/
#define SPI_FLASH_DUB_N     /*25LC640 spi flash */
#endif

#endif//__PRINTER_CONFIG_H

