/**
* @file    wmbus_link.h
* @author  SRA- NOIDA
* @version V2.5.1
* @date    14-Sept-2020
* @brief   This file contains routines for LINK LAYER state machine
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2020 STMicroelectronics</center></h2>
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
#ifndef __WMBUS_LINK_H
#define __WMBUS_LINK_H

/* Includes ------------------------------------------------------------------*/
#include "wmbus_phy.h"

/** @addtogroup WMBUS_Library
* @{
*/

 
/** @addtogroup WMBus_LinkLayer   wM-Bus Link Layer
* @brief Configuration and management of WMBus Link layer.
* @{
*/

/** @addtogroup WMBus_Link         WMBus Link
* @brief Configuration and management of WMBus Link layer State machine.
* @details See the file <i>@ref wmbus_link.h</i> for more details.
* @{
*/

/** @defgroup WMBus_Link_Exported_Constants       WMBus Link Exported Constants
* @{
*/

#define LINK_ATTR_ID_START  0x65/*!< Link Layer Attribute Start index*/
#define LINK_ATTR_ID_END    LINK_ATTR_ID_FAC/*!<Link Attribute end id*/
#define MFR_ATTR_SIZE       2/*!< MFR_ID attribute size*/
#define ADDR_ATTR_SIZE      6/*!< Indentification, Device Type and 
version number attribute size*/

#define LINK_C_FIELD_MASK            0x4F/*!<C-Field mask bits*/
#define LINK_C_FIELD_PRM_MASK        0x40/*!<C-Field PRM mask bits*/
#define LINK_C_FIELD_FCB_MASK        0x20/*!<C-Field FCB mask bits*/
#define LINK_C_FIELD_FCV_MASK        0x10/*!<C-Field FCVmask bits*/
#define LINK_C_FIELD_FUNCTION_MASK   0x0F/*!<C-Field Function mask bits*/
#define LINK_C_FIELD_ACD_MASK        0x20/*!<C-Field ACD mask bits*/
#define LINK_C_FIELD_DFC_MASK        0x10/*!<C-Field DFC mask bits*/




#define LINK_GET_FCV_BIT(C_FIELD)               (( (C_FIELD) & LINK_C_FIELD_FCV_MASK )!=0 )
#define LINK_GET_FCB_BIT(C_FIELD)               (( (C_FIELD) & LINK_C_FIELD_FCB_MASK )!=0 )

#define LINK_GET_DFC_BIT(C_FIELD)               (( (C_FIELD) & LINK_C_FIELD_DFC_MASK )!=0 )
#define LINK_GET_ACD_BIT(C_FIELD)               (( (C_FIELD) & LINK_C_FIELD_ACD_MASK )!=0 )

/**
* @}
*/

/** @defgroup WMBus_Link_Exported_Types          WMBus Link Exported Types
* @{
*/


