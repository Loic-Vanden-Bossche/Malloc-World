//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#ifndef MALLOC_WORLD_MAP_H
#define MALLOC_WORLD_MAP_H

#include "stdlib.h"
#include "stdio.h"
#include "map-generator.h"

#define MAP_SIZE_X 150
#define MAP_SIZE_Y 40

typedef struct MapElement {

  int value;
  char *name;
  int avaliableZones[3];

} mapElement;

typedef struct Map {
    int currentLvl;
    int mapSizeX;
    int mapSizeY;
    int ***lvl;
} map;

const mapElement* getMapElements();
int elementIsInLvl(mapElement element, int targetLvl);

map* createMap(int startLvl);

void destroyMap(map* worldMap);

void displayMap(map* worldMap);


#endif //MALLOC_WORLD_MAP_H
