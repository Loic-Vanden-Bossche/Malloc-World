//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#include "../headers/map.h"

const mapElement mapElements[103] = {
        { -3, {0, 2, 3}, PORTAL }, // Portal between zones II and III
        { -2, {1, 2, 0}, PORTAL }, // Portal between zones I and II
        { -1, {1, 2, 3}, WALL }, // inaccessible area
        { 0, {1, 2, 3}, FLOOR }, // Free area
        { 1, {1, 2, 3}, PLAYER }, // Player
        { 2, {1, 2, 3}, NPC }, // NPC
        { 3, {1, 0, 0}, RESSOURCE }, // Plant zone I
        { 4, {1, 0, 0}, RESSOURCE }, // Rock zone I
        { 5, {1, 0, 0}, RESSOURCE }, // Wood zone I
        { 6, {0, 2, 0}, RESSOURCE }, // Plant zone II
        { 7, {0, 2, 0}, RESSOURCE }, // Rock zone II
        { 8, {0, 2, 0}, RESSOURCE }, // Wood zone II
        { 9, {0, 0, 3}, RESSOURCE }, // Plant zone III
        { 10, {0, 0, 3}, RESSOURCE }, // Rock zone III
        { 11, {0, 0, 3}, RESSOURCE }, // Wood zone III
        { 12, {1, 2, 3}, MONSTER },
        { 13, {1, 2, 3}, MONSTER },
        { 14, {1, 2, 3}, MONSTER },
        { 15, {1, 2, 3}, MONSTER },
        { 16, {1, 2, 3}, MONSTER },
        { 17, {1, 2, 3}, MONSTER },
        { 18, {1, 2, 3}, MONSTER },
        { 19, {1, 2, 3}, MONSTER },
        { 20, {1, 2, 3}, MONSTER },
        { 21, {1, 2, 3}, MONSTER },
        { 22, {1, 2, 3}, MONSTER },
        { 23, {1, 2, 3}, MONSTER },
        { 24, {1, 2, 3}, MONSTER },
        { 25, {1, 2, 3}, MONSTER },
        { 26, {1, 2, 3}, MONSTER },
        { 27, {1, 2, 3}, MONSTER },
        { 28, {1, 2, 3}, MONSTER },
        { 29, {1, 2, 3}, MONSTER },
        { 30, {1, 2, 3}, MONSTER },
        { 31, {1, 2, 3}, MONSTER },
        { 32, {1, 2, 3}, MONSTER },
        { 33, {1, 2, 3}, MONSTER },
        { 34, {1, 2, 3}, MONSTER },
        { 35, {1, 2, 3}, MONSTER },
        { 36, {1, 2, 3}, MONSTER },
        { 37, {1, 2, 3}, MONSTER },
        { 38, {1, 2, 3}, MONSTER },
        { 39, {1, 2, 3}, MONSTER },
        { 40, {1, 2, 3}, MONSTER },
        { 41, {1, 2, 3}, MONSTER },
        { 42, {1, 2, 3}, MONSTER },
        { 43, {1, 2, 3}, MONSTER },
        { 44, {1, 2, 3}, MONSTER },
        { 45, {1, 2, 3}, MONSTER },
        { 46, {1, 2, 3}, MONSTER },
        { 47, {1, 2, 3}, MONSTER },
        { 48, {1, 2, 3}, MONSTER },
        { 49, {1, 2, 3}, MONSTER },
        { 50, {1, 2, 3}, MONSTER },
        { 51, {1, 2, 3}, MONSTER },
        { 52, {1, 2, 3}, MONSTER },
        { 53, {1, 2, 3}, MONSTER },
        { 54, {1, 2, 3}, MONSTER },
        { 55, {1, 2, 3}, MONSTER },
        { 56, {1, 2, 3}, MONSTER },
        { 57, {1, 2, 3}, MONSTER },
        { 58, {1, 2, 3}, MONSTER },
        { 59, {1, 2, 3}, MONSTER },
        { 60, {1, 2, 3}, MONSTER },
        { 61, {1, 2, 3}, MONSTER },
        { 62, {1, 2, 3}, MONSTER },
        { 63, {1, 2, 3}, MONSTER },
        { 64, {1, 2, 3}, MONSTER },
        { 65, {1, 2, 3}, MONSTER },
        { 66, {1, 2, 3}, MONSTER },
        { 67, {1, 2, 3}, MONSTER },
        { 68, {1, 2, 3}, MONSTER },
        { 69, {1, 2, 3}, MONSTER },
        { 70, {1, 2, 3}, MONSTER },
        { 71, {1, 2, 3}, MONSTER },
        { 72, {1, 2, 3}, MONSTER },
        { 73, {1, 2, 3}, MONSTER },
        { 74, {1, 2, 3}, MONSTER },
        { 75, {1, 2, 3}, MONSTER },
        { 76, {1, 2, 3}, MONSTER },
        { 77, {1, 2, 3}, MONSTER },
        { 78, {1, 2, 3}, MONSTER },
        { 79, {1, 2, 3}, MONSTER },
        { 80, {1, 2, 3}, MONSTER },
        { 81, {1, 2, 3}, MONSTER },
        { 82, {1, 2, 3}, MONSTER },
        { 83, {1, 2, 3}, MONSTER },
        { 84, {1, 2, 3}, MONSTER },
        { 85, {1, 2, 3}, MONSTER },
        { 86, {1, 2, 3}, MONSTER },
        { 87, {1, 2, 3}, MONSTER },
        { 88, {1, 2, 3}, MONSTER },
        { 89, {1, 2, 3}, MONSTER },
        { 90, {1, 2, 3}, MONSTER },
        { 91, {1, 2, 3}, MONSTER },
        { 92, {1, 2, 3}, MONSTER },
        { 93, {1, 2, 3}, MONSTER },
        { 94, {1, 2, 3}, MONSTER },
        { 95, {1, 2, 3}, MONSTER },
        { 96, {1, 2, 3}, MONSTER },
        { 97, {1, 2, 3}, MONSTER },
        { 98, {1, 2, 3}, MONSTER },
        { 99, {0, 0, 3}, BOSS }, // Final Boss
};

