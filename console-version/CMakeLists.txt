cmake_minimum_required(VERSION 3.20)
project(Malloc-World C)

set(CMAKE_C_STANDARD 99)

set(Sources src/main.c src/save.c src/map.c src/player.c src/item.c src/craft.c src/game.c src/storage.c src/map-generator.c)
set(Headers headers/save.h headers/map.h headers/main.h headers/player.h headers/item.h headers/craft.h headers/game.h headers/storage.h headers/map-generator.h)

add_executable(Malloc-World ${Sources} ${Headers})
