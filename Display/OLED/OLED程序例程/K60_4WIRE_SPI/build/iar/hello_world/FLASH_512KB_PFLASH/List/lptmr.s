///////////////////////////////////////////////////////////////////////////////
//                                                                            /
//                                                      26/Jun/2014  09:42:00 /
// IAR ANSI C/C++ Compiler V6.30.6.23336/W32 EVALUATION for ARM               /
// Copyright 1999-2012 IAR Systems AB.                                        /
//                                                                            /
//    Cpu mode     =  thumb                                                   /
//    Endian       =  little                                                  /
//    Source file  =  C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4W /
//                    IRE_SPI\src\drivers\lptmr\lptmr.c                       /
//    Command line =  C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4W /
//                    IRE_SPI\src\drivers\lptmr\lptmr.c -D IAR -D             /
//                    TWR_K60N512 -lCN C:\Users\me\Desktop\OLED�ͻ�����-14050 /
//                    9\��������\K60_4WIRE_SPI\build\iar\hello_world\FLASH_51 /
//                    2KB_PFLASH\List\ -lB C:\Users\me\Desktop\OLED�ͻ�����-1 /
//                    40509\��������\K60_4WIRE_SPI\build\iar\hello_world\FLAS /
//                    H_512KB_PFLASH\List\ -o C:\Users\me\Desktop\OLED�ͻ���� /
//                    �-140509\��������\K60_4WIRE_SPI\build\iar\hello_world\F /
//                    LASH_512KB_PFLASH\Obj\ --no_cse --no_unroll             /
//                    --no_inline --no_code_motion --no_tbaa --no_clustering  /
//                    --no_scheduling --debug --endian=little                 /
//                    --cpu=Cortex-M4 -e --fpu=None --dlib_config             /
//                    "C:\Program Files (x86)\IAR Systems\Embedded Workbench  /
//                    6.0 Evaluation\arm\INC\c\DLib_Config_Normal.h" -I       /
//                    C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4W /
//                    IRE_SPI\build\iar\hello_world\..\..\..\src\projects\hel /
//                    lo_world\ -I C:\Users\me\Desktop\OLED�ͻ�����-140509\�� /
//                    ������\K60_4WIRE_SPI\build\iar\hello_world\..\..\..\src /
//                    \common\ -I C:\Users\me\Desktop\OLED�ͻ�����-140509\��� /
//                    �����\K60_4WIRE_SPI\build\iar\hello_world\..\..\..\src\ /
//                    cpu\ -I C:\Users\me\Desktop\OLED�ͻ�����-140509\������� /
//                    �\K60_4WIRE_SPI\build\iar\hello_world\..\..\..\src\cpu\ /
//                    headers\ -I C:\Users\me\Desktop\OLED�ͻ�����-140509\��� /
//                    �����\K60_4WIRE_SPI\build\iar\hello_world\..\..\..\src\ /
//                    drivers\adc16\ -I C:\Users\me\Desktop\OLED�ͻ�����-1405 /
//                    09\��������\K60_4WIRE_SPI\build\iar\hello_world\..\..\. /
//                    .\src\drivers\enet\ -I C:\Users\me\Desktop\OLED�ͻ����� /
//                    -140509\��������\K60_4WIRE_SPI\build\iar\hello_world\.. /
//                    \..\..\src\drivers\pmc\ -I                              /
//                    C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4W /
//                    IRE_SPI\build\iar\hello_world\..\..\..\src\drivers\rtc\ /
//                     -I C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K6 /
//                    0_4WIRE_SPI\build\iar\hello_world\..\..\..\src\drivers\ /
//                    lptmr\ -I C:\Users\me\Desktop\OLED�ͻ�����-140509\����� /
//                    ���\K60_4WIRE_SPI\build\iar\hello_world\..\..\..\src\dr /
//                    ivers\uart\ -I C:\Users\me\Desktop\OLED�ͻ�����-140509\ /
//                    ��������\K60_4WIRE_SPI\build\iar\hello_world\..\..\..\s /
//                    rc\drivers\mcg\ -I C:\Users\me\Desktop\OLED�ͻ�����-140 /
//                    509\��������\K60_4WIRE_SPI\build\iar\hello_world\..\..\ /
//                    ..\src\drivers\wdog\ -I C:\Users\me\Desktop\OLED�ͻ���� /
//                    �-140509\��������\K60_4WIRE_SPI\build\iar\hello_world\. /
//                    .\..\..\src\platforms\ -I C:\Users\me\Desktop\OLED�ͻ�� /
//                    ���-140509\��������\K60_4WIRE_SPI\build\iar\hello_world /
//                    \..\..\..\src\drivers\ftm\ -I                           /
//                    C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4W /
//                    IRE_SPI\build\iar\hello_world\..\..\..\src\drivers\SPI\ /
//                     -I C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K6 /
//                    0_4WIRE_SPI\build\iar\hello_world\..\..\..\src\drivers\ /
//                    OLED\ -I C:\Users\me\Desktop\OLED�ͻ�����-140509\������ /
//                    ��\K60_4WIRE_SPI\build\iar\hello_world\..\ -Ol          /
//                    --use_c++_inline                                        /
//    List file    =  C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4W /
//                    IRE_SPI\build\iar\hello_world\FLASH_512KB_PFLASH\List\l /
//                    ptmr.s                                                  /
//                                                                            /
//                                                                            /
///////////////////////////////////////////////////////////////////////////////

        NAME lptmr

        #define SHT_PROGBITS 0x1

        PUBLIC time_delay_ms

