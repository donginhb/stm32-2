//mp_out.h
#ifndef __MP_OUT_H
#define __MP_OUT_H

#define  MP_OFF  Bit_RESET 
#define  MP_ON   Bit_SET

extern void Init_Mp(void);
extern void Mp_Fan12(BitAction OnOff);

#ifdef MP_DUB
extern void Mp_test(void);
#endif//#ifdef MP_DUB

#endif//#ifndef __MP_OUT_H

