cmake_minimum_required(VERSION 3.29)
project(calc4 C)

set(CMAKE_C_STANDARD 11)

add_executable(calc4 main.c
        arithmetic.h
        processing.h
        power.h
        convertBase.h)
