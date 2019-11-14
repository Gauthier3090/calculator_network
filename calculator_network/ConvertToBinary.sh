#!/bin/bash

#compiling
gcc -Wall -Wextra -Werror ./srcs/tobinary.c

#run with argv1 as argument
./a.out "$1"