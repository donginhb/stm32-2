///////////////////////////////////////////////////////////////////////////////
//                                                                            /
//                                                      07/May/2014  16:39:04 /
// IAR ANSI C/C++ Compiler V6.30.6.23336/W32 EVALUATION for ARM               /
// Copyright 1999-2012 IAR Systems AB.                                        /
//                                                                            /
//    Cpu mode     =  thumb                                                   /
//    Endian       =  little                                                  /
//    Source file  =  C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK60_De /
//                    mo_OLED\src\common\startup.c                            /
//    Command line =  C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK60_De /
//                    mo_OLED\src\common\startup.c -D IAR -D TWR_K60N512      /
//                    -lCN C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK /
//                    60_Demo_OLED\build\iar\hello_world\RAM_128KB\List\ -lB  /
//                    C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\RAM_128KB\List\ -o        /
//                    C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\RAM_128KB\Obj\ --no_cse   /
//                    --no_unroll --no_inline --no_code_motion --no_tbaa      /
//                    --no_clustering --no_scheduling --debug                 /
//                    --endian=little --cpu=Cortex-M4 -e --fpu=None           /
//                    --dlib_config "C:\Program Files (x86)\IAR               /
//                    Systems\Embedded Workbench 6.0                          /
//                    Evaluation\arm\INC\c\DLib_Config_Normal.h" -I           /
//                    C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\..\..\..\src\projects\hel /
//                    lo_world\ -I C:\Users\me\Desktop\OLED�ͻ�����\��������\ /
//                    KinetisK60_Demo_OLED\build\iar\hello_world\..\..\..\src /
//                    \common\ -I C:\Users\me\Desktop\OLED�ͻ�����\��������\K /
//                    inetisK60_Demo_OLED\build\iar\hello_world\..\..\..\src\ /
//                    cpu\ -I C:\Users\me\Desktop\OLED�ͻ�����\��������\Kinet /
//                    isK60_Demo_OLED\build\iar\hello_world\..\..\..\src\cpu\ /
//                    headers\ -I C:\Users\me\Desktop\OLED�ͻ�����\��������\K /
//                    inetisK60_Demo_OLED\build\iar\hello_world\..\..\..\src\ /
//                    drivers\adc16\ -I C:\Users\me\Desktop\OLED�ͻ�����\���� /
//                    ����\KinetisK60_Demo_OLED\build\iar\hello_world\..\..\. /
//                    .\src\drivers\enet\ -I C:\Users\me\Desktop\OLED�ͻ����� /
//                    \��������\KinetisK60_Demo_OLED\build\iar\hello_world\.. /
//                    \..\..\src\drivers\pmc\ -I                              /
//                    C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\..\..\..\src\drivers\rtc\ /
//                     -I C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK6 /
//                    0_Demo_OLED\build\iar\hello_world\..\..\..\src\drivers\ /
//                    lptmr\ -I C:\Users\me\Desktop\OLED�ͻ�����\��������\Kin /
//                    etisK60_Demo_OLED\build\iar\hello_world\..\..\..\src\dr /
//                    ivers\uart\ -I C:\Users\me\Desktop\OLED�ͻ�����\������� /
//                    �\KinetisK60_Demo_OLED\build\iar\hello_world\..\..\..\s /
//                    rc\drivers\mcg\ -I C:\Users\me\Desktop\OLED�ͻ�����\��� /
//                    �����\KinetisK60_Demo_OLED\build\iar\hello_world\..\..\ /
//                    ..\src\drivers\wdog\ -I C:\Users\me\Desktop\OLED�ͻ���� /
//                    �\��������\KinetisK60_Demo_OLED\build\iar\hello_world\. /
//                    .\..\..\src\platforms\ -I C:\Users\me\Desktop\OLED�ͻ�� /
//                    ���\��������\KinetisK60_Demo_OLED\build\iar\hello_world /
//                    \..\..\..\src\drivers\ftm\ -I                           /
//                    C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\..\..\..\src\drivers\SPI\ /
//                     -I C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK6 /
//                    0_Demo_OLED\build\iar\hello_world\..\..\..\src\drivers\ /
//                    OLED\ -I C:\Users\me\Desktop\OLED�ͻ�����\��������\Kine /
//                    tisK60_Demo_OLED\build\iar\hello_world\..\ -On          /
//                    --use_c++_inline                                        /
//    List file    =  C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK60_De /
//                    mo_OLED\build\iar\hello_world\RAM_128KB\List\startup.s  /
//                                                                            /
//                                                                            /
///////////////////////////////////////////////////////////////////////////////

        NAME startup

        #define SHT_PROGBITS 0x1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
        SECTION `.data`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
        SECTION `.data_init`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
        SECTION CodeRelocate:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
        SECTION CodeRelocateRam:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        EXTERN __VECTOR_RAM
        EXTERN __VECTOR_TABLE
        EXTERN write_vtor

        PUBLIC common_startup