// C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4WIRE_SPI\src\drivers\lptmr\lptmr.c
//    1 /*
//    2  * File:        lptmr.c
//    3  * Purpose:     Provide common low power timer functions
//    4  *
//    5  * Notes:       Right now only function provided is used
//    6  *              to generate a delay in ms. This driver
//    7  *              could be expanded to include more functions
//    8  *              in the future.
//    9  *              
//   10  */
//   11 
//   12 
//   13 #include "common.h"
//   14 #include "lptmr.h"
//   15 
//   16 /********************************************************************/
//   17 /*
//   18  * Initialize the low power time to provide a delay measured in ms.
//   19  *
//   20  *
//   21  * Parameters:
//   22  *  count_val   number of ms to delay
//   23  *
//   24  * Returns:
//   25  * None
//   26  */

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   27 void time_delay_ms(uint32 count_val)
//   28 {
//   29   /* Make sure the clock to the LPTMR is enabled */
//   30   SIM_SCGC5|=SIM_SCGC5_LPTIMER_MASK; 
time_delay_ms:
        LDR.N    R1,??time_delay_ms_0  ;; 0x40048038
        LDR      R1,[R1, #+0]
        ORRS     R1,R1,#0x1
        LDR.N    R2,??time_delay_ms_0  ;; 0x40048038
        STR      R1,[R2, #+0]
//   31   
//   32   /* Set the compare value to the number of ms to delay */
//   33   LPTMR0_CMR = count_val; 
        LDR.N    R1,??time_delay_ms_0+0x4  ;; 0x40040008
        STR      R0,[R1, #+0]
//   34   
//   35   /* Set up LPTMR to use 1kHz LPO with no prescaler as its clock source */
//   36   LPTMR0_PSR = LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK; 
        LDR.N    R0,??time_delay_ms_0+0x8  ;; 0x40040004
        MOVS     R1,#+5
        STR      R1,[R0, #+0]
//   37   
//   38   /* Start the timer */
//   39   LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; 
        LDR.N    R0,??time_delay_ms_0+0xC  ;; 0x40040000
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x1
        LDR.N    R1,??time_delay_ms_0+0xC  ;; 0x40040000
        STR      R0,[R1, #+0]
//   40 
//   41   /* Wait for counter to reach compare value */
//   42   while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK));
??time_delay_ms_1:
        LDR.N    R0,??time_delay_ms_0+0xC  ;; 0x40040000
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+24
        BPL.N    ??time_delay_ms_1
//   43   
//   44   /* Clear Timer Compare Flag */
//   45   LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;
        LDR.N    R0,??time_delay_ms_0+0xC  ;; 0x40040000
        LDR      R0,[R0, #+0]
        LSRS     R0,R0,#+1
        LSLS     R0,R0,#+1
        LDR.N    R1,??time_delay_ms_0+0xC  ;; 0x40040000
        STR      R0,[R1, #+0]
//   46   
//   47   return;
        BX       LR               ;; return
        DATA
??time_delay_ms_0:
        DC32     0x40048038
        DC32     0x40040008
        DC32     0x40040004
        DC32     0x40040000
//   48 }

        SECTION `.iar_vfe_header`:DATA:REORDER:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
// 
// 72 bytes in section .text
// 
// 72 bytes of CODE memory
//
//Errors: none
//Warnings: none
