
/*-----------------------------------------------------------------------------------------------------------------------------------------------------
*       Çý¶¯ÃüÁîÊ±Ðò²¿·Ö
*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
#define OSC_ON    0x01         // ¿ªÆôÕðµ´Æ÷
#define DISP_ON   0x03         // ¿ªÏÔÊ¾
#define COM_1_3__4       0x29         // 1/3Æ«ÖÃ·½Ê½,4¹«¹²¶Ë
#define BUZZ_OFF  0x08         // ¹Ø±Õ·äÃùÆ÷ 
#define BUZZ_ON   0X09         // ¿ªÆô·äÃùÆ÷
#define BUZZ_2KHZ 0x60//0B01100000   // ·äÃùÆ÷  2k
#define BUZZ_4KHZ 0x40//0B01000000   // ·äÃùÆ÷  4k

//#define RD_H() GPIOB ->ODR |=  GPIO_Pin_3
//#define RD_L() GPIOB ->ODR &= ~GPIO_Pin_3

#define RW_H() GPIOB ->ODR |=  GPIO_Pin_2
#define RW_L() GPIOB ->ODR &= ~GPIO_Pin_2

#define CS_H() GPIOB ->ODR |=  GPIO_Pin_5
#define CS_L() GPIOB ->ODR &= ~GPIO_Pin_5

#define DATA_H() GPIOB ->ODR |=  GPIO_Pin_6
#define DATA_L() GPIOB ->ODR &= ~GPIO_Pin_6

void DisAll(u8 Dat);
