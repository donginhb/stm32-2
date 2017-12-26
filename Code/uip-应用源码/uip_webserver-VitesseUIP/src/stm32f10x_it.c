#include "global.h"

__IO int32_t g_RunTime = 0; 
__IO int32_t time_1000ms = 0; 


void SysTick_Handler(void) 
{
 
}
/*usart1*/
void USART1_IRQHandler(void)
{
    unsigned char *t1;										   //  *t1 �¶���ָ�룬ָ��Buf1

    if(USART_GetITStatus(USART1, USART_IT_RXNE)==SET)		   //  �жϣ�һ�����յ�����
    {
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);		   //  ����жϱ�־λ

        rcv_usart1_str_flag=1;					               //  �������ݽ��ձ�־��1
        rcv_usart1_over_count=0;			                   //  ÿ��һ�ֽ����������־��0

        t1 = inRx1Buf;							   			   //  ����ָ��,һ��������,һ��������
        (u8 *)t1++;				                               //  ����ָ��λ��

        if((u8 *)t1 == Rx1Buf + BUF1_LEN) 			   		   //  �ж��Ƿ񵽻�����ĩβ
		{
            t1 = Rx1Buf;	                                   //  �����������ĩβ,�򷵻ػ�����ͷ

		}
        if((u8 *)t1 == (u8 *)outRx1Buf)						   //  ������,˵������������,RxBuf Full
        {
            

          
        }

        *inRx1Buf = USART_ReceiveData(USART1);
        inRx1Buf  = t1;
    }
    /*���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ��� �������������жϵ�����*/
    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART1,USART_FLAG_ORE);
        USART_ReceiveData(USART1);
    }
}

/*usart1*/
void USART2_IRQHandler(void)
{
    unsigned char *t2;										   //  *t1 �¶���ָ�룬ָ��Buf1

    if(USART_GetITStatus(USART2, USART_IT_RXNE)==SET)		   //  �жϣ�һ�����յ�����
    {
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);		   //  ����жϱ�־λ

        rcv_usart2_str_flag=1;					               //  �������ݽ��ձ�־��1
        rcv_usart2_over_count=0;			                   //  ÿ��һ�ֽ����������־��0

        t2 = inRx2Buf;							   			   //  ����ָ��,һ��������,һ��������
        (u8 *)t2++;				                               //  ����ָ��λ��

        if((u8 *)t2 == Rx2Buf + BUF2_LEN) 			   		   //  �ж��Ƿ񵽻�����ĩβ
            t2 = Rx2Buf;	                                   //  �����������ĩβ,�򷵻ػ�����ͷ

        if((u8 *)t2 == (u8 *)outRx2Buf)						   //  ������,˵������������,RxBuf Full
        {
           

            /*���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ��� �������������жϵ�����*/
            if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
            {
                USART_ClearFlag(USART2,USART_FLAG_ORE);	//��SR
                USART_ReceiveData(USART2);				//��DR
            }
        }

        *inRx2Buf = USART_ReceiveData(USART2);
        inRx2Buf  = t2;
    }
    /*���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ��� �������������жϵ�����*/
    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART2,USART_FLAG_ORE);
        USART_ReceiveData(USART2);
    }
}



/*tim2*/
void TIM2_IRQHandler(void)
{
	static u8  s_count = 0; 
	static u16 u16SubCounter    =0;
	static u16 u16Tim_flg_200ms =0;
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);


	   if(CPU_DOG) IWDG_ReloadCounter();  /*ιSTM32����Ӳ����*/
	   if(Sys_Dog_start==1)
	   {
	     if((++Sys_Dog_Count)>3000)	           /*��system  DOG 3000ms over*/
         {
		  Sys_Dog_Count=0;
		  if(CPU_DEBUG) USART1_Put_String("[system info]:system  DOG 3000ms over=:( \r\n");			  
          *((u32*)0xE000ED0C)=0x05fa0004; /*ϵͳ��λ*/ 
         }
	   }

	


		if(++u16SubCounter >1000)
		{
			u16SubCounter = 0;
			time_1000ms=1;								   //  1sʱ�䵽

		}

        if(rcv_usart1_str_flag)					           //  �����˴�������
        {
            if(rcv_usart1_over_count < 2)
            {
                rcv_usart1_over_count++;			       //  2ms���ڽ��ս���
            }
            else
            {
                rcv_usart1_str_flag=0;
                rcv_usart1_end_flag=1;				       //  ��λ���rcv_end_flag
            }
        }


        if(rcv_usart2_str_flag)					           //  �����˴�������
        {
            if(rcv_usart2_over_count < 2)
            {
                rcv_usart2_over_count++;			       //  2ms���ڽ��ս���
            }
            else
            {
                rcv_usart2_str_flag=0;
                rcv_usart2_end_flag=1;				       //  ��λ���rcv_end_flag
            }
        }
		u16Tim_flg_200ms++;
		if(u16Tim_flg_200ms==200)
		{
		  u16Tim_flg_200ms=0;
		  LED_Green_FLASH();
		}
      
        
       if (++s_count >= 10)  
       {  
          s_count = 0;  
          g_RunTime++;    /* ȫ������ʱ��ÿ10ms��1 */  
          if (g_RunTime == 0x80000000)  
          {  
             g_RunTime = 0;  
          }         

       }  



    }
}



void HardFault_Handler(void)
{
    *((u32 *)0xE000ED0C) = 0x05FA0004;
 
}
void BusFault_Handler(void)
{
    *((u32 *)0xE000ED0C) = 0x05FA0004;
}
void UsageFault_Handler(void)
{
    *((u32 *)0xE000ED0C) = 0x05FA0004;
}
