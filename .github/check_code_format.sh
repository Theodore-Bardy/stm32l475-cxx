#!/bin/bash
# @file      check_code_format.sh
# @brief     Check code format
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

# Initialize list of files that are not properly formatted
result=""

# Check source and header files
for source_file in `git ls-tree -r HEAD --name-only | grep -E '(.*\.c$|.*\.cpp$|.*\.h$)'`
do
    lines=$(clang-format --dry-run ${source_file} 2>&1 | wc -l)
    if [[ ! $lines -eq 0 ]]; then
      result="${result}\n${source_file}"
    fi
done

# Check result
if [[ ${result} != "" ]]; then
  echo "The following files are not properly formatted:"
  echo -e $result
  exit 1
fi

exit 0
