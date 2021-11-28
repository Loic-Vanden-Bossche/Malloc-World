//
// Created by Loïc Vanden Bossche on 24/11/2021.
//

#include "../headers/display.h"

#define DISPLAY_SIZE_X 150
#define DISPLAY_SIZE_Y 40

#define DISPLAY_MAP_SIZE_X 50
#define DISPLAY_MAP_SIZE_Y 20


int isUnicode = 0;

void setUnicode() {
    isUnicode = 1;
}

void getMapDisplayOffsetParams(coordinate playerPos, int* sXParam, int* sYParam, int* eXParam, int* eYParam) {

    if(playerPos.x < DISPLAY_MAP_SIZE_X/2) {
        *sXParam = 0;
        *eXParam = DISPLAY_MAP_SIZE_X;
    } else if (playerPos.x > MAP_SIZE_X - (DISPLAY_MAP_SIZE_X/2)) {
        *sXParam = MAP_SIZE_X - DISPLAY_MAP_SIZE_X - 1;
        *eXParam = MAP_SIZE_X;
    } else {
        *sXParam = playerPos.x - (DISPLAY_MAP_SIZE_X/2);
        *eXParam = playerPos.x + (DISPLAY_MAP_SIZE_X/2);
    }

    if(playerPos.y < DISPLAY_MAP_SIZE_Y/2) {
        *sYParam = 0;
        *eYParam = DISPLAY_MAP_SIZE_Y;
    } else if (playerPos.y > MAP_SIZE_Y - (DISPLAY_MAP_SIZE_Y/2)) {
        *sYParam = MAP_SIZE_Y - DISPLAY_MAP_SIZE_Y - 1;
        *eYParam = MAP_SIZE_Y;
    } else {
        *sYParam = playerPos.y - (DISPLAY_MAP_SIZE_Y/2);
        *eYParam = playerPos.y + (DISPLAY_MAP_SIZE_Y/2);
    }
}

void displayGridCoords(int** grid, coordinate coords) {

    switch(grid[coords.y][coords.x]) {
        case TILE_WALL: isUnicode ? printf("\uE191") : putchar('#'); break;
        case TILE_FLOOR: putchar(' '); break;
        case -3 ... -2: isUnicode ? printf("\uE6DC") : putchar('S'); break;
        case 1: isUnicode ? printf("\uE0E8") : putchar('1'); break;
        case 2: isUnicode ? printf("\uE2E6") : putchar('2'); break;
        case 3:
        case 6:
        case 9: isUnicode ? printf("\uE86A") : putchar('P'); break;
        case 4:
        case 7:
        case 10: isUnicode ? printf("\uE52A") : putchar('R'); break;
        case 5:
        case 8:
        case 11: isUnicode ? printf("\uE9B5") : putchar('A'); break;
        case 12 ... 40: isUnicode ? printf("\uE85E") : putchar('M'); break;
        case 41 ... 69: isUnicode ? printf("\uE82B") : putchar('M'); break;
        case 70 ... 98: isUnicode ? printf("\uE8A7") : putchar('M'); break;
        case 99: isUnicode ? printf("\uE89A") : putchar('B'); break;
        default: printf("%d", grid[coords.y][coords.x]); break;
    }
}

void display(map* worldMap) {

    int sXParam, sYParam, eXParam, eYParam;

    getMapDisplayOffsetParams(worldMap->currentCoords, &sXParam, &sYParam, &eXParam, &eYParam);

    for (int dy = 0; dy < DISPLAY_SIZE_Y; ++dy) {
        for (int dx = 0; dx < DISPLAY_SIZE_X; ++dx) {
            if(dy < DISPLAY_MAP_SIZE_Y && dx < DISPLAY_MAP_SIZE_X) {

                displayGridCoords(worldMap->lvl[worldMap->currentLvl], (coordinate){ sXParam + dx, sYParam + dy });

            } else {
                printf(".");
            }
        }
        putchar('\n');
    }
}

void displayMap(map* worldMap) {
    display(worldMap);
}
