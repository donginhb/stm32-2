/****************************************Copyright (c)****************************************************
**
**                                   安阳新世纪电子研究所                                                      
**
**                                   http://www.ayxsj.com
**
**--------------File Info---------------------------------------------------------------------------------
**
** File name:			jf24.h
** Last modified Date:	2009-09-16
** Last Version:		V1.0
** Descriptions:	
**	
*********************************************************************************************************/
#ifndef __JF24C_H__

#define __JF24C_H__

//***********************************************************************************
//***     根据实际情况修改
//*********************************************************************************** 
 sbit SPI_MISO = P3^7;
 sbit RESET_N  = P1^4;
 sbit SPI_CLK  = P3^5;		
 sbit SPI_MOSI = P3^4;
 sbit SPI_SS   = P1^2;
// sbit FIFO_FLG = P1^3;
 sbit PKT_FLG  = P1^3;

sbit KEY_TX = P1^7;			
sbit LED_TX = P1^5;			
sbit LED_RX = P1^6;

//**********发送字节数，不包含实际数据长度**************
#define N 50		

//*************函数及常量声明，不需修改***************
#define IDLE_MASK	0xC0
#define READ_MASK	0x80
#define enter_idle()   write_spi_reg(REG7_IDLE);	//进入IDLE模式

		

extern void delay_1ms(unsigned char n);
extern void rf_rst(void);  				//JF24C复位
extern void tx_data(unsigned char data_tx[N]); 		//发送数据
extern void write_spi_byte(unsigned char spi_byte);	//写字节子函数
extern void write_spi_reg(unsigned char reg_table[3]);	//写三个字节
extern unsigned char read_spi_byte();			//读一个数据
extern void read_spi_reg(unsigned char reg_num,unsigned char read_data[2]);
extern void rx_data(unsigned char data_rx[N]);			//接收数据


 #endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/