#!/bin/bash

make
cd tests
./K1820BE1 test_inc_ok.asm
cd -