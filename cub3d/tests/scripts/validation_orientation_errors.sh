#!/bin/sh

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

MAP_PATH="./tests/maps/color_codes/"
SCRIPT_PATH="./tests/scripts/"
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all"
TEST_OUTPUT="test_output"
VALGRIND_OUTPUT="valgrind_output"
TEST_FILE="test_map.cub"

executeOrientationErrors() {
    echo "$2" > $SCRIPT_PATH$TEST_FILE
    ./cub3d "$SCRIPT_PATH$TEST_FILE" > /dev/null 2> "$SCRIPT_PATH$TEST_OUTPUT"

    # Output check
    if [ "$(cat $SCRIPT_PATH$TEST_OUTPUT)" = "$1" ]
    then
        echo "\n\n    ${GREEN}- $3 ($(cat $SCRIPT_PATH$TEST_FILE)): ok ✅${NC}"
        echo "        Message:"
        echo "            $1\n"
    else
        echo "\n\n    ${RED}- $3: not ok ❌${NC}"
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
    $VALGRIND ./cub3d "$SCRIPT_PATH$TEST_FILE" > /dev/null 2> "$SCRIPT_PATH$VALGRIND_OUTPUT"
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

echo "\nORIENTATION ERRORS:"

MAP_CONTENT="A"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="Wrong first letter"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="0 invalid_path"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="0 as first letter"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

# This skips checks and goes to map validation
MAP_CONTENT="1 invalid_path"
ERR_MESSAGE="Error: incomplete scene info"
DESCRIPTION="1 as first letter"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="V  \t"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="Wrong first letter (with space)"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="SE"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="Wrong second letter"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="SE   \t"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="Wrong second letter (with space)"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NE"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="Wrong second letter"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="WO"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="Wrong second letter"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="EO"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="Wrong second letter"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NOpath_to_file"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="Path without space"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO path_to_file"
ERR_MESSAGE="Error: file opening failed"
DESCRIPTION="Invalid path"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO path_to_file    \t"
ERR_MESSAGE="Error: file opening failed"
DESCRIPTION="Invalid path (with space)"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO path_to_file\n"
ERR_MESSAGE="Error: file opening failed"
DESCRIPTION="Invalid path (with newline)"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO ./fold/path_to_file"
ERR_MESSAGE="Error: file opening failed"
DESCRIPTION="Invalid path (nested)"
executeOrientationErrors "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"