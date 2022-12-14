/**
******************************************************************************
* @file    radio_gpio.c
* @author  Central Labs
* @version V1.0.0
* @date    15-May-2014 
* @brief   This file provides code for the configuration of all used GPIO pins 
for Radio inetrface.
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

/* Includes ------------------------------------------------------------------*/
#include "radio_gpio.h"

/**
* @addtogroup BSP
* @{
*/


/**
* @addtogroup X-NUCLEO-IDS01Ax
* @{
*/


/**
* @defgroup Radio_Gpio_Private_TypesDefinitions       Radio_Gpio Private Types Definitions
* @{
*/

/**
* @}
*/


/**
* @defgroup Radio_Gpio_Private_Defines                Radio_Gpio Private Defines
* @{
*/

/**
* @}
*/


/**
* @defgroup Radio_Gpio_Private_Macros                 Radio_Gpio Private Macros
* @{
*/
#define POR_TIME ((uint16_t)0x1E00)

/**
* @}
*/


/**
* @defgroup Radio_Gpio_Private_Variables              Radio_Gpio Private Variables
* @{
*/

/**
* @brief  Radio_Gpio Port array
*/
GPIO_TypeDef* aRADIO_GPIO_PORT[RADIO_GPIO_NUMBER] = {
  RADIO_GPIO_0_PORT,
  RADIO_GPIO_1_PORT,
  RADIO_GPIO_2_PORT,
  RADIO_GPIO_3_PORT,
  RADIO_GPIO_SDN_PORT
};


/**
* @brief  Radio_Gpio Pin array
*/
static const uint16_t aRADIO_GPIO_PIN[RADIO_GPIO_NUMBER] = {
  RADIO_GPIO_0_PIN,
  RADIO_GPIO_1_PIN,
  RADIO_GPIO_2_PIN,
  RADIO_GPIO_3_PIN,
  RADIO_GPIO_SDN_PIN   
};


/**
* @brief  Radio_Gpio Speed array
*/
static const uint32_t aRADIO_GPIO_SPEED[RADIO_GPIO_NUMBER] = { 
  RADIO_GPIO_0_SPEED,
  RADIO_GPIO_1_SPEED,
  RADIO_GPIO_2_SPEED,
  RADIO_GPIO_3_SPEED,
  RADIO_GPIO_SDN_SPEED    
};


/**
* @brief  Radio_Gpio PuPd array
*/
static const uint32_t aRADIO_GPIO_PUPD[RADIO_GPIO_NUMBER] = {
  RADIO_GPIO_0_PUPD,
  RADIO_GPIO_1_PUPD,
  RADIO_GPIO_2_PUPD,
  RADIO_GPIO_3_PUPD,
  RADIO_GPIO_SDN_PUPD   
};


/**
* @brief  Exti Mode array
*/
static const uint32_t aRADIO_GPIO_EXTI_MODE[RADIO_GPIO_NUMBER-1] = {
  RADIO_GPIO_0_EXTI_MODE,
  RADIO_GPIO_1_EXTI_MODE,
  RADIO_GPIO_2_EXTI_MODE,
  RADIO_GPIO_3_EXTI_MODE     
};


/**
* @brief  Exti IRQn array
*/
static const uint8_t aRADIO_GPIO_IRQn[RADIO_GPIO_NUMBER-1] = {
  RADIO_GPIO_0_EXTI_IRQN,
  RADIO_GPIO_1_EXTI_IRQN,
  RADIO_GPIO_2_EXTI_IRQN,
  RADIO_GPIO_3_EXTI_IRQN  
};


/**
* @}
*/


/**
* @defgroup Radio_Gpio_Private_FunctionPrototypes     Radio_Gpio Private Function Prototypes
* @{
*/
void RadioExitShutdown(void);
void RadioEnterShutdown(void);
void RadioGpioSetLevel(RadioGpioPin xGpio, GPIO_PinState xState);
FlagStatus RadioGpioGetLevel(RadioGpioPin xGpio);
void RadioGpioInterruptCmd(RadioGpioPin xGpio, uint8_t nPreemption, uint8_t nSubpriority, FunctionalState xNewState);
void RadioGpioInit(RadioGpioPin xGpio, RadioGpioMode xGpioMode);
FlagStatus RadioCheckShutdown(void);
/**
* @}
*/


