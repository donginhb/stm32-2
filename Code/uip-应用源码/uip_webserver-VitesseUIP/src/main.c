/*****************************************************************************************************
 @project name: cosmos
 @system:       nOS with uIP1.0	
 @funcation: 	TCP/IPתRS485  socket=10
 @bug:          jerkoh@163.com
 @date:         2013-02
     stress tests: 
                   ���Ի���: ����1~25��C
                   ���ػ�: ATOM D425��2G�ڴ�
			       USB����: RD9700 USB2.0 To Fast Ethernet Adapter  
			       ������: Mercury-S108M
			       ��������MDK-4.12
	
                   Tcp/ip client ÿ1ms ����32Kbytes,server����32Kbytes���� (����2��Tcp client
                   ͬʱ����)������2��icmp echo,1��webserverÿ1s ˢ��һ��,
			       �������ϵ����5��,��������������ϵͳ���������������client��ʱ��������server
			       (ע������Mss��RAM���⡢����ÿ1ms�շ�32Kbytes���ݱض��ж�������,����Ӱ��ѹ��
			       ����) 

      disclaimer��
			       ����Э��ջ�����������ļ�����Դ������.
			       Ӧ��APP�������Դ,Ӧ��APP������ڲ���������ͬ��������������ҵ�����ҵ��
			       Ŀ�ĵ�Ӧ�ã�������Ӧ�����漰�������Ʋ���ȫ�Ĺ���,��ҽ�ơ����¡����յ���Ŀ,
				   �κ���ʹ��cosmos������ɵĲ������,���߲��е��κη�������
 ----------------------------------------------------------------------------------------------------
 logs: alpha=V0.x  beta=V1.x  Release>=V2.0	  	 ������صĵ��Ժ�������global.h  ***debug define***
 ----------------------------------------------------------------------------------------------------
 V2.0  2013-xx-xx  Release                    
 ----------------------------------------------------------------------------------------------------
 V1.f  2013-xx-xx                     
 ----------------------------------------------------------------------------------------------------
 V1.e  2013-03-14  ���������еı���������(����warning=<unspecified> ��level0(-o0))
                   �����˲���debug�����Ϣ
				   ������UIP_STATIC_IP_ADDR�궨����þ�̬IP��̬DHCP                     
 ----------------------------------------------------------------------------------------------------
 V1.d  2013-03-13  ������uip1.0��DHCP����,���Գɹ�
                   ע������޸�enc28j60�ĳ�ʼ�����չ㲥���ܼĴ���ERXFCON_BCEN                     
 ----------------------------------------------------------------------------------------------------
 V1.c  2013-03-11  ������uip_main��elseif �ж��������⣬�����V1.b��Bug                   
 ----------------------------------------------------------------------------------------------------
 V1.b  2013-03-11  ʵ���˶��(10��)client���ӵ�server keepalive����
                   #define UIP_CONF_MAX_CONNECTIONS 10
                   #define UIP_CONF_MAX_LISTENPORTS 10
				   if((socket_keepalive[i].uip_kpl_type==SOCKET_COMM_OFF)&&
				   ((uip_conn->rport==socket_keepalive[i].uip_kpl_rport)))
				   ���ڵ�©���� ĳ��clientһֱ��ͣ�ط����ݸ�uIPջ,uIP��һֱnewdata��Ǵ���
				   �޻�����벢��⵽uip_poll���keepalive������Ҫ�ͷŵ�client                 
 ----------------------------------------------------------------------------------------------------
 V1.a  2013-03-09  ȡ��webserver���й���,ע��80�ڵļ���
                   ɾ����STM32�¶Ⱥ���
                   #define UIP_CONF_MAX_CONNECTIONS 1
                   #define UIP_CONF_MAX_LISTENPORTS 1                     
 ----------------------------------------------------------------------------------------------------
 V1.9  2013-03-08  ��������0,1��len u8�ĳ�u16   
                   ���ڻ����С����С��1500���ĳ�1200����ֹ�ڴ�copy�����hardfault����                
 ----------------------------------------------------------------------------------------------------
 V1.8  2013-03-05  ������T2��ʱ�� 1ms��1.1ms��BUG (ETTG ��������)                  
 ----------------------------------------------------------------------------------------------------
 V1.7  2013-03-04  �����˲������ƶ���
                   ʵ����TCP Serverģʽ��keepalivetime����,Socket�������10��
				   keepalive ��Զ�̿ͻ����½����Ӻ󡢻���ͨ�Ź�һ�κ󳬹����õı���ʱ��
				   ���������Զ��Ͽ��ͷŸÿͻ���(ֻ�ܿ�һ��socket��ģʽ��Ч
				   #define UIP_CONF_MAX_CONNECTIONS 1) �����޷�ȷ���ĸ�client������uip
				   _abort()����Ͽ�client
 ----------------------------------------------------------------------------------------------------
 V1.6  2013-03-03  ������web�����ݷ���״̬Ǩ�Ʊ���(html_status δ�궨��ʵ��)
				   webserver���ڸ��ʽϵ͵��Զ�ˢ�´���
				   POST����δ����
				   ����Ұ��Ƕ��ʽ�����ҵ�STM32�ڲ��¶�ֵ�������
 ----------------------------------------------------------------------------------------------------
 V1.5  2013-03-02  main.c δ���д��������鵵
                   RAM �ܼ�20K
                   ����10K��RAM����UART1&2,�����궨��ֵ�����޸�UART�Ļ����շ�����
				   ���ͷŴ����ڴ湩�û�����ʹ��
                   ����STM32 ����Ӳ����,ʵ����main��0,��ʱ�����
				   Ӳ����ʱ����0,��֤��mainĳ����ѭ���������붨ʱ��
				   ���߶�ʱ�������С�main����������¶����Խ���ϵͳ��λ
                   ����������δ����,�����ľ��涼δ����
				   TCP Serverģʽ��keepalive�����Ͽ���ʱ��client����δ����(������BUG)
				   uip1.0Э��ջ����Ϣ��ӡδ�궨�嵽usart1 
				   ����1��USART1 CMD��TCP CLINET����: ~Cosmos Restart~ =ϵͳ��λ
				   (�ɹ�����TCP���Ӳ������շ����������Ч)     
 ----------------------------------------------------------------------------------------------------
 V1.4  2013-03-01  ������һ���򵥵�webserver����,����ReplaceStr��������ǿ��˵��
                   caNewString[1024];����ȫ��	
                   ���ڲ���HTML�Ķ�̬�����޸�
				   ������MAC��ַ��*Ψһ*���㷨(ע�Ⲣ��100%Ψһ,������������дMAC)
				   ����web��ϵͳ��������ʱ��(����ȷ?)
 ----------------------------------------------------------------------------------------------------
 V1.3  2013-02-26  uIP1.0�ں��޸ģ�UIP_TIMER����µĴ���
                   ԭ��0.5sһ�θĳ�10msһ�κ�,uIP��Ӧ����ҲҪ����50��
                    static u8_t uip_reasstmr;      �ĳ� static u16_t uip_reasstmr;
                   (ԭ��u8_t<=255,ϵͳ��Ҫ40*50��ֵ���Ըĳ�u16_t)
				   #define UIP_REASS_MAXAGE 40    �ĳ� #define UIP_REASS_MAXAGE 40*50
				   ������V1.1 timer_expired(&periodic_timer)����������
				   �����˰汾�Ŀɱ�������DEBUG���
 ----------------------------------------------------------------------------------------------------
 V1.2  2013-02-26  ͨ���ײ�enc28j60 send����������V1.0�汾��enc28j60��������
                   (1ms�ͻ��˷���������,����������lookback����,ͬʱ����icmp
				   ͨ�����׵���EIR_TXERIF����ķ���)
				   �������ݵ�ͨ��ʱ,ICMP��ʧ�ʽϸ�
 ----------------------------------------------------------------------------------------------------
 V1.1  2013-02-25  �޸�timer_expired(&periodic_timer) ԭ��500msִ��һ��
                   �ָĳ�500/50 msһ��ִ��һ�� Ŀ����Ϊ�˿ͻ��������������̵ȴ�ʱ��
				   ��uip���ں���Ӧ����ʱ��Ҳ��500ms���10msһ������,ע��ARP�ϻ�����
				   δ�仹��10sһ��
				   Uip_Appcall(����rport�ı�������),��keepaliveʹ��,��connected��ʱ��
				   �޷�����conn�ľ���rport����connֵ,����uIP1.0�����ʺ���server������
				   ����һЩ�������ϴ����ݲ���.
 ----------------------------------------------------------------------------------------------------
 V1.0  2013-02-23  �����˲��ִ���Ķ��壬beta�汾V1.0
                   ʵ���˳�ʱ��������ݵ�TCP->RS485���͹���,����10GB�����޴���
				   δʵ��TCP Server��conn�� keepalive����(socket �����ɹ�
				   ���Ӻ���ָ��ʱ����δ�����շ�����,�����������ر�Socket
				   Ŀ��,��ֹclient�˴�������Ӻ�,���������ݽ���,���ķ�һ����Դ)
				   ��ʵ����RJ45�ĶϿ����,��δ����socket�������ر�
				   δʵ��ʵʱ�Ľ�RS485�ڽ����ݷ��͵�TCP Socket(���н�����
				   socket�������һ��ͨ�ŵ�socket)
				   enc28j60 EIR_TXERIF����δ���,����ʼ��enc28j60��ʱ���
				   ���socket clientͬʱ����tcp/ip���ݽ���,uIP1.0��������ͨ��
				   ���׶�ʧ��
				   1ms�ͻ��˷���������,����������lookback����,ͬʱ����icmpͨ��
				   ���׵���EIR_TXERIF����ķ���
				   ����Beta Release �汾�����ӹ��ܰ������¹���:
				   01.WebServer  02.tcp client 03.udp server 04.udp client
				   05.keepalive  06.udp broadcast search 07.flash save 08.dhcp      
				   09.telnet     10.tftp upgrade  11.Change the baud rate
 ----------------------------------------------------------------------------------------------------
 V0.5  ------V0.F  null 
 ----------------------------------------------------------------------------------------------------
 V0.4  2013-02-23  ����limit retrieve length   len-1�Ĵ���ᵼ��mss=1446ʱ�ְ�
				   536,@enc28j60PacketReceive
				   �ײ���������ȫ���������
 ----------------------------------------------------------------------------------------------------
 V0.3  2013-02-22  ����Enc28j60_EREVID����Ϣ���,�ر�ENC28J60��ʼ���ж�ʹ��
                   ����BUG pc�����ݰ�1ms���͸�Enc28j60,����OK,��ENC28J60
				   �ײ㷢�ͺ�������BUG. 
				   ������1.ECON1_TXRTS�ĳ�ECON1_TXRST,������Ȼ����
 ----------------------------------------------------------------------------------------------------
 V0.2  2013-02-21  ���uIP1.0����ֲ,enc28j60�ײ�������ICMP =:)
                   Debug����1��� =:)
 ----------------------------------------------------------------------------------------------------
 V0.1  2013-02-20  ��������ֲ���� alpha�汾V0.1	
                   T410 Intel(R) 82577LM Gigabit Network Connection
				   ʹ�ý����߿���ENC28J60���� ping

                   �ο���ֲ������Ӳ����Դ��Դ����;�������£�
                   (1)uIP1.0 Adam Dunkels adam@dunkels.com
				   (2)GPL V2 Guido Socher
				   (3)(C)COPYRIGHT 2011 Ұ��Ƕ��ʽ����������
				   (4)STMicroelectronics.
				   (5)Microchip TCP/IP
				   (6)j60 code+protues v1 
 ----------------------------------------------------------------------------------------------------
 V0.0  2013-02-18  ȷ��ʹ�õ�Ӳ���忪���� ��Դ��
                   http://item.taobao.com/item.htm?spm=a230r.1.14.21.KC10xP&id=21403012589
 ----------------------------------------------------------------------------------------------------                  
****************************************************************************************************/

