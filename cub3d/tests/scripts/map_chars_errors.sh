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
                \t\t\t
                EA path_to_the_east_texture
                F 0,0,0
                  
                C 0,10,0
                  "

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

echo "\n${YELLOW}MAP CHARS ERRORS:${NC}\n"

MAP_CONTENT="
101
101             
111"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (top - middle)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
           
     101      
     101                   
     111  
            "
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (top - middle) with spaces around"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
110
101             
111"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (top - right)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
           
     110      
     101                   
     111  
            "
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (top - right) with spaces around"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111
001             
111"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (middle - left)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
           
     111      
     001                   
     111  
            "
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (middle - left) with spaces around"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111
100             
111"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (middle - right)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
           
     111      
     100                   
     111  
            "
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (middle - right) with spaces around"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111
101             
011"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (bottom - left)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
           
     111      
     101                   
     011  
            "
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (bottom - left) with spaces around"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="111
101             
101"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (bottom - middle)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111
101             
101"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (bottom - middle)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
           
     111      
     101                   
     101  
            "
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (bottom - middle) with spaces around"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111
101             
110"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (bottom - right)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
           
     111      
     101                   
     110  
            "
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Breach in wall (bottom - right) with spaces around"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

# WRONG MESSAGE, SHOWING ALLOWED CHARACTERS BUT THEY'RE VALID
# MAP_CONTENT="
# 111111111111
# 100010110001
# 10001  100O1
# 10001  10001
# 100011110001
# 100000000001
# 111111111111"
# ERR_MESSAGE="Error."
# DESCRIPTION="Unclosed inside"
# executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

echo "\n${YELLOW}FOREIGN CHARS ERRORS:${NC}\n"

MAP_CONTENT="
111
1L1
111"
ERR_MESSAGE="Error. Allowed characters: '1' - '0' - ' ' - 'N' - 'S' - 'E' - 'W'."
DESCRIPTION="No content, foreign character"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111111111111
100000000001
1000000000O1
111111111111"
ERR_MESSAGE="Error. Allowed characters: '1' - '0' - ' ' - 'N' - 'S' - 'E' - 'W'."
DESCRIPTION="Foreign character in corner"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111111111111
1000000000\t1
100000000001
111111111111"
ERR_MESSAGE="Error. Allowed characters: '1' - '0' - ' ' - 'N' - 'S' - 'E' - 'W'."
DESCRIPTION="Tab in corner"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111111111111
100000000001
10000a000001
100000000001
111111111111"
ERR_MESSAGE="Error. Allowed characters: '1' - '0' - ' ' - 'N' - 'S' - 'E' - 'W'."
DESCRIPTION="Foreign character in the middle"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111111111111
100011110001
10001L 100O1
10001  10001
100011110001
100000000001
111111111111"
ERR_MESSAGE="Error. Allowed characters: '1' - '0' - ' ' - 'N' - 'S' - 'E' - 'W'."
DESCRIPTION="Foreign char inside inner hole"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"


echo "\n${YELLOW}REPEATED PLAYER ERRORS:${NC}\n"

MAP_CONTENT="
1111
1SS1             
1111"
ERR_MESSAGE="Error. Incorrect player number."
DESCRIPTION="Repeated player char (same)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111111111111
1S0000000001
100000000001
1000000000S1
111111111111"
ERR_MESSAGE="Error. Incorrect player number."
DESCRIPTION="Repeated player (same char)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111111111111
1S0000000001
100000000001
1000000000W1
111111111111"
ERR_MESSAGE="Error. Incorrect player number."
DESCRIPTION="Repeated player (different char)"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111
1S1
1S1
1S1
111"
ERR_MESSAGE="Error. Incorrect player number."
DESCRIPTION="Repeated player, no 0"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
111
1S1
1W1
1E1
1N1
111"
ERR_MESSAGE="Error. Incorrect player number."
DESCRIPTION="Repeated player, all chars"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

# WRONG ERROR MESSAGE, CAN BE IGNORED?
MAP_CONTENT="
111
1S1
1W1
1E1
1N1
111"
ERR_MESSAGE="Error. Incorrect player number."
DESCRIPTION="Repeated player, all chars"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

echo "\n${YELLOW}INTERNET MAP ERRORS:${NC}\n"

