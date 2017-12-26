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
#include "stm32f0xx.h"
#include "ucos_ii.h"

/* 私有类型定义---------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
#define LED3            GPIO_Pin_9
#define LED4            GPIO_Pin_8

#define LED_PORT        GPIOC
#define LED_GPIO_CLK    RCC_AHBPeriph_GPIOC

/* 私有变量 ------------------------------------------------------------------*/
/* 变量 ----------------------------------------------------------------------*/
static   OS_STK   App_Task_LED1_Stk[APP_TASK_LED1_STK_SIZE];
static   OS_STK   App_Task_LED2_Stk[APP_TASK_LED2_STK_SIZE];

/* 任务函数 ------------------------------------------------------------------*/
static  void  App_Task_LED1(void* p_arg);
static  void  App_Task_LED2(void* p_arg);
/* 私有函数 ------------------------------------------------------------------*/
void LED_Configuration(void);
void Delay(__IO uint32_t nCount);

/***************************************************************************//**
  * @brief  主函数，硬件初始化，实现LED1-LED4闪烁
  * @note   无
  * @param  无
  * @retval 无
*******************************************************************************/
int main(void)
{
    INT8U os_err;

    LED_Configuration ();
    OSInit();
    OS_CPU_SysTickInit();
    
    //创建LED1闪烁的任务
    os_err = OSTaskCreate( App_Task_LED1,
                          (void *) 0,
                          (OS_STK *) &App_Task_LED1_Stk[APP_TASK_LED1_STK_SIZE - 1],
                          (INT8U) APP_TASK_LED1_PRIO);

    //创建LED2闪烁的任务
    os_err = OSTaskCreate( App_Task_LED2,
                          (void*) 0,
                          (OS_STK*) &App_Task_LED2_Stk[APP_TASK_LED2_STK_SIZE - 1],
                          (INT8U ) APP_TASK_LED2_PRIO);
    
    os_err = os_err;//仅仅是清除这个变量未使用的编译警告
    
    //启动uSOS 操作系统
    OSStart ();
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

/*******************************************************************************
  * @函数名称	LED_On
  * @函数说明   点亮LED 
  * @输入参数   LEDx：LED的编号
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void LED_On(uint16_t LEDx)
{
	GPIO_SetBits (LED_PORT, LEDx);
}

/*******************************************************************************
  * @函数名称	LED_Off
  * @函数说明   关闭LEDx 
  * @输入参数   LEDx：LED的编号
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void LED_Off(uint16_t LEDx)
{
	GPIO_ResetBits (LED_PORT, LEDx);
}

/*******************************************************************************
  * @函数名称	App_Task_LED1
  * @函数说明   LED任务1
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
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
  * @函数名称	App_Task_LED2
  * @函数说明   LED任务2
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
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
  * @brief  插入一段延时时间
  * @note   无
  * @param  nCount：指定延时的时间长度
  * @retval 无
*******************************************************************************/
void Delay(__IO uint32_t nCount)
{
    int i,j;
    //利用循环来延时一定的时间
    for (i=0; i<nCount; i++)
        for (j=0; j<5000; j++)
            ;
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