/*! \file stm-tcp main.c
 *	\brief the main function.
 */

#include "global.h"
#include "stdio.h"



char Vxy[]="beta v1.e";											   //�ı�Beta V1.x���ɸı�Debug����Ĵ�ӡ��Ϣ
char fw_version[]="[system info]:firmware =~VvEeRrSsIiOoNn~ \r\n"; //ע��~VvEeRrSsIiOoNn~ʵ���Ǳ����ַ�
                                                                   //����Vxy[],Ӧ��string�����滻���ܵĺ���
																   //Ŀ�Ľ�����ReplaceStr����,��ʵ������

unsigned char  lasted_compiled_system_date[]="" __DATE__;	       //����������
unsigned char  lasted_compiled_system_time[]="" __TIME__;	       //������ʱ��



struct timer periodic_timer, arp_timer;

struct uip_tcp_socket_keepalive {
  unsigned int  uip_kpl_rport;
  unsigned int  uip_kpl_time;
  unsigned int  uip_kpl_type;
};
struct 	uip_tcp_socket_keepalive socket_keepalive[UIP_CONNS];      //���屣�ʱ��

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

#ifndef NULL
#define NULL (void *)0
#endif /* NULL */

                                                                   //http://standards.ieee.org/develop/regauth/oui/public.html     Search for:00-11-22
