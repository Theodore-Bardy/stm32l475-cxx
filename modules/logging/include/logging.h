/**
 * @file      logging.h
 * @brief     Logging class declaration
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#ifndef _LOGGING_H_
#define _LOGGING_H_

#include <stdint.h>
#include <FreeRTOS.h>

/**
 * @brief Initialized the logging task
 * @param usStackSize Stack size used by the logging task
 * @param uxPriority Priority used by the logging task
 * @param uxQueueLength Length of the message queue
 * @return pdPASS if its succeed, pdFAIL otherwise
 */
BaseType_t xLoggingTaskInitialize(uint16_t usStackSize, UBaseType_t uxPriority, UBaseType_t uxQueueLength);

/**
 * @brief Loggings level available
 */
#define LOG_NONE 0 /**< No log messages */
#define LOG_ERR  1 /**< Only error logs enabled */
#define LOG_WAR  2 /**< Error and warning logs enabled */
#define LOG_INF  3 /**< Error, warning and inforamation logs enabled */
#define LOG_DBG  4 /**< All logs enabled */

/**
 * @brief This enables verbosity in log messages. Disabled by default.
 */
#ifndef VERBOSE_LOG
#define VERBOSE_LOG 0
#endif

/**
 * @brief This defines the log level apply to the repository. LOG_WAR by default.
 */
#ifndef MODULE_LOG_LEVEL
#define MODULE_LOG_LEVEL LOG_WAR
#endif

#if !defined(MODULE_LOG_LEVEL)                                                                                                            \
    || ((MODULE_LOG_LEVEL != LOG_NONE) && (MODULE_LOG_LEVEL != LOG_ERR) && (MODULE_LOG_LEVEL != LOG_WAR) && (MODULE_LOG_LEVEL != LOG_INF) \
        && (MODULE_LOG_LEVEL != LOG_DBG))
#error "Please define MODULE_LOG_LEVEL as either LOG_NONE, LOG_ERR, LOG_WAR, LOG_INF, or LOG_DBG."
#endif

#if VERBOSE_LOG == 1

/**
 * @brief Same as vLoggingPrintf but additionally takes parameters of source file location of log to add as metadata in message.
 * @param pcFile The file name or file path containing the log message. If a file path is passed, only the filename is added to the log message.
 * @param fileLineNo The line number in the @p pcFile containing the message being logged.
 * @param level Level of the message, can be LOG_NONE, LOG_ERR, LOG_WAR, LOG_INF, or LOG_DBG
 * @param pcFormat The format string of the log message.
 * @param ... The variadic list of parameters for the format specifiers in the @p pcFormat.
 */
void vLoggingPrintfWithMetadata(const char* pcFile, size_t fileLineNo, const uint8_t level, const char* pcFormat, ...);

#if MODULE_LOG_LEVEL == LOG_DBG

/**
 * @brief Log error message
 */
#define LOG_ERROR(...) vLoggingPrintfWithMetadata(__FILE__, __LINE__, LOG_ERR, __VA_ARGS__)

/**
 * @brief Log warning message
 */
#define LOG_WARNING(...) vLoggingPrintfWithMetadata(__FILE__, __LINE__, LOG_WAR, __VA_ARGS__)

/**
 * @brief Log info message
 */
#define LOG_INFO(...) vLoggingPrintfWithMetadata(__FILE__, __LINE__, LOG_INF, __VA_ARGS__)

/**
 * @brief Log debug message
 */
#define LOG_DEBUG(...) vLoggingPrintfWithMetadata(__FILE__, __LINE__, LOG_DBG, __VA_ARGS__)

#elif MODULE_LOG_LEVEL == LOG_INF

/**
 * @brief Log error message
 */
#define LOG_ERROR(...)   vLoggingPrintfWithMetadata(__FILE__, __LINE__, LOG_ERR, __VA_ARGS__)

/**
 * @brief Log warning message
 */
#define LOG_WARNING(...) vLoggingPrintfWithMetadata(__FILE__, __LINE__, LOG_WAR, __VA_ARGS__)

/**
 * @brief Log info message
 */
#define LOG_INFO(...)    vLoggingPrintfWithMetadata(__FILE__, __LINE__, LOG_INF, __VA_ARGS__)

/**
 * @brief Log debug message
 */
#define LOG_DEBUG(...)

#elif MODULE_LOG_LEVEL == LOG_WAR

/**
 * @brief Log error message
 */
#define LOG_ERROR(...)   vLoggingPrintfWithMetadata(__FILE__, __LINE__, LOG_ERR, __VA_ARGS__)

/**
 * @brief Log warning message
 */
#define LOG_WARNING(...) vLoggingPrintfWithMetadata(__FILE__, __LINE__, LOG_WAR, __VA_ARGS__)

/**
 * @brief Log info message
 */
#define LOG_INFO(...)

/**
 * @brief Log debug message
 */
#define LOG_DEBUG(...)

#elif MODULE_LOG_LEVEL == LOG_ERR

/**
 * @brief Log error message
 */
#define LOG_ERROR(...) vLoggingPrintfWithMetadata(__FILE__, __LINE__, LOG_ERR, __VA_ARGS__)

/**
 * @brief Log warning message
 */
#define LOG_WARNING(...)

/**
 * @brief Log info message
 */
#define LOG_INFO(...)

/**
 * @brief Log debug message
 */
#define LOG_DEBUG(...)

#else /* MODULE_LOG_LEVEL == LOG_NONE */

/**
 * @brief Log error message
 */
#define LOG_ERROR(...)

/**
 * @brief Log warning message
 */
#define LOG_WARNING(...)

/**
 * @brief Log info message
 */
#define LOG_INFO(...)

/**
 * @brief Log debug message
 */
#define LOG_DEBUG(...)

#endif /* Value of MODULE_LOG_LEVEL */

#endif /* VERBOSE_LOG == 1 */

#endif /* _LOGGING_H_ */
