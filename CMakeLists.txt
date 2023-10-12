cmake_minimum_required(VERSION 3.26)
project(roughFile)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(roughFile
        header.c
        header.h
        limitOfUnsignedLongLongInt.c
        masterPassword.c
        rsa.c
        RSA.cpp)
