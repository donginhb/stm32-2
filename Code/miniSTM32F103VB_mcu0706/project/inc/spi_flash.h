//  SPI_BB_DEC.h  
 //............................................................................
 //  FUNCTIONS DECLARATIONS 
 //............................................................................
 // File Name    : spi_flash.h 
 // Dependencies :    
 // Processor    :   
 // Hardware     : MicroChip's SPI EEPROM = 25xx256 on MCB950 EVB . 
 // I.D.E.       : uVision3 - Keil 
 // Company      : MicroChip Technology , Inc. 
 //...........................................................................
 //                      SOFTWARE  LICENSE AGREEMENT 
 //...........................................................................
 // "Microchip Technology Inc. (“Microchip? licenses this software to you 
 // solely for use with Microchip Serial EEPROM products. 
 // The software is owned by Microchip and/or its licensors,and is protected 
 // under applicable copyright laws.  All rights reserved.
 // SOFTWARE IS PROVIDED “AS IS.? MICROCHIP AND ITS LICENSOR EXPRESSLY 
 // DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING 
 // BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS 
 // FOR A PARTICULAR PURPOSE,OR NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP 
 // AND ITS LICENSORS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR 
 // CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, 
 // COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY 
 // CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 // THEREOF),ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS."
 //***************************************************************************
 // History      :  V1.0 - Initial Release 
 //...........................................................................
 // File Description : This is the file declaring all the necesary functions
 //                    for the application note ANxxxx . 
 //                    Functions are declared in the below file as external 
 // functions , using formal variable . Accordingly , they will be defined 
 // in the mirror file : spi_bb_def.c . As described , there are 3 types of 
 // functions : initialization , spi_access , auxiliary .                     
 //............................................................................
 //                  INITIALIZATION FUNCTIONS DECLARATIONS  
 //............................................................................  
    extern void SPIF_GpioInit( void );
    extern void  SPIF_MemInit(void);     // memory(prot) init 
 //............................................................................
 //                  SPI  ACCESS FUNCTIONS  DECLARATIONS 
 //............................................................................
    extern void spi_start(void) ; //  SPI START  
    extern void spi_stop(void) ; //  SPI STOP   
    extern void spi_wren(void) ; //  write enable  
    extern void spi_wr(u8 data); //  WRITE 8b stream 
    extern u8  spi_rd(void)  ; //  READ  8b stream 
    extern void spi_rndwr(u16 , unsigned char) ; //  WRITE rand byte 
    extern void spi_rndrd(u16, unsigned char*); //  READ  rand byte 
    extern void spi_pgwr(unsigned char*, u16,unsigned char) ;  //  PAGE WRITE                                                        
    extern void spi_pgrd(unsigned char*, u16, unsigned char) ;  //  PAGE READ 
    #ifdef SPI_FLASH_DUB
    extern void spif_test(void)  ;
#endif//#ifdef SPI_FLASH_DUB
//.............................................................................
//                   AUXILIARY  FUNCTIONS  DECLARATIONS 
//............................................................................. 
      extern void dly5ms(void); // 5 msec delay 
      extern void dly250ms(void); // 250 msec delay 
      extern void dly1s(void); // 1 sec delay     
