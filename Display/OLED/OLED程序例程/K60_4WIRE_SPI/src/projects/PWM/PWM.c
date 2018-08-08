/*********************************************************************************
 * �ļ���       ��main.c
 * ����         ��PWMʵ��
 *
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
**********************************************************************************/

#include "common.h"


#define GPIO_PIN_MASK            0x1Fu
#define GPIO_PIN(x)              (((1)<<(x & GPIO_PIN_MASK)))



#define LED3_TOGGLE (GPIOB_PTOR = (1<<20))
#define LED2_TOGGLE (GPIOB_PTOR = (1<<21))
#define LED1_TOGGLE (GPIOB_PTOR = (1<<22))
#define LED0_TOGGLE (GPIOB_PTOR = (1<<23))


void init_gpio();

void delay();

#if 1    //����ѡ�� 0 �� 1 ���л�����������ͬ��main����

/*************************************************************************
*
*
*  ʵ������������� FTM1_CH0 ���� PWM ���岨 ���� PTA0 �ܽš�
*            �� PTB0 ����ʾ����
*
*  ʵ��Ч�������Բ��Ƶ��Ϊ 35kHz
*
*  ʵ��Ŀ�ģ����� PWM Ƶ���Ƿ���ȷ
*
*  ��    ע��FTM.h ���и���FTMͨ������Ӧ�ܽŵı�񣬷���鿴
*            ռ�ձȴ��ݽ���Ĳ�����Ҫ���� FTM_PRECISON �Ķ�����ѡ��
*************************************************************************/
void  main()
{
    
    init_gpio();//��ʼ��IO��
    
    LED3_TOGGLE;
    
    FTM_PWM_init(FTM1, CH0,1, 50); //��ʼ��FTM1_CH0���Ƶ��Ϊ35kHZ,ռ�ձ�Ϊ50%��PWM ��FTM1_CH0��ӦPTB0��
    while(1)
    {
    }
}

#else


/*************************************************************************
*                               PWMʵ��LED����
*
*  ʵ��˵������LED������ռ�ձȵı仯��
*
*  ʵ������������� FTM1_CH0 ���� PWM ���岨
*            �� FTM.h ����Բ鵽 FTM1_CH0 ��Ӧ�ܽ�Ϊ PTA8
*            �� PTB0 ���� LED0���� PTB0 �� PTB20 �̽�
*
*  ʵ��Ч�������Կ��� LED0 �ɰ���������ͻȻ���������ȥ����
*
*  ʵ��Ŀ�ģ����� PWM Ƶ���Ƿ���ȷ

*  ��    ע�������Ƿ�ΪPWM��������ţ���鿴�����ֲṦ�ܵĶ��ձ�
*           
*************************************************************************/
void  main()
{
    u32 i;
    init_gpio();//��ʼ��IO��
    FTM_PWM_init(FTM1, CH0, 35000, 100);     //FTM1_CH0��ʼ��PWM ��PA8
    while(1)
    {
        for(i = 10; i > 1; i--)
        {
            FTM_PWM_Duty(FTM1, CH0, i * 10);  //�ı�ռ�ձȣ��𽥱�С ,LED �𽥱��� ���͵�ƽ������
            time_delay_ms(100);               //��ʱ100ms
        }
    }
}
/********************************************************************/


#endif



void init_gpio()
{
  //Set PTA19 and PTE26 (connected to SW1 and SW2) for GPIO functionality, falling IRQ,
  //   and to use internal pull-ups. (pin defaults to input state)
  //PORTA_PCR19=PORT_PCR_MUX(1)|PORT_PCR_IRQC(0xA)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
  //PORTE_PCR26=PORT_PCR_MUX(1)|PORT_PCR_IRQC(0xA)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;

  //Set PTB10, PTB21, PTB21, and PTB23 (connected to LED's) for GPIO functionality//�޸��ʺϱ���·��
  
  
  PORTB_PCR20=(0|PORT_PCR_MUX(1));
  PORTB_PCR21=(0|PORT_PCR_MUX(1));
  PORTB_PCR22=(0|PORT_PCR_MUX(1));
  PORTB_PCR23=(0|PORT_PCR_MUX(1));

  //Change PTB20, PTB21, PTB22, PTB23 to outputs
  GPIOB_PDDR=GPIO_PDDR_PDD(GPIO_PIN(20) | GPIO_PIN(21) | GPIO_PIN(22) | GPIO_PIN(23) );	
}

/*
 * Function to provide a short delay
 */
void delay()
{
  unsigned int i, n;
  for(i=0;i<30000;i++)
  {
    for(n=0;n<100;n++)
    {
      asm("nop");
    }
  }
}