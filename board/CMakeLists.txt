# @file      CMakeLists.txt
# @brief     CMakeLists file for the board B-L475E-IOT01
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

include (bsp_stm32l475)

# Board sources
file(GLOB_RECURSE SOURCES_TEMP ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
target_sources(${APP_EXECUTABLE_NAME} PRIVATE ${SOURCES_TEMP})

# Board includes
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
