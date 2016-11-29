//file: printer_mem.c
#include "stm32f10x_lib.h"
#include "includes.h"

 void bmemcpy(u8 *dst , u8  *src , u16 size)
{
	u8 *tdst = dst;
	u8 *tsrc = src;
	u16 i ;
	for ( i = 0 ; i < size ; i ++)
		*(tdst++) = *(tsrc++);
	
}
void bmemset(u8 *dst , u8 data , u16 size )
{
	u8 *tdst = dst;
	u16 i ;
	for ( i = 0 ; i < size ; i ++)
		*(tdst++) = data ;
	
}

