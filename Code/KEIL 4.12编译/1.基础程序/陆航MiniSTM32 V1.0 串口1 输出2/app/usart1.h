#include "stm32f10x.h"
#include <stdio.h>
void ConfigurationUsart1(void);
int fputc(int ch, FILE *f);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
