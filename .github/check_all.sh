#!/bin/bash
# @file      check_all.sh
# @brief     Exectues all checks scripts
# @copyright Copyright (C) Theodore Bardy. All rights reserved.
#            Developed by Theodore Bardy.
#            Reproduction, copy, modification in whole or part is prohibited
#            without the written permission of the copyright owner.

# Initialize list of files that have not properly pass checks
result=0

# Check headers
echo "Check headers..."
.github/check_headers.sh
if [ $? != 0 ]; then
    result=1
else
    echo "  OK"
fi
echo

# Check include guards
echo "Check include guards..."
.github/check_include_guards.sh
if [ $? != 0 ]; then
    result=1
else
    echo "  OK"
fi
echo

# Check code format
echo "Check code format..."
.github/check_code_format.sh
if [ $? != 0 ]; then
    result=1
else
    echo "  OK"
fi
echo

exit ${result}
