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

executeErrorTest() {
    echo "$2" > $SCRIPT_PATH$TEST_FILE
    ./cub3d "$SCRIPT_PATH$TEST_FILE" > /dev/null 2> "$SCRIPT_PATH$TEST_OUTPUT"

    # Output check
    if [ "$(cat $SCRIPT_PATH$TEST_OUTPUT)" = "$1" ]
    then
        echo "    ${GREEN}- $3 ($(cat $SCRIPT_PATH$TEST_FILE)): ok ✅${NC}"
        echo "        Message:"
        echo "            $1\n"
    else
        echo "    ${RED}- $3: not ok ❌${NC}"
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
    echo "=========================================================================================================="
}

echo "\nCOLORS CODES ERRORS:"

MAP_CONTENT=" \t\t"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="No statement (spaces)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F"
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="No color statement"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F     "
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="No color statement (trailing spaces)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F20,20,20"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="No space before color"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F -20,20,20"
ERR_MESSAGE="Error: invalid color code"
DESCRIPTION="Negative color code"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 256,20,20"
ERR_MESSAGE="Error: invalid color code"
DESCRIPTION="Color code > 255"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 256,20,20,"
ERR_MESSAGE="Error: invalid color code"
DESCRIPTION="Color code > 255 (trailing comma)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 2a0,20,20"
ERR_MESSAGE="Error: invalid color code"
DESCRIPTION="Non-numeric color code"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 2a0,20,20,"
ERR_MESSAGE="Error: invalid color code"
DESCRIPTION="Non-numeric color code (trailing comma)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 225,200"
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="One color code missing"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 225,200,"
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="One color code missing (trailing comma)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 225"
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="Two color codes missing"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 225,"
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="Two color codes missing (trailing comma)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 225,200,200,200"
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="Four color codes"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 225,200,200,"
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="Correct but trailing comma"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 225,200,200."
ERR_MESSAGE="Error: invalid color code"
DESCRIPTION="Correct but trailing period"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 225,200,200]"
ERR_MESSAGE="Error: invalid color code"
DESCRIPTION="Correct but trailing period"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 225,200,200,,"
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="Correct but 2 trailing commas"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 225,200,200,200,"
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="Four color codes (trailing comma)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F ,,,"
ERR_MESSAGE="Error: invalid color statement"
DESCRIPTION="Correct but 2 trailing commas"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"