unsigned char  mymac[6]={0x00,0x11,0x22,0x33,0x44,0x55};           //0x00 0x11 0x22= CIMSYS Inc  MAC�̶����̺�, 0x33,0x44,0x55ʹ��STM32��*Ψһ*ID����ó�
unsigned char  myip[4] ={192,168,1,8};
unsigned char  mysm[4]={255,255,255,0};
unsigned char  mygw[4]={192,168,1,1};
unsigned int   myserverport =5005;	
#define  TCP_KEEPALIVE_TIME			10                             //TCP������ģʽ�¶Կͻ��˵ĳ�ʱ��� Ĭ��60s


//--------------TCP/IP ״̬Ǩ�Ʊ��----------------------------------------------------------------------------------------------------------------------------------------
unsigned char __IO  uip_poll_ack_static  =0;          //CLINET��SERVER������ͨ��״̬���,�ϵ�Ĭ��ֵΪ0=�ͻ��˴��� �Ͽ����߱��ر���

#define   CLINT_ACKED_CLOSED             0			 //��������Ϊ:�ͻ��˴���,�Ͽ����߱��ر���״̬
#define   CLINT_ACKED_SYNACK             1			 //��������Ϊ:�ͻ��˷���SYN���������ӦSYN+ACK��������ACKED״̬
#define   SERVER_ACTIVE_SEND             2 			 //��������Ϊ:�ͻ����״����ӳɹ���״̬��,����clientû�����ݹ���, ������������ͻ��˷������ݺ�״̬
#define   CLINT_NEWDAT_ACKED_CARRY       3           //��������Ϊ:�ͻ��˷��������ݸ��������󣬷���������NEWDATA״̬,����������PSH+ACKģʽ�����������Ӵ����͵�client
#define   CLINT_ACKED_CARRY              4           //��������Ϊ:�ͻ���ACKED��EWDATAģʽ���Դ��ķ���������(CARRYģʽ������)
#define   CLINT_ACKED_NORMAL             5           //��������Ϊ:һֱ�ڷ�����������->�ͻ���ACKED->������������->�ͻ���ACKEDģʽ  ����ѭ��ģʽ,��δ����NEWDATA״̬�µ��Դ� 
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void Init_Enc28j60_Chip(void);
void loop_process_tcpip(void);
void loop_process_uart1(void);
void loop_process_uart2(void);
void loop_feed_softdog(void);
void Init_uip(void);

void uip_main(void);
void sys_time_poll(void);
void sys_time_nms(void);
void Get_SerialNum(void);

/*! \ Get_SerialNum
 *
 */
void Get_SerialNum(void) 
{ 
  u32 Device_Serial0, Device_Serial1, Device_Serial2;   
  Device_Serial0 = *(vu32*)(0x1FFFF7E8); 
  Device_Serial1 = *(vu32*)(0x1FFFF7EC); 
  Device_Serial2 = *(vu32*)(0x1FFFF7F0);
  mymac[3]=(u8 )(Device_Serial0>>1);
  mymac[4]=(u8 )(Device_Serial1>>2);
  mymac[5]=(u8 )(Device_Serial2>>3);    	   /*MAC���3�ֽ�����STM��ΨһID���㣬�ر�ע��˷������ܴ����ظ�����Ҫ����Ӧ��������������MAC��Ψһ��*/
}


/*! \loop_feed_softdog
 *
 */
void loop_feed_softdog(void)
{
  Sys_Dog_Count=0;			    //ι��
}
/*! \brief led flash in a quite mode for a while when power up.
 *
 */
void LedPwrUp(void) {
    u8 s =0;
    for(s=0; s<20; s++) {		//flash in short time when power in
        LED_Green_FLASH();
        delay_ms(30);
    }
}



/*! \brief the application main.c
 *
 */
