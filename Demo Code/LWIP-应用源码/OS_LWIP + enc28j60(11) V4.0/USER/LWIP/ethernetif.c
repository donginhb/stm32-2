/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/* lwIP includes. */
#include <string.h>
//#include "opt.h"
//#include "def.h"

//#include "pbuf.h"

//#include "stats.h"

/* FreeRTOS includes. */
//#include "FreeRTOS.h"
//#include "enc28j60.h"
//#include "config.h"
#include "err.h"
#include "netif.h"
#include "stm32f10x.h"
#include "etharp.h"
#include "enc28j60.h"
#include "mem.h"
#include "sys.h"

#include "..\..\Task.h"
#include "Timers.h"
#define ETH_RXBUFNB        4
#define ETH_TXBUFNB        2

uint8_t MACaddr[6];
//uint8_t Rx_Buff[ETH_RXBUFNB][1520],Tx_Buff[ETH_TXBUFNB][1520];/* Ethernet buffers */
//#define ADDRESS_MAC  {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}
//#define ADDRESS_IP	 {192, 168, 1, 11}
//#define ADDRESS_MASK {255, 255, 255, 0}
//#define ADDRESS_GATEWAY {192 ,168, 1, 1}

#define netifMTU							( 1500 )
#define netifINTERFACE_TASK_STACK_SIZE		( 350 )
#define netifGUARD_BLOCK_TIME				( 250 )
#define IFNAME0 'S'
#define IFNAME1 'T'

unsigned char Data_Buf[1520 *4 +1];
unsigned char Tx_Data_Buf[1500 *2 ];
/* lwIP definitions. */
struct ethernetif
{
	struct eth_addr *ethaddr;
};

/* Forward declarations. */
err_t  ethernetif_input(struct netif *netif);
static err_t ethernetif_output( struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr );
err_t ethernetif_init( struct netif *netif );


/*-----------------------------------------------------------*/
     //网卡初始化函数
static void low_level_init( struct netif *netif )
{
	/* set MAC hardware address length */
	netif->hwaddr_len = 6;

	/* set MAC hardware address */
	/* MAC地址 */
	netif->hwaddr[0] = MACaddr[0];
	netif->hwaddr[1] = MACaddr[1];
	netif->hwaddr[2] = MACaddr[2];
	netif->hwaddr[3] = MACaddr[3];
	netif->hwaddr[4] = MACaddr[4];
	netif->hwaddr[5] = MACaddr[5];

	/* maximum transfer unit */
	/* 最大传输单元 */
	netif->mtu = netifMTU;

	/* broadcast capability */
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

	/* Initialise the EMAC.  This routine contains code that polls status bits.  
	If the Ethernet cable is not plugged in then this can take a considerable 
	time.  To prevent this starving lower priority tasks of processing time we
	lower our priority prior to the call, then raise it back again once the
	initialisation is complete. */
	taskENTER_CRITICAL();
	enc28j60Init(netif->hwaddr);
    enc28j60PhyWrite(PHLCON, 0x476);
    enc28j60clkout(1); // change clkout from 6.25MHz to 12.5MHz
	taskEXIT_CRITICAL();

		/* Create the task that handles the EMAC. */
	//              任务入口函数           创建任务的名字           任务堆栈的长度            给任务的参数       优先级       句柄反馈使用任务的
	//xTaskCreate( ethernetif_input, ( signed char * ) "ETH_INT", 512,0, 4, NULL );
	//ethernetif_input( netif );
}		   
/*-----------------------------------------------------------*/

/*
 * low_level_output(): Should do the actual transmission of the packet. The 
 * packet is contained in the pbuf that is passed to the function. This pbuf 
 * might be chained.
 */
      //链路层发送函数

static err_t low_level_output( struct netif *netif, struct pbuf *p )
{                                                                   extern void enc28j60PacketSend(u16 len, u8* packet);
//static xSemaphoreHandle xTxSemaphore = NULL;
  struct pbuf *q;
  int l = 0;   
//  u8 *buffer = Data_Buf;
  err_t xReturn = ERR_OK;

  /* Parameter not used. */	
//  ( void ) netif;  
  
// if ( q->len > 1500 + 1) q->len = 1500 +1;                        

  for(q = p; q != NULL; q = q->next) 
  {
    memcpy(&Tx_Data_Buf[l], (u8_t*)q->payload, q->len); // ping -t 192.168.0.8
//	 memcpy(Tx_Data_Buf, q->payload, q->len); // ping 192.168.0.8

	 //	enc28j60PacketSend(p->tot_len,Tx_Data_Buf);
	                                      //	enc28j60PacketSend(p->len,q->payload);
//	 enc28j60PacketSend(q->len,&Tx_Data_Buf[l]);
   	l = l + q->len;
  }
    //pbuf_free(p);	 
 //	enc28j60PacketSend(p->tot_len,Tx_Data_Buf);
	// 	enc28j60PacketSend(p->len,Tx_Data_Buf);

	 //	enc28j60PacketSend(p->len,q->payload);
 enc28j60PacketSend(l,Tx_Data_Buf);
	/*
   	if( xTxSemaphore == NULL )
	{
		vSemaphoreCreateBinary( xTxSemaphore );
	} */

	 	/* Access to the EMAC is guarded using a semaphore. */
//	if( xSemaphoreTake( xTxSemaphore, netifGUARD_BLOCK_TIME ) )
	{	   

 //   xSemaphoreGive( xTxSemaphore );
	}

    return xReturn;
}
/*--------------------------------------------p---------------*/

/*
 * low_level_input(): Should allocate a pbuf and transfer the bytes of the 
 * incoming packet from the interface into the pbuf. 
 */

