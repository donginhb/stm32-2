#include "stm32f7xx.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"
#include "./flash/bsp_qspi_flash.h"
#include "./sdram/bsp_sdram.h"
#include "./key/bsp_key.h" 
#include "main.h" 

//����SDRAM��ض���
/*���Զ�λ��ʽ����SDRAM,���ַ�ʽ���붨���ȫ�ֱ���*/
#define SDRAM_SIZE (IS42S16400J_SIZE/4)
uint8_t testValue __attribute__((at(SDRAM_BANK_ADDR)));
void SDRAM_Check(void);
uint32_t RadomBuffer[10000];
uint32_t ReadBuffer[10000];
uint32_t *pSDRAM;
long long count=0,sdram_count=0;
RNG_HandleTypeDef hrng;



//����W25Q��ض���
/* ��ȡ�������ĳ��� */
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)
#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress 
/* ���ͻ�������ʼ�� */
uint8_t Tx_Buffer[] = "��л��ʹ�ð�����STM32F767������\r\nhttp://www.lctech-inc.com/";
uint8_t Rx_Buffer[BufferSize];
//��ȡ��ID�洢λ��
__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;
__IO TestStatus TransferStatus1 = FAILED;
// ����ԭ������
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);



//����ʱ����
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/**
  * @brief  System Clock ����
  *         system Clock �������� : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  ��
  * @retval ��
  */
	
/****ϵͳʱ������****/
void SystemClock_Config(void)      
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* ʹ��HSE������HSEΪPLL��ʱ��Դ������PLL�ĸ��ַ�Ƶ����M N P Q 
	 * PLLCLK = HSE/M*N/P = 25M / 25 *432 / 2 = 216M
	 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* ���� OverDrive ģʽ�Դﵽ216MƵ��  */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* ѡ��PLLCLK��ΪSYSCLK�������� HCLK, PCLK1 and PCLK2 ��ʱ�ӷ�Ƶ���� 
	 * SYSCLK = PLLCLK     = 216M
	 * HCLK   = SYSCLK / 1 = 216M
	 * PCLK2  = SYSCLK / 2 = 108M
	 * PCLK1  = SYSCLK / 4 = 54M
	 */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 
  
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }  
}


/*
 * ��������Buffercmp
 * ����  ���Ƚ������������е������Ƿ����
 * ����  ��-pBuffer1     src������ָ��
 *         -pBuffer2     dst������ָ��
 *         -BufferLength ����������
 * ���  ����
 * ����  ��-PASSED pBuffer1 ����   pBuffer2
 *         -FAILED pBuffer1 ��ͬ�� pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }
  return PASSED;
}



/****SPI�ӿ�flashоƬW25Q128����****/

void SPI_Test_All(void)
{
	printf("\r\n\r\n\r\n������STM32F767������ W25Q128����");
	
	/* ��ȡ Flash Device ID */
	DeviceID = QSPI_FLASH_ReadDeviceID();
	
	Delay( 200 );
	
	/* ��ȡ SPI Flash ID */
	FlashID = QSPI_FLASH_ReadID();
	
	printf("\r\nFlashID is 0x%X,  Manufacturer Device ID is 0x%X", FlashID, DeviceID);
	
	/* ���� SPI Flash ID */
	if (FlashID == sFLASH_ID) 
	{	
		/* Enable I-Cache */
		SCB_EnableICache();
		/* Enable D-Cache */
		SCB_EnableDCache();
		printf("\r\n\r\n��⵽QSPI FLASH W25Q128 !\r\n");
		
		/* ������Ҫд��� QSPI FLASH ������FLASHд��ǰҪ�Ȳ��� */
		BSP_QSPI_Erase_Block(FLASH_SectorToErase);	 	 
		
		/* �����ͻ�����������д��flash�� */
		BSP_QSPI_Write(Tx_Buffer, FLASH_WriteAddress, BufferSize);
		printf("\r\nд�������Ϊ��\r\n%s", Tx_Buffer);
		
		/* ���ո�д������ݶ������ŵ����ջ������� */
		BSP_QSPI_Read(Rx_Buffer, FLASH_ReadAddress, BufferSize);
		printf("\r\n����������Ϊ��\r\n%s", Rx_Buffer);
		
		/* ���д�������������������Ƿ���� */
		TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
		
		if( PASSED == TransferStatus1 )
		{ 
      LED4(ON);		 //W25Q128���Գɹ���D1����	
			printf("\r\n\r\n16M����flash(W25Q128)���Գɹ�!\n\r");
		}
		else
		{  
      LED4(OFF);   //W25Q128���Գɹ���D1Ϩ�� 
			printf("\r\n\r\n16M����flash(W25Q128)����ʧ��!\n\r");
		}
	}// if (FlashID == sFLASH_ID)
	else
	{ 
		LED4(OFF);    //��ȡW25Q128 ID��ʧ�ܣ�D1Ϩ��
		printf("\r\n\r\n��ȡ���� W25Q128 ID!\n\r");
	}
}







