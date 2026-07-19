#!/bin/bash

cd tests

printf "empty test [1]: if no error ......................\t"
[ $(./K1820BE1 TEST_EMPTY_OK.ASM | grep ".*ERROR.*" | wc -l) -eq 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"

printf "include test [1]: if no error ....................\t"
[ $(./K1820BE1 TEST_INC_OK.ASM | grep ".*ERROR.*" | wc -l) -eq 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "include test [2]: include without name ...........\t"
[ $(./K1820BE1 TEST_INC_ERR2.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "include test [3]: include file which not exist ...\t"
[ $(./K1820BE1 TEST_INC_ERR3.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "include test [4]: one file included twice ........\t"
[ $(./K1820BE1 TEST_INC_ERR1.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"

printf "macros test [1]: if no error .........................\t"
[ $(./K1820BE1 TEST_MAC_OK.ASM | grep ".*ERROR.*" | wc -l) -eq 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "macros test [2]: macro without name ..................\t"
[ $(./K1820BE1 TEST_MAC_ERR1.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "macros test [3]: macro wrong name - number ...........\t"
[ $(./K1820BE1 TEST_MAC_ERR2.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "macros test [4]: macro without endm ..................\t"
[ $(./K1820BE1 TEST_MAC_ERR3.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "macros test [5]: endm without macro ..................\t"
[ $(./K1820BE1 TEST_MAC_ERR4.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "macros test [6]: macro similar names .................\t"
[ $(./K1820BE1 TEST_MAC_ERR5.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "macros test [7]: macro similar names in other file ...\t"
[ $(./K1820BE1 TEST_MAC_ERR6.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "macros test [8]: macro in macro - error ..............\t"
[ $(./K1820BE1 TEST_MAC_ERR7.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"

printf "equal test [ 1]: if no error .................\t"
[ $(./K1820BE1 TEST_EQU_OK.ASM | grep ".*ERROR.*" | wc -l) -eq 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [ 2]: empty equal .................\t"
[ $(./K1820BE1 TEST_EQU_ERR1.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [ 3]: equal without '=' ...........\t"
[ $(./K1820BE1 TEST_EQU_ERR2.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [ 4]: equal without name ..........\t"
[ $(./K1820BE1 TEST_EQU_ERR3.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [ 5]: equal without number ........\t"
[ $(./K1820BE1 TEST_EQU_ERR4.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [ 6]: wrong name - it is number ...\t"
[ $(./K1820BE1 TEST_EQU_ERR5.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [ 7]: similar names ...............\t"
[ $(./K1820BE1 TEST_EQU_ERR6.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [ 8]: wrong number 1 ..............\t"
[ $(./K1820BE1 TEST_EQU_ERR8.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [ 9]: wrong number 2 ..............\t"
[ $(./K1820BE1 TEST_EQU_ERR9.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [10]: wrong brackets 1 ............\t"
[ $(./K1820BE1 TEST_EQU_ERR10.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [11]: wrong brackets 2 ............\t"
[ $(./K1820BE1 TEST_EQU_ERR11.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [12]: wrong definision 1 ..........\t"
[ $(./K1820BE1 TEST_EQU_ERR12.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [13]: wrong definision 2 ..........\t"
[ $(./K1820BE1 TEST_EQU_ERR13.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [14]: wrong definision 3 ..........\t"
[ $(./K1820BE1 TEST_EQU_ERR14.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [15]: wrong definision 4 ..........\t"
[ $(./K1820BE1 TEST_EQU_ERR15.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [16]: wrong definision 5 ..........\t"
[ $(./K1820BE1 TEST_EQU_ERR16.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [17]: wrong definision 6 ..........\t"
[ $(./K1820BE1 TEST_EQU_ERR17.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [18]: wrong definision 7 ..........\t"
[ $(./K1820BE1 TEST_EQU_ERR18.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [19]: wrong definision 8 ..........\t"
[ $(./K1820BE1 TEST_EQU_ERR19.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "equal test [20]: wrong definision 9 ..........\t"
[ $(./K1820BE1 TEST_EQU_ERR20.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"

printf "all test [ 1]: if no error ...\t"
[ $(./K1820BE1 TEST_ALL_OK1.ASM | grep ".*ERROR.*" | wc -l) -eq 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "all test [ 2]: if no error ...\t"
[ $(./K1820BE1 TEST_ALL_OK2.ASM | grep ".*ERROR.*" | wc -l) -eq 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"
printf "all test [ 3]: empty equal ...\t"
[ $(./K1820BE1 TEST_ALL_ERR1.ASM | grep ".*ERROR.*" | wc -l) -gt 0 ] \
    && echo -e "\033[1;32mOK\033[0m" || echo -e "\033[1;31mERROR\033[0m"

cd -
echo "tests end"
