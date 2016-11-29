//file: setpper.h
#ifndef __STEPPER_A3979_H
#define __STEPPER_A3979_H

extern void Stepper_InitA3979(void);
extern void Stepper_ModeSetA3979( SetpperCurMode stm , SetpperDir dir );
extern  void Stepper_SetDirA3979( SetpperDir dir );
extern void Stepper_SetCurA3979( SetpperCurMode  scm );
#endif //__STEPPER_A3979_H

