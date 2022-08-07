#!/bin/bash
clear
cd src
gcc main.c dynstack.c -o main -Wall && ./main $1 $2
