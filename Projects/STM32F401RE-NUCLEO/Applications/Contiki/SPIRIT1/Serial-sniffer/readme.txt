/**
  @page Serial Sniffer - Application to capture RF packets.

  @verbatim
  ******************************************************************************
  * @file    Serial Sniffer/readme.txt
  * @author  SRA Application Team
  * @brief   This application provides an example on how to capture RF packets
  *          and display them through Wireshark protocol analyzer application.
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

This application captures the RF packets.

To test this application you need:
- one STM32 Nucleo board with its X-NUCLEO-IDS01A4 or X-NUCLEO-IDS01A5 or (X-NUCLEO-S2868A1 or X-NUCLEO-S2915A1) expansion board.
- a host PC running Windows or Linux (optional to print output to a serial line monitor)
- Utilities to use the sniffer are in Utilities/serial-sniffer folder, a Readme is there with the command to be executed.


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
