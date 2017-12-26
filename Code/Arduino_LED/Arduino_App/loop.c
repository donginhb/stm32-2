/***************************************************************************//**
  * @file    loop.c
  * @author  吴国炎
  * @version V1.0.0
  * @date    2012年8月16号
  * @brief   loop程序
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
#include <stdio.h>
#include "loop.h"

/* 私有类型定义---------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 变量 ----------------------------------------------------------------------*/
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
extern int led ;

/***************************************************************************//**
  * @brief  Arduino 循环处理程序
  * @note   无
  * @param  无
  * @retval 无
*******************************************************************************/
void loop()
{
    while (1)
    {
        digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(300);               // wait for a second
        digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
        delay(300);
    };

}

/******************* (C) COPYRIGHT wuguoyana ***************文件结束***********/