int main(void)
{
    unsigned char i;
	Sys_Dog_start=0;
    led_red_sel = 1;

	Get_SerialNum();//ȡMAC*Ψһ*ֵ
    Platform_Init();
	
	if(CPU_DEBUG) USART1_Put_String("[system info]:/******************************************************* \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:Ƕ��ʽTCP/IP����Ⱥ(ETTG) QQ:28221007 (C)2006-2013\r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:project name: cosmos\r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:stm32f103cbt6+enc28j60+uIP1.0+usart1+usart2 \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:tcp/ip server mode<=>rs485 \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:usart1=115200bps 8/n/1 \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:usart2=115200bps 8/n/1 \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:created date=Feb 20 2013 by gjk \r\n");
    if(CPU_DEBUG) USART1_Put_String("[system info]:lasted compiled_date=");
	if(CPU_DEBUG) USART1_Put_String(lasted_compiled_system_date);
	if(CPU_DEBUG) USART1_Put_String("\r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:lasted compiled_time=");
	if(CPU_DEBUG) USART1_Put_String(lasted_compiled_system_time);
	if(CPU_DEBUG) USART1_Put_String("\r\n");
	ReplaceStr(fw_version,"~VvEeRrSsIiOoNn~",Vxy);	
	if(CPU_DEBUG) USART1_Put_String((unsigned char *)fw_version);
	if(CPU_DEBUG) USART1_Put_String("[system info]:Platform_Init()= OK \r\n");
    LedPwrUp();
	if(CPU_DEBUG) USART1_Put_String("[system info]:LedPwrUp()= OK \r\n");
	SPI_Enc28j60_Init();
	if(CPU_DEBUG) USART1_Put_String("[system info]:SPI_Enc28j60_Init()= OK \r\n");
	Init_Enc28j60_Chip();
	if(CPU_DEBUG) USART1_Put_String("[system info]:Init_Enc28j60_Chip()= OK \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:Enc28j60_EREVID = ");
	if(CPU_DEBUG) Hex2HexStr(enc28j60getrev());
    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
	if(CPU_DEBUG) USART1_Put_String(" (B1=02,B4=04,B5=05,B7=06) \r\n");
	Init_uip();
	if(CPU_DEBUG) USART1_Put_String("[system info]:Init_uip()= OK \r\n");

	if(CPU_DEBUG) USART1_Put_String("[system info]:->");
    if(CPU_DEBUG)
	{
	   for(i=0;i<10;i++)
	   {
	     Hex2HexStr(9-i);
	     if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		 if(CPU_DEBUG) USART1_Put_String("->");
	     delay_ms(200);
	   }
	}
	if(CPU_DEBUG) USART1_Put_String("\r\n");
	Sys_Dog_start=1;
	if(CPU_DEBUG) USART1_Put_String("[system info]:Sys_Dog_start  = OK \r\n");
	if(CPU_DOG) IWDG_Configuration(781); /*5s*/
	if(CPU_DEBUG) USART1_Put_String("[system info]:IWDG_Configuration = OK \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:System Running = OK \r\n");
#ifdef UIP_STATIC_IP_ADDR 
	{
	  if(CPU_DEBUG) USART1_Put_String("[system info]::) \r\n");
	  if(CPU_DEBUG) USART1_Put_String("[system info]:********************************************************/ \r\n");
	}
#endif
    while(1)
    {
	  loop_feed_softdog();
	  loop_process_tcpip();
    loop_process_uart1();
	  loop_process_uart2(); 
    }
	
}
/*! \ loop_process_tcpip
 *
 */
void loop_process_tcpip(void)
{
       static unsigned long addlen;


	   /*task 1*/
       if(enc28j60_mac_is_linked()==0)	   /*��ѯ����״̬*/
	   {
	    if(((++addlen)%10000)==0)
	    {
	      if(CPU_DEBUG) USART1_Put_String("[system info]:enc28j60_mac_is_linked()=:( [RJ45 Disconnect] \r\n");
	    }
	   }
	   /*task 2*/
	   if( (enc28j60Read(EIR) & EIR_TXERIF) )
       {
	      if(CPU_DEBUG) USART1_Put_String("[system info]:enc28j60Read(EIR) & EIR_TXERIF=:( [Error->Init_Enc28j60_Chip()] \r\n");
	      Init_Enc28j60_Chip();		 //enc28j60оƬbug,���������Ľ��շ��������,���Խ��յ�	
		                             //EIR_TXERIF��Զ�޷��ָ�һֱ����������ײ��ʼ��enc28j60
									 //ע��:�����⾭���޸�enc28j60�ײ�ķ��ͺ�����,����һֱ����,���Է���һ,���鲻ע��
       }
	   /*task 3*/
	   uip_main();
	   /*task 4*/
	   sys_time_poll();
	   /*task 5*/
	 
}
/*! \ sys_time_poll
 *
 */

void web_timer_1(void);

void sys_time_poll(void)
{

     unsigned int i=0;
     if(time_1000ms==1)
	 {
	    time_1000ms=0;
		   web_timer_1();
	     for(i=0;i<UIP_CONNS;i++)
		 {
		   if((socket_keepalive[i].uip_kpl_time>0)&&(socket_keepalive[i].uip_kpl_rport!=0))
		   {
			   socket_keepalive[i].uip_kpl_time--;
			   if(socket_keepalive[i].uip_kpl_time==0)	//ƥ��һ��
			   { 
                     if(1)
					 {
						socket_keepalive[i].uip_kpl_rport=socket_keepalive[i].uip_kpl_rport;   //������0��Ҫ��uip_appcall������ʹ��,���+-0.5s
						socket_keepalive[i].uip_kpl_type=0;   
						socket_keepalive[i].uip_kpl_time=0;
						socket_keepalive[i].uip_kpl_type=SOCKET_COMM_OFF; //keepalive��Ҫ�ر�socket  
						if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
						if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
						if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==0  :) \r\n");
					 } 
               }
           }			 			   
		 }
	}
	
}
/*! \ Uip_Poll
 *
 */
