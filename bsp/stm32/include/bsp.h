/**
 * @file      bsp.h
 * @brief     BSP header
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#ifndef _BSP_H_
#define _BSP_H_

/**
 * @brief Perform any BSP initialization that does not require the RTOS to be running.
 * @return 0 if the function succeeds, -1 otherwise
 */
int BspInit(void);

/**
 * @brief Perform any hardware initialization that require the RTOS to be running.
 * @return 0 if the function succeeds, -1 otherwise
 */
int BspStartupHook(void);

#endif /* _BSP_H_ */
