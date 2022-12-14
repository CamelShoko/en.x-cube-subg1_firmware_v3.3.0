/**
******************************************************************************
* @file    st-lib.h
* @author  System LAB
* @version V1.0.0
* @date    30-July-2015
* @brief   Contiki style wrapping library for STM32Cube HAL APIs 
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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
/*---------------------------------------------------------------------------*/

/**
 * @addtogroup STM32_Contiki_Library
 * Abstraction of STM32Cube HAL APIs as per Contiki coding rules
 * @{
 * @file Header file for the STM32Cube HAL APIs
 */

/*---------------------------------------------------------------------------*/
#ifndef ST_LIB_H_
#define ST_LIB_H_

/*---------------------------------------------------------------------------*/
/* extern global varialbles */
#ifdef USE_X_CUBE_IDW01M1
#define st_lib_uart_handle                       UartMsgHandle
#else
#define st_lib_uart_handle                       UartHandle
#endif
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
#include "MCU_Interface.h"
#include "radio_gpio.h"
#include "radio_spi.h"

#ifdef USE_STM32L1XX_NUCLEO
#include "stm32l1xx_hal_uart.h"
#include "stm32l152xe.h"
#include "stm32l1xx.h"
#include "stm32l1xx_hal_cortex.h"
#include "stm32l1xx_hal_rcc.h"
#include "stm32l1xx_hal_spi.h"
#include "stm32l1xx_hal_tim.h"
#include "stm32l1xx_nucleo.h"
#define st_lib_gpio_port                         LED_PORT
#define st_lib_gpio_pin                          LED_PIN
#endif /*USE_STM32L1XX_NUCLEO*/

#ifdef USE_STM32F4XX_NUCLEO
#include "stm32f4xx_hal_uart.h"
#include "stm32f401xe.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_nucleo.h"

#define st_lib_gpio_port                         GPIO_PORT
#define st_lib_gpio_pin                          GPIO_PIN
#endif /*USE_STM32F4XX_NUCLEO*/


#define st_lib_radio_enter_shutdown              RadioEnterShutdown
#define st_lib_radio_exit_shutdown               RadioExitShutdown
#define st_lib_g_x_status                        g_xStatus

#define st_lib_tim2_irq_handler(...)             TIM2_IRQHandler(__VA_ARGS__)
#define st_lib_tim5_irq_handler(...)             TIM5_IRQHandler(__VA_ARGS__)
#define st_lib_sys_tick_handler(...)             SysTick_Handler(__VA_ARGS__)

#define st_lib_radio_gpio_init(...)              RadioGpioInit(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* radio_shield_config.h */
#include "radio_shield_config.h"
#define st_lib_a_led_gpio_port                   aLED_GPIO_PORT
#define st_lib_a_led_gpio_pin                    aLED_GPIO_PIN

#define st_lib_radio_shield_led_init(...)        RadioShieldLedInit(__VA_ARGS__)
#define st_lib_radio_shield_led_off(...)         RadioShieldLedOff(__VA_ARGS__)
#define st_lib_radio_shield_led_on(...)          RadioShieldLedOn(__VA_ARGS__)
#define st_lib_radio_spi_cs_high(...)            RadioSpiCSHigh(__VA_ARGS__)
#define st_lib_radio_spi_cs_low(...)             RadioSpiCSLow(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
#if defined(X_NUCLEO_IDS01A4) || defined(X_NUCLEO_IDS01A5)
#include "SPIRIT_Commands.h"
#include "SPIRIT_Gpio.h"
#include "SPIRIT_Irq.h"
#include "SPIRIT_LinearFifo.h"
#include "SPIRIT_PktBasic.h"
#include "SPIRIT_Qi.h"
#include "SPIRIT_Radio.h"
#include "SPIRIT_Timer.h"
#include "SPIRIT_Types.h"
#include "SPIRIT_Csma.h"
#include "radio_spi.h"

