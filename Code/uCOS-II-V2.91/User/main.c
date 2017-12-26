/***************************************************************************//**
  * @file    main.c
  * @author  �����
  * @version V1.0.0
  * @date    2012��8��16��
  * @brief   ������
  ******************************************************************************
  @verbatim
  ������
  ���������
  ����������ַ��http://hi.baidu.com/wuguoyana/home
  @endverbatim
  * @attention
  *
  * ֣��������
  * ���ļ�ֻ�����ṩ�����ο����������ļ����������κ�������ף��ҸŲ�����
  *
  * <h2><center> &copy; COPYRIGHT 2011 wuguoyana </center></h2>
*******************************************************************************/

/* ������ͷ�ļ�---------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "ucos_ii.h"

/* ˽�����Ͷ���---------------------------------------------------------------*/
/* ˽�ж��� ------------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
#define LED3            GPIO_Pin_9
#define LED4            GPIO_Pin_8

#define LED_PORT        GPIOC
#define LED_GPIO_CLK    RCC_AHBPeriph_GPIOC

/* ˽�б��� ------------------------------------------------------------------*/
/* ���� ----------------------------------------------------------------------*/
static   OS_STK   App_Task_LED1_Stk[APP_TASK_LED1_STK_SIZE];
static   OS_STK   App_Task_LED2_Stk[APP_TASK_LED2_STK_SIZE];

/* ������ ------------------------------------------------------------------*/
static  void  App_Task_LED1(void* p_arg);
static  void  App_Task_LED2(void* p_arg);
/* ˽�к��� ------------------------------------------------------------------*/
void LED_Configuration(void);
void Delay(__IO uint32_t nCount);

/***************************************************************************//**
  * @brief  ��������Ӳ����ʼ����ʵ��LED1-LED4��˸
  * @note   ��
  * @param  ��
  * @retval ��
*******************************************************************************/
int main(void)
{
    INT8U os_err;

    LED_Configuration ();
    OSInit();
    OS_CPU_SysTickInit();
    
    //����LED1��˸������
    os_err = OSTaskCreate( App_Task_LED1,
                          (void *) 0,
                          (OS_STK *) &App_Task_LED1_Stk[APP_TASK_LED1_STK_SIZE - 1],
                          (INT8U) APP_TASK_LED1_PRIO);

    //����LED2��˸������
    os_err = OSTaskCreate( App_Task_LED2,
                          (void*) 0,
                          (OS_STK*) &App_Task_LED2_Stk[APP_TASK_LED2_STK_SIZE - 1],
                          (INT8U ) APP_TASK_LED2_PRIO);
    
    os_err = os_err;//����������������δʹ�õı��뾯��
    
    //����uSOS ����ϵͳ
    OSStart ();
}

/***************************************************************************//**
  * @brief  ����ʹ��LED
  * @note   LED��صĶ�����Ҫ���������ú궨�����޸�
  * @param  ��
  * @retval ��
*******************************************************************************/
void LED_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    //ʹ��LED����GPIO��ʱ��
    RCC_AHBPeriphClockCmd(LED_GPIO_CLK, ENABLE);

    //��ʼ��LED��GPIO
    GPIO_InitStructure.GPIO_Pin = LED3 | LED4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    
    GPIO_ResetBits(LED_PORT,LED3 | LED4);  //Ϩ��LED3-4
}

/*******************************************************************************
  * @��������	LED_On
  * @����˵��   ����LED 
  * @�������   LEDx��LED�ı��
  * @�������   ��
  * @���ز���   ��
*******************************************************************************/
void LED_On(uint16_t LEDx)
{
	GPIO_SetBits (LED_PORT, LEDx);
}

/*******************************************************************************
  * @��������	LED_Off
  * @����˵��   �ر�LEDx 
  * @�������   LEDx��LED�ı��
  * @�������   ��
  * @���ز���   ��
*******************************************************************************/
void LED_Off(uint16_t LEDx)
{
	GPIO_ResetBits (LED_PORT, LEDx);
}

/*******************************************************************************
  * @��������	App_Task_LED1
  * @����˵��   LED����1
  * @�������   ��
  * @�������   ��
  * @���ز���   ��
*******************************************************************************/
void App_Task_LED1(void* pdata)
{
    pdata = pdata;

    for (;;)
    {
        LED_On(LED3);
        OSTimeDlyHMSM(0, 0, 0, 500);
        LED_Off(LED3);
        OSTimeDlyHMSM(0, 0, 0, 500);
    }

}

/*******************************************************************************
  * @��������	App_Task_LED2
  * @����˵��   LED����2
  * @�������   ��
  * @�������   ��
  * @���ز���   ��
*******************************************************************************/
void App_Task_LED2(void* pdata)
{
    pdata = pdata;

    for (;;)
    {
        LED_On(LED4);
        OSTimeDly(100);
        LED_Off(LED4);
        OSTimeDly(100);
    }
}

/***************************************************************************//**
  * @brief  ����һ����ʱʱ��
  * @note   ��
  * @param  nCount��ָ����ʱ��ʱ�䳤��
  * @retval ��
*******************************************************************************/
void Delay(__IO uint32_t nCount)
{
    int i,j;
    //����ѭ������ʱһ����ʱ��
    for (i=0; i<nCount; i++)
        for (j=0; j<5000; j++)
            ;
}

#ifdef  USE_FULL_ASSERT
/***************************************************************************//**
  * @brief  �����ڼ�������������ʱ��Դ�ļ����ʹ�������
  * @param  file: ָ������ļ���Դ�ļ���
  * @param  line: �����Դ������������
  * @retval ��
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
    /* �û����������Լ��Ĵ������ڱ��������ļ�������������,
       ���磺printf("�������ֵ: �ļ��� %s �� %d��\r\n", file, line) */

    /* ��ѭ�� */
    while (1)
    {
    }
}
#endif

/******************* (C) COPYRIGHT wuguoyana ***************�ļ�����***********/