/**
* @brief  WMBus Link Layer Status Enum.
*/
typedef enum 
{
  LINK_STATUS_SUCCESS = 0x00,/*!< No error*/  
  LINK_STATUS_PHY_ERROR,/*!<Indicates PHY Radio error */               
  LINK_STATUS_PHY_ERROR_TIMEOUT,/*!< Link Service is not invoked in proper time*/   
  LINK_STATUS_PHY_ERROR_READ_ONLY_ADDRESS,/*!<The attribute is read only*/
  LINK_STATUS_PHY_ERROR_INVALID_ADDRESS,/*!<Link Status for invalid PHY address*/
  LINK_STATUS_PHY_ERROR_INVALID_VALUE,/*!<Link Status for invalid PHY value*/
  LINK_STATUS_PHY_ERROR_INVALID_STATE,/*!<Link Status for invalid PHY state*/
  LINK_STATUS_PHY_ERROR_INVALID_LENGTH,/*!<Frame size is not valid, 
  length-field is smaller 
  than the min value*/
  LINK_STATUS_PHY_ERROR_NOTHING_RECEIVED,/*!<Indicates response when frame is 
  not received*/
  LINK_STATUS_PHY_ERROR_DECODING,/*!<Link Status for invalid decoding of PHY packet*/
  LINK_STATUS_PHY_ERROR_POR_TIMEOUT,/*!<Link Status for PHY timeout*/
  LINK_STATUS_PHY_ERROR_XTAL_TIMEOUT,/*!<Link Status for PHY XTAL timeout*/
  LINK_STATUS_PHY_ERROR_UNSUPPORTED_RADIO,/*!<Link Status for unsupported PHY Radio*/
  LINK_STATUS_PHY_ERROR_TX_TIMEOUT,/*!<Link Status for PHY transmission timeout*/  
  LINK_STATUS_PHY_ERROR_RX_INVALID_LENGTH,/*!< Received frame size is not valid*/  
  LINK_STATUS_PHY_ERROR_RX_PACKET_INCOMPLETE,/*!<Link Status for incomplete received packet*/
  LINK_STATUS_PHY_STATE_ERROR,/*!<Service request is unsuccessful*/
  
  /* LINK layer status codes */
  LINK_STATUS_INVALID_SIZE = 0x40,/*!<The data-field buffer is too large*/  
  LINK_STATUS_INVALID_ATTR,/*!< The attribute ID is invalid*/
  LINK_STATUS_INVALID_ATTR_VAL,/*!< The attribute value is invalid.*/  
  LINK_STATUS_NOT_PERMITTED,/*!<Link Status for no permission*/ 
  LINK_STATUS_CRC_ERROR,/*!<CRC for first block is invalid*/  
  LINK_STATUS_FRAME_ERROR,/*!<There is not enough data to parse the first block */
  LINK_STATUS_TX_RETRY_ERROR,/*!<Link Status for re-transmission timeout*/
  LINK_STATUS_UNKNOWN_ERROR = 0xFF/*!<Data is not received within the timeout period specified*/
}LINK_STATUS_t;

/**
* @brief  SPIRIT1 WMBus Link Layer Attributes.
*/
typedef enum 
{ 
  LINK_ATTR_ID_DEV_TYPE = LINK_ATTR_ID_START,/*!< The Device type; Meter or Concentrator*/
  LINK_ATTR_ID_M_FIELD,/*!< The M-Field, Sender's manufacturer ID*/  
  LINK_ATTR_ID_A_FIELD,/*!< The A-Field, Sender's manufacturer ID*/
  LINK_ATTR_ID_FRAME_FORMAT,/*!< The Frame Format, for details refer FrameFormatType_t*/
  LINK_ATTR_ID_LINK_TIMEOUT,
  LINK_ATTR_ID_FAC,
}LINK_ATTR_ID_t;



/**
* @brief  WMBus Link Layer Primary C-Field Enum.
*/
typedef enum 
{
  LL_SND_NKE = 0x40,/*!< Reset Remote Link Command From Concentrator; 
  The direction is from Concentrator to meter */
  LL_SND_UD = 0x43,/*!<  Send User data Command from Concentrator; 
                            The meter should respond with ACK(FCV=1)*/   
  LL_SND_UD2 = 0x43,/*!<  Send User data Command from Concentrator; 
  The meter should respond with RSP_UD(FCV=0)*/
  LL_SND_NR = 0x44,/*!< Send Application Data; The Application data from Meter
  without request and no Ack is needed*/
  LL_SND_IR = 0x46,/*!< Installation Request from Meter; The concentrator 
  should ACK and register meter in its database*/
  LL_ACC_NR = 0x47,/*!< ACCESS Request from Meter; The meter needs access. 
  No Ack needed from Concentrator */
  LL_ACC_DMD = 0x48,/*!< Access Demand request from Meter; The concentrator 
  should reply with LINK_CONFIRM_ACK for this request*/
  LL_REQ_UD1 = 0x4A,/*!< Class 1 Data(Status/Alarm)Request from Concentrator;
  The meter should reply with LINK_RESPOND_USER_DATA/
  LINK_CONFIRM_ACK */
  LL_REQ_UD2 = 0x4B/*!< Class 2 Data(Application)Request from Concentrator; 
    The meter should reply with LINK_RESPOND_USER_DATA*/ 
} LL_C_FIELD_PRIMARY_t;

