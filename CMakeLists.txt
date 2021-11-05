cmake_minimum_required(VERSION 3.20)
project(Malloc-World C)

set(CMAKE_C_STANDARD 99)

set(Sources src/main.c src/save.c)
set(Headers headers/save.h src/map.c headers/map.h headers/main.h src/player.c headers/player.h src/item.c headers/item.h)

add_executable(Malloc-World ${Sources} ${Headers})
