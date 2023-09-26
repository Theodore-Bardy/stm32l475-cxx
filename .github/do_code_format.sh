#!/bin/bash
# @file      do_code_format.sh
# @brief     Update all source files according to wanted code format
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

# Update source and header files
for source_file in `git ls-tree -r HEAD --name-only | grep -E '(.*\.c$|.*\.cpp$|.*\.h$)'`
do
    clang-format -i ${source_file} || exit 1
done

exit 0
