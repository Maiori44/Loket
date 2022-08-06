#!/bin/bash
clear
cd src
gcc main.c dynstack.c encryptor.c -o main -Wall && ./main $1 $2 $3