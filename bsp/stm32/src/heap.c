/**
 * @file      heap.c
 * @brief     Initialization of heap
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#include "FreeRTOS.h"

void
HeapInit(void)
{
    HeapRegion_t xHeapRegions[] = {
        { (unsigned char*)0x10000000, 32*1024 },
        { (unsigned char*)0x20000000, 96*1024 },
        { NULL, 0 }
    };
    vPortDefineHeapRegions(xHeapRegions);
}
