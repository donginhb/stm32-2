/***************************************************************************//**
  * @file    main.c
  * @author  �����
  * @version V1.0.0
  * @date    2012��5��25��
  * @brief   CooCox������
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
#include <CoOS.h>			 			/*!< CooCox RTOS header file.		  */

/* ˽�����Ͷ���---------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
#define TASK_STK_SIZE		128	 		/*!< Define stack size.				  */
#define LED3            GPIO_Pin_9
#define LED4            GPIO_Pin_8

#define LED_PORT        GPIOC
#define LED_GPIO_CLK    RCC_AHBPeriph_GPIOC

/* ˽�б��� ------------------------------------------------------------------*/
OS_STK   LEDA_Task_Stk[TASK_STK_SIZE];	 	  /*!< Stack of 'LEDA_Task' task. */
OS_STK   LEDB_Task_Stk[TASK_STK_SIZE];	 	  /*!< Stack of 'LEDB_Task' task. */

/* ˽�к��� ------------------------------------------------------------------*/
void LED_Configuration(void);
void LEDA_Task (void* pdata) ;
void LEDB_Task (void* pdata) ;

/***************************************************************************//**
  * @brief  ��������Ӳ����ʼ����ʵ��LED1-LED4��˸
  * @note   ��
  * @param  ��
  * @retval ��
*******************************************************************************/
int main(void)
{
    CoInitOS();							/*!< Initial CooCox RTOS 			  */

    CoCreateTask(LEDA_Task, (void *)0, 10,&LEDA_Task_Stk[TASK_STK_SIZE-1], TASK_STK_SIZE);
    CoCreateTask(LEDB_Task, (void *)0, 11,&LEDB_Task_Stk[TASK_STK_SIZE-1], TASK_STK_SIZE);
    
    CoStartOS();

    while (1)
    {
    }
}

/***************************************************************************//**
 * @brief   ��������A
 * @param   ��
 * @retval  ��
 * @par     ��ϸ������
 * @details ���� ����A����������200msΪ���ڵ���LED3��ʵ��LED3��˸��
*******************************************************************************/
void LEDA_Task (void* pdata) 
{
    //��ʼ��LED
    LED_Configuration();

    for (;;) 
    {
        GPIO_SetBits(LED_PORT,LED3);  //����LED1
        //��ʱ100 ms
        CoTickDelay (100);
        GPIO_ResetBits(LED_PORT,LED3);//Ϩ��LED1
        //��ʱ100 ms
        CoTickDelay (100);
    }
}

/***************************************************************************//**
 * @brief   ��������B
 * @param   ��
 * @retval  ��
 * @par     ��ϸ������
 * @details ���� ����B����������400msΪ���ڵ���LED4��ʵ��LED4��˸��
*******************************************************************************/
void LEDB_Task (void* pdata) 
{
    //��ʼ��LED
    LED_Configuration();

    for (;;) 
    {
        GPIO_SetBits(LED_PORT,LED4);  //����LED2
        //��ʱ200 ms
        CoTickDelay (200);
        GPIO_ResetBits(LED_PORT,LED4);//Ϩ��LED2
        //��ʱ200 ms
        CoTickDelay (200);
    }
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
