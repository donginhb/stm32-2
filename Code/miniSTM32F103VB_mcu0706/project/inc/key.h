//file
#ifndef __KEY_H
#define __KEY_H

#if (KEY_EN>0) ||(SERVO_POS_CTR_EN>0)||(LOAD_PAPER_EN>0)
extern void Init_KeyPosPMTime(void);
#endif

#if KEY_EN>0
//*--------key value list-------------------------------------
//--connect-------------------------------------------------
//KEY_PIN0	KEY_PIN1	KEY_PIN2	KEY_PIN3	KEY_PIN4	KEY_PIN5	KEY_PIN6	KEY_PIN7
/*-------------------------------------------------
*KEY_PIN3	KEY_PIN2	KEY_PIN4	KEY_PIN5	KEY_PIN6	KEY_PIN7
*	|			|			|			|			|			|
*	/			/-----------|			|			|			|
*	/			/-----------------------|			|			|			
*	/			/-----------------------------------|			|			
*	/			/-----------------------------------------------|	
------------------------------------------------------------------------
*KEY_LEFT1			KEY_RIGHT1
*KEY_LEFT2			KEY_RIGHT2
*KEY_LEFT3			KEY_RIGHT3
*KEY_LEFT4			KEY_RIGHT4
*
--------------------------------------------------*/
#define KEY_LEFT0  	0x43
#define KEY_LEFT1	0x53
#define KEY_LEFT2	0x63
#define KEY_LEFT3	0x73

#define KEY_RIGHT0 	0x42
#define KEY_RIGHT1	0x52
#define KEY_RIGHT2 	0x62
#define KEY_RIGHT3	0x72
#define KEY_NULL	0x00

//**EER maro***************************
#define 	ERR_KEYVALUE 	(u8)(0x7f)

extern u8  Key_ValGet(void);

//extern  void Key_NVICInit( void ) ;
extern void Init_Key( void );

//extern u8  KeyScan( void );
extern void Key_ValClear(void);
extern void  KeyScanBack(void);

#endif //#if KEY_EN>0

#endif //__KEY_H


