#!/bin/bash
# @file      check_include_guards.sh
# @brief     Check include guards
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

# Initialize list of files that are not properly formatted
result=""

# Check header files
for source_file in `git ls-tree -r HEAD --name-only | grep -E '(.*\.h$)'`
do
    uppercase=$(echo $(basename ${source_file^^}) | tr '.' '_')
    grep -Pze "#ifndef _${uppercase}_\n#define _${uppercase}_" ${source_file} > /dev/null 2>&1
    if [ "$?" != "0" ]; then
      result="${result}\n${source_file}"
    else
      grep -e "#endif /\* _${uppercase}_ \*/" ${source_file} > /dev/null 2>&1
      if [ "$?" != "0" ]; then
        result="${result}\n${source_file}"
      fi
    fi
done

# Check result
if [[ ${result} != "" ]]; then
  echo "The following files have wrong or missing include guards:"
  echo -e $result
  exit 1
fi

exit 0