// C:\Users\me\Desktop\OLED�ͻ�����\��������\KinetisK60_Demo_OLED\src\common\startup.c
//    1 /*
//    2  * File:    startup.c
//    3  * Purpose: Generic Kinetis startup code
//    4  *
//    5  * Notes:
//    6  */
//    7 
//    8 #include "common.h"
//    9 
//   10 #if (defined(IAR))
//   11 	#pragma section = ".data"
//   12 	#pragma section = ".data_init"
//   13 	#pragma section = ".bss"
//   14 	#pragma section = "CodeRelocate"
//   15 	#pragma section = "CodeRelocateRam"
//   16 #endif
//   17 
//   18 /********************************************************************/

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   19 void
//   20 common_startup(void)
//   21 {
common_startup:
        PUSH     {R3-R9,LR}
//   22 
//   23 #if (defined(CW))	
//   24     extern char __START_BSS[];
//   25     extern char __END_BSS[];
//   26     extern uint32 __DATA_ROM[];
//   27     extern uint32 __DATA_RAM[];
//   28     extern char __DATA_END[];
//   29 #endif
//   30 
//   31     /* Declare a counter we'll use in all of the copy loops */
//   32     uint32 n;
//   33 
//   34     /* Declare pointers for various data sections. These pointers
//   35      * are initialized using values pulled in from the linker file
//   36      */
//   37     uint8 * data_ram, * data_rom, * data_rom_end;
//   38     uint8 * bss_start, * bss_end;
//   39 
//   40 
//   41     /* Addresses for VECTOR_TABLE and VECTOR_RAM come from the linker file */
//   42     extern uint32 __VECTOR_TABLE[];
//   43     extern uint32 __VECTOR_RAM[];
//   44 
//   45     /* Copy the vector table to RAM */
//   46     if (__VECTOR_RAM != __VECTOR_TABLE)
        LDR.N    R0,??common_startup_0
        LDR.N    R1,??common_startup_0+0x4
        CMP      R0,R1
        BEQ.N    ??common_startup_1
//   47     {
//   48         for (n = 0; n < 0x410; n++)
        MOVS     R0,#+0
        MOV      R8,R0
??common_startup_2:
        CMP      R8,#+1040
        BCS.N    ??common_startup_1
