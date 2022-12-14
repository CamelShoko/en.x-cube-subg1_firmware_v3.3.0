/**
******************************************************************************
  * @file    project-conf.h
  * @author  Central LAB
  * @version V1.0.0
  * @date    18-Oct-2016
  * @brief   Per project specific configuration
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
#ifndef PROJECT_ROUTER_CONF_H_
#define PROJECT_ROUTER_CONF_H_

#ifndef UIP_FALLBACK_INTERFACE
#define UIP_FALLBACK_INTERFACE rpl_interface
#endif

#if (!defined MCU_LOW_POWER) || (MCU_LOW_POWER == 1)
#undef MCU_LOW_POWER
#define MCU_LOW_POWER 0
#warning "Disbaling MCU_LOW_POWER for the Border Router."
#endif

#if RADIO_USES_CONTIKIMAC
//We are not supporting this case at application level for Border Router
#undef LP_PERIPHERAL_IN_SLEEP
#define LP_PERIPHERAL_IN_SLEEP 0
#endif /*RADIO_USES_CONTIKIMAC*/

#undef UIP_CONF_MAX_ROUTES
#define UIP_CONF_MAX_ROUTES 100
#undef NBR_TABLE_CONF_MAX_NEIGHBORS
#define NBR_TABLE_CONF_MAX_NEIGHBORS 50

/*Set PANID if needed */
//#undef IEEE802154_CONF_PANID
//#define IEEE802154_CONF_PANID 0xFEDE

#ifndef QUEUEBUF_CONF_NUM
#define QUEUEBUF_CONF_NUM          16
#endif

/* To align with FP-SNS-6LPNODE1... to be validated ...*/
#undef UIP_CONF_RECEIVE_WINDOW
#undef UIP_CONF_TCP_MSS
#undef UIP_CONF_BUFFER_SIZE
#define UIP_CONF_BUFFER_SIZE    1300
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*
#ifndef UIP_CONF_BUFFER_SIZE
#define UIP_CONF_BUFFER_SIZE    600
#endif

#ifndef UIP_CONF_RECEIVE_WINDOW
#define UIP_CONF_RECEIVE_WINDOW  150
#endif
*/


#ifndef WEBSERVER_CONF_CFS_CONNS
#define WEBSERVER_CONF_CFS_CONNS 2
#endif

#endif /* PROJECT_ROUTER_CONF_H_ */
