/*
*  Copyright(c) 2012-2020     ΢Ƕ���� http://Tonvon.taobao.com
*
*  QQ: 30611966    ������twd3621576   Email: tangweidong2004@163.com 
*
* Ӳ��ƽ̨��½��MiniStm32������
*
* Ӳ�����ӣ�
*===========================================�ļ���Ϣ=======================================================
* �ļ�����:         
* ��    ��:
*
* ���������Keil MDK for ARM 4.12
* ��ǰ�汾: V5.0.0.0
* ��    ��: Tonvdon(a dong)
* �������: 2012-03-03
*
* ȡ���汾:
* ԭ����  :
* �������:
*********************************************************************************************************
*/
//#define XOR_LED_D1	 GPIOA ->ODR ^= GPIO_Pin_8;
#define XOR_LED_D4()   GPIOC ->ODR ^= GPIO_Pin_11;
#define XOR_LED_D6()   GPIOD ->ODR ^= GPIO_Pin_2;
#define XOR_LED_D5()   GPIOC ->ODR ^= GPIO_Pin_12;
#define XOR_LED_D3()   GPIOC ->ODR ^= GPIO_Pin_10;

  
void GpioConfigurationLed(void);
