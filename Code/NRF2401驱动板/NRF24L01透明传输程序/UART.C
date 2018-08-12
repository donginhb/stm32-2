#include "typedef.h"
#include "gpio.h"
#include "uart.h"


static bit bUartFlag;


//sfr  AUXR = 0x8E;
sbit RXB = P3^0; //define UART TX/RX port

sbit TXB = P3^1;

//typedef bit BOOL;
//typedef unsigned char BYTE;
//typedef unsigned int WORD;

unsigned char TBUF,RBUF;

unsigned char TDAT,RDAT;

unsigned char TCNT,RCNT;

unsigned char TBIT,RBIT;

 bit TING,RING;

 bit TEND,REND;

unsigned char t, r;

unsigned char buf[33];



//initial UART module variable


 void UART_INIT(void)
	{
		TING=0;
		RING=0;
		TEND=1;
		REND=0;
		TCNT=0;
		RCNT=0;
	}

/******************************************************************************/
// 函数名称：uartInit 
// 输入参数：无 
// 输出参数：无 
// 函数功能：设置好定时器0的工作模式 
/******************************************************************************/
void uartInit(void)
{
    /*
     * 设置定时器0为16位自动重载定时器
    */

	TMOD = 0x00; //设置定时器为模式0(16位自动重装载)
    AUXR = 0xC0; //定时器0为1T模式   同时初始化 定时器1为1T模式
    
	//TL0 = (0xFFFF - MCU_FREQ / UART_BUAD) & 0xFF; //设置定时初值
	//TH0 = ((0xFFFF - MCU_FREQ / UART_BUAD) >> 8) & 0xFF; //设置定时初值
    
	
	TL0 = BAUD;
    TH0 = BAUD>>8;
	
	
	TR0 = 1; //定时器0开始计时
    ET0 = 1; //使能定时器0中断
	PT0 = 1;
    EA = 1;  //开总中断

	UART_INIT();	//开波特率发生器定时器



}


/******************************************************************************/
// 函数名称：time0ISR 
// 输入参数：无 
// 输出参数：无 
// 函数功能：串口0服务函数 
/******************************************************************************/
void time0ISR(void) interrupt 1 using 1
{

  if (RING)
	{
	if (--RCNT == 0)
	{
		RCNT = 3; //reset send baudrate counter
		if (--RBIT == 0)
		{
			RBUF = RDAT; //save the data to RBUF
			RING = 0; //stop receive
			REND = 1; //set receive completed flag
		}
		else
		{
			RDAT >>= 1;
			if (RXB) RDAT |= 0x80; //shift RX data to RX buffer
		}
	  }
	}
   else if (!RXB)
   {
		RING = 1; //set start receive flag
		RCNT = 4; //initial receive baudrate counter
		RBIT = 9; //initial receive bit number (8 data bits + 1 stop bit)
	}
   if (--TCNT == 0)
	{
		TCNT = 3; //reset send baudrate counter
		if (TING) //judge whether sending
		{
			if (TBIT == 0)
			{
				TXB = 0; //send start bit
				TDAT = TBUF; //load data from TBUF to TDAT
				TBIT = 9; //initial send bit number (8 data bits + 1 stop bit)
			}
	       else
			{
				TDAT >>= 1; //shift data to CY
				if (--TBIT == 0)
				{
					TXB = 1;
					TING = 0; //stop send
					TEND = 1; //set send completed flag
				}
				else
				{
					TXB = CY; //write CY to TX port
				 }
			}
		}
	}
}








