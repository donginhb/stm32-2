/***************************飞音云电子****************************
**  工程名称：IR01F 红外底层驱动程序
**	CPU:STM32
**	晶振：8MHZ
**	波特率：
**	配套产品信息： IR01F 红外学习核心模块
**                http://yuesheng001.taobao.com
**  作者：未知
**  联系：751956552@qq.com
**  修改日期：2012.12.28
**  说明： 本文件为驱动文件，请根据以下程序函数的相关提示进行修改。
          
**************************飞音云电子******************************/

//要点：
//1.IO设置要正确
//2.checksum不过时,注意unit 8的定义,低8位 ,checksum & 0x00ff  做运算，取低8位，
//3.两个时序调好
//4.硬件接好
//5.电压供电:2.4-3.6V,200mA以上

#define I2CERR_NO_ERROR	0

#ifndef UINT8
typedef unsigned char UINT8;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

/**************************************************************************
**********************以下包含的为用户进行修改的参数**********************
*******************根据每个函数的要求写入对应的配置***********************
***************************** begin **************************************
**************************************************************************/

#include "stm32f10x.h"
/************编写好延时函数后，这里宏定义自定义修改*********************/
#define  DELAY_TIME  60	//50-100uS
#define  DELAY_ST 20	//20mS

/************GPIOA  IO口的定义*********************/
#define SDA_PIN GPIO_Pin_0 
#define SCL_PIN GPIO_Pin_1 
#define BUSY_PIN GPIO_Pin_2 
GPIO_InitTypeDef GPIO_InitStructure;


/***********************************************************
* 名    称：Set_SDA_IO(void) 
* 功    能： 定义SDA端口
* 入口参数： 无 
* 出口参数：无
* 说    明：如51单片机可以在外部进行定义端口，该函数为空！ 					 
**********************************************************/
void Set_SDA_IO(void)
{
    /* Set this port to IO port of SDA */
//	GPIO_ModeSetup(REMOTE_DIN_PIN, 0x00);	//设置ＩＯ为ＳＤＡ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
  GPIO_InitStructure.GPIO_Pin = SDA_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,SDA_PIN); 
}
/***********************************************************
* 名    称：SetSDAInput(void) 
* 功    能： 设置SDA端口为输入
* 入口参数： 无 
* 出口参数：无
* 说    明：如51单片机则不必操作（空函数），如AVR则需要配置输入 					 
**********************************************************/
void SetSDAInput(void)
{
    /* It set SDA port as an input */	
	//GPIO_InitIO(0,REMOTE_DIN_PIN);			//设置ＳＤＡ为输入，关闭下拉
	GPIO_InitStructure.GPIO_Pin = SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上啦输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/***********************************************************
* 名    称： SetSDAOutput(void)
* 功    能： 设置SDA端口为输出
* 入口参数： 无 
* 出口参数：无
* 说    明：如51单片机则不必操作（空函数），如AVR则需要配置输出 					 
**********************************************************/
void SetSDAOutput(void)
{
    /* It set SDA port as an output */	
				//设置ＳＤＡ为输出
	GPIO_InitStructure.GPIO_Pin = SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init( GPIOA, &GPIO_InitStructure);
}

/***********************************************************
* 名    称： SetSDAHigh(void)
* 功    能： 设置SDA端口为高电平
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void SetSDAHigh(void)
{
    /* It output a High level to SDA here. */	
	 GPIO_SetBits(GPIOA,SDA_PIN);  //设置ＳＤＡ为输出1
}
/***********************************************************
* 名    称：SetSDALow(void)
* 功    能：设置SDA 端口为低电平 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void SetSDALow(void)
{
    /* It output a Low level to SDA here. */		
	GPIO_ResetBits(GPIOA,SDA_PIN); //设置ＳＤＡ为输出0
}

/***********************************************************
* 名    称：GetACKStatus(void)
* 功    能： 获取SDA端口应答状态
* 入口参数： 无 
* 出口参数：无
* 说    明：读取 SDA 端口的状态  					 
**********************************************************/
UINT8 GetACKStatus(void)
{

	return GPIO_ReadInputDataBit(GPIOA,SDA_PIN);
}

/***********************************************************
* 名    称：GetDINStatus(void) 
* 功    能： 获取SDA端口状态
* 入口参数： 无 
* 出口参数：无
* 说    明：读取SDA 端口的状态  					 
**********************************************************/
UINT8 GetDINStatus(void)
{	
		return GPIO_ReadInputDataBit(GPIOA,SDA_PIN);//读ＳＤＡ的状态
}