/****SDRAMоƬIS42S16400J����****/

void SDRAM_Check(void)
{
  pSDRAM=(uint32_t*)SDRAM_BANK_ADDR;

	count=0;

	printf("��ʼд��SDRAM\r\n");

	for(sdram_count=0;sdram_count<SDRAM_SIZE;sdram_count++)

	{

		*pSDRAM=RadomBuffer[count];

		count++;

		pSDRAM++;

		if(count>=10000)

		{

			count=0;

		}

	}

	printf("д�����ֽ���:%d\r\n",(uint32_t)pSDRAM-SDRAM_BANK_ADDR);

	

	count=0;

	pSDRAM=(uint32_t*)SDRAM_BANK_ADDR;

	printf("��ʼ��ȡSDRAM����ԭ������Ƚ�\r\n");

	sdram_count=0;

	for(;sdram_count<SDRAM_SIZE;sdram_count++)

	{

		if(*pSDRAM != RadomBuffer[count])

		{

			printf("���ݱȽϴ��󡪡��˳�~\r\n");

			break;

		}

		count++;

		pSDRAM++;

		if(count>=10000)

		{

			count=0;

		}

	}

	printf("�Ƚ�ͨ�����ֽ���:%d\r\n",(uint32_t)pSDRAM-SDRAM_BANK_ADDR);

	

	if(sdram_count == SDRAM_SIZE)

	{

		printf("\r\nSDRAM���Գɹ�\r\n");

	}

	else

	{
		printf("\r\nSDRAM����ʧ��\r\n");

	}  
}


void SDRAM_Test_All(void)
{
	
	printf("\r\n\r\n\r\n������STM32F767������ SDRAM ��д����\r\n");
  
	SDRAM_Test();
	
	 __HAL_RCC_RNG_CLK_ENABLE();

    hrng.Instance = RNG;
    HAL_RNG_Init(&hrng);

    printf("\r\n��ʼ����10000��SDRAM���������\r\n");   
    for(count=0;count<10000;count++)

    {
        RadomBuffer[count]=HAL_RNG_GetRandomNumber(&hrng);

    }    
    printf("10000��SDRAM����������������\r\n");

    SDRAM_Check();
		
}






/****������****/

int main(void)
{ 	
	/* Configure the system clock to 200 MHz */
	SystemClock_Config();
	
  /*������ʼ��*/
	Key_GPIO_Config();
	
	/*LED��ʼ��*/
	LED_GPIO_Config();
	
	/* 16M����flash W25Q128��ʼ�� */
	QSPI_FLASH_Init();
	
	/* ���ô���1Ϊ��115200 8-N-1 */
	DEBUG_USART_Config();
	
	/*SDRAM��ʼ��*/
	SDRAM_Init();
	
	
	SDRAM_Test_All();  //�ϵ�˲����߰���λ��������SDRAM
	
	while(1)
	{
			if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )   //KEY������
			{
				SPI_Test_All();   //����W25Q128
			} 
  }	
	
  
}

/******************* END OF FILE*******************/ 

