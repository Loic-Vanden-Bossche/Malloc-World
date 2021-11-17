cmake_minimum_required(VERSION 3.20)
project(Malloc-World-SDL C)

set(CMAKE_C_STANDARD 99)

message(STATUS "project location is : " ${CMAKE_SOURCE_DIR})

find_library(SDL2_LIBRARY SDL2 HINTS ${CMAKE_SOURCE_DIR}/SDL2-Libraries/lib/i686)

message(STATUS "SDL2 location is : " ${SDL2_LIBRARY})

set(Sources src/main.c)
set(Headers headers/main.h)

include_directories(${CMAKE_SOURCE_DIR}/SDL2-Libraries/includes)

add_executable(Malloc-World-SDL ${Sources} ${Headers})

target_link_libraries(Malloc-World-SDL ${SDL2_LIBRARY})
