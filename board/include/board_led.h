/**
 * @file      board_led.h
 * @brief     Board LED functions
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#ifndef _BOARD_LED_H_
#define _BOARD_LED_H_

#include <stdint.h>
#include "stm32l4xx_hal.h"

/**
 * @brief List of LEDs available on the board
 */
#define LED2      0
#define LED_GREEN LED2

/* Definition for the GPIO used to drive the LEDs */
#define LED2_GPIO_PORT          GPIOB
#define LED2_PIN                GPIO_PIN_14
#define LED2_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE() __HAL_RCC_GPIOB_CLK_DISABLE()

/**
 * @brief Macro used to enable clocks
 */
#define LEDx_GPIO_CLK_ENABLE(__INDEX__) \
    do                                  \
    {                                   \
        if (0 == (__INDEX__))           \
        {                               \
            LED2_GPIO_CLK_ENABLE();     \
        }                               \
    } while (0)

/**
 * @brief Macro used to disable clocks
 */
#define LEDx_GPIO_CLK_DISABLE(__INDEX__) \
    do                                   \
    {                                    \
        if (0 == (__INDEX__))            \
        {                                \
            LED2_GPIO_CLK_DISABLE();     \
        }                                \
    } while (0)

class BOARD_LED
{
private:
    uint8_t led;

public:
    void init(uint8_t _led);
    void deinit();
    void on();
    void off();
    void toggle();
};

#endif /* _BOARD_LED_H_ */
