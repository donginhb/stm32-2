/*
 * File:        sysinit.c
 * Purpose:     Kinetis Configuration
 *              Initializes processor to a default state
 *
 * Notes:
 *
 */

#include "common.h"
#include "sysinit.h"
#include "uart.h"

/********************************************************************/

/* Actual system clock frequency */
int core_clk_khz;   //�ں�ʱ��(KHz)
int core_clk_mhz;   //�ں�ʱ��(MHz)
int periph_clk_khz;  //��Χ����ʱ��

/********************************************************************/
void sysinit (void)
{
        /*
         * Enable all of the port clocks. These have to be enabled to configure
         * pin muxing options, so most code will need all of these on anyway.
         */
        /* ʹ�����ж˿�PORTʱ��   */
  
        SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
                      | SIM_SCGC5_PORTB_MASK
                      | SIM_SCGC5_PORTC_MASK
                      | SIM_SCGC5_PORTD_MASK
                      | SIM_SCGC5_PORTE_MASK );

#if defined(NO_PLL_INIT)       //������岻��ʼ�����໷������� FEI mode
          core_clk_mhz = 21; //FEI mode
#else 
 	/* Ramp up the system clock */
	core_clk_mhz = pll_init(CORE_CLK_MHZ, REF_CLK);
#endif

	/*
         * Use the value obtained from the pll_init function to define variables
	 * for the core clock in kHz and also the peripheral clock. These
	 * variables can be used by other functions that need awareness of the
	 * system frequency.
	 */
        
        //ͨ��pll_init�����ķ���ֵ�������ں�ʱ�Ӻ�����ʱ�ӣ��������������ɲ�ѯʱ��Ƶ��
        
	core_clk_khz = core_clk_mhz * 1000;
  	periph_clk_khz = core_clk_khz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> 24)+ 1);

  	/* For debugging purposes, enable the trace clock and/or FB_CLK so that
  	 * we'll be able to monitor clocks and know the PLL is at the frequency
  	 * that we expect.
  	 */
	trace_clk_init();    //ʹ�ܸ���ʱ�ӣ����ڵ���
  	fb_clk_init();         //FlexBusʱ�ӳ�ʼ��

  	/* Enable the pins for the selected UART */
        
         //��ʼ�� printf �������õ��Ĵ���
        
        //�ҵ�TERM_PORT�ĺ궨��λ�ã��Ϳ������ù�������
        
         
       

  	

  	
  	/* UART0 and UART1 are clocked from the core clock, but all other UARTs are
         * clocked from the peripheral clock. So we have to determine which clock
         * to send to the uart_init function.
         */
    //    if ((TERM_PORT == UART0_BASE_PTR) | (TERM_PORT == UART1_BASE_PTR))  //���㲨���ʣ�����0��1ʹ���ں�ʱ�ӣ���������ʹ������ʱ��
    //        uart_init (TERM_PORT, core_clk_khz, TERMINAL_BAUD);
    //    else
    //	    uart_init (TERM_PORT, periph_clk_khz, TERMINAL_BAUD); //��ʼ��ʹ�ô��ڵ�ͨ�Ų�����
}
/********************************************************************/
void trace_clk_init(void)
{
	/* Set the trace clock to the core clock frequency */
	SIM_SOPT2 |= SIM_SOPT2_TRACECLKSEL_MASK;

	/* Enable the TRACE_CLKOUT pin function on PTA6 (alt7 function) */
	PORTA_PCR6 = ( PORT_PCR_MUX(0x7));
}
/********************************************************************/
void fb_clk_init(void)
{
	/* Enable the clock to the FlexBus module */
        SIM_SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;

 	/* Enable the FB_CLKOUT function on PTC3 (alt5 function) */
	PORTC_PCR3 = ( PORT_PCR_MUX(0x5));
}
/********************************************************************/
