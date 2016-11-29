//file: ziku.h

#ifndef __ZIKULIB_H
#define __ZIKULIB_H

#include "stm32f10x_lib.h"

//ASCII 字模宽度及高度
#define ASC_CHR_WIDTH	8
#define ASC_CHR_HEIGHT	16

typedef struct  _FNT_ASC816{	/* 汉字字模显示数据结构 */

	u8 Index[1];
	u8 Msk[16];
	
}FNT_ASC816_t ;


//汉字
#define ASC_HZ_WIDTH	16
//#define ASC_HZ_HEIGHT	12

typedef struct  _FNT_HZGB1616	/*12*16 汉字字模显示数据结构 */
{
	u8 Index[2];
	u8 Msk[32];
}FNT_HZGB1616_t;



extern FNT_ASC816_t  const  ASC_816[];
extern FNT_HZGB1616_t  const  HzTable1616[];
//#define HZ_TABLE1616_LEN   	sizeof(HzTable1616)/sizeof(HzTable1616[0])
extern u16 HZTable1616Len ;
//#define ASC_TABLE816_LEN	sizeof(ASC_816)/sizeof(ASC_816[0])
extern u8 ASCTable816Len ;

#endif //__ZIKULIB_H

