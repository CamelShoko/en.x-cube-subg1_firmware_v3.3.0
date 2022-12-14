/**
  ******************************************************************************
  * @file    stm32l1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "cube_hal.h"
#include "radio_shield_config.h"
#include "radio_appli.h"
#include "radio_gpio.h"

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
#if defined(X_NUCLEO_S2868A1) || defined(X_NUCLEO_S2915A1)
extern volatile uint32_t lSystickCounter;
#endif

void SysTick_Handler(void)
{
#if defined(X_NUCLEO_S2868A1) || defined(X_NUCLEO_S2915A1)
  lSystickCounter++;
#endif
  
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
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
    // __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
    
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
    //__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  }
}


void EXTI9_5_IRQHandler(void)
{
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
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
    //__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  }  
}

void EXTI15_10_IRQHandler(void)
{
  
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
  }
  
}


void EXTI0_IRQHandler(void)
{
  
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
    P2PInterruptHandler();
  }
}

void EXTI4_IRQHandler(void)
{
  
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_4) != RESET) 
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
