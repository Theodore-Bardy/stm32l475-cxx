/**
 * @file      swo.h
 * @brief     Serial Wire Output header
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#ifndef _SWO_H_
#define _SWO_H_

/**
 * @brief Initialize serial wire output
 */
void SwoInit(void);

/**
 * @brief Prints trace through SWO
 * @param pcString String to print
 */
void SwoPrintTraceString(const char* pcString);

#endif /* _SWO_H_ */
