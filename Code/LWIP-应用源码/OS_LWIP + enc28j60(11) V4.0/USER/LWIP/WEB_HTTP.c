#include "tcp.h"
#include "stm32f10x.h"
typedef unsigned char uint8;
#include "web_html.h"

#include "webpage.h"
/*********************************************************************************************************
  全局CONSTANTS 常量定义
*********************************************************************************************************/
/********************************TCP测试的WEB服务器建立网页与服务器声明**********************************/


const static uint8 http_BASIC_REALM[] = HTTP_WEB_BASIC_REALM;
const static uint8 http_html_hdr[] =  HTTP_HEAD;
const static uint8 indexdata[]= INDEX_DATA;
//const static uint8 indexdata[]= TABLE2;
//const static uint8 indexdata[]= TABLE;
/*********************************************************************************************************
  全局VARIABLES 变量定义
*********************************************************************************************************/

/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
void http_init(void);

/*********************************************************************************************************
** Function name:      main	   
** Descriptions:       系统主函数入口
** input parameters:   无
** output parameters:  无      
** Returned value:      0	 
** Created by:		   任海波
** Created Date:	   2008.8.28
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:         
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

/******* 这是一个回调函数，当一个TCP段到达这个连接时会被调用********/
//static unsigned char pcbDataBuf[1024];
  struct pbuf *q;
static err_t http_recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
{ 
  u8_t * ppayload = (u8_t*)p->payload; u16_t i =0; u8_t Flag = 1;  u8_t RES = 0;
static unsigned long TxCount = 0;;
//const static  u8_t Name[] ="yourname";
  if(p != NULL)
  {
    if( ppayload[0] == 'P' && ppayload[1] == 'O' &&
	    ppayload[2] == 'S' && ppayload[3] == 'T') {		

  	    printf( "%s\r\n",ppayload);		
     
/*
			do {
	 	     	 if( ppayload[i++] == 'y') {	  
			 
			          if( ppayload[i++] == 'o') { 

						   if( ppayload[i++] == 'u') { 

							   	if( ppayload[i++] == 'r') { 
								
								      if( ppayload[i++] == 'n') { 

										  if( ppayload[i++] == 'a') {

											  if( ppayload[i++] == 'm') {
											  
												  if( ppayload[i++] == 'e') {
												
				                                GPIOD->ODR ^= 0x00000400;

												printf("\r\n");
												do{
												   ppayload[i++];
												   printf("%c",ppayload[i]);

												}
												while(ppayload[i]!= '&');	printf("\r\n");
												   Flag = 0;
												  }
											  } 
										  }
									  }
								}      

						  }
				       }
			     }
			}
			while( Flag);*/		
	}
if( ppayload[0] == 'G' && ppayload[1] == 'E' && ppayload[2] == 'T') {

   printf( "%s\r\n",ppayload);

    if( ppayload[4]=='/' && ppayload[5] == '1') {
	
		RES = 1;
	}
	if ( RES) {
			 TxCount ++; printf("TxCount =%d\r\n",TxCount);
		tcp_write(pcb,WebSide,sizeof(WebSide),0);	// AD
	
	}
	else {
  														  
    tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* 发送http协议头部信息 */
  
    tcp_write(pcb,indexdata,sizeof(indexdata),0);              /* 发送http网页信息 */
	
   	  tcp_write(pcb,WebSide,sizeof(WebSide),0);	// AD

 //tcp_write(pcb,http_BASIC_REALM,sizeof(http_BASIC_REALM),0); //验证
    }
}
    pbuf_free(p);                                              /* 释放该TCP段 */

  }
  tcp_close(pcb);                                              /* 关闭这个连接 */
  err = ERR_OK;
  
  return err;
}

/******这是一个回调函数，当一个连接已经接受时会被调用******/
static err_t http_accept(void *arg,struct tcp_pcb *pcb,err_t err)
{
  tcp_setprio(pcb, TCP_PRIO_MIN);     /* 设置回调函数优先级，当存在几个连接时特别重要，此函数必须调用*/


  tcp_recv(pcb,http_recv);            /* 设置TCP段到时的回调函数 */
   
  err = ERR_OK;
  
  return err;
}
/*********************************************************************************************************
** Function name:           http_init	   
** Descriptions:            WEB服务器的初始化	
** input parameters:        无
** output parameters:       无      
** Returned value:          0	 
** Created by:		    任海波
** Created Date:	    2008.8.28
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:         
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void http_init(void)
{
  struct tcp_pcb *pcb;
  
  pcb = tcp_new();                           /* 建立通信的TCP控制块(pcb) */
  
  tcp_bind(pcb,IP_ADDR_ANY,5005);             /* 绑定本地IP地址和端口号 */
 
  pcb = tcp_listen(pcb);                    /* 进入监听状态 */
  
  tcp_accept(pcb,http_accept);             /* 设置有连接请求时的回调函数 */

} 

const static uint8 TCP_TestData[]="This is LwIP TCP Client 在Luminary Cortex-M3上的测试！\r\n";


/******* 这是一个回调函数，当TCP客户端请求的连接建立时被调用********/
err_t TcpCli_Connected(void *arg,struct tcp_pcb *pcb,err_t err)
{
   tcp_write(pcb,TCP_TestData,sizeof(TCP_TestData),0);      //发送数据
   
   tcp_close(pcb);
   
   return ERR_OK;
}

/*********************************************************************************************************
** Function name:           TCP_Client_Init	   
** Descriptions:            TCP客户端的初始化，当需要建立客户端连接时调用
** input parameters:        无
** output parameters:       无      
** Returned value:          0	 
** Created by:		    任海波
** Created Date:	    2008.10.9
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:         
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void TCP_Client_Init(void)
{
  struct tcp_pcb *Clipcb;
  struct ip_addr ipaddr;
  
  IP4_ADDR(&ipaddr,192,168,0,2);
  
  Clipcb = tcp_new();                       // 建立通信的TCP控制块(Clipcb) 
  
  tcp_bind(Clipcb,IP_ADDR_ANY,1026);       // 绑定本地IP地址和端口号 
  
  tcp_connect(Clipcb,&ipaddr,1026,TcpCli_Connected);
}


