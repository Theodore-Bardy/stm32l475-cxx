# @file      CMakeLists.txt
# @brief     CMakeLists file for FreeRTOS Kernel
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

set(GIT_REPO_URL    "https://github.com/FreeRTOS/FreeRTOS-Kernel")
set(GIT_TAG_NAME    "V10.4.6")
set(GIT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel)

include(FetchContent)
FetchContent_Declare(
    freertos-kernel
    URL             ${GIT_REPO_URL}/archive/refs/tags/${GIT_TAG_NAME}.zip
    SOURCE_DIR      ${GIT_FOLDER_NAME}
)

FetchContent_GetProperties(freertos-kernel)
if(NOT freertos-kernel_POPULATED)
    message("Populating ${GIT_FOLDER_NAME}, please wait...")
    FetchContent_Populate(freertos-kernel)
endif()

# Set porting layer
set(FREERTOS_PORT ${GIT_FOLDER_NAME}/portable/GCC/ARM_CM4F)

# FreeRTOS sources
file(GLOB_RECURSE SOURCES_TEMP ${FREERTOS_PORT}/*.c ${FREERTOS_PORT}/*.S)
list(APPEND SOURCES_TEMP
    ${GIT_FOLDER_NAME}/event_groups.c
    ${GIT_FOLDER_NAME}/list.c
    ${GIT_FOLDER_NAME}/queue.c
    ${GIT_FOLDER_NAME}/stream_buffer.c
    ${GIT_FOLDER_NAME}/tasks.c
    ${GIT_FOLDER_NAME}/timers.c
)
target_sources(${APP_EXECUTABLE_NAME} PRIVATE ${SOURCES_TEMP})

# FreeRTOS includes
include_directories(${CMAKE_CURRENT_LIST_DIR}/config)
include_directories(${GIT_FOLDER_NAME}/include)
include_directories(${FREERTOS_PORT})
include_directories(${FREERTOS_PORT}/include)
