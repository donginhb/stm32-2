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


extern unsigned char TBUF,RBUF;

extern unsigned char TDAT,RDAT;

extern unsigned char TCNT,RCNT;

extern unsigned char TBIT,RBIT;

extern bit TING,RING;
extern bit TEND,REND;

extern unsigned char t, r;

extern unsigned char buf[32];


extern idata unsigned char tx_buf[];

extern idata unsigned char rx_buf[];

unsigned char RX_Flag=0;

unsigned char TX_Flag=0;


unsigned char count=100; //1000 times counter

unsigned int LED_Time=300;


//内存拷贝函数

void Copy_Mem (unsigned char *P1, unsigned char *P2,unsigned int Count);


void InitTime1(void);  //初始化定时器1




/**************************************************************************************
  函数功能：内存拷贝函数

**************************************************************************************/
void Copy_Mem (unsigned char *P1, unsigned char *P2,unsigned int Count)
{
   
   unsigned int i ;

   for(i=0;i<Count;i++)*P1++=*P2++;

  
}



void main(void)
{

  unsigned char i=0;
  unsigned int count_send=0;
  unsigned int rec_new=0;
  unsigned int rec_old=0;
  unsigned int rec_err=0;
  unsigned int lock_key=0;

  uartInit();	 //初始化串口


 ///一下为测试代码	  

//	  while (1)
//		{ //user's function
//		if (REND)
//		{
//			REND = 0;
//			buf[r++ & 0x0f] = RBUF;
//		}
//		if (TEND)
//		{
//			if (t != r)
//			{
//				TEND = 0;
//				TBUF = buf[t++ & 0x0f];
//				TING = 1;
//				}
//			}
//		}




  InitTime1();//初始化定时器1  

  Delay100ms();

  init_nrf24l01_io(); //初始化驱动NRF24L01的IO口

  Delay100ms();

  ifnnrf_rx_mode();	   //设置NRF24L01上电后为接收模式

  IRQ=1;

  while(IRQ==0);

   _delay_us(400);



  while(1)
  {
	
	IRQ=1;		  //等待NRF24L01接收中断

    if(IRQ==0) 	  //如果接收到了数据，则对接收到的数据进行处理

	  {        
        
		LED_Time=300;//点亮LED

		sta=SPI_Read(STATUS);		  //读取状态寄存器

        SPI_RW_Reg(WRITE_REG+STATUS,0xff);	  //进入到等待状态
        
        if(sta&STA_MARK_RX)					  //判断状态寄存器的状态，如果为接收到数据状态，则启动接收数据处理函数
	
		 { 
			
			SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);	 //读取接收数据到接收缓冲区

			t=0;//初始化发送数据长度

			while(t<TX_PLOAD_WIDTH)
			{

	      		if (TEND)
				  {
					
					//if (t != TX_PLOAD_WIDTH)
					//	{
							
							TEND = 0;
	
							TBUF = rx_buf[t];

							t++;
	
							TING = 1;
						
				//		}
					
					}
			      }		
               }
				else
				{
		            ifnnrf_CLERN_ALL();
		            
					ifnnrf_rx_mode();
		            
					IRQ=1;
		           
				    while(IRQ==0);
		
					 _delay_us(400);
		        }
            } //接收


	   //串口接收数据


		if (REND)
		{
		
			count=0;//清除超时标记

			REND = 0; //清除接收字节完成标记
									
			if(r<32)
			{
				
				buf[r] = RBUF;

				r++;

//				if(r>32)
//				{
//
//				 r=0;//如果接收数据超过缓冲区限制，则从缓冲区头开始接收数据。
//
//				}
				

			}

		}


	 if(RX_Flag==0xaa)
		 {
		   	 
			
			  RX_Flag=0x55;//清除接收到数据标记

			 //unsigned char j;

			  LED_Time=300;//点亮LED
			 
			  Copy_Mem (tx_buf, buf,r);

			  IRQ=1;
	
	          SPI_RW_Reg(WRITE_REG+STATUS,0xff);

			  ifnnrf_tx_mode();              //写数据到nrf24L01的发送缓冲区，最长32个字节

	          while(IRQ);	                  //等待NRF24L01的发送完中断信号
	
	          sta=SPI_Read(STATUS);         //读取状态寄存器
	
	          SPI_RW_Reg(WRITE_REG+STATUS,0xff);	  //进入到等待状态	  

			 if(sta&STA_MARK_TX)			  //如果发送完成，则闪烁LED灯
				{
		           
				       r=0;//清除接收数据长度
				       Delay100ms();
			   } 
			   else
			    {

		          ifnnrf_CLERN_ALL();		  //否则，清除本次发送，重新发
			    
				}


		 }
		if(RX_Flag==0x55)  //发送完，nrf2401 设置为接收模式

			{
				
				RX_Flag=0;

				ifnnrf_rx_mode();

		        IRQ=1;

		        while(IRQ==0);

		        _delay_us(400);

        
				}

	  
  }
}


/* define constants */

#define SYSclk  22118400L     //18432000L
			   
#define MODE1T //Timer clock mode, comment this line is 12T mode, uncomment is 1T mode

#ifdef MODE1T

	#define T1MS (65536-SYSclk/1000) //1ms timer calculation method in 1T mode

#else

	#define T1MS (65536-SYSclk/12/1000) //1ms timer calculation method in 12T mode

#endif




/* define SFR */
//sfr AUXR = 0x8e; //Auxiliary register
//sbit TEST_LED = P0^0; //work LED, flash once per second
/* define variables */


void InitTime1(void)
{
    
	
	//TMOD = 0x00; //set timer1 as mode0 (16-bit auto-reload)

	TL1 = T1MS; //initial timer1 low byte
	TH1 = T1MS >> 8; //initial timer1 high byte
	TR1 = 1; //timer1 start running
	ET1 = 1; //enable timer1 interrupt
	EA = 1; //open global interrupt switch

	count = 0; //initial counter

}




//-----------------------------------------------
/* Timer1 interrupt routine */
void tm1_isr() interrupt 3 using 1
{
	 if(count<5)
	  {

	   count++;

	  }
	  if(count==5)
	  {
		
		count++;

		RX_Flag=0xaa;


	  }



	  if(LED_Time>0)
	  {
	  
	  	led=0;
		
		LED_Time--;

	  }
	  else
	  {

		led=1;


	  }

}