/**
* @brief  WMBus Link Layer Secondary C-Field Enum.
*/
typedef enum 
{
  LL_ACK = 0x00,/*!< The frame transmitted/received needs 
  confirmation/ack  from Secondary station */
  LL_CNF_IR = 0x06,/*!< The frame transmitted/received 
  is SND_NR user data;No ack needed */
  LL_RSP_UD = 0x08/*!< The frame transmitted/received needs 
    response(Data) from Secondary station */
} LL_C_FIELD_SECONDARY_t;

/**
* @brief  WMBus Link Layer Header Type Enum.
*/
typedef enum{
  NO_HEADER = 0x00,/*!<No header is used: header lenght is 0*/
  SHORT_HEADER = 0x04,/*!<Short header is used: header lenght is 4 bytes*/
  LONG_HEADER = 0x0C/*!<Long header is used: header lenght is 12 bytes*/
}DataHeaderLength_t;


/**
* @brief  WMBus Link Layer State Enum.
*/
typedef enum {
  LL_SM_IDLE=0,/*!<Link Layer state machine state is idle*/
  LL_SM_SEND_NKE,/*!<Link Layer state machine state is in SND-NKE state*/ 
  LL_SM_SEND_SND_IR,/*!<Link Layer state machine state is in SND-IR state*/ 
  LL_SM_SEND_CNF_IR,/*!<Link Layer state machine state is in CNF-IR state*/  
  LL_SM_SEND_SND_NR,/*!<Link Layer state machine state is in SND-NR state*/   
  LL_SM_SEND_SND_UD,/*!<Link Layer state machine state is in SND-UD state*/     
  LL_SM_SEND_SND_UD2,/*!<Link Layer state machine state is in SND-UD2 state*/ 
  LL_SM_SEND_REQ_UD1,/*!<Link Layer state machine state is in REQ-DU1 state*/ 
  LL_SM_SEND_REQ_UD2,/*!<Link Layer state machine state is in REQ-UD2 state*/   
  LL_SM_SEND_RSP_UD,/*!<Link Layer state machine state is in RSP-UD state*/ 
  LL_SM_SEND_ACK,/*!<Link Layer state machine state is in ACK state*/   
  LL_SM_SEND_ACC_DMD,/*!<Link Layer state machine state is in ACC-DMD state*/ 
  LL_SM_SEND_ACC_NR,/*!<Link Layer state machine state is in ACC-NR state*/ 
  LL_SM_WAIT_ACK,/*!<Link Layer state machine state is in wait for ack state*/ 
  LL_SM_WAIT_RSP_UD,/*!<Link Layer state machine state is in wait for RSP-UD state*/ 
  LL_SM_WAIT_CNF_IR,/*!<Link Layer state machine state is in wait for CNF-IR state*/ 
  LL_SM_WAIT_STATE,/*!<Link Layer state machine state is in wait state*/ 
  LL_SM_VCO_CAL,/*!<Link Layer state machine VCO calibration state */ 
  LL_SM_TEST_MODE, /*!<Link Layer state machine for Radio Test Mode */
  LL_INVALID_EVENT=0xFF/*!<Link Layer state machine state is in invalid state*/     
} LL_State_t;


