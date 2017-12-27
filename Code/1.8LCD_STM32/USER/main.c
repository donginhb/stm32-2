/*********************************************************************************/	 
//STM32Һ����������ʾ������
//����֧��:www.tjc1688.com
//�������Ծ��۵������޹�˾
//�������ϣ�http://tftmcu.taobao.com

//Ӳ��SPI1�ӿ�: Ӳ������STM32f103VCT6
//TFT_CS��STM32	 PA4
//RESET��STM32	 PB0
//TFT_A0��STM32	 PC4
//TFT_SDA��STM32 SPI1_MOSI
//TFT_SCK��STM32 SPI1_SCK									  
/*********************************************************************************/	
#include "led.h"
#include "delay.h"
#include "key.h"
//#include "sys.h"
#include "lcd.h"	
#include "font.h" 

#define LCD_W 128
#define LCD_H 160


_lcd_dev lcddev;

u8 xx=0;
u8 state=0;
u8 idfind(u8 *buf,u8 *val,u8 len);


void beepms(u16 va);

//m^n����
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	



//void refshow(void);//ˢ����ʾ	 
//u8 stringfind(u8 *buf,u8 *val);
u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
{
	while((SPIx->SR&SPI_I2S_FLAG_TXE)==RESET);		//�ȴ���������	  
	SPIx->DR=Byte;	 	//����һ��byte   
	while((SPIx->SR&SPI_I2S_FLAG_RXNE)==RESET);//�ȴ�������һ��byte  
	return SPIx->DR;          	     //�����յ�������			
} 

void LCD_Writ_Bus(u8 da)   //��������д��
{

 SPI_WriteByte(SPI1,da);

} 
void LCD_WR_DATA8(u8 da) //��������-8λ����
{
    LCD_RS_SET;		     //RS=1
	LCD_Writ_Bus(da);
}  
 void LCD_WR_DATA(u16 da)
{
    LCD_RS_SET;
	LCD_Writ_Bus(da>>8);
	LCD_Writ_Bus(da);
}	  
void LCD_WR_REG(u8 da)	 
{
    LCD_RS_RESET;
	LCD_Writ_Bus(da);
}
 void LCD_WR_REG_DATA(u16 reg,int da)
{
    LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}
void Address_set(u16 x1,u16 y1,u16 x2,u16 y2)
{  
   LCD_WR_REG(0x2a);
   LCD_WR_DATA8(x1>>8);
   LCD_WR_DATA8(x1);
   LCD_WR_DATA8(x2>>8);
   LCD_WR_DATA8(x2);
  
   LCD_WR_REG(0x2b);
   LCD_WR_DATA8(y1>>8);
   LCD_WR_DATA8(y1);
   LCD_WR_DATA8(y2>>8);
   LCD_WR_DATA8(y2);

   LCD_WR_REG(0x2C);

}

		 
//��������
//Color:Ҫ���������ɫ
void LCD_Clear(u16 Color)
{
	u8 VH,VL;
	u16 i,j;
	VH=Color>>8;
	VL=Color;	
	Address_set(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_W;i++)
	 {
	  for (j=0;j<LCD_H;j++)
	   	{
        	 LCD_WR_DATA8(VH);
			 LCD_WR_DATA8(VL);	
	    }
	  }
}
//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;

	      			     
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	Address_set(x,y,x+8-1,y+16-1);      //���ù��λ��
	if(!mode) //�ǵ��ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				//LCD_DrawPoint(x,y);
				LCD_WR_DATA(POINT_COLOR);	
				temp>>=1;
				y++;
				if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
					break;
				} 
			}  	 
	    }    
	}else//���ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����		 LCD_ShowChar(x,y,*p,size,1);
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_WR_DATA(POINT_COLOR);//LCD_DrawPoint(x,y); 
				temp>>=1;
				y++;
				if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
					break; 
				}	 
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,1);
        x+=size/2;
        p++;
    }  
}

void showhanzi(unsigned int x,unsigned int y,unsigned char index)	
{  
	unsigned char i,j;
	unsigned char *temp=hanzi;    
    Address_set(x,y,x+31,y+31); //��������      
	temp+=index*128;	
	for(j=0;j<128;j++)
	{
		for(i=0;i<8;i++)
		{ 		     
		 	if((*temp&(1<<i))!=0)
			{
				LCD_WR_DATA(POINT_COLOR);
			} 
			else
			{
				LCD_WR_DATA(BACK_COLOR);
			}   
		}
		temp++;
	 }
}

void xianshi()
{
	
	LCD_Clear(RED);	
	delay_ms(1000);
	LCD_Clear(GREEN);
	delay_ms(1000);
	LCD_Clear(BLUE);
	delay_ms(1000);
	LCD_Clear(WHITE);
	BACK_COLOR=YELLOW;
	POINT_COLOR=RED;
	showhanzi(5,5,0);   //��
	showhanzi(37,5,1); 	//��
//	showhanzi(69,4,2);	//��
//	showhanzi(101,4,3);	//��
//	showhanzi(133,4,4);	//��
//	showhanzi(165,4,5);	//��
	BACK_COLOR=YELLOW;
	POINT_COLOR=RED;
	LCD_ShowString(5,50,200,16,16,"tftmcu.taobao.com");	


}

void showimage() //��ʾ40*40ͼƬ
{
  	int i,j,k;
	xianshi(); //��ʾ��Ϣ
	for(k=2;k<4;k++)
	{
	   	for(j=0;j<3;j++)
		{	
			Address_set(40*j,40*k,40*j+39,40*k+39);		//��������
		    for(i=0;i<1600;i++)
			 {				
			  	 LCD_WR_DATA8(image[i*2+1]);	 //������ɫ����
				 LCD_WR_DATA8(image[i*2]);					
			 }	
		 }
	}
		
}	

void beepms(u16 va)
{
	beep=1;
	delay_ms(va);
	beep=0;
}					
int main(void)
 {	 
	lcddev.height=160;
	lcddev.width=128;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	LED_Init();			     //LED�˿ڳ�ʼ��
    SPI1_Init();
	LCD_Init();
	showimage();
	while(1);
}


