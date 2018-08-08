/*
 * --------------"��������K60�ײ��"-----------------
 *
 *
 * �ļ���: HAL_SPI.h
 * ��;: SPI�ײ�ģ����غ���
 *
 */
#ifndef __HAL_SPI_H__
#define __HAL_SPI_H__
/********************************************************************/
#include"common.h"

typedef enum SPIx
{
  SPI0,
  SPI1,
  SPI2
}SPIx;


#define SPI_SCK_DIV_2        (0)
#define SPI_SCK_DIV_4        (1)
#define SPI_SCK_DIV_6        (2)
#define SPI_SCK_DIV_8        (3)
#define SPI_SCK_DIV_16       (4)
#define SPI_SCK_DIV_32       (5)
#define SPI_SCK_DIV_64       (6)
#define SPI_SCK_DIV_128      (7)
#define SPI_SCK_DIV_256      (8)
#define SPI_SCK_DIV_512      (9)
#define SPI_SCK_DIV_1024     (10)
#define SPI_SCK_DIV_2048     (11)
#define SPI_SCK_DIV_4096     (12)
#define SPI_SCK_DIV_8192     (13)
#define SPI_SCK_DIV_16384    (14
#define SPI_SCK_DIV_32768    (15)

#define SPI_PCS0             (1)
#define SPI_PCS1             (2)
#define SPI_PCS2             (4)
#define SPI_PCS3             (8)
#define SPI_PCS4             (16)
#define SPI_PCS5             (32)

#define SPI_PCS_ASSERTED     (0x01)
#define SPI_PCS_INACTIVE     (0x00)

//SPIģ���жϻص���������
typedef void (*SPI_ISR_CALLBACK)(void);
//SPI��ʼ������
uint8 SPI_Init(SPIx spix,uint8 sck_div,uint8 pcs_num);
//SPI������д����
uint8 SPI_Master_WriteRead(SPIx spix,uint8 data,uint8 pcsx,uint8 pcs_state);
//SPI����������
uint8 SPI_Master_Read(SPIx spix);
//SPI����д����
void SPI_Master_Write(SPIx spix,uint8 data,uint8 pcsx,uint8 pcs_state);

/********************************************************************/
#endif