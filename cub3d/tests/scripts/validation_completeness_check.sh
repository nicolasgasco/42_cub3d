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
        echo "\n\n    ${GREEN}- $3: ok ✅${NC}"
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

echo "\nCOLORS COMPLETENESS CHECKS:"

MAP_CONTENT="F 255,20,20"
ERR_MESSAGE="Error: incomplete scene info"
DESCRIPTION="C is missing"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 255,20,20"
ERR_MESSAGE="Error: incomplete scene info"
DESCRIPTION="F is missing"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO path_to_the_north_texture
            SO path_to_the_south_texture
            WE path_to_the_west_texture
            EA path_to_the_east_texture
            F 255,20,20"
ERR_MESSAGE="Error: incomplete scene info"
DESCRIPTION="All orientations, C is missing"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO path_to_the_north_texture
            SO path_to_the_south_texture
            WE path_to_the_west_texture
            EA path_to_the_east_texture
            C 255,20,20"
ERR_MESSAGE="Error: incomplete scene info"
DESCRIPTION="All orientations, F is missing"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

# MAP_CONTENT="C 255,20,20
#             C 10,10,10"
# ERR_MESSAGE="Error: incomplete scene info"
# DESCRIPTION="C is duplicated"
# executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="F 255,20,20
             C 255,20,20"
ERR_MESSAGE="Error: duplicated scene info"
DESCRIPTION="C is equal F"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="C 0,0,0
             F 0,0,0"
ERR_MESSAGE="Error: duplicated scene info"
DESCRIPTION="F is equal C"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO path_to_the_north_texture
            SO path_to_the_south_texture
            WE path_to_the_west_texture
            EA path_to_the_east_texture
            C 255,20,20
            F 255,20,20"
ERR_MESSAGE="Error: duplicated scene info"
DESCRIPTION="All orientations, F is equal C"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"