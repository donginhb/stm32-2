/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 * Author: Guido Socher
 * Copyright: GPL V2
 * See http://www.gnu.org/licenses/gpl.html
 *
 * Ethernet remote device and sensor
 * UDP and HTTP interface 
        url looks like this http://baseurl/password/command
        or http://baseurl/password/
 *
 * Title: Microchip ENC28J60 Ethernet Interface Driver
 * Chip type           : ATMEGA88 with ENC28J60
 * Note: there is a version number in the text. Search for tuxgraphics
 *********************************************/


/*********************************************
 * modified: 2007-08-08
 * Author  : awake
 * Copyright: GPL V2
 * http://www.icdev.com.cn/?2213/
 * Host chip: ADUC7026
**********************************************/
//#include "..\main\include.h"
#include "MyType.h"
#include "net.h"
#include "stm32f10x_spi.h"
#include <string.h>
#include "config.h"
#include "enc28j60/ENC28J60.H"
#include "net/ip_arp_udp_tcp.h"

//struct pbuf * enc28j60_getpacket (struct netif *netif);
#define PSTR(s) s

//extern void delay_ms(u8 ms);

// please modify the following two lines. mac and ip have to be unique
// in your local area network. You can not have the same numbers in
// two devices:
static u8 mymac[6] =
{
   0x54, 0x55, 0x58, 0x10, 0x00, 0x24
};
static u8 myip[4] =
{
   192, 168, 0, 98
};
// base url (you can put a DNS name instead of an IP addr. if you have
// a DNS server (baseurl must end in "/"):
static char baseurl[] = "http://192.168.0.98/";
static u16 mywwwport = 80; // listen port for tcp/www (max range 1-254)
// or on a different port:
//static char baseurl[]="http://10.0.0.24:88/";
//static u16 mywwwport =88; // listen port for tcp/www (max range 1-254)
//
static u16 myudpport = 1200; // listen port for udp
// how did I get the mac addr? Translate the first 3 numbers into ascii is: TUX

#define BUFFER_SIZE 1500//400
static u8 buf[BUFFER_SIZE + 1];

// the password string (only the first 5 char checked), (only a-z,0-9,_ characters):
static char password[] = "888"; // must not be longer than 9 char


// 
u8 verify_password(char* str)
{
   // the first characters of the received string are
   // a simple password/cookie:
   if (strncmp(password, str, sizeof(password)-1) == 0)
   {
      return(1);
   }
   return(0);
}

// takes a string of the form password/commandNumber and analyse it
// return values: -1 invalid password, otherwise command number
//                -2 no command given but password valid
u8 analyse_get_url(char* str)
{
   u8 i = 0;
   if (verify_password(str) == 0)
   {
      return((u8)-1);
   }
   // find first "/"
   // passw not longer than 9 char:
   while (*str && i<10 && *str>',' && *str < '{')
   {
      if (*str == '/')
      {
         str++;
         break;
      }
      i++;
      str++;
   }
   if (*str <0x3a && *str> 0x2f)
   {
      // is a ASCII number, return it
      return(*str - 0x30);
   }
   return((u8)-2);
}

// prepare the webpage by writing the data to the tcp send buffer
u16 print_webpage(u8* buf, u8 on_off)
{
   u16 plen;
   plen = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
   plen = fill_tcp_data_p(buf, plen, PSTR("<center><p>LEDÊä³ö: "));
   if (on_off)
   {
      plen = fill_tcp_data_p(buf, plen, PSTR("<font color=\"#FF0000\"> ÁÁ</font>"));
   }
   else
   {
      plen = fill_tcp_data_p(buf, plen, PSTR("Ãð"));
   }
   plen = fill_tcp_data_p(buf, plen, PSTR(" <small><a href=\""));
   plen = fill_tcp_data(buf, plen, baseurl);
   plen = fill_tcp_data(buf, plen, password);
   plen = fill_tcp_data_p(buf, plen, PSTR("\">[Ë¢ÐÂ]</a></small></p>\n<p><a href=\""));
   // the url looks like this http://baseurl/password/command
   plen = fill_tcp_data(buf, plen, baseurl);
   plen = fill_tcp_data(buf, plen, password);
   if (on_off)
   {
      plen = fill_tcp_data_p(buf, plen, PSTR("/0\">¹Ø±ÕLED</a><p>"));
   }
   else
   {
      plen = fill_tcp_data_p(buf, plen, PSTR("/1\">¿ªÆôLED</a><p>"));
   }
   plen = fill_tcp_data_p(buf, plen, PSTR("»ðÅ£¿ª·¢°å WEB ÍøÒ³LEDÊÔÑé</a><p>"));
   //plen = fill_tcp_data_p(buf, plen, PSTR("</center><hr><br>»ðÅ£¿ª·¢°å WEB ÍøÒ³LEDÊÔÑé\n"));


   return(plen);
}
extern uint8_t MACaddr[6];
int simple_server(void)
{
   u16 plen;
   u16 dat_p;
   u8 i = 0;
   u8 cmd_pos = 0;
   u8 cmd;
   u8 payloadlen = 0;
   char str[30];
   char cmdval;


   // Del_1ms(100);
   /*initialize enc28j60*/
   enc28j60Init(mymac);
 //   enc28j60Init(MACaddr);
   str[0]=(char)enc28j60getrev();
   
 //  init_ip_arp_udp_tcp(MACaddr, myip, mywwwport);
   init_ip_arp_udp_tcp(mymac, myip, mywwwport);
   //Ö¸Ê¾µÆ×´Ì¬:0x476 is PHLCON LEDA(ÂÌ)=links status, LEDB(ºì)=receive/transmit
//   enc28j60PhyWrite(PHLCON, 0x7a4); 
   enc28j60PhyWrite(PHLCON, 0x476);
   enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
   // Del_1ms(20);

   //init the ethernet/ip layer:
 //  while (1)
 //  {
      //    OSTimeDlyHMSM(0, 0, 0, 50);
      // get the next new packet:
Start:
      plen = enc28j60PacketReceive(BUFFER_SIZE, buf);
      //USART_DMASendData(USART1,buf,plen);

      /*plen will ne unequal to zero if there is a valid packet (without crc error) */
      if (plen == 0)
      {
         goto Start;//continue;
      }
      // arp is broadcast if unknown but a host may also
      // verify the mac address by sending it to 
      // a unicast address.
      if (eth_type_is_arp_and_my_ip(buf, plen))
      {
         make_arp_answer_from_request(buf);
         //USART_DMASendText(USART1,"make_arp_answer_from_request\n");	 //ping 192.168.0.98
        goto Start; //continue;
      }

      // check if ip packets are for us:
      if (eth_type_is_ip_and_my_ip(buf, plen) == 0)
      {
        goto Start; //continue;
      }


      if (buf[IP_PROTO_P] == IP_PROTO_ICMP_V &&
         buf[ICMP_TYPE_P] == ICMP_TYPE_ECHOREQUEST_V)
      {
         // a ping packet, let's send pong	
         make_echo_reply_from_request(buf, plen);
         //USART_DMASendText(USART1,"make_echo_reply_from_request\n");
        goto Start;// continue;
      }
     
  // }
   //        return (0);
}