/***********************************************************
* 名    称： Set_SCL_IO(void)
* 功    能： 定义SCL端口
* 入口参数： 无 
* 出口参数：无
* 说    明： 如51单片机可以在外部进行定义端口，该函数为空！					 
**********************************************************/
void Set_SCL_IO(void)
{
	/* Set this port to IO port of SCL */
//	GPIO_ModeSetup(REMOTE_CLK_PIN, 0x00);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
  GPIO_InitStructure.GPIO_Pin = SCL_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,SCL_PIN);	
}
/***********************************************************
* 名    称：SetSCLOutput(void 
* 功    能： 设置SCL为输出状态
* 入口参数： 无 
* 出口参数：无
* 说    明： 如51单片机则不必操作（空函数），如AVR则需要配置输入					 
**********************************************************/
void SetSCLOutput(void)
{
    /* It set SCL port as an output */
	//GPIO_InitIO(1,REMOTE_CLK_PIN); 
	GPIO_InitStructure.GPIO_Pin = SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
/***********************************************************
* 名    称：SetSCLInput(void) 
* 功    能：设置SCL端口为输入状态 
* 入口参数： 无 
* 出口参数：无
* 说    明： 如51单片机则不必操作（空函数），如AVR则需要配置输入					 
**********************************************************/
void SetSCLInput(void)
{
    /* It set SCL port as an Input */
	//GPIO_InitIO(0,REMOTE_CLK_PIN); 
		GPIO_InitStructure.GPIO_Pin = SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}

/***********************************************************
* 名    称：SetSCLHigh(void)
* 功    能： 设置SCL端口为高电平 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void SetSCLHigh(void)
{
    /* It output a High level to SCL here. */	

	GPIO_SetBits(GPIOA,SCL_PIN);
}
/***********************************************************
* 名    称：SetSCLLow(void) 
* 功    能： 设置SCL 端口为低电平
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void SetSCLLow(void)
{
    /* It output a Low level to SCL here. */	
	GPIO_ResetBits(GPIOA,SCL_PIN);
}



/***********************************************************
* 名    称： Set_BUSY_IO(void)
* 功    能： 定义BUSY 端口 
* 入口参数： 无 
* 出口参数：无
* 说    明：如51单片机可以在外部进行定义端口，该函数为空！ 					 
**********************************************************/
void Set_BUSY_IO(void)
{
	/* Set this port to IO port of BUSY */
//	GPIO_ModeSetup(REMOTE_BUSY_PIN, 0x00);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
  GPIO_InitStructure.GPIO_Pin = BUSY_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,BUSY_PIN);
}

