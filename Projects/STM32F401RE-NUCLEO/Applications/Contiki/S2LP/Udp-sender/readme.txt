/**
  @page UDP Sender - Application sending messages via UPD to a UDP Server

  @verbatim
  ******************************************************************************
  * @file    UDP Sender /readme.txt
  * @author  SRA Application Team
  * @brief   This application provides an example on how to send messages using
  *          UDP protocol to a UDP Receiver.
  ******************************************************************************
  *
  * Copyright (c) 2021 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under ODE Software License Agreement
  * SLA0094, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                               www.st.com/SLA0094
  *
  ******************************************************************************
   @endverbatim

@par Example Description

This sample application shows how to use SPIRIT1/S2-LP radio and Contiki OS to enable UDP communication over 6LoWPAN network.
This sample application configures a node to periodically send a message to a receiver.
Please refer to Projects/Multi/Applications/Contiki/low-power.txt file for the specific low power features available in this application.

To test this application you need:
- one STM32 Nucleo board with its X-NUCLEO-IDS01A4 or X-NUCLEO-IDS01A5 or (X-NUCLEO-S2868A1 or X-NUCLEO-S2915A1) expansion board.
- a host PC running Windows or Linux (optional to print output to a serial line monitor)

On the STM32 Nucleo board this sample application for Udp-sender must be running.
Another STM32 Nucleo board with its X-NUCLEO-IDS01A4 or X-NUCLEO-IDS01A5 or X-NUCLEO-S2868A1 or X-NUCLEO-S2915A1 STM32 expansion board (running the Udp-receiver sample application included in this package) should be used to test the communication via UDP over 6LoWPAN.

Be sure to select the right X-NUCLEO-IDS01A4 or X-NUCLEO-IDS01A5 board or X-NUCLEO-S2868A1 or X-NUCLEO-S2915A1 in the code by setting the symbol X-NUCLEO-IDS01A4 for the 868MHz bandwidth, and X-NUCLEO-IDS01A5 for the 915MHz bandwidth

@par Hardware and Software environment

  - This example runs on STM32 Nucleo devices with X-NUCLEO-IDS01A4 or X-NUCLEO-IDS01A5 or X-NUCLEO-S2868A1 or X-NUCLEO-S2915A1 STM32 expansion board
  - This example has been tested with STMicroelectronics:
    - NUCLEO-L152RE RevC board
    - NUCLEO-F401RE RevC board
    and can be easily tailored to any other supported device and development board.
    

@par How to use it?

In order to make the program work, you must do the following:
 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.
 - Open IAR toolchain (see the release note for detailed information about the version).
   Alternatively you can use the Keil uVision toolchain (see the release note for detailed information about the version).
   Alternatively you can use the System Workbench for STM32 (see the release note for detailed information about the version).
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - Alternatively, you can download the pre-built binaries in "Binary" 
   folder included in the distributed package. 
   
 - IMPORTANT NOTE: To avoid issues with USB connection (mandatory if you have USB 3.0), it is   
   suggested to update the ST-Link/V2 firmware for STM32 Nucleo boards to the latest version.
   Please refer to the readme.txt file in the Applications directory for details.
   

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
