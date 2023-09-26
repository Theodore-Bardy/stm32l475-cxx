/**
 * @file      main.cpp
 * @brief     main file
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#include <FreeRTOS.h>
#include <task.h>
#include "main.h"
#include "board_led.h"
extern "C" {
    #include "bsp.h"
}

/**
 * @brief First task starts by the scheduler
 * @param[in] pvParams Task parameters, unused 
 */
static void vTaskApplication(void* pvParams);

int
main(void)
{
    /* Initialize BSP */
    if (0 != BspInit())
    {
        return -1;
    }

    /* Create application task */
    if (pdPASS != xTaskCreate(vTaskApplication, "TaskApp", configMINIMAL_STACK_SIZE, NULL, 1, NULL))
    {
        return -1;
    }

    /* Start the scheduler */
    vTaskStartScheduler();

    return 0;
}

static void
vTaskApplication(void* pvParams)
{
    (void)pvParams;

    BOARD_LED led;

    /* Initialize green LED */
    led.init(LED_GREEN);

    /* Toggle green LED every 200ms */
    for (;;)
    {
        led.toggle();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
