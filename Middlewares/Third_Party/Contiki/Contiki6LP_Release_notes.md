---
pagetitle: Release Notes for Contiki6LP Middleware
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for <mark>Contiki6LP Middleware</mark>
    
[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>


# Purpose

Contiki6LP Library is a middleware for the the X-CUBE-SUBG1 expansion software.
This middleware provides the 6LoWPAN functionality to enable a full IPv6 mesh network to be build using STM32 ODE Hardware components.

Contiki6LP software features:

 - Middleware library with Contiki OS and Contiki 6LoWPAN protocol stack 3.x
 - Support for mesh networking technology by the means of the standard RPL protocol
 - Easy portability across different STM32 MCU families thanks to STM32Cube.
 - Sample applications enabling communication via UDP over 6LoWPAN.
 - Sample application configuring a node as "RPL border router"
 - Free user-friendly license terms
 - Examples available for NUCLEO-F401RE and NUCLEO-L152RE boards.
 - ST platform specific implementation is provided in Contiki_STM32_Library middleware.

:::

::: {.col-sm-12 .col-lg-8}
# Update History

::: {.collapse}
<input type="checkbox" id="collapse-section4" checked aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__1.5.0 / April 19th 2021__</label>
<div>			

## Main Changes

 - Patch in uip-icmp6.c to avoid random memove with negative offset 

## Contents

 - Documentation
    - Doxygen documentation: [Contiki6LP.chm](..\\..\\..\\Documentation\Contiki6LP.chm)
 - Middlewares
    - Contiki OS v3.x
	- version updated to commit bc2e445817aa546c0bb93a9900093ec276005e2a from [https://github.com/contiki-os/contiki](https://github.com/contiki-os/contiki) repository
      - Includes (in apps) TinyDTLS v0.8.6 derived and modifed starting from commit cc5863fa0e438ba1fa46c05f2a27cd8dd3d85b96 on [https://git.eclipse.org/r/tinydtls/org.eclipse.tinydtls](https://git.eclipse.org/r/tinydtls/org.eclipse.tinydtls)
      - Includes DTLS CoAP bindings derived and modified from commit 98a3eac5d0570a98fe7245b4e16e90c9ecab14d4 on develop branch of [https://github.com/cetic/6lbr.git](https://github.com/cetic/6lbr.git)
      - Includes preliminary X.509 support derived by earlier version of IoTivity constrained from [https://github.com/iotivity/iotivity-constrained](https://github.com/iotivity/iotivity-constrained)
      - Some internal bugfix
	  
## Development Toolchains and Compilers

 - IAR Embedded Workbench for ARM (EWARM) toolchain V8.50.9 + ST-Link
 - Keil Microcontroller Development Kit (MDK-ARM) toolchain V5.32 + ST-Link
 - STM32CubeIDE 1.6.1 + ST-LINK

## Supported Devices and EVAL boards

 - STM32F401RE and STM32L152RE devices
 - NUCLEO-F401RE Board RevC
 - NUCLEO-L152RE Board RevC
 - X-NUCLEO-IDS01A4 Board
 - X-NUCLEO-IDS01A5 Board

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section4" checked aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__1.4.0 / December 10th 2018__</label>
<div>			

## Main Changes

 - Added TinyDTLS bindings for CoAP stack
 - ContikiMAC slightly modified to be supported by Contiki_STM32_Library V1.1.0

## Contents

 - Documentation
    - Doxygen documentation: [Contiki6LP.chm](..\\..\\..\\Documentation\Contiki6LP.chm)
 - Middlewares
    - Contiki OS v3.x
	- version updated to commit bc2e445817aa546c0bb93a9900093ec276005e2a from [https://github.com/contiki-os/contiki](https://github.com/contiki-os/contiki) repository
      - Includes (in apps) TinyDTLS v0.8.6 derived and modifed starting from commit cc5863fa0e438ba1fa46c05f2a27cd8dd3d85b96 on [https://git.eclipse.org/r/tinydtls/org.eclipse.tinydtls](https://git.eclipse.org/r/tinydtls/org.eclipse.tinydtls)
      - Includes DTLS CoAP bindings derived and modified from commit 98a3eac5d0570a98fe7245b4e16e90c9ecab14d4 on develop branch of [https://github.com/cetic/6lbr.git](https://github.com/cetic/6lbr.git)
      - Includes preliminary X.509 support derived by earlier version of IoTivity constrained from [https://github.com/iotivity/iotivity-constrained](https://github.com/iotivity/iotivity-constrained)

## Development Toolchains and Compilers

 - IAR Embedded Workbench for ARM (EWARM) toolchain V8.20.2 + ST-Link
 - Keil Microcontroller Development Kit (MDK-ARM) toolchain V5.24.2 + ST-Link
 - System Workbench for STM32 (SW4STM32) toolchain v1.16.0 (IDE 2.5.0) + ST-LINK

## Supported Devices and EVAL boards

 - STM32F401RE and STM32L152RE devices
 - NUCLEO-F401RE Board RevC
 - NUCLEO-L152RE Board RevC
 - X-NUCLEO-IDS01A4 Board
 - X-NUCLEO-IDS01A5 Board

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section4" checked aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__1.3.0 / June 1st 2018__</label>
<div>			

## Main Changes

 - Update for SUBG1 3.0.0
 - Support of S2-LP Radio
 - Update of IAR and Keil projects.

## Contents

 - Documentation
    - Doxygen documentation: [Contiki6LP.chm](..\\..\\..\\Documentation\Contiki6LP.chm)
 - Middlewares
    - Contiki OS v3.x
	- version updated to commit bc2e445817aa546c0bb93a9900093ec276005e2a from [https://github.com/contiki-os/contiki](https://github.com/contiki-os/contiki) repository
    - STM32_Contiki_Library

## Development Toolchains and Compilers

 - IAR Embedded Workbench for ARM (EWARM) toolchain V8.11.3 + ST-Link
 - Keil Microcontroller Development Kit (MDK-ARM) toolchain V5.24.2 + ST-Link
 - System Workbench for STM32 1.15.0 + ST-LINK

## Supported Devices and EVAL boards

 - STM32F401RE and STM32L152RE devices
 - NUCLEO-F401RE Board RevC
 - NUCLEO-L152RE Board RevC
 - X-NUCLEO-IDS01A4 Board
 - X-NUCLEO-IDS01A5 Board

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section4" checked aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__1.2.0 / May 11th 2017__</label>
<div>			

## Main Changes

 - First integration as a Middleware of X-CUBE-SUBG1
 - Update of IAR and Keil projects.

## Contents

 - Documentation
    - Doxygen documentation: [Contiki6LP.chm](..\\..\\..\\Documentation\Contiki6LP.chm)
 - Middlewares
    - Contiki OS v3.x
	- version updated to commit 3c150a5e992372ecfbedee4020b05f1b56f73ed2 from [https://github.com/contiki-os/contiki](https://github.com/contiki-os/contiki) repository
    - STM32_Contiki_Library

## Development Toolchains and Compilers

 - IAR Embedded Workbench for ARM (EWARM) toolchain V7.80 + ST-Link
 - Keil Microcontroller Development Kit (MDK-ARM) toolchain V5.23 + ST-Link
 - System Workbench for STM32 1.13.1 + ST-LINK

## Supported Devices and EVAL boards

 - STM32F401RE and STM32L152RE devices
 - NUCLEO-F401RE Board RevC
 - NUCLEO-L152RE Board RevC
 - X-NUCLEO-IDS01A4 Board
 - X-NUCLEO-IDS01A5 Board

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section4" checked aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__1.1.0 / November 8th 2016__</label>
<div>			

## Main Changes

 - Update of Applications to use X-CUBE-SUBG1 V1.2.0
 - Update of Third Party Contiki Library Middleware
 - Update of ST Contiki (STM32_Contiki_Library) Middleware: code cleanup and different radio parameters selection


## Contents

 - Middlewares
    - Contiki OS v3.x
	- version updated to commit c05665a16b875f7c140e8110b913c32c7d430078 from [https://github.com/contiki-os/contiki](https://github.com/contiki-os/contiki) repository
    - STM32_Contiki_Library

## Development Toolchains and Compilers

 - IAR Embedded Workbench for ARM (EWARM) toolchain V7.70 + ST-Link
 - Keil Microcontroller Development Kit (MDK-ARM) toolchain V5.18 + ST-Link
 - System Workbench for STM32 1.10 + ST-LINK

## Supported Devices and EVAL boards

 - STM32F401RE and STM32L152RE devices
 - NUCLEO-F401RE Board RevC
 - NUCLEO-L152RE Board RevC
 - X-NUCLEO-IDS01A4 Board
 - X-NUCLEO-IDS01A5 Board

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section4" checked aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__1.0.0 / March 16th 2016__</label>
<div>			

## Main Changes

 - First release

## Contents

 - Middlewares
    - Contiki OS v3.x
	- version updated to commit df5ff896a8825cbfa7f3139e6f6bf8f73eaf9274 from [https://github.com/contiki-os/contiki](https://github.com/contiki-os/contiki) repository
    - STM32_Contiki_Library

## Development Toolchains and Compilers

 - IAR Embedded Workbench for ARM (EWARM) toolchain V7.50.2 + ST-Link
 - RealView Microcontroller Development Kit (MDK-ARM) toolchain V5.17.0 + ST-Link
 - System Workbench for STM32 1.7.0.201602121829 + ST-LINK

## Supported Devices and EVAL boards

 - STM32F401RE and STM32L152RE devices
 - NUCLEO-F401RE Board RevC
 - NUCLEO-L152RE Board RevC
 - X-NUCLEO-IDS01A4 Board
 - X-NUCLEO-IDS01A5 Board

</div>
:::

:::
:::

<footer class="sticky">
::: {.columns}
::: {.column width="95%"}
:::
::: {.column width="5%"}

:::
:::
</footer>
