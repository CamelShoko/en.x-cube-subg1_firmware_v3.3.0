/**
  ******************************************************************************
  * @file    USB_Device/HID_Standalone/Src/stm32l1xx_it.c
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    27-Apr-2021
  * @brief   Main Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2021 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
    
#ifdef USE_SPIRIT1_DEFAULT
    
/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "cube_hal.h"
#include "radio_shield_config.h"
#include "radio_gpio.h"
#include "radio_hal.h"
#include "wmbus_phy.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
//void HardFault_Handler(void)
//{
  /* Go to infinite loop when Hard Fault exception occurs */
//  while (1)
//  {
//  }
//}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}

/**
* @brief  This function handles External line 0 interrupt request.
* @param  None
* @retval None
*/
void EXTI0_IRQHandler(void)
{
  /* EXTI line 0 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
  } 
}

/**
* @brief  This function handles External line 1 interrupt request.
* @param  None
* @retval None
*/
void EXTI1_IRQHandler(void)
{
  /* EXTI line 1 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
  }  
}
/**
* @brief  This function handles External line 2 interrupt request.
* @param  None
* @retval None
*/
void EXTI2_IRQHandler(void)
{
  /* EXTI line 2 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_2) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
  }
}

/**
* @brief  This function handles External line 3 interrupt request.
* @param  None
* @retval None
*/
void EXTI3_IRQHandler(void)
{
  /* EXTI line 3 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
  }  
}

/**
* @brief  This function handles External line 4 interrupt request.
* @param  None
* @retval None
*/
void EXTI4_IRQHandler(void)
{
  /* EXTI line 4 interrupt detected */
}

/**
* @brief  This function handles External lines 5 to 9 interrupt request.
* @param  None
* @retval None
*/
void EXTI9_5_IRQHandler(void)
{
  /* EXTI line 7 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(RADIO_GPIO_3_EXTI_LINE) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(RADIO_GPIO_3_EXTI_LINE);
    
    WMBus_PhyInterruptHandler();
  } 
}

/**
* @brief  This function handles External lines 10 to 15 interrupt request.
* @param  None
* @retval None
*/
void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(USER_BUTTON_PIN);
   /* EXTI line 13 interrupt detected */
  
}


/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx.s).                                               */
/******************************************************************************/


/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

#endif


#ifdef USE_S2_LP_DEFAULT

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "stm32l1xx_nucleo.h"
#include "cube_hal.h"
#include "radio_gpio.h"
#include "radio_hal.h"
#include "wmbus_phy.h"
#include "uart.h"
#include "user_config.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t SysTickTimeStamp = 0;

/* Exported variables ---------------------------------------------------------*/
extern UART_HandleTypeDef Huart2;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
* @brief  This function handles NMI exception.
* @param  None
* @retval None
*/
void NMI_Handler(void)
{
}

/**
* @brief  This function handles Hard Fault exception.
* @param  None
* @retval None
*/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Memory Manage exception.
* @param  None
* @retval None
*/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Bus Fault exception.
* @param  None
* @retval None
*/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Usage Fault exception.
* @param  None
* @retval None
*/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles SVCall exception.
* @param  None
* @retval None
*/
void SVC_Handler(void)
{
}

/**
* @brief  This function handles Debug Monitor exception.
* @param  None
* @retval None
*/
void DebugMon_Handler(void)
{
}

/**
* @brief  This function handles PendSVC exception.
* @param  None
* @retval None
*/
void PendSV_Handler(void)
{
}

/**
* @brief  This function handles SysTick Handler.
* @param  None
* @retval None
*/
void SysTick_Handler(void)
{
#ifdef DEVICE_TYPE_METER
#ifdef ENABLE_CONTINUOUS_TX
  static uint32_t tCtr = 0;
  
  tCtr++;
  
  if(tCtr == CONTINUOUS_TX_TIME_INTERVAL)
  {
    SW1_PUSHED = 1;
    tCtr = 0;
  }
#endif /*End of ENABLE_CONTINUOUS_TX*/
#endif /*End of DEVICE_TYPE_METER*/ 
  
  SysTickTimeStamp++;
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler(); 
}

/**
* @brief  This function handles External line 0 interrupt request.
* @param  None
* @retval None
*/
void EXTI0_IRQHandler(void)
{
  /* EXTI line 7 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(RADIO_GPIO_3_EXTI_LINE) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(RADIO_GPIO_3_EXTI_LINE);
    
    WMBus_PhyInterruptHandler();
  } 
  
}


/**
* @brief  This function handles DMA interrupt request.  
* @param  None
* @retval None
* @Note   This function is redefined in "main.h" and related to DMA  
*         used for USART data transmission     
*/
void USARTx_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(Huart2.hdmarx);
}

/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
* @Note   This function is redefined in "main.h" and related to DMA  
*         used for USART data reception    
*/
void USARTx_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(Huart2.hdmatx);
}

/**
* @brief  This function handles External line 1 interrupt request.
* @param  None
* @retval None
*/
void EXTI1_IRQHandler(void)
{
  /* EXTI line 1 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
  }  
}
/**
* @brief  This function handles External line 2 interrupt request.
* @param  None
* @retval None
*/
void EXTI2_IRQHandler(void)
{
  /* EXTI line 2 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_2) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
  }
}

/**
* @brief  This function handles External line 3 interrupt request.
* @param  None
* @retval None
*/
void EXTI3_IRQHandler(void)
{
  /* EXTI line 3 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
  }  
}

/**
* @brief  This function handles External line 4 interrupt request.
* @param  None
* @retval None
*/
void EXTI4_IRQHandler(void)
{
  /* EXTI line 4 interrupt detected */
}

/**
* @brief  This function handles External lines 10 to 15 interrupt request.
* @param  None
* @retval None
*/
void EXTI15_10_IRQHandler(void)
{
  /* EXTI line 13 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(KEY_BUTTON_EXTI_LINE) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(KEY_BUTTON_EXTI_LINE);
    SW1_PUSHED = 0x01;
#if defined(LPM_ENABLE)
    HAL_GPIO_EXTI_Callback(KEY_BUTTON_EXTI_LINE);
#endif    
  }
}

#endif




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
