/*****************************************************************************************************
 @project name: cosmos
 @system:       nOS with uIP1.0	
 @funcation: 	TCP/IP转RS485  socket=10
 @bug:          jerkoh@163.com
 @date:         2013-02
     stress tests: 
                   测试环境: 室内1~25°C
                   工控机: ATOM D425、2G内存
			       USB网卡: RD9700 USB2.0 To Fast Ethernet Adapter  
			       交换机: Mercury-S108M
			       编译器：MDK-4.12
	
                   Tcp/ip client 每1ms 发送32Kbytes,server返回32Kbytes数据 (开启2个Tcp client
                   同时进行)并进行2个icmp echo,1个webserver每1s 刷新一次,
			       连续不断电测试5天,服务器不重启、系统不出现溢出死机、client随时可连接上server
			       (注意由于Mss及RAM问题、进行每1ms收发32Kbytes数据必定有丢包存在,但不影响压力
			       测试) 

      disclaimer：
			       所有协议栈、驱动、库文件都来源于网络.
			       应用APP代码均开源,应用APP代码可在不经过作者同意的情况下用于商业或非商业的
			       目的的应用，但请勿应用于涉及生命、财产安全的工程,如医疗、军事、航空等项目,
				   任何因使用cosmos工程造成的不良后果,作者不承担任何法律责任
 ----------------------------------------------------------------------------------------------------
 logs: alpha=V0.x  beta=V1.x  Release>=V2.0	  	 所有相关的调试宏设置在global.h  ***debug define***
 ----------------------------------------------------------------------------------------------------
 V2.0  2013-xx-xx  Release                    
 ----------------------------------------------------------------------------------------------------
 V1.f  2013-xx-xx                     
 ----------------------------------------------------------------------------------------------------
 V1.e  2013-03-14  修正了所有的编译器警告(采用warning=<unspecified> 、level0(-o0))
                   修正了部分debug输出信息
				   增加了UIP_STATIC_IP_ADDR宏定义采用静态IP或动态DHCP                     
 ----------------------------------------------------------------------------------------------------
 V1.d  2013-03-13  增加了uip1.0的DHCP功能,测试成功
                   注意必须修改enc28j60的初始化接收广播功能寄存器ERXFCON_BCEN                     
 ----------------------------------------------------------------------------------------------------
 V1.c  2013-03-11  修正了uip_main的elseif 判断周期问题，解决了V1.b的Bug                   
 ----------------------------------------------------------------------------------------------------
 V1.b  2013-03-11  实现了多个(10个)client连接的server keepalive功能
                   #define UIP_CONF_MAX_CONNECTIONS 10
                   #define UIP_CONF_MAX_LISTENPORTS 10
				   if((socket_keepalive[i].uip_kpl_type==SOCKET_COMM_OFF)&&
				   ((uip_conn->rport==socket_keepalive[i].uip_kpl_rport)))
				   存在的漏洞是 某个client一直不停地发数据给uIP栈,uIP就一直newdata标记处理
				   无机会进入并检测到uip_poll标记keepalive处理需要释放的client                 
 ----------------------------------------------------------------------------------------------------
 V1.a  2013-03-09  取消webserver所有功能,注销80口的监听
                   删除读STM32温度函数
                   #define UIP_CONF_MAX_CONNECTIONS 1
                   #define UIP_CONF_MAX_LISTENPORTS 1                     
 ----------------------------------------------------------------------------------------------------
 V1.9  2013-03-08  修正串口0,1的len u8改成u16   
                   串口缓冲大小设置小于1500，改成1200，防止内存copy溢出而hardfault重启                
 ----------------------------------------------------------------------------------------------------
 V1.8  2013-03-05  修正了T2定时器 1ms是1.1ms的BUG (ETTG 控我所控)                  
 ----------------------------------------------------------------------------------------------------
 V1.7  2013-03-04  修正了部分名称定义
                   实现了TCP Server模式的keepalivetime功能,Socket定义最多10个
				   keepalive 在远程客户端新建连接后、或者通信过一次后超过设置的保活时间
				   服务器将自动断开释放该客户端(只能开一个socket的模式有效
				   #define UIP_CONF_MAX_CONNECTIONS 1) 否则无法确定哪个client而导致uip
				   _abort()错误断开client
 ----------------------------------------------------------------------------------------------------
 V1.6  2013-03-03  增加了web的数据发送状态迁移变量(html_status 未宏定义实名)
				   webserver存在概率较低的自动刷新错误
				   POST解析未处理
				   增加野火嵌入式工作室的STM32内部温度值计算代码
 ----------------------------------------------------------------------------------------------------
 V1.5  2013-03-02  main.c 未进行代码的整理归档
                   RAM 总计20K
                   其中10K多RAM用于UART1&2,调整宏定义值或者修改UART的环形收发函数
				   可释放大量内存供用户继续使用
                   增加STM32 内置硬件狗,实现软狗main清0,定时器溢出
				   硬狗定时器清0,保证了main某处死循环、但进入定时器
				   或者定时器不进行、main正常的情况下都可以进行系统复位
                   编译器警告未开启,隐含的警告都未处理
				   TCP Server模式下keepalive主动断开超时的client功能未开启(测试有BUG)
				   uip1.0协议栈的信息打印未宏定义到usart1 
				   增加1个USART1 CMD和TCP CLINET命令: ~Cosmos Restart~ =系统软复位
				   (成功建立TCP连接并数据收发的情况下有效)     
 ----------------------------------------------------------------------------------------------------
 V1.4  2013-03-01  加入了一个简单的webserver例程,并对ReplaceStr函数做了强调说明
                   caNewString[1024];定义全局	
                   便于操作HTML的动态参数修改
				   加入了MAC地址的*唯一*计算法(注意并非100%唯一,但利于生产编写MAC)
				   增加web的系统持续运行时间(不精确?)
 ----------------------------------------------------------------------------------------------------
 V1.3  2013-02-26  uIP1.0内核修改：UIP_TIMER标记下的处理
                   原来0.5s一次改成10ms一次后,uIP相应参数也要增加50倍
                    static u8_t uip_reasstmr;      改成 static u16_t uip_reasstmr;
                   (原因：u8_t<=255,系统需要40*50的值所以改成u16_t)
				   #define UIP_REASS_MAXAGE 40    改成 #define UIP_REASS_MAXAGE 40*50
				   修正了V1.1 timer_expired(&periodic_timer)的提速问题
				   修正了版本的可变量定义DEBUG输出
 ----------------------------------------------------------------------------------------------------
 V1.2  2013-02-26  通过底层enc28j60 send函数修正了V1.0版本的enc28j60错误问题
                   (1ms客户端发大数据量,服务器开启lookback功能,同时进行icmp
				   通信容易导致EIR_TXERIF问题的发生)
				   但大数据的通信时,ICMP丢失率较高
 ----------------------------------------------------------------------------------------------------
 V1.1  2013-02-25  修改timer_expired(&periodic_timer) 原来500ms执行一次
                   现改成500/50 ms一次执行一次 目的是为了客户端主动发送缩短等待时间
				   但uip的内核相应处理时间也从500ms编程10ms一个周期,注意ARP老化更行
				   未变还是10s一次
				   Uip_Appcall(增加rport的变量传递),做keepalive使用,但connected的时候
				   无法传递conn的具体rport或者conn值,所有uIP1.0很难适合做server服务器
				   进行一些主动的上传数据操作.
 ----------------------------------------------------------------------------------------------------
 V1.0  2013-02-23  修正了部分代码的定义，beta版本V1.0
                   实现了长时间大量数据的TCP->RS485发送功能,测试10GB数据无错误
				   未实现TCP Server对conn的 keepalive功能(socket 建立成功
				   连接后在指定时间内未进行收发数据,服务器主动关闭Socket
				   目的,防止client端错误的连接后,不进行数据交换,仅耗费一个资源)
				   仅实现了RJ45的断开检测,但未进行socket的主动关闭
				   未实现实时的将RS485口将数据发送到TCP Socket(所有建立的
				   socket或者最后一个通信的socket)
				   enc28j60 EIR_TXERIF问题未解决,靠初始化enc28j60暂时解决
				   多个socket client同时进行tcp/ip数据交换,uIP1.0大数据量通信
				   容易丢失包
				   1ms客户端发大数据量,服务器开启lookback功能,同时进行icmp通信
				   容易导致EIR_TXERIF问题的发生
				   后续Beta Release 版本逐步增加功能包含以下功能:
				   01.WebServer  02.tcp client 03.udp server 04.udp client
				   05.keepalive  06.udp broadcast search 07.flash save 08.dhcp      
				   09.telnet     10.tftp upgrade  11.Change the baud rate
 ----------------------------------------------------------------------------------------------------
 V0.5  ------V0.F  null 
 ----------------------------------------------------------------------------------------------------
 V0.4  2013-02-23  修正limit retrieve length   len-1的错误会导致mss=1446时分包
				   536,@enc28j60PacketReceive
				   底层驱动基本全部测试完成
 ----------------------------------------------------------------------------------------------------
 V0.3  2013-02-22  增加Enc28j60_EREVID的信息输出,关闭ENC28J60初始化中断使能
                   存在BUG pc大数据包1ms发送给Enc28j60,接收OK,但ENC28J60
				   底层发送函数存在BUG. 
				   修正了1.ECON1_TXRTS改成ECON1_TXRST,问题依然存在
 ----------------------------------------------------------------------------------------------------
 V0.2  2013-02-21  完成uIP1.0的移植,enc28j60底层驱动及ICMP =:)
                   Debug串口1输出 =:)
 ----------------------------------------------------------------------------------------------------
 V0.1  2013-02-20  创建、移植程序 alpha版本V0.1	
                   T410 Intel(R) 82577LM Gigabit Network Connection
				   使用交叉线可与ENC28J60正常 ping

                   参考移植驱动及硬件资源来源网络;包含以下：
                   (1)uIP1.0 Adam Dunkels adam@dunkels.com
				   (2)GPL V2 Guido Socher
				   (3)(C)COPYRIGHT 2011 野火嵌入式开发工作室
				   (4)STMicroelectronics.
				   (5)Microchip TCP/IP
				   (6)j60 code+protues v1 
 ----------------------------------------------------------------------------------------------------
 V0.0  2013-02-18  确定使用的硬件板开发板 来源：
                   http://item.taobao.com/item.htm?spm=a230r.1.14.21.KC10xP&id=21403012589
 ----------------------------------------------------------------------------------------------------                  
****************************************************************************************************/

