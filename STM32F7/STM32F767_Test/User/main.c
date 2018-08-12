#include "stm32f7xx.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"
#include "./flash/bsp_qspi_flash.h"
#include "./sdram/bsp_sdram.h"
#include "./key/bsp_key.h" 
#include "main.h" 

//测试SDRAM相关定义
/*绝对定位方式访问SDRAM,这种方式必须定义成全局变量*/
#define SDRAM_SIZE (IS42S16400J_SIZE/4)
uint8_t testValue __attribute__((at(SDRAM_BANK_ADDR)));
void SDRAM_Check(void);
uint32_t RadomBuffer[10000];
uint32_t ReadBuffer[10000];
uint32_t *pSDRAM;
long long count=0,sdram_count=0;
RNG_HandleTypeDef hrng;



//测试W25Q相关定义
/* 获取缓冲区的长度 */
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)
#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress 
/* 发送缓冲区初始化 */
uint8_t Tx_Buffer[] = "感谢您使用艾尔赛STM32F767开发板\r\nhttp://www.lctech-inc.com/";
uint8_t Rx_Buffer[BufferSize];
//读取的ID存储位置
__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;
__IO TestStatus TransferStatus1 = FAILED;
// 函数原型声明
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);



//简单延时函数
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/**
  * @brief  System Clock 配置
  *         system Clock 配置如下 : 
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
  * @param  无
  * @retval 无
  */
	
/****系统时钟配置****/
void SystemClock_Config(void)      
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* 使能HSE，配置HSE为PLL的时钟源，配置PLL的各种分频因子M N P Q 
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
  
  /* 激活 OverDrive 模式以达到216M频率  */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* 选择PLLCLK作为SYSCLK，并配置 HCLK, PCLK1 and PCLK2 的时钟分频因子 
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
 * 函数名：Buffercmp
 * 描述  ：比较两个缓冲区中的数据是否相等
 * 输入  ：-pBuffer1     src缓冲区指针
 *         -pBuffer2     dst缓冲区指针
 *         -BufferLength 缓冲区长度
 * 输出  ：无
 * 返回  ：-PASSED pBuffer1 等于   pBuffer2
 *         -FAILED pBuffer1 不同于 pBuffer2
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



/****SPI接口flash芯片W25Q128测试****/

void SPI_Test_All(void)
{
	printf("\r\n\r\n\r\n艾尔赛STM32F767开发板 W25Q128测试");
	
	/* 获取 Flash Device ID */
	DeviceID = QSPI_FLASH_ReadDeviceID();
	
	Delay( 200 );
	
	/* 获取 SPI Flash ID */
	FlashID = QSPI_FLASH_ReadID();
	
	printf("\r\nFlashID is 0x%X,  Manufacturer Device ID is 0x%X", FlashID, DeviceID);
	
	/* 检验 SPI Flash ID */
	if (FlashID == sFLASH_ID) 
	{	
		/* Enable I-Cache */
		SCB_EnableICache();
		/* Enable D-Cache */
		SCB_EnableDCache();
		printf("\r\n\r\n检测到QSPI FLASH W25Q128 !\r\n");
		
		/* 擦除将要写入的 QSPI FLASH 扇区，FLASH写入前要先擦除 */
		BSP_QSPI_Erase_Block(FLASH_SectorToErase);	 	 
		
		/* 将发送缓冲区的数据写到flash中 */
		BSP_QSPI_Write(Tx_Buffer, FLASH_WriteAddress, BufferSize);
		printf("\r\n写入的数据为：\r\n%s", Tx_Buffer);
		
		/* 将刚刚写入的数据读出来放到接收缓冲区中 */
		BSP_QSPI_Read(Rx_Buffer, FLASH_ReadAddress, BufferSize);
		printf("\r\n读出的数据为：\r\n%s", Rx_Buffer);
		
		/* 检查写入的数据与读出的数据是否相等 */
		TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
		
		if( PASSED == TransferStatus1 )
		{ 
      LED4(ON);		 //W25Q128测试成功，D1点亮	
			printf("\r\n\r\n16M串行flash(W25Q128)测试成功!\n\r");
		}
		else
		{  
      LED4(OFF);   //W25Q128测试成功，D1熄灭 
			printf("\r\n\r\n16M串行flash(W25Q128)测试失败!\n\r");
		}
	}// if (FlashID == sFLASH_ID)
	else
	{ 
		LED4(OFF);    //获取W25Q128 ID号失败，D1熄灭
		printf("\r\n\r\n获取不到 W25Q128 ID!\n\r");
	}
}







/****SDRAM芯片IS42S16400J测试****/

void SDRAM_Check(void)
{
  pSDRAM=(uint32_t*)SDRAM_BANK_ADDR;

	count=0;

	printf("开始写入SDRAM\r\n");

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

	printf("写入总字节数:%d\r\n",(uint32_t)pSDRAM-SDRAM_BANK_ADDR);

	

	count=0;

	pSDRAM=(uint32_t*)SDRAM_BANK_ADDR;

	printf("开始读取SDRAM并与原随机数比较\r\n");

	sdram_count=0;

	for(;sdram_count<SDRAM_SIZE;sdram_count++)

	{

		if(*pSDRAM != RadomBuffer[count])

		{

			printf("数据比较错误——退出~\r\n");

			break;

		}

		count++;

		pSDRAM++;

		if(count>=10000)

		{

			count=0;

		}

	}

	printf("比较通过总字节数:%d\r\n",(uint32_t)pSDRAM-SDRAM_BANK_ADDR);

	

	if(sdram_count == SDRAM_SIZE)

	{

		printf("\r\nSDRAM测试成功\r\n");

	}

	else

	{
		printf("\r\nSDRAM测试失败\r\n");

	}  
}


void SDRAM_Test_All(void)
{
	
	printf("\r\n\r\n\r\n艾尔赛STM32F767开发板 SDRAM 读写测试\r\n");
  
	SDRAM_Test();
	
	 __HAL_RCC_RNG_CLK_ENABLE();

    hrng.Instance = RNG;
    HAL_RNG_Init(&hrng);

    printf("\r\n开始生成10000个SDRAM测试随机数\r\n");   
    for(count=0;count<10000;count++)

    {
        RadomBuffer[count]=HAL_RNG_GetRandomNumber(&hrng);

    }    
    printf("10000个SDRAM测试随机数生成完毕\r\n");

    SDRAM_Check();
		
}






/****主函数****/

int main(void)
{ 	
	/* Configure the system clock to 200 MHz */
	SystemClock_Config();
	
  /*按键初始化*/
	Key_GPIO_Config();
	
	/*LED初始化*/
	LED_GPIO_Config();
	
	/* 16M串行flash W25Q128初始化 */
	QSPI_FLASH_Init();
	
	/* 配置串口1为：115200 8-N-1 */
	DEBUG_USART_Config();
	
	/*SDRAM初始化*/
	SDRAM_Init();
	
	
	SDRAM_Test_All();  //上电瞬间或者按复位按键测试SDRAM
	
	while(1)
	{
			if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )   //KEY被按下
			{
				SPI_Test_All();   //测试W25Q128
			} 
  }	
	
  
}

/******************* END OF FILE*******************/ 

