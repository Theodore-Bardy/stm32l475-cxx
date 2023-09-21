# @file      bsp_stm32l4.cmake
# @brief     CMake file for BSP STM32L4
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

include (bsp_stm32)

# STM32L4 dependencies
include(${CMAKE_CURRENT_LIST_DIR}/STM32CubeL4/CMakeLists.txt)

# STM32L4 compile options
set(ARM_CFLAGS -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffunction-sections -fdata-sections)
add_compile_options(${ARM_CFLAGS})
target_compile_options(${APP_EXECUTABLE_NAME} PRIVATE ${ARM_CFLAGS})

# STM32L4 sources
file(GLOB SOURCES_TEMP
    ${CMAKE_CURRENT_LIST_DIR}/src/*.c
)
target_sources(${APP_EXECUTABLE_NAME} PRIVATE ${SOURCES_TEMP})

# STM32L4 includes
target_include_directories(${APP_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
