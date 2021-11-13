//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#include "../headers/map.h"

const int MAP_SIZE = 40;

const mapElement mapElements[103] = {
        { -3, "Portail entre zones II & III", {0, 2, 3} },
        { -2, "Portail entre zones I & II", {1, 2, 0} },
        { -1, "Case infranchissable", {1, 2, 3} },
        { 0, "Zone libre pour se déplacer", {1, 2, 3} },
        { 1, "Joueur", {1, 2, 3} },
        { 2, "PNJ", {1, 2, 3} },
        { 3, "Plante zone I", {1, 0, 0} },
        { 4, "Rocher zone I", {1, 0, 0} },
        { 5, "Bois zone I", {1, 0, 0} },
        { 6, "Plante zone II", {0, 2, 0} },
        { 7, "Rocher zone II", {0, 2, 0} },
        { 8, "Bois zone II", {0, 2, 0} },
        { 9, "Plante zone III", {0, 0, 3} },
        { 10, "Rocher zone III", {0, 0, 3} },
        { 11, "Bois zone III", {0, 0, 3} },
        { 12, "Monstre 12", {1, 2, 3} },
        { 13, "Monstre 13", {1, 2, 3} },
        { 14, "Monstre 14", {1, 2, 3} },
        { 15, "Monstre 15", {1, 2, 3} },
        { 16, "Monstre 16", {1, 2, 3} },
        { 17, "Monstre 17", {1, 2, 3} },
        { 18, "Monstre 18", {1, 2, 3} },
        { 19, "Monstre 19", {1, 2, 3} },
        { 20, "Monstre 20", {1, 2, 3} },
        { 21, "Monstre 21", {1, 2, 3} },
        { 22, "Monstre 22", {1, 2, 3} },
        { 23, "Monstre 23", {1, 2, 3} },
        { 24, "Monstre 24", {1, 2, 3} },
        { 25, "Monstre 25", {1, 2, 3} },
        { 26, "Monstre 26", {1, 2, 3} },
        { 27, "Monstre 27", {1, 2, 3} },
        { 28, "Monstre 28", {1, 2, 3} },
        { 29, "Monstre 29", {1, 2, 3} },
        { 30, "Monstre 30", {1, 2, 3} },
        { 31, "Monstre 31", {1, 2, 3} },
        { 32, "Monstre 32", {1, 2, 3} },
        { 33, "Monstre 33", {1, 2, 3} },
        { 34, "Monstre 34", {1, 2, 3} },
        { 35, "Monstre 35", {1, 2, 3} },
        { 36, "Monstre 36", {1, 2, 3} },
        { 37, "Monstre 37", {1, 2, 3} },
        { 38, "Monstre 38", {1, 2, 3} },
        { 39, "Monstre 39", {1, 2, 3} },
        { 40, "Monstre 40", {1, 2, 3} },
        { 41, "Monstre 41", {1, 2, 3} },
        { 42, "Monstre 42", {1, 2, 3} },
        { 43, "Monstre 43", {1, 2, 3} },
        { 44, "Monstre 44", {1, 2, 3} },
        { 45, "Monstre 45", {1, 2, 3} },
        { 46, "Monstre 46", {1, 2, 3} },
        { 47, "Monstre 47", {1, 2, 3} },
        { 48, "Monstre 48", {1, 2, 3} },
        { 49, "Monstre 49", {1, 2, 3} },
        { 50, "Monstre 50", {1, 2, 3} },
        { 51, "Monstre 51", {1, 2, 3} },
        { 52, "Monstre 52", {1, 2, 3} },
        { 53, "Monstre 53", {1, 2, 3} },
        { 54, "Monstre 54", {1, 2, 3} },
        { 55, "Monstre 55", {1, 2, 3} },
        { 56, "Monstre 56", {1, 2, 3} },
        { 57, "Monstre 57", {1, 2, 3} },
        { 58, "Monstre 58", {1, 2, 3} },
        { 59, "Monstre 59", {1, 2, 3} },
        { 60, "Monstre 60", {1, 2, 3} },
        { 61, "Monstre 61", {1, 2, 3} },
        { 62, "Monstre 62", {1, 2, 3} },
        { 63, "Monstre 63", {1, 2, 3} },
        { 64, "Monstre 64", {1, 2, 3} },
        { 65, "Monstre 65", {1, 2, 3} },
        { 66, "Monstre 66", {1, 2, 3} },
        { 67, "Monstre 67", {1, 2, 3} },
        { 68, "Monstre 68", {1, 2, 3} },
        { 69, "Monstre 69", {1, 2, 3} },
        { 70, "Monstre 70", {1, 2, 3} },
        { 71, "Monstre 71", {1, 2, 3} },
        { 72, "Monstre 72", {1, 2, 3} },
        { 73, "Monstre 73", {1, 2, 3} },
        { 74, "Monstre 74", {1, 2, 3} },
        { 75, "Monstre 75", {1, 2, 3} },
        { 76, "Monstre 76", {1, 2, 3} },
        { 77, "Monstre 77", {1, 2, 3} },
        { 78, "Monstre 78", {1, 2, 3} },
        { 79, "Monstre 79", {1, 2, 3} },
        { 80, "Monstre 80", {1, 2, 3} },
        { 81, "Monstre 81", {1, 2, 3} },
        { 82, "Monstre 82", {1, 2, 3} },
        { 83, "Monstre 83", {1, 2, 3} },
        { 84, "Monstre 84", {1, 2, 3} },
        { 85, "Monstre 85", {1, 2, 3} },
        { 86, "Monstre 86", {1, 2, 3} },
        { 87, "Monstre 87", {1, 2, 3} },
        { 88, "Monstre 88", {1, 2, 3} },
        { 89, "Monstre 89", {1, 2, 3} },
        { 90, "Monstre 90", {1, 2, 3} },
        { 91, "Monstre 91", {1, 2, 3} },
        { 92, "Monstre 92", {1, 2, 3} },
        { 93, "Monstre 93", {1, 2, 3} },
        { 94, "Monstre 94", {1, 2, 3} },
        { 95, "Monstre 95", {1, 2, 3} },
        { 96, "Monstre 96", {1, 2, 3} },
        { 97, "Monstre 97", {1, 2, 3} },
        { 98, "Monstre 98", {1, 2, 3} },
        { 99, "Boss de fin", {0, 0, 3} },
};

const mapElement* getMapElements() {
    return mapElements;
}

int elementIsInLvl(mapElement element, int targetLvl) {

    for (int i = 0; i < 3; ++i)
        if(element.avaliableZones[i] == targetLvl) return 1;

    return 0;
}

map *createMap(int startLvl) {

    map *newMap = malloc(sizeof(newMap));
    newMap->mapSize = MAP_SIZE;
    newMap->currentLvl = startLvl;

    newMap->lvl = malloc(3*sizeof(int**));

    for (int lvl = 0; lvl < 3; lvl++) {
        newMap->lvl[lvl] = malloc(MAP_SIZE*sizeof(int*));
        for (int i = 0; i < MAP_SIZE; i++) {
            newMap->lvl[lvl][i] = malloc(MAP_SIZE*sizeof(int));

            for (int j = 0; j < MAP_SIZE; ++j) {
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

void displayMap(map* worldMap) {

    for (int i = 0; i < worldMap->mapSize; ++i) {
        for (int j = 0; j < worldMap->mapSize; ++j) {
            printf("%d", worldMap->lvl[worldMap->currentLvl][i][j]);
        }
        printf("\n");
    }
}

