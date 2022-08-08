@echo off
cls
cd src
gcc main.c dynstack.c -o loket -Wall && .\loket %1 %2
