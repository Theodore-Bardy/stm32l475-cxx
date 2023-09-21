/**
 * @file      bsp.c
 * @brief     STM32 BSP functions used by the main application entry point
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#include <FreeRTOS.h>
#include <task.h>
#include "bsp.h"
#include "heap.h"
#include "stm32l4xx_hal.h"

void SystemClock_Config(void);
void vErrorHandler(void);

int
BspInit(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick */
    if (HAL_OK != HAL_Init())
    {
        return -1;
    }

    /* Configure the system clock */
    SystemClock_Config();

    /* Configure the heap */
    HeapInit();

    return 0;
}

int
BspStartupHook(void)
{
    return 0;
}

void
SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
        vErrorHandler();
    }

    /** Configure LSE Drive Capability
     */
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = 0;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 40;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        vErrorHandler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        vErrorHandler();
    }

    /** Enable MSI Auto calibration
     */
    HAL_RCCEx_EnableMSIPLLMode();
}

/**
 * @brief Idle hook function
 */
__attribute__((weak)) void
vApplicationIdleHook(void)
{
    /* Nothing to do */
}

/**
 * @brief RTOS daemon task startup hook
 */
void
vApplicationDaemonTaskStartupHook(void)
{
    /* An error occurred */
    portDISABLE_INTERRUPTS();

    /* Loop forever */
    for (;;)
    {
#if !defined(NDEBUG)
        /* Breakpoint for STM32 */
        __asm("BKPT");
#endif
    }
}

/**
 * @brief Provide memory used to the Idle task
 * @see configUSE_STATIC_ALLOCATION FreeRTOS option
 */
void
vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer, uint32_t* pulIdleTaskStackSize)
{
    static StaticTask_t xIdleTaskTCB;
    static StackType_t  uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's state will be stored */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/**
 * @brief Provide memory used by the RTOS daemon/time task
 * @see configUSE_STATIC_ALLOCATION FreeRTOS option
 */
void
vApplicationGetTimerTaskMemory(StaticTask_t** ppxTimerTaskTCBBuffer, StackType_t** ppxTimerTaskStackBuffer, uint32_t* pulTimerTaskStackSize)
{
    static StaticTask_t xTimerTaskTCB;
    static StackType_t  uxTimerTaskStack[configMINIMAL_STACK_SIZE * 6];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's state will be stored */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer */
    *pulTimerTaskStackSize = configMINIMAL_STACK_SIZE * 6;
}

/**
 * @brief Warn user if pvPortMalloc fails
 * Called if a call to pvPortMalloc() fails because there is insufficient free memory available in the FreeRTOS heap.
 * pvPortMalloc() is called internally by FreeRTOS API functions that create tasks, queues, software timers, and semaphores.
 * The size of the FreeRTOS heap is set by the configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h.
 */
__attribute__((noreturn)) void
vApplicationMallocFailedHook()
{
    portDISABLE_INTERRUPTS();

    /* Loop forever */
    for (;;)
    {
#if !defined(NDEBUG)
        /* Breakpoint for STM32 */
        __asm("BKPT");
#endif
    }
}

/**
 * @brief Loop forever if stack overflow is detected.
 * If configCHECK_FOR_STACK_OVERFLOW is set to 1, this hook provides a location for applications to define a response to a stack overflow.
 * Use this hook to help identify that a stack overflow has occurred.
 */
__attribute__((noreturn)) void
vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName)
{
    (void)xTask;

    /* Disable interrupts */
    portDISABLE_INTERRUPTS();

    /* Loop forever */
    for (;;)
    {
#if !defined(NDEBUG)
        /* Breakpoint for STM32 */
        __asm("BKPT");
#endif
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void
vErrorHandler(void)
{
    /* Disable IRQ interrupts */
    __disable_irq();

    /* Loop forever */
    for (;;)
    {
#if !defined(NDEBUG)
        /* Breakpoint for STM32 */
        __asm("BKPT");
#endif
    }
}
