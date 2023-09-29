/**
 * @file      logging.cpp
 * @brief     Logging implementation
 * @copyright Copyright (C) Theodore Bardy. All rights reserved.
 *            Developed by Theodore Bardy.
 *            Reproduction, copy, modification in whole or part is prohibited
 *            without the written permission of the copyright owner.
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>
#include "logging.h"
extern "C" {
#include "swo.h"
}

/**
 * @brief Maximum log message length
 */
#define LOGGING_MAX_LOG_LENGTH (128)

/**
 * @brief Invalid pointer value used for requesting the logging task to notify the task waiting for flush to complete
 */
#define FLUSH_REQUEST ((char*)NULL)

/**
 * @brief Queue used to pass pointers to log messages to the log task
 */
static QueueHandle_t xLogsQueue = NULL;

/**
 * @brief Task waiting for flush to complete
 */
static TaskHandle_t xTaskWaitingFlush;

/**
 * @brief Mutex used to protect critical sections
 */
static StaticSemaphore_t xMutex;

/**
 * @brief Logging task function
 * @param pvParams Task parameters, unused
 */
__attribute__((noreturn)) static void
prvLoggingTask(void* const pvParams)
{
    (void)pvParams;

    char* pcReceivedString = NULL;

    for (;;)
    {
        /* Block to wait for the next string to print. */
        if (pdPASS == xQueueReceive(xLogsQueue, &pcReceivedString, portMAX_DELAY))
        {
            if (FLUSH_REQUEST == pcReceivedString)
            {
                configASSERT(NULL != xTaskWaitingFlush);
                xTaskNotifyGive(xTaskWaitingFlush);
            }
            else
            {
                SwoPrintTraceString(pcReceivedString);
                vPortFree((void*)pcReceivedString);
            }
        }
    }
}

BaseType_t
xLoggingTaskInitialize(uint16_t usStackSize, UBaseType_t uxPriority, UBaseType_t uxQueueLength)
{
    BaseType_t xReturn = pdFAIL;

    /* Ensure the logging task has not been created already. */
    if (NULL == xLogsQueue)
    {
        /* Initialize logs */
        SwoInit();

        /* Create mutex for data race protection */
        xSemaphoreCreateMutexStatic(&xMutex);

        /* Create the queue used to pass pointers to strings to the logging task. */
        xLogsQueue = xQueueCreate(uxQueueLength, sizeof(char**));

        if (NULL != xLogsQueue)
        {
            if (pdPASS == xTaskCreate(prvLoggingTask, "Logging", usStackSize, NULL, uxPriority, NULL))
            {
                xReturn = pdPASS;
            }
            else
            {
                /* Could not create the task, so delete the queue again. */
                vQueueDelete(xLogsQueue);
            }
        }
    }

    return xReturn;
}

#if VERBOSE_LOG == 1
void
vLoggingPrintfWithMetadata(const char* pcFile, size_t fileLineNo, const uint8_t level, const char* pcFormat, ...)
{
    configASSERT(NULL != pcFile);
    configASSERT(NULL != pcFormat);
    configASSERT(NULL != xLogsQueue);
    configASSERT(LOG_DBG > level);

    va_list args;
    va_start(args, pcFormat);

    size_t          xLength         = 0;
    char*           pcPrintString   = NULL;
    const char*     pcFileName      = NULL;
    const char*     pcLogLvlString  = NULL;
    static uint32_t ulMessageNumber = 0;

    /* Allocate a buffer to hold the log message */
    pcPrintString = (char*)pvPortMalloc(LOGGING_MAX_LOG_LENGTH);

    if (NULL != pcPrintString)
    {
        /* Add metadata for log message */
        if ((0 != strcmp(pcFormat, "\n")) && (NULL != pcFile))
        {
            /* Check if file path contains "\" as the directory separator. */
            if (NULL != strrchr(pcFile, '\\'))
            {
                pcFileName = strrchr(pcFile, '\\') + 1;
            }
            /* Check if file path contains "/" as the directory separator. */
            else if (NULL != strrchr(pcFile, '/'))
            {
                pcFileName = strrchr(pcFile, '/') + 1;
            }
            else
            {
                /* File path contains only file name. */
                pcFileName = pcFile;
            }

            if (taskSCHEDULER_NOT_STARTED != xTaskGetSchedulerState())
            {
                xLength = snprintf(pcPrintString, LOGGING_MAX_LOG_LENGTH, "%lu [%s][%s:%d]", ulMessageNumber++, pcTaskGetName(NULL), pcFileName, fileLineNo);
            }
            else
            {
                xLength = snprintf(pcPrintString, LOGGING_MAX_LOG_LENGTH, "%lu [none][%s:%d]", ulMessageNumber++, pcFileName, fileLineNo);
            }
        }

        /* Add log level */
        switch (level)
        {
            case LOG_ERR:
                pcLogLvlString = "[ERR] ";
                break;

            case LOG_WAR:
                pcLogLvlString = "[WAR] ";
                break;

            case LOG_INF:
                pcLogLvlString = "[INF] ";
                break;

            case LOG_DBG:
                pcLogLvlString = "[DBG] ";
                break;

            default:
                pcLogLvlString = "[NONE] ";
                break;
        }
        if (xLength < LOGGING_MAX_LOG_LENGTH)
        {
            xLength += snprintf(pcPrintString + xLength, LOGGING_MAX_LOG_LENGTH - xLength, "%s", pcLogLvlString);
        }

        /* Add message */
        if (xLength < LOGGING_MAX_LOG_LENGTH)
        {
            xLength += vsnprintf(pcPrintString + xLength, LOGGING_MAX_LOG_LENGTH - xLength, pcFormat, args);
        }

        /* Add newline characters if the message does not end with them.*/
        size_t ulFormatLen = 0UL;
        if (NULL != pcFormat)
        {
            ulFormatLen = strlen(pcFormat);
            if (LOGGING_MAX_LOG_LENGTH < ulFormatLen)
            {
                ulFormatLen = LOGGING_MAX_LOG_LENGTH;
            }
        }
        if ((ulFormatLen >= 2) && ('\n' != pcFormat[ulFormatLen]) && (xLength < LOGGING_MAX_LOG_LENGTH))
        {
            xLength += snprintf(pcPrintString + xLength, LOGGING_MAX_LOG_LENGTH - xLength, "%s", "\n");
        }

        /* The standard says that snprintf writes the terminating NULL
         * character. Just re-write it in case some buggy implementation does
         * not. */
        configASSERT(xLength < LOGGING_MAX_LOG_LENGTH);
        pcPrintString[xLength] = '\0';

        /* Only send the buffer to the logging task if it is not empty. */
        if (xLength > 0)
        {
            /* Send the string to the logging task for IO. */
            if (pdPASS != xQueueSend(xLogsQueue, &pcPrintString, 0))
            {
                /* The buffer was not sent so must be freed again. */
                vPortFree((void*)pcPrintString);
            }
        }
        else
        {
            /* The buffer was not sent, so it must be freed. */
            vPortFree((void*)pcPrintString);
        }
    }

    va_end(args);
}
#endif /* VERBOSE_LOG == 1 */
