#!/bin/sh

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m'

MAP_PATH="./tests/maps/color_codes/"
SCRIPT_PATH="./tests/validation_scripts/"
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all"
TEST_OUTPUT="test_output"
VALGRIND_OUTPUT="valgrind_output"
TEST_FILE="test_map.cub"
DEBUG_FILE="debug_output"

executeErrorTest() {
    echo "$2" > $SCRIPT_PATH$TEST_FILE
    ./cub3d "$SCRIPT_PATH$TEST_FILE" > /dev/null 2> "$SCRIPT_PATH$TEST_OUTPUT"

    # Output check
    if [ "$(cat $SCRIPT_PATH$DEBUG_FILE)" = "$1" ]
    then
        echo "    ${GREEN}- $3 (${NC}$(cat $SCRIPT_PATH$TEST_FILE)${GREEN}): ok ✅${NC}"
        echo "        Message:"
        echo "            $1\n"
    else
        echo "    ${RED}- $3: not ok ❌${NC}"
        echo "========================================================================================="
        echo "    Expected:"
        echo "        |$1|\n"
        echo "    Got:"
        echo "        |$(cat $SCRIPT_PATH$DEBUG_FILE)|"
        echo "========================================================================================="
        echo "\n"
        exit 1
    fi

    ERRS_FOUND=$(cat ${SCRIPT_PATH}${TEST_OUTPUT} | grep 'AddressSanitizer' | wc -l)
    # Sanitizer checker
    if [ $ERRS_FOUND -eq 0 ]
    then
        echo "        ${GREEN}No Sanitizer errors detected 👍${NC}"
    else
        echo "        ${RED}Sanitizer errors detected ⛔${NC}"
        echo "\n$(less $SCRIPT_PATH$TEST_OUTPUT)"
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

echo "\n${YELLOW}TYPE IDS HAPPY PATH:${NC}\n"

MAP_CONTENT="NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Regular file"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="

NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0

"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Regular file with newlines"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="   NO ./path_to_the_north_texture
   SO ./path_to_the_south_texture
   WE ./path_to_the_west_texture
   EA ./path_to_the_east_texture
   F 220,100,0
   C 225,30,0
   
"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Regular file with spaces before"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO ./path_to_the_north_texture   
SO ./path_to_the_south_texture   
WE ./path_to_the_west_texture   
EA ./path_to_the_east_texture   
F 220,100,0   
C 225,30,0   
      
"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Regular file with spaces after"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="   NO ./path_to_the_north_texture   
   SO ./path_to_the_south_texture   
   WE ./path_to_the_west_texture   
   EA ./path_to_the_east_texture   
   F 220,100,0   
   C 225,30,0   
   
"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Regular file with spaces before and after"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO ./path_to_the_north_texture

SO ./path_to_the_south_texture

WE ./path_to_the_west_texture

EA ./path_to_the_east_texture

F 220,100,0

C 225,30,0"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Regular file with 1 nl inbetween"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO ./path_to_the_north_texture
   
SO ./path_to_the_south_texture
   
WE ./path_to_the_west_texture
   
EA ./path_to_the_east_texture
   
F 220,100,0
   
C 225,30,0"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Regular file with 1 nl + spaces inbetween"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO ./path_to_the_north_texture


SO ./path_to_the_south_texture


WE ./path_to_the_west_texture


EA ./path_to_the_east_texture


F 220,100,0


C 225,30,0"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Regular file with 2 nl inbetween"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO ./path_to_the_north_texture
   

SO ./path_to_the_south_texture
   

WE ./path_to_the_west_texture
   

EA ./path_to_the_east_texture
   

F 220,100,0
   

C 225,30,0"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Regular file with 2 nl + spaces inbetween"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Orientation chars separated by colors with nl"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Orientation chars separated by colors with nl + spaces"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture


F 220,100,0
C 225,30,0"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Orientation chars separated by colors with 2 nl"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
   
   
F 220,100,0
C 225,30,0"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Orientation chars separated by colors with 2 nl + spaces"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
F 220,100,0
C 225,30,0
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Colors first"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"


MAP_CONTENT="
C 225,30,0
F 220,100,0
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Colors first and swapped"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
C 225,30,0
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Colors first and last"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
NO ./path_to_the_north_texture
C 225,30,0
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
F 220,100,0
EA ./path_to_the_east_texture
"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Scrambled view"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="
    NO ./path_to_the_north_texture     
     C 225,30,0             
            SO ./path_to_the_south_texture      
         WE ./path_to_the_west_texture   
    F 220,100,0     
 EA ./path_to_the_east_texture                                      




"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Scrambled view with spaces and tabs"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"

MAP_CONTENT="

NO ./path_to_the_north_texture


C 225,30,0


SO ./path_to_the_south_texture


WE ./path_to_the_west_texture


F 220,100,0


EA ./path_to_the_east_texture


"
DEBUG_MSG="Type ids validated successfully"
DESCRIPTION="Scrambled view with nls"
executeErrorTest "$DEBUG_MSG" "$MAP_CONTENT" "$DESCRIPTION"