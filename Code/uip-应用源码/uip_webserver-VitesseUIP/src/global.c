#include "global.h"

unsigned int  volatile  Sys_Dog_start=0;        //�����
unsigned int  volatile  Sys_Dog_Count=0;        //��������



char caNewString[1024];	            //ע�ⶨ���ں����ڲ����׶�ջ��� ��ֵ�ķ�Χ����С�����һ�β�ѯ���ڴ�λ��
char HexTable[]={"0123456789ABCDEF"};    //ascii��>hex��ת����
char HEXStr[32];	                     //����ת����ʱ�ڴ�
char sssStr[5];		                     //����ת����ʱ�ڴ�

/*usart1 send start and end flags & send dwell time counter */
u8 volatile  rcv_usart1_str_flag   = 0;		//�������ݽ����������
u8 volatile  rcv_usart1_end_flag   = 0;		//�������ݽ��ս������			             
u8 volatile  rcv_usart1_over_count = 0;		//���ݽ���ʱ��������
u8           rcv_usart1_array[BUF1_LEN];
u8  volatile rcv_usart1_data_flg   = 0;
u16 volatile rcv_usart1_data_len   = 0;

u8 volatile rcv_usart2_str_flag    = 0;		//�������ݽ����������
u8 volatile  rcv_usart2_end_flag   = 0;		//�������ݽ��ս������			             
u8 volatile  rcv_usart2_over_count = 0;		//���ݽ���ʱ��������
u8           rcv_usart2_array[BUF2_LEN];
u8  volatile rcv_usart2_data_flg   = 0;
u16 volatile rcv_usart2_data_len   = 0;

u8 *inTx1Buf;
u8 *outTx1Buf; 
u8 *inRx1Buf;
u8 *outRx1Buf;                      //�շ���������дָ���жϺ������õ�,��Ϊȫ�ֱ���

u8 Tx1Buf[BUF1_LEN];
u8 Rx1Buf[BUF1_LEN];                // �շ�������ʵ��


//u8 send_buffer2[BUF2_LEN];

u8 *inTx2Buf;
u8 *outTx2Buf; 
u8 *inRx2Buf;
u8 *outRx2Buf;                      //�շ���������дָ���жϺ������õ�,��Ϊȫ�ֱ���

u8 Tx2Buf[BUF2_LEN];
u8 Rx2Buf[BUF2_LEN];                // �շ�������ʵ��
		                   


/*Communication err flag*/

u8  volatile led_red_sel = 0;
u8  volatile led_blue_sel = 0;


/*! \ Hex2HexStr
 *
 */
void Hex2HexStr(unsigned char hex) 
{
  char  *Str;
  char  ch;
  memset(HEXStr,0,sizeof(HEXStr));

  Str=HEXStr;

  ch  =hex>>4;
  *Str++=HexTable[ch];

  ch  =hex&0x0F;
  *Str++=HexTable[ch];

}
/*! \ Hex2Str
 *
 */
void Hex2Str(unsigned char hex) 
{
   char *Str;
   unsigned char x,y,k;
   
   memset(HEXStr,0,sizeof(HEXStr));
   Str = HEXStr;

    x=hex;
    if(x>99)
	{
      y=x/100;*Str++=y+'0';
      x=x-100*y;y=x/10;*Str++=y+'0';
      x=x-10*y;*Str++=x+'0';
    }
    else if(x>9)
	{
      y=x/10;*Str++=y+'0';
      x=x-10*y;*Str++=x+'0';
    }
    else
	{
      *Str++=x+'0';
    }

	for(k=0;k<3;k++)
	{
	  if(HEXStr[k]==0)
	  {
		if(k==0){};
	    if(k==1){memmove(HEXStr+2,HEXStr,1);HEXStr[0]=0x30;HEXStr[1]=0x30;}
		if(k==2){memmove(HEXStr+1,HEXStr,2);HEXStr[0]=0x30; }
	  }
	}
   
}

/**********************************************************************
**����ԭ�ͣ�    void 	int2Str(unsigned int portnum)
**��ڲ���:     unsigned int portnum		:UDP��TCP�˿�
**���ڲ���:		��
**�� �� ֵ��	��       
**˵    ����	ʵ�ֶ˿ںŵ��ַ�����ת��,�ַ��������PortStr[5]�ַ�����
************************************************************************/
void U16_2Str(unsigned int portnum)    
{
    unsigned int  x;
	unsigned char y;
	unsigned char *Str;
    Str = (unsigned char *)sssStr;
	x = portnum;
	   if(x>9999)
			{
            y=x/10000;*Str++=y+'0';
            x=x-10000*y;y=x/1000;*Str++=y+'0';
            x=x-1000*y;y=x/100;*Str++=y+'0';
			x=x-100*y;y=x/10;*Str++=y+'0';
			x=x-10*y;*Str++=x+'0';
			*Str++='\0';
     		}
        else if(x>999)
			{
			y=x/1000;*Str++=y+'0';
           	x=x-1000*y;y=x/100;*Str++=y+'0';
			x=x-100*y;y=x/10;*Str++=y+'0';
			x=x-10*y;*Str++=x+'0';
			*Str++='\0';
        	}
        else if(x>99)
			{
            y=x/100;*Str++=y+'0';
           	x=x-100*y;y=x/10;*Str++=y+'0';
			x=x-10*y;*Str++=x+'0';
			*Str++='\0';
		  	}
		else
		    {
			y=x/10;*Str++=y+'0';
			x=x-10*y;*Str++=x+'0';
			*Str++='\0';
			}    
	
}
/*! \ ReplaceStr
 *
 */
int ReplaceStr(char *sSrc, char *sSubStr, char *sReplaceStr)
{
    int  StringLen;

//	char caNewString[1024];	 //ע�ⶨ���ں����ڲ����׶�ջ��� ��ֵ�ķ�Χ����С�����һ�β�ѯ���ڴ�λ��
	
    char *FindPos = strstr(sSrc, sSubStr);
    if( (!FindPos) || (!sSubStr) )
        return -1;
    
    while( FindPos )
    {
        memset(caNewString, 0, sizeof(caNewString));
        StringLen = FindPos - sSrc;
        strncpy(caNewString, sSrc, StringLen);//0x14F ��Զ��λ��
        strcat(caNewString, sReplaceStr);
        strcat(caNewString, FindPos + strlen(sSubStr));
        strcpy(sSrc, caNewString);
        
        FindPos = strstr(sSrc, sSubStr);
    }
    
    return 0;
}
