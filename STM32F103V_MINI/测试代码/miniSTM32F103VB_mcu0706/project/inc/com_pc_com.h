#ifndef __COM_PC_COM_H
#define __COM_PC_COM_H
/******************************************************************************************************
*1, 通讯协议
*通讯协议采用主从模式，上位机为主,单片机为从。上位机发送一帧命令，单片机需返回一帧响应。
*它们的格式基本相同，都有同步头，帧长底部，帧长高部，数据段，校验，校验的反码等组成。
*同步头用于确定起始字节，命令帧为0xAA， 响应帧为0x55。 帧长低部和帧长高部合起来组长
*一个16位整数（帧长高部<<8 + 帧长低部）表示从同步头到校验反码的总字节数，最大为65536.
*数据段是用户要发送的数据， 里面可包含命令、参数等 ， 它的字节是可变的， 最多为65531
*个。校验为从同步头到最后一个数据的所有字节的异或结果。校验反码是校验被取反的值。
*
*命令帧  上位机---> 单片机
*---------------------------------------------------------------------------------------------------
*|同步头 | 帧长 |	数据(0...N-1) | 		校验  								 | 校验反码
*|-------|--------------|----------------|----------------|----------------------------|------------
*|0xAA   | 整个帧长| N个用户数据    | 从同步到最后一个数据的异或 | 校验的反码
*---------------------------------------------------------------------------------------------------
*
*响应帧  单片机--->上位机
*----------------------------------------------------------------------
*-----------------------------------------------------------------------------------------------
*|同步头 | 帧长	 | 数据(0...N-1)|		校验  									 |校验反码	 |
*|-------|------------|----------------|--------------|----------------------------|-----------|
*|0x55   |整个帧长 | N个用户数据  | 从同步到最后一个数据的异或 | 校验的反码|
*-----------------------------------------------------------------------------------------------
*
*命令帧的数据段由命令码和参数组成， 如表3； 其中命令码，参数的个数根据命令码定。
*
*命令帧  数据段
*------------------------------------------------
*|偏移量 |   0   |   1    |... |  N
*|-------|-------|--------|----|-----------------
*|说明   |命令码 |第一参数|... |第N个参数
*------------------------------------------------
*
*响应帧  数据段
*------------------------------------------------
*|偏移量 |  0    |   1     | ... |  N
*|-------|-------|---------|-----|---------------
*|说明   |响应码 | 第一参数| ... |第N个参数
*------------------------------------------------
*
*********************************************************************************************************/
#define COM_PC_CMD_HDR	(u8)(0xAA)	/*命令同步头*/
#define COM_MCU_ACK_HDR	'#'    //'#' = 0x23  /*响应同步头(0x55)*/

//**Err list
#define COM_MP_HDR_ERR		1
#define COM_MP_XOR_ERR		2

#define COM_RESPONSE		(u8)(0x01)
/*------------------------------
*第一级命令list，
*------------------------------*/
/*主要pc  机传数据到mcu*/
#define PC_CMD_H_X_J_Q				'j'     /*横向静区--1*/
#define PC_CMD_V_X_J_Q				'v'     /*纵向静区--2*/
#define PC_CMD_SPEED				'S'     /*打印速度--3*/
#define PC_CMD_CLEAR               		'C'     /*青色		--4*/
#define PC_CMD_P          				'P'  	/*pass，抽墨 --5*/
#define PC_CMD_MOTOR             		'M'	/*----------------6*/
#define PC_CMD_MOTOR_SERVO       	's' 	 /*伺服---------7*/
#define PC_CMD_MOTOR_STEPPER         'm'	/*步进---------8*/
#define PC_CMD_SERVO_SETPPER_ADJ	'A'	/*伺服，步进调整---9*/  
#define PC_CMD_ACK_OK			       COM_RESPONSE/*正常应答*/
/*------------------------------------------
*第二级命令list
*------------------------------------------*/
typedef enum {
 PASS1  =   0x01,
 PASS2   ,            
 PASS3   ,            
 PASS4    ,           
 PASS5   ,            
 PASS6   ,            
 PASS7    ,           
 PASS8              
}PriPassMode_t;


