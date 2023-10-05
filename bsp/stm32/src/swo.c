/**
 * @file      swo.c
 * @brief     Serial Wire Output implementation
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#include <string.h>
#include <FreeRTOS.h>
#include "stm32l4xx_hal.h"

/**
 * @brief Prints char through SWO
 * @param c Char to print
 */
static void prvSwoPrintChar(const char c);

void
SwoInit(void)
{
    uint32_t ulSwoSpeed = 200000000;
    uint32_t ulSwoPrescaler;

    ulSwoPrescaler = (SystemCoreClock / ulSwoSpeed) - 1;

    CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; /* Enable trace in core debug */
    TPI->SPPR        = 0x00000002U;                /* Select pin protocol: Serial Wire NRZ */
    TPI->ACPR        = ulSwoPrescaler;             /* TPI->ACPR "Async Clock Prescaler Register". Scale the baud rate of the asynchronous output */
    ITM->LAR         = 0xC5ACCE55U;                /* ITM Lock Access Register, C5ACCE55 enables more write access to Control Register 0xE00 :: 0xFFC */
    ITM->TCR         = ITM_TCR_TraceBusID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk | ITM_TCR_ITMENA_Msk; /* ITM Trace Control Register */
    ITM->TPR         = ITM_TPR_PRIVMASK_Msk;                                                                   /* ITM Trace Privilege Register */
    ITM->TER         = 1U;          /* ITM Trace Enable Register. Enabled tracing on stimulus ports. One bit per stimulus port. */
    DWT->CTRL        = 0x400003FEU; /*  */
    TPI->FFCR        = 0x00000100U; /* Formatter and Flush Control Register */
}

void
SwoPrintTraceString(const char* pcString)
{
    while ('\0' != *pcString)
    {
        prvSwoPrintChar(*pcString++);
    }
}

static void
prvSwoPrintChar(const char c)
{
    uint32_t ulTimeout = 5000U; /* arbitrary timeout value */

    /* Check if Trace Control Register is set and if the requested channel stimulus port is enabled */
    if ((0U != (ITM->TCR & ITM_TCR_ITMENA_Msk)) && (1U == (ITM->TER & 1UL)))
    {
        while (0U == ITM->PORT[0].u32)
        {
            /* Wait until STIMx is ready, then send data */
            ulTimeout--;
            if (0U == ulTimeout)
            {
                return; /* not able to send */
            }
        }
        ITM->PORT[0].u8 = c;
    }
}
