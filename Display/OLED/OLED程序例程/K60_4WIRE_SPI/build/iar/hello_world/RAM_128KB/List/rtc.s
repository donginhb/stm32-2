///////////////////////////////////////////////////////////////////////////////
//                                                                            /
//                                                      07/May/2014  16:39:04 /
// IAR ANSI C/C++ Compiler V6.30.6.23336/W32 EVALUATION for ARM               /
// Copyright 1999-2012 IAR Systems AB.                                        /
//                                                                            /
//    Cpu mode     =  thumb                                                   /
//    Endian       =  little                                                  /
//    Source file  =  C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK60_De /
//                    mo_OLED\src\drivers\rtc\rtc.c                           /
//    Command line =  C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK60_De /
//                    mo_OLED\src\drivers\rtc\rtc.c -D IAR -D TWR_K60N512     /
//                    -lCN C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK /
//                    60_Demo_OLED\build\iar\hello_world\RAM_128KB\List\ -lB  /
//                    C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\RAM_128KB\List\ -o        /
//                    C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\RAM_128KB\Obj\ --no_cse   /
//                    --no_unroll --no_inline --no_code_motion --no_tbaa      /
//                    --no_clustering --no_scheduling --debug                 /
//                    --endian=little --cpu=Cortex-M4 -e --fpu=None           /
//                    --dlib_config "C:\Program Files (x86)\IAR               /
//                    Systems\Embedded Workbench 6.0                          /
//                    Evaluation\arm\INC\c\DLib_Config_Normal.h" -I           /
//                    C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\..\..\..\src\projects\hel /
//                    lo_world\ -I C:\Users\me\Desktop\OLED客户资料\程序例程\ /
//                    KinetisK60_Demo_OLED\build\iar\hello_world\..\..\..\src /
//                    \common\ -I C:\Users\me\Desktop\OLED客户资料\程序例程\K /
//                    inetisK60_Demo_OLED\build\iar\hello_world\..\..\..\src\ /
//                    cpu\ -I C:\Users\me\Desktop\OLED客户资料\程序例程\Kinet /
//                    isK60_Demo_OLED\build\iar\hello_world\..\..\..\src\cpu\ /
//                    headers\ -I C:\Users\me\Desktop\OLED客户资料\程序例程\K /
//                    inetisK60_Demo_OLED\build\iar\hello_world\..\..\..\src\ /
//                    drivers\adc16\ -I C:\Users\me\Desktop\OLED客户资料\程序 /
//                    例程\KinetisK60_Demo_OLED\build\iar\hello_world\..\..\. /
//                    .\src\drivers\enet\ -I C:\Users\me\Desktop\OLED客户资料 /
//                    \程序例程\KinetisK60_Demo_OLED\build\iar\hello_world\.. /
//                    \..\..\src\drivers\pmc\ -I                              /
//                    C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\..\..\..\src\drivers\rtc\ /
//                     -I C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK6 /
//                    0_Demo_OLED\build\iar\hello_world\..\..\..\src\drivers\ /
//                    lptmr\ -I C:\Users\me\Desktop\OLED客户资料\程序例程\Kin /
//                    etisK60_Demo_OLED\build\iar\hello_world\..\..\..\src\dr /
//                    ivers\uart\ -I C:\Users\me\Desktop\OLED客户资料\程序例� /
//                    蘚KinetisK60_Demo_OLED\build\iar\hello_world\..\..\..\s /
//                    rc\drivers\mcg\ -I C:\Users\me\Desktop\OLED客户资料\程� /
//                    蚶蘚KinetisK60_Demo_OLED\build\iar\hello_world\..\..\ /
//                    ..\src\drivers\wdog\ -I C:\Users\me\Desktop\OLED客户资� /
//                    蟎程序例程\KinetisK60_Demo_OLED\build\iar\hello_world\. /
//                    .\..\..\src\platforms\ -I C:\Users\me\Desktop\OLED客户� /
//                    柿蟎程序例程\KinetisK60_Demo_OLED\build\iar\hello_world /
//                    \..\..\..\src\drivers\ftm\ -I                           /
//                    C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\..\..\..\src\drivers\SPI\ /
//                     -I C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK6 /
//                    0_Demo_OLED\build\iar\hello_world\..\..\..\src\drivers\ /
//                    OLED\ -I C:\Users\me\Desktop\OLED客户资料\程序例程\Kine /
//                    tisK60_Demo_OLED\build\iar\hello_world\..\ -On          /
//                    --use_c++_inline                                        /
//    List file    =  C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\RAM_128KB\List\rtc.s      /
//                                                                            /
//                                                                            /
///////////////////////////////////////////////////////////////////////////////

        NAME rtc

        #define SHT_PROGBITS 0x1

        EXTERN enable_irq
        EXTERN printf

        PUBLIC rtc_init
        PUBLIC rtc_isr