/*! \file stm-tcp main.c
 *	\brief the main function.
 */

#include "global.h"
#include "stdio.h"



char Vxy[]="beta v1.e";											   //改变Beta V1.x即可改变Debug输出的打印信息
char fw_version[]="[system info]:firmware =~VvEeRrSsIiOoNn~ \r\n"; //注意~VvEeRrSsIiOoNn~实际是变量字符
                                                                   //定义Vxy[],应用string查找替换功能的函数
																   //目的仅测试ReplaceStr函数,无实际意义

unsigned char  lasted_compiled_system_date[]="" __DATE__;	       //最后编译日期
unsigned char  lasted_compiled_system_time[]="" __TIME__;	       //最后编译时间



struct timer periodic_timer, arp_timer;

struct uip_tcp_socket_keepalive {
  unsigned int  uip_kpl_rport;
  unsigned int  uip_kpl_time;
  unsigned int  uip_kpl_type;
};
struct 	uip_tcp_socket_keepalive socket_keepalive[UIP_CONNS];      //定义保活超时组

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

#ifndef NULL
#define NULL (void *)0
#endif /* NULL */

                                                                   //http://standards.ieee.org/develop/regauth/oui/public.html     Search for:00-11-22
unsigned char  mymac[6]={0x00,0x11,0x22,0x33,0x44,0x55};           //0x00 0x11 0x22= CIMSYS Inc  MAC固定厂商号, 0x33,0x44,0x55使用STM32的*唯一*ID计算得出
unsigned char  myip[4] ={192,168,1,8};
unsigned char  mysm[4]={255,255,255,0};
unsigned char  mygw[4]={192,168,1,1};
unsigned int   myserverport =5005;	
#define  TCP_KEEPALIVE_TIME			10                             //TCP服务器模式下对客户端的超时检测 默认60s


