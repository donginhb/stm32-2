//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
//����delay_us,delay_ms
//�������Ƶ���
//���̵�ַ��http://shop73023976.taobao.com/shop/view_shop.htm?tracelog=twddp&trace_log=qianniu_pc
//�޸�����:2014/3/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������Ƶ���2014/3/16
//All rights reserved
//********************************************************************************
#include "delay.h"
#include "oled.h"


 int main(void)
 {	u8 t;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�// 	LED_Init();			     //LED�˿ڳ�ʼ��
	OLED_Init();			//��ʼ��OLED      
  	OLED_ShowString(1,0, "0.96' OLED TEST");  
  	OLED_ShowString(1,16,"ICEFIRE@QINGYUN");  
   	OLED_ShowString(1,32,"2014/03/16");  
  	OLED_ShowString(1,48,"ASCII:");  
  	OLED_ShowString(63,48,"CODE:");  
	
/*	 OLED_ShowCHinese(13,16,0);
	 OLED_ShowCHinese(33,16,1);
	 OLED_ShowCHinese(53,16,2);
	 OLED_ShowCHinese(73,16,3);
	 OLED_ShowCHinese(93,16,4);
	 OLED_ShowCHinese(113,16,5);
	 OLED_ShowCHinese(33,36,6);
	 OLED_ShowCHinese(53,36,7);
	 OLED_ShowCHinese(73,36,8);
	 OLED_ShowCHinese(93,36,9);*/
//OLED_Refresh_Gram();	 
	t=' ';  
	while(1) 
	{		
		OLED_ShowChar(48,48,t,16,1);//��ʾASCII�ַ�	   	OLED_Refresh_Gram();
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,48,t,3,16);//��ʾASCII�ַ�����ֵ 
		delay_ms(300);
	}	  
	
}

