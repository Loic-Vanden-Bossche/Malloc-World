//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#ifndef MALLOC_WORLD_MAP_H
#define MALLOC_WORLD_MAP_H

#include "stdlib.h"
#include "stdio.h"


#define MAP_SIZE_X 150
#define MAP_SIZE_Y 40

#define TILE_FLOOR 0
#define TILE_WALL -1

typedef struct MapElement {

  int value;
  char *name;
  int avaliableZones[3];

} mapElement;

typedef struct Map {
    int currentLvl;
    int ***lvl;
} map;

const mapElement* getMapElements();
int elementIsInLvl(mapElement element, int targetLvl);

map* createMap(int startLvl);

void destroyMap(map* worldMap);

#include "map-generator.h"

#endif //MALLOC_WORLD_MAP_H
