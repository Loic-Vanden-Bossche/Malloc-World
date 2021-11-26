//
// Created by Loïc Vanden Bossche on 24/11/2021.
//

#include "../headers/display.h"

int isUnicode = 0;

void setUnicode() {
    isUnicode = 1;
}

void displayGrid(int** grid) {

    int xi, yi;
    for(yi=0; yi<MAP_SIZE_Y; yi++)
    {
        for(xi=0; xi<MAP_SIZE_X; xi++)
        {
            switch(grid[yi][xi]) {
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
                default: printf("%d", grid[yi][xi]); break;
            }
        }
        putchar('\n');
    }
}

void displayMap(map* worldMap) {

    displayGrid(worldMap->lvl[worldMap->currentLvl]);
}