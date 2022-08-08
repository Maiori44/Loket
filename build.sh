#!/bin/bash
clear
cd src
if [[ "$1" == "-win" ]]; then
	x86_64-w64-mingw32-gcc-win32 main.c dynstack.c -o loket.exe -Wall && wine ./loket.exe $2 $3
else
	gcc main.c dynstack.c -o loket -Wall && ./loket $1 $2
fi