#define st_lib_p_spi_handle                             pSpiHandle
#define st_lib_s_radio_init                             SRadioInit
#define st_lib_radio_cmd_strobe_flush_rx_fifo(...)      SpiritCmdStrobeFlushRxFifo(__VA_ARGS__)
#define st_lib_radio_cmd_strobe_command(...)            SpiritCmdStrobeCommand(__VA_ARGS__)
#define st_lib_radio_cmd_strobe_sabort(...)	        SpiritCmdStrobeSabort(__VA_ARGS__)
#define st_lib_radio_gpio_irq_init(...)                 SpiritGpioInit(__VA_ARGS__)
#define st_lib_radio_irqs                               SpiritIrqs
#define st_lib_radio_irq(...)                           SpiritIrq(__VA_ARGS__)
#define st_lib_radio_irq_de_init(...)                   SpiritIrqDeInit(__VA_ARGS__)
#define st_lib_radio_irq_init(...)                      SpiritIrqInit(__VA_ARGS__)
#define st_lib_radio_irq_get_mask(...)                  SpiritIrqGetMask(__VA_ARGS__)
#define st_lib_radio_irq_get_status(...)                SpiritIrqGetStatus(__VA_ARGS__)
#define st_lib_radio_irq_clear_status(...)              SpiritIrqClearStatus(__VA_ARGS__)
#define st_lib_radio_irq_check_flag(...)                SpiritIrqCheckFlag(__VA_ARGS__)
#define st_lib_FifoSetAlmostEmptyThresholdTx            SpiritLinearFifoSetAlmostEmptyThresholdTx
#define st_lib_radio_linear_fifo_read_num_elements_rx_fifo(...) SpiritLinearFifoReadNumElementsRxFifo(__VA_ARGS__)
#define st_lib_radio_pkt_basic_init(...)                    SpiritPktBasicInit(__VA_ARGS__)
#define st_lib_radio_pkt_basic_get_received_pkt_length(...) SpiritPktBasicGetReceivedPktLength(__VA_ARGS__)
#define st_lib_radio_pkt_basic_set_payload_length(...)      SpiritPktBasicSetPayloadLength(__VA_ARGS__)
#define st_lib_radio_qi_get_rssi_dbm(...)               SpiritQiGetRssidBm(__VA_ARGS__)
#define st_lib_radio_qi_get_rssi_dbm_run                st_lib_radio_qi_get_rssi_dbm
#define st_lib_radio_qi_pqi_check(...)                  SpiritQiPqiCheck(__VA_ARGS__)
#define st_lib_radio_qi_sqi_check(...)                  SpiritQiSqiCheck(__VA_ARGS__)
#define st_lib_radio_qi_set_rssi_threshold_dbm(...)     SpiritQiSetRssiThresholddBm(__VA_ARGS__)
#define st_lib_radio_qi_get_lqi(...)                    SpiritQiGetLqi(__VA_ARGS__)
#define st_lib_radio_qi_get_rssi(...)                   SpiritQiGetRssi(__VA_ARGS__)
#define st_lib_radio_radio_afc_freeze_on_sync(...)      SpiritRadioAFCFreezeOnSync(__VA_ARGS__)
#define st_lib_radio_radio_init(...)                    SpiritRadioInit(__VA_ARGS__)
#define st_lib_radio_radio_persisten_rx(...)            SpiritRadioPersistenRx(__VA_ARGS__)
#define st_lib_radio_radio_set_pa_level_dbm(...)        SpiritRadioSetPALeveldBm(__VA_ARGS__)
#define st_lib_radio_radio_set_pa_level_max_index(...)  SpiritRadioSetPALevelMaxIndex(__VA_ARGS__)
#define st_lib_radio_radio_set_xtal_frequency(...)      SpiritRadioSetXtalFrequency(__VA_ARGS__)
#define st_lib_radio_radio_cs_blanking(...)		SpiritRadioCsBlanking(__VA_ARGS__)
#define st_lib_radio_timer_set_rx_timeout_stop_condition(...)  SpiritTimerSetRxTimeoutStopCondition(__VA_ARGS__)
#define st_lib_radio_bool                               SpiritBool
#define st_lib_radio_status                             SpiritStatus
#define st_lib_radio_flag_status                        SpiritFlagStatus
#define st_lib_radio_refresh_status(...)                SpiritRefreshStatus(__VA_ARGS__)
#define st_lib_radio_csma_init(...)			SpiritCsmaInit(__VA_ARGS__)
#define st_lib_radio_csma(...)				SpiritCsma(__VA_ARGS__)
#define st_lib_CmdStrobeTx			        SpiritCmdStrobeTx
#define st_lib_QiGetCs                                  SpiritQiGetCs
#define st_lib_radio_Cmd                                SpiritCmd
#define st_lib_FifoReadNumberBytesTxFifo                SpiritLinearFifoReadNumElementsTxFifo
#define Radio_GPIO_IRQ                                  SPIRIT_GPIO_3
#define Radio_GPIO_MODE_DIGITAL_OUTPUT_LP               SPIRIT_GPIO_MODE_DIGITAL_OUTPUT_LP
#define Radio_GPIO_DIG_OUT_IRQ                          SPIRIT_GPIO_DIG_OUT_IRQ
#define RadioCmdStrobeStandby()         radio_strobe(RADIO_STROBE_STANDBY)
#define RadioCmdStrobeSabort()          radio_strobe(RADIO_STROBE_SABORT)
#define RadioCmdStrobeReady()           radio_strobe(RADIO_STROBE_READY)
#define RadioCmdStrobeRx()              radio_strobe(RADIO_STROBE_RX)
#define st_lib_FifoSetAlmostFullThresholdRx    SpiritLinearFifoSetAlmostFullThresholdRx
#define st_lib_radio_spi_init(...)              SpiritSpiInit(__VA_ARGS__)
#define st_lib_radio_spi_read_linear_fifo(...)  SpiritSpiReadLinearFifo(__VA_ARGS__)
#define st_lib_radio_spi_write_linear_fifo(...) SpiritSpiWriteLinearFifo(__VA_ARGS__)
#define st_lib_radio_gpio_interrupt_cmd(...)     RadioGpioInterruptCmd(__VA_ARGS__)
#define st_lib_radio_management_set_frequency_base(...)  SpiritManagementSetFrequencyBase(__VA_ARGS__)
#endif /*SPIRIT1 Radio*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#if defined(X_NUCLEO_S2868A1) || defined(X_NUCLEO_S2915A1)
#include "S2LP_Commands.h"
#include "S2LP_Gpio.h"
#include "S2LP_Fifo.h"
#include "S2LP_PktBasic.h"
#include "S2LP_Qi.h"
#include "S2LP_Radio.h"
#include "S2LP_Timer.h"
#include "S2LP_Types.h"
#include "S2LP_Csma.h"
#include "radio_eeprom.h"
#include "S2LP_Util.h"
#include "radio_timer.h"

