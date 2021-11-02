//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#include "map.h"

map *createMap(int startLvl, int mapSize) {

    map *newMap = malloc(sizeof(newMap));
    newMap->mapSize = mapSize;
    newMap->currentLvl = startLvl;

    newMap->lvl = malloc(3*sizeof(int**));

    for (int lvl = 0; lvl < 3; lvl++) {
        newMap->lvl[lvl] = malloc(mapSize*sizeof(int*));
        for (int i = 0; i < mapSize; i++) {
            newMap->lvl[lvl][i] = malloc(mapSize*sizeof(int));

            for (int j = 0; j < mapSize; ++j) {
                newMap->lvl[lvl][i][j] = 0;
            }
        }
    }

    return newMap;
}

void destroyMap(map *worldMap) {

    for (int lvl = 0; lvl < 3; ++lvl) {
        for (int i = 0; i < worldMap->mapSize; ++i) {
            free(worldMap->lvl[lvl][i]);
        }
    }

    for (int lvl = 0; lvl < 3; ++lvl) {
        free(worldMap->lvl[lvl]);
    }

    free(worldMap->lvl);
}

void displayMap(map worldMap) {

    for (int i = 0; i < worldMap.mapSize; ++i) {
        printf("\n");
        for (int j = 0; j < worldMap.mapSize; ++j) {
            printf("%d", worldMap.lvl[worldMap.currentLvl][i][j]);
        }
    }
}

