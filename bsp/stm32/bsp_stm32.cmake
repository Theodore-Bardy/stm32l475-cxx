# @file      bsp_stm32.cmake
# @brief     CMake file for BSP STM32
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

include (arm_gcc)
include (bsp)

# STM32 sources
file(GLOB SOURCES_TEMP
    ${CMAKE_CURRENT_LIST_DIR}/src/*.c
)
list(APPEND SOURCES_TEMP
    ${FREERTOS_KERNEL_DIR}/portable/MemMang/heap_5.c
)
target_sources(${APP_EXECUTABLE_NAME} PRIVATE ${SOURCES_TEMP})

# STM32 includes
target_include_directories(${APP_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

# Create .hex for application
add_custom_command(TARGET ${APP_EXECUTABLE_NAME}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex "${APP_EXECUTABLE_NAME}" "${PROJECT_BASE_NAME}.hex"
    COMMENT "Invoking: Unsigned Hex file creation"
)
