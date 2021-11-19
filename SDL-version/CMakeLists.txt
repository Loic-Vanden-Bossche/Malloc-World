cmake_minimum_required(VERSION 3.16.3)
project(Malloc-World-SDL C)

set(CMAKE_C_STANDARD 99)

message(STATUS "project location is : " ${CMAKE_SOURCE_DIR})

if (WIN32)
    find_library(SDL2_LIBRARY SDL2 HINTS ${CMAKE_SOURCE_DIR}/SDL2-Library/SDL2-2.0.16/x86_64-w64-mingw32/lib)
    include_directories(${CMAKE_SOURCE_DIR}/SDL2-Library/SDL2-2.0.16/x86_64-w64-mingw32/include)
elseif(UNIX)
    set(SDL2_LIBRARY SDL2)
endif()

message(STATUS "SDL2 location is : " ${SDL2_LIBRARY})

set(Sources src/main.c)
set(Headers headers/main.h)

add_executable(Malloc-World-SDL ${Sources} ${Headers})

target_link_libraries(Malloc-World-SDL ${SDL2_LIBRARY})