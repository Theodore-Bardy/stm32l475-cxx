# @file      CMakeLists.txt
# @brief     CMakeLists file of the repository
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

cmake_minimum_required(VERSION 3.19)

# CMake configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# C11 according to Code Style
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Define location of main folders
set(BSP_DIR ${CMAKE_CURRENT_LIST_DIR}/bsp)
set(FREERTOS_KERNEL_DIR ${CMAKE_CURRENT_LIST_DIR}/freertos/FreeRTOS-Kernel)

# Set project's name
set(PROJECT_BASE_NAME stm32l475_cpp)

# Declare the executable first, so that we can add flags and sources later on
set(APP_EXECUTABLE_NAME ${PROJECT_BASE_NAME}.elf)
message("Executable name: ${APP_EXECUTABLE_NAME}")
add_executable(${APP_EXECUTABLE_NAME})

# Find all .cmake modules and include them
file(GLOB_RECURSE BSP_MOCKS_PACKAGE_LIST ${CMAKE_CURRENT_LIST_DIR}/**.cmake)
foreach(package ${BSP_MOCKS_PACKAGE_LIST})
    get_filename_component(dir ${package} DIRECTORY)
    list (APPEND CMAKE_MODULE_PATH ${dir})
endforeach()

# Default log verbosity
if(NOT DEFINED VERBOSE_LOG)
    set(VERBOSE_LOG 1)
    message("VERBOSE_LOG is not defined, defaulting to ${VERBOSE_LOG}")
endif()
target_compile_definitions(${APP_EXECUTABLE_NAME} PRIVATE VERBOSE_LOG=${VERBOSE_LOG})

# Define SDK compile options
target_compile_options(${APP_EXECUTABLE_NAME} PRIVATE -O0)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(${APP_EXECUTABLE_NAME} PRIVATE -g)
    target_compile_definitions(${APP_EXECUTABLE_NAME} PRIVATE MODULE_LOG_LEVEL=LOG_DBG)
else()
    target_compile_definitions(${APP_EXECUTABLE_NAME} PRIVATE MODULE_LOG_LEVEL=LOG_INF)
endif()

# Set project's version
project(${PROJECT_BASE_NAME} LANGUAGES)

# Include sub-directories
include(${CMAKE_CURRENT_LIST_DIR}/board/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/freertos/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/libraries/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/main/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/modules/CMakeLists.txt)

# Enable used languages. This must be done after the toolchain has been defined by the BSP.
enable_language(C CXX ASM)

# Create .hex for application
add_custom_command(TARGET ${APP_EXECUTABLE_NAME}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex "${APP_EXECUTABLE_NAME}" "${PROJECT_BASE_NAME}.hex"
    COMMENT "Invoking: Unsigned Hex file creation"
)
