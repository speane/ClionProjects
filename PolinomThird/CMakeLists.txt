cmake_minimum_required(VERSION 3.3)
project(PolinomThird)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c lexer.c lexer.h parser.c parser.h generator.c generator.h)
add_executable(PolinomThird ${SOURCE_FILES})