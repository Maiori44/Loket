#!/bin/bash
clear
cd src
if [[ "$1" == "-win" ]]; then
	x86_64-w64-mingw32-gcc-win32 main.c dynstack.c -o main.exe -Wall && wine ./main.exe $2 $3
else
	gcc main.c dynstack.c -o main -Wall && ./main $1 $2
fi