void uip_main(void)
{
   	  int i; 
     //u16 datlen = 0;				//the variable for the array data's length
	  uip_len = etherdev_read();
      if(uip_len > 0)
      {
          if(BUF->type == htons(UIP_ETHTYPE_IP)) 
          {
        	  uip_arp_ipin();
        	  uip_input();
        	  /* If the above function invocation resulted in data that
        	     should be sent out on the network, the global variable
        	     uip_len is set to a value > 0. */
          	  if(uip_len > 0) 
              {
        	     uip_arp_out();
        	     etherdev_send();
        	  }
          } 
          else if(BUF->type == htons(UIP_ETHTYPE_ARP)) 
		  {
    	      uip_arp_arpin();
    	      /* If the above function invocation resulted in data that
    	         should be sent out on the network, the global variable
    	         uip_len is set to a value > 0. */
        	  if(uip_len > 0) 
              {
        	     etherdev_send();
        	  }
          }
      }
      if(timer_expired(&periodic_timer)) 
      {
			
            timer_reset(&periodic_timer);
			if(CPU_DEBUG_TIMER) USART1_Put_String("timer_expired=periodic_timer\r\n");
            for(i = 0; i < UIP_CONNS; i++) 
            {
            	uip_periodic(i);
            	/* If the above function invocation resulted in data that
        	   should be sent out on the network, the global variable
        	   uip_len is set to a value > 0. */

            	if(uip_len > 0)
                {
            	   uip_arp_out();
            	   etherdev_send();
        	    }
            }

             #if UIP_UDP
              for(i = 0; i < UIP_UDP_CONNS; i++) 
              {
        	      uip_udp_periodic(i);
        	     /* If the above function invocation resulted in data that
        	     should be sent out on the network, the global variable
        	     uip_len is set to a value > 0. */

        	     if(uip_len > 0) 
                 {
                	  uip_arp_out();
                	  etherdev_send();
            	 }
              }
              #endif /* UIP_UDP */
              
              /* Call the ARP timer function every 10 seconds. */
              if(timer_expired(&arp_timer)) 
              {
            	  timer_reset(&arp_timer);
            	  uip_arp_timer();
				  if(CPU_DEBUG_TIMER) USART1_Put_String("timer_expired=arp_timer\r\n");
              }
      }

}
/*! \ loop_uart1
 *
 */
void loop_process_uart1(void)
{
        u16 datlen = 0;					  //the variable for the array data's length
        if(rcv_usart1_end_flag)				  //Timer counts 6ms, then, usart1_end_flag turns high
        {
            datlen = Rcv_Usart1_To_Array();	  //get data from the buffer
			if(datlen>0)
			{
			   rcv_usart1_data_flg = 1;
			   rcv_usart1_data_len = datlen;
			}
            rcv_usart1_end_flag = 0;
        }
}
/*! \ loop_uart2
 *
 */
void loop_process_uart2(void)
{
        u16 datlen = 0;					  //the variable for the array data's length
        if(rcv_usart2_end_flag)				  //Timer counts 6ms, then, usart1_end_flag turns high
        {
            datlen = Rcv_Usart2_To_Array();	  //get data from the buffer
			if(datlen>0)
			{
			   //������2���͹���������
			   //�����Դ���Ӳ��δ������
			   USART2_Put_Data(rcv_usart2_array,datlen);
			}
            rcv_usart2_end_flag = 0;
        }
}
/*! \ Init_Enc28j60_Chip
 *
 */
void Init_Enc28j60_Chip(void)
{
    enc28j60Init(mymac);  
}
/*! \ Init_uip
 *
 */
void Init_uip(void)
{  
   uip_ipaddr_t ipaddr;
#ifdef UIP_STATIC_IP_ADDR
   u8 i=0;
#endif
   static struct uip_eth_addr sTempAddr;

   uip_init();

#ifndef UIP_STATIC_IP_ADDR
	  sTempAddr.addr[0] = mymac[0];
      sTempAddr.addr[1] = mymac[1];
      sTempAddr.addr[2] = mymac[2];
      sTempAddr.addr[3] = mymac[3];
      sTempAddr.addr[4] = mymac[4];
      sTempAddr.addr[5] = mymac[5];
      uip_setethaddr(sTempAddr);

	  uip_ipaddr(ipaddr, 0, 0, 0, 0);
      uip_sethostaddr(ipaddr);
      uip_ipaddr(ipaddr, 0, 0, 0, 0);
      uip_setnetmask(ipaddr);
	  dhcpc_init(&sTempAddr.addr[0], 6);
      dhcpc_request();
	  if(CPU_DEBUG) USART1_Put_String("[system info]:dhcpc_request() Please wait a few seconds\r\n");
#endif


#ifdef UIP_STATIC_IP_ADDR
   sTempAddr.addr[0] = mymac[0];
   sTempAddr.addr[1] = mymac[1];
   sTempAddr.addr[2] = mymac[2];
   sTempAddr.addr[3] = mymac[3];
   sTempAddr.addr[4] = mymac[4];
   sTempAddr.addr[5] = mymac[5];
   uip_setethaddr(sTempAddr);

   uip_ipaddr(ipaddr, myip[0], myip[1], myip[2], myip[3]); //����Ip
   uip_sethostaddr(ipaddr);
   uip_ipaddr(ipaddr, mygw[0], mygw[1], mygw[2], mygw[3]); //��������
   uip_setdraddr(ipaddr);
   uip_ipaddr(ipaddr, mysm[0], mysm[1], mysm[2], mysm[3]); //������������
   uip_setnetmask(ipaddr);

   timer_set(&periodic_timer, ((CLOCK_CONF_SECOND / 2)/10)/1); //����TIM2 10ms periodic  500msִ��һ��  �ĳ�10msִ��һ��	  ȫ��g_RunTime����ʱ��ÿ10ms��1
   timer_set(&arp_timer, ((CLOCK_CONF_SECOND * 10)/10));	    //10sִ��һ��	ʵ����ÿ10msִ��һ������Ҫ��10 CLOCK_CONF_SECOND=1000Ĭ��
   uip_arp_init();
   uip_listen(HTONS(myserverport));							    //�����������Ķ˿�
   if(CPU_DEBUG) USART1_Put_String("[system info]:static ip mode \r\n");
   /*mac*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:mac=");
   if(CPU_DEBUG)
   {
      for(i=0;i<6;i++)
      {
        Hex2HexStr(mymac[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<5) if(CPU_DEBUG) USART1_Put_String("-");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
   
    /*ip*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:ip=");
   if(CPU_DEBUG)
   {
      for(i=0;i<4;i++)
      {
        Hex2Str(myip[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
	/*Subnet mask*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:sm=");
   if(CPU_DEBUG)
   {
      for(i=0;i<4;i++)
      {
        Hex2Str(mysm[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
	/*Gateway*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:gw=");
   if(CPU_DEBUG)
   {
      for(i=0;i<4;i++)
      {
        Hex2Str(mygw[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
    /*port*/
   
   if(CPU_DEBUG) USART1_Put_String("[system info]:port=");
   if(CPU_DEBUG)
   {
        U16_2Str(myserverport);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)sssStr);
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
#endif
	 
	 httpd_init();
}
/*! \ app_aborted
 *
 */
