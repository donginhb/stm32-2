/*
 * File:        uart.c
 * Purpose:     Provide common UART routines for serial IO
 *
 * Notes:       
 *              
 */

#include "common.h"
#include "uart.h"




//volatile struct UART_MemMap *UARTx[6]={UART0_BASE_PTR,UART1_BASE_PTR,UART2_BASE_PTR,UART3_BASE_PTR,UART4_BASE_PTR,UART5_BASE_PTR}; //�������ָ�����鱣�� UARTx �ĵ�ַ


/********************************************************************/
/*
 * Initialize the UART for 8N1 operation, interrupts disabled, and
 * no hardware flow-control
 *
 * NOTE: Since the UARTs are pinned out in multiple locations on most
 *       Kinetis devices, this driver does not enable UART pin functions.
 *       The desired pins should be enabled before calling this init function.
 *
 * Parameters:
 *  uartch      UART channel to initialize
 *  sysclk      UART module Clock in kHz(used to calculate baud)
 *  baud        UART baud rate
 */
void uart_init (UART_MemMapPtr uartch, int sysclk, int baud)
{
    register uint16 sbr, brfa;
    uint8 temp;
    
	/* Enable the clock to the selected UART */    
    if(uartch == UART0_BASE_PTR)
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
    else
    	if (uartch == UART1_BASE_PTR)
			SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
    	else
    		if (uartch == UART2_BASE_PTR)
    			SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
    		else
    			if(uartch == UART3_BASE_PTR)
    				SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
    			else
    				if(uartch == UART4_BASE_PTR)
    					SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;
    				else
    					SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;
                                
    /* Make sure that the transmitter and receiver are disabled while we 
     * change settings.
     */
    UART_C2_REG(uartch) &= ~(UART_C2_TE_MASK
				| UART_C2_RE_MASK );

    /* Configure the UART for 8-bit mode, no parity */
    UART_C1_REG(uartch) = 0;	/* We need all default settings, so entire register is cleared */
    
    /* Calculate baud settings */
    sbr = (uint16)((sysclk*1000)/(baud * 16));
        
    /* Save off the current value of the UARTx_BDH except for the SBR field */
    temp = UART_BDH_REG(uartch) & ~(UART_BDH_SBR(0x1F));
    
    UART_BDH_REG(uartch) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
    UART_BDL_REG(uartch) = (uint8)(sbr & UART_BDL_SBR_MASK);
    
    /* Determine if a fractional divider is needed to get closer to the baud rate */
    brfa = (((sysclk*32000)/(baud * 16)) - (sbr * 32));
    
    /* Save off the current value of the UARTx_C4 register except for the BRFA field */
    temp = UART_C4_REG(uartch) & ~(UART_C4_BRFA(0x1F));
    
    UART_C4_REG(uartch) = temp |  UART_C4_BRFA(brfa);    

    /* Enable receiver and transmitter */
	UART_C2_REG(uartch) |= (UART_C2_TE_MASK
				| UART_C2_RE_MASK );
}
/********************************************************************/
/*
 * Wait for a character to be received on the specified UART
 *
 * Parameters:
 *  channel      UART channel to read from
 *
 * Return Values:
 *  the received character
 */
char uart_getchar (UART_MemMapPtr channel)
{
    /* Wait until character has been received */
    while (!(UART_S1_REG(channel) & UART_S1_RDRF_MASK));
    
    /* Return the 8-bit data from the receiver */
    return UART_D_REG(channel);
}
/********************************************************************/
/*
 * Wait for space in the UART Tx FIFO and then send a character
 *
 * Parameters:
 *  channel      UART channel to send to
 *  ch			 character to send
 */ 
void uart_putchar (UART_MemMapPtr channel, char ch)
{
    /* Wait until space is available in the FIFO */
    while(!(UART_S1_REG(channel) & UART_S1_TDRE_MASK));
    
    /* Send the character */
    UART_D_REG(channel) = (uint8)ch;
 }
/********************************************************************/
/*
 * Check to see if a character has been received
 *
 * Parameters:
 *  channel      UART channel to check for a character
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */
int uart_getchar_present (UART_MemMapPtr channel)
{
    return (UART_S1_REG(channel) & UART_S1_RDRF_MASK);
}
/********************************************************************/
 


/*******���õ�UART�жϣ�����isr.h��ճ��һ�´���:*********

//UARTģ���жϷ�����
#undef  VECTOR_061
#define VECTOR_061 LPLD_UART_Isr
#undef  VECTOR_063
#define VECTOR_063 LPLD_UART_Isr
#undef  VECTOR_065
#define VECTOR_065 LPLD_UART_Isr
#undef  VECTOR_067
#define VECTOR_067 LPLD_UART_Isr
#undef  VECTOR_069
#define VECTOR_069 LPLD_UART_Isr
#undef  VECTOR_071
#define VECTOR_071 LPLD_UART_Isr
//���º�����LPLD_Kinetis�ײ���������޸�
extern void LPLD_UART_Isr(void);

***********************************************************/





UART_ISR_CALLBACK UART_R_ISR[6];  //�û������жϺ�����ڵ�ַ����
UART_ISR_CALLBACK UART_T_ISR[6];  //�û������жϺ�����ڵ�ַ����

//UARTӳ���ַ����
volatile UART_MemMapPtr UARTx_Ptr[5] = {UART0_BASE_PTR, 
                                        UART1_BASE_PTR, 
                                        UART2_BASE_PTR, 
                                        UART3_BASE_PTR, 
                                        UART4_BASE_PTR};



/******************************һ��Ϊ�Լ���ӵĳ���************************************************/
/*************************************************************************

*
*  �������ƣ�uart_irq_EN
*  ����˵���������ڽ����ж�
*  ����˵����UARTn       ģ��ţ�UART0~UART5��;UART_NUM,������ţ�0��5
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/
void uart_irq_EN(UART_MemMapPtr channel,uint8 UART_NUM)
{
    UART_C2_REG(channel)|=UART_C2_RIE_MASK;      //����UART�����ж�
    enable_irq((UART_NUM<<1)+45);			            //���������ŵ�IRQ�ж�
}


/*************************************************************************

*
*  �������ƣ�uart_irq_DIS
*  ����˵�����ش��ڽ����ж�
*  ����˵����UARTn       ģ��ţ�UART0~UART5��;UART_NUM,������ţ�0��5
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/
void uart_irq_DIS(UART_MemMapPtr channel,uint8 UART_NUM)
{
    UART_C2_REG(channel)&=~UART_C2_RIE_MASK;     //��ֹUART�����ж�
    disable_irq((UART_NUM<<1)+45);			            //�ؽ������ŵ�IRQ�ж�
}



/*************************************************************************
*  
*  �������ƣ�USART3_IRQHandler
*  ����˵��������1 �ж� ���� ������
*  ����˵������   
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*  ��    ע��
*************************************************************************/
void USART3_IRQHandler(void)
{
    uint8 data=0;
    
    DisableInterrupts;		    //�����ж�
    
    //����һ���ֽ����ݲ��ط�
    data=uart_getchar (UART3_BASE_PTR);                //���յ�һ������
    printf("\n�㷢�͵�����Ϊ��%c",data);      //���ͳ�ȥ
 
    
    EnableInterrupts;		    //�����ж�
}