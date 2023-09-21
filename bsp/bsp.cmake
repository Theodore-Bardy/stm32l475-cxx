# @file      bsp.cmake
# @brief     CMake file for BSP
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

include (cmsis-svd)

# BSP linker options
target_link_options(${APP_EXECUTABLE_NAME} PRIVATE "-Wl,--wrap=_malloc_r,--wrap=_calloc_r,--wrap=_realloc_r,--wrap=_free_r")