/**
* @brief  WMBus Link Layer CI-Field Enum.
*/
typedef enum 
{
  CI_APPLI_RESET_NONE = 0x52,/*!<CI field: application reset: No header*/ 
  CI_APPLI_RESET_LONG = 0x53,/*!<CI field: application reset: long header*/ 
  
  CI_CMD_TO_DEV_SHORT = 0x5A,/*!<CI field: command to device: short header*/
  CI_CMD_TO_DEV_LONG = 0x5B,/*!<CI field: command to device: long header*/
  
  CI_TIME_SYNC_TO_DEV_ABS = 0x6C,/*!<CI field: time synch to device absolute*/
  CI_TIME_SYNC_TO_DEV_REL = 0x6D,/*!<CI field: time synch to device relative*/
  
  CI_ALARM_FROM_DEV_NONE = 0x71,/*!<CI field: alarm from device: no header*/
  CI_ALARM_FROM_DEV_SHORT = 0x74,/*!<CI field: alarm from device: short header*/
  CI_ALARM_FROM_DEV_LONG = 0x75,/*!<CI field: alarm from device: long header*/
  
  CI_RESPONSE_FROM_DEV_NONE = 0x78,/*!<CI field: respone from device: no header*/
  CI_RESPONSE_FROM_DEV_SHORT = 0x7A,/*!<CI field: respone from device: short header*/
  CI_RESPONSE_FROM_DEV_LONG = 0x72,/*!<CI field: respone from device: long header*/
  
  CI_TRANSPORT_TO_DEV_LONG = 0x80,/*!<CI field: transport to device: long header*/
  
  CI_TRANSPORT_FROM_DEV_SHORT = 0x8A,/*!<CI field: transport from device: short header*/
  CI_TRANSPORT_FROM_DEV_LONG = 0x8B,/*!<CI field: transport from device: long header*/
  
  CI_EXTENDED_LINK_LAYER_I = 0x8C,/*!<CI field: extended link layer: 2 Bytes*/
  CI_EXTENDED_LINK_LAYER_II = 0x8D,/*!<CI field: extended link layer: 8 Bytes*/
  CI_EXTENDED_LINK_LAYER_III = 0x8E,/*!<CI field: extended link layer: 10 Bytes*/
  CI_EXTENDED_LINK_LAYER_IV = 0x8F/*!<CI field: extended link layer: 16 Bytes*/
    
} CI_FIELD_t;



/**
* @brief  WMBus Tx Outcome
*/
typedef enum 
{
  TX_DONE=0,
  TX_ERROR_LBT
} Tx_Outcome_t;





/**
* @brief  WMBus Data field stucture.
*/

typedef struct 
{
  uint8_t size;       /*!< Payload Size; */
  //uint8_t capacity;   /*!< Payload buffer capacity; */
  uint8_t *payload;   /*!< pointer to Payload buffer; */
}DataField_t;


/**
* @brief  WMBus Link layer Frame primitive definition.
*/

typedef struct
{
  uint8_t       c_field;     /*!< C-field attribute*/
  uint8_t*       m_field;     /*!< M-field attribute*/
  uint8_t*       a_field;     /*!< A-field attribute*/
  uint8_t       ci_field;    /*!< CI-field attribute*/
  DataField_t   data_field;  /*!< Data field; */
  float         RSSI_field;  /*!< RSSI of the packet */
  uint32_t      timestamp;   /*!< Timestamp of the packet; */
  FrameFormatType_t frame_format;   /*!< Received frame format attribute */
  WMBusMode_t   submode;     /*!< submode of the packet */
}Frame_t;



/**
* @brief  WMBus Link layer attibutes.
*/
typedef struct 
{
  WMBusDeviceType_t DevType;/*!< Device type attribute*/
  uint8_t MField[2];/*!< M-field attribute*/
  uint8_t AField[6];/*!< A-field attribute*/   
  FrameFormatType_t LinkFrameFormat;/*!< Frame format attribute*/
  uint32_t LinkTimeout;
  uint8_t LinkFreqAccessCycle;
}WMBusLinkAttributes_t;


/**
* @brief  WMBus Extended Link Layer Header Type Enum.
*/
typedef enum{
  ELL_0 = 0, /*!<No ELL applied*/
  ELL_I = 0x03,/*!<ell CI + 2 bytes ELL is applied*/
  ELL_II = 0x09,/*!<ell CI + 8 bytes ELL is applied*/
  ELL_III = 0x0B,/*!<ell CI + 10 bytes ELL is applied*/ 
  ELL_IV = 0x11/*!<ell CI + 16 bytes ELL is applied*/
}ExtendedLinkLayer_t;



/**
* @brief  WMBus Link layer parameters taken from application layer.
*/
typedef struct
{
  uint8_t LinkEllLength;/*!<Extended link layer length*/
  uint8_t LinkHeaderLength;/*!<Header length*/ 
  uint16_t LinkManufrID;/*!<Manufacturing id*/
  uint32_t LinkDeviceID;/*!<Device identification number*/
  uint8_t LinkDeviceVersion;/*!<Device version*/
  uint8_t LinkMeterType;/*!<Meter type*/
  uint8_t LinkAccessNumber;/*!<Access Number*/ 
  uint8_t LinkStatusField;/*!<Status field*/
  uint16_t LinkConfigWord;/*!<Configuration word*/
  uint32_t LinkTimeout; /*!<User defined timeout*/
  uint8_t LinkFreqAccessCycle;/*!<Frequent Access Cycle*/
  ExtendedLinkLayer_t LinkEllType;/*!<Extended link layer type*/  
  uint8_t LinkEllAccessNum;/*!<Extended link layer access number*/  
}WMBusLinkAppliParams_t;