/***********************************************************
* 名    称：SetBUSYInput(void) 
* 功    能：设置BUSY端口为输入 
* 入口参数： 无 
* 出口参数：无
* 说    明：如51单片机则不必操作（空函数），如AVR则需要配置输入 					 
**********************************************************/
void SetBUSYInput(void)
{
	 /* It set BUSY port as an input */	
	//GPIO_InitIO(0,REMOTE_BUSY_PIN);
		GPIO_InitStructure.GPIO_Pin = BUSY_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/***********************************************************
* 名    称：SetBUSYOutput(void) 
* 功    能：设置BUSY端口为输出 
* 入口参数： 无 
* 出口参数：无
* 说    明：如51单片机则不必操作（空函数），如AVR则需要配置输出 					 
**********************************************************/
void SetBUSYOutput(void)
{
	 /* It set BUSY port as an output */	
//	GPIO_InitIO(1,REMOTE_BUSY_PIN);
	GPIO_InitStructure.GPIO_Pin = BUSY_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/***********************************************************
* 名    称： SetBUSYHigh(void)
* 功    能： 设置BUSY端口为高电平
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void SetBUSYHigh(void)
{
    /* It output a High level to BUSY here. */
	GPIO_SetBits(GPIOA,BUSY_PIN);
	
}
/***********************************************************
* 名    称： SetBUSYLow(void)
* 功    能： 设置BUSY 端口为低电平
* 入口参数： 无 
* 出口参数：无
* 说    明：  					 
**********************************************************/
void SetBUSYLow(void)
{
    /* It output a Low level to BUSY here. */	
	GPIO_ResetBits(GPIOA,BUSY_PIN);
}
/***********************************************************
* 名    称：GetBUSYStatus(void) 
* 功    能： 获取忙状态 
* 入口参数： 无 
* 出口参数：无
* 说    明： 读取忙 BUSY 端口的状态 					 
**********************************************************/
UINT8 GetBUSYStatus(void)
{
	//return GPIO_ReadIO(REMOTE_BUSY_PIN);
	return GPIO_ReadInputDataBit(GPIOA,BUSY_PIN);
}

/***********************************************************
* 名    称：void DelayTime( UINT16 lTime ) 
* 功    能：微秒延时函数
* 入口参数： lTime=1；表示1us  
* 出口参数：无
* 说    明：根据不同的单片机系统进行调整 					 
**********************************************************/

void DelayTime( UINT16 lTime )
{
	uint16_t i=0;
	while(lTime--)
	{
		i=10;
		while(i--);
	}

}
/***********************************************************
* 名    称：RemoteDelayms(UINT16 dat) 
* 功    能：毫秒延时函数
* 入口参数： data=1；表示1毫秒  
* 出口参数：无
* 说    明：根据不同的单片机系统进行调整 					 
**********************************************************/
void RemoteDelayms(UINT16 dat)
{
   uint16_t i=0;  
	 while(dat--)
	 {
	 	i=12000;
		while(i--);
	 }

}

/**************************************************************************
**********************以上包含的为用户进行修改的参数**********************
*******************根据每个函数的要求写入对应的配置***********************
***************************** end **************************************
**************************************************************************/






/***********************************************************
* 名    称：IR01F_Init_Cfg(void) 
* 功    能： IR初始化函数
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void IR01F_Init_Cfg(void)		
{

	Set_SDA_IO();
	SetSDAHigh();
	SetSDAOutput();

	Set_SCL_IO();
	SetSCLHigh();
	SetSCLOutput();

	Set_BUSY_IO();
	SetBUSYInput();				

}

/***********************************************************
* 名    称：UINT8 GetACKSign(void) 
* 功    能：获取应答信号 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
UINT8 GetACKSign(void) 
{
	UINT8 ACKSign;

	SetSDAInput();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	SetSCLHigh();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	ACKSign = GetDINStatus();		

	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	SetSCLLow();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	return ACKSign;

}

/***********************************************************
* 名    称：void SendACKSign(void) 
* 功    能：发送应答 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void SendACKSign(void)
{
	SetSDAOutput();
	DelayTime(DELAY_TIME);
	SetSDALow();					///wjs;后加低SDA_Low,没有验证过
	DelayTime(DELAY_TIME);

	SetSCLHigh();					//第9次的CLK的高
	DelayTime(DELAY_TIME);			//1mS
	
	SetSCLLow(); 
}
/***********************************************************
* 名    称：UINT16 I2COpen(void) 
* 功    能：启动I2C 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
UINT16 I2COpen(void)
{	
	Set_SDA_IO(); 
	Set_SCL_IO(); 

	SetSDAOutput(); 
	SetSCLOutput(); 

	SetSCLHigh();  
	SetSDAHigh();

	return I2CERR_NO_ERROR; 
}
/***********************************************************
* 名    称：UINT16 I2CClose(void)  
* 功    能：关闭I2C 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
UINT16 I2CClose(void)   
{
	SetSDAOutput(); 
	SetSCLOutput(); 

	SetSCLHigh();
	SetSDAHigh();

	return I2CERR_NO_ERROR; 
}
/***********************************************************
* 名    称：UINT16 I2CStart(void) 
* 功    能：开始I2C通讯 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
UINT16 I2CStart(void) 
{
	SetSDAOutput();
	SetSCLOutput();
	SetSCLHigh();
	SetSDAHigh();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	SetSDALow();
	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	SetSCLLow();  
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	return 1;

}

/***********************************************************
* 名    称：UINT16 I2CStop(void) 
* 功    能： 停止I2C通讯
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
UINT16 I2CStop(void)
{
	SetSDAOutput();
	SetSCLOutput();
	SetSCLLow();
	SetSDALow();
	DelayTime(DELAY_TIME);

	SetSCLHigh();
	DelayTime(DELAY_TIME);

	SetSDAHigh();
	DelayTime(DELAY_TIME);  

	return I2CERR_NO_ERROR; 
}

/***********************************************************
* 名    称：UINT16 I2CWriteData( char bData ) 
* 功    能： 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
UINT16 I2CWriteData( char bData )
{
	UINT8 Data_Bit,ACKSign;
	int i;

	SetSDAOutput();
	SetSCLLow();
	DelayTime(DELAY_TIME);
    
	for(i=7;i>=0;i--)
	{
		DelayTime(DELAY_TIME);
		
		Data_Bit=(bData>>i)& 0x01;

		if(Data_Bit)
		SetSDAHigh();
		else
		SetSDALow();

		DelayTime(DELAY_TIME);
		SetSCLHigh();
		DelayTime(DELAY_TIME);
		SetSCLLow();		
	}
	
	ACKSign=GetACKSign();

	return ACKSign;

}

/***********************************************************
* 名    称：Send_IR_Data(char* dat, UINT8 count) 
* 功    能：发送IR数据 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void Send_IR_Data(char* dat, UINT8 count)
{
	UINT8 i;
	char iBuffer;

	I2COpen();
	DelayTime(DELAY_TIME);

	SetSCLLow();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	SetSCLHigh();
	
	RemoteDelayms(DELAY_ST); //20ms	//14

	I2CStart();
	DelayTime(DELAY_TIME);
	
	
	for(i = 0; i < count; i++)	//count=7,初值
	{
		iBuffer = dat[i];
		I2CWriteData(iBuffer);
		DelayTime(DELAY_TIME);
	}


	DelayTime(DELAY_TIME);

	I2CStop();
	DelayTime(DELAY_TIME);

	I2CClose();
	DelayTime(DELAY_TIME);

}

/***********************************************************
* 名    称：void IR_Learn_Start(void) 
* 功    能：红外学习开始 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void IR_Learn_Start(void)
{
		
	I2COpen();
	DelayTime(DELAY_TIME);

	SetSCLLow();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	SetSCLHigh();
	
	RemoteDelayms(DELAY_ST); //20ms	//14

	I2CStart();
	DelayTime(DELAY_TIME);
	
	I2CWriteData(0x30);
	DelayTime(DELAY_TIME);

	I2CWriteData(0x10);
	DelayTime(DELAY_TIME);
	
	I2CWriteData(0x40);
	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);	

	I2CStop();
	DelayTime(DELAY_TIME);

	I2CClose();
	DelayTime(DELAY_TIME);

}

/***********************************************************
* 名    称：UINT16 I2CReadData(UINT8* pbData) 
* 功    能： 读取I2C数据
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
UINT16 I2CReadData(UINT8* pbData)
{
	UINT8 readdata = 0;
	UINT8 i=8;

	SetSDAInput(); 
	while (i--)
	{
		readdata<<=1;

		SetSCLHigh(); 
		DelayTime(DELAY_TIME);

		readdata |= GetDINStatus();

		SetSCLLow();
		DelayTime(DELAY_TIME);
		DelayTime(DELAY_TIME);	
	}
	SetSCLLow(); 
	DelayTime(DELAY_TIME);

	*pbData = readdata;

	SendACKSign();
	
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);		//wjs;1G以上的系统要加,test
	

	return I2CERR_NO_ERROR;
}

/***********************************************************
* 名    称：uint8_t readI2C(char* readtempbuf) 
* 功    能： 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
uint8_t readI2C(char* readtempbuf)
{
	UINT8 bValue;
	UINT8 i=0;
	UINT8 checksum;

	I2COpen();
	DelayTime(DELAY_TIME);

	SetSCLLow();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	SetSCLHigh();
	RemoteDelayms(DELAY_ST); //20ms	

	I2CStart();
	DelayTime(DELAY_TIME);

	//----------------------------------------
	//write
	I2CWriteData(0x30);
	DelayTime(DELAY_TIME);
	//address point
	I2CWriteData(0x52);
	DelayTime(DELAY_TIME);

	//---------------------------------------
	//read
	I2CStart();
	DelayTime(DELAY_TIME);

	I2CWriteData(0x31);
	DelayTime(DELAY_TIME);

	I2CReadData(&bValue);		
	DelayTime(DELAY_TIME);			
	
	if(bValue != 0x00)
	{
		I2CStop();
		DelayTime(DELAY_TIME);
		I2CClose();
		DelayTime(DELAY_TIME);
		return 0;
	}

	i = 0;
	readtempbuf[i] = bValue;

	checksum = 0xB3;

	for(i = 1; i < 110; i++)			
	{
		I2CReadData(&bValue);
		DelayTime(DELAY_TIME);
		readtempbuf[i] = bValue;
	
		checksum += bValue;
	}
	
	I2CReadData(&bValue);	
	DelayTime(DELAY_TIME);

	I2CStop();
	DelayTime(DELAY_TIME);
	I2CClose();
	DelayTime(DELAY_TIME);

	if(bValue != checksum)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}