/**
* @defgroup Radio_Gpio_Private_Functions              Radio_Gpio Private Functions
* @{
*/


/**
* @brief  Configures MCU GPIO and EXTI Line for GPIOs.
* @param  xGpio Specifies the GPIO to be configured.
*         This parameter can be one of following parameters:
*         @arg GPIO_0
*         @arg GPIO_1
*         @arg GPIO_2
*         @arg GPIO_3
* @param  xGpioMode Specifies GPIO mode.
*         This parameter can be one of following parameters:
*         @arg RADIO_MODE_GPIO_IN: MCU GPIO will be used as simple input.
*         @argRADIO_MODE_GPIO_OUT: MCU GPIO will be used as simple output.
*         @arg RADIO_MODE_EXTI_IN: MCU GPIO will be connected to EXTI line with interrupt
*         generation capability.
* @retval None.
*/
void RadioGpioInit(RadioGpioPin xGpio, RadioGpioMode xGpioMode)
{
  GPIO_InitTypeDef GPIO_InitStructure, EXTI_InitStructure;
  
  /* Check the parameters */
  assert_param(IS_M2S_GPIO_PIN(xGpio));
  assert_param(IS_M2S_GPIO_MODE(xGpioMode));
  
  switch(xGpio)
  {
  case RADIO_GPIO_0:
    RADIO_GPIO_0_CLOCK_ENABLE();
    break;
  case RADIO_GPIO_1:
    RADIO_GPIO_1_CLOCK_ENABLE();
    break;
  case RADIO_GPIO_2:
    RADIO_GPIO_2_CLOCK_ENABLE();
    break;
  case RADIO_GPIO_3:
    RADIO_GPIO_3_CLOCK_ENABLE();
    break;
  case RADIO_GPIO_SDN:
    RADIO_GPIO_SDN_CLOCK_ENABLE();
    break;
  }
  
  /* Configures MCU GPIO */
  if(xGpioMode == RADIO_MODE_GPIO_OUT)
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  else
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  
  GPIO_InitStructure.Pull = aRADIO_GPIO_PUPD[xGpio];
  GPIO_InitStructure.Speed = aRADIO_GPIO_SPEED[xGpio];
  GPIO_InitStructure.Pin = aRADIO_GPIO_PIN[xGpio];
  HAL_GPIO_Init(aRADIO_GPIO_PORT[xGpio], &GPIO_InitStructure);
  
  /* Configures MCU GPIO EXTI line */
  EXTI_InitStructure.Pull = aRADIO_GPIO_PUPD[xGpio];
  EXTI_InitStructure.Mode = aRADIO_GPIO_EXTI_MODE[xGpio];
  EXTI_InitStructure.Pin = aRADIO_GPIO_PIN[xGpio];
  EXTI_InitStructure.Speed = aRADIO_GPIO_SPEED[xGpio];
  
  if (xGpioMode == RADIO_MODE_EXTI_IN) {
    HAL_GPIO_Init(aRADIO_GPIO_PORT[xGpio], &EXTI_InitStructure);
    
  }
  
}

/**
* @brief  Enables or disables the interrupt on GPIO .
* @param  xGpio Specifies the GPIO whose priority shall be changed.
*         This parameter can be one of following parameters:
*         @arg M2S_GPIO_0: GPIO_0
*         @arg M2S_GPIO_1: GPIO_1
*         @arg M2S_GPIO_2: GPIO_2
*         @arg M2S_GPIO_3: GPIO_3
* @param  nPreemption Specifies Preemption Priority.
* @param  nSubpriority Specifies Subgroup Priority.
* @param  xNewState Specifies the State.
*         This parameter can be one of following parameters:
*         @arg ENABLE: Interrupt is enabled
*         @arg DISABLE: Interrupt is disabled
* @retval None.
*/
/*@TODO: added semaphore irq_disable_cnt, validate*/
static volatile int irq_disable_cnt = 0;
void RadioGpioInterruptCmd(RadioGpioPin xGpio, uint8_t nPreemption, uint8_t nSubpriority, FunctionalState xNewState)
{
  if (xNewState == ENABLE)  
  {
     if (irq_disable_cnt > 0)                                         
       irq_disable_cnt--;                                             
     if (irq_disable_cnt==0)
     {
       HAL_NVIC_EnableIRQ((IRQn_Type)aRADIO_GPIO_IRQn[xGpio]);
       HAL_NVIC_SetPriority((IRQn_Type)aRADIO_GPIO_IRQn[xGpio], nPreemption, nSubpriority);
     }
  }
  else 
  {
    irq_disable_cnt++; 
    HAL_NVIC_DisableIRQ((IRQn_Type)aRADIO_GPIO_IRQn[xGpio]);
  }
}


