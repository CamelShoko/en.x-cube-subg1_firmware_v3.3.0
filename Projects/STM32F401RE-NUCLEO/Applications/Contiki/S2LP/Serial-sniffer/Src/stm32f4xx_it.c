/**
******************************************************************************
* @file    stm32f4xx_it.c
* @author  SRA
* @version V1.1.0
* @date    28-May-2019
* @brief   Main Interrupt Service Routines
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
#include "main.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_nucleo.h"
#include "sensors.h"



/** @addtogroup F4
* @ingroup Serial_Sniffer
* @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

extern UART_HandleTypeDef UartHandle;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
extern const struct sensors_sensor button_sensor;
extern volatile unsigned long seconds;
extern volatile clock_time_t ticks;

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
* @brief   This function handles NMI exception.
* @param  None
* @retval None
*/
void NMI_Handler(void)
{
}
/*----------------------------------------------------------------------------*/
void WWDG_IRQHandler(void)
{
  while(1);
}
/*----------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------*/
/**
* @brief  This function handles Memory Manage exception.
* @param  None
* @retval None
*/
/*----------------------------------------------------------------------------*/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}
/*----------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------*/
/**
* @brief  This function handles SVCall exception.
* @param  None
* @retval None
*/
void SVC_Handler(void)
{
}
/*----------------------------------------------------------------------------*/
/**
* @brief  This function handles Debug Monitor exception.
* @param  None
* @retval None
*/
void DebugMon_Handler(void)
{
}
/*----------------------------------------------------------------------------*/
/**
* @brief  This function handles PendSVC exception.
* @param  None
* @retval None
*/
void PendSV_Handler(void)
{
}
/*----------------------------------------------------------------------------*/
/**
* @brief  This function handles External lines 15 to 4 interrupt request.
* @param  None
* @retval None
*/
void EXTI0_IRQHandler(void)
{
  /* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
    
#if defined(X_NUCLEO_S2868A1) || defined(X_NUCLEO_S2915A1)
    HAL_GPIO_EXTI_Callback(GPIO_PIN_0);
    
    Radio_interrupt_callback();      
#endif /*defined(X_NUCLEO_S2868A1) || defined(X_NUCLEO_S2915A1)*/
    
  }
}
/*----------------------------------------------------------------------------*/
void EXTI1_IRQHandler(void)
{
  /* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
  }
  while(1);
}
/*----------------------------------------------------------------------------*/
void EXTI2_IRQHandler(void)
{
  /* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_2) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
  }
  while(1);
}
/*----------------------------------------------------------------------------*/
void EXTI3_IRQHandler(void)
{
  /* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
  }
  while(1);
}
/*----------------------------------------------------------------------------*/
/**
* @brief  This function handles External lines 9 to 5 interrupt request.
* @param  None
* @retval None
*/
void EXTI9_5_IRQHandler(void)
{
#if defined(X_NUCLEO_IDS01A4) || defined(X_NUCLEO_IDS01A5)
  /* EXTI line 7 interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(RADIO_GPIO_3_EXTI_LINE))
  {
    __HAL_GPIO_EXTI_CLEAR_IT(RADIO_GPIO_3_EXTI_LINE);
    
    HAL_GPIO_EXTI_Callback(RADIO_GPIO_3_EXTI_LINE);
    
    Radio_interrupt_callback();
  }
  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
  
  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);
  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
#endif /*defined(X_NUCLEO_IDS01A4) || defined(X_NUCLEO_IDS01A5)*/
}
/*----------------------------------------------------------------------------*/
/**
* @brief  This function handles EXTI15_10_IRQHandler
* @param  None
* @retval None
*/
void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(USER_BUTTON_PIN);
}
/*----------------------------------------------------------------------------*/
/**
* @brief  This function handles UART interrupt request.
* @param  None
* @retval None
*/
#ifdef USE_USART2
void USART2_IRQHandler(void)
{
  UART_HandleTypeDef *huart = &UartHandle;
  
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_PE)){
    __HAL_UART_CLEAR_PEFLAG(huart);
  }
  
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_FE)){
    __HAL_UART_CLEAR_FEFLAG(huart);
  }
  
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_NE)){
    __HAL_UART_CLEAR_NEFLAG(huart);
  }
  
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE)){
    __HAL_UART_CLEAR_OREFLAG(&UartHandle);
  }
  
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE)){
    //slip_input_byte(UartHandle.Instance->DR);/*Uncomment this line if slip needs to be enabled*/
  }
}
#endif /*USE_USART2*/
/*----------------------------------------------------------------------------*/
#ifdef USE_USART6
void USART6_IRQHandler(void)
{
  UART_HandleTypeDef *huart = &UartHandle;
  
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_PE)){
    __HAL_UART_CLEAR_PEFLAG(huart);
  }
  
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_FE)){
    __HAL_UART_CLEAR_FEFLAG(huart);
  }
  
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_NE)){
    __HAL_UART_CLEAR_NEFLAG(huart);
  }
  
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE)){
    __HAL_UART_CLEAR_OREFLAG(&UartHandle);
  }
  
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE)){
    //slip_input_byte(UartHandle.Instance->DR);/*Uncomment this line if slip needs to be enabled*/
  }
}
#endif /*USE_USART6*/
/*----------------------------------------------------------------------------*/
/**
* @brief  This function handles TIM5 interrupt request.
* @param  None
* @retval None
*/
void TIM5_IRQHandler(void)
{
  if (__HAL_TIM_GET_FLAG(&htim5, TIM_FLAG_UPDATE)) {
	  __HAL_TIM_CLEAR_FLAG(&htim5, TIM_FLAG_UPDATE);
  }
  if (__HAL_TIM_GET_FLAG(&htim5, TIM_FLAG_CC1)){
	  __HAL_TIM_CLEAR_FLAG(&htim5, TIM_FLAG_CC1);
	  __HAL_TIM_DISABLE_IT(&htim5,TIM_IT_CC1);
	  rtimer_run_next();
  }
}
/*----------------------------------------------------------------------------*/
/**
* @brief  This function handles TIM2 interrupt request.
* @param  None
* @retval None
*/
void TIM2_IRQHandler(void)
{
  __HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
}
/*----------------------------------------------------------------------------*/
/**
* @brief  Tx Transfer completed callback
* @param  UartHandle: UART handle.
* @note   This example shows a simple way to report end of IT Tx transfer, and
*         you can add your own implementation.
* @retval None
*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  
}
/*----------------------------------------------------------------------------*/
/**
* @brief  Systick Handler
* @param  None
* @retval None
*/
#if defined(X_NUCLEO_S2868A1) || defined(X_NUCLEO_S2915A1)
extern volatile uint32_t lSystickCounter;
#endif /*defined(X_NUCLEO_S2868A1) || defined(X_NUCLEO_S2915A1)*/
/*----------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
#if defined(X_NUCLEO_S2868A1) || defined(X_NUCLEO_S2915A1)
  lSystickCounter++;
#endif /*defined(X_NUCLEO_S2868A1) || defined(X_NUCLEO_S2915A1)*/
  
  HAL_IncTick();
  Contiki_SysTick_Handler();
}
/*----------------------------------------------------------------------------*/
/**
* @brief  Systick Handler for Contiki timings
* @param  None
* @retval None
*/
void Contiki_SysTick_Handler(void)
{
  ticks++;
  if((ticks % CLOCK_SECOND) == 0) {
    seconds++;
    energest_flush();
  }
  
  if(etimer_pending()) {
    etimer_request_poll();
  }
}
/*----------------------------------------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
#if defined(X_NUCLEO_IDS01A4) || defined(X_NUCLEO_IDS01A5)
  /* Initialize LEDs*/
  RadioShieldLedInit(RADIO_SHIELD_LED);
  BSP_LED_Init(LED2);
#endif /*defined(X_NUCLEO_IDS01A4) || defined(X_NUCLEO_IDS01A5)*/
  
  if (GPIO_Pin == USER_BUTTON_PIN)
  {
    sensors_changed(&button_sensor);
  }
}
/*----------------------------------------------------------------------------*/
/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
