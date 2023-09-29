/**
 * @file      messages.h
 * @brief     Messages class declaration
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#include <stdint.h>

class messages
{
private:
    uint16_t usSize;  /**< Size of the message */
    uint8_t* pucData; /**< Data of the message */

public:
    /**
     * @brief Construct a new messages object
     * @param usMessageSize Size of the message
     */
    messages(uint16_t usMessageSize);

    /**
     * @brief Destroy the messages object
     */
    ~messages();

    /**
     * @brief Send message
     * @return The number of bytes sent
     */
    uint16_t send();

    /**
     * @brief Receive message
     * @return The number of bytes received
     */
    uint16_t receive();

    /**
     * @brief Encode data to a message
     * @param usIndex Index in the message buffer where the data will be encode
     * @param xValueToEncode Variable to encode
     */
    void encode(uint16_t& usIndex, bool xValueToEncode);
    void encode(uint16_t& usIndex, uint8_t xValueToEncode);
    void encode(uint16_t& usIndex, uint16_t xValueToEncode);
    void encode(uint16_t& usIndex, uint32_t xValueToEncode);
    void encode(uint16_t& usIndex, uint64_t xValueToEncode);

    /**
     * @brief Decode data from a message
     * @param usIndex Index in the message buffer where the data will be decode
     * @param xValueToDecode Variable where the decoded data will be stored
     */
    void decode(uint16_t& usIndex, bool& xValueToDecode);
    void decode(uint16_t& usIndex, uint8_t& xValueToDecode);
    void decode(uint16_t& usIndex, uint16_t& xValueToDecode);
    void decode(uint16_t& usIndex, uint32_t& xValueToDecode);
    void decode(uint16_t& usIndex, uint64_t& xValueToDecode);
};

#endif /* _MESSAGES_H_ */
