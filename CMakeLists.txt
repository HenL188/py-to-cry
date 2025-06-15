cmake_minimum_required(VERSION 3.31)
project(lexer CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(lexer main.cpp
        writer.cpp
        writer.h)
# lexer.cpp writer.cpp