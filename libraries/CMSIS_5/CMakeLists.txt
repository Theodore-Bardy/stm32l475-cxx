# @file      CMakeLists.txt
# @brief     CMakeLists file for CMSIS 5 library
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

set(GIT_REPO_URL    "https://github.com/ARM-software/CMSIS_5")
set(GIT_TAG_NAME    "5.9.0")
set(GIT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR}/CMSIS_5)

include(FetchContent)
FetchContent_Declare(
    cmsis_5
    URL             ${GIT_REPO_URL}/archive/refs/tags/${GIT_TAG_NAME}.zip
    SOURCE_DIR      ${GIT_FOLDER_NAME}
)

FetchContent_GetProperties(cmsis_5)
if(NOT cmsis_5_POPULATED)
    message("Populating ${GIT_FOLDER_NAME}, please wait...")
    FetchContent_Populate(cmsis_5)
endif()

# CMSIS 5 includes
include_directories(${GIT_FOLDER_NAME}/CMSIS/Core/Include)
include_directories(${GIT_FOLDER_NAME}/CMSIS/RTOS2/Include)
