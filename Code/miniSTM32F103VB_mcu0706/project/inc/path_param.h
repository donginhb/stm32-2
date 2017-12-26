//path_param.h
/*
*4600�����ī������
*1������
*2, ī��
*3��īվ
*/
#ifndef __PATH_PARAM_H
#define __PATH_PARAM_H

#define ORIGIN_TO_INK_STOP_NEAR_LEN_MM  	(u16)(27)
/*ת��Ϊ��0.0423mm Ϊ��λ, ����������դ������1/4*/
#define ORIGIN_TO_INK_STOP_NEAR_LEN_EDGE   (long)(ORIGIN_TO_INK_STOP_NEAR_LEN_MM*ENCODER_PPR_LINE*10/( 254))
	
#define INK_STOP_LEN_MM   	   (u16)(240) 	 	/*īվ�ĳ���*/
#define INK_STOP_LEN_EDGE	   (long)(INK_STOP_LEN_MM*ENCODER_PPR_LINE*10/( 254))

#define PRINT_AREA_LEN_MM  	(u16) (1545) 		/*��Ч��ӡ������*/
#define PRINT_AREA_LEN_EDGE	(long)(PRINT_AREA_LEN_MM*ENCODER_PPR_LINE*10/( 254))

#define PRINT_AREA_NEAR_TO_INK_STOP_FAR_LEN_MM  60 	 /*��ӡ�����ߺ�īվԶ�߼��*/
#define PRINT_AREA_NEAR_TO_INK_STOP_FAR_LEN_EDGE	(long)(PRINT_AREA_NEAR_TO_INK_STOP_FAR_LEN_MM*ENCODER_PPR_LINE*10/( 254))

#define FAR_SPEED_UP_AREA_LEN_MM  (u16)(257)  	/*Զ�˼���������*/
#define FAR_SPEED_UP_AREA_LEN_EDGE	(long)(FAR_SPEED_UP_AREA_LEN_MM*ENCODER_PPR_LINE*10/( 254))

#define PRINT_ORIGIN_DEFAULT_LEN_MM    (u16)(40) 
#define PRINT_ORIGIN_DEFAULT_LEN_EDGE   (long)(PRINT_ORIGIN_DEFAULT_LEN_MM*ENCODER_PPR_LINE*10/( 254))

#define STOP_NEAR_TO_INK_STOP_LEN_MM 	(u16)(14)		/*����ͣ���㵽īվ���˵�ľ���*/
#define STOP_NEAR_TO_INK_STOP_LEN_EDGE   (long)(STOP_NEAR_TO_INK_STOP_LEN_MM*ENCODER_PPR_LINE*10/( 254))/*����ͣ���㵽īվ���˵�ľ���*/

#define STOP_NEAR_TO_INK_STOP_LEN_MM 	(u16)(14)		/*����ͣ���㵽īվ���˵�ľ���*/
#define STOP_NEAR_TO_INK_STOP_LEN_EDGE   (long)(STOP_NEAR_TO_INK_STOP_LEN_MM*ENCODER_PPR_LINE*10/( 254))/*����ͣ���㵽īվ���˵�ľ���*/

#endif


