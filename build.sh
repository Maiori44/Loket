#!/bin/bash
clear
cd src
gcc main.c -o main -Wall && ./main $1 $2 $3