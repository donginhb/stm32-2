/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : platform_config.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : Evaluation board specific configuration file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes -----------------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */

/* Define the STM32F10x hardware depending on the used evaluation board */
//
//----gpio speed-------------------------------------------------
#define GPIOA_SPEED	 GPIO_Speed_50MHz
#define GPIOB_SPEED	 GPIO_Speed_50MHz
#define GPIOC_SPEED	 GPIO_Speed_50MHz
#define GPIOD_SPEED  GPIO_Speed_50MHz
#define GPIOE_SPEED	 GPIO_Speed_50MHz

//**board gpio use define *****************************************
//----led1 led2---------------------
  #define LED_PIN0  	GPIO_Pin_5
  #define LED_PIN1  	GPIO_Pin_6  
  #define GPIO_LED     				GPIOE
  #define GPIO_SPEED_LED			GPIOE_SPEED
  #define RCC_APB2Periph_GPIO_LED	RCC_APB2Periph_GPIOE
//#endif /* USE_STM3210B_EVAL */

//***SERVO*****io output***
/***Y    轴**********/
#define SERVO_IN1_PIN	GPIO_Pin_8   //Remap TIM1_CH1N--PE8
#define SERVO_IN2_PIN 	GPIO_Pin_9	 //Remap TIM1_CH1--PE9
/****X    轴*********/
#define SERVO_IN21_PIN	GPIO_Pin_10   //Remap TIM1_CH2N--PE10
#define SERVO_IN22_PIN 	GPIO_Pin_11	 //Remap TIM1_CH2--PE11

#define GPIO_SERVO  						GPIOE
#define GPIO_SPEED_SERVO				GPIOE_SPEED
#define RCC_APB2Periph_GPIO_SERVO		RCC_APB2Periph_GPIOE

//--encoder 编码器输入-
//-Y-轴编码器输入--------TIMER2_HANDLES_ENCODER-
#define GPIO_ECODER_T1_PIN				GPIO_Pin_0   /*T1 --A*/
#define GPIO_ECODER_T2_PIN 			GPIO_Pin_1	  /*T2 --B*/
#define GPIO_ECODER						GPIOA
#define RCC_APB2Periph_GPIO_ECODER	RCC_APB2Periph_GPIOA
//-x-轴编码器输入--------TIMER3_HANDLES_ENCODER
#define GPIO_ECODER_X_T1_PIN			GPIO_Pin_6   /*T1 --A*/
#define GPIO_ECODER_X_T2_PIN 			GPIO_Pin_7	 /*T2 --B*/
#define GPIO_ECODER_X						GPIOB
#define RCC_APB2Periph_GPIO_ECODER_X	RCC_APB2Periph_GPIOB

//**BUZ******************************************************
#define BUZ_PIN6					GPIO_Pin_10

#define GPIO_BUZ 					GPIOC
#define GPIO_SPEED_BUZ 				GPIOC_SPEED
#define RCC_APB2Periph_GPIO_BUZ	RCC_APB2Periph_GPIOC

//**setpper*************************************************
//--setpper-74hc164--------------------------------------------
//#define STEP_164_RST GPIO_Pin_
#define STEP_164_CLK_PIN 	GPIO_Pin_0	/*output PE0 stm32-pin97*/
#define STEP_164_D12_PIN 	GPIO_Pin_1	/*output PE1 stm32-pin98*/

#define GPIO_STEP_164     				GPIOE
#define GPIO_SPEED_STEP_164			GPIOE_SPEED
#define RCC_APB2Periph_GPIO_STEP_164	RCC_APB2Periph_GPIOE

//---key io---------stm32f103 board-------------------------
#define KEY_PIN2 	GPIO_Pin_0 /*PC0*/
#define KEY_PIN3	GPIO_Pin_1  /*PC1*/

#define GPIO_KEY 				  	GPIOC
#define GPIO_SPEED_KEY			  	GPIOC_SPEED
#define RCC_APB2Periph_GPIO_KEY	  RCC_APB2Periph_GPIOC

//---lcd io----------------------------------------
//*******data gpio********************************
#define LCM_DATA0_PIN  GPIO_Pin_0  	/*stm32 (pin81)--245--LCM pin18*/
#define LCM_DATA1_PIN  GPIO_Pin_1	/*stm32 (pin82)--245--LCM pin17*/
#define LCM_DATA2_PIN  GPIO_Pin_2	/*stm32 (pin83)--245--LCM pin16*/
#define LCM_DATA3_PIN  GPIO_Pin_3	/*stm32 (pin84)--245--LCM pin15*/
#define LCM_DATA4_PIN  GPIO_Pin_4	/*stm32 (pin85)--245--LCM pin14*/
#define LCM_DATA5_PIN  GPIO_Pin_5	/*stm32 (pin86)--245--LCM pin13*/
#define LCM_DATA6_PIN  GPIO_Pin_6	/*stm32 (pin87)--245--LCM pin12*/
#define LCM_DATA7_PIN  GPIO_Pin_7	/*stm32 (pin88)--245--LCM pin11*/

#define GPIO_LCM_DATA 					GPIOD
#define GPIO_SPEED_LCM_DATA 			GPIOD_SPEED
#define RCC_APB2Periph_GPIO_LCM_DATA 	RCC_APB2Periph_GPIOD

