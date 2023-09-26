#!/bin/bash
# @file      check_headers.sh
# @brief     Check headers
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

# Function used to check headers
# Arg1: Source file path
# Arg2: First line, "" if it is not present
# Arg3: String added in front of each new line except the first and last lines
# Arg4: Last line, "" if it is not present
check_header() {
    source_file=$1
    first_line=$2
    new_line=$3
    last_line=$4
    filename=$(echo $(basename ${source_file}) | sed -r 's/\+/\\+/g')
    grep -Pze "${first_line}${first_line:+\n}${new_line} @file      ${filename}\n${new_line} @brief     .+\n${new_line} @copyright Copyright \(C\) Theodore Bardy. All rights reserved.\n${new_line}            Developed by Theodore Bardy.\n${new_line}            Reproduction, copy, modification in whole or part is prohibited\n${new_line}            without the written permission of the copyright owner.${last_line:+\n}${last_line}\n\n" ${source_file} > /dev/null 2>&1
    return $?
}

# Initialize list of files that are not properly formatted
result=""

# Check source, header, ASM and linker files
for source_file in `git ls-tree -r HEAD --name-only | grep -E '(.*\.c$|.*\.cpp$|.*\.h$|.*\.s$|.*\.ld$)'`
do
    check_header ${source_file} "/\*\*" " \*" " \*/"
    if [ "$?" != "0" ]; then
      result="${result}\n${source_file}"
    fi
done

# Check YAML, Python, CMake and configuration files
for source_file in `git ls-tree -r HEAD --name-only | grep -E '(.*\.yml$|.*\.py$|CMakeLists.*\.txt$|.*\.cmake$|.*\.cfg$|.*\.conf$|.clang-format$)'`
do
    check_header ${source_file} "" "#" ""
    if [ "$?" != "0" ]; then
      result="${result}\n${source_file}"
    fi
done

# Check bash files
for source_file in `git ls-tree -r HEAD --name-only | grep -E '(.*\.sh$)'`
do
    check_header ${source_file} "#!/bin/bash" "#" ""
    if [ "$?" != "0" ]; then
      result="${result}\n${source_file}"
    fi
done

# Check result
if [[ ${result} != "" ]]; then
  echo "The following files have wrong header format:"
  echo -e $result
  exit 1
fi

exit 0