#define MC_STATE1_BASE                                  MC_STATE1_ADDR //used in radio-arch.c
#define st_lib_p_spi_handle                             SpiHandle //pSpiHandle 
#define st_lib_radio_cmd_strobe_flush_rx_fifo(...)      S2LPCmdStrobeFlushRxFifo(__VA_ARGS__)
#define st_lib_radio_cmd_strobe_command(...)            S2LPCmdStrobeCommand(__VA_ARGS__)
//#define st_lib_radio_cmd_strobe_sabort(...)		SpiritCmdStrobeSabort(__VA_ARGS__)
#define st_lib_radio_gpio_irq_init(...)                 S2LPGpioInit(__VA_ARGS__)
#define st_lib_radio_irqs                               S2LPIrqs
#define st_lib_radio_irq(...)                           S2LPGpioIrqConfig(__VA_ARGS__)
#define st_lib_radio_irq_de_init(...)                   S2LPGpioIrqDeInit(__VA_ARGS__)
#define st_lib_radio_irq_init(...)                      S2LPGpioIrqInit(__VA_ARGS__)
#define st_lib_radio_irq_get_mask(...)                  S2LPGpioIrqGetMask(__VA_ARGS__)
#define st_lib_radio_irq_get_status(...)                S2LPGpioIrqGetStatus(__VA_ARGS__)
#define st_lib_radio_irq_clear_status(...)              S2LPGpioIrqClearStatus(__VA_ARGS__)
#define st_lib_radio_irq_check_flag(...)                S2LPGpioIrqCheckFlag(__VA_ARGS__)
#define st_lib_FifoSetAlmostEmptyThresholdTx             S2LPFifoSetAlmostEmptyThresholdTx
#define st_lib_radio_linear_fifo_read_num_elements_rx_fifo(...) S2LPFifoReadNumberBytesRxFifo(__VA_ARGS__)
#define st_lib_radio_pkt_basic_init(...)                    S2LPPktBasicInit(__VA_ARGS__)
#define st_lib_radio_pkt_basic_get_received_pkt_length(...) S2LPPktBasicGetReceivedPktLength(__VA_ARGS__)
#define st_lib_radio_pkt_basic_set_payload_length(...)      S2LPPktBasicSetPayloadLength(__VA_ARGS__)
#define st_lib_radio_qi_get_rssi_dbm(...)               S2LPRadioGetRssidBm(__VA_ARGS__)
#define st_lib_radio_qi_get_rssi_dbm_run(...)           S2LPRadioGetRssidBmRun(__VA_ARGS__)
#define st_lib_radio_qi_pqi_check(...)                  S2LPRadioSetPqiCheck(__VA_ARGS__)
#define st_lib_radio_qi_sqi_check(...)                  S2LPRadioSetPqiCheck(__VA_ARGS__)
#define st_lib_radio_qi_set_rssi_threshold_dbm(...)     S2LPRadioSetRssiThreshdBm(__VA_ARGS__)
#define st_lib_radio_qi_get_lqi(...)                    S2LPQiGetLqi(__VA_ARGS__)
#define st_lib_radio_qi_get_rssi(...)                   S2LPRadioGetRssidBm(__VA_ARGS__)
#define st_lib_radio_radio_afc_freeze_on_sync(...)      S2LPRadioAfcInit(__VA_ARGS__)
#define st_lib_radio_radio_init(...)                    S2LPRadioInit(__VA_ARGS__)
#define st_lib_radio_radio_persisten_rx(...)            S2LPPacketHandlerSetRxPersistentMode(__VA_ARGS__)
#define st_lib_radio_radio_set_pa_level_dbm(...)        S2LPRadioSetPALeveldBm(__VA_ARGS__)
#define st_lib_radio_radio_set_pa_level_max_index(...)  S2LPRadioSetPALevelMaxIndex(__VA_ARGS__)
#define st_lib_radio_radio_set_xtal_frequency(...)      S2LPRadioSetXtalFrequency(__VA_ARGS__)
//#define st_lib_radio_radio_cs_blanking(...)		SpiritRadioCsBlanking(__VA_ARGS__)
#define st_lib_s_radio_init                             SRadioInit
#define st_lib_radio_timer_set_rx_timeout_stop_condition(...)  S2LPTimerSetRxTimerStopCondition(__VA_ARGS__)

