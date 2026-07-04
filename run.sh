#!/bin/bash

make
cd tests
./K1820BE1 TEST_MAC_OK.ASM
cd -