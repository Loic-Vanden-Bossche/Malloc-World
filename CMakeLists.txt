cmake_minimum_required(VERSION 3.20)
project(Malloc-World C)

set(CMAKE_C_STANDARD 99)

set(Sources main.c save.c)
set(Headers save.h map.c map.h)

add_executable(Malloc-World ${Sources} ${Headers})
