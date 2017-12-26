
#include "lwip/tcp.h"


#include <string.h>

struct http_state
{
  char *file;
  u32_t left;
};
struct fs_file {
  char *data;
  int len;
};
static void
send_data(struct tcp_pcb *pcb, struct http_state *hs);
static void
close_conn(struct tcp_pcb *pcb, struct http_state *hs);

static void
close_conn(struct tcp_pcb *pcb, struct http_state *hs)
{

  tcp_arg(pcb, NULL);
  tcp_sent(pcb, NULL);
  tcp_recv(pcb, NULL);
  mem_free(hs);
  tcp_close(pcb);
}
static err_t
http_sent(void *arg, struct tcp_pcb *pcb, u16_t len)
{
  struct http_state *hs;

  hs = arg;

  if (hs->left > 0)
  {
    send_data(pcb, hs);
  }
  else
  {
    close_conn(pcb, hs);
  }

  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
static err_t
http_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
  int i, j;
  char *data;
  char fname[40];
  struct fs_file file = {0, 0};
  struct http_state *hs;

  hs = arg;

  if (err == ERR_OK && p != NULL)
  {

    /* Inform TCP that we have taken the data. */
    tcp_recved(pcb, p->tot_len);

    if (hs->file == NULL)
    {
      data = p->payload;
        
      if (strncmp(data, "GET /STM32F107ADC", 17) == 0)
      {
     

        pbuf_free(p);

        hs->file = file.data;
        hs->left = file.len;

        send_data(pcb, hs);

        /* Tell TCP that we wish be to informed of data that has been
           successfully sent by a call to the http_sent() function. */
        tcp_sent(pcb, http_sent);
      }
      else if (strncmp(data, "GET /method=get", 15) == 0)
      {        
        while(data[i]!=0x20/* */)
        {
          i++; 
          if (data[i] == 0x6C /* l */)
          {
            i++;
            if (data[i] ==  0x65 /* e */)
            {
              i++;
              if (data[i] ==  0x64 /* d*/)
              {
                i+=2; 
                if(data[i]==0x31 /* 1 */)
                {
                 // STM_EVAL_LEDOn(LED1);   
                }
  
                if(data[i]==0x32 /* 2 */)
                {
                 // STM_EVAL_LEDOn(LED2);   
                }
        
                if(data[i]==0x33 /* 3 */)
                {
                 // STM_EVAL_LEDOn(LED3);   
                }
            
                if(data[i]==0x34 /* 4 */)
                {
                 // STM_EVAL_LEDOn(LED4);  
                }
              }   
            }
          } 
        }

        pbuf_free(p);

        hs->file = file.data;
        hs->left = file.len;

        send_data(pcb, hs);

        /* Tell TCP that we wish be to informed of data that has been
           successfully sent by a call to the http_sent() function. */
        tcp_sent(pcb, http_sent);
      }    
      else if (strncmp(data, "GET ", 4) == 0)
      {
        for (i = 0; i < 40; i++)
        {
          if (((char *)data + 4)[i] == ' ' ||
              ((char *)data + 4)[i] == '\r' ||
              ((char *)data + 4)[i] == '\n')
          {
            ((char *)data + 4)[i] = 0;
          }
        }
        
        i = 0;
        j = 0;
        
        do
        {
          fname[i] = ((char *)data + 4)[j];
          j++;
          i++;
        } while (fname[i - 1] != 0 && i < 40);
        
        pbuf_free(p);

        hs->file = file.data;
        hs->left = file.len;

        send_data(pcb, hs);

        /* Tell TCP that we wish be to informed of data that has been
           successfully sent by a call to the http_sent() function. */
        tcp_sent(pcb, http_sent);
      }
      else
      {
        close_conn(pcb, hs);
      }
    }
    else
    {
      pbuf_free(p);
    }
  }

  if (err == ERR_OK && p == NULL)
  {

    close_conn(pcb, hs);
  }
  
  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
static void
send_data(struct tcp_pcb *pcb, struct http_state *hs)
{
  err_t err;
  u16_t len;

  /* We cannot send more data than space avaliable in the send
     buffer. */
  if (tcp_sndbuf(pcb) < hs->left)
  {
    len = tcp_sndbuf(pcb);
  }
  else
  {
    len = hs->left;
  }

  err = tcp_write(pcb, hs->file, len, 0);

  if (err == ERR_OK)
  {
    hs->file += len;
    hs->left -= len;
  }
}

/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
static void
conn_err(void *arg, err_t err)
{
  struct http_state *hs;

  hs = arg;
  mem_free(hs);
}
/*-----------------------------------------------------------------------------------*/
static err_t
http_poll(void *arg, struct tcp_pcb *pcb)
{
  if (arg == NULL)
  {
    /*    printf("Null, close\n");*/
    tcp_close(pcb);
  }
  else
  {
    send_data(pcb, (struct http_state *)arg);
  }

  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
static err_t
http_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
  struct http_state *hs;

  /* Allocate memory for the structure that holds the state of the
     connection. */
  hs = mem_malloc(sizeof(struct http_state));

  if (hs == NULL)
  {
    return ERR_MEM;
  }

  /* Initialize the structure. */
  hs->file = NULL;
  hs->left = 0;

  /* Tell TCP that this is the structure we wish to be passed for our
     callbacks. */
  tcp_arg(pcb, hs);

  /* Tell TCP that we wish to be informed of incoming data by a call
     to the http_recv() function. */
  tcp_recv(pcb, http_recv);

  tcp_err(pcb, conn_err);

  tcp_poll(pcb, http_poll, 10);
  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/

void
httpd_init(void)
{
  struct tcp_pcb *pcb;

  pcb = tcp_new();
  tcp_bind(pcb, IP_ADDR_ANY, 80);
  pcb = tcp_listen(pcb);
  tcp_accept(pcb, http_accept);
}
/********************************************************************************************************************************
*
*********************************************************************************************************************************/
 void my_udp_rx(void *arg, struct udp_pcb *upcb,

               struct pbuf *p, struct ip_addr *addr, u16_t port)

{

    /* process the payload in p->payload */

       unsigned char g_tData[200];

    udp_connect(upcb, addr, port);            /* connect to the remote host */

       if(p->len>=200) p->len=100;

              memcpy(g_tData,p->payload,p->len);

       if(p->next != NULL)

       {

       //     memcpy(g_tData+(p->len)/sizeof(unsigned short),p->next->payload,p->next->len);

       }                   

       udp_send(g_tData,p->len);

    pbuf_free(p);   /* don't leak the pbuf! */
}


const static char UDPData[]= "123456789ABCDEFG\r\n";//////////////////////怎样改成变量数组？ 
struct udp_pcb *
udp_new(void);

struct udp_pcb *UdpPcb; 
  struct ip_addr ipaddr;  struct ip_addr FARipaddr; 
  struct pbuf *p; 

void Test_UDP( void )
{ 
 err_t  Err_T;
  
  p = pbuf_alloc(PBUF_RAW,sizeof(UDPData),PBUF_RAM); 
   
  p->payload=(void *)UDPData; 
p->len = p->tot_len = sizeof(UDPData);      
//  IP4_ADDR(&ipaddr,192,168,0,8); 
   
UdpPcb = udp_new();
udp_bind(UdpPcb,IP_ADDR_ANY,1234);   /* 绑定本地IP地址 */ 

IP4_ADDR(&FARipaddr,192,168,0,2); 

  Err_T = udp_connect(UdpPcb,&FARipaddr,1234);    /* 连接远程主机 */ 

  if ( Err_T == 0) {

      printf("udp_connect Sucessful!\r\n ");
  
  }
  udp_recv(UdpPcb, &my_udp_rx, (void *)0);
}

void UDP_send( void )
{
err_t  Err_T; 

 p->len = p->tot_len = sizeof(UDPData); 

p->tot_len -= 1;
 p->len = p->tot_len;

  Err_T =  udp_send(UdpPcb,p); 

  if( Err_T != 0) {
  
      printf(" udp_send  Fail!");
  }
}
/***********************************************************************************/
/******* 这是一个回调函数，当有UDP数据收到时会被调用********/
void UDP_Receive(void *arg, struct udp_pcb *upcb, struct pbuf *p,
                 struct ip_addr *addr, u16_t port)
{
  struct ip_addr destAddr = *addr;
  if(p != NULL)                          /* 如果收到的数据不为空   */             
  {
    udp_sendto(upcb,p,&destAddr,port);                    /* 将收到的数据再发送出去 */            
    
    pbuf_free(p);                       /* 释放缓冲区数据 */
  }
}
/*********************************************************************************************************
** Function name:           UDP_Test	   
** Descriptions:            UDP服务器通信的初始化	
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
void UDP_Test_Init(void)
{
  struct udp_pcb *UdpPcb;
  //struct ip_addr ipaddr;
  
  //IP4_ADDR(&ipaddr,192,168,1,16);
  
  UdpPcb = udp_new();
  
  udp_bind(UdpPcb,IP_ADDR_ANY,1025);   /* 绑定本地IP地址 */
  
 // udp_connect(UdpPcb,&ipaddr,1025);    /* 连接远程主机 */
  
  udp_recv(UdpPcb,UDP_Receive,NULL);   /* 设置数据接收时的回调函数*/
  
}
