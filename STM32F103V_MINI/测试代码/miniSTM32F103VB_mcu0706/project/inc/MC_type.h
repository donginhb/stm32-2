/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : MC_type.h
* Author             : IMS Systems Lab 
* Date First Issued  : 21/11/07
* Description        : This header file provides structure type definitions that 
*                      are used throughout this motor control library.
********************************************************************************
* History:
* 21/11/07 v1.0
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MC_TYPE_H
#define __MC_TYPE_H

#include "MC_servo.h"
/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef enum 
{
	 IDLE,
	 INIT,
	 START, 
	 RUN, 
	 STOP, 
	 BRAKE, 
	 WAIT, 
	 FAULT
} SystStatus_t;

typedef enum 
{
	NO_FAULT, 
	OVER_VOLT, 
	UNDER_VOLT
} BusV_t;
/*单趟控制过程状态*/
typedef enum{	
	S_INIT,
	S_START, 
	S_SPEEDUP,
	S_RUN, 
	S_SPEEDDOWN,
	S_STOP, 
	S_DIR,/*换向*/
	S_BRAKE, 
	S_WAIT, 
	S_FAULT
} ServoSpeedtStatus_t;

/*运动模式*/
typedef enum{	
	SPORT_FIND_ORIGIN, 		/*找原点*/
	SPORT_MEA_RASTER_LEN, 	 /*测光栅总长度*/	
	SPORT_MEA_PAPER_WITH,	/*测量纸宽*/
	SPORT_PASS_PRINT,			/*抽墨*/
	SPORT_ODD  ,		/*单向打印*/
       SPORT_EVEN ,	 	/*双向打印*/
	SPORT_PUMP_INK, 	/*抽墨*/
	SPORT_CUT_PAPER, 	/*切纸*/
	SPORT_FAULT,		/*故障*/
	SPORT_WAIT,	 	/*等待模式*/
	SPORT_IDLE,
	
}SportMode_t;

#if 0
typedef enum{
	SPORT_PASS1,
	SPORT_PASS2,
	SPORT_PASS3,
	SPORT_PASS4,
	SPORT_PASS5,
	SPORT_PASS6,
	SPORT_PASS7,
	SPORT_PASS8,
}SportPassMode_t;
#endif

/*运动模式*/
typedef enum{	
	TASK_INIT,
	TASK_RUN,
	TASK_END,	
	TASK_RUN1,
	TASK_RUN2,
	TASK_RUN3,
	TASK_RUN4,
	TASK_RUN5,
	TASK_RUN6,
	TASK_INIT1,
	TASK_INIT2,
}TaskStatus_t;
#if 0
 	 s16 Kp;/*比例项系数*/
	  s16 Ki;/*积分项系数*/
	  
#ifdef SPEED_DIFFERENTIAL_TERM_ENABLED
	  s16 Kd;/*微分项系数*/
#endif

	volatile	s16 Ka;		/*Ek 系数*/
	volatile	s16 Kb;		/*Ek-1 系数*/  
	#ifdef SPEED_DIFFERENTIAL_TERM_ENABLED
	volatile	s16 Kc;		/*Ek-2 系数*/
	#endif

 //   volatile s16 PV_Per;                  /*过程变量,未整定数值*/
 //   volatile s16 PV;                        /*整定后的数值*/
 //   volatile s16 Mn;                        /*输出值*/
//    volatile s16 Kc;                        /*增益*/
//    volatile s16 Ts;                        /*采样时间*/
//    volatile s16 Ti;                        /*积分时间*/
//    volatile s16 Td;                        /*微分时间*/
//    volatile s16 SegmaE;                    /*偏差和*/	
//	volatile	bool Max_PID_Output;    // 
//	volatile	bool Min_PID_Output;	
	
	volatile	s16 IErr;		/*积分项*/
	volatile	s16 PErr;	/*比例项*/ 
	volatile	s16 DErr;	/*微分项*/	
#endif

typedef struct
{
		s16 DstRef;/*匀速度*/
		s16 Kp; /*比例项系数*/
		s16 Ki; /*积分项系数*/	
		
#ifdef SPEED_DIFFERENTIAL_TERM_ENABLED
		s16 Kd;/*微分项系数*/
#endif	
		//s16 Ks; /*速度误差值转化为pwm占空比比例系数*/
//		s16  RefTargetVal;/*单位: 转/10秒，目标值，打印区的速度 , 此时Reference == RefTargetVal*/
		s16 Lower_Limit_Err ;     /*Lower Limit for Output limitation*/
		s16 Upper_Limit_Err ;     /*Lower Limit for Output limitation*/
		//bool Max_PID_Output ;
	       //bool Min_PID_Output ;
		bool PID_Reg_Use;
		bool PID_Reg_EN;	/*pid自动调节标志位*/
		s16 SrcRef;
		s16 StaRef;			 /*启动速度*/
		s16 CurRef ;			/**/
		s16 EndRef ;			/*结束速度*/
		s16 Reference; 		/*单位: 设定值, 主要是在加速区改变此值，最终Reference == RefTargetVal*/ 	
		s16 KISum;
		u8 PidSimapleTime;		/*pid 速度调节反馈时间*/
		u8 SpeedSimapleTime;	/*速度采样反馈时间*/
}PID_SpeedTYPEDEF;