void app_aborted(void)
{
  
  u8_t i;  
  if(CPU_DEBUG) USART1_Put_String("[system info]:app_aborted()=:( \r\n");
  if(uip_conn->lport!=HTONS(80))
  {
      for(i=0;i<UIP_CONNS;i++)
	  {
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //�еǼǹ�
		{
			socket_keepalive[i].uip_kpl_rport=0;                   //����ǰclient�Ķ˿ڸ�ֵ
			socket_keepalive[i].uip_kpl_time=0;                    //��ֵ����
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //׼��...
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]: client socket active released=socket_closed[");
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("]:) \r\n"); 
			break;
		}
	  }
  }
  uip_close();
  uip_poll_ack_static=CLINT_ACKED_CLOSED;
}
/*! \ app_timedout
 *
 */
void app_timedout(void)
{ 
  u8_t i;
  if(CPU_DEBUG) USART1_Put_String("[system info]:app_timedout=:( \r\n");
  if(uip_conn->lport!=HTONS(80))
  {
      for(i=0;i<UIP_CONNS;i++)
	  {
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //�еǼǹ�
		{
			socket_keepalive[i].uip_kpl_rport=0;                   //����ǰclient�Ķ˿ڸ�ֵ
			socket_keepalive[i].uip_kpl_time=0;                    //��ֵ����
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //׼��...
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]: client socket active released=socket_closed[");
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("]:) \r\n"); 
			break;
		}
	  }
  }
  uip_close();
  uip_poll_ack_static=CLINT_ACKED_CLOSED;
}
/*! \ app_closed
 *	  ������client�Ͽ���������ͷ�keepalive conn�ĵ���ʱ����
 */
void app_closed(void)
{
  u8_t i;
  uip_poll_ack_static=CLINT_ACKED_CLOSED;
  if(CPU_DEBUG) USART1_Put_String("[system info]:app_closed=:( \r\n");
  if(uip_conn->lport!=HTONS(80))
   {
      for(i=0;i<UIP_CONNS;i++)
	  {
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //�еǼǹ�
		{
			socket_keepalive[i].uip_kpl_rport=0;                   //����ǰclient�Ķ˿ڸ�ֵ
			socket_keepalive[i].uip_kpl_time=0;                    //��ֵ����
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //׼��...
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]: client socket active released=socket_closed[");
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("]:) \r\n"); 
			break;
		}
	  }
   }
}
/*! \ app_connected
 *	  ������client���Ӻ������keepalive�ĵ���ʱ����
 */
void app_connected(void)
{
    u16 i;
    if(CPU_DEBUG) USART1_Put_String("[system info]:app_connected=:) \r\n");

   uip_poll_ack_static=CLINT_ACKED_SYNACK;

   if(uip_conn->lport!=HTONS(80))
   {
      for(i=0;i<UIP_CONNS;i++)
	  {
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //�еǼǹ�
		{
			socket_keepalive[i].uip_kpl_rport=uip_conn->rport;    //����ǰclient�Ķ˿ڸ�ֵ
			socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //��ֵ����
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //���ͨ����,�����ͷ�
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==TCP_KEEPALIVE_TIME(app_connected=resume) :) \r\n"); 
			break;
		}
	  }
	  if(i==UIP_CONNS)  //��ƥ���
	  {
		for(i=0;i<UIP_CONNS;i++)
		{
		   if(socket_keepalive[i].uip_kpl_rport==0)                 //���λ
		   {
			  socket_keepalive[i].uip_kpl_rport=uip_conn->rport;    //����ǰclient�Ķ˿ڸ�ֵ
			  socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //��ֵ����
			  socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //���ͨ����,�����ͷ� 
			  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
			  if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
			  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==TCP_KEEPALIVE_TIME(app_connected=new) :) \r\n");
			  break;
		   }
		}
	  }
   }
} 

/*! \ app_stop
 *
 */ 
void app_stop(void)
{
  u8_t i;
  if(CPU_DEBUG) USART1_Put_String("[system info]:app_stop=:) \r\n");
  if(uip_conn->lport!=HTONS(80))
   {
      for(i=0;i<UIP_CONNS;i++)
	  {
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //�еǼǹ�
		{
			socket_keepalive[i].uip_kpl_rport=0;                   //����ǰclient�Ķ˿ڸ�ֵ
			socket_keepalive[i].uip_kpl_time=0;                    //��ֵ����
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //׼��...
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]: client socket active released=socket_closed[");
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("]:) \r\n"); 
			break;
		}
	  }
   }
   uip_close();
   uip_poll_ack_static= CLINT_ACKED_CLOSED;

} 
/*! \ app_rexmit
 *
 */ 
