//fpga_driver.c
#include "includes.h"

#if FPGA_DRIVER_EN > 0

#define LCM_PWM_PERIOD_REG_L_ADDR 		0x01
#define LCM_PWM_PERIOD_REG_H_ADDR 		0x02
#define LCM_PWM_PULSE_WIDTH_REG_L_ADDR 		0x03
#define LCM_PWM_PULSE_WIDTH_REG_H_ADDR 	        0x04
//收放纸系统
#define WIND_REG_ADDR 	  0x06 		//6'h06 	//load
#define UNWIND_REG_ADDR   0x07  	 // 6'h07	//unload
	#define WIND_AFTER_ROTATE  	(u8)(1<<0)  
	#define WIND_BEFORE_ROTATE 	(u8)(1<<1)
	#define WIND_STOP				 (WIND_AFTER_ROTATE|WIND_BEFORE_ROTATE)
/*#################和mcu 有关的定义   开始......################*/
void Init_FpgaGpio( void )
{

	GPIO_InitTypeDef GPIO_InitStructure;
	/*----- Configure IO connected to ---------------------*/
	 /* ------Enable GPIO  clock --------------------------*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_FPGA_ADDR, ENABLE ) ;
	//RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_FPGA_ADDR1, ENABLE ) ;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_FPGA_CTL , ENABLE ) ;
	
	GPIO_InitStructure.GPIO_Pin = FPGA_CS_PIN | FPGA_RD_PIN|FPGA_WR_PIN |FPGA_A5 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_FPGA_CTL ;
	GPIO_Init( GPIO_FPGA_CTL , &GPIO_InitStructure );
	
	GPIO_SetBits( GPIO_FPGA_CTL ,  FPGA_CS_PIN ) ; 
	GPIO_SetBits( GPIO_FPGA_CTL ,  FPGA_WR_PIN ) ;
	GPIO_SetBits( GPIO_FPGA_CTL ,  FPGA_RD_PIN ) ;  

	GPIO_ResetBits( GPIO_FPGA_ADDR1 ,  FPGA_A5 ) ;  
	
	GPIO_InitStructure.GPIO_Pin = FPGA_A0 | FPGA_A1 | FPGA_A2| FPGA_A3 |FPGA_A4  ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_FPGA_ADDR ;	
	GPIO_Init( GPIO_FPGA_ADDR , &GPIO_InitStructure );

	GPIO_ResetBits( GPIO_FPGA_ADDR ,  FPGA_A0) ;  
	GPIO_ResetBits( GPIO_FPGA_ADDR ,  FPGA_A1) ; 
	GPIO_ResetBits( GPIO_FPGA_ADDR ,  FPGA_A2) ; 
	GPIO_ResetBits( GPIO_FPGA_ADDR ,  FPGA_A3) ; 
	GPIO_ResetBits( GPIO_FPGA_ADDR ,  FPGA_A4) ; 
	Delaynus(1000000); 	/*冷启动后 fpga 处在配置阶段*/
	{
		//Delaynus(1000000); 
		//lcd 偏压模块设置
		//period = (fpga_clk /fpwm ) -1   --pwm freq 1000Hz
	      FPGA_WriteByteData(  LCM_PWM_PERIOD_REG_L_ADDR, (u8)899 );  /*20k*/
		FPGA_WriteByteData(  LCM_PWM_PERIOD_REG_H_ADDR , (u8)(899>>8) );  
		//pulse_width = (period + 1)* 70% =    //70%
	      FPGA_WriteByteData(  LCM_PWM_PULSE_WIDTH_REG_L_ADDR , (u8)422  ); 
	      FPGA_WriteByteData( LCM_PWM_PULSE_WIDTH_REG_H_ADDR  , (u8)(422>>8) );  /*70%*/   
		/*
 			data =  FPGA_ReadByteData( LCM_PWM_PERIOD_REG_L_ADDR );
			 data =  FPGA_ReadByteData( LCM_PWM_PERIOD_REG_H_ADDR );
		  	data =  FPGA_ReadByteData( LCM_PWM_PULSE_WIDTH_REG_L_ADDR );
		  	 data =  FPGA_ReadByteData( LCM_PWM_PULSE_WIDTH_REG_H_ADDR );
		*/		   
	}		  	  
}
/*******************************************************************************
* Function Name  : FPGA_DataPortIOSet
* Description    : 驱动FPGA 数据端口输入输出模式设定, fpga和lcm共用8bit数据总线
* Input          : - InOutMode:
* Output         : None
* Return         : None
*******************************************************************************/
void FPGA_DataPortIOSet(u8 WrRdMode)/*FPGA D0--D7 ---MCU( PD0--PD7)  */
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	LF_DataBusForFPGA();
	
	GPIO_InitStructure.GPIO_Pin = LCM_DATA0_PIN |LCM_DATA1_PIN|LCM_DATA2_PIN|LCM_DATA3_PIN\
	  						|LCM_DATA4_PIN |LCM_DATA5_PIN|LCM_DATA6_PIN|LCM_DATA7_PIN;	

	if( WrRdMode == DATA_BUS_READ_MODE )//in mode
	  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING ;		 //GPIO_Mode_Out_PP ;/*pull up input*/
	else if( WrRdMode ==  DATA_BUS_WRITE_MODE )//out mode
	  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP ;			 //GPIO_Mode_Out_PP ;/*pull up input*/
	else
		return;
	  
	  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_FPGA_DATA ;
	  GPIO_Init( GPIO_FPGA_DATA , &GPIO_InitStructure );
	  
}

