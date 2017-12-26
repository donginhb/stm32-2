/***************************�����Ƶ���****************************
**  �������ƣ�IR01F ����ײ���������
**	CPU:STM32
**	����8MHZ
**	�����ʣ�
**	���ײ�Ʒ��Ϣ�� IR01F ����ѧϰ����ģ��
**                http://yuesheng001.taobao.com
**  ���ߣ�δ֪
**  ��ϵ��751956552@qq.com
**  �޸����ڣ�2012.12.28
**  ˵���� ���ļ�Ϊ�����ļ�����������³������������ʾ�����޸ġ�
          
**************************�����Ƶ���******************************/

//Ҫ�㣺
//1.IO����Ҫ��ȷ
//2.checksum����ʱ,ע��unit 8�Ķ���,��8λ ,checksum & 0x00ff  �����㣬ȡ��8λ��
//3.����ʱ�����
//4.Ӳ���Ӻ�
//5.��ѹ����:2.4-3.6V,200mA����

#define I2CERR_NO_ERROR	0

#ifndef UINT8
typedef unsigned char UINT8;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

/**************************************************************************
**********************���°�����Ϊ�û������޸ĵĲ���**********************
*******************����ÿ��������Ҫ��д���Ӧ������***********************
***************************** begin **************************************
**************************************************************************/

#include "stm32f10x.h"
/************��д����ʱ����������궨���Զ����޸�*********************/
#define  DELAY_TIME  60	//50-100uS
#define  DELAY_ST 20	//20mS

/************GPIOA  IO�ڵĶ���*********************/
#define SDA_PIN GPIO_Pin_0 
#define SCL_PIN GPIO_Pin_1 
#define BUSY_PIN GPIO_Pin_2 
GPIO_InitTypeDef GPIO_InitStructure;


/***********************************************************
* ��    �ƣ�Set_SDA_IO(void) 
* ��    �ܣ� ����SDA�˿�
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ������51��Ƭ���������ⲿ���ж���˿ڣ��ú���Ϊ�գ� 					 
**********************************************************/
void Set_SDA_IO(void)
{
    /* Set this port to IO port of SDA */
//	GPIO_ModeSetup(REMOTE_DIN_PIN, 0x00);	//���ãɣ�Ϊ�ӣģ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
  GPIO_InitStructure.GPIO_Pin = SDA_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,SDA_PIN); 
}
/***********************************************************
* ��    �ƣ�SetSDAInput(void) 
* ��    �ܣ� ����SDA�˿�Ϊ����
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ������51��Ƭ���򲻱ز������պ���������AVR����Ҫ�������� 					 
**********************************************************/
void SetSDAInput(void)
{
    /* It set SDA port as an input */	
	//GPIO_InitIO(0,REMOTE_DIN_PIN);			//���ãӣģ�Ϊ���룬�ر�����
	GPIO_InitStructure.GPIO_Pin = SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/***********************************************************
* ��    �ƣ� SetSDAOutput(void)
* ��    �ܣ� ����SDA�˿�Ϊ���
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ������51��Ƭ���򲻱ز������պ���������AVR����Ҫ������� 					 
**********************************************************/
void SetSDAOutput(void)
{
    /* It set SDA port as an output */	
				//���ãӣģ�Ϊ���
	GPIO_InitStructure.GPIO_Pin = SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init( GPIOA, &GPIO_InitStructure);
}

/***********************************************************
* ��    �ƣ� SetSDAHigh(void)
* ��    �ܣ� ����SDA�˿�Ϊ�ߵ�ƽ
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void SetSDAHigh(void)
{
    /* It output a High level to SDA here. */	
	 GPIO_SetBits(GPIOA,SDA_PIN);  //���ãӣģ�Ϊ���1
}
/***********************************************************
* ��    �ƣ�SetSDALow(void)
* ��    �ܣ�����SDA �˿�Ϊ�͵�ƽ 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void SetSDALow(void)
{
    /* It output a Low level to SDA here. */		
	GPIO_ResetBits(GPIOA,SDA_PIN); //���ãӣģ�Ϊ���0
}

/***********************************************************
* ��    �ƣ�GetACKStatus(void)
* ��    �ܣ� ��ȡSDA�˿�Ӧ��״̬
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ������ȡ SDA �˿ڵ�״̬  					 
**********************************************************/
UINT8 GetACKStatus(void)
{

	return GPIO_ReadInputDataBit(GPIOA,SDA_PIN);
}

/***********************************************************
* ��    �ƣ�GetDINStatus(void) 
* ��    �ܣ� ��ȡSDA�˿�״̬
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ������ȡSDA �˿ڵ�״̬  					 
**********************************************************/
UINT8 GetDINStatus(void)
{	
		return GPIO_ReadInputDataBit(GPIOA,SDA_PIN);//���ӣģ���״̬
}

