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

int collectRessource(int ressourceId, int playerInventory[10], coordinate targetCoordinates, int** mapGrid) {

    debug("This element is a ressource !!");
}

void processContextAction(int contextAction,coordinate targetCoordinates,map* worldMap,player* player) {

    displayMap(worldMap);

    const mapElement* elem = getMapElementById(contextAction);

    if(elem != NULL) {

        debug("%s ,%d\n", elem->name, elem->value);

        switch (elem->type) {
            case WALL:
                debug("Destination is blocked\n");
                break;
            case FLOOR:
                debug("Player moved successfully\n");
                break;
            case RESSOURCE:
                collectRessource(elem->value, player->inventory, targetCoordinates, worldMap->lvl[worldMap->currentLvl]);
                break;
            default:
                debug("Action : %d\n", contextAction);
                break;
        }
    }
}

int game(map* worldMap, player* player, storageNode* storage) {

    char ch = 0;

    coordinate targetCoords;

    do
    {
        targetCoords = worldMap->currentCoords;

        switch (ch) {
            case 's':
                debug("Moving DOWN\n");
                targetCoords.y += 1;
                break;
            case 'z':
                debug("Moving UP\n");
                targetCoords.y -= 1;
                break;
            case 'd':
                debug("Moving RIGHT\n");
                targetCoords.x += 1;
                break;
            case 'q':
                debug("Moving LEFT\n");
                targetCoords.x -= 1;
                break;
            default:
                targetCoords.x = -1;
                targetCoords.y = -1;
                break;
        }

        processContextAction(setCurrentCoordinate(worldMap, targetCoords), targetCoords, worldMap, player);

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

