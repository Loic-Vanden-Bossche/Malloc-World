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

void generateMap(map* worldMap){

    for (int i = 0; i < 3; ++i)
        cellularAutomata(worldMap->lvl[i]);
}



int game(map* worldMap, player* player, storageNode* storage) {

    char ch = 0;

    do
    {
        display(worldMap, player, storage);

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

        fflush(stdin);
        ch = getchar();

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

    map *worldMap = createMap(0);
    player* player = createPlayer();
    storageNode* storage = NULL;

    parseSaveFile(worldMap, player, &storage);

    game(worldMap, player, storage);

    destroyMap(worldMap);
    destroyStorage(storage);
    destroyPlayer(player);

    return 0;
}

