/****************************************Copyright (c)****************************************************
**
**                                   ���������͵����о���    
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


unsigned char code REG7_IDLE[3] = {	7,0x00,0x00	};	//����IDLEģʽʱ���Ĵ���2��ֵ

unsigned char code REG7_TX[3] =   { 	7,0x01,0x05	};	//����TXģʽʱ���Ĵ���7��ֵ

unsigned char code REG7_RX[3] =	{ 7,0x00,0x85	};	//����RXģʽʱ���Ĵ���7��ֵ

unsigned char code REG82_TX[3] = {	82,0x80,0x00	};	//��FIFOдָ�룬�Ĵ���82��ֵ	

unsigned char code REG82_RX[3] = {	82,0x00,0x80	};	//��FIFO��ָ�룬�Ĵ���82��ֵ		

unsigned char code FRAME_TABLE[11][3] = {  
			48,0x98,0x00,		//48��(�����볤�ȡ�ͬ��ͷ���ȡ�Trailer����)
			49,0xFF,0x8F,		//49�Ż������š���ʼֵ�ߡ����ֽ�
			50,0x50,0x14,		//50�Ż������š���ʼֵ�ߡ����ֽ�
			51,0x50,0x52,		//51�Ż������š���ʼֵ�ߡ����ֽ� 
          	52,0x80,0x01,		//52�ţ���ַ:ͬ��ͷSYNC_WORD�Ĵ���1��
			53,0xAA,0x55,		//53�ţ���ַ:ͬ��ͷSYNC_WORD�Ĵ���4��
			54,0xB7,0x5C,		//54�ţ���ַ:ͬ��ͷSYNC_WORD�Ĵ���3��
			55,0xD6,0x18,		//55�ţ���ַ:ͬ��ͷSYNC_WORD�Ĵ���2��
			56,0x44,0x04,		//56�Ż������š���ʼֵ�ߡ����ֽ�
			57,0xE0,0x00,		//57�ţ�����CRC��SCRAMBLE�����ݰ����ȡ�����MCU�������ݣ�
			0x0FF,0xFF,0xFF};

unsigned char code RF_TABLE[][3]={
			9,0x21,0x03,		// 9�Ż������š���ʼֵ�ߡ����ֽ�
			0,0x35,0x4D,	    // 0�Ż������š���ʼֵ�ߡ����ֽ�
			2,0x1E,0x01,		// 2�Ż������š���ʼֵ�ߡ����ֽ�
			4,0xBC,0xF0,		// 4�Ż������š���ʼֵ�ߡ����ֽ�
			5,0x00,0xA1,		// 5�Ż������š���ʼֵ�ߡ����ֽ�
			8,0x80,0x00,		// 8�Ż������š���ʼֵ�ߡ����ֽ�
			10,0x00,0x04,		//10�Ż������š���ʼֵ�ߡ����ֽ�
			11,0x40,0x41,		//11�Ż������š���ʼֵ�ߡ����ֽ�
			12,0x80,0x00,		//12�Ż������š���ʼֵ�ߡ����ֽ�
			13,0x00,0x00,		//13�Ż������š���ʼֵ�ߡ����ֽ�
			14,0x16,0x9B,		//14�Ż������š���ʼֵ�ߡ����ֽ�
			15,0x0D,0xED,		//15�Ż������š���ʼֵ�ߡ����ֽ�
			16,0xB0,0x00,		//16�Ż������š���ʼֵ�ߡ����ֽ�
			18,0xE0,0x00,		//18�Ż������š���ʼֵ�ߡ����ֽ�
			19,0xA1,0x14,		//19�Ż������š���ʼֵ�ߡ����ֽ�
			20,0x81,0x95,		//20�Ż������š���ʼֵ�ߡ����ֽ�
			21,0x69,0x62,		//21�Ż������š���ʼֵ�ߡ����ֽ�
			22,0x00,0x02,		//22�Ż������š���ʼֵ�ߡ����ֽ�
			23,0x00,0x02,		//23�Ż������š���ʼֵ�ߡ����ֽ�
			24,0xB1,0x40,		//24�Ż������š���ʼֵ�ߡ����ֽ�
			25,0xA8,0x0F,		//25�Ż������š���ʼֵ�ߡ����ֽ�
			26,0x3E,0x07,		//26�Ż������š���ʼֵ�ߡ����ֽ�
			28,0x58,0x00,		//28�Ż������š���ʼֵ�ߡ����ֽ�
			0xff,0xff,0xff
			};

//***************дһ���ֽ�***************************
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
//***************д�����ֽ�****************************
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

//****************�Ĵ������ʼ��***********************
void reg_init(unsigned char reg_table[][3])
{
		unsigned char i;
		for(i=0;*(reg_table[i])!=0xFF;i++)
		 {
		 	write_spi_reg(reg_table[i]);
		 }	 	
}

//*******************��ȡһ���ֽ�********************** 
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

//*****************��ȡһ���Ĵ���***********************
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
 
//*************jf24c��ʼ���Ӻ���************************   
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

//**************��������************************
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

//******************����**********************************
void rx_data(unsigned char data_rx[N])
{
 	unsigned char i;

	enter_idle();
	write_spi_reg(REG82_RX);	 	//��FIFO��ָ��
	write_spi_reg(REG7_RX);		 	//��RX��ѡ��Ƶ��		
	while(!PKT_FLG);			 	//�ȴ����ձ�־

	SPI_SS=0;
	write_spi_byte(0xd0);		 	//дFIFO��ַ

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