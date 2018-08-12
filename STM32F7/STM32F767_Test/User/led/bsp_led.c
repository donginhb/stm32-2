#include "./led/bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef  GPIO_InitStruct;

		/*����LED��ص�GPIO����ʱ��*/

		LED4_GPIO_CLK_ENABLE();

    /*�������ŵ��������Ϊ�������*/
		GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;  
    
    /*��������Ϊ����ģʽ��Ĭ��LED��*/
    GPIO_InitStruct.Pull  = GPIO_PULLUP;

		/*������������Ϊ���� */   
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH; 

		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStruct.Pin = LED4_PIN;	
    HAL_GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStruct);	
			
		/*ָʾ��D1Ĭ�Ϲر�*/
		LED4(OFF);
		
}
/*********************************************END OF FILE**********************/
