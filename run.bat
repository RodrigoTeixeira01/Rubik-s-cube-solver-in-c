@echo off
if EXIST main.c (if EXIST main.exe (del main.exe))
if EXIST main.c (gcc main.c -O3 -o main.exe)
if EXIST main.c (if EXIST main.exe (.\main.exe))
@echo on