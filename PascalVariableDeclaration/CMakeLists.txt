cmake_minimum_required(VERSION 3.3)
project(PascalVariableDeclaration)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c filehandle.c filehandle.h lexer.c lexer.h parser.c parser.h)
add_executable(PascalVariableDeclaration ${SOURCE_FILES})