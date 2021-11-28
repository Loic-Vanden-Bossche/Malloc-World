cmake_minimum_required(VERSION 3.16.3)
project(Malloc-World C)

set(CMAKE_C_STANDARD 99)

set(LIB m)

set(Sources src/main.c src/save.c src/map.c src/player.c src/item.c src/craft.c src/game.c src/storage.c src/map-generator.c src/pathfind.c src/debugger.c src/display.c src/monster.c)
set(headers headers/save.h headers/map.h headers/main.h headers/player.h headers/item.h headers/craft.h headers/game.h headers/storage.h headers/map-generator.h headers/pathfind.h headers/debugger.h headers/display.h headers/monster.h)

add_executable(Malloc-World ${Sources} ${Headers})

target_link_libraries(Malloc-World ${LIB})