#ifndef __UART_H
#define __UART_H

//#define UART_BUAD                            115200



//#define BAUD 0xE800 // 1200bps @ 22.11 84MHz
//#define BAUD 0xF400 // 2400bps @ 22.11 84MHz
//#define BAUD 0xFA00 // 4800bps @ 22.11 84MHz
#define BAUD 0xFD00 // 9600bps @ 22.11 84MHz
//#define BAUD 0xFE80 //19200bps @ 22.11 84MHz
//#define BAUD 0xFF40 //38400bps @ 22.11 84MHz
//#define BAUD 0xFF80 //57600bps @ 22.11 84MHz   //设置通信波特率

void uartInit(void);
//void uartSendData(u8 ucData);
//void uartSendString(char *s);

#endif