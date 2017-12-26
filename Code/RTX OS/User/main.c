/***************************************************************************//**
  * @file    main.c
  * @author  吴国炎
  * @version V1.0.0
  * @date    2012年8月16号
  * @brief   主程序
  ******************************************************************************
  @verbatim
  主程序
  吴国炎制作
  技术博客网址：http://hi.baidu.com/wuguoyana/home
  @endverbatim
  * @attention
  *
  * 郑重声明：
  * 此文件只用于提供开发参考，如果因此文件而产生的任何问题纠纷，我概不负责。
  *
  * <h2><center> &copy; COPYRIGHT 2011 wuguoyana </center></h2>
*******************************************************************************/

/* 包含的头文件---------------------------------------------------------------*/
#include <RTL.h>
#include "stm32f0xx.h"

/* 私有类型定义---------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
#define LED3            GPIO_Pin_9
#define LED4            GPIO_Pin_8

#define LED_PORT        GPIOC
#define LED_GPIO_CLK    RCC_AHBPeriph_GPIOC

/* 私有变量 ------------------------------------------------------------------*/
OS_TID t_led1;                         /* assigned task id of task: ledOn   */
OS_TID t_led2;                        /* assigned task id of task: ledOff  */
/* 私有函数 ------------------------------------------------------------------*/
void LED_Configuration(void);

/* 操作系统任务 --------------------------------------------------------------*/
__task void LED1 (void);
__task void LED2 (void);
__task void init (void);

/***************************************************************************//**
  * @brief  主函数，硬件初始化，实现LED1-LED4闪烁
  * @note   无
  * @param  无
  * @retval 无
*******************************************************************************/
int main(void)
{
    os_sys_init (init);   //初始化RTX操作系统和启动操作系统
    while (1)
    {
    }
}


/***************************************************************************//**
  * @brief  LED1_Task，实现LED3 1s闪烁
  * @note   无
  * @param  无
  * @retval 无
*******************************************************************************/
__task void LED1_Task (void) 
{
    for (;;) 
    {
        GPIO_SetBits(LED_PORT,LED3);  //点亮LED1                                  
        os_dly_wait (500);            //延时0.5s 
        GPIO_ResetBits(LED_PORT,LED3);//熄灭LED1
        os_dly_wait (500);            
    }
}

/***************************************************************************//**
  * @brief  LED2_Task，实现LED4 0.4s闪烁
  * @note   无
  * @param  无
  * @retval 无
*******************************************************************************/
__task void LED2_Task (void) 
{
    for (;;) 
    {
        GPIO_SetBits(LED_PORT,LED4);  //点亮LED1                                  
        os_dly_wait (200);            //延时0.2s
        GPIO_ResetBits(LED_PORT,LED4);//熄灭LED1
        os_dly_wait (200);  
    }
}

/***************************************************************************//**
  * @brief  init，任务初始化函数
  * @note   无
  * @param  无
  * @retval 无
*******************************************************************************/
__task void init (void) 
{

    LED_Configuration();                      /* Initialize LEDs                  */

    t_led1  = os_tsk_create (LED1_Task, 0);   /* start task 'ledOn'               */
    t_led2 = os_tsk_create  (LED2_Task, 0);   /* start task 'ledOff'              */
    os_tsk_delete_self ();
}

/***************************************************************************//**
  * @brief  配置使用LED
  * @note   LED相关的定义需要根据需求用宏定义来修改
  * @param  无
  * @retval 无
*******************************************************************************/
void LED_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //使能LED所在GPIO的时钟
    RCC_AHBPeriphClockCmd(LED_GPIO_CLK, ENABLE);

    //初始化LED的GPIO
    GPIO_InitStructure.GPIO_Pin = LED3 | LED4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);

    GPIO_ResetBits(LED_PORT,LED3 | LED4);  //熄灭LED3-4
}


#ifdef  USE_FULL_ASSERT
/***************************************************************************//**
  * @brief  报告在检查参数发生错误时的源文件名和错误行数
  * @param  file: 指向错误文件的源文件名
  * @param  line: 错误的源代码所在行数
  * @retval 无
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
    /* 用户可以增加自己的代码用于报告错误的文件名和所在行数,
       例如：printf("错误参数值: 文件名 %s 在 %d行\r\n", file, line) */

    /* 死循环 */
    while (1)
    {
    }
}
#endif

/******************* (C) COPYRIGHT wuguoyana ***************文件结束***********/
