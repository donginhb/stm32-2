//file://MC_servo_speed_ctr.h
#ifndef __MC_SERVO_SPEED_CTR
#define __MC_SERVO_SPEED_CTR
extern bool PosOutDataUpdataFlag ;
extern u16 PosOutData[10] ;

enum{
	P_START = 0 , /*启动点*/
	P_END,		/*停止点位置*/
	P_L,			/*所走距离度*/
	P_CntSpdNear,  	 /*恒速近端点*/
	P_CntSpdFar,  	/*恒速远端点*/
};
typedef enum{
	S_HIGH,
	S_MID,
	S_LOW,
}Speed_HML_Mode;

typedef enum{
	S_GO_ORIGIN,		/*找原点速度*/
	S_MEA_RASTER_LEN,	/*测量光栅总长速度*/
	S_MEA_PAPER,		/*测纸宽速度*/
	S_GO_INK_STOP,		 /*归墨站*/
	S_PASS_PRI,
	S_PASS1,
	S_PASS2,
	S_PASS3,
	S_PASS4,
	S_PASS5,
	S_FATE,			/*安全速度,即使撞到两端也无碍*/
	S_MEA_PAPER_DOWN,	/*测纸停车*/
	S_GO_INK_STOP_DOWN,	/*去墨站停车*/
	
}PrintSpeedSetMode;

extern void MC_SpdCarParaInit( void );
extern bool MC_SpdCarStartup( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed )   ;
extern bool MC_SpdCarStop( void ) ;
extern bool MC_SpdCarSpdup( ServoSpeedCtr_t  *ServoSCP, PID_SpeedTYPEDEF *PID_Speed )  ;
extern bool MC_SpdCarSpddown( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed );
extern bool MC_SpdCarStartSpdup( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed ) ;
extern bool MC_SpdCarSpddownStop( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed ) ;

extern bool MC_SpdCarAvoidBumpCar(ServoCarPosCtr_t  *CarPos );
extern bool MC_SpdCarCtr( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos  );
extern void MC_SpdCarSpdSet(PID_SpeedTYPEDEF *PID_Speed , PrintSpeedSetMode SpeedMode );
extern void MC_SpdCarDirSet(ServoCarPosCtr_t  *CarPos  , SevroDir Dir );

extern void MC_SpdCarSafeSpd( ServoSpeedCtr_t  *ServoSCP , PID_SpeedTYPEDEF *PID_Speed , ServoCarPosCtr_t  *CarPos  );
#if 0
extern s16 MC_SpdCarPosCurGet(void);
extern s16 MC_SpdCarPosStartGet(void);
extern s16 MC_SpdCarLGet(void);

#endif

extern void MC_SpdCtrModeAutoFun( FunctionalState NewState );

#endif //__MC_SERVO_SPEED_CTR