#define LCM_DATA_DIR_PIN 		GPIO_Pin_12	/*control hc245 dir */
#define LCM_DATA_OUT_EN_PIN  	GPIO_Pin_11	 /*74hc245的 /OE pin   低有效work, , 高Z 高阻*/

#define GPIO_LCM_DATA_DIR_EN 					GPIOA
#define GPIO_SPEED_LCM_DATA_DIR_EN 				GPIOA_SPEED
#define RCC_APB2Periph_GPIO_LCM_DATA_DIR_EN 	RCC_APB2Periph_GPIOA

//******ctr gpio**********************************
#define LCM_WR_PIN   GPIO_Pin_6   	/*pc stm32 (pin64)---LCM (pin5)*/
#define LCM_RD_PIN   GPIO_Pin_7		/*pc stm32 (pin65)---LCM (pin6)*/
#define LCM_CD_PIN   GPIO_Pin_9		/*pc stm32 (pin66)---LCM (pin8)*/
#define LCM_CE_PIN   GPIO_Pin_8		/*pc stm32 (pin78)---LCM (pin7)*/
#define LCM_FS_PIN   GPIO_Pin_9		/*pa stm32 (pin68)---LCM (pin19),  Font Select , L =  8x8 dot matrix ,*/

#define LCM_DIR_PIN						GPIO_Pin_12 /*pa stm32 (pin71)--245*/
/*sch 此脚悬空，应接mcu io ,或接RC */
#define GPIO_LCM_CTR 					GPIOC
#define GPIO_SPEED_LCM_CTR 			GPIOC_SPEED
#define RCC_APB2Periph_GPIO_LCM_CTR 	RCC_APB2Periph_GPIOC

#define LCM_RST_PIN						GPIO_Pin_8	/*stm32 (pin67)---LCM (pin10)*/
#define GPIOA_LCM_CTR 					GPIOA
#define GPIOA_SPEED_LCM_CTR 			GPIOA_SPEED
#define RCC_APB2Periph_GPIOA_LCM_CTR 	RCC_APB2Periph_GPIOA


/***************************************
*1, TIM1     servo pwm,  ch1~ch3 双极性
*2, TIM2     Encoder
*3, TIM3     key, pos
*4, TIM4   Setpper
***************************************/
//------sys tim use define ---KEY_TIMER---------------------------------------------
#define  TIM_CCR_VAl_KEY_SCAN  			(10) 		 /*key scan 10ms*/
#define  TIM_CCR_VAl_SYS_POS_CTR  		(1) 	/* pos ctr 1ms*/
#define TIM_CCR_VAl_P_MOTOR_SENSOR_SAMPLEING (2 ) /*5ms*/
#define TIM_IT_CC_KEY   TIM_IT_CC1
#define TIM_IT_CC_POS   TIM_IT_CC2
#define TIM_IT_CC_PM    TIM_IT_CC3
/**********encoder counter  full interrupt******************************/
#define ENCODER_TIMER  				TIM2  		// Encoder unit connected to TIM2
#define RCC_APB1Periph_ENC_TIM 	RCC_APB1Periph_TIM2 
#define ENCODER_IRQChannel   		TIM2_IRQChannel  	/*NVIC IRQChannel */
#define  ENCODER_TIM_IRQHandler  	TIM2_IRQHandler  	/*中断函数*/

/*******key time scan***************************/
#define KEY_TIMER  					TIM3			 /*key scan timer*/
#define  RCC_APB1Periph_KEY_TIM  	RCC_APB1Periph_TIM3
#define KEYSCAN_IRQChannel   		TIM3_IRQChannel  		/*NVIC IRQChannel */
#define KEY_IRQHandler 				TIM3_IRQHandler  		/*中断函数*/

/*********capture postion********************************************/
#if 1
#define  POS_TIMER  					TIM3			 /**/
#define  RCC_APB1Periph_POS_TIM  	RCC_APB1Periph_TIM3
#define  POS_IRQChannel  	 		TIM3_IRQChannel  		/*NVIC IRQChannel */
#define  POS_IRQHandler  			TIM3_IRQHandler  		/*中断函数*/
#endif
#if 1 	/*收放纸*/
#define  PM_TIMER  					TIM3			 /**/
#define  RCC_APB1Periph_PM_TIM  	RCC_APB1Periph_TIM3
#define  PM_IRQChannel  	 		TIM3_IRQChannel  		/*NVIC IRQChannel */
#define  PM_IRQHandler  			TIM3_IRQHandler  		/*中断函数*/
#endif
/*********setpper********************************************/
//spi flash 25lc640
#define SPIF_SS_PIN    	GPIO_Pin_12
#define SPIF_CLK_PIN   	GPIO_Pin_13
#define SPIF_MISO_PIN 	GPIO_Pin_15
#define SPIF_MOSI_PIN 	GPIO_Pin_14

#define GPIO_SPIF				GPIOB
#define GPIO_SPEED_SPIF			GPIOB_SPEED
#define RCC_APB2Periph_GPIO_SPIF 	RCC_APB2Periph_GPIOB
/* Exported functions ------------------------------------------------------- */
/* Exported macro ------------------------------------------------------------*/

#endif /* __PLATFORM_CONFIG_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