#define st_lib_radio_bool                               SBool
#define st_lib_radio_status                             S2LPStatus
#define st_lib_radio_flag_status                        SFlagStatus
#define st_lib_radio_refresh_status(...)                S2LPRefreshStatus(__VA_ARGS__)
#define st_lib_radio_csma_init(...)			S2LPCsmaInit(__VA_ARGS__)
#define st_lib_radio_csma(...)				S2LPCsma(__VA_ARGS__)
#define st_lib_CmdStrobeTx      			S2LPCmdStrobeTx  
#define st_lib_QiGetCs                                  S2LPQiGetCs
#define st_lib_radio_Cmd                                S2LPCmd
#define st_lib_FifoReadNumberBytesTxFifo                S2LPFifoReadNumberBytesTxFifo
#define Radio_GPIO_IRQ                                  S2LP_GPIO_3
#define Radio_GPIO_MODE_DIGITAL_OUTPUT_LP               S2LP_GPIO_MODE_DIGITAL_OUTPUT_LP
#define Radio_GPIO_DIG_OUT_IRQ                          S2LP_GPIO_DIG_OUT_IRQ
#define RadioCmdStrobeStandby()                        S2LPCmdStrobeStandby()
#define RadioCmdStrobeSabort()                         S2LPCmdStrobeSabort()
#define RadioCmdStrobeReady()                          S2LPCmdStrobeReady()
#define RadioCmdStrobeRx()                             S2LPCmdStrobeRx() 
#define st_lib_FifoSetAlmostFullThresholdRx            S2LPFifoSetAlmostFullThresholdRx
#define st_lib_radio_spi_init(...)                      S2LPSpiInit(__VA_ARGS__)
#define st_lib_radio_spi_read_linear_fifo(...)          S2LPSpiReadFifo(__VA_ARGS__)
#define st_lib_radio_spi_write_linear_fifo(...)         S2LPSpiWriteFifo(__VA_ARGS__)
#endif /*S2-LP Radio*/

