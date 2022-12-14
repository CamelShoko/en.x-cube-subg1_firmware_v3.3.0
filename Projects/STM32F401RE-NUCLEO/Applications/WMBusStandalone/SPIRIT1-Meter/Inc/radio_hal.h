/**
******************************************************************************
* @file    radio_hal.h 
* @author  System Lab - NOIDA
* @version V3.3.0
* @date    15-Feb-2021
* @brief   Header for rf_hal.c module
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2021 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RADIO_HAL_H
#define __RADIO_HAL_H
#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
#include "string.h" 
#include "radio_gpio.h" 

#ifdef USE_SPIRIT1_DEFAULT
#include "SPIRIT_Config.h"
#endif

  
#ifdef USE_S2_LP_DEFAULT 
#include "S2LP_Config.h"
#endif
  
  
/** @addtogroup X-NUCLEO-IDS01Ax
  * @{
  */

/** @addtogroup SPIRIT1_SHIELD_HAL_LOW_LEVEL
  * @{
  */
 
/* Exported macro ------------------------------------------------------------*/
      
/* Wireless Meter Bus Specific Configuration----------------------------------*/
  
  
/*  Uncomment the system Operating mode */
//#define USE_LOW_POWER_MODE

#if defined (USE_LOW_POWER_MODE)
 /* #define LPM_ENABLE */
 /* #define MCU_STOP_MODE */
 /* #define MCU_SLEEP_MODE */
#define RF_STANDBY
#endif
/* Exported types ------------------------------------------------------------*/
  
typedef struct sRadioDriver
{
    void ( *Init )( void );
    void (*StartRx)( void );
    void ( *GetRxPacket )(uint8_t *buffer, uint8_t* cRxData );
    void ( *SetTxPacket )(uint8_t *buffer, uint8_t size );
}RadioDriver_t;   

typedef struct sMCULowPowerMode
{
    void ( *McuStopMode )( void );
    void ( *McuStandbyMode )( void );
    void ( *McuSleepMode )( void );      
}MCULowPowerMode_t;

typedef struct sRadioLowPowerMode
{
    void ( *RadioShutDown )( void );
    void ( *RadioStandBy )( void );
    void ( *RadioPowerON )( void );
}RadioLowPowerMode_t; 

/* Exported constants --------------------------------------------------------*/


/* Exported Variables ------------------------------------------------------------*/
extern uint8_t SW1_PUSHED;
extern uint8_t SW2_PUSHED;
extern uint8_t aManufIdBuff[8];
extern uint8_t aMeter_EnKey[16];
extern uint64_t accNum;

/* Exported functions ------------------------------------------------------- */
void Radio_HAL_Init(void); 
void Radio_WMBus_Init(void);
void Radio_WMBus_On(void);
void Enter_LP_mode(void);
void Exit_LP_mode(void);
void MCU_Enter_StopMode(void);
void MCU_Enter_StandbyMode(void);
void MCU_Enter_SleepMode(void);
void RadioPowerON(void);
void RadioPowerOFF(void);
void RadioStandBy(void);

#ifdef USE_S2_LP_DEFAULT

void S2LPStartTx(uint8_t *buffer, uint8_t size );
void S2LPGetRxPacket(uint8_t *buffer, uint8_t *cRxData );
void S2LPStartRx(void);
void S2LP_InterfaceInit(void);

#endif

#ifdef __cplusplus
}
#endif
#endif /*__SPIRIT1_SHIELD_HAL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

