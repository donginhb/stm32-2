/****************************************Copyright (c)****************************************************
**
**                                   ���������͵����о���                                                      
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
//***     ����ʵ������޸�
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

//**********�����ֽ�����������ʵ�����ݳ���**************
#define N 50		

//*************���������������������޸�***************
#define IDLE_MASK	0xC0
#define READ_MASK	0x80
#define enter_idle()   write_spi_reg(REG7_IDLE);	//����IDLEģʽ

		

extern void delay_1ms(unsigned char n);
extern void rf_rst(void);  				//JF24C��λ
extern void tx_data(unsigned char data_tx[N]); 		//��������
extern void write_spi_byte(unsigned char spi_byte);	//д�ֽ��Ӻ���
extern void write_spi_reg(unsigned char reg_table[3]);	//д�����ֽ�
extern unsigned char read_spi_byte();			//��һ������
extern void read_spi_reg(unsigned char reg_num,unsigned char read_data[2]);
extern void rx_data(unsigned char data_rx[N]);			//��������


 #endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/