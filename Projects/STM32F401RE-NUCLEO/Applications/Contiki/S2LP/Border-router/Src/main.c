/**
******************************************************************************
* @file    main.c
* @author  ST
* @version V2.0.0
* @date    05-December-2018
* @brief   STM32 Cube HAL and Contiki 6LoWPAN Initialization, infinite main loop.
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/

/**
* @mainpage
* @section Introduction
*	Contiki6LP is a middleware for STM32Cube and specifically the X-CUBE-SUBG1 expansion software.
*	The key features of Contiki6LP are:
*		- Middleware library with Contiki OS and Contiki 6LoWPAN protocol stack 3.x
*		- Support for mesh networking technology by the means of the standard RPL protocol
*		- Built-in support for STM32 L1 and F4 platforms.
*		- Easy portability across different STM32 MCU families thanks to STM32Cube.
*		- Sample applications enabling communication via UDP over 6LoWPAN, with support for
*		    MCU and Radio low power capabilities ((@ref Low_power), and demonstrating how to implement an
*		    Application Level Duty Cycle for different use cases.
*		- Free user-friendly license terms.
*		- Examples available for NUCLEO-F401RE and NUCLEO-L152RE boards.
*
*	This software provides a porting of the Contiki OS for the STM32 platform, in the STM32Cube
*	software environment, enabling the support for the SPIRIT1 sub-1GHz radio transceiver.
*	The package also includes three sample applications that the developer can use to start
*	experimenting with the code. Two of these applications are supposed to be used together
*	since they implement the communication between two nodes. A sender node (@ref Udp_sender)
*	is going to periodically send UDP packets to a receiver node (@ref Udp_receiver) looking up
*	for a specific service number in the same 6LoWPAN network. A third application implements a
*	6LoWPAN border router (@ref Border_router) functionality. The last application
*	(@ref Serial_sniffer) can be used together with WireShark to sniff and analyze on air packets.
*
*/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "cube_hal.h"
#include "radio_shield_config.h"
#include "radio-driver.h"
#include "process.h"
#include "low-power.h"
#include "contiki-st-radio-main.h"

/** @defgroup Border_router
* @{
*/

/** @addtogroup Border_router
* @{
*/


/* Private function prototypes -----------------------------------------------*/
static void _print_fw_info(void);
/*----------------------------------------------------------------------------*/
#if MCU_LOW_POWER
extern UART_HandleTypeDef UartHandle;
#endif /*MCU_LOW_POWER*/
/*----------------------------------------------------------------------------*/

/**
* @brief  main()
* @param  None
* @retval None
*/
int main()
{
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();

	HAL_EnableDBGStopMode();

	MX_GPIO_Init();
	USARTConfig();
#if MCU_LOW_POWER
	if (USER_CLOCK_FREQUENCY != DEFAULT_CLOCK_FREQUENCY) {
	  HAL_RCC_DeInit();
	  LP_sysclk_config(USER_CLOCK_FREQUENCY);
	  MX_GPIO_Init();
	  HAL_UART_DeInit(&UartHandle);
	  USARTConfig();
	}
#endif /*MCU_LOW_POWER*/

	/* Initialize LEDs */
	BSP_LED_Init(LED2);

	RadioShieldLedInit(RADIO_SHIELD_LED);

	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

	/* Initialize RTC */
	RTC_Config();
	RTC_TimeStampConfig();
	_print_fw_info();
  
	Stack_6LoWPAN_Init();

	while(1) {
		int r = 0;
#if MCU_LOW_POWER
		LP_interrupt_from_radio=0;
#endif /*MCU_LOW_POWER*/
		do {
		  r = process_run();
		} while(r > 0);
#if MCU_LOW_POWER
		LP_enter_sleep_mode();
		LP_exit_sleep_mode();
#endif /*MCU_LOW_POWER*/
	}
}
/*----------------------------------------------------------------------------*/
static void _print_fw_info(void)
{
  /*Compiler, HAL and firmware info:*/
  printf("\t(HAL %ld.%ld.%ld_%ld)\r\n"
	       "\tCompiled %s %s"
#if defined (__IAR_SYSTEMS_ICC__)
	           " (IAR)\r\n\n",
#elif defined (__CC_ARM)
	           " (KEIL)\r\n\n",
#elif defined (__GNUC__)
	           " (openstm32)\r\n\n",
#endif
   HAL_GetHalVersion() >>24,
   (HAL_GetHalVersion() >>16)&0xFF,
   (HAL_GetHalVersion() >> 8)&0xFF,
   HAL_GetHalVersion()      &0xFF,
   __DATE__,__TIME__);
}
/*----------------------------------------------------------------------------*/

/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
