/***************************************************************************//**
  * @file    stm32f0xx_it.c
  * @author  吴国炎
  * @version V1.0.0
  * @date    2012年5月25号
  * @brief   中断服务函数代码
*******************************************************************************/
 
/* 包含头文件 *****************************************************************/
#include "stm32f0xx_it.h"


/* 私有类型定义---------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
/* 私有函数声明 --------------------------------------------------------------*/
/* 私有函数 ------------------------------------------------------------------*/

/******************************************************************************/
/*                      STM32F0xx 外设 中断 服务函数                          */
/******************************************************************************/
// void PPP_Handler(void)
// {

// }

/******************************************************************************/
/*                  Cortex-M0 处理器的相关中断服务函数                        */
/******************************************************************************/

/***************************************************************************//**                                                                          
  * @brief  不可屏蔽中断发生的中断处理函数                        
  * @note   该中断是m3内核中不可屏蔽的中断 
  * @param  无
  * @retval 无
*******************************************************************************/
void NMI_Handler(void)
{
}

/***************************************************************************//**                                                                          
  * @brief  硬件错误发生的中断处理函数                       
  * @note   程序运行中硬件发生错误时就会进入该中断
  * @param  无
  * @retval 无
*******************************************************************************/
void HardFault_Handler(void)
{
    //当硬件错误发生时进入死循环 
    while (1)
    {
    }
}

// /***************************************************************************//**                                                                          
//   * @brief  SVC调用中断发生的中断处理函数                     
//   * @note   无
//   * @param  无
//   * @retval 无
// *******************************************************************************/
// void SVC_Handler(void)
// {
// }

// /***************************************************************************//**                                                                          
//   * @brief  Pend SV中断发生的中断处理函数                    
//   * @note   无
//   * @param  无
//   * @retval 无
// *******************************************************************************/
// void PendSV_Handler(void)
// {
// }
//
// /***************************************************************************//**                                                                          
//   * @brief  SysTick中断发生的中断处理函数               
//   * @note   无
//   * @param  无
//   * @retval 无
// *******************************************************************************/
// void SysTick_Handler(void)
// {
// }

/******************* (C) COPYRIGHT wuguoyana ***************文件结束***********/