MAP_CONTENT="
        1111111111111111111111111
        1000000000000000000000001
        1100000000000000000000001
        1000000000000000000000001
111111111000000000000000000000001
100000000000000000000000000001111
1000000000000AE00000000000001
10000000000000000000000000001
10000000000000000000000000001
10000000000000000000000000001
10000000000000000001010000001
11000001110101011111011110101
11110111 1110111 101111010001
11111111 1111111 111111111111 "
ERR_MESSAGE="Error. Allowed characters: '1' - '0' - ' ' - 'N' - 'S' - 'E' - 'W'."
DESCRIPTION="Foreign character"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"


# Wrong error message
# MAP_CONTENT="
#         1111111111111111111111111
#         1000000000000000000000001
#         1100000000000000000000001
#         1000000000000000000000001
# 111111111000000000000000000000001
# 100000000000000000000000000001111
# 1000000000000EE00000000000001
# 10000000000000000000000000001
# 10000000000000000000000000001
# 10000000000000000000000000001
# 10000000000000000001010000001
# 11000001110101011111011110101
# 11110111 1110111 101111010001
# 11111111 1111111 111111111111
# "
# ERR_MESSAGE="Error on duplicated player"
# DESCRIPTION="Repeated player"
# executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

# Wrong error message
# MAP_CONTENT="
#         1111111111111111111111111
#         1000000000000000000000001
#         1100000000000000000000001
#         1000000000000000000000001
# 111111111000000000000000000000001
# 100000000000000000000000000001111
# 10000000000000000000000000001
# 10000000000000000000000000001
# 10000000000000000000000000001
# 10000000000000000000000000001
# 10000000000000000001010000001
# 11000001110101011111011110101
# 11110111 1110111 101111010001
# 11111111 1111111 111111111111
# "
# ERR_MESSAGE="Error on missing player"
# DESCRIPTION="Missing player"
# executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
        1111111111111111111111111
        0000002000000000000000001
        1200000000000000000000001
        1000000000000000000000001
111111111000000000000000000000001
10000000000000N000000000000001111
10000000000000000000000000001
10000000000000000000000000001
10000000000000000000000000001
10000000000000000000000000001
10000000000000000001010000001
11000001110101011111011110101
11110111 1110111 111111110001
11111111 1111111 111111111111
"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Open wall"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

# FOREIGN CHAR OR OPEN WALL?
MAP_CONTENT="
        1111111111111111111111111
       20000000000000000000000001
        1200000000000000000000001
        1000000000000000000000001
111111111000000000000000000000001
10000000000000N000000000000001111
10000000000000000000000000001
10000000000000000000000000001
10000000000000000000000000001
10000000000000000000000000001
10000000000000000001010000001
11000001110101011111011110101
11110111 1110111 101111010001
11111111 1111111 111111111111
"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Open wall + foreign char"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"



MAP_CONTENT="
        1111111111111110111111111
        1000000000000000000000001
        1200000000000000000000001
        1000000000000000000000001
111111111000000000000000000000001
10000000000000N000000000000001111
10000000000000000000000000001
10000000000000000000000000001
10000000000000000000000000001
10000000000000000000000000001
10000000000000000001010000001
11000001110101011111011110101
11110111 1110111 101111010001
11111111 1111111 111111111111
"
ERR_MESSAGE="Error. Incorrect map: not surrounded by walls."
DESCRIPTION="Open wall"
executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"

# Wrong error message
# MAP_CONTENT="
#         1111111111111111111111111
#         1000000000000000000000000
#         1200000000000000000000001
#         1000000000000000000000001
# 111111111000000000000000000000001
# 10000000000000N000000000000001111
# 10000000000000000000000000001
# 10000000000000000000000000001
# 10000000000000000000000000001
# 10000000000000000000000000001
# 10000000000000000001010000001
# 11000001110101011111011110101
# 11110111 1110111 101111010001
# 11111111 1111111 111111111111
# "
# ERR_MESSAGE="Error. Allowed characters: '1' - '0' - ' ' - 'N' - 'S' - 'E' - 'W'."
# DESCRIPTION="Foreign char"
# executeErrorTest "$ERR_MESSAGE" "$MAP_CONTENT" "$DESCRIPTION"