#define Y_COLOR	  	 'Y'   /*Y  黄 色*/
#define M_COLOR  	 'M'   /*M   色*/
#define C_COLOR   	 'C'  	/*C  色*/
#define K_COLOR  	 'K'   /*K  黑色*/
#define LM_COLOR   	 'm'  /*LM  色*/
#define LC_COLOR  	 'c'   /*LC  色*/

typedef enum {
 SPD_HIGH  = 'H'	,	/*高速模式*/
 SPD_MIDDLE = 'M',	 /*中速模式*/
 SPD_LOW    	=	'L' , 	/*低速模式*/

}SpdMode_t;

#define HORI   		'H' 	 /*横向模式*/
#define VERT			'V'	/*纵向模式*/

#define PAPER_FEED		'I'  /*进纸*/
#define PAPER_UNFEED	'B'	/*退纸*/

#define MOTOR_STOP  	'S'

#define LEFT     			'L'		/* 左移*/
#define RIGHT    			'R'		/* 右移*/

/*打印,*/
#define PRINT_ODD  		'O'  	/*单向打印*/
#define PRINT_EVEN	 	'E'  	/*双向打印*/
/*伺服运动方向*/
#define GO_FAR	  		0x47 	 /* 远离'G' = 0x47*/
#define GO_NEAR    		0x43 	 /* 回来'C' = 0x43*/

/*
*伺服电机 *第二级命令list
*/
typedef enum{
	SERVO_CMD_AREA_FAR = 1,/*远端点*/
	SERVO_CMD_AREA_NAR,	/*--2 近端点*/
	SERVO_CMD_STEP , 		 // --3
	SERVO_CMD_AUTO ,		 //--4
	SERVO_CMD_STOP, 		//--5
	SERVO_CMD_START,			//--6
	SERVO_CMD_PID_PARA_SET, //--7
	SERVO_CMD_STATE_GET,		//--8
	SERVO_CMD_PID_PARA_GET, //--9
}SERVO_CMD_LEVEL22;

/*打印速度*/
#define PC_CMD_S_CLEAR_A	'A'	/*清洗A  所有*/
/*清洗LM  喷头*/
/*清洗LC  喷头*/

#define PC_CMD_S_PUMP  'I'	/*抽墨*/

#define PC_CMD_S_PASS_NUM  	'P'	/*pass 数*/
#define PC_CMD_S_PRINT_ORIGIN	'O' 	 /*打印原点*/
#define PC_CMD_S_PRINT_BLANK   'M'	/*打印空白*/

#define PC_CMD_S_SERVO_ADJ    	'H'     /*H横向伺服调整*/
#define PC_CMD_S_SETPPER_ADJ    'V'     /*V纵向步进调整*/

/***************************************************************/
/*高中低速横向静区*/
/*1~~8pass纵向静区*/
/*1~~8pass 步进电机调整数*/
/*高中低速伺服电机调整数*/
typedef struct{
	u8 Cmd;	                //第一级菜单
	u8 CmdSub;              //第二级菜单
	u8 CmdSubSub;           //第三级菜单
	u32 nData;     //
}Cmd_Data_t;

typedef struct{
	u8 Header;              //同步头
	u8 HDRLen;              //1帧长
}Cmd_HDR_t;

typedef struct{
	Cmd_HDR_t chl ;
	u8 Cmd;	                //第一级菜单
	u8 CmdSub;              //第二级菜单
	u8 CmdSubSub;           //第三级菜单
	u32 nData;     //
}COM_SERIAL_PORT;

typedef  COM_SERIAL_PORT  COM_PC_HDR_T;

u8 CheckXor(u8 *buf , u16 size);
bool ComPCCmdRec(u8 *buf , u16 size);//USBPC_HDR_T * Hdr);
void ComMCUACKSend(u8 *buf , u16 size);
extern void ComSendString(u8 *str );
extern void ComSendStringInt(u8 *str , u16 val );
#endif	//__COM_PC_COM_H