//   49             __VECTOR_RAM[n] = __VECTOR_TABLE[n];
        LDR.N    R0,??common_startup_0
        LDR.N    R1,??common_startup_0+0x4
        LDR      R1,[R1, R8, LSL #+2]
        STR      R1,[R0, R8, LSL #+2]
        ADDS     R8,R8,#+1
        B.N      ??common_startup_2
//   50     }
//   51     /* Point the VTOR to the new copy of the vector table */
//   52     write_vtor((uint32)__VECTOR_RAM);
??common_startup_1:
        LDR.N    R0,??common_startup_0
        BL       write_vtor
//   53 
//   54     /* Get the addresses for the .data section (initialized data section) */
//   55 	#if (defined(CW))
//   56         data_ram = (uint8 *)__DATA_RAM;
//   57 	    data_rom = (uint8 *)__DATA_ROM;
//   58 	    data_rom_end  = (uint8 *)__DATA_END; /* This is actually a RAM address in CodeWarrior */
//   59 	    n = data_rom_end - data_ram;
//   60     #elif (defined(IAR))
//   61 		data_ram = __section_begin(".data");
        LDR.N    R0,??common_startup_0+0x8
        MOVS     R7,R0
//   62 		data_rom = __section_begin(".data_init");
        LDR.N    R0,??common_startup_0+0xC
        MOVS     R6,R0
//   63 		data_rom_end = __section_end(".data_init");
        LDR.N    R0,??common_startup_0+0x10
        MOVS     R4,R0
//   64 		n = data_rom_end - data_rom;
        SUBS     R0,R4,R6
        MOV      R8,R0
//   65 	#endif		
//   66 		
//   67 	/* Copy initialized data from ROM to RAM */
//   68 	while (n--)
??common_startup_3:
        MOV      R0,R8
        SUBS     R8,R0,#+1
        CMP      R0,#+0
        BEQ.N    ??common_startup_4
//   69 		*data_ram++ = *data_rom++;
        LDRB     R0,[R6, #+0]
        STRB     R0,[R7, #+0]
        ADDS     R6,R6,#+1
        ADDS     R7,R7,#+1
        B.N      ??common_startup_3
//   70 	
//   71 	
//   72     /* Get the addresses for the .bss section (zero-initialized data) */
//   73 	#if (defined(CW))
//   74 		bss_start = (uint8 *)__START_BSS;
//   75 		bss_end = (uint8 *)__END_BSS;
//   76 	#elif (defined(IAR))
//   77 		bss_start = __section_begin(".bss");
??common_startup_4:
        LDR.N    R0,??common_startup_0+0x14
        MOV      R9,R0
//   78 		bss_end = __section_end(".bss");
        LDR.N    R0,??common_startup_0+0x18
        MOVS     R5,R0
//   79 	#endif
//   80 		
//   81 		
//   82 	
//   83 
//   84     /* Clear the zero-initialized data section */
//   85     n = bss_end - bss_start;
        SUBS     R0,R5,R9
        MOV      R8,R0
//   86     while(n--)
??common_startup_5:
        MOV      R0,R8
        SUBS     R8,R0,#+1
        CMP      R0,#+0
        BEQ.N    ??common_startup_6
//   87       *bss_start++ = 0;
        MOVS     R0,#+0
        STRB     R0,[R9, #+0]
        ADDS     R9,R9,#+1
        B.N      ??common_startup_5
//   88 
//   89 	/* Get addresses for any code sections that need to be copied from ROM to RAM.
//   90 	 * The IAR tools have a predefined keyword that can be used to mark individual
//   91 	 * functions for execution from RAM. Add "__ramfunc" before the return type in
//   92 	 * the function prototype for any routines you need to execute from RAM instead
//   93 	 * of ROM. ex: __ramfunc void foo(void);
//   94 	 */
//   95 	#if (defined(IAR))
//   96 		uint8* code_relocate_ram = __section_begin("CodeRelocateRam");
??common_startup_6:
        LDR.N    R0,??common_startup_0+0x1C
//   97 		uint8* code_relocate = __section_begin("CodeRelocate");
        LDR.N    R1,??common_startup_0+0x20
//   98 		uint8* code_relocate_end = __section_end("CodeRelocate");
        LDR.N    R2,??common_startup_0+0x24
//   99 
//  100 		/* Copy functions from ROM to RAM */
//  101 		n = code_relocate_end - code_relocate;
        SUBS     R3,R2,R1
        MOV      R8,R3
//  102 		while (n--)
??common_startup_7:
        MOV      R3,R8
        SUBS     R8,R3,#+1
        CMP      R3,#+0
        BEQ.N    ??common_startup_8
//  103 			*code_relocate_ram++ = *code_relocate++;
        LDRB     R3,[R1, #+0]
        STRB     R3,[R0, #+0]
        ADDS     R1,R1,#+1
        ADDS     R0,R0,#+1
        B.N      ??common_startup_7
//  104 	#endif
//  105 }
??common_startup_8:
        POP      {R0,R4-R9,PC}    ;; return
        DATA
??common_startup_0:
        DC32     __VECTOR_RAM
        DC32     __VECTOR_TABLE
        DC32     SFB(`.data`)
        DC32     SFB(`.data_init`)
        DC32     SFE(`.data_init`)
        DC32     SFB(`.bss`)
        DC32     SFE(`.bss`)
        DC32     SFB(CodeRelocateRam)
        DC32     SFB(CodeRelocate)
        DC32     SFE(CodeRelocate)

        SECTION `.iar_vfe_header`:DATA:REORDER:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION `.data`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION `.data_init`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION CodeRelocate:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION CodeRelocateRam:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//  106 /********************************************************************/
// 
// 192 bytes in section .text
// 
// 192 bytes of CODE memory
//
//Errors: none
//Warnings: none