void app_rexmit(void)
{
  if(CPU_DEBUG) USART1_Put_String("[system info]:app_rexmit=:) \r\n");
  // uip_poll_ack_static= CLINT_ACKED_CLOSED;
} 
/*! \ Uip_Appcall
 *
 */ 
void Uip_Appcall()  
{  	
    //u16 s_len;
	u16 i;
	u16 datlen;
	if(HTONS(uip_conn->lport)==80){
		httpd_appcall();
		return ;
	}
    if(uip_connected())  app_connected();
	if(uip_closed())     app_closed();
	if(uip_timedout())   app_timedout();
	if(uip_aborted())    app_aborted();
	//if(uip_stop())     app_stop();
	//if(uip_rexmit())	 app_rexmit();

    switch(uip_conn->lport) {
	case HTONS(4001):
	if (uip_newdata())	  
	{
           if((uip_len>0)&&(uip_len<=1446))
		   {
			 //�յ����� ����keepalive��ʼ��
			 if(uip_conn->lport!=HTONS(80))
			 {
			    for(i=0;i<UIP_CONNS;i++)
			    {
			        if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)  //�еǼǹ�
				    {
					  socket_keepalive[i].uip_kpl_rport=uip_conn->rport;    //����ǰclient�Ķ˿ڸ�ֵ
				      socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //��ֵ����
					  socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //���ͨ����,�����ͷ� 
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==TCP_KEEPALIVE_TIME(uip_newdata()||(uip_rexmit())=resume) :) \r\n");
					  break; 
				    }
			    }
			    if(i==UIP_CONNS)  //��ƥ���
			    {
			       for(i=0;i<UIP_CONNS;i++)
			       {
			         if(socket_keepalive[i].uip_kpl_rport==0)               //���λ
				     {
					  socket_keepalive[i].uip_kpl_rport=uip_conn->rport;    //����ǰclient�Ķ˿ڸ�ֵ
				      socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //��ֵ����
					  socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //���ͨ����,�����ͷ� 
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==TCP_KEEPALIVE_TIME(uip_newdata()||(uip_rexmit())=new) :) \r\n");
				      break;
					 }
			       }
			    }
			 }
			 if(memcmp(uip_appdata,"~Cosmos Restart~",16)==0)				//����Զ��TCP��λ������
			 {
			      if(CPU_DEBUG) USART1_Put_String("[system info]:form tcp client ~Cosmos Restart~ = RST_CPU()\r\n");
			      RST_CPU();
			 }

		     if(TCP_LOOKBACK) 
			 {   
				 uip_send(uip_appdata,uip_len); //�����ش�����,�˹���һ��ֻ���ڲ���TCP���շ�����
			
			 }
			 if(TCP2UART1)
			 {
			     USART1_Put_Data(uip_appdata,uip_len);
				 //TCP���ݷ��͸�����1,����ķ�������ʱ�� 
				 //���ÿ��Գ䵱TCP Ack�ĵȴ�ʱ��, 
				 //1446��������ͨ�����ڷ��Ͳ��ᵼ��socket�˵ĵȴ�ACKʱ���쳣����
				 //Q��TCP��ʱȷ�ϻ��ƹ���ԭ��
                 //A��TCP��ʱȷ��ʱ��ͨ��Ϊ���ٺ��룬
				 //������ӳ�ʱ�����б��Ķ�Ҫ���͵Ļ���
				 //ack���ӵ����ݱ��Ķ�һ���ͣ����û�У���ô���ӳ�ʱ�䵽ʱ���͵�������ACK��
				 //������Դ����ڵ�����,������ڸպ������ݴ����� ��uip_send(uip_appdata,uip_len); ��PSH,ACKһ��
			 }
			 //���¹��ܶ�����Ҫ����ʱ,�˴�����ʵ���Ƕ�uip_newdata()||(uip_rexmit())��Ack����

			 if(1)//�Ƿ����Ӵ��Ĵ�������Ҫһ����
			 {
			   	 if(uip_poll_ack_static==CLINT_ACKED_SYNACK||uip_poll_ack_static==CLINT_ACKED_NORMAL||uip_poll_ack_static==CLINT_ACKED_CARRY)
				 {
				     uip_poll_ack_static=CLINT_NEWDAT_ACKED_CARRY;		  //���ñ��ΪPSH+ACKֵ
				 }
			     
			 }
		   }
    }

	/*test*/
	if(uip_acked()&&(uip_poll_ack_static==CLINT_ACKED_CLOSED)) 
	{
	   //�����ڵ�״̬			  
	}
	if(uip_acked()&&(uip_poll_ack_static==CLINT_ACKED_SYNACK)) 
	{
	   //�����ڵ�״̬			  
	}
	if(uip_acked()&&(uip_poll_ack_static==SERVER_ACTIVE_SEND)) 
	{
	   //���ڵ�״̬			  
	}
	if(uip_acked()&&(uip_poll_ack_static==CLINT_NEWDAT_ACKED_CARRY)) 
	{
	   //���ڵ�״̬			  
	}
	if(uip_acked()&&(uip_poll_ack_static==CLINT_ACKED_CARRY)) 
	{
	   //���ڵ�״̬			  
	}
	if(uip_acked()&&(uip_poll_ack_static==CLINT_ACKED_NORMAL)) 
	{
	   //���ڵ�״̬			  
	}
	/*test*/

	if(uip_acked()||uip_poll()||uip_rexmit())		 
    {   
		//�鿴�Ƿ��д���������Ҫ����

		if(CPU_DEBUG_TIMER) USART1_Put_String("uip_poll()\r\n");
		datlen=0;						
        if(rcv_usart1_data_flg)				  //Timer counts 6ms, then, usart1_end_flag turns high
        {
			datlen=rcv_usart1_data_len;
			if(datlen>0)
			{
			   //������1���͹���������
			   if(memcmp(rcv_usart1_array,"~Cosmos Restart~",16)==0)
			   {
			      if(CPU_DEBUG) USART1_Put_String("[system info]:form tcp uart1 ~Cosmos Restart~ = RST_CPU()\r\n");
			      RST_CPU();
			   }
			   uip_len=datlen;
			   if(uip_len>=1500)
			   {
			      uip_len=0; 
			      if(CPU_DEBUG) USART1_Put_String("[system info]:form  uart1  uip_len>=1500\r\n");
			   }
			   memcpy(uip_appdata,rcv_usart1_array,uip_len);
	           uip_send(uip_appdata,uip_len);
			   uip_poll_ack_static=3; 		 
			   for(i=0;i<UIP_CONNS;i++)
			   {    
				  socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //��ֵ����	 
			   }
			       
			}
            rcv_usart1_data_flg = 0;
        } 
		for(i=0;i<UIP_CONNS;i++)
		{
			
			if((socket_keepalive[i].uip_kpl_type==SOCKET_COMM_OFF)&&((uip_conn->rport==socket_keepalive[i].uip_kpl_rport)))	    //ƥ��һ��
			 { 
				  socket_keepalive[i].uip_kpl_rport=0;
				  socket_keepalive[i].uip_kpl_type=0;   
				  socket_keepalive[i].uip_kpl_time=0;				  
				  socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //�ر�socket,�ظ��ɳ�ʼ�ȴ� 				  
				  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
				  if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
				  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_close() :) \r\n");
				  if(CPU_DEBUG) USART1_Put_String("[system info].uip_close()=socket_keepalive :) \r\n");
				  uip_abort();	           	                            //ע��keepalive���� uip_close()��رն�Ӧkeepalive��socket
				  break;												//һ��ֻ����һ���ͷ�
             } 			 			   
		} 
	}



	break;

	case HTONS(80):
			httpd_appcall();
	break;

	default:
	break;
 }
}