/**
* @}
*/


/** @defgroup WMBus_Link_Exported_Functions       WMBus Link Exported Functions
* @{
*/

void WMBus_LinkOverHeadEst(void);

/**
* @brief  This function will init the link layer link layer attributes 
* @param  *m_field:Pointer to the M-Field.
* @param  *a_field:Pointer to the A-Field.
* @param  WMBusDeviceType_t:WMBus Device Type.
* @param  FrameFormatType_t:Frame Format.
* @retval LINK_STATUS_t:Returns Link status success after Initialization.
*                       
*/
LINK_STATUS_t WMBus_LinkInit(uint8_t* m_field,
                             uint8_t* a_field,
                             WMBusDeviceType_t dev_type,
                             FrameFormatType_t frame_format);


/**
* @brief  This function will run the Link Layer State Machine 
*         for Meter and Other device. To be caled in the application main loop.
* @param  None
* @retval None
*/
void WMBus_LinkLayer_SM(void);

/**
* @brief  This function will compute the Header Type
* @param  uint8_t ci_field : CI Field
* @retval uint8_t : Header length
*                       
*/
uint8_t WMBus_LinkCheckHeaderType(uint8_t ci_field);


/**
* @brief  This function returns the Link layer attributes to application layer
* @param  attr:The Link attribute.
* @param  *value:The value of the attribute.
* @retval LINK_STATUS_t : LINK_STATUS_SUCCESS
*       LINK_STATUS_INVALID_ATTR   - The attribute ID is invalid.
*                       
*/
LINK_STATUS_t WMBus_LinkGetAttribute(LINK_ATTR_ID_t attr, uint8_t* value);


/**
* @brief  This function will put the radio in standby state.
* @param  None. 
* @retval LINK_STATUS_t.                      
*/
LINK_STATUS_t WMBus_LinkRadioStandby(void);



/**
* @brief  This function is handler for received frames  
* @param  None
* @retval LINK_STATUS_t
*/
LINK_STATUS_t WMBus_LinkRxFrameHandler(void);

/**
* @brief  This function will set the link attribute value.
* @param  attr: The Link attribute.
*         value: The value of the attribute.
* @retval LINK_STATUS_t : LINK_STATUS_SUCCESS
*       LINK_STATUS_INVALID_ATTR   - The attribute ID is invalid.
*       LINK_STATUS_INVALID_ATTR_VAL   - The attribute value is invalid.
*       LINK_STATUS_PHY_ERROR_READ_ONLY_ADDRESS   - The attribute is read only.
*                       
*/
LINK_STATUS_t WMBus_LinkSetAttribute(LINK_ATTR_ID_t attr, uint32_t value);


/**
* @brief  This function sets the payload,payload length and ci-Field
* @param  *payload: Pointer to payload buffer
* @param  payloadLen:Payload Length 
* @param  ciField: CI-Field
* @retval None                     
*/
void WMBus_Link_SetPayload(uint8_t* payload,
                           uint8_t payloadLen,
                           uint8_t ciField);

/**
* @brief  This function is handler for received frames  
* @param  None
* @retval LINK_STATUS_t
*/
LINK_STATUS_t WMBus_LinkRxFrameHandler(void);

/**
* @brief  This function returns the actual Link Layer state machine state.  
* @param  None
* @retval LL_State_t
*/
LL_State_t WMBus_LinkGetState(void);

/**
* @brief  This function returns the last frame received from the link layer. 
* @param  None
* @retval LL_State_t
*/
Frame_t* WMBus_LinkGetLastRxFrame(void);

/**
* @brief  Gets the configured packet format form the link layer.
* @param  none
* @retval FrameFormatType_t frame format.
*/
FrameFormatType_t WMBus_LinkGetFormat(void);

