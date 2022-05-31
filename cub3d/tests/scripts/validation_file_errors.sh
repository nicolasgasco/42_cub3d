#!/bin/sh

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

SCRIPT_PATH="./tests/scripts/"
VALGRIND="valgrind --leak-check=full"
TEST_OUTPUT="test_output"
VALGRIND_OUTPUT="valgrind_output"
TEST_FILE="test_map.cub"

executeFileErrorTest() {
    ./cub3d $3 $4 $5 > /dev/null 2> "$SCRIPT_PATH$TEST_OUTPUT"

    # Output check
    if [ "$(cat $SCRIPT_PATH$TEST_OUTPUT)" = "$1" ]
    then
        echo "\n\n    ${GREEN}- $2: ok ✅${NC}"
        echo "        Message:"
        echo "            $1\n"
    else
        echo "\n\n    ${RED}- $2: not ok ❌${NC}"
        echo "========================================================================================="
        echo "    Expected:"
        echo "        |$1|\n"
        echo "    Got:"
        echo "        |$(cat $SCRIPT_PATH$TEST_OUTPUT)|"
        echo "========================================================================================="
        echo "\n"
        exit 1
    fi

    # Leaks check
    $VALGRIND ./cub3d > /dev/null 2> "$SCRIPT_PATH$VALGRIND_OUTPUT"
    VALGRIND_ERRORS=$(cat $SCRIPT_PATH$VALGRIND_OUTPUT | grep "in use at exit: 0 bytes in 0 blocks" | wc -l)
    if [ $VALGRIND_ERRORS -eq  1 ]
    then
        echo "        ${GREEN}No memory leaks detected 👍${NC}"
    else
        echo "        ${RED}Memory leaks detected ⛔${NC}"
        echo "\n$(less $SCRIPT_PATH$VALGRIND_OUTPUT)"
        exit 1
    fi
    
    # Errors check
    VALGRIND_ERRORS=$(cat $SCRIPT_PATH$VALGRIND_OUTPUT | grep "ERROR SUMMARY: 0 errors from 0 contexts" | wc -l)
    if [ $VALGRIND_ERRORS -eq  1 ]
    then
        echo "        ${GREEN}No Valgrind errors found 👍${NC}"
    else
        echo "        ${RED}Valgrind errors found ⛔${NC}"
        echo "\n$(less $SCRIPT_PATH$VALGRIND_OUTPUT)"
        exit 1
    fi
    echo "\n==========================================================================================================\n"
}

echo "\nFILE ERRORS:"

DESC="No arguments"
ERR_MESSAGE="Error: arguments"
executeFileErrorTest "$ERR_MESSAGE" "$DESC"

DESC="Two arguments"
ERR_MESSAGE="Error: arguments"
executeFileErrorTest "$ERR_MESSAGE" "$DESC" "arg1" "arg2"

DESC="Three arguments"
ERR_MESSAGE="Error: arguments"
executeFileErrorTest "$ERR_MESSAGE" "$DESC" "arg1" "arg2" "arg3"

DESC="One argument no extension"
ERR_MESSAGE="Error: invalid extension"
executeFileErrorTest "$ERR_MESSAGE" "$DESC" "arg1"

DESC="One argument only dot (.)"
ERR_MESSAGE="Error: invalid extension"
executeFileErrorTest "$ERR_MESSAGE" "$DESC" "arg1."

DESC="One argument wrong extension (.txt)"
ERR_MESSAGE="Error: invalid extension"
executeFileErrorTest "$ERR_MESSAGE" "$DESC" "arg1.txt"

DESC="One argument wrong extension (.cubb)"
ERR_MESSAGE="Error: invalid extension"
executeFileErrorTest "$ERR_MESSAGE" "$DESC" "arg1.cubb"

DESC="One argument wrong extension (.cu)"
ERR_MESSAGE="Error: invalid extension"
executeFileErrorTest "$ERR_MESSAGE" "$DESC" "arg1.cu"

DESC="One argument wrong extension (cub)"
ERR_MESSAGE="Error: invalid extension"
executeFileErrorTest "$ERR_MESSAGE" "$DESC" "arg1cub"

DESC="One argument no filename"
ERR_MESSAGE="Error: invalid extension"
executeFileErrorTest "$ERR_MESSAGE" "$DESC" ".cub"