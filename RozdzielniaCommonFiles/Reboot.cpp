#include "Reboot.h"

#if !defined(ARDUINO_ARCH_SAM)
#include <avr/wdt.h>
#else
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ******************************/
  NonMaskableInt_IRQn   = -14, /**<  2 Non Maskable Interrupt                */
  MemoryManagement_IRQn = -12, /**<  4 Cortex-M3 Memory Management Interrupt */
  BusFault_IRQn         = -11, /**<  5 Cortex-M3 Bus Fault Interrupt         */
  UsageFault_IRQn       = -10, /**<  6 Cortex-M3 Usage Fault Interrupt       */
  SVCall_IRQn           = -5,  /**< 11 Cortex-M3 SV Call Interrupt           */
  DebugMonitor_IRQn     = -4,  /**< 12 Cortex-M3 Debug Monitor Interrupt     */
  PendSV_IRQn           = -2,  /**< 14 Cortex-M3 Pend SV Interrupt           */
  SysTick_IRQn          = -1,  /**< 15 Cortex-M3 System Tick Interrupt       */
/******  SAM3X8E specific Interrupt Numbers *********************************/

  SUPC_IRQn            =  0, /**<  0 SAM3X8E Supply Controller (SUPC) */
  RSTC_IRQn            =  1, /**<  1 SAM3X8E Reset Controller (RSTC) */
  RTC_IRQn             =  2, /**<  2 SAM3X8E Real Time Clock (RTC) */
  RTT_IRQn             =  3, /**<  3 SAM3X8E Real Time Timer (RTT) */
  WDT_IRQn             =  4, /**<  4 SAM3X8E Watchdog Timer (WDT) */
  PMC_IRQn             =  5, /**<  5 SAM3X8E Power Management Controller (PMC) */
  EFC0_IRQn            =  6, /**<  6 SAM3X8E Enhanced Flash Controller 0 (EFC0) */
  EFC1_IRQn            =  7, /**<  7 SAM3X8E Enhanced Flash Controller 1 (EFC1) */
  UART_IRQn            =  8, /**<  8 SAM3X8E Universal Asynchronous Receiver Transceiver (UART) */
  SMC_IRQn             =  9, /**<  9 SAM3X8E Static Memory Controller (SMC) */
  PIOA_IRQn            = 11, /**< 11 SAM3X8E Parallel I/O Controller A, (PIOA) */
  PIOB_IRQn            = 12, /**< 12 SAM3X8E Parallel I/O Controller B (PIOB) */
  PIOC_IRQn            = 13, /**< 13 SAM3X8E Parallel I/O Controller C (PIOC) */
  PIOD_IRQn            = 14, /**< 14 SAM3X8E Parallel I/O Controller D (PIOD) */
  USART0_IRQn          = 17, /**< 17 SAM3X8E USART 0 (USART0) */
  USART1_IRQn          = 18, /**< 18 SAM3X8E USART 1 (USART1) */
  USART2_IRQn          = 19, /**< 19 SAM3X8E USART 2 (USART2) */
  USART3_IRQn          = 20, /**< 20 SAM3X8E USART 3 (USART3) */
  HSMCI_IRQn           = 21, /**< 21 SAM3X8E Multimedia Card Interface (HSMCI) */
  TWI0_IRQn            = 22, /**< 22 SAM3X8E Two-Wire Interface 0 (TWI0) */
  TWI1_IRQn            = 23, /**< 23 SAM3X8E Two-Wire Interface 1 (TWI1) */
  SPI0_IRQn            = 24, /**< 24 SAM3X8E Serial Peripheral Interface (SPI0) */
  SSC_IRQn             = 26, /**< 26 SAM3X8E Synchronous Serial Controller (SSC) */
  TC0_IRQn             = 27, /**< 27 SAM3X8E Timer Counter 0 (TC0) */
  TC1_IRQn             = 28, /**< 28 SAM3X8E Timer Counter 1 (TC1) */
  TC2_IRQn             = 29, /**< 29 SAM3X8E Timer Counter 2 (TC2) */
  TC3_IRQn             = 30, /**< 30 SAM3X8E Timer Counter 3 (TC3) */
  TC4_IRQn             = 31, /**< 31 SAM3X8E Timer Counter 4 (TC4) */
  TC5_IRQn             = 32, /**< 32 SAM3X8E Timer Counter 5 (TC5) */
  TC6_IRQn             = 33, /**< 33 SAM3X8E Timer Counter 6 (TC6) */
  TC7_IRQn             = 34, /**< 34 SAM3X8E Timer Counter 7 (TC7) */
  TC8_IRQn             = 35, /**< 35 SAM3X8E Timer Counter 8 (TC8) */
  PWM_IRQn             = 36, /**< 36 SAM3X8E Pulse Width Modulation Controller (PWM) */
  ADC_IRQn             = 37, /**< 37 SAM3X8E ADC Controller (ADC) */
  DACC_IRQn            = 38, /**< 38 SAM3X8E DAC Controller (DACC) */
  DMAC_IRQn            = 39, /**< 39 SAM3X8E DMA Controller (DMAC) */
  UOTGHS_IRQn          = 40, /**< 40 SAM3X8E USB OTG High Speed (UOTGHS) */
  TRNG_IRQn            = 41, /**< 41 SAM3X8E True Random Number Generator (TRNG) */
  EMAC_IRQn            = 42, /**< 42 SAM3X8E Ethernet MAC (EMAC) */
  CAN0_IRQn            = 43, /**< 43 SAM3X8E CAN Controller 0 (CAN0) */
  CAN1_IRQn            = 44, /**< 44 SAM3X8E CAN Controller 1 (CAN1) */

  PERIPH_COUNT_IRQn    = 45  /**< Number of peripheral IDs */
} IRQn_Type;

#define __CM3_REV              0x0200 /**< SAM3X8E core revision number ([15:8] revision number, [7:0] patch number) */
#define __MPU_PRESENT          1      /**< SAM3X8E does provide a MPU */
#define __NVIC_PRIO_BITS       4      /**< SAM3X8E uses 4 Bits for the Priority Levels */
#define __Vendor_SysTickConfig 0      /**< Set to 1 if different SysTick Config is used */

#include <core_cm3.h>
#endif

void reboot() {
#if defined(ARDUINO_ARCH_MEGAAVR)
  wdt_enable(WDT_PERIOD_8CLK_gc);
  while (true);
#elif defined(__AVR__)
  wdt_enable(WDTO_15MS);
  while (true);
#elif defined(ESP8266) || defined(ESP32)
  ESP.restart();
#elif defined(ARDUINO_ARCH_MEGAAVR)
  wdt_enable(WDT_PERIOD_8CLK_gc);
  while (true);
#elif defined(ARDUINO_ARCH_SAM)
  //hwReboot();... albo
  NVIC_SystemReset();
  //__DSB;
  //SCB->AIRCR = ((0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk); // software reset
  // RSTC->RSTC_CR = RSTC_CR_KEY(0xA5) | RSTC_CR_PERRST | RSTC_CR_PROCRST;
  // NVIC_SystemReset(); 
#else
  NVIC_SystemReset();
#endif
}