/*! \ Udp_Appcall
 *																														  
 */
void Udp_Appcall(void)  
{  

    switch(uip_udp_conn->rport) 
	{
	  case HTONS(67):
	  case HTONS(68):
           dhcpc_appcall();
	       break;
	  default:
	       break; 
	}

} 


void dhcpc_configured(const struct dhcpc_state *s)
{
    u8 i;
	uip_ipaddr_t ipaddr;

    uip_sethostaddr(&s->ipaddr);
    uip_setnetmask(&s->netmask);
    uip_setdraddr(&s->default_router);

	memcpy(myip,s->ipaddr,4);
	memcpy(mysm,s->netmask,4);
	memcpy(mygw,s->default_router,4);


   uip_ethaddr.addr[0] = mymac[0];
   uip_ethaddr.addr[1] = mymac[1];
   uip_ethaddr.addr[2] = mymac[2];
   uip_ethaddr.addr[3] = mymac[3];
   uip_ethaddr.addr[4] = mymac[4];
   uip_ethaddr.addr[5] = mymac[5];
   uip_setethaddr(uip_ethaddr);

   uip_ipaddr(ipaddr, myip[0], myip[1], myip[2], myip[3]);      //����Ip
   uip_sethostaddr(ipaddr);
   uip_ipaddr(ipaddr, mygw[0], mygw[1], mygw[2], mygw[3]);      //��������
   uip_setdraddr(ipaddr);
   uip_ipaddr(ipaddr, mysm[0], mysm[1], mysm[2], mysm[3]);      //������������
   uip_setnetmask(ipaddr);

   timer_set(&periodic_timer, ((CLOCK_CONF_SECOND / 2)/10)/1);  //����TIM2 10ms periodic  500msִ��һ��  �ĳ�10msִ��һ��	  ȫ��g_RunTime����ʱ��ÿ10ms��1
   timer_set(&arp_timer, ((CLOCK_CONF_SECOND * 10)/10));	    //10sִ��һ��	ʵ����ÿ10msִ��һ������Ҫ��10 CLOCK_CONF_SECOND=1000Ĭ��
   uip_arp_init();
   uip_listen(HTONS(myserverport));							    //�����������Ķ˿�
	if(CPU_DEBUG) USART1_Put_String("[system info]:dhcpc_configured()=successed \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:dhcp  mode \r\n");
	/*mac*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:mac=");
   if(CPU_DEBUG)
   {
      for(i=0;i<6;i++)
      {
        Hex2HexStr(mymac[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<5) if(CPU_DEBUG) USART1_Put_String("-");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
   
    /*ip*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:dhcp-ip=");
   if(CPU_DEBUG)
   {
      for(i=0;i<4;i++)
      {
        Hex2Str(myip[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
	/*Subnet mask*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:dhcp-sm=");
   if(CPU_DEBUG)
   {
      for(i=0;i<4;i++)
      {
        Hex2Str(mysm[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
	/*Gateway*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:dhcp-gw=");
   if(CPU_DEBUG)
   {
      for(i=0;i<4;i++)
      {
        Hex2Str(mygw[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
    /*port*/
   
   if(CPU_DEBUG) USART1_Put_String("[system info]:port=");
   if(CPU_DEBUG)
   {
        U16_2Str(myserverport);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)sssStr);
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
   if(CPU_DEBUG) USART1_Put_String("[system info]::) \r\n");
   if(CPU_DEBUG) USART1_Put_String("[system info]:********************************************************/ \r\n");
}
