#include "stm32f10x.h"
/* Select SPI FLASH: Chip Select pin low  */
#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOC, GPIO_Pin_5)
/* Deselect SPI FLASH: Chip Select pin high */
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOC, GPIO_Pin_5)
#define Dummy_Byte 0xFF


 u32 FLASH_ID;

 u32 SPI_FLASH_ReadID(void)
{
  u32 Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0, Temp3;

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "RDID " instruction */
  SPI1_ReadWrite(0x9F);

  /* Read a byte from the FLASH */
  Temp0 = SPI1_ReadWrite(Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp1 = SPI1_ReadWrite(Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp2 = SPI1_ReadWrite(Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp3 = SPI1_ReadWrite(Dummy_Byte);
  
  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  Temp = (Temp0 << 24) | (Temp1 << 16) | (Temp2<<8) | Temp3;

  return Temp;
}