void FPGA_WrRdDelay( )
{
	Delay(3);
}
void  BusyCheckTimeOut()
{
	Delay(4);
	while(1);
}

void FPGA_WriteAddr( u8 addr)
{
	u8 taddr = 0x3f&addr;

	if( taddr&(1<<0) )
		GPIO_SetBits( GPIO_FPGA_ADDR,  FPGA_A0) ; 
	else
		GPIO_ResetBits( GPIO_FPGA_ADDR,  FPGA_A0) ; 
	
	if( taddr&(1<<1) )
		GPIO_SetBits( GPIO_FPGA_ADDR,  FPGA_A1) ; 
	else
		GPIO_ResetBits( GPIO_FPGA_ADDR,  FPGA_A1) ; 
	
	if( taddr&(1<<2) )
		GPIO_SetBits( GPIO_FPGA_ADDR,  FPGA_A2) ; 
	else
		GPIO_ResetBits( GPIO_FPGA_ADDR,  FPGA_A2) ; 
	
	if( taddr&(1<<3) )
		GPIO_SetBits( GPIO_FPGA_ADDR,  FPGA_A3) ; 
	else
		GPIO_ResetBits( GPIO_FPGA_ADDR,  FPGA_A3) ; 
	
	if( taddr&(1<<4) )
		GPIO_SetBits( GPIO_FPGA_ADDR,  FPGA_A4) ; 
	else
		GPIO_ResetBits( GPIO_FPGA_ADDR,  FPGA_A4) ; 
	
	if( taddr&(1<<5) )
		GPIO_SetBits( GPIO_FPGA_ADDR1,  FPGA_A5) ; 
	else
		GPIO_ResetBits( GPIO_FPGA_ADDR1,  FPGA_A5) ; 
		
}
/*
1,向fpga写数据或地址
*/
void FPGA_WriteByteData( u8  addr ,u8 nByte )
{
	FPGA_DataPortIOSet( DATA_BUS_WRITE_MODE );
	
	GPIO_SetBits( GPIO_FPGA_CTL ,  FPGA_RD_PIN ) ; 	
			
	LF_GPIO_WriteLow8Bit( GPIO_FPGA_DATA ,nByte );
	FPGA_WriteAddr(addr);
	
	GPIO_ResetBits( GPIO_FPGA_CTL ,  FPGA_CS_PIN ) ;  
	GPIO_ResetBits( GPIO_FPGA_CTL ,  FPGA_WR_PIN ) ;	
	FPGA_WrRdDelay( );
	GPIO_SetBits( GPIO_FPGA_CTL ,  FPGA_WR_PIN ) ; 	
	GPIO_SetBits( GPIO_FPGA_CTL ,  FPGA_CS_PIN ) ;  
			
}
u8 FPGA_ReadByteData( u8  addr  )
{
	u8 nbyte = 0;
	FPGA_DataPortIOSet( DATA_BUS_READ_MODE );	
	GPIO_SetBits( GPIO_FPGA_CTL ,  FPGA_WR_PIN ) ; 	
			
	FPGA_WriteAddr(addr);
	
	GPIO_ResetBits( GPIO_FPGA_CTL ,  FPGA_CS_PIN ) ;  
	GPIO_ResetBits( GPIO_FPGA_CTL ,   FPGA_RD_PIN ) ;		
	FPGA_WrRdDelay( );
	
	nbyte = (u8)GPIO_ReadInputData( GPIO_FPGA_DATA ) ;
	
	GPIO_SetBits( GPIO_FPGA_CTL ,  FPGA_RD_PIN ) ; 	
	GPIO_SetBits( GPIO_FPGA_CTL ,  FPGA_CS_PIN ) ;  
	
	return nbyte;
}
//


//
//u8 data;
void FPGA_Test(void)
{
	//u32 i ;        
	
	{
	/* -- 20090519 test ok   收放纸控制控制
		#define NUS_TIME    3000000
		//wind
            
		FPGA_WriteByteData(  WIND_REG_ADDR , WIND_AFTER_ROTATE ); 
		Delaynus(NUS_TIME);
		FPGA_WriteByteData(  WIND_REG_ADDR , WIND_STOP ); 
		Delaynus(NUS_TIME);
		FPGA_WriteByteData(  WIND_REG_ADDR , WIND_BEFORE_ROTATE ); 
		Delaynus(NUS_TIME);
		FPGA_WriteByteData(  WIND_REG_ADDR , WIND_STOP ); 
		Delaynus(NUS_TIME);
		//
		LedAutoOnOff(LED2);
		//unwind
		FPGA_WriteByteData(  UNWIND_REG_ADDR , WIND_AFTER_ROTATE ); 
		Delaynus(NUS_TIME);
		FPGA_WriteByteData(  UNWIND_REG_ADDR , WIND_STOP ); 
		Delaynus(NUS_TIME);
		FPGA_WriteByteData(  UNWIND_REG_ADDR , WIND_BEFORE_ROTATE ); 
		Delaynus(NUS_TIME);
		FPGA_WriteByteData(  UNWIND_REG_ADDR , WIND_STOP ); 
		Delaynus(NUS_TIME);
		LedAutoOnOff(LED2)	;			
          */	
	}
	//while(1)
	{	
		
	}
	
}

#endif //#if FPGA_DRIVER_EN > 0

