cmake_minimum_required(VERSION 3.12)
project(My_Personal_Diary C)

set(CMAKE_C_STANDARD 99)

add_executable(My_Personal_Diary main.c file_handling.h getTime.h)