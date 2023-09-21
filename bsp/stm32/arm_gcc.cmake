# @file      arm_gcc.cmake
# @brief     CMake file for ARM none eabi gcc toolchain configuration
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

# We are cross compiling so we don't want compiler tests to run, as they will fail
set(CMAKE_C_COMPILER_WORKS 1)

# Indicate we aren't compiling for an OS
set(CMAKE_SYSTEM_NAME Generic)

# Set processor type
set(CMAKE_SYSTEM_PROCESSOR arm)

# Override compiler
set(COMPILER_PREFIX arm-none-eabi-)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_C_COMPILER ${COMPILER_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${COMPILER_PREFIX}g++)
set(CMAKE_AR ${COMPILER_PREFIX}gcc-ar)
set(CMAKE_RANLIB ${COMPILER_PREFIX}gcc-ranlib)

# Set other tools
set(OBJSIZE ${COMPILER_PREFIX}size)
set(OBJCOPY ${COMPILER_PREFIX}objcopy)
set(OBJDUMP ${COMPILER_PREFIX}objdump)
set(DEBUGGER ${COMPILER_PREFIX}gdb)

# Remove preset linker flags
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_ASM_FLAGS "")

# Set library options
set(SHARED_LIBS OFF)
set(STATIC_LIBS ON)
