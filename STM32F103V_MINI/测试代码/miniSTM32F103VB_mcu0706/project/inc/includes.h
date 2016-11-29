#ifndef __INCLUDES_H
#define __INCLUDES_H

#include "stm32f10x_lib.h"
#include "stm32f10x_it.h"

#include "printer_config.h"
#include "platform_config.h"
//***********************
#include "path_param.h"
#if LED103_EN>0
#include "led103.h"
#endif

#if DELAY_EN
#include "delay.h"
#endif

#if BUZ_EN>0
#include "buz.h"
#endif


#if (KEY_EN>0)||(LCM_GUI_EN>0)
#include "key.h"
#endif

//**lcm *gui***************
#include "lcm_driver.h"
#if LCM_GUI_EN>0
#include "lcm_zikulib.h" //HZTable[ ][32] , ASCII816[ ][16]
#include "lcm_menu.h"
#endif//#if LCM_GUI_EN>0

#include "printer_mem.h"
#include "stm32f10x_Timebase.h"

#if FPGA_DRIVER_EN >0
#include "fpga_driver.h"
#endif

#include "MC_type.h"

#if PAPER_MEA_EN>0
#include "paper_mea.h"
#endif
#include "MC_encoder_param.h"
#include "MC_Control_Param.h"

#if ENCODER_EN>0
#include "stm32f10x_encoder.h"
#endif


//****uart*********
#if COM_EN>0
#include "Com_app.h"
#include "Com_pc_com.h"
#endif//#ifCOM_EN>0

#if EXTI_EN>0
#include "exti.h"
#endif

#if MP_EN>0
#include "mp_out.h"
#endif//#if MP_EN>0

#if LOAD_PAPER_EN>0
#include "load_paper.h"
#endif

#if UART_DRIVER_EN>0
#include"uart_driver.h"
#endif

#if SPI_FLASH_EN>0
#include "spi_flash.h"
#endif //SPI_FLASH_EN>0

#endif //__INCLUDES_H

