cmake_minimum_required(VERSION 3.20)
project(Malloc-World C)

set(CMAKE_C_STANDARD 99)

set(Sources main.c save-parser.c)
set(Headers save-parser.h map.c map.h)

add_executable(Malloc-World ${Sources} ${Headers})
