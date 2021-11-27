//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#include "../headers/map.h"

const mapElement mapElements[103] = {
        { -3, "Portail entre zones II & III", {0, 2, 3}, PORTAL },
        { -2, "Portail entre zones I & II", {1, 2, 0}, PORTAL },
        { -1, "Case infranchissable", {1, 2, 3}, WALL },
        { 0, "Zone libre pour se déplacer", {1, 2, 3}, FLOOR },
        { 1, "Joueur", {1, 2, 3}, PLAYER },
        { 2, "PNJ", {1, 2, 3}, NPC },
        { 3, "Plante zone I", {1, 0, 0}, RESSOURCE },
        { 4, "Rocher zone I", {1, 0, 0}, RESSOURCE },
        { 5, "Bois zone I", {1, 0, 0}, RESSOURCE },
        { 6, "Plante zone II", {0, 2, 0}, RESSOURCE },
        { 7, "Rocher zone II", {0, 2, 0}, RESSOURCE },
        { 8, "Bois zone II", {0, 2, 0}, RESSOURCE },
        { 9, "Plante zone III", {0, 0, 3}, RESSOURCE },
        { 10, "Rocher zone III", {0, 0, 3}, RESSOURCE },
        { 11, "Bois zone III", {0, 0, 3}, RESSOURCE },
        { 12, "Monstre 12", {1, 2, 3}, MONSTER },
        { 13, "Monstre 13", {1, 2, 3}, MONSTER },
        { 14, "Monstre 14", {1, 2, 3}, MONSTER },
        { 15, "Monstre 15", {1, 2, 3}, MONSTER },
        { 16, "Monstre 16", {1, 2, 3}, MONSTER },
        { 17, "Monstre 17", {1, 2, 3}, MONSTER },
        { 18, "Monstre 18", {1, 2, 3}, MONSTER },
        { 19, "Monstre 19", {1, 2, 3}, MONSTER },
        { 20, "Monstre 20", {1, 2, 3}, MONSTER },
        { 21, "Monstre 21", {1, 2, 3}, MONSTER },
        { 22, "Monstre 22", {1, 2, 3}, MONSTER },
        { 23, "Monstre 23", {1, 2, 3}, MONSTER },
        { 24, "Monstre 24", {1, 2, 3}, MONSTER },
        { 25, "Monstre 25", {1, 2, 3}, MONSTER },
        { 26, "Monstre 26", {1, 2, 3}, MONSTER },
        { 27, "Monstre 27", {1, 2, 3}, MONSTER },
        { 28, "Monstre 28", {1, 2, 3}, MONSTER },
        { 29, "Monstre 29", {1, 2, 3}, MONSTER },
        { 30, "Monstre 30", {1, 2, 3}, MONSTER },
        { 31, "Monstre 31", {1, 2, 3}, MONSTER },
        { 32, "Monstre 32", {1, 2, 3}, MONSTER },
        { 33, "Monstre 33", {1, 2, 3}, MONSTER },
        { 34, "Monstre 34", {1, 2, 3}, MONSTER },
        { 35, "Monstre 35", {1, 2, 3}, MONSTER },
        { 36, "Monstre 36", {1, 2, 3}, MONSTER },
        { 37, "Monstre 37", {1, 2, 3}, MONSTER },
        { 38, "Monstre 38", {1, 2, 3}, MONSTER },
        { 39, "Monstre 39", {1, 2, 3}, MONSTER },
        { 40, "Monstre 40", {1, 2, 3}, MONSTER },
        { 41, "Monstre 41", {1, 2, 3}, MONSTER },
        { 42, "Monstre 42", {1, 2, 3}, MONSTER },
        { 43, "Monstre 43", {1, 2, 3}, MONSTER },
        { 44, "Monstre 44", {1, 2, 3}, MONSTER },
        { 45, "Monstre 45", {1, 2, 3}, MONSTER },
        { 46, "Monstre 46", {1, 2, 3}, MONSTER },
        { 47, "Monstre 47", {1, 2, 3}, MONSTER },
        { 48, "Monstre 48", {1, 2, 3}, MONSTER },
        { 49, "Monstre 49", {1, 2, 3}, MONSTER },
        { 50, "Monstre 50", {1, 2, 3}, MONSTER },
        { 51, "Monstre 51", {1, 2, 3}, MONSTER },
        { 52, "Monstre 52", {1, 2, 3}, MONSTER },
        { 53, "Monstre 53", {1, 2, 3}, MONSTER },
        { 54, "Monstre 54", {1, 2, 3}, MONSTER },
        { 55, "Monstre 55", {1, 2, 3}, MONSTER },
        { 56, "Monstre 56", {1, 2, 3}, MONSTER },
        { 57, "Monstre 57", {1, 2, 3}, MONSTER },
        { 58, "Monstre 58", {1, 2, 3}, MONSTER },
        { 59, "Monstre 59", {1, 2, 3}, MONSTER },
        { 60, "Monstre 60", {1, 2, 3}, MONSTER },
        { 61, "Monstre 61", {1, 2, 3}, MONSTER },
        { 62, "Monstre 62", {1, 2, 3}, MONSTER },
        { 63, "Monstre 63", {1, 2, 3}, MONSTER },
        { 64, "Monstre 64", {1, 2, 3}, MONSTER },
        { 65, "Monstre 65", {1, 2, 3}, MONSTER },
        { 66, "Monstre 66", {1, 2, 3}, MONSTER },
        { 67, "Monstre 67", {1, 2, 3}, MONSTER },
        { 68, "Monstre 68", {1, 2, 3}, MONSTER },
        { 69, "Monstre 69", {1, 2, 3}, MONSTER },
        { 70, "Monstre 70", {1, 2, 3}, MONSTER },
        { 71, "Monstre 71", {1, 2, 3}, MONSTER },
        { 72, "Monstre 72", {1, 2, 3}, MONSTER },
        { 73, "Monstre 73", {1, 2, 3}, MONSTER },
        { 74, "Monstre 74", {1, 2, 3}, MONSTER },
        { 75, "Monstre 75", {1, 2, 3}, MONSTER },
        { 76, "Monstre 76", {1, 2, 3}, MONSTER },
        { 77, "Monstre 77", {1, 2, 3}, MONSTER },
        { 78, "Monstre 78", {1, 2, 3}, MONSTER },
        { 79, "Monstre 79", {1, 2, 3}, MONSTER },
        { 80, "Monstre 80", {1, 2, 3}, MONSTER },
        { 81, "Monstre 81", {1, 2, 3}, MONSTER },
        { 82, "Monstre 82", {1, 2, 3}, MONSTER },
        { 83, "Monstre 83", {1, 2, 3}, MONSTER },
        { 84, "Monstre 84", {1, 2, 3}, MONSTER },
        { 85, "Monstre 85", {1, 2, 3}, MONSTER },
        { 86, "Monstre 86", {1, 2, 3}, MONSTER },
        { 87, "Monstre 87", {1, 2, 3}, MONSTER },
        { 88, "Monstre 88", {1, 2, 3}, MONSTER },
        { 89, "Monstre 89", {1, 2, 3}, MONSTER },
        { 90, "Monstre 90", {1, 2, 3}, MONSTER },
        { 91, "Monstre 91", {1, 2, 3}, MONSTER },
        { 92, "Monstre 92", {1, 2, 3}, MONSTER },
        { 93, "Monstre 93", {1, 2, 3}, MONSTER },
        { 94, "Monstre 94", {1, 2, 3}, MONSTER },
        { 95, "Monstre 95", {1, 2, 3}, MONSTER },
        { 96, "Monstre 96", {1, 2, 3}, MONSTER },
        { 97, "Monstre 97", {1, 2, 3}, MONSTER },
        { 98, "Monstre 98", {1, 2, 3}, MONSTER },
        { 99, "Boss de fin", {0, 0, 3}, BOSS },
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