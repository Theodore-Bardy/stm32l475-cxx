# @file      CMakeLists.txt
# @brief     CMakeLists file for STM32CubeL4
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

set(GIT_REPO_URL    "https://github.com/STMicroelectronics/STM32CubeL4")
set(GIT_TAG_NAME    "v1.17.2")
set(GIT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR}/STM32CubeL4)

include(FetchContent)
FetchContent_Declare(
    stm32cubel4
    URL             ${GIT_REPO_URL}/archive/refs/tags/${GIT_TAG_NAME}.zip
    SOURCE_DIR      ${GIT_FOLDER_NAME}
    PATCH_COMMAND   patch --directory=${CMAKE_CURRENT_LIST_DIR} -p0 -R -f < ${CMAKE_CURRENT_LIST_DIR}/STM32CubeL4.patch
)

FetchContent_GetProperties(stm32cubel4)
if(NOT stm32cubel4_POPULATED)
    message("Populating ${GIT_FOLDER_NAME}, please wait...")
    FetchContent_Populate(stm32cubel4)
endif()

# STM32CubeL4 sources
file(GLOB_RECURSE SOURCES_TEMP "${GIT_FOLDER_NAME}/Drivers/STM32L4xx_HAL_Driver/**")
list(FILTER SOURCES_TEMP EXCLUDE REGEX "[Tt]emplate")
target_sources(${APP_EXECUTABLE_NAME} PRIVATE ${SOURCES_TEMP})

# STM32CubeL4 includes
include_directories(${GIT_FOLDER_NAME}/Drivers/CMSIS/Device/ST/STM32L4xx/Include)
include_directories(${GIT_FOLDER_NAME}/Drivers/STM32L4xx_HAL_Driver/Inc)
