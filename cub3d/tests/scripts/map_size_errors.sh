#!/bin/sh

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m'

MAP_PATH="./tests/maps/color_codes/"
SCRIPT_PATH="./tests/scripts/"
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all"
TEST_OUTPUT="test_output"
VALGRIND_OUTPUT="valgrind_output"
TEST_FILE="test_map.cub"

VALID_TYPE_IDS="NO path_to_the_north_texture
                SO path_to_the_south_texture
                WE path_to_the_west_texture
                EA path_to_the_east_texture
                F 0,0,0
                C 0,10,0"

executeErrorTest() {
    echo "${VALID_TYPE_IDS}\n$2" > $SCRIPT_PATH$TEST_FILE
    ./cub3d "$SCRIPT_PATH$TEST_FILE" > /dev/null 2> "$SCRIPT_PATH$TEST_OUTPUT"

    # Output check
    if [ "$(cat $SCRIPT_PATH$TEST_OUTPUT)" = "$1" ]
    then
        echo "    ${GREEN}- $3 ($2): ok ✅${NC}"
        echo "        Message:"
        echo "            $1\n"
    else
        echo "    ${RED}- $3 ($2): not ok ❌${NC}"
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

echo "\n${YELLOW}MAP SIZE ERRORS:${NC}\n"

MAP_CONTENT=""
ERR_MESSAGE="Error. Incorrect map size: height must be over 3 rows"
DESCRIPTION="Zero lines maps"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="1"
ERR_MESSAGE="Error. Incorrect map size: height must be over 3 rows"
DESCRIPTION="Only 1"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="1    "
ERR_MESSAGE="Error. Incorrect map size: height must be over 3 rows"
DESCRIPTION="Only 1 with spaces"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="0"
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="One 0"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="0       "
ERR_MESSAGE="Error: invalid identifier"
DESCRIPTION="One 0 with spaces"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="1111111111111111111111111"
ERR_MESSAGE="Error. Incorrect map size: height must be over 3 rows"
DESCRIPTION="One line maps"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="1111111111111111111111111
1111111111111111111111111"
ERR_MESSAGE="Error. Incorrect map size: height must be over 3 rows"
DESCRIPTION="Two lines maps"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="      1111111111111111111111111          
        1111111111111111111111111          "
ERR_MESSAGE="Error. Incorrect map size: height must be over 3 rows"
DESCRIPTION="Two lines maps (with spaces)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="1\n1\n1"
ERR_MESSAGE="Error. Incorrect map size: width must be over 3 columns"
DESCRIPTION="One column map"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="11\n11\n11"
ERR_MESSAGE="Error. Incorrect map size: width must be over 3 columns"
DESCRIPTION="Two columns map"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"


# Segmentation fault !!!
# MAP_CONTENT="${VALID_TYPE_IDS}
#             11111111111111111L1111111111111111             
#             1111111111111111111111111111111111             
#             1111111111111111111111111111111111             "
# ERR_MESSAGE="Error: invalid "
# DESCRIPTION="L in map wall"
# executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"