#define st_lib_s_gpio_init                              SGpioInit

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* S2LP_PktBasic.h */

#define st_lib_pkt_basic_init                       PktBasicInit
#define st_lib_radio_qi_set_pqi_threshold(...)      SpiritQiSetPqiThreshold(__VA_ARGS__)
#define st_lib_radio_qi_get_pqi_threshold(...)      SpiritQiGetPqiThreshold(__VA_ARGS__)
#define st_lib_radio_qi_set_sqi_threshold(...)      SpiritQiSetSqiThreshold(__VA_ARGS__)
#define st_lib_radio_qi_get_sqi_threshold(...)      SpiritQiGetSqiThreshold(__VA_ARGS__)
#define st_lib_radio_qi_set_rssi_threshold(...)     SpiritQiSetRssiThreshold(__VA_ARGS__)
#define st_lib_radio_qi_get_rssi_threshold(...)     SpiritQiGetRssiThreshold(__VA_ARGS__)
#define st_lib_radio_qi_compute_rssi_threshold(...) SpiritQiComputeRssiThreshold(__VA_ARGS__)
#define st_lib_radio_qi_get_pqi(...)                SpiritQiGetPqi(__VA_ARGS__)
#define st_lib_radio_qi_get_sqi(...)                SpiritQiGetSqi(__VA_ARGS__)
#define st_lib_radio_qi_get_cs(...)                 SpiritQiGetCs(__VA_ARGS__)
#define st_lib_radio_qi_set_rssi_filter_gain(...)   SpiritQiSetRssiFilterGain(__VA_ARGS__)
#define st_lib_radio_qi_get_rssi_filter_gain(...)   SpiritQiGetRssiFilterGain(__VA_ARGS__)
#define st_lib_radio_qi_set_cs_mode(...)            SpiritQiSetCsMode(__VA_ARGS__)
#define st_lib_radio_qi_get_cs_mode(...)            SpiritQiGetCsMode(__VA_ARGS__)
#define st_lib_radio_qi_cs_timeout_mask(...)        SpiritQiCsTimeoutMask(__VA_ARGS__)
#define st_lib_radio_qi_pqi_timeout_mask(...)       SpiritQiPqiTimeoutMask(__VA_ARGS__)
#define st_lib_radio_qi_sqi_timeout_mask(...)       SpiritQiSqiTimeoutMask(__VA_ARGS__)
#define st_lib_irq_n_type                        IRQn_Type
#define st_lib_flag_status                       FlagStatus
#define st_lib_hal_nvic_enable_irq(...)           HAL_NVIC_EnableIRQ(__VA_ARGS__)
#define st_lib_hal_nvic_set_priority(...)         HAL_NVIC_SetPriority(__VA_ARGS__)
#define st_lib_hal_systick_clk_source_config(...) HAL_SYSTICK_CLKSourceConfig(__VA_ARGS__)
#define st_lib_hal_systick_config(...)            HAL_SYSTICK_Config(__VA_ARGS__)
#define st_lib_hal_rcc_get_hclk_freq(...)		  HAL_RCC_GetHCLKFreq(__VA_ARGS__)
#define st_lib_tim2_clk_enable(...)              __TIM2_CLK_ENABLE(__VA_ARGS__)
#define st_lib_tim5_clk_enable(...)              __TIM5_CLK_ENABLE(__VA_ARGS__)
#define st_lib_spi_handle_typedef                SPI_HandleTypeDef
#define st_lib_hal_spi_get_flag(...)             __HAL_SPI_GET_FLAG(__VA_ARGS__)
#define st_lib_hal_spi_transmit_receive(...)     HAL_SPI_TransmitReceive(__VA_ARGS__)
#define st_lib_tim_handle_typedef                TIM_HandleTypeDef
#define st_lib_tim_clock_config_typedef          TIM_ClockConfigTypeDef
#define st_lib_tim_oc_init_typedef               TIM_OC_InitTypeDef
#define st_lib_hal_tim_base_init(...)            HAL_TIM_Base_Init(__VA_ARGS__)
#define st_lib_hal_tim_base_start_it(...)        HAL_TIM_Base_Start_IT(__VA_ARGS__)
#define st_lib_hal_tim_config_clock_source(...)  HAL_TIM_ConfigClockSource(__VA_ARGS__)
#define st_lib_hal_tim_clear_flag(...)           __HAL_TIM_CLEAR_FLAG(__VA_ARGS__)
#define st_lib_hal_tim_clear_it(...)             __HAL_TIM_CLEAR_IT(__VA_ARGS__)
#define st_lib_hal_tim_enable(...)               __HAL_TIM_ENABLE(__VA_ARGS__)
#define st_lib_hal_tim_enable_it(...)            __HAL_TIM_ENABLE_IT(__VA_ARGS__)
#define st_lib_hal_tim_oc_init(...)              HAL_TIM_OC_Init(__VA_ARGS__)
#define st_lib_hal_tim_oc_config_channel(...)    HAL_TIM_OC_ConfigChannel(__VA_ARGS__)
#define st_lib_uart_handle_typedef               UART_HandleTypeDef
#define st_lib_hal_uart_enable_it(...)           __HAL_UART_ENABLE_IT(__VA_ARGS__)
#define st_lib_hal_uart_init(...)                HAL_UART_Init(__VA_ARGS__)
#define st_lib_hal_uart_receive(...)             HAL_UART_Receive(__VA_ARGS__)
#define st_lib_hal_uart_receive_it(...)          HAL_UART_Receive_IT(__VA_ARGS__)
#define st_lib_hal_uart_rx_cplt_callback(...)    HAL_UART_RxCpltCallback(__VA_ARGS__)
#define st_lib_hal_uart_transmit(...)            HAL_UART_Transmit(__VA_ARGS__)
#define st_lib_gpio_typedef                      GPIO_TypeDef
#define st_lib_bsp_led_init(...)                 BSP_LED_Init(__VA_ARGS__)
#define st_lib_bsp_led_off(...)                  BSP_LED_Off(__VA_ARGS__)
#define st_lib_bsp_led_on(...)                   BSP_LED_On(__VA_ARGS__)
#define st_lib_bsp_pb_init(...)                  BSP_PB_Init(__VA_ARGS__)
#define st_lib_bsp_pb_get_state(...)             BSP_PB_GetState(__VA_ARGS__)
#define st_lib_hal_gpio_read_pin(...)            HAL_GPIO_ReadPin(__VA_ARGS__)
#define st_lib_hal_gpio_write_pin(...)           HAL_GPIO_WritePin(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

