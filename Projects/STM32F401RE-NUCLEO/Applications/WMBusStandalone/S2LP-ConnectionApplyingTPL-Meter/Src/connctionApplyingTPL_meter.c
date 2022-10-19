/**
******************************************************************************
* @file    connctionApplyingTPL_meter.c
* @author  System Lab - NOIDA / RF application group - AMG
 * @version V3.3.0
 * @date    27-Apr-2021
* @brief   WMBus Example for Connection applying transport layer (short/long) 
*               for meter devices
*
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


/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "wmbus_phy.h"
#include "wmbus_link.h"
#include "wmbus_linkcommand.h"
#include "wmbus_tim.h"
#include "wmbus_cbc.h"
#include "user_config.h"
#include "wmbus_transport_utils.h"
#include "wmbus_datarecord_utils.h"
#include "uart.h"
#include "radio_hal.h"


/**
* @addtogroup Application Application
* @{
*/

/**
* @addtogroup WMBus_Examples WMBus Examples
* @{
*/


/**
* @addtogroup Connection_Applying_Transport_Layer        Connection Applying Transport Layer
* @{
*/

/**
* @addtogroup connectionApplyingTPL_meter                 Connection Applying Transport Layer Meter
* @{
*/


/**
* @defgroup connectionApplyingTPL_meter_Private_Variables      Connection Applying Transport Layer Meter Private Variables
* @{
*/



uint8_t encryption_key[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                        0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x11};
uint8_t ConnTPLCompleteFlag = 1;

/**
*@}
*/


/**
* @defgroup connectionApplyingTPL_meter_Private_Functions         Connection Applying Transport Layer Meter Private Functions
* @{
*/


/**
* @brief  This function is used to send Application Data based 
*         on User Key.
* @param  None.
* @retval None.
*/
void MeterApplication(void)
{
  static uint8_t acc_num=0x96;
  static uint8_t payload[4]={0};
  
  if(SW1_PUSHED)
  {
    SW1_PUSHED = 0;   
    
    WMBus_SetConfigWord(payload,0x7A,0);
    WMBus_SetAccessNum(payload,0x7A,acc_num++);
    
    WMBus_LinkSendNoReplyApplicationData(payload, 4, 0x7A);  
     
    PRINTF("Sending SND-NR\n\r");
  }   
  
}


/**
* @brief  This is the main application routine.
* @param  None.
* @retval None.
*/
int main (void)
{ 
/* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick*/
  HAL_Init();
  
  /* Configure the system clock */
  SystemClock_Config();
    
  HAL_EnableDBGStopMode();

  /* Initialize LEDs*/
  BSP_LED_Init(LED2);
  
  /* Initialize HAL for S2-LP*/
  Radio_HAL_Init();
  
  /* Initialize wM-Bus Radio*/
  Radio_WMBus_Init();
  
  /* Initialize Buttons*/
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

  /* Initialize UART*/
  uart_init(UART_BAUD_RATE);
  
  /* Overhead Estimation*/
  WMBus_LinkOverHeadEst();
  
  /* ON the LED2*/
  BSP_LED_On(LED2);
  
  /* main loop. 
  Here the application should never block the cpu 
  and the link layer state machine as well. */
  while(1)
  {
#ifdef USE_LOW_POWER_MODE
    if(ConnTPLCompleteFlag)
    {
      ConnTPLCompleteFlag = 0;
      SystemPower_Config();  
      Enter_LP_mode();
    }
#endif
    
    /* Application buisness */
    MeterApplication();
    
    /* Link layer state machine */
    WMBus_LinkLayer_SM(); 
  }
}



/**
* @brief  This callback is called when SND-UD is received at meter 
* @param  frame:Pointer to the Frame.
* @retval Sucess/Error
*/
void WMBus_LinkSendUdReceived_CB(Frame_t *frame)
{
  static uint8_t payload[4]={0};
  
  /* answer only if it is a SND_UD (not SND_UD2) */
  if(LINK_GET_FCV_BIT(frame->c_field))
  {
    WMBus_SetConfigWord(payload,0x7A,0);
    WMBus_SetAccessNum(payload,0x7A,WMBus_GetAccessNum(frame));
    
    /* send a ACK with CI=short tl*/
    WMBus_LinkSendAck(payload,4,0x7A);
    
    
    PRINTF("SND_UD received , ACK sent\n\r");
  }
  
}
  
  
  

/**
* @brief  This callback is called when SND-UD2 or REQ-UD2 is received at meter
* @param  frame: Pointer to the Frame.
* @retval Success/Error
*/
void WMBus_LinkRequestUd2Received_CB(Frame_t *frame)
{  
  uint16_t enc_size,conf_word=0x0500;
  static uint8_t payload[16+4]={0x2F};
  static uint8_t enc_payload[16+4];
  
  /* here we set the data block */
  {
    uint8_t size;
    /* 2 padding bytes 0x2F */
    payload[4]=0x2F;payload[5]=0x2F;
    size=data_record_bcd8_enc(28504.27f, RECORD_TYPE_VOLUME, &payload[6]);
    for(uint8_t i=size+6;i<16+4;i++) payload[i]=0x2F;
  }
  
  uint8_t iv[16];
  /* set the init vector of CBC5 */
  WMBus_LinkGetAttribute(LINK_ATTR_ID_M_FIELD,iv);
  WMBus_LinkGetAttribute(LINK_ATTR_ID_A_FIELD,&iv[2]);
  /* acc num 8 times */
  memset(&iv[8], WMBus_GetAccessNum(frame)+1,8);
  
  /*Encrypt data to send*/
  enc_size=WMBus_AES_Encrypt_CBC(&payload[4],16,encryption_key,&enc_payload[4],iv);
  SIZE_IN_CONFIG_WORD(conf_word,enc_size);
  
  WMBus_SetConfigWord(enc_payload, 0x7A, conf_word);
  WMBus_SetAccessNum(enc_payload, 0x7A, WMBus_GetAccessNum(frame)+1);
  
  /* suppose we don't have class 1 data */
  WMBus_LinkSetAcd(0);
    
  WMBus_LinkSendResponse_UD(enc_payload, enc_size+4, 0x7A);
  
  PRINTF("REQ-UD2 received , RSP-UD sent\n\r");

}



/**
* @brief  This callback is called when SND-NKE is Received at meter side
* @param  frame: Pointer to the Frame.
* @retval Success/Error
*/
void WMBus_LinkSendNkeReceived_CB(Frame_t *frame)
{
  PRINTF("SND-NKE received\n\r");
  ConnTPLCompleteFlag = 1;
}



/**
*@}
*/

/**
*@}
*/

/**
*@}
*/

/**
*@}
*/

/**
*@}
*/
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
