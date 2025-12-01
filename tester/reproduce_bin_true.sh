#!/bin/bash

# Path to minishell
MINISHELL=./bin/minishell

# Command to test
CMD="/usr/bin/true"

# Run minishell and check output
echo "Testing $CMD..."
echo "$CMD
echo \$?
exit" | $MINISHELL > output.txt 2>&1

# Check result
cat output.txt
if grep -q "command not found" output.txt; then
    echo "FAIL: Command not found"
    exit 1
fi

if grep -q "0" output.txt; then
    echo "SUCCESS: Command executed correctly"
    exit 0
else
    echo "FAIL: Exit status not 0"
    exit 1
fi
