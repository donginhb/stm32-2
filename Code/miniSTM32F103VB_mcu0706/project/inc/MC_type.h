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
/*���˿��ƹ���״̬*/
typedef enum{	
	S_INIT,
	S_START, 
	S_SPEEDUP,
	S_RUN, 
	S_SPEEDDOWN,
	S_STOP, 
	S_DIR,/*����*/
	S_BRAKE, 
	S_WAIT, 
	S_FAULT
} ServoSpeedtStatus_t;

/*�˶�ģʽ*/
typedef enum{	
	SPORT_FIND_ORIGIN, 		/*��ԭ��*/
	SPORT_MEA_RASTER_LEN, 	 /*���դ�ܳ���*/	
	SPORT_MEA_PAPER_WITH,	/*����ֽ��*/
	SPORT_PASS_PRINT,			/*��ī*/
	SPORT_ODD  ,		/*�����ӡ*/
       SPORT_EVEN ,	 	/*˫���ӡ*/
	SPORT_PUMP_INK, 	/*��ī*/
	SPORT_CUT_PAPER, 	/*��ֽ*/
	SPORT_FAULT,		/*����*/
	SPORT_WAIT,	 	/*�ȴ�ģʽ*/
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

/*�˶�ģʽ*/
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
 	 s16 Kp;/*������ϵ��*/
	  s16 Ki;/*������ϵ��*/
	  
#ifdef SPEED_DIFFERENTIAL_TERM_ENABLED
	  s16 Kd;/*΢����ϵ��*/
#endif

	volatile	s16 Ka;		/*Ek ϵ��*/
	volatile	s16 Kb;		/*Ek-1 ϵ��*/  
	#ifdef SPEED_DIFFERENTIAL_TERM_ENABLED
	volatile	s16 Kc;		/*Ek-2 ϵ��*/
	#endif

 //   volatile s16 PV_Per;                  /*���̱���,δ������ֵ*/
 //   volatile s16 PV;                        /*���������ֵ*/
 //   volatile s16 Mn;                        /*���ֵ*/
//    volatile s16 Kc;                        /*����*/
//    volatile s16 Ts;                        /*����ʱ��*/
//    volatile s16 Ti;                        /*����ʱ��*/
//    volatile s16 Td;                        /*΢��ʱ��*/
//    volatile s16 SegmaE;                    /*ƫ���*/	
//	volatile	bool Max_PID_Output;    // 
//	volatile	bool Min_PID_Output;	
	
	volatile	s16 IErr;		/*������*/
	volatile	s16 PErr;	/*������*/ 
	volatile	s16 DErr;	/*΢����*/	
#endif

typedef struct
{
		s16 DstRef;/*���ٶ�*/
		s16 Kp; /*������ϵ��*/
		s16 Ki; /*������ϵ��*/	
		
#ifdef SPEED_DIFFERENTIAL_TERM_ENABLED
		s16 Kd;/*΢����ϵ��*/
#endif	
		//s16 Ks; /*�ٶ����ֵת��Ϊpwmռ�ձȱ���ϵ��*/
//		s16  RefTargetVal;/*��λ: ת/10�룬Ŀ��ֵ����ӡ�����ٶ� , ��ʱReference == RefTargetVal*/
		s16 Lower_Limit_Err ;     /*Lower Limit for Output limitation*/
		s16 Upper_Limit_Err ;     /*Lower Limit for Output limitation*/
		//bool Max_PID_Output ;
	       //bool Min_PID_Output ;
		bool PID_Reg_Use;
		bool PID_Reg_EN;	/*pid�Զ����ڱ�־λ*/
		s16 SrcRef;
		s16 StaRef;			 /*�����ٶ�*/
		s16 CurRef ;			/**/
		s16 EndRef ;			/*�����ٶ�*/
		s16 Reference; 		/*��λ: �趨ֵ, ��Ҫ���ڼ������ı��ֵ������Reference == RefTargetVal*/ 	
		s16 KISum;
		u8 PidSimapleTime;		/*pid �ٶȵ��ڷ���ʱ��*/
		u8 SpeedSimapleTime;	/*�ٶȲ�������ʱ��*/
}PID_SpeedTYPEDEF;


typedef struct{	
	u16 SpeedStartRef ; 			//50rec /10s , min set speed ,300rec/m, �����ٶ�
	u16 SpeedStartDuty;
	u16 SpeedDutyCur;	
	u16 SpeedDutyDst;			/*Ŀ��*/	
	u16 SpeedDutyUpCur;
	u16 SpeedDutyUpDst;
	u16 SpeedDutyDownCur;
	u16 SpeedDutyDownDst;
	u16 SpeedStepDownBase;		/*���ٶ�: /simple_TIME*/
	u16 SpeedStepUpBase;		/*���ٶ�: /simple_TIME*/
	u16 SpeedStepDutyDownBase;	/*���ٶ�: /simple_TIME*/
	u16 SpdStepDutyDownScale;  
	u16 SpeedStepDutyUpBase;	/*���ٶ�: /simple_TIME*/
	u16 SpdStepDutyUpScale;		/*������ֵ���Ըı��趨��Ŀ���ٶ�ƥ��*/
	u16 SpdStepDutyCntScale;		/*ȥ�˵㣬pid�Զ����ڱ���ϵ��*/
	u16 SpdStepDutyCntGoFarScale;	/*ȥԶ�˵㣬pid�Զ����ڱ���ϵ����˫���ӡʱ��*/
	u16 SpdStepDutyCntGoNearScale;	/*ȥ���˵㣬pid�Զ����ڱ���ϵ���� ˫���ӡʱ��*/
	u16 SpeedStepDutyBase;		/*���ٶȶ�Ӧ��ռ�ձ���*/
	u8 TimeNmsSetpBase;		/*ÿ�μ��ټ��ʱ��: ms*/
	u8 SpeedStepUpNum ;		/*�ﵽ�û��趨����Ҫ�Ĳ���down*/
	u8 SpeedStepUpNumTmp ;	/*�ﵽ�û��趨����Ҫ�Ĳ�����ʱ����*/
	u8 SpeedStepDownNum ;		/*�ﵽ�û��趨����Ҫ�Ĳ���down*/
	u8 SpeedStepDownNumTmp ;	/*�ﵽ�û��趨����Ҫ�Ĳ�����ʱ����*/
	u16 StepNum ;
	u8 SpeedDutyScale ; /*Ŀ��ռ�ձ�*/
	u16 RunLen;			/*���������ߵĳ���*/
	u16 AccSpdNear;		/*���˵���ٶ�*/
	u16 AccSpdFar;		/*Զ�˵���ٶ�*/
	u16 DecSpdNear; 	/*���˵���ٶ�*/
	u16 DecSpdFar;		/*Զ�˵���ٶ�*/
	u16 Counter ; 		/*���̼�����*/
	//ServoSpeedtStatus_t ServoSpeedStatus;	/*�ŷ��˶�״̬*/
	bool ServoSpeedCtrUse;	
	/*Զ�������Զ����� ��ǣ��Զ�ģʽ: S_INIT-->S_Sartup-->S_SPEEDUP-->S_RUN-->S_SPEEDDOWN-->S_STOP*/
	bool ServpSpeedCtrModeAutoFlag;
}ServoSpeedCtr_t;

/*ī��˫���˶��е�״̬**/
typedef enum{
	PS_PAUSE, 		/*��ͣ��ӡ*/
	PS_CANSE, 		/*ȡ����ӡ*/
	PS_CONTINUE ,	/*������ӡ*/
	PS_RUN, 		/*��ӡ��*/
	PS_END 			/*��ӡ����*/
}PrintStatus_t;
typedef struct{	
	u16 DistanceRefNearToFar ;	/*N --> Far  ����(���-->ͣ��)*/
	u16 DistanceRefFarToNear ; 	/* F --> N  ����(���-->ͣ��)*/
	u16 OnePassDistance;		/*���˾����ľ���*/
	u16 PictureWith;				/*����ͼ��Ŀ��*/
	u16 FarErr ;					/*Զ�˵㲹��*/
	u16 NearErr;					/*���˵㲹��*/	
	u16 RasterLen; 		/*------��դ�ܸ���*4    ----*/
	s16 CurPos;			/*--ī����ǰ��λ��--*/	
	s16 StartPos;		/*ī������λ��*/
	s16 PassLen;
	//u16 PriOrigin; /*��ӡԭ��*/
	u16 SafeDisFar;		/*��ֹײ����Զ�˵㣬�˵�Ϊ�ް�ȫ�ٶ�ͨ����*/
	u16 SafeDisNear; 	/*��ֹײ�������˵㣬�˵�Ϊ�ް�ȫ�ٶ�ͨ����*/
	
	u16 CnstSpdNear;	/*���ٽ��˵�*/
	u16 CnstSpdFar;		/*����Զ��*/
	
	u16 DecSpdNear; 	 /*���ٽ��˵�*/
	u16 DecSpdFar;	 	/*����Զ�˵�*/
	
	//u16 BrakeNear;		/*����ɲ����*/
	///	u16 BrakeFar;		/*Զ��ɲ����*/
	u16 PriPicToPriOriginLen;		/*��ī��ʼ�㵽��ӡԭ�����*/
	u16 PriPicToPaperEdgeLen;	/*��ī��ʼ�㵽��ӡԭ�����*/
	u16 SpdDecL;		/*�������򳤣��ٶȴ�С�����������*/
	u16 SpdIncL;			/*�������򳤣��ٶȴ�С�����������*/	
	u16 BrakeL; 			/*ɲ������*/
	u16 PrintOriginLen;	 /*��ӡԭ��,��ɲ�������*/
	u16 PaperEdgeErr;
	SportMode_t SportMode;
	SevroDir  Dir;			/*--�ŷ���ǰ�ķ���---*/
	PriPassMode_t  PassMode;
	SpdMode_t SpdMode;
	PrintStatus_t PrintStatus;
}ServoCarPosCtr_t;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MC_TYPE_H */
/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