/**
* @brief  This function takes a frame as an input and calculates the L and CRC 
*         fields and formats the buffer as per the block format.Copies the frame
*         to LinkTxFrameBuffer and sets LinkTxFrameBufferSize
* @param  *frame - A pointer to a frame structure containing
*                      C, M, A, CI, and Data fields
* @retval LINK_STATUS_t : LINK_STATUS_SUCCESS
*       LINK_STATUS_INVALID_SIZE   - The data-field buffer is too large.  
*/
LINK_STATUS_t WMBus_LinkSetTxFrameBuffer(Frame_t *frame);


/**
* @brief  This callback is called when SND-IR is received at other device.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkInstallReqReceived_CB(Frame_t *frame);

/**
* @brief  This callback is called when SND-NR is received at other device.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkSendNoReplyReceived_CB(Frame_t *frame);

/**
* @brief  This callback is called when ACC-NR is received at other device.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkAccessNoReplyReceived_CB(Frame_t *frame);

/**
* @brief  This callback is called when RSP-UD is received at other device.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkResponseUdReceived_CB(Frame_t *frame);

/**
* @brief  This callback is called when ACC_DMD is received at other device.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkAccessDemandReceived_CB(Frame_t *frame);

/**
* @brief  This callback is called when CNF-IR is received at meter.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkConfirmInstallReqReceived_CB(Frame_t *frame);

/**
* @brief  This callback is called when SND-UD is received at meter.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkSendUdReceived_CB(Frame_t *frame);

/**
* @brief  This callback is called when REQ-UD2/SND-UD2 is received at meter.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkRequestUd2Received_CB(Frame_t *frame);

/**
* @brief  This callback is called when REQ-UD1 is received at meter.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkRequestUd1Received_CB(Frame_t *frame);

/**
* @brief  This callback is called when SND-NKE is received at meter.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkSendNkeReceived_CB(Frame_t *frame);

/**
* @brief  This callback is called when ACK is received at meter/Other device.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkAckReceived_CB(Frame_t *frame);

/**
* @brief  ACK timeout callback.
* @param  None
* @retval Success/Error
*/
void WMBus_LinkAckTimeout_CB(void);

/**
* @brief  CNF-IR timeout callback.
* @param  None
* @retval Success/Error
*/
void WMBus_LinkCnfIRTimeout_CB(void);

/**
* @brief  Send ACK callback.
* @param  *frame: Pointer to received frame
* @retval Success/Error
*/
void WMBus_LinkSendAck_CB(Frame_t *frame);


/**
* @brief  Rx Timeout callback.
* @param  None
* @retval Success/Error
*/
void WMBus_LinkRxTimeout_CB(void);

/**
* @brief  Tx Completed callback.
* @param  None
* @retval Success/Error
*/
void WMBus_LinkTxCompleted_CB(Tx_Outcome_t tx_outcome, Frame_t *frame);

/**
* @brief  RSP-UD Timeout callback.
* @param  None
* @retval Success/Error
*/
void WMBus_LinkRspUdTimeout_CB(void);


/**
* @brief  This callback is called from the weak implementation of all the callbacks 
*         of received frames.
*         The user can decide to use this callback or implement teh callbacks of specific frames.
* @param  none
* @retval Success/Error
*/
void WMBus_LinkFrameReceived_CB(Frame_t *frame);

void WMBus_LinkRxCompleted_SNDIR_CB(void);

WMBusLinkAppliParams_t* WMBus_Link_GetAppliParameterPointer(void);

/**
* @brief  This function will run the Link Layer State Machine for SNIFFER 
* @param  None
* @retval None
*/
void WMBus_LinkLayer_SM_Sniffer(void);

LINK_STATUS_t WMBus_LinkInit_Test_Mode(uint8_t* m_field,
                             uint8_t* a_field,
                             WMBusDeviceType_t dev_type,
                             FrameFormatType_t frame_format);
void WMBus_LinkRxPERTestModeFrameReceived_CB(Frame_t *frame);
/**
* @}
*/

/**
*@}
*/

/**
* @}
*/

/**
* @}
*/

#endif/* __WMBUS_LINK_H*/
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
