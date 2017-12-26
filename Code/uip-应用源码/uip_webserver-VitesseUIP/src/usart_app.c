
#include "global.h"

/**********************************************************************
 *����ԭ�ͣ�    GetDataToBuf1()
 *����˵����	u8 *ch
 *�� �� ֵ��	temp
 *˵    ����	�Ӵ��ڻ���������һ���ַ�
 *********************************************************************/
static u8 GetDataToBuf1(u8 *ch)
{
	

	if((u8 *)inRx1Buf == (u8 *)outRx1Buf) 	 return 0;			  // ���ݽ���Buff��ַ�����ݶ�ȡBuff��ַһ�±�ʾ��������

	*ch = *outRx1Buf;											  // �����ݶ������ݸ�ֵ����������
	outRx1Buf++;					                              // ���ݱ����ߣ���ָ���1

	if((u8 *)outRx1Buf == Rx1Buf + BUF1_LEN) 					  // ����ָ��ָ��λ�ã�+ Buff1���� = ��������ָ��ָ��λ��
	outRx1Buf = Rx1Buf;                                           // �����ָ�뵽������β��,��ô��������ָ��ͷ��

	return 1;
}

/**********************************************************************
 *����ԭ�ͣ�    GetDataToBuf2()
 *����˵����	u8 *ch
 *�� �� ֵ��	temp
 *˵    ����	�Ӵ��ڻ���������һ���ַ�
 *********************************************************************/
static u8 GetDataToBuf2(u8 *ch)
{
	USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);				  // ���жϣ�ֹͣ���ݽ���

	if((u8 *)inRx2Buf == (u8 *)outRx2Buf) 					      // ���ݽ���Buff��ַ�����ݶ�ȡBuff��ַһ�±�ʾBuff1�Ѿ�����
	{
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);		      // �򿪽����жϣ�������������
	    return 0;
	}
	
	*ch = *outRx2Buf;											  // �����ݶ������ݸ�ֵ����������
	outRx2Buf++;					                              // ���ݱ����ߣ���ָ���1

	if((u8 *)outRx2Buf == Rx2Buf + BUF2_LEN) 					  // ����ָ��ָ��λ�ã�+ Buff1���� = ��������ָ��ָ��λ��
	outRx2Buf = Rx2Buf;                                           // �����ָ�뵽������β��,��ô��������ָ��ͷ��
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	return 1;
}

/**********************************************************************
 *����ԭ�ͣ�    Usart1_Command
 *��ڲ���:		com_len
 *���ڲ���:		��
 *�� �� ֵ��	��
 *����˵��:		������λ������,�ȴ�һ֡���ݽ�������
 **********************************************************************/

u16 Rcv_Usart1_To_Array(void)
{
    unsigned int dat_len = 0;
    unsigned char ch;

    while(GetDataToBuf1(&ch))
    {
        rcv_usart1_array[dat_len] = ch;			   //�ӻ��λ�����������
        dat_len++;
       
	    if(dat_len == array_maxlen) 
		{
		  dat_len=0;	
		  return array_maxlen;
		}
    }
	return dat_len;
} 

u16 Rcv_Usart2_To_Array(void)
{
    unsigned int dat_len = 0;
    unsigned char ch;

    while(GetDataToBuf2(&ch))
    {
        rcv_usart2_array[dat_len] = ch;			   //�ӻ��λ�����������
        dat_len++;
       
	    if(dat_len == array_maxlen) 
		{
		  dat_len=0;	
		  return array_maxlen;
		}
    }
	return dat_len;
} 

