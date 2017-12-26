#include "global.h"


char HexTable[]={"0123456789ABCDEF"}; //ascii��>hex��ת����
char HEXStr[32];	//����ת����ʱ�ڴ�
char sssStr[5];		//����ת����ʱ�ڴ�
char caNewString[1024];	 //ע�ⶨ���ں����ڲ����׶�ջ��� ��ֵ�ķ�Χ����С�����һ�β�ѯ���ڴ�λ��
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
    Str = sssStr;
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
/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART1_printf()����
 */
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

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
  mymac[5]=(u8 )(Device_Serial2>>3);    	   /*MAC���3�ֽ�����STM��ΨһID���㣬�ر�ע��˷������ܴ����ظ�*/
}