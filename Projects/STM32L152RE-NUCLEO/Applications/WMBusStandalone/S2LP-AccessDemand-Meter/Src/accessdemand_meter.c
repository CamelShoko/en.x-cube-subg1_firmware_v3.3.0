/**
******************************************************************************
* @file    accessdemand_meter.c
* @author  System Lab - NOIDA / RF application group - AMG
 * @version V3.3.0
 * @date    27-Apr-2021
* @brief   WMBus Example for Access Demand for Meter Devices 
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
#include "wmbus_transport_utils.h"
#include "uart.h"
#include "user_config.h"
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
* @addtogroup Access_Demand        Access Demand
* @{
*/

/**
* @addtogroup accessdemand_meter                 Access demand Meter
* @{
*/


/**
* @defgroup accessdemand_meter_Private_Variables      Access Demand Meter Private Variables
* @{
*/


static uint8_t encryption_key[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                        0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x11};

static uint8_t have_class1_data=0;
uint8_t AccDmdCompleteFlag = 1;

/**
*@}
*/

/**
* @defgroup accessdemand_meter_Private_Functions         Access Demand Meter Private Functions
* @{
*/

/**
* @brief  This function is used to send Access Demand,Once User Key is Detected.
* @param  None.
* @retval None.
*/
void AccDmdMeterApplication(void)
{
  static uint8_t acc_num=0x96;
  static uint8_t payload[4]={0};
  
  
  if(SW1_PUSHED)
  {
    SW1_PUSHED = 0;   
        
    have_class1_data=1;
    
    WMBus_SetConfigWord(payload,0x7A,0);
    WMBus_SetAccessNum(payload,0x7A,acc_num++);

    WMBus_LinkSendAccessDemand(payload, 4, 0x7A);  
    
    PRINTF("Sending ACC-DMD\n\r");
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
    if(AccDmdCompleteFlag)
    {
      AccDmdCompleteFlag = 0;
      SystemPower_Config();  
      Enter_LP_mode();
    }
#endif
    
    /* Application buisness */
    AccDmdMeterApplication();
    
    /* Link layer state machine */
    WMBus_LinkLayer_SM(); 
  }
}



/**
* @brief  This callback is called when ACK is Received (at meter)
* @param  frame: Pointer to the Frame.
* @retval Success/Error
*/
void WMBus_LinkAckReceived_CB(Frame_t *frame)
{  
  static uint8_t payload[4]={0};
  
  WMBus_SetConfigWord(payload,0x7A,0);
  WMBus_SetAccessNum(payload,0x7A,WMBus_GetAccessNum(frame));
  
  /* send a SND_NR with CI=short tl*/
  WMBus_LinkSendAccess_NoReply(payload,4,0x7A);
  
  PRINTF("ACK received , ACC_NR sent\n\r");

}


/**
* @brief  This callback is called when ACK is not received at Meter
*          before Timeout
* @param  None.
* @retval Success/Error
*/
void WMBus_LinkAckTimeout_CB(void)
{
  PRINTF("ACK timeout, impossible to reach the OTHER dev\n\r");
}


/**
* @brief  This callback is called when REQ-UD1 is received.
* @param  frame: Pointer to the Frame.
* @retval Success/Error
*/
void WMBus_LinkRequestUd1Received_CB(Frame_t *frame)
{   
  uint16_t enc_size,conf_word=0x0500;
  static uint8_t payload[16+4]={0};
  static uint8_t enc_payload[16+4];
  
  /* here we set the data block */
  {
    /* 2 padding bytes 0x2F to say that data are encrypted */
    payload[4]=0x2F;payload[5]=0x2F;
    /* simulate a data array */
    for(uint8_t i=6;i<12;i++)
      payload[i]=(i-5)+0x10;
    for(uint8_t i=12;i<16+4;i++)
      payload[i]=0x2F;
  }
  
  uint8_t iv[16];
  /* set the init vector of CBC5 */
  WMBus_LinkGetAttribute(LINK_ATTR_ID_M_FIELD,iv);
  WMBus_LinkGetAttribute(LINK_ATTR_ID_A_FIELD,&iv[2]);
  /* acc num 8 times */
  memset(&iv[8], WMBus_GetAccessNum(frame)+1,8);
  
  /*Encrypt data to send , size is 8 because it is payload idx from 4 to 12*/
  enc_size=WMBus_AES_Encrypt_CBC(&payload[4],8,encryption_key,&enc_payload[4],iv);
  SIZE_IN_CONFIG_WORD(conf_word,enc_size);
  
  WMBus_SetConfigWord(enc_payload, 0x7A, conf_word);
  WMBus_SetAccessNum(enc_payload, 0x7A, WMBus_GetAccessNum(frame)+1);
  

  /* suppose we have no more class 1 data */
  WMBus_LinkSetAcd(0);
  
  have_class1_data=0;
  WMBus_LinkSendResponse_UD(enc_payload, enc_size+4, 0x7A);
  
  PRINTF("REQ-UD1 received , RSP-UD sent\n\r");
}


/**
* @brief  This callback is called when REQ-UD2 is received.
*         In this example we suppose we have class 1 data only first time.
* @param  frame: Pointer to the Frame.
* @retval Success/Error
*/
void WMBus_LinkRequestUd2Received_CB(Frame_t *frame)
{  
  uint16_t enc_size,conf_word=0x0500;
  static uint8_t payload[16+4]={0};
  static uint8_t enc_payload[16+4];
  
  /* here we set the data block */
  {
    /* 2 padding bytes 0x2F to say that data are encrypted */
    payload[4]=0x2F;payload[5]=0x2F;
    /* simulate a data array */
    for(uint8_t i=6;i<12;i++)
      payload[i]=(i-5)+0x20;
    for(uint8_t i=12;i<16+4;i++)
      payload[i]=0x2F;
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
  
  /* suppose we have also class 1 data */
  WMBus_LinkSetAcd(have_class1_data);
    
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
  AccDmdCompleteFlag = 1;
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