// C:\Users\me\Desktop\OLED客户资料\程序例程\KinetisK60_Demo_OLED\src\drivers\rtc\rtc.c
//    1 /*
//    2  * File:        rtc.c
//    3  * Purpose:     Provide common RTC routines
//    4  *
//    5  * Notes:       
//    6  *              
//    7  */
//    8 
//    9 
//   10 #include "common.h"
//   11 #include "rtc.h"
//   12 #include "arm_cm4.h"
//   13 
//   14 /********************************************************************/
//   15 /*
//   16  * Initialize the RTC
//   17  *
//   18  *
//   19  * Parameters:
//   20  *  seconds         Start value of seconds register
//   21  *  alarm           Time in seconds of first alarm. Set to 0xFFFFFFFF to effectively disable alarm
//   22  *  c_interval      Interval at which to apply time compensation can range from 1 second (0x0) to 256 (0xFF)
//   23  *  c_value         Compensation value ranges from -127 32kHz cycles to +128 32 kHz cycles
//   24  *                  80h Time prescaler register overflows every 32896 clock cycles.
//   25  *                  FFh Time prescaler register overflows every 32769 clock cycles.
//   26  *                  00h Time prescaler register overflows every 32768 clock cycles.
//   27  *                  01h Time prescaler register overflows every 32767 clock cycles.
//   28  *                  7Fh Time prescaler register overflows every 32641 clock cycles.
//   29  *  interrupt       TRUE or FALSE
//   30  */
//   31 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   32 void rtc_init(uint32 seconds, uint32 alarm, uint8 c_interval, uint8 c_value, uint8 interrupt) 
//   33 {
rtc_init:
        PUSH     {R3-R9,LR}
        MOVS     R5,R0
        MOVS     R6,R1
        MOVS     R7,R2
        MOV      R8,R3
        LDR      R4,[SP, #+32]
//   34   int i;
//   35   
//   36   /*enable the clock to SRTC module register space*/
//   37   SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;
        LDR.N    R0,??DataTable1  ;; 0x4004803c
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x20000000
        LDR.N    R1,??DataTable1  ;; 0x4004803c
        STR      R0,[R1, #+0]
//   38   
//   39   /*Only VBAT_POR has an effect on the SRTC, RESET to the part does not, so you must manually reset the SRTC to make sure everything is in a known state*/
//   40   /*clear the software reset bit*/
//   41   RTC_CR  = RTC_CR_SWR_MASK;
        LDR.N    R0,??DataTable1_1  ;; 0x4003d010
        MOVS     R1,#+1
        STR      R1,[R0, #+0]
//   42   RTC_CR  &= ~RTC_CR_SWR_MASK;  
        LDR.N    R0,??DataTable1_1  ;; 0x4003d010
        LDR      R0,[R0, #+0]
        LSRS     R0,R0,#+1
        LSLS     R0,R0,#+1
        LDR.N    R1,??DataTable1_1  ;; 0x4003d010
        STR      R0,[R1, #+0]
//   43   
//   44   /*Enable the interrupt*/
//   45   if(interrupt)
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+0
        BEQ.N    ??rtc_init_0
//   46     enable_irq(66);
        MOVS     R0,#+66
        BL       enable_irq
//   47   
//   48   /*Enable the oscillator*/
//   49   RTC_CR |= RTC_CR_OSCE_MASK;
??rtc_init_0:
        LDR.N    R0,??DataTable1_1  ;; 0x4003d010
        LDR      R0,[R0, #+0]
        MOV      R1,#+256
        ORRS     R0,R1,R0
        LDR.N    R1,??DataTable1_1  ;; 0x4003d010
        STR      R0,[R1, #+0]
//   50   
//   51   /*Wait to all the 32 kHz to stabilize, refer to the crystal startup time in the crystal datasheet*/
//   52   for(i=0;i<0x600000;i++);
        MOVS     R0,#+0
        MOV      R9,R0
??rtc_init_1:
        CMP      R9,#+6291456
        BGE.N    ??rtc_init_2
        ADDS     R9,R9,#+1
        B.N      ??rtc_init_1
//   53   
//   54   /*Set time compensation parameters*/
//   55   RTC_TCR = RTC_TCR_CIR(c_interval) | RTC_TCR_TCR(c_value);
??rtc_init_2:
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        ORRS     R0,R8,R7, LSL #+8
        LDR.N    R1,??DataTable1_2  ;; 0x4003d00c
        STR      R0,[R1, #+0]
//   56   
//   57   /*Configure the timer seconds and alarm registers*/
//   58   RTC_TSR = seconds;
        LDR.N    R0,??DataTable1_3  ;; 0x4003d000
        STR      R5,[R0, #+0]
//   59   RTC_TAR = alarm;
        LDR.N    R0,??DataTable1_4  ;; 0x4003d008
        STR      R6,[R0, #+0]
//   60   
//   61   /*Enable the counter*/
//   62   RTC_SR |= RTC_SR_TCE_MASK;
        LDR.N    R0,??DataTable1_5  ;; 0x4003d014
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x10
        LDR.N    R1,??DataTable1_5  ;; 0x4003d014
        STR      R0,[R1, #+0]
//   63   
//   64 }
        POP      {R0,R4-R9,PC}    ;; return
//   65 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   66 void rtc_isr(void) 
//   67 {
rtc_isr:
        PUSH     {R7,LR}
//   68    
//   69    if((RTC_SR & RTC_SR_TIF_MASK)== 0x01)
        LDR.N    R0,??DataTable1_5  ;; 0x4003d014
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+31
        BPL.N    ??rtc_isr_0
//   70      {
//   71        printf("SRTC time invalid interrupt entered...\r\n");
        LDR.N    R0,??DataTable1_6
        BL       printf
//   72    	   RTC_SR &= 0x07;  //clear TCE, or RTC_TSR can  not be written
        LDR.N    R0,??DataTable1_5  ;; 0x4003d014
        LDR      R0,[R0, #+0]
        ANDS     R0,R0,#0x7
        LDR.N    R1,??DataTable1_5  ;; 0x4003d014
        STR      R0,[R1, #+0]
//   73    	   RTC_TSR = 0x00000000;  //clear TIF 
        LDR.N    R0,??DataTable1_3  ;; 0x4003d000
        MOVS     R1,#+0
        STR      R1,[R0, #+0]
        B.N      ??rtc_isr_1
//   74      }	
//   75    else if((RTC_SR & RTC_SR_TOF_MASK) == 0x02)
??rtc_isr_0:
        LDR.N    R0,??DataTable1_5  ;; 0x4003d014
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+30
        BPL.N    ??rtc_isr_2
//   76    {
//   77    	   printf("SRTC time overflow interrupt entered...\r\n");
        LDR.N    R0,??DataTable1_7
        BL       printf
//   78    	   RTC_SR &= 0x07;  //clear TCE, or RTC_TSR can  not be written
        LDR.N    R0,??DataTable1_5  ;; 0x4003d014
        LDR      R0,[R0, #+0]
        ANDS     R0,R0,#0x7
        LDR.N    R1,??DataTable1_5  ;; 0x4003d014
        STR      R0,[R1, #+0]
//   79    	   RTC_TSR = 0x00000000;  //clear TOF
        LDR.N    R0,??DataTable1_3  ;; 0x4003d000
        MOVS     R1,#+0
        STR      R1,[R0, #+0]
        B.N      ??rtc_isr_1
//   80    }	 	
//   81    else if((RTC_SR & RTC_SR_TAF_MASK) == 0x04)
??rtc_isr_2:
        LDR.N    R0,??DataTable1_5  ;; 0x4003d014
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+29
        BPL.N    ??rtc_isr_3
//   82    {
//   83    	   printf("SRTC alarm interrupt entered...\r\n");
        LDR.N    R0,??DataTable1_8
        BL       printf
//   84            printf("Time Seconds Register value is: %i\n", RTC_TSR);
        LDR.N    R0,??DataTable1_3  ;; 0x4003d000
        LDR      R1,[R0, #+0]
        LDR.N    R0,??DataTable1_9
        BL       printf
//   85    	   RTC_TAR += 1;// Write new alarm value, to generate an alarm every second add 1
        LDR.N    R0,??DataTable1_4  ;; 0x4003d008
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.N    R1,??DataTable1_4  ;; 0x4003d008
        STR      R0,[R1, #+0]
        B.N      ??rtc_isr_1
//   86    }	
//   87    else
//   88    {
//   89            printf("No valid Flag was set!\n");
??rtc_isr_3:
        LDR.N    R0,??DataTable1_10
        BL       printf
//   90    }
//   91    return;
??rtc_isr_1:
        POP      {R0,PC}          ;; return
//   92 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1:
        DC32     0x4004803c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_1:
        DC32     0x4003d010

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_2:
        DC32     0x4003d00c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_3:
        DC32     0x4003d000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_4:
        DC32     0x4003d008

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_5:
        DC32     0x4003d014

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_6:
        DC32     `?<Constant "SRTC time invalid int...">`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_7:
        DC32     `?<Constant "SRTC time overflow in...">`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_8:
        DC32     `?<Constant "SRTC alarm interrupt ...">`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_9:
        DC32     `?<Constant "Time Seconds Register...">`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_10:
        DC32     `?<Constant "No valid Flag was set!\\n">`

        SECTION `.iar_vfe_header`:DATA:REORDER:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
`?<Constant "SRTC time invalid int...">`:
        DATA
        DC8 "SRTC time invalid interrupt entered...\015\012"
        DC8 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
`?<Constant "SRTC time overflow in...">`:
        DATA
        DC8 "SRTC time overflow interrupt entered...\015\012"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
`?<Constant "SRTC alarm interrupt ...">`:
        DATA
        DC8 "SRTC alarm interrupt entered...\015\012"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
`?<Constant "Time Seconds Register...">`:
        DATA
        DC8 "Time Seconds Register value is: %i\012"

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
`?<Constant "No valid Flag was set!\\n">`:
        DATA
        DC8 "No valid Flag was set!\012"

        END
// 
// 184 bytes in section .rodata
// 282 bytes in section .text
// 
// 282 bytes of CODE  memory
// 184 bytes of CONST memory
//
//Errors: none
//Warnings: none