const mapElement* getMapElements() {
    return mapElements;
}

const mapElement* getMapElementById(int id) {
    for (int i = 0; i < 103; ++i) {
        if(mapElements[i].value == id) return &mapElements[i];
    }

    return NULL;
}

int elementIsInLvl(mapElement element, int targetLvl) {

    for (int i = 0; i < 3; ++i)
        if(element.avaliableZones[i] == targetLvl) return 1;

    return 0;
}

void setCurrentLvl(map* worldMap, int lvl,int upOrDown) {

    if(lvl < 0 || lvl > 3) return;

    worldMap->currentLvl = lvl;

    if(upOrDown) {
        setCurrentCoordinate(worldMap, (coordinate){2, 1});
    } else {
        setCurrentCoordinate(worldMap, (coordinate){MAP_SIZE_X - 2, MAP_SIZE_Y - 1});
    }
}

map *createMap(int startLvl) {

    map *newMap = malloc(sizeof(map));
    newMap->currentLvl = startLvl;

    newMap->currentCoords.x = -1;
    newMap->currentCoords.y = -1;

    newMap->lvl = (int***)malloc(3*sizeof(int**));

    for (int lvl = 0; lvl < 3; lvl++) {
        newMap->lvl[lvl] = (int**)malloc(MAP_SIZE_Y*sizeof(int*));
        for (int i = 0; i < MAP_SIZE_Y; i++) {
            newMap->lvl[lvl][i] = (int*)malloc(MAP_SIZE_X*sizeof(int));

            for (int j = 0; j < MAP_SIZE_X; ++j) {
                newMap->lvl[lvl][i][j] = 0;
            }
        }
    }

    return newMap;
}

void destroyMap(map *worldMap) {

    for(int lvl = 0; lvl < 3;lvl++) {
        for(int yi = 0;yi < MAP_SIZE_Y;yi++) {
            free(worldMap->lvl[lvl][yi]);
        }
        free(worldMap->lvl[lvl]);
    }

    free(worldMap->lvl);
    free(worldMap);
}

int setCurrentCoordinate(map* worldMap, coordinate targetCoordinates) {

    if((targetCoordinates.x >= MAP_SIZE_X - 1 || targetCoordinates.y >= MAP_SIZE_Y - 1) ||
    (targetCoordinates.x < 0 || targetCoordinates.y < 0))
        return -10;

    const int targetMapElem = worldMap->lvl[worldMap->currentLvl][targetCoordinates.y][targetCoordinates.x];

    if(targetMapElem == 0){

        if(worldMap->currentCoords.x != -1 && worldMap->currentCoords.y != -1) {
            worldMap->lvl[worldMap->currentLvl][worldMap->currentCoords.y][worldMap->currentCoords.x] = 0;
        }

        worldMap->currentCoords.x = targetCoordinates.x;
        worldMap->currentCoords.y = targetCoordinates.y;

        debug("Player is at (%d, %d)\n", worldMap->currentCoords.x, worldMap->currentCoords.y);

        worldMap->lvl[worldMap->currentLvl][targetCoordinates.y][targetCoordinates.x] = 1;
    }

    return targetMapElem;
}