//--------------TCP/IP 状态迁移标记----------------------------------------------------------------------------------------------------------------------------------------
unsigned char __IO  uip_poll_ack_static  =0;          //CLINET与SERVER的数据通信状态标记,上电默认值为0=客户端错误 断开或者被关闭了

#define   CLINT_ACKED_CLOSED             0			 //服务器认为:客户端错误,断开或者被关闭了状态
#define   CLINT_ACKED_SYNACK             1			 //服务器认为:客户端发起SYN后服务器回应SYN+ACK的无数据ACKED状态
#define   SERVER_ACTIVE_SEND             2 			 //服务器认为:客户端首次连接成功的状态下,并且client没发数据过来, 服务器主动向客户端发了数据后状态
#define   CLINT_NEWDAT_ACKED_CARRY       3           //服务器认为:客户端发送新数据给服务器后，服务器进入NEWDATA状态,服务器利用PSH+ACK模式将串口数据捎带发送到client
#define   CLINT_ACKED_CARRY              4           //服务器认为:客户端ACKED了EWDATA模式下稍带的服务器数据(CARRY模式的数据)
#define   CLINT_ACKED_NORMAL             5           //服务器认为:一直在服务器发数据->客户端ACKED->服务器发数据->客户端ACKED模式  正常循环模式,并未出现NEWDATA状态下的稍带 
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
  mymac[5]=(u8 )(Device_Serial2>>3);    	   /*MAC最后3字节利用STM的唯一ID计算，特别注意此方法可能存在重复，需要配置应用软件做出厂检测MAC的唯一性*/
}