static struct pbuf *low_level_input( struct netif *netif )
{	                                                    //  u16 enc28j60PacketReceive(u16 maxlen, u8* packet);

struct pbuf *q,*p = NULL; u16 Len = 0;	 unsigned int Count;

  int l =0;
//static xSemaphoreHandle xRxSemaphore = NULL;

	/* Parameter not used. */
//	( void ) netif;
	/*
	if( xRxSemaphore == NULL )
	{
		vSemaphoreCreateBinary( xRxSemaphore );
	} */
	 	/* Access to the emac is guarded using a semaphore. */
 //  	if( xSemaphoreTake( xRxSemaphore, netifGUARD_BLOCK_TIME ) )
	{
		  	//  Len = enc28j60_getpacket(1500, (u8*)(&(p->payload)));	
			//  Len = enc28j60PacketReceive(1500, (u8*)(&(p->payload)));

				Len = enc28j60PacketReceive(1520 *4,  Data_Buf);		// ping 192.168.0.8

				if ( Len == 0 ) return 0;
GPIOD->ODR ^= 0x00000100;
			//	q->len = Len;
//printf("%d\ ",Len);			
				p = pbuf_alloc(PBUF_RAW, Len, PBUF_POOL);
					
				if (p != NULL) {

                    for (q = p; q != NULL; q = q->next) {

	                     memcpy((u8_t*)q->payload, (u8_t*)&Data_Buf[l], q->len);

                         l = l + q->len;
                    }
					if( l != p->tot_len ){ return 0;}
                }
	}
	return p;
}
/*-----------------------------------------------------------*/

/*
 * ethernetif_output(): This function is called by the TCP/IP stack when an 
 * IP packet should be sent. It calls the function called low_level_output() 
 * to do the actual transmission of the packet.
 */
static err_t ethernetif_output( struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr )
{
    /* resolve hardware address, then send (or queue) packet */
    return etharp_output( netif, p, ipaddr );
}
/*-----------------------------------------------------------*/

/*
 * ethernetif_input(): This function should be called when a packet is ready to 
 * be read from the interface. It uses the function low_level_input() that 
 * should handle the actual reception of bytes from the network interface.
 */
static void delay( unsigned int dly )
 {
  while ( dly --);
 }
//#define HTTP_HTML_HEADER
//#define NETCONN_COPY 0x01
//extern struct netif EMAC_if;

err_t  ethernetif_input(struct netif *netif)  //ping -l 500 192.168.0.8 -t
{  	
 err_t err = ERR_OK;		// struct netconn *conn;
 struct pbuf *p = NULL;

// netif = &EMAC_if; 

// p->tot_len = 0;
			
   /* move received packet into a new pbuf */
  p = low_level_input(netif);

  if (p == NULL) return ERR_MEM;

  err = netif->input(p, netif);
  if (err != ERR_OK)
  {
    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
    pbuf_free(p);
    p = NULL;
  }

  return err;
}
  /*

  if (err == ERR_OK ) {
  	printf("\033[1;44;32m%s\033[0m"," Hello,NSFocus\n");				   
      printf (" Call ip_input(); successful! \r\n ");  printf("0x0C");
  }
  else {
  
  	  printf (" Call ip_input(); fail! \r\n");
  }
  err =  ethernet_input( p , netif);  //etharp_arp_input

 if( err == ERR_OK ) {
 
	  printf (" Call etharp_arp_input(); successful! \r\n");
 }
 else {
 
	  printf (" Call etharp_arp_input(); fail! \r\n");
 }

// err = low_level_output( netif,p );
//	err = netif->output(netif, p, &netif->ip_addr);	 
// delay( 0x654321);	 GPIOD->ODR ^= 0x00000100;
  /* no packet could be read, silently ignore this */
//  if (p == NULL) { vTaskDelay(15);continue;}


//GPIOD->ODR = 0xFFFFFFFF;
//GPIO_SetBits(GPIOD,GPIO_Pin_8);	 

//  err = netif->input(p, netif);

//  netconn_write(conn, HTTP_HTML_HEADER,20, NETCONN_COPY);
//  if (err == ERR_OK)
 // {
//    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n\r"));
  //  pbuf_free(p);
  //  p = NULL;

//	err = netif->output(netif, p, &netif->ip_addr);
//  }	
// }
//     p = NULL; 
//}

   
static void arp_timer( void *arg )
{
	( void ) arg;

    etharp_tmr();
    sys_timeout( ARP_TMR_INTERVAL, arp_timer, NULL );
}
/*-----------------------------------------------------------*/

err_t ethernetif_init( struct netif *netif )
{
struct ethernetif   *ethernetif;

	ethernetif = mem_malloc( sizeof(struct ethernetif) );

	if( ethernetif == NULL )
	{
		LWIP_DEBUGF( NETIF_DEBUG, ("ethernetif_init: out of memory\n\r") );
		return ERR_MEM;
	}

	netif->state = ethernetif;
	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;
	netif->output = ethernetif_output;
	netif->linkoutput = low_level_output;

	ethernetif->ethaddr = ( struct eth_addr * ) &( netif->hwaddr[0] );

	low_level_init( netif );
	//etharp_init();

	return ERR_OK;
}
/*************************************************************************************************************
*
**************************************************************************************************************/
void Set_MAC_Address ( uint8_t* macadd )
{
     MACaddr[0] = macadd[0];
	  MACaddr[1] = macadd[1];
	   MACaddr[2] = macadd[2];
	    MACaddr[3] = macadd[3];
		 MACaddr[4] = macadd[4];
		  MACaddr[5] = macadd[5];
}
