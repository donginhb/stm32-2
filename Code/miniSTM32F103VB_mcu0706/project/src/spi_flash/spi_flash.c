//                   SPI_BB_DEF.C  - FUNCTIONS  DEFINITION 
 //****************************************************************************
 // File Name    : c_spi_bb_def.c 
 // Dependencies : .h = functions declaration  
 //                .h     = SFRs definitions offered by "Keil" 
 //                   = start-up code for LPC952 ( "Keil" )  
 // Processor    :   
 // Hardware     : MicroChip's SPI EEPROM = 25xx256 on . 
 // I.D.E.       : uVision3 - Keil 
 // Company      : MicroChip Technology , Inc. 
 //...........................................................................
 //                       SOFTWARE  LICENSE AGREEMENT 
 //...........................................................................
 // "Microchip Technology Inc. (Microchip licenses this software to you 
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
 //                    Functions are declared in "spi_bb_dec.h" and defined in
 // the below file . As described , there are 3 types of  functions : 
 // initialization , spi_access , auxiliary . Moreover , the function defines 
 // the public variables ( byte & bit ) and the slave_address constants :
 // for write and read .                     
 //.............................................................................
#include "includes.h"

#if SPI_FLASH_EN >0 
//.............................................................................
//                         GLOBAL CONSTANTS 
//............................................................................
#define SPIF_CMD_READ    0x03       // SPIF_CMD_READ       instruction code  
#define SPIF_CMD_WRITE   0x02       // SPIF_CMD_WRITE      instruction code 
#define SPIF_CMD_WRDI    0x04       // WR DISBALE instruction code 
#define SPIF_CMD_WREN    0x06       // WR ENABLE  instruction code
#define SPIF_CMD_RDSR     0x05       // RD STATUS  instruction code 
#define SPIF_CMD_WRSR     0x01       // WR STATUS  instruction code 
#define SPIF_CMD_NOPROT  0x00       // NO SPIF_CMD_WRITE PROTECTION 
//............................................................................ 
//                        GLOBAL  VARIABLES
//............................................................................  
//                        INITIALIZATION FUNCTIONS  
//...........................................................................
/******************************************************************************
* Function Name  : Stepper_GpioInitA3979
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void SPIF_GpioInit( void )
{

        GPIO_InitTypeDef GPIO_InitStructure;	 
	  /* Configure IO connected to *********************/
	  /* Enable  clock  output  init*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_SPIF , ENABLE);

	GPIO_InitStructure.GPIO_Pin =  SPIF_MISO_PIN ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_Init(GPIO_SPIF , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  SPIF_SS_PIN|SPIF_CLK_PIN |SPIF_MOSI_PIN ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed =  GPIO_SPEED_SPIF;
	GPIO_Init(GPIO_SPIF , &GPIO_InitStructure);
	
	GPIO_SetBits( GPIO_SPIF ,  SPIF_SS_PIN );
	GPIO_SetBits( GPIO_SPIF,  SPIF_CLK_PIN );
	GPIO_SetBits( GPIO_SPIF,  SPIF_MOSI_PIN );
	//	
	Delaynus(100);	
}
static void DelayIO( )
{
	Delay(10);
}
void SPIF_MemInit(void)
{  
	spi_wren()           ;  // enable writes in the memory 
	spi_start()          ;  // SPIF_SS_PIN=nCS=0 , start access  
	spi_wr(SPIF_CMD_WRSR)  ;  // program "write status reg" instruction 
	spi_wr(SPIF_CMD_NOPROT)  ;  // write "no protection" in the status reg
	spi_stop()           ;  // SPIF_SS_PIN=nCS=1 , stop access  
	dly5ms()         ;  
}  // write cycle time 
//.............................................................................  
//                   SPI  ACCESS FUNCTIONS  DEFINITIONS 
//*****************************************************************************
void spi_start(void) 
{ 
	GPIO_SetBits( GPIO_SPIF ,  SPIF_SS_PIN );
	GPIO_ResetBits( GPIO_SPIF ,  SPIF_SS_PIN );
	//DelayIO();
}  // assert nCS=0                                                                 
//.............................................................................
void spi_stop(void) 
{	
	GPIO_ResetBits( GPIO_SPIF ,  SPIF_SS_PIN );
	GPIO_SetBits( GPIO_SPIF ,  SPIF_SS_PIN );
	//DelayIO();
}  // assert nCS=1                      
//.............................................................................
void spi_wren(void) 
{ 
	spi_start()            ;   // SPIF_SS_PIN=nCS=0 , start access 
	spi_wr(SPIF_CMD_WREN)    ;   // insert "write enable" command . 
	spi_stop()        ;  
}   // SPIF_SS_PIN=nCS=1 , stop access  
//............................................................................

void spi_wr(u8 data)           // write an 8b streaming 
{
	unsigned char bit_count = 0 ;    // bit counter for the 8b streaming 
        while(bit_count<8)               // 8 bits cycle          
        { 
        	if( data & 0x80)
			GPIO_SetBits( GPIO_SPIF,  SPIF_MOSI_PIN );
		else
			GPIO_ResetBits( GPIO_SPIF,  SPIF_MOSI_PIN );
			
		GPIO_ResetBits( GPIO_SPIF,  SPIF_CLK_PIN );     // pulse low SPIF_CLK_PIN  
		DelayIO();
		GPIO_SetBits( GPIO_SPIF,  SPIF_CLK_PIN );      // the memory will read on rising edge
		DelayIO();
		data = data << 1        ;    // shift left 1bit the eep's data buf 
		bit_count++         ;  
	  } 
}    // increment bit counter(repeat for 8b)
//............................................................................
unsigned char spi_rd(void)      // read an 8b streaming 
{
	unsigned char bit_count=0  ;    // bit counter of the 8b streaming 
	u8 tdata = 0 ;
	while(bit_count<8)              // 8 bits cycle 
       { 
		GPIO_ResetBits( GPIO_SPIF,  SPIF_CLK_PIN );     // pulse low SPIF_CLK_PIN  
		DelayIO();
		GPIO_SetBits( GPIO_SPIF,  SPIF_CLK_PIN );      // the memory will read on rising edge
		DelayIO();
		tdata = tdata<<1         ;    // shift left 1b eeprom data buffer  
		if(GPIO_ReadInputDataBit( GPIO_SPIF,  SPIF_MISO_PIN ))    // read bit_n from eeprom   
			tdata |= 0x01 ;
		else
			tdata &= ~0x01 ;		
		bit_count++      ;        
	}    // increment bit counter(repeat for 8b) 
	return tdata   ;        
}    // return read data byte                                          
//...........................................................................
void spi_rndwr(u16 eep_adr, unsigned char eep_data) 
{  
	spi_wren() ;    // enable future writes 
	spi_start() ;    // START command 

	spi_wr(SPIF_CMD_WRITE)   ;    // insert SPIF_CMD_WRITE instruction  
	spi_wr((u8)(eep_adr>>8)  )       ;    // write the high_byte of the adr    
	spi_wr( (u8)(eep_adr&0xff) ) ;    // write the  low_byte of the adr
	spi_wr(eep_data) ;    // write the data_character 
	spi_stop()  ;    // finally , STOP command
	dly5ms()   ;    
}    // write cycle time     
//............................................................................
void spi_rndrd(u16 eep_adr,unsigned char *dst) 
{  
	spi_start()                ;  // START command 
	spi_wr(SPIF_CMD_READ)                   ;  // write instruction code = SPIF_CMD_READ  
	spi_wr((u8)(eep_adr>>8)  )       ;    // write the high_byte of the adr    
	spi_wr( (u8)(eep_adr&0xff) ) ;    // write the  low_byte of the adr  
	*dst = spi_rd()               ;  // read random byte 
	spi_stop()         ;     
}  // STOP command 
                                       // WILL IT WORK WITH EEP_DATA ??? 
//............................................................................
void spi_pgwr(unsigned char *source, u16 eep_adr, unsigned char lofsstr)
   { // lofsstr = length of the source string 
	unsigned char k=0              ;  // char counter 
	spi_wren()                     ;  // enable future writes 
	spi_start()                    ;  // START command 
	spi_wr(SPIF_CMD_WRITE)     ;  // insert SPIF_CMD_WRITE instruction 
	spi_wr((u8)(eep_adr>>8)  )       ;    // write the high_byte of the adr    
	spi_wr( (u8)(eep_adr&0xff) ) ;    // write the  low_byte of the adr  
	while( k < lofsstr ) 
	{ 
		spi_wr(*source)   ;  // write char from the source str 
		source++ ;
		k++ ;               
	}  // increment pointer & counter            
	spi_stop() ; 
	dly5ms()  ;       
}  // STOP + write cycle time 
//............................................................................
void spi_pgrd(unsigned char *dest, u16 eep_adr,unsigned char lofdstr) 
{
     // lofdstr = length of the destination string 
	unsigned char k=0  ;  // char counter  
	spi_start()   ;  // START command 
	spi_wr(SPIF_CMD_READ)  ;  // insert SPIF_CMD_READ instruction 
	spi_wr((u8)(eep_adr>>8)  )   ;    // write the high_byte of the adr    
	spi_wr( (u8)(eep_adr&0xff) ) ;    // write the  low_byte of the adr  
	while( k < lofdstr ) 
	{
		*dest =spi_rd()   ;    // read char in the destination str 
		dest++    ;
		k++  ;         
	}  // increment pointer & counter            
	spi_stop()       ;          
}  // STOP command      

//............................................................................
void dly5ms(void)                 // 5 miliseconds delay 
{ 
	unsigned char j = 100      ;      // 100 * 50usec = 5 msec 
	while(--j) 
	{
		Delaynus(50) ;
	}  
}  
//............................................................................
void dly250ms(void)               // 250 miliseconds delay 
{
	unsigned char k = 50       ;      //  50 * 5 msec = 250 msec 
	while(--k) 
	{ 
		dly5ms()      ; 
	}    // usefull for messages' display
}  
//.............................................................................
void dly1s(void)                  // 1 second delay  
{ 
	dly250ms() ;
	dly250ms() ;      // 4 * 250 ms = 1 second 
	dly250ms() ; 
	dly250ms() ;   
}  // usefull for messages' display
#ifdef SPI_FLASH_DUB
//.............................................................................        
//*******************************************************
void spif_test(void)   
{ 
        #define  ADR0  0x0040          // initialization of the address
        #define  STRSZ     32          //32 page string length   --25LC640
        #define  RND_MODE   0          // random mode 
        #define   PG_MODE   1          // page mode
 //........................................................................... 
        unsigned int adr_cnt        ;  // address counter 
        unsigned char ch_cnt        ;  // character counter inside  strings        
        unsigned int n              ;  // auxiliary variable used to display 
        unsigned int duty           ;  // the variable duty PWM
        unsigned char access_mode = RND_MODE ;  // access mode = RANDOM MODE
   //   unsigned char access_mode =  PG_MODE ;  // access mode = PAGE   MODE  
 //........................................................................... 
        unsigned char *src_str = "0123456789-abcdefghi-jklmnopqr-s" ;           //"s-rqponmlkj-ihgfedcba-9876543210";//      
        unsigned char dst_str[STRSZ];  // destination string,read from the eep   
         //  call all initialization routines   
        SPIF_GpioInit()  ;  	//  GPIO's       init , change for SPI    
        SPIF_MemInit()  ; 	 //  init the SPI memory , no wr prot 
 // WRITE SOURCE STRING IN EEPROM 
 //............................................................................
	if( access_mode==RND_MODE )      // IF random access mode 
	{ 
		ch_cnt=0  ;  
		adr_cnt=ADR0   ;  // intialize necessary variables 
		while(ch_cnt<STRSZ)            // for all chars in the source string 
		{
			spi_rndwr(adr_cnt, src_str[ch_cnt]) ;  // perform random byte write  
			ch_cnt++ ; 
			adr_cnt++ ; 
		}   
	}  // increment char + address counters 
        else                           // IF page access mode 
	{
		spi_pgwr(src_str,ADR0,STRSZ)   ; 
	}  // perform page write from source str,  ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬? // READ EEPROM IN THE DESTINATION STRING 
 // ...........................................................................
	if( access_mode==RND_MODE )      // IF random access mode 
	{ 
		ch_cnt=0 ; 
		adr_cnt=ADR0  ;  // intialize necessary variables 
		while(ch_cnt<STRSZ)            // for all chars in the source string 
		{ 
			spi_rndrd(adr_cnt,dst_str+ch_cnt);  // perform random byte read   
			adr_cnt++ ;
                     ch_cnt++ ;  
                }   
	}  // increment char + address counters 
	else                           // IF page access mode 
	{
		spi_pgrd(dst_str,ADR0,STRSZ) ; 
	}  // perform page read in dest str, ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬
 // COMPARE SOURCE & DESTINATION STRINGS 
 //............................................................................
	for(ch_cnt=0;ch_cnt<STRSZ;ch_cnt++)      // STRSZ length comparison cycle  
	{
		if((*(dst_str+ch_cnt))!=(*(src_str+ch_cnt))) // compare source <> destination
		{
			while(1)                            // IF error flash for ever 
			{ 
				LedAutoOnOff(LED1);
				dly250ms();	
			}
		}     // LEDs once / second 		
	  }     // once / second                        
 // An alternative to this "success" sequence is to gradualy light the 8 LEDs 
 // through a PWM with self-variable duty-cycle . Below , the possible code .
  #define  speed   0x010             // the speed of changing the PWM ratio
  #define MAXDUTY  3000              // MAXDUTY steps for the PWM 
	while(1)  
	{ 
		n++ ; 
		if(n<duty)
			Led( LED1, LED_ON );
		else      
			Led( LED1, LED_OFF);
		if(n>MAXDUTY) { duty +=speed ; n=0x0000 ; } 
		if(duty>MAXDUTY) { duty=0x0000 ; } 
        } 
} 
#endif //#ifdef SPI_FLASH_DUB
#endif //#if SPI_FLASH_EN >0 
 // *************************************************************************** 
