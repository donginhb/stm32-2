//fpga_driver.h
#ifndef __FPGA_DRIVER_H
#define __FPGA_DRIVER_H


#if FPGA_DRIVER_EN > 0

#define DATA_BUS_WRITE_MODE 1
#define DATA_BUS_READ_MODE   0
extern u8 FPGA_ReadByteData( u8  addr  );
extern void FPGA_WriteByteData( u8  addr ,u8 nByte );
extern void FPGA_WriteData( u16 nWord , u8 Addr);
//extern void Init_FpgaGpio( void );
extern void FPGA_Test(void);
#endif//#if FPGA_DRIVER_EN > 0

#endif //__FPGA_DRIVER_H
