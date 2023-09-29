/**
 * @file      messages.cpp
 * @brief     Messages class implementation
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#include <FreeRTOS.h>
#include "messages.h"

messages::messages(uint16_t usMessageSize)
    : usSize(usMessageSize)
{
    pucData = new uint8_t[usMessageSize];
}

messages::~messages()
{
    delete pucData;
}

void
messages::encode(uint16_t& usIndex, bool xValueToEncode)
{
    configASSERT((usIndex + sizeof(bool)) <= usSize);
    pucData[usIndex] = (0xFF & xValueToEncode);
    usIndex += sizeof(bool);
}

void
messages::encode(uint16_t& usIndex, uint8_t xValueToEncode)
{
    configASSERT((usIndex + sizeof(uint8_t)) <= usSize);
    pucData[usIndex] = (0xFF & xValueToEncode);
    usIndex += sizeof(uint8_t);
}

void
messages::encode(uint16_t& usIndex, uint16_t xValueToEncode)
{
    configASSERT((usIndex + sizeof(uint16_t)) <= usSize);
    pucData[usIndex]     = (uint8_t)((0x00FF & xValueToEncode) >> 0);
    pucData[usIndex + 1] = (uint8_t)((0xFF00 & xValueToEncode) >> 8);
    usIndex += sizeof(uint16_t);
}

void
messages::encode(uint16_t& usIndex, uint32_t xValueToEncode)
{
    configASSERT((usIndex + sizeof(uint32_t)) <= usSize);
    pucData[usIndex]     = (uint8_t)((0x000000FF & xValueToEncode) >> 0);
    pucData[usIndex + 1] = (uint8_t)((0x0000FF00 & xValueToEncode) >> 8);
    pucData[usIndex + 2] = (uint8_t)((0x00FF0000 & xValueToEncode) >> 16);
    pucData[usIndex + 3] = (uint8_t)((0xFF000000 & xValueToEncode) >> 24);
    usIndex += sizeof(uint32_t);
}

void
messages::encode(uint16_t& usIndex, uint64_t xValueToEncode)
{
    configASSERT((usIndex + sizeof(uint64_t)) <= usSize);
    pucData[usIndex]     = (uint8_t)((0x00000000000000FF & xValueToEncode) >> 0);
    pucData[usIndex + 1] = (uint8_t)((0x000000000000FF00 & xValueToEncode) >> 8);
    pucData[usIndex + 2] = (uint8_t)((0x0000000000FF0000 & xValueToEncode) >> 16);
    pucData[usIndex + 3] = (uint8_t)((0x00000000FF000000 & xValueToEncode) >> 24);
    pucData[usIndex + 4] = (uint8_t)((0x000000FF00000000 & xValueToEncode) >> 32);
    pucData[usIndex + 5] = (uint8_t)((0x0000FF0000000000 & xValueToEncode) >> 40);
    pucData[usIndex + 6] = (uint8_t)((0x00FF000000000000 & xValueToEncode) >> 48);
    pucData[usIndex + 7] = (uint8_t)((0xF00000000000000F & xValueToEncode) >> 56);
    usIndex += sizeof(uint64_t);
}

void
messages::decode(uint16_t& usIndex, bool& xValueToDecode)
{
    configASSERT((usIndex + sizeof(bool)) <= usSize);
    xValueToDecode = (0x00 != pucData[usIndex]) ? true : false;
    usIndex += sizeof(bool);
}
void
messages::decode(uint16_t& usIndex, uint8_t& xValueToDecode)
{
    configASSERT((usIndex + sizeof(uint8_t)) <= usSize);
    usIndex += sizeof(uint8_t);
    usIndex += sizeof(uint8_t);
}
void
messages::decode(uint16_t& usIndex, uint16_t& xValueToDecode)
{
    configASSERT((usIndex + sizeof(uint16_t)) <= usSize);
    xValueToDecode = (uint16_t)((uint16_t)(pucData[usIndex]) | (((uint16_t)pucData[usIndex + 1]) << 8));
    usIndex += sizeof(uint16_t);
}
void
messages::decode(uint16_t& usIndex, uint32_t& xValueToDecode)
{
    configASSERT((usIndex + sizeof(uint32_t)) <= usSize);
    xValueToDecode = (uint32_t)(pucData[usIndex]) | (((uint32_t)pucData[usIndex + 1]) << 8) | (((uint32_t)pucData[usIndex + 2]) << 16)
                     | (((uint32_t)pucData[usIndex + 3]) << 24);
    usIndex += sizeof(uint32_t);
}
void
messages::decode(uint16_t& usIndex, uint64_t& xValueToDecode)
{
    configASSERT((usIndex + sizeof(uint64_t)) <= usSize);
    xValueToDecode = (uint64_t)(pucData[usIndex]) | (((uint64_t)pucData[usIndex + 1]) << 8) | (((uint64_t)pucData[usIndex + 2]) << 16)
                     | (((uint64_t)pucData[usIndex + 3]) << 24) | (((uint64_t)pucData[usIndex + 4]) << 32) | (((uint64_t)pucData[usIndex + 5]) << 40)
                     | (((uint64_t)pucData[usIndex + 6]) << 48) | (((uint64_t)pucData[usIndex + 7]) << 56);
    usIndex += sizeof(uint64_t);
}
