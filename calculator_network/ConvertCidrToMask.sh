#!/bin/bash

#compiling
gcc -Wall -Wextra -Werror ./srcs/find_subnet.c

#run with argv1 as argument
./a.out "$1"