/*! \loop_feed_softdog
 *
 */
void loop_feed_softdog(void)
{
  Sys_Dog_Count=0;			    //喂软狗
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

	Get_SerialNum();//取MAC*唯一*值
    Platform_Init();
	
	if(CPU_DEBUG) USART1_Put_String("[system info]:/******************************************************* \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:嵌入式TCP/IP技术群(ETTG) QQ:28221007 (C)2006-2013\r\n");
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
       if(enc28j60_mac_is_linked()==0)	   /*查询连接状态*/
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
	      Init_Enc28j60_Chip();		 //enc28j60芯片bug,大数据量的接收发送溢出后,可以接收但	
		                             //EIR_TXERIF永远无法恢复一直锁死，必须底层初始化enc28j60
									 //注意:该问题经过修改enc28j60底层的发送函数后,测试一直正常,但以防万一,建议不注销
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
			   if(socket_keepalive[i].uip_kpl_time==0)	//匹配一致
			   { 
                     if(1)
					 {
						socket_keepalive[i].uip_kpl_rport=socket_keepalive[i].uip_kpl_rport;   //不能清0，要等uip_appcall里面检测使用,误差+-0.5s
						socket_keepalive[i].uip_kpl_type=0;   
						socket_keepalive[i].uip_kpl_time=0;
						socket_keepalive[i].uip_kpl_type=SOCKET_COMM_OFF; //keepalive需要关闭socket  
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
			   //处理串口2发送过来的数据
			   //做回显处理、硬件未经测试
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

   uip_ipaddr(ipaddr, myip[0], myip[1], myip[2], myip[3]); //配置Ip
   uip_sethostaddr(ipaddr);
   uip_ipaddr(ipaddr, mygw[0], mygw[1], mygw[2], mygw[3]); //配置网关
   uip_setdraddr(ipaddr);
   uip_ipaddr(ipaddr, mysm[0], mysm[1], mysm[2], mysm[3]); //配置子网掩码
   uip_setnetmask(ipaddr);

   timer_set(&periodic_timer, ((CLOCK_CONF_SECOND / 2)/10)/1); //基于TIM2 10ms periodic  500ms执行一次  改成10ms执行一次	  全局g_RunTime运行时间每10ms增1
   timer_set(&arp_timer, ((CLOCK_CONF_SECOND * 10)/10));	    //10s执行一次	实际是每10ms执行一次所有要除10 CLOCK_CONF_SECOND=1000默认
   uip_arp_init();
   uip_listen(HTONS(myserverport));							    //服务器监听的端口
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
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //有登记过
		{
			socket_keepalive[i].uip_kpl_rport=0;                   //将当前client的端口赋值
			socket_keepalive[i].uip_kpl_time=0;                    //置值倒计
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //准备...
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
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //有登记过
		{
			socket_keepalive[i].uip_kpl_rport=0;                   //将当前client的端口赋值
			socket_keepalive[i].uip_kpl_time=0;                    //置值倒计
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //准备...
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
 *	  功能是client断开后就启用释放keepalive conn的倒计时功能
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
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //有登记过
		{
			socket_keepalive[i].uip_kpl_rport=0;                   //将当前client的端口赋值
			socket_keepalive[i].uip_kpl_time=0;                    //置值倒计
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //准备...
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]: client socket active released=socket_closed[");
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("]:) \r\n"); 
			break;
		}
	  }
   }
}
/*! \ app_connected
 *	  功能是client连接后就启用keepalive的倒计时功能
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
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //有登记过
		{
			socket_keepalive[i].uip_kpl_rport=uip_conn->rport;    //将当前client的端口赋值
			socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //置值倒计
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //标记通信中,不可释放
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==TCP_KEEPALIVE_TIME(app_connected=resume) :) \r\n"); 
			break;
		}
	  }
	  if(i==UIP_CONNS)  //无匹配的
	  {
		for(i=0;i<UIP_CONNS;i++)
		{
		   if(socket_keepalive[i].uip_kpl_rport==0)                 //查空位
		   {
			  socket_keepalive[i].uip_kpl_rport=uip_conn->rport;    //将当前client的端口赋值
			  socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //置值倒计
			  socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //标记通信中,不可释放 
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
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //有登记过
		{
			socket_keepalive[i].uip_kpl_rport=0;                   //将当前client的端口赋值
			socket_keepalive[i].uip_kpl_time=0;                    //置值倒计
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //准备...
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
			 //收到数据 进行keepalive初始化
			 if(uip_conn->lport!=HTONS(80))
			 {
			    for(i=0;i<UIP_CONNS;i++)
			    {
			        if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)  //有登记过
				    {
					  socket_keepalive[i].uip_kpl_rport=uip_conn->rport;    //将当前client的端口赋值
				      socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //置值倒计
					  socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //标记通信中,不可释放 
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==TCP_KEEPALIVE_TIME(uip_newdata()||(uip_rexmit())=resume) :) \r\n");
					  break; 
				    }
			    }
			    if(i==UIP_CONNS)  //无匹配的
			    {
			       for(i=0;i<UIP_CONNS;i++)
			       {
			         if(socket_keepalive[i].uip_kpl_rport==0)               //查空位
				     {
					  socket_keepalive[i].uip_kpl_rport=uip_conn->rport;    //将当前client的端口赋值
				      socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //置值倒计
					  socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //标记通信中,不可释放 
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
					  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==TCP_KEEPALIVE_TIME(uip_newdata()||(uip_rexmit())=new) :) \r\n");
				      break;
					 }
			       }
			    }
			 }
			 if(memcmp(uip_appdata,"~Cosmos Restart~",16)==0)				//用于远程TCP复位处理器
			 {
			      if(CPU_DEBUG) USART1_Put_String("[system info]:form tcp client ~Cosmos Restart~ = RST_CPU()\r\n");
			      RST_CPU();
			 }

		     if(TCP_LOOKBACK) 
			 {   
				 uip_send(uip_appdata,uip_len); //开启回传数据,此功能一般只用于测试TCP的收发速率
			
			 }
			 if(TCP2UART1)
			 {
			     USART1_Put_Data(uip_appdata,uip_len);
				 //TCP数据发送给串口1,这里的发送数据时间 
				 //正好可以充当TCP Ack的等待时间, 
				 //1446的数据量通过串口发送不会导致socket端的等待ACK时间异常报错
				 //Q：TCP延时确认机制工作原理？
                 //A：TCP延时确认时间通常为几百毫秒，
				 //如果在延迟时间内有报文段要发送的话，
				 //ack附加到数据报文段一起发送；如果没有，那么当延迟时间到时，就单独发送ACK。
				 //这里可以处理串口的数据,如果串口刚好有数据待发送 就uip_send(uip_appdata,uip_len); 会PSH,ACK一起发
			 }
			 //上下功能都不需要操作时,此处返回实际是对uip_newdata()||(uip_rexmit())的Ack返回

			 if(1)//是否有捎带的串口数据要一起发送
			 {
			   	 if(uip_poll_ack_static==CLINT_ACKED_SYNACK||uip_poll_ack_static==CLINT_ACKED_NORMAL||uip_poll_ack_static==CLINT_ACKED_CARRY)
				 {
				     uip_poll_ack_static=CLINT_NEWDAT_ACKED_CARRY;		  //设置标记为PSH+ACK值
				 }
			     
			 }
		   }
    }

	/*test*/
	if(uip_acked()&&(uip_poll_ack_static==CLINT_ACKED_CLOSED)) 
	{
	   //不存在的状态			  
	}
	if(uip_acked()&&(uip_poll_ack_static==CLINT_ACKED_SYNACK)) 
	{
	   //不存在的状态			  
	}
	if(uip_acked()&&(uip_poll_ack_static==SERVER_ACTIVE_SEND)) 
	{
	   //存在的状态			  
	}
	if(uip_acked()&&(uip_poll_ack_static==CLINT_NEWDAT_ACKED_CARRY)) 
	{
	   //存在的状态			  
	}
	if(uip_acked()&&(uip_poll_ack_static==CLINT_ACKED_CARRY)) 
	{
	   //存在的状态			  
	}
	if(uip_acked()&&(uip_poll_ack_static==CLINT_ACKED_NORMAL)) 
	{
	   //存在的状态			  
	}
	/*test*/

	if(uip_acked()||uip_poll()||uip_rexmit())		 
    {   
		//查看是否有串口数据需要发送

		if(CPU_DEBUG_TIMER) USART1_Put_String("uip_poll()\r\n");
		datlen=0;						
        if(rcv_usart1_data_flg)				  //Timer counts 6ms, then, usart1_end_flag turns high
        {
			datlen=rcv_usart1_data_len;
			if(datlen>0)
			{
			   //处理串口1发送过来的数据
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
				  socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //置值倒计	 
			   }
			       
			}
            rcv_usart1_data_flg = 0;
        } 
		for(i=0;i<UIP_CONNS;i++)
		{
			
			if((socket_keepalive[i].uip_kpl_type==SOCKET_COMM_OFF)&&((uip_conn->rport==socket_keepalive[i].uip_kpl_rport)))	    //匹配一致
			 { 
				  socket_keepalive[i].uip_kpl_rport=0;
				  socket_keepalive[i].uip_kpl_type=0;   
				  socket_keepalive[i].uip_kpl_time=0;				  
				  socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //关闭socket,回复成初始等待 				  
				  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
				  if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
				  if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_close() :) \r\n");
				  if(CPU_DEBUG) USART1_Put_String("[system info].uip_close()=socket_keepalive :) \r\n");
				  uip_abort();	           	                            //注意keepalive到后 uip_close()会关闭对应keepalive的socket
				  break;												//一次只可以一个释放
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

   uip_ipaddr(ipaddr, myip[0], myip[1], myip[2], myip[3]);      //配置Ip
   uip_sethostaddr(ipaddr);
   uip_ipaddr(ipaddr, mygw[0], mygw[1], mygw[2], mygw[3]);      //配置网关
   uip_setdraddr(ipaddr);
   uip_ipaddr(ipaddr, mysm[0], mysm[1], mysm[2], mysm[3]);      //配置子网掩码
   uip_setnetmask(ipaddr);

   timer_set(&periodic_timer, ((CLOCK_CONF_SECOND / 2)/10)/1);  //基于TIM2 10ms periodic  500ms执行一次  改成10ms执行一次	  全局g_RunTime运行时间每10ms增1
   timer_set(&arp_timer, ((CLOCK_CONF_SECOND * 10)/10));	    //10s执行一次	实际是每10ms执行一次所有要除10 CLOCK_CONF_SECOND=1000默认
   uip_arp_init();
   uip_listen(HTONS(myserverport));							    //服务器监听的端口
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
