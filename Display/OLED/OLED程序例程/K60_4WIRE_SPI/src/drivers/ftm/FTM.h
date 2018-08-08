/**************************************************************************************
 * �ļ���       ��FTM.h
 * ����         ������PWM�����벶׽��������ͷ�ļ�
 *
**********************************************************************************/

#ifndef _ftm_H
#define _ftm_H

extern volatile struct FTM_MemMap *FTMx[3];

typedef enum FTMn
{
    FTM0,
    FTM1,
    FTM2
} FTMn;

typedef enum CHn
{
    
    CH0,   
    CH1,   
    CH2,   
    CH3,  
    CH4,  
    CH5,   
    CH6,   
    CH7    
    // ����ʾ������
} CHn;



/**********************************  FTM    ***************************************/

//      ģ��ͨ��    �˿�          ��ѡ��Χ             
#define FTM0_CH0    PTC1        //PTC1��PTA3            PTA3��Ҫ�ã���Jtag��SWD��ͻ��
#define FTM0_CH1    PTC2        //PTC2��PTA4
#define FTM0_CH2    PTC3        //PTC3��PTA5
#define FTM0_CH3    PTC4        //PTC4��PTA6
#define FTM0_CH4    PTD4        //PTD4��PTA7
#define FTM0_CH5    PTD5        //PTD5��PTA0            PTA0��Ҫ�ã���Jtag��SWD��ͻ��
#define FTM0_CH6    PTD6        //PTD6��PTA1            PTA1��Ҫ�ã���Jtag��ͻ��
#define FTM0_CH7    PTD7        //PTD7��PTA2            PTA2��Ҫ�ã���Jtag��ͻ��


//      ģ��ͨ��    �˿�          ��ѡ��Χ             
#define FTM1_CH0    PTB0        //PTA8��PTA12��PTB0
#define FTM1_CH1    PTB1        //PTA9��PTA13��PTB1
/*
#define FTM1_CH2                //��
#define FTM1_CH3                //��
#define FTM1_CH4                //��
#define FTM1_CH5                //��
#define FTM1_CH6                //��
#define FTM1_CH7                //��
*/

//      ģ��ͨ��    �˿�          ��ѡ��Χ             
#define FTM2_CH0    PTA10       //PTA10��PTB18
#define FTM2_CH1    PTA11       //PTA11��PTB19
/*
#define FTM2_CH2                //��
#define FTM2_CH3                //��
#define FTM2_CH4                //��
#define FTM2_CH5                //��
#define FTM2_CH6                //��
#define FTM2_CH7                //��
*/







/**********************************  FTM    ***************************************/

//      ģ��ͨ��    �˿�          ��ѡ��Χ              ����
#define FTM0_CH0    PTC1        //PTC1��PTA3            PTA3��Ҫ�ã���Jtag��SWD��ͻ��
#define FTM0_CH1    PTC2        //PTC2��PTA4
#define FTM0_CH2    PTC3        //PTC3��PTA5
#define FTM0_CH3    PTC4        //PTC4��PTA6
#define FTM0_CH4    PTD4        //PTD4��PTA7
#define FTM0_CH5    PTD5        //PTD5��PTA0            PTA0��Ҫ�ã���Jtag��SWD��ͻ��
#define FTM0_CH6    PTD6        //PTD6��PTA1            PTA1��Ҫ�ã���Jtag��ͻ��
#define FTM0_CH7    PTD7        //PTD7��PTA2            PTA2��Ҫ�ã���Jtag��ͻ��



/*********************** PWM **************************/

#define FTM_PRECISON 100u     //����ռ�ձȾ��ȣ�100������Ϊ1%��1000u�򾫶�Ϊ0.1%������ռ�ձ� duty �βδ��룬��ռ�ձ�Ϊ duty/FTM_PRECISON

void  FTM_PWM_init(FTMn, CHn, u32 freq, u32 duty);  //��ʼ��FTM��PWM���ܲ�����Ƶ�ʡ�ռ�ձȡ�����ͨ�����ռ�ձȡ�ͬһ��FTM����ͨ����PWMƵ����һ���ģ���3��FTM

void  FTM_PWM_Duty(FTMn, CHn,         u32 duty);    //����ͨ��ռ�ձ�,ռ�ձ�Ϊ ��duty * ���ȣ� % ����� FTM_PRECISON ����Ϊ 1000 ��duty = 100 ����ռ�ձ� 100*0.1%=10%
void  FTM_PWM_freq(FTMn,    u32 freq);              //����FTM��Ƶ��


/*********************** ���벶׽ **************************/

typedef enum Input_cfg
{
    Rising,               //�����ز�׽
    Falling,              //�½��ز�׽
    Rising_or_Falling     //�����ز�׽
} Input_cfg;


void FTM_Input_init(FTMn, CHn, Input_cfg);

#define FTM_IRQ_EN(FTMn,CHn)        FTM_CnSC_REG(FTMx[FTMn],CHn) |= FTM_CnSC_CHIE_MASK       //���� FTMn_CHn �ж�
#define FTM_IRQ_DIS(FTMn,CHn)       FTM_CnSC_REG(FTMx[FTMn],CHn) &= ~FTM_CnSC_CHIE_MASK      //�ر� FTMn_CHn �ж�








#endif  //_FTM_H_



