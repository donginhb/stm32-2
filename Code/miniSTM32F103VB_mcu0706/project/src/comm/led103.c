//file: led.c

#include "includes.h"

/*******************************************************************************
* Function Name  : Init_LedGpio
* Description    : 
* Input             : 			    
* Output         : None
* Return         : None
*******************************************************************************/
void Init_LedGpio(void)
{       
          GPIO_InitTypeDef GPIO_InitStructure;
	 //#############################################
	  /* Configure IO connected to LD1, LD2  leds *********************/
	  /* Enable GPIO_LED clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_LED, ENABLE);

	  GPIO_InitStructure.GPIO_Pin = LED_PIN0 | LED_PIN1 ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIO_LED, &GPIO_InitStructure);

	/* Turn off LD1 */
	GPIO_SetBits(GPIO_LED, LED_PIN0);
	/* Turn off LD2 */
	GPIO_SetBits(GPIO_LED, LED_PIN1);	
}
/*******************************************************************************
* Function Name  : Led
* Description    : None
* Input             : None
* Output         : None
* Return         : None
*******************************************************************************/
void Led( u16 ledno , BitAction onoff)
{
	//LEDStatus LS = (LEDStatus) onoff;
	GPIO_WriteBit( GPIO_LED , ledno , onoff  );
}
void LedAutoOnOff( u16 ledno )
{
	//LEDStatus LS = (LEDStatus) onoff;
	GPIO_WriteBit(GPIO_LED, ledno, (BitAction)(1-GPIO_ReadOutputDataBit(GPIO_LED, ledno)));

	//GPIO_WriteBit( GPIO_LED , ledno , onoff  );
}