/**
* @brief  Returns the level of a specified GPIO.
* @param  xGpio Specifies the GPIO to be read.
*         This parameter can be one of following parameters:
*         @arg M2S_GPIO_0: GPIO_0
*         @arg M2S_GPIO_1: GPIO_1
*         @arg M2S_GPIO_2: GPIO_2
*         @arg M2S_GPIO_3: GPIO_3
* @retval FlagStatus Level of the GPIO. This parameter can be:
*         SET or RESET.
*/
FlagStatus RadioGpioGetLevel(RadioGpioPin xGpio)
{
  /* Gets the GPIO level */
  GPIO_PinState ret = HAL_GPIO_ReadPin(aRADIO_GPIO_PORT[xGpio], aRADIO_GPIO_PIN[xGpio]);
  
  return (FlagStatus)ret;
}


/**
* @brief  Sets the level of a specified GPIO.
* @param  xGpio Specifies the GPIO to be set.
*         This parameter can be one of following parameters:
*         @arg M2S_GPIO_0: GPIO_0
*         @arg M2S_GPIO_1: GPIO_1
*         @arg M2S_GPIO_2: GPIO_2
*         @arg M2S_GPIO_3: GPIO_3
* @param  FlagStatus Level of the GPIO. This parameter can be:
*         SET or RESET.
* @retval None.
*/
void RadioGpioSetLevel(RadioGpioPin xGpio, GPIO_PinState xState)
{
  /* Sets the GPIO level */
  HAL_GPIO_WritePin(aRADIO_GPIO_PORT[xGpio], aRADIO_GPIO_PIN[xGpio], (GPIO_PinState)xState);
}


/**
* @brief  Puts at logic 1 the SDN pin.
* @param  None.
* @retval None.
*/
void RadioEnterShutdown(void)
{
  /* Puts high the GPIO connected to shutdown pin */
  HAL_GPIO_WritePin(RADIO_GPIO_SDN_PORT, RADIO_GPIO_SDN_PIN, GPIO_PIN_SET);
}


/**
* @brief  Put at logic 0 the SDN pin.
* @param  None.
* @retval None.
*/
void RadioExitShutdown(void)
{
  /* Puts low the GPIO connected to shutdown pin */
  HAL_GPIO_WritePin(RADIO_GPIO_SDN_PORT, RADIO_GPIO_SDN_PIN, GPIO_PIN_RESET);
  
  /* Delay to allow the circuit POR, about 700 us */
  for(volatile uint32_t i=0;i<0x1E00;i++);
}


/**
* @brief  check the logic(0 or 1) at the SDN pin.
* @param  None.
* @retval FlagStatus.
*/
FlagStatus RadioCheckShutdown(void)
{
  return RadioGpioGetLevel(RADIO_GPIO_SDN);
}

/**
* @brief  Configure Range ext (PA).
* @param  None.
* @retval None.
*/
/*  gpio0 :  PA0 : CSD
    gpio1 :  PA4 : CPS
    gpio2 :  PB0 : CTX */
void RangeExtGpioInit()
{
    /* Configures MCU GPIOs to drive external PA */
    GPIO_InitTypeDef GPIO_InitStructure;

    /*CSD*/
    PA_CSD_GPIO_CLK();
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pin = PA_CSD_PIN;
    HAL_GPIO_Init(PA_CSD_PORT, &GPIO_InitStructure);

    /*CPS*/
    PA_CPS_GPIO_CLK();
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pin = PA_CPS_PIN;
    HAL_GPIO_Init(PA_CPS_PORT, &GPIO_InitStructure);

    /*CTX*/
    PA_CTX_GPIO_CLK();
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pin = PA_CTX_PIN;
    HAL_GPIO_Init(PA_CTX_PORT, &GPIO_InitStructure);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
