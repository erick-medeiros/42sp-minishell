#!/bin/sh

gcc -Wall -Wextra -Werror -g3 -I../../include Unity/unity.c ../../src/list.c ../../src/cleanup.c list_test.c -o ./list_test.out
./list_test.out
rm ./list_test.out