#if COMPILE_SENSORS
/*---------------------------------------------------------------------------*/
#ifdef USE_IKS01A1
#include "x_nucleo_iks01a1.h"
#include "x_nucleo_iks01a1_accelero.h"
#include "x_nucleo_iks01a1_gyro.h"
#include "x_nucleo_iks01a1_magneto.h"
#include "x_nucleo_iks01a1_humidity.h"
#include "x_nucleo_iks01a1_temperature.h"
#include "x_nucleo_iks01a1_pressure.h"
#else
#include "x_nucleo_iks01a2.h"
#include "x_nucleo_iks01a2_accelero.h"
#include "x_nucleo_iks01a2_gyro.h"
#include "x_nucleo_iks01a2_magneto.h"
#include "x_nucleo_iks01a2_humidity.h"
#include "x_nucleo_iks01a2_temperature.h"
#include "x_nucleo_iks01a2_pressure.h"
#endif /*USE_IKS01Ax*/

/* x_nucleo_iks01ax.h */
#define st_lib_sensor_axes_raw_t                SensorAxesRaw_t
#define st_lib_sensor_axes_t                    SensorAxes_t
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01ax_temperature.h */

#define st_lib_bsp_temperature_init(...)           BSP_TEMPERATURE_Init(__VA_ARGS__)
#define st_lib_bsp_temperature_sensor_enable(...)  BSP_TEMPERATURE_Sensor_Enable(__VA_ARGS__)
#define st_lib_bsp_temperature_sensor_disable(...) BSP_TEMPERATURE_Sensor_Disable(__VA_ARGS__)
#define st_lib_bsp_temperature_is_initialized(...) BSP_TEMPERATURE_IsInitialized(__VA_ARGS__)
#define st_lib_bsp_temperature_get_temp(...)       BSP_TEMPERATURE_Get_Temp(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01ax_humidity.h */

