//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#ifndef MALLOC_WORLD_MAP_H
#define MALLOC_WORLD_MAP_H

#include "stdlib.h"
#include "stdio.h"

typedef struct Map {

    int currentLvl;

    int mapSize;

    int ***lvl;

} map;

map *createMap(int startLvl, int mapSize);

void destroyMap(map *worldMap);

void displayMap(map worldMap);

#endif //MALLOC_WORLD_MAP_H