typedef struct{	
	u16 SpeedStartRef ; 			//50rec /10s , min set speed ,300rec/m, 启动速度
	u16 SpeedStartDuty;
	u16 SpeedDutyCur;	
	u16 SpeedDutyDst;			/*目标*/	
	u16 SpeedDutyUpCur;
	u16 SpeedDutyUpDst;
	u16 SpeedDutyDownCur;
	u16 SpeedDutyDownDst;
	u16 SpeedStepDownBase;		/*减速度: /simple_TIME*/
	u16 SpeedStepUpBase;		/*加速度: /simple_TIME*/
	u16 SpeedStepDutyDownBase;	/*减速度: /simple_TIME*/
	u16 SpdStepDutyDownScale;  
	u16 SpeedStepDutyUpBase;	/*加速度: /simple_TIME*/
	u16 SpdStepDutyUpScale;		/*调整此值可以改变设定和目标速度匹配*/
	u16 SpdStepDutyCntScale;		/*去端点，pid自动调节比例系数*/
	u16 SpdStepDutyCntGoFarScale;	/*去远端点，pid自动调节比例系数，双向打印时用*/
	u16 SpdStepDutyCntGoNearScale;	/*去近端点，pid自动调节比例系数， 双向打印时用*/
	u16 SpeedStepDutyBase;		/*加速度对应的占空比数*/
	u8 TimeNmsSetpBase;		/*每次加速间隔时间: ms*/
	u8 SpeedStepUpNum ;		/*达到用户设定所需要的步数down*/
	u8 SpeedStepUpNumTmp ;	/*达到用户设定所需要的步数临时变量*/
	u8 SpeedStepDownNum ;		/*达到用户设定所需要的步数down*/
	u8 SpeedStepDownNumTmp ;	/*达到用户设定所需要的步数临时变量*/
	u16 StepNum ;
	u8 SpeedDutyScale ; /*目标占空比*/
	u16 RunLen;			/*单程匀速走的长度*/
	u16 AccSpdNear;		/*近端点加速度*/
	u16 AccSpdFar;		/*远端点加速度*/
	u16 DecSpdNear; 	/*近端点减速度*/
	u16 DecSpdFar;		/*远端点减速度*/
	u16 Counter ; 		/*过程计数器*/
	//ServoSpeedtStatus_t ServoSpeedStatus;	/*伺服运动状态*/
	bool ServoSpeedCtrUse;	
	/*远动过程自动控制 标记，自动模式: S_INIT-->S_Sartup-->S_SPEEDUP-->S_RUN-->S_SPEEDDOWN-->S_STOP*/
	bool ServpSpeedCtrModeAutoFlag;
}ServoSpeedCtr_t;

/*墨车双向运动中的状态**/
typedef enum{
	PS_PAUSE, 		/*暂停打印*/
	PS_CANSE, 		/*取消打印*/
	PS_CONTINUE ,	/*继续打印*/
	PS_RUN, 		/*打印中*/
	PS_END 			/*打印结束*/
}PrintStatus_t;
typedef struct{	
	u16 DistanceRefNearToFar ;	/*N --> Far  距离(起点-->停车)*/
	u16 DistanceRefFarToNear ; 	/* F --> N  距离(起点-->停车)*/
	u16 OnePassDistance;		/*单趟经过的距离*/
	u16 PictureWith;				/*所打图像的宽度*/
	u16 FarErr ;					/*远端点补偿*/
	u16 NearErr;					/*近端点补偿*/	
	u16 RasterLen; 		/*------光栅总格数*4    ----*/
	s16 CurPos;			/*--墨车当前的位置--*/	
	s16 StartPos;		/*墨车启动位置*/
	s16 PassLen;
	//u16 PriOrigin; /*打印原点*/
	u16 SafeDisFar;		/*防止撞车，远端点，此点为限安全速度通过点*/
	u16 SafeDisNear; 	/*防止撞车，近端点，此点为限安全速度通过点*/
	
	u16 CnstSpdNear;	/*恒速近端点*/
	u16 CnstSpdFar;		/*恒速远点*/
	
	u16 DecSpdNear; 	 /*减速近端点*/
	u16 DecSpdFar;	 	/*减速远端点*/
	
	//u16 BrakeNear;		/*近端刹车点*/
	///	u16 BrakeFar;		/*远端刹车点*/
	u16 PriPicToPriOriginLen;		/*喷墨起始点到打印原点距离*/
	u16 PriPicToPaperEdgeLen;	/*喷墨起始点到打印原点距离*/
	u16 SpdDecL;		/*减速区域长，速度大小决定这个长度*/
	u16 SpdIncL;			/*加速区域长，速度大小决定这个长度*/	
	u16 BrakeL; 			/*刹车距离*/
	u16 PrintOriginLen;	 /*打印原点,到刹车点距离*/
	u16 PaperEdgeErr;
	SportMode_t SportMode;
	SevroDir  Dir;			/*--伺服当前的方向---*/
	PriPassMode_t  PassMode;
	SpdMode_t SpdMode;
	PrintStatus_t PrintStatus;
}ServoCarPosCtr_t;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MC_TYPE_H */
/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