#define st_lib_bsp_humidity_init(...)           BSP_HUMIDITY_Init(__VA_ARGS__)
#define st_lib_bsp_humidity_sensor_enable(...)  BSP_HUMIDITY_Sensor_Enable(__VA_ARGS__)
#define st_lib_bsp_humidity_sensor_disable(...) BSP_HUMIDITY_Sensor_Disable(__VA_ARGS__)
#define st_lib_bsp_humidity_is_initialized(...) BSP_HUMIDITY_IsInitialized(__VA_ARGS__)
#define st_lib_bsp_humidity_get_hum(...)        BSP_HUMIDITY_Get_Hum(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01ax_accelero.h */

#define st_lib_bsp_accelero_init(...)           BSP_ACCELERO_Init(__VA_ARGS__)
#define st_lib_bsp_accelero_sensor_enable(...)  BSP_ACCELERO_Sensor_Enable(__VA_ARGS__)
#define st_lib_bsp_accelero_sensor_disable(...) BSP_ACCELERO_Sensor_Disable(__VA_ARGS__)
#define st_lib_bsp_accelero_is_initialized(...) BSP_ACCELERO_IsInitialized(__VA_ARGS__)
#define st_lib_bsp_accelero_get_axes(...)       BSP_ACCELERO_Get_Axes(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01ax_gyro.h */

#define st_lib_bsp_gyro_init(...)           BSP_GYRO_Init(__VA_ARGS__)
#define st_lib_bsp_gyro_sensor_enable(...)  BSP_GYRO_Sensor_Enable(__VA_ARGS__)
#define st_lib_bsp_gyro_sensor_disable(...) BSP_GYRO_Sensor_Disable(__VA_ARGS__)
#define st_lib_bsp_gyro_is_initialized(...) BSP_GYRO_IsInitialized(__VA_ARGS__)
#define st_lib_bsp_gyro_get_axes(...)       BSP_GYRO_Get_Axes(__VA_ARGS__)
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01ax_magneto.h */

#define st_lib_bsp_magneto_init(...)           BSP_MAGNETO_Init(__VA_ARGS__)
#define st_lib_bsp_magneto_sensor_enable(...)  BSP_MAGNETO_Sensor_Enable(__VA_ARGS__)
#define st_lib_bsp_magneto_sensor_disable(...) BSP_MAGNETO_Sensor_Disable(__VA_ARGS__)
#define st_lib_bsp_magneto_is_initialized(...) BSP_MAGNETO_IsInitialized(__VA_ARGS__)
#define st_lib_bsp_magneto_get_axes(...)       BSP_MAGNETO_Get_Axes(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01ax_pressure.h */

#define st_lib_bsp_pressure_init(...)            BSP_PRESSURE_Init(__VA_ARGS__)
#define st_lib_bsp_pressure_sensor_enable(...)   BSP_PRESSURE_Sensor_Enable(__VA_ARGS__)
#define st_lib_bsp_pressure_sensor_disable(...)  BSP_PRESSURE_Sensor_Disable(__VA_ARGS__)
#define st_lib_bsp_pressure_is_initialized(...)  BSP_PRESSURE_IsInitialized(__VA_ARGS__)
#define st_lib_bsp_pressure_get_press(...)       BSP_PRESSURE_Get_Press(__VA_ARGS__)
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#endif /*COMPILE_SENSORS*/
/*---------------------------------------------------------------------------*/

#ifdef X_NUCLEO_6180XA1
#include "x-nucleo-6180xa1.h"
#include "main.h"
#define st_lib_vl6180x_init(...)				Init_VL6180X_ProximitySens(__VA_ARGS__)//Proximity_Init(__VA_ARGS__)
#define st_lib_vl6180x_kickoff(...)				Kickoff_VL6180X_ProximitySen(__VA_ARGS__)
#define st_lib_vl6180x_get_range(...)				RdFligthSense_Distance(__VA_ARGS__)//Proximity_GetRange(__VA_ARGS__)
#endif
/*---------------------------------------------------------------------------*/
#endif /*ST_LIB_H_*/



/*---------------------------------------------------------------------------*/
/** @} */
