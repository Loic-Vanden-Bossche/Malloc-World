//
// Created by Loïc Vanden Bossche on 12/11/2021.
//

#include "../headers/game.h"

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

#include <stdio.h>
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int game(map* worldMap, player* player, storageNode* storage) {

    char ch = 0;

    int contextAction;

    do
    {
        contextAction = -10;

        switch (ch) {
            case 's':
                debug("Moving DOWN\n");
                contextAction = setCurrentCoordinate(worldMap, worldMap->currentCoords.x, worldMap->currentCoords.y+1);
                break;
            case 'z':
                debug("Moving UP\n");
                contextAction = setCurrentCoordinate(worldMap, worldMap->currentCoords.x, worldMap->currentCoords.y-1);
                break;
            case 'd':
                debug("Moving RIGHT\n");
                contextAction = setCurrentCoordinate(worldMap, worldMap->currentCoords.x+1, worldMap->currentCoords.y);
                break;
            case 'q':
                debug("Moving LEFT\n");
                contextAction = setCurrentCoordinate(worldMap, worldMap->currentCoords.x-1, worldMap->currentCoords.y);
                break;
        }

        displayMap(worldMap);

        switch (contextAction) {
            case -1:
                debug("Destination is blocked or invalid\n");
                break;
            case 0:
                debug("Player moved successfully\n");
                break;
            default:
                debug("Action : %d\n", contextAction);
                break;
        }

        clean_stdin();
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

