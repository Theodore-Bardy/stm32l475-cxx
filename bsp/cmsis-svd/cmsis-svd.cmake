# @file      cmsis-svd.cmake
# @brief     CMake file for CMSIS SVD
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

# Fetch repository
set(GIT_REPO_URL    "https://github.com/posborne/cmsis-svd")
set(GIT_TAG_NAME    "551849db7be8415b1acc19bcc7fbbb07e808a4bf")

# Fetch destination
set(GIT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR}/cmsis-svd)

# Declare fetch content
include(FetchContent)
FetchContent_Declare(
    cmsis-svd
    GIT_REPOSITORY  ${GIT_REPO_URL}
    GIT_TAG         ${GIT_TAG_NAME}
    SOURCE_DIR      ${GIT_FOLDER_NAME}
)

# Fetch if not already done
FetchContent_GetProperties(cmsis-svd)
if(NOT cmsis-svd_POPULATED)
    message("Populating ${GIT_FOLDER_NAME}, please wait...")
    FetchContent_Populate(cmsis-svd)
endif()
