/****************************************Copyright (c)****************************************************
**
**                                   安阳新世纪电子研究所    
**                                                  
**                                   http://www.ayxsj.com
**
**--------------File Info---------------------------------------------------------------------------------
**
** File name:			jf24.c
** Last modified Date:  2009-09-16
** Last Version:		V1.0
** Descriptions:		
**
*********************************************************************************************************/

#include<reg51.h>
#include<jf24c.h>	   
#include<intrins.h>


unsigned char code REG7_IDLE[3] = {	7,0x00,0x00	};	//进入IDLE模式时，寄存器2的值

unsigned char code REG7_TX[3] =   { 	7,0x01,0x05	};	//进入TX模式时，寄存器7的值

unsigned char code REG7_RX[3] =	{ 7,0x00,0x85	};	//进入RX模式时，寄存器7的值

unsigned char code REG82_TX[3] = {	82,0x80,0x00	};	//清FIFO写指针，寄存器82的值	

unsigned char code REG82_RX[3] = {	82,0x00,0x80	};	//清FIFO读指针，寄存器82的值		

unsigned char code FRAME_TABLE[11][3] = {  
			48,0x98,0x00,		//48号(引导码长度、同步头长度、Trailer长度)
			49,0xFF,0x8F,		//49号积存器号、初始值高、低字节
			50,0x50,0x14,		//50号积存器号、初始值高、低字节
			51,0x50,0x52,		//51号积存器号、初始值高、低字节 
          	52,0x80,0x01,		//52号（地址:同步头SYNC_WORD寄存器1）
			53,0xAA,0x55,		//53号（地址:同步头SYNC_WORD寄存器4）
			54,0xB7,0x5C,		//54号（地址:同步头SYNC_WORD寄存器3）
			55,0xD6,0x18,		//55号（地址:同步头SYNC_WORD寄存器2）
			56,0x44,0x04,		//56号积存器号、初始值高、低字节
			57,0xE0,0x00,		//57号（控制CRC、SCRAMBLE、数据包长度、是由MCU处理数据）
			0x0FF,0xFF,0xFF};

unsigned char code RF_TABLE[][3]={
			9,0x21,0x03,		// 9号积存器号、初始值高、低字节
			0,0x35,0x4D,	    // 0号积存器号、初始值高、低字节
			2,0x1E,0x01,		// 2号积存器号、初始值高、低字节
			4,0xBC,0xF0,		// 4号积存器号、初始值高、低字节
			5,0x00,0xA1,		// 5号积存器号、初始值高、低字节
			8,0x80,0x00,		// 8号积存器号、初始值高、低字节
			10,0x00,0x04,		//10号积存器号、初始值高、低字节
			11,0x40,0x41,		//11号积存器号、初始值高、低字节
			12,0x80,0x00,		//12号积存器号、初始值高、低字节
			13,0x00,0x00,		//13号积存器号、初始值高、低字节
			14,0x16,0x9B,		//14号积存器号、初始值高、低字节
			15,0x0D,0xED,		//15号积存器号、初始值高、低字节
			16,0xB0,0x00,		//16号积存器号、初始值高、低字节
			18,0xE0,0x00,		//18号积存器号、初始值高、低字节
			19,0xA1,0x14,		//19号积存器号、初始值高、低字节
			20,0x81,0x95,		//20号积存器号、初始值高、低字节
			21,0x69,0x62,		//21号积存器号、初始值高、低字节
			22,0x00,0x02,		//22号积存器号、初始值高、低字节
			23,0x00,0x02,		//23号积存器号、初始值高、低字节
			24,0xB1,0x40,		//24号积存器号、初始值高、低字节
			25,0xA8,0x0F,		//25号积存器号、初始值高、低字节
			26,0x3E,0x07,		//26号积存器号、初始值高、低字节
			28,0x58,0x00,		//28号积存器号、初始值高、低字节
			0xff,0xff,0xff
			};

//***************写一个字节***************************
void write_spi_byte(unsigned char spi_byte)
{
	unsigned char i;
	SPI_CLK=0;
	SPI_MOSI=0;
	  for(i=0;i<8;i++)
		{
			if((spi_byte&0x80)!=0)
				SPI_MOSI=1;
			else
				SPI_MOSI=0;
			SPI_CLK=1;
			_nop_();
			SPI_CLK=0;
			spi_byte<<=1;
		  }	 
} 
//***************写三个字节****************************
void write_spi_reg(unsigned char reg_table[3])
{
	SPI_SS=0;
	write_spi_byte(reg_table[0]);
	if((reg_table[0]<0x20))
		{
			_nop_();
			_nop_();
			_nop_();
		}
	write_spi_byte(reg_table[1]);
	write_spi_byte(reg_table[2]);
	if((reg_table[0]<0x20))
		{
			_nop_();
			_nop_();
			_nop_();
		}
  	SPI_SS=1;
}

//****************寄存器组初始化***********************
void reg_init(unsigned char reg_table[][3])
{
		unsigned char i;
		for(i=0;*(reg_table[i])!=0xFF;i++)
		 {
		 	write_spi_reg(reg_table[i]);
		 }	 	
}

//*******************读取一个字节********************** 
unsigned char read_spi_byte()
{
 	unsigned char i,spi_byte=0;
	SPI_CLK=0;
	SPI_MOSI=0;
	  for(i=0;i<8;i++)
		{
			SPI_CLK=1;
			if(SPI_MISO)
				spi_byte++;
			SPI_CLK=0;
			if(i<7)
				spi_byte<<=1;
		}
	return(spi_byte);
}  

//*****************读取一个寄存器***********************
void read_spi_reg(unsigned char reg_num,unsigned char read_data[2])
{
	SPI_SS=0;
	reg_num|=0x80;
	write_spi_byte(reg_num);
	if(reg_num<0xa0)
		{
			_nop_();
			_nop_();
			_nop_();
		}
	read_data[0]=read_spi_byte();
	read_data[1]=read_spi_byte();
	SPI_SS=1;
}
 
//*************jf24c初始化子函数************************   
void rf_rst(void)
{
	SPI_CLK=0;
	SPI_MOSI=0;
	RESET_N=0;

	_nop_();
	_nop_();
	_nop_();

	RESET_N=1;

	delay_1ms(3);

	reg_init(FRAME_TABLE);

	delay_1ms(2);

	reg_init(RF_TABLE);

	delay_1ms(2);
	enter_idle();
	
}

//**************发送数据************************
  void tx_data(unsigned char data_tx[N])
{
	unsigned char i;
	enter_idle();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	write_spi_reg(REG82_TX);

	SPI_SS=0;
	write_spi_byte(80);
	write_spi_byte(N);
	for(i=0;i<N;i++)
	{
		write_spi_byte(data_tx[i]);
	}
	SPI_SS=1;

	write_spi_reg(REG7_TX);
	while(!PKT_FLG);
		
}

//******************接收**********************************
void rx_data(unsigned char data_rx[N])
{
 	unsigned char i;

	enter_idle();
	write_spi_reg(REG82_RX);	 	//清FIFO读指针
	write_spi_reg(REG7_RX);		 	//开RX并选择频道		
	while(!PKT_FLG);			 	//等待就收标志

	SPI_SS=0;
	write_spi_byte(0xd0);		 	//写FIFO地址

	while((read_spi_byte()!=N))	;

	for(i=0;i<N;i++)
	{
		data_rx[i]=read_spi_byte();
	 }
	 SPI_SS=1;
		
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/