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
#define SERVO_DUG_N		/* 伺服测试*/
#define LCM_KEY_DUG_N		/*LCM gui 测试*/

#define FPGA_DUG_N 			/*fpga 接口调试*/
#define EXTI_DUG_N			/*外部中断脚测试*/
#define ENCODER_DUG_N 	 	/*伺服PID，编码器测试*/
//#define VCP_DUB_N			/*虚拟串口程序*/
#define COM_DUB_N			/*串口程序*/
#define STEPPER_DUB_N		 /*步进*/
#define SERVO_POS_DUB_N	/*小车运动控制*/
#define SPI_FLASH_DUB_N	  /*25LC640 spi flash */
#define MP_DUB_N			/*吸纸风扇*/
#define LP_DUB_N			/*收放纸*/
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
#define LCM_KEY_DUG_N 	/*LCM gui 测试*/
#define FPGA_DUG_N

#define EXTI_DUG_N		/*外部中断脚测试*/
#define ENCODER_DUG_N  	/*伺服PID，编码器测试*/
//#define VCP_DUB_N			/*虚拟串口程序*/
#define COM_DUB_N			/*串口程序*/
#define SPI_FLASH_DUB_N     /*25LC640 spi flash */
#endif

#endif//__PRINTER_CONFIG_H

