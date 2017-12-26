
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

/* include files  */
#include "stdlib/stm32f10x.h"
#include "platform_init.h"	
#include "gpio.h"
#include "usart.h"
#include "usart_app.h"
#include "exti.h"
#include "timer.h"	
#include "delay.h"
#include "main.h"
#include "stm32f10x_it.h"
#include "string.h"
#include "spi_enc28j60.h"
#include "enc28j60.h"
#include "uip.h"
#include "uip_arp.h"
#include "uipopt.h"
#include "clock-arch.h"
#include "uip_timer.h"
#include "tapdev.h"
#include "dhcpc.h"


void Hex2Str(unsigned char hex);
void Hex2HexStr(unsigned char hex);
void U16_2Str(unsigned int portnum);
int  ReplaceStr(char *sSrc, char *sSubStr, char *sReplaceStr);

#define  RST_CPU()      (*((u32*)0xE000ED0C)=0x05fa0004) /*ϵͳ��λ*/


/********************************* debug define ********************************************/
#define  CPU_DOG		     0	 //jlink����ʱ�����Կ���
#define  CPU_DEBUG_TIMER     0	 //UIP��ʱ���������
#define  CPU_DEBUG_KEEPALIVE 0	 //����������ʱ�����
#define  CPU_DEBUG           1	 //ϵͳ��Ϣ��ӡ����
#define  TCP_LOOKBACK        1   //��̫��TCPЭ��ش�,��Ҫ���ڲ������ܵ�Ӧ��
#define  TCP2UART1           0   //��̫��TCPת��UART1
#define  TCP2UART2           0   //��̫��TCPת��UART2
#define  UIP_STATIC_IP_ADDR      //����DHCP����ʱ��ע������
/********************************* debug define ********************************************/



/********************************* private define ********************************************/
#define  SOCKET_COMM_ON		 0	 //ͨ���л���׼����
#define  SOCKET_COMM_OFF	 1	 //��Ҫ�ر� socket
/********************************* private define ********************************************/

/*! \brief Buf1 that store usart1's data, this macro indicates the buffer volume.
 */
#define  BUF1_LEN            1024	         // the dimension of the buufer used in usart1  
/*! \brief Buf2 that store usart2's data, this macro indicates the buffer volume.
 */
#define  BUF2_LEN            255	         // the dimension of the buufer used in usart1  


#define  array_maxlen        1024			 //	the length of the array which store the data from buffer



/********************************* private typedef ********************************************/

/*Flags for instruction's*/

#if 0
/*add by web server*/
typedef uint8_t  uchar;
typedef uint16_t  ushort;
#define ARRAY_LENGTH( arr ) (sizeof(arr) / sizeof(arr[0]))
#endif


typedef struct
{
	u8 event;
	u8 send_times;
	u8 send_str;
	u8 send_end;
	u8 send_count;
	u8 send_ok;

}flags_typedef;


extern unsigned char  volatile  sys_year;
extern unsigned char  volatile  sys_month;
extern unsigned char  volatile  sys_date;
extern unsigned char  volatile  sys_hour;
extern unsigned char  volatile  sys_minute;
extern unsigned char  volatile  sys_second;


/********************************* global variables ******************************************/
extern unsigned int  volatile  Sys_Dog_start;      
extern unsigned int  volatile  Sys_Dog_Count;        
extern __IO int32_t time_1000ms;
extern char caNewString[1024];	        
extern char HexTable[];                          
extern char HEXStr[32];	                                       
extern char sssStr[5];	
/*usart1*/
extern u8 volatile rcv_usart1_str_flag;
extern u8 volatile rcv_usart1_end_flag;					             
extern u8 volatile rcv_usart1_over_count;
extern u8          rcv_usart1_array[BUF1_LEN];
extern u8 volatile rcv_usart1_data_flg;
extern u16 volatile rcv_usart1_data_len;

extern u8 *inTx1Buf;
extern u8 *outTx1Buf; 
extern u8 *inRx1Buf;
extern u8 *outRx1Buf; 
extern u8 Tx1Buf[BUF1_LEN];
extern u8 Rx1Buf[BUF1_LEN]; 
                            

/*usart2*/
extern u8 volatile rcv_usart2_str_flag;
extern u8 volatile rcv_usart2_end_flag;					             
extern u8 volatile rcv_usart2_over_count;
extern u8          rcv_usart2_array[BUF2_LEN ];
extern u8 volatile rcv_usart2_data_flg;
extern u16 volatile rcv_usart2_data_len;

extern u8 *inTx2Buf;
extern u8 *outTx2Buf; 
extern u8 *inRx2Buf;
extern u8 *outRx2Buf; 
extern u8 Tx2Buf[BUF2_LEN];
extern u8 Rx2Buf[BUF2_LEN]; 
 
 	


/*Communication err flag*/

extern u8 volatile led_red_sel;
extern u8 volatile led_blue_sel;

#endif
