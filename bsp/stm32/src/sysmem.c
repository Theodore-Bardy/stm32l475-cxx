/**
 * @file      sysmem.c
 * @brief     Implementation of newlib system memory calls using FreeRTOS memory allocation routines.
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#include <stdlib.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>

/** Size, in bytes, of metadata added to each memory block, without considering padding */
#define BLOCK_METADATA_SIZE (sizeof(void*) + sizeof(size_t))
/** Size, in bytes, of block header (metadata + padding) of a memory block */
#define BLOCK_HEADER_SIZE ((BLOCK_METADATA_SIZE + (portBYTE_ALIGNMENT - 1u)) & ~(portBYTE_ALIGNMENT_MASK))
/** Offset, in bytes, from memory block data start and block size */
#define BLOCK_SIZE_OFFSET -(sizeof(size_t) + (BLOCK_HEADER_SIZE - BLOCK_METADATA_SIZE))
/** Mask that, when applied on block size, indicates if the block is allocated or not */
#define BLOCK_ALLOCATED_MASK ((size_t)1u << (sizeof(size_t) * 8u - 1u))

void*
__wrap__malloc_r(struct _reent* reent, size_t size)
{
    (void)reent;
    return pvPortMalloc(size);
}

void*
__wrap__calloc_r(struct _reent* reent, size_t size, size_t len)
{
    (void)reent;

    void* ptr = pvPortMalloc(size * len);

    if (NULL != ptr)
    {
        memset(ptr, 0, size * len);
    }

    return ptr;
}

void*
__wrap__realloc_r(struct _reent* reent, void* old, size_t new_size)
{
    (void)reent;

    void* new = pvPortMalloc(new_size);

    if (NULL != new)
    {
        size_t old_size = *(size_t*)((uint8_t*)old + BLOCK_SIZE_OFFSET);

        configASSERT(old_size & BLOCK_ALLOCATED_MASK);
        old_size &= ~BLOCK_ALLOCATED_MASK;

        configASSERT(old_size >= BLOCK_HEADER_SIZE);
        old_size -= BLOCK_HEADER_SIZE;

        size_t copy_size = old_size > new_size ? new_size : old_size;

        memcpy(new, old, copy_size);
        vPortFree(old);
    }

    return new;
}

void
__wrap__free_r(struct _reent* reent, void* ptr)
{
    (void)reent;
    vPortFree(ptr);
}
