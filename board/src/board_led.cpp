/**
 * @file      board_led.cpp
 * @brief     Board LED functions
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#include "FreeRTOS.h"
#include "board_led.h"

/**
 * @brief Definition of LED structure
 */
typedef struct
{
    GPIO_TypeDef* port;
    uint16_t      pin;
} Led_TypeDef;

/**
 * @brief Declaration of LEDs
 */
static Led_TypeDef LEDs[] = { { LED2_GPIO_PORT, LED2_PIN } };

void
BOARD_LED::init(uint8_t _led)
{
    /* Check parameters */
    configASSERT(_led < sizeof(LEDs) / sizeof(LEDs[0]));

    led = _led;

    /* Enable clock */
    LEDx_GPIO_CLK_ENABLE(led);

    /* Configure the GPIO_LED pin */
    GPIO_InitTypeDef gpio_init;
    gpio_init.Pin   = LEDs[led].pin;
    gpio_init.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull  = GPIO_NOPULL;
    gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LEDs[led].port, &gpio_init);
}

void
BOARD_LED::deinit()
{
    /* Check parameter */
    configASSERT(led < sizeof(LEDs) / sizeof(LEDs[0]));

    /* Turn off LED */
    HAL_GPIO_WritePin(LEDs[led].port, LEDs[led].pin, GPIO_PIN_RESET);

    /* DeInit the GPIO_LED pin */
    HAL_GPIO_DeInit(LEDs[led].port, LEDs[led].pin);
}

void
BOARD_LED::on()
{
    /* Check parameter */
    configASSERT(led < sizeof(LEDs) / sizeof(LEDs[0]));

    /* Turn on LED */
    HAL_GPIO_WritePin(LEDs[led].port, LEDs[led].pin, GPIO_PIN_SET);
}

void
BOARD_LED::off()
{
    /* Check parameter */
    configASSERT(led < sizeof(LEDs) / sizeof(LEDs[0]));

    /* Turn off LED */
    HAL_GPIO_WritePin(LEDs[led].port, LEDs[led].pin, GPIO_PIN_RESET);
}

void
BOARD_LED::toggle()
{
    /* Check parameter */
    configASSERT(led < sizeof(LEDs) / sizeof(LEDs[0]));

    /* Toggle LED */
    HAL_GPIO_TogglePin(LEDs[led].port, LEDs[led].pin);
}