/***********************************************************
* ��    �ƣ� Set_SCL_IO(void)
* ��    �ܣ� ����SCL�˿�
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� ��51��Ƭ���������ⲿ���ж���˿ڣ��ú���Ϊ�գ�					 
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
* ��    �ƣ�SetSCLOutput(void 
* ��    �ܣ� ����SCLΪ���״̬
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� ��51��Ƭ���򲻱ز������պ���������AVR����Ҫ��������					 
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
* ��    �ƣ�SetSCLInput(void) 
* ��    �ܣ�����SCL�˿�Ϊ����״̬ 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� ��51��Ƭ���򲻱ز������պ���������AVR����Ҫ��������					 
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
* ��    �ƣ�SetSCLHigh(void)
* ��    �ܣ� ����SCL�˿�Ϊ�ߵ�ƽ 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void SetSCLHigh(void)
{
    /* It output a High level to SCL here. */	

	GPIO_SetBits(GPIOA,SCL_PIN);
}
/***********************************************************
* ��    �ƣ�SetSCLLow(void) 
* ��    �ܣ� ����SCL �˿�Ϊ�͵�ƽ
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void SetSCLLow(void)
{
    /* It output a Low level to SCL here. */	
	GPIO_ResetBits(GPIOA,SCL_PIN);
}



/***********************************************************
* ��    �ƣ� Set_BUSY_IO(void)
* ��    �ܣ� ����BUSY �˿� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ������51��Ƭ���������ⲿ���ж���˿ڣ��ú���Ϊ�գ� 					 
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
* ��    �ƣ�SetBUSYInput(void) 
* ��    �ܣ�����BUSY�˿�Ϊ���� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ������51��Ƭ���򲻱ز������պ���������AVR����Ҫ�������� 					 
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
* ��    �ƣ�SetBUSYOutput(void) 
* ��    �ܣ�����BUSY�˿�Ϊ��� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ������51��Ƭ���򲻱ز������պ���������AVR����Ҫ������� 					 
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
* ��    �ƣ� SetBUSYHigh(void)
* ��    �ܣ� ����BUSY�˿�Ϊ�ߵ�ƽ
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void SetBUSYHigh(void)
{
    /* It output a High level to BUSY here. */
	GPIO_SetBits(GPIOA,BUSY_PIN);
	
}
/***********************************************************
* ��    �ƣ� SetBUSYLow(void)
* ��    �ܣ� ����BUSY �˿�Ϊ�͵�ƽ
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ����  					 
**********************************************************/
void SetBUSYLow(void)
{
    /* It output a Low level to BUSY here. */	
	GPIO_ResetBits(GPIOA,BUSY_PIN);
}
/***********************************************************
* ��    �ƣ�GetBUSYStatus(void) 
* ��    �ܣ� ��ȡæ״̬ 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� ��ȡæ BUSY �˿ڵ�״̬ 					 
**********************************************************/
UINT8 GetBUSYStatus(void)
{
	//return GPIO_ReadIO(REMOTE_BUSY_PIN);
	return GPIO_ReadInputDataBit(GPIOA,BUSY_PIN);
}

/***********************************************************
* ��    �ƣ�void DelayTime( UINT16 lTime ) 
* ��    �ܣ�΢����ʱ����
* ��ڲ����� lTime=1����ʾ1us  
* ���ڲ�������
* ˵    �������ݲ�ͬ�ĵ�Ƭ��ϵͳ���е��� 					 
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
* ��    �ƣ�RemoteDelayms(UINT16 dat) 
* ��    �ܣ�������ʱ����
* ��ڲ����� data=1����ʾ1����  
* ���ڲ�������
* ˵    �������ݲ�ͬ�ĵ�Ƭ��ϵͳ���е��� 					 
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
**********************���ϰ�����Ϊ�û������޸ĵĲ���**********************
*******************����ÿ��������Ҫ��д���Ӧ������***********************
***************************** end **************************************
**************************************************************************/






/***********************************************************
* ��    �ƣ�IR01F_Init_Cfg(void) 
* ��    �ܣ� IR��ʼ������
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
* ��    �ƣ�UINT8 GetACKSign(void) 
* ��    �ܣ���ȡӦ���ź� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
* ��    �ƣ�void SendACKSign(void) 
* ��    �ܣ�����Ӧ�� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void SendACKSign(void)
{
	SetSDAOutput();
	DelayTime(DELAY_TIME);
	SetSDALow();					///wjs;��ӵ�SDA_Low,û����֤��
	DelayTime(DELAY_TIME);

	SetSCLHigh();					//��9�ε�CLK�ĸ�
	DelayTime(DELAY_TIME);			//1mS
	
	SetSCLLow(); 
}
/***********************************************************
* ��    �ƣ�UINT16 I2COpen(void) 
* ��    �ܣ�����I2C 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
* ��    �ƣ�UINT16 I2CClose(void)  
* ��    �ܣ��ر�I2C 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
* ��    �ƣ�UINT16 I2CStart(void) 
* ��    �ܣ���ʼI2CͨѶ 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
* ��    �ƣ�UINT16 I2CStop(void) 
* ��    �ܣ� ֹͣI2CͨѶ
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
* ��    �ƣ�UINT16 I2CWriteData( char bData ) 
* ��    �ܣ� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
* ��    �ƣ�Send_IR_Data(char* dat, UINT8 count) 
* ��    �ܣ�����IR���� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
	
	
	for(i = 0; i < count; i++)	//count=7,��ֵ
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
* ��    �ƣ�void IR_Learn_Start(void) 
* ��    �ܣ�����ѧϰ��ʼ 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
* ��    �ƣ�UINT16 I2CReadData(UINT8* pbData) 
* ��    �ܣ� ��ȡI2C����
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
	DelayTime(DELAY_TIME);		//wjs;1G���ϵ�ϵͳҪ��,test
	

	return I2CERR_NO_ERROR;
}

/***********************************************************
* ��    �ƣ�uint8_t readI2C(char* readtempbuf) 
* ��    �ܣ� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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



