//
// Created by Loïc Vanden Bossche on 12/11/2021.
//

#include "../headers/game.h"

void display(map* worldMap, player* player, storageNode* storage) {

    clrscr();

    for (int i = 0; i < 3; ++i)
        displayMap(worldMap->lvl[i]);

    displayPlayerInfos(player);
    printStorage(storage);
}

int mainMenu() {

    clrscr();

    printf("1 - Continuer\n");
    printf("2 - Nouvelle partie\n");
    printf("3 - Quitter\n");

    char ch;

    while(1) {

        fflush(stdin);
        ch = getchar();

        if(ch == '1' || ch == '2' || ch == '3'){

            return ch - '0';
        }
    }
}

void waitKey(char* message){

    clrscr();

    printf("%s, press any key to continue\n",message);

    fflush(stdin);
    getchar();
}

int displayConfirm(char* message) {

    clrscr();
    printf("%s Oui (o) Non (n)\n",message);

    char ch = 0;

    while(1) {

        fflush(stdin);
        ch = getchar();

        if (ch == 'o') return 1;
        else if (ch == 'n') return 0;
    }
}

void resetMap(int** grid) {
    for (int i = 0; i < MAP_SIZE_Y; ++i) {
        for (int j = 0; j < MAP_SIZE_X; ++j) {
            grid[i][j] = 0;
        }
    }
}

void generateMap(map* worldMap){

    pathFindResult res;

    float fillProb = 0.0;

    for (int lvl = 0; lvl < 3; ++lvl) {

        debug("Generate lvl : %d\n", lvl);

        debug("\t- Generating skeleton\n");

        do {
            resetMap(worldMap->lvl[lvl]);
            cellularAutomata(worldMap->lvl[lvl]);

            res = solveAStar(worldMap->lvl[lvl], 1,1, MAP_SIZE_X - 2, MAP_SIZE_Y - 2);
            destroyPair(res.path);
        } while(res.solved != P_FOUND);

        int count = 0;

        debug("\t- Filling unreachable spaces\n");

        for (int i = 0; i < MAP_SIZE_Y; ++i) {
            for (int j = 0; j < MAP_SIZE_X; ++j) {
                if (worldMap->lvl[lvl][i][j] == 0) {
                    res = solveAStar(worldMap->lvl[lvl], 1, 1, j, i);
                    destroyPair(res.path);
                    if (res.solved != P_FOUND && res.solved != P_ALREADY_AT_DESTINATION) {
                        worldMap->lvl[lvl][i][j] = -1;
                        count++;
                    }
                } else {
                    count++;
                }
            }
        }

        fillProb = (count/(float)(MAP_SIZE_X*MAP_SIZE_Y));

        debug("\t- Fill prob : %f\n", fillProb);
        debug("\t- Populating lvl\n");
        populateMap(worldMap->lvl[lvl], lvl, fillProb);
        debug("`\n");
    }
}

int game(map* worldMap, player* player, storageNode* storage) {

    char ch = 0;

    do
    {
        displayMap(worldMap->lvl[worldMap->currentLvl]);

        switch (ch) {
            case 's':
                printf("DOWN");
                break;
            case 'z':
                printf("UP");
                break;
            case 'd':
                printf("RIGHT");
                break;
            case 'q':
                printf("LEFT");
                break;
        }

        scanf(" %c", &ch);

    } while (ch != 'a');

    saveData(worldMap, player, storage);

    return 0;
}

int newGame() {

    map *worldMap = createMap(0);
    player* player = createPlayer();
    storageNode* storage = NULL;

    generateMap(worldMap);

    game(worldMap, player, storage);

    destroyMap(worldMap);
    destroyStorage(storage);
    destroyPlayer(player);

    return 0;
}

int continueGame() {

    if(!checkSaveFile()){
        return 0;
    }

    map *worldMap = createMap(0);
    player* player = createPlayer();
    storageNode* storage = NULL;

    if(!parseSaveFile(worldMap, player, &storage)){
        waitKey("Error occurred while getting saved data");
    }

    game(worldMap, player, storage);

    destroyMap(worldMap);
    destroyStorage(storage);
    destroyPlayer(player);

    return 0;
}

