//
// Created by Loïc Vanden Bossche on 24/11/2021.
//

#include "../headers/display.h"

#define DISPLAY_SIZE_X 150
#define DISPLAY_SIZE_Y 40

#define GRID1_X 100
#define GRID1_Y 30

#define GRID2_X 100
#define GRID2_Y 10

#define GRID3_X 50
#define GRID3_Y 30

#define GRID4_X 50
#define GRID4_Y 10

int isUnicode = 0;

void setUnicode() {
    isUnicode = 1;
}

logNode *logs = NULL;

void getBlankLog(char log[50]) {

    for (int i = 0; i < 50; ++i) {
        log[i] = ' ';
    }
}

void logPushFront(char message[50]) {

    logNode* new_node = (logNode*) malloc(sizeof(logNode));

    char fMessage[50] = {' '};

    sprintf(fMessage, "- %s", message);

    getBlankLog(new_node->log);

    strcpy(new_node->log, fMessage);

    new_node->next = (*&logs);

    (*&logs) = new_node;
}

char* getLogAtIndex(int index) {

    logNode* current = logs;

    int i = 0;
    while (current != NULL) {
        if(i == index) return current->log;
        i++;
        current = current->next;
    }

    return NULL;
}

void getMapDisplayOffsetParams(coordinate playerPos, int* sXParam, int* sYParam) {

    if(playerPos.x < GRID1_X/2) {
        *sXParam = 0;
    } else if (playerPos.x > MAP_SIZE_X - (GRID1_X/2)) {
        *sXParam = MAP_SIZE_X - GRID1_X - 1;
    } else {
        *sXParam = playerPos.x - (GRID1_X/2);
    }

    if(playerPos.y < GRID1_Y/2) {
        *sYParam = 0;
    } else if (playerPos.y > MAP_SIZE_Y - (GRID1_Y/2)) {
        *sYParam = MAP_SIZE_Y - GRID1_Y - 1;
    } else {
        *sYParam = playerPos.y - (GRID1_Y/2);
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

void displayMap(map* worldMap, int dx, int dy) {
    int sXParam, sYParam;

    getMapDisplayOffsetParams(worldMap->currentCoords, &sXParam, &sYParam);
    displayGridCoords(worldMap->lvl[worldMap->currentLvl], (coordinate){ sXParam + dx, sYParam + dy });
}

void drawBars(char playerDisplay[GRID2_Y][GRID2_X], player* player,int x,int y) {

    int barIndex = 1;

    //Draw frames

    if(((x < 49 && x >= 0) && (y == barIndex || y == (barIndex + 2))) || (y == (barIndex + 1) && (x == 0 || x == 48)) ) {
        playerDisplay[y][x] = '#';
    }

    if(((x <= 99 && x >= 50) && (y == barIndex || y == (barIndex + 2))) || (y == (barIndex + 1) && (x == 50 || x == 99)) ) {
        playerDisplay[y][x] = '#';
    }

    //Fill with values

    float mult = (float)player->hp/player->maxHp;

    if(y == (barIndex + 1) && (x < 48 && x >= 1) && ((x - 1) <= mult*(48 - 1))) {
        playerDisplay[y][x] = ',';
    }

    mult = getLvlProgression(player->xp, player->lvl);

    if(y == (barIndex + 1) && (x < 99 && x >= 51) && ((x - 51) <= mult*(99 - 51))) {
        playerDisplay[y][x] = ',';
    }
}

void displayPlayer(player* player, int dx, int dy) {

    char playerDisplay[GRID2_Y][GRID2_X];

    for (int i = 0; i < GRID2_Y; ++i) {
        for (int j = 0; j < GRID2_X; ++j) {
            playerDisplay[i][j] = ' ';

            drawBars(playerDisplay, player, j, i);
        }
    }

    sprintf(playerDisplay[5], "| NIVEAU %d | VIE : %d/%d | XP : %d/%d |", player->lvl, player->hp, player->maxHp, player->xp,
            calculateXpForNextLvl(player->lvl));

    char toPrint = playerDisplay[dy - GRID1_Y][dx];

    toPrint != '\0' ? putchar(toPrint) : putchar(' ');
}

void displayInventory(item inventory[10], int dx, int dy) {
    char inventoryDisplay[GRID3_Y][GRID3_X];

    for (int i = 0; i < GRID3_Y; ++i) {
        for (int j = 0; j < GRID3_X; ++j) {
            inventoryDisplay[i][j] = ' ';
        }
    }

    int displayedLines = 0;

    for (int i = 0; i < 10; ++i) {
        const itemData* item =  getItemData(inventory[i].id);
        if(item != NULL && displayedLines != GRID3_Y) {
            sprintf(inventoryDisplay[displayedLines++], " %d - %s", i + 1, item->name);
            switch (item->type) {
                case WEAPON:
                    sprintf(inventoryDisplay[displayedLines++], "     - Degats : %d", item->damages);
                    sprintf(inventoryDisplay[displayedLines++], "     - Durabilite : %d", inventory[i].durabitity);
                    break;
                case CRAFTING:
                    sprintf(inventoryDisplay[displayedLines++], "     - Quantite : %d", inventory[i].qty);
                    break;
                case TOOL:
                    sprintf(inventoryDisplay[displayedLines++], "     - Durabilite : %d", inventory[i].durabitity);
                    break;
                case ARMOR:
                    sprintf(inventoryDisplay[displayedLines++], "     - Taux de protection : %f", item->pRate);
                    break;
                case HEAL:
                    sprintf(inventoryDisplay[displayedLines++], "     - Points de vie restaurés : %d", item->healValue);
                    break;
            }

            displayedLines++;
        }
    }

    char toPrint = inventoryDisplay[dy - 1][dx - GRID1_X - 2];

    toPrint != '\0' ? putchar(toPrint) : putchar(' ');
}

void displayLogs(int dx, int dy) {

    char toPrint;

    for (int i = 0; i < 4; ++i) {
        if(dy == DISPLAY_SIZE_Y - 2*(i+1)) {
            if(getLogAtIndex(i) != NULL) {
                toPrint = getLogAtIndex(i)[dx - GRID1_X - 2];
                if (toPrint != '\0') {
                    putchar(toPrint);
                    return;
                }
            }
        }
    }

    putchar(' ');
}

void display(map* worldMap, player* player) {

    for (int dy = 0; dy < DISPLAY_SIZE_Y; ++dy) {
        for (int dx = 0; dx < DISPLAY_SIZE_X; ++dx) {
            if(dy <= GRID1_Y && dx <= GRID1_X && dy != 0 && dx != 0) {

                displayMap(worldMap, dx - 1, dy - 1);

            } else if(dy > GRID1_Y && dx <= GRID2_X && dx != 0 && dy != DISPLAY_SIZE_Y - 1 && dy != GRID1_Y + 1) {
                displayPlayer(player, dx - 1, dy - 1);
            } else if(dy > 0 && dy <= GRID3_Y && dx > GRID1_X && dx != DISPLAY_SIZE_X - 1 && dx != GRID1_X + 1) {
                displayInventory(player->inventory, dx, dy);
            } else if (dx > GRID1_X + 1 && dy > GRID3_Y + 1 && dy != DISPLAY_SIZE_Y - 1 && dx != DISPLAY_SIZE_X - 1) {
                displayLogs(dx, dy);
            } else {
                putchar('x');
            }
        }
        putchar('\n');
    }
}

