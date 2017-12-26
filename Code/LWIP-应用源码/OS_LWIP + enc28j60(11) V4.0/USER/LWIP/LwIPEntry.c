#include "etharp.h"
#include "LwIPConfig.H"
#include "tcpip.h"

#include "api.h"
#include "err.h"
#include "tcp.h"
#include "stm32f10x.h"
#include "udp.h"
//#include "tcpip.h"

struct netif EMAC_if;

typedef unsigned char uint8;
/*********************************************************************************************************
  全局CONSTANTS 常量定义
*********************************************************************************************************/

/************************************************************************************************************************
*
**************************************************************************************************************************/
void dhcp_start(struct netif *netif);  void Set_MAC_Address(uint8_t*);
err_t ethernetif_init( struct netif *netif ); void memp_init(void);	
struct netif netif;

void LwIP_Init( void )
{
  struct ip_addr ipaddr;
  struct ip_addr netmask;
  struct ip_addr gw;
  uint8_t macaddress[6]={0,0,0,0,0,1};

  /* Initializes the dynamic memory heap defined by MEM_SIZE.*/
 // mem_init();

  /* Initializes the memory pools defined by MEMP_NUM_x.*/
 // memp_init(); 

   lwip_init();
//	tcp_init();
	  
#if LWIP_DHCP
  ipaddr.addr = 0;
  netmask.addr = 0;
  gw.addr = 0; 
#else
  IP4_ADDR(&ipaddr, 192, 168, 1, 8);
  IP4_ADDR(&netmask, 255, 255, 255, 0);
  IP4_ADDR(&gw, 192, 168, 1, 1);
//  IP4_ADDR(&ipaddr, 202, 197, 243, 179);
//  IP4_ADDR(&netmask, 255, 255, 255, 192);
//  IP4_ADDR(&gw, 202, 197, 243, 129);
#endif


  Set_MAC_Address(macaddress);

  netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);
 // netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ip_input);
  /*  Registers the default network interface.*/
  netif_set_default(&netif);


#if LWIP_DHCP
  /*  Creates a new DHCP client for this interface on the first call.
  Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
  the predefined regular intervals after starting the client.
  You can peek in the netif->dhcp struct for the actual DHCP status.*/
  dhcp_start(&netif);
#endif

  /*  When the netif is fully configured this function must be called.*/
  netif_set_up(&netif);
}
