///////////////////////////////////////////////////////////////////////////////
//                                                                            /
//                                                      26/Jun/2014  09:41:59 /
// IAR ANSI C/C++ Compiler V6.30.6.23336/W32 EVALUATION for ARM               /
// Copyright 1999-2012 IAR Systems AB.                                        /
//                                                                            /
//    Cpu mode     =  thumb                                                   /
//    Endian       =  little                                                  /
//    Source file  =  C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4W /
//                    IRE_SPI\src\common\assert.c                             /
//    Command line =  C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4W /
//                    IRE_SPI\src\common\assert.c -D IAR -D TWR_K60N512 -lCN  /
//                    C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4W /
//                    IRE_SPI\build\iar\hello_world\FLASH_512KB_PFLASH\List\  /
//                    -lB C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K6 /
//                    0_4WIRE_SPI\build\iar\hello_world\FLASH_512KB_PFLASH\Li /
//                    st\ -o C:\Users\me\Desktop\OLED�ͻ�����-140509\�������� /
//                    \K60_4WIRE_SPI\build\iar\hello_world\FLASH_512KB_PFLASH /
//                    \Obj\ --no_cse --no_unroll --no_inline                  /
//                    --no_code_motion --no_tbaa --no_clustering              /
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
//                    IRE_SPI\build\iar\hello_world\FLASH_512KB_PFLASH\List\a /
//                    ssert.s                                                 /
//                                                                            /
//                                                                            /
///////////////////////////////////////////////////////////////////////////////

        NAME assert

        #define SHT_PROGBITS 0x1

        EXTERN printf

        PUBLIC ASSERT_FAILED_STR
        PUBLIC assert_failed

// C:\Users\me\Desktop\OLED�ͻ�����-140509\��������\K60_4WIRE_SPI\src\common\assert.c
//    1 /*
//    2  * File:        assert.c
//    3  * Purpose:     Provide macro for software assertions
//    4  *
//    5  * Notes:       ASSERT macro defined in assert.h calls assert_failed()
//    6  */
//    7 
//    8 #include "common.h"
//    9 

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
//   10 const char ASSERT_FAILED_STR[] = "Assertion failed in %s at line %d\n";
ASSERT_FAILED_STR:
        DATA
        DC8 "Assertion failed in %s at line %d\012"
        DC8 0
//   11 
//   12 /********************************************************************/

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   13 void
//   14 assert_failed(char *file, int line)
//   15 {
assert_failed:
        PUSH     {R7,LR}
//   16     int i;
//   17     
//   18     printf(ASSERT_FAILED_STR, file, line);
        MOVS     R2,R1
        MOVS     R1,R0
        LDR.N    R0,??assert_failed_0
        BL       printf
//   19 
//   20     while (1)
//   21     {
//   22 //        platform_led_display(0xFF);
//   23         for (i = 100000; i; i--) ;
??assert_failed_1:
        LDR.N    R0,??assert_failed_0+0x4  ;; 0x186a0
        B.N      ??assert_failed_2
??assert_failed_3:
        SUBS     R0,R0,#+1
??assert_failed_2:
        CMP      R0,#+0
        BNE.N    ??assert_failed_3
//   24 //        platform_led_display(0x00);
//   25         for (i = 100000; i; i--) ;
        LDR.N    R0,??assert_failed_0+0x4  ;; 0x186a0
??assert_failed_4:
        CMP      R0,#+0
        BEQ.N    ??assert_failed_1
        SUBS     R0,R0,#+1
        B.N      ??assert_failed_4
        DATA
??assert_failed_0:
        DC32     ASSERT_FAILED_STR
        DC32     0x186a0
//   26     }
//   27 }

        SECTION `.iar_vfe_header`:DATA:REORDER:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//   28 /********************************************************************/
// 
// 36 bytes in section .rodata
// 40 bytes in section .text
// 
// 40 bytes of CODE  memory
// 36 bytes of CONST memory
//
//Errors: none
//Warnings: none
