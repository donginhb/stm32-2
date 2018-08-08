#include "typedef.h"
#include "gpio.h"
#include "uart.h"
#include "nrf_24l01.h"
#include "delay.h"

/******************************************************************************/
// 函数名称：main 
// 输入参数： 
// 输出参数： 
// 函数功能： 
/******************************************************************************/
void main(void)
{
  unsigned char i=0;

  unsigned int count_send=0;
  unsigned int rec_new=0;
  unsigned int rec_old=0;
  unsigned int rec_err=0;
  unsigned int lock_key=0;


  uartInit();	 //初始化串口

  Delay100ms();

  init_nrf24l01_io(); //初始化驱动NRF24L01的IO口

//  led=0;
//  Delay100ms();
//  led=1;
//  Delay100ms();
//  led=0;
//  Delay100ms();
//  led=1;
//  Delay100ms();
//  TI=1;
  Delay100ms();


  uartSendString("READY!\r\n");


  ifnnrf_rx_mode();	   //设置NRF24L01上电后为接收模式



  while(1)
  {

    KEY=1;

    KEY2=1;

    while(KEY == 0 || KEY2 == 0)		  	//发送:当有按键按下的时候，将测试数据通过无线模块发送出去。
	{
        
		IRQ=1;

        SPI_RW_Reg(WRITE_REG+STATUS,0xff);

        if (KEY == 0)
		{
            tx_buf[0]=0xAA;
        } 
		else if (KEY2 == 0) 
		{
            tx_buf[0]=0x55;
        }

        ifnnrf_tx_mode();              //写数据到nrf24L01的发送缓冲区，最长32个字节

        while(IRQ);	                  //等待NRF24L01的发送完中断信号

        sta=SPI_Read(STATUS);         //读取状态寄存器

        SPI_RW_Reg(WRITE_REG+STATUS,0xff);	  //进入到等待状态

        if(sta&STA_MARK_TX)			  //如果发送完成，则闪烁LED灯
		{
            if (KEY == 0)
			{
        		led=0;
        		Delay100ms();
        		led=1;
                Delay100ms();
            } 
			else
			 {
        		led2=0;
        		Delay100ms();
        		led2=1;
                Delay100ms();
            }
	   } 
	   else
	    {
            ifnnrf_CLERN_ALL();		  //否则，清除本次发送，重新发
	    }

	   lock_key=1;

    }
		//发送
    if(lock_key) 
	{
        lock_key=0;

        ifnnrf_rx_mode();	//进入到接收模式，等待接收数据

        IRQ=1;				//设置中断接收标记

        while(IRQ==0);	    //等待中断

        _delay_us(400);		//延时

    }

    IRQ=1;

    if(IRQ==0) 			 //如果接收到了数据，则对接收到的数据进行处理

	{        
        sta=SPI_Read(STATUS);		  //读取状态寄存器

        SPI_RW_Reg(WRITE_REG+STATUS,0xff);	  //进入到等待状态
        
        if(sta&STA_MARK_RX)					  //判断状态寄存器的状态，如果为接收到数据状态，则启动接收数据处理函数
		{ 
            SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);	 //读取接收数据到接收缓冲区

            if (rx_buf[0] == 0xAA) 
			{
                uartSendString("你按下了左边按键\r\n");
                led=0;
                Delay100ms();
                led=1;
                Delay100ms();
            } 
			else if (rx_buf[0] == 0x55)
			{
                uartSendString("你按下了右边按键\r\n");
        		led2=0;
        		Delay100ms();
        		led2=1;
                Delay100ms();
            }
            rx_buf[0] = 0;
        }
		else
		{
            ifnnrf_CLERN_ALL();
            ifnnrf_rx_mode();
            IRQ=1;
            while(IRQ==0);
        }
    } //接收
	  
  }
}