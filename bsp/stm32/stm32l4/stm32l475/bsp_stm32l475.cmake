# @file      bsp_stm32l475.cmake
# @brief     CMake file for BSP STM32L475
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

# STM32L475 memory areas
math(EXPR FLASH_START 0x08000000)
math(EXPR FLASH_AREA_SIZE 1024*1024 OUTPUT_FORMAT HEXADECIMAL)
math(EXPR MIN_VECTOR_TABLE_ALIGNMENT 512)
math(EXPR SRAM1_START 0x20000000)
math(EXPR SRAM1_SIZE 96*1024 OUTPUT_FORMAT HEXADECIMAL)
math(EXPR SRAM2_START 0x10000000)
math(EXPR SRAM2_SIZE 32*1024 OUTPUT_FORMAT HEXADECIMAL)

message("Memory Areas:")
message("Flash Size           : ${FLASH_AREA_SIZE} bytes")
message("SRAM1 Size           : ${SRAM1_SIZE} bytes")
message("SRAM2 Size           : ${SRAM2_SIZE} bytes")

# STM32L475 link options
set(LINK_OPTIONS -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -specs=nosys.specs -specs=nano.specs -Wl,-Map=output.map -Wl,--gc-sections -lm)

# STM32L475 link options
target_link_options(${APP_EXECUTABLE_NAME} PUBLIC ${LINK_OPTIONS} "SHELL:-L ${CMAKE_CURRENT_LIST_DIR}/src/" -TSTM32L475_FLASH.ld)

include (bsp_stm32l4)

# STM32L475 sources
file(GLOB_RECURSE SOURCES_TEMP ${CMAKE_CURRENT_LIST_DIR}/src/**)

# Application
target_compile_definitions(${APP_EXECUTABLE_NAME} PRIVATE 
    STM32L475xx
)
target_sources(${APP_EXECUTABLE_NAME} PRIVATE ${SOURCES_TEMP})
