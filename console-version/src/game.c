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

        switch(ch) {
            case '1' ... '3':
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

int getInput() {
    clean_stdin();
    return getchar();
}

item* getToolForRessource(enum RessourceType type, item playerInventory[10]) {

    for (int i = 0; i < 10; ++i) {
        const itemData* data = getItemData(playerInventory[i].id);

        if(data != NULL) {
            if(data->ressourceType == type && data->type == TOOL) {
                return &playerInventory[i];
            }
        }
    }

    return NULL;
}

int collectRessource(int ressourceId, item playerInventory[10], coordinate targetCoordinates, int** mapGrid) {

    const itemData* data = getItemDataByRessourceId(ressourceId);

    if(data != NULL) {
        debug("This ressource is : %s !!\n", data->name);
        item* tool = getToolForRessource(data->ressourceType, playerInventory);

        if(tool != NULL) {
            if(tool->durabitity > 0) {

                switch(addItem(data->id, playerInventory)) {
                    case 0:
                        addLog("%s recolte", data->name);
                        mapGrid[targetCoordinates.y][targetCoordinates.x] = 0;
                        tool->durabitity--;
                        break;
                    case -2:
                        addLog("Votre inventaire est plein");
                        break;
                }
                
            } else {
                addLog("votre outil est casse");
            }
        } else {
            addLog("il vous manque l'outil");
        }
    }
}

int interactMonster(int monsterId, player* player, coordinate targetCoordinates, int** mapGrid ) {
    debug("This element is a monster !!\n");
    debug("This element is a monster !!\n");

    fightMonster(monsterId - 12, player);
}


void processContextAction(int contextAction, coordinate targetCoordinates,map* worldMap,player* player) {

    const mapElement* elem = getMapElementById(contextAction);

    if(elem != NULL) {

        debug("%d\n", elem->value);

        switch (elem->type) {
            case WALL:
                addLog("La destination est bloque");
                break;
            case FLOOR:
                addLog("Deplacement reussi");
                break;
            case RESSOURCE:
                collectRessource(elem->value, player->inventory, targetCoordinates, worldMap->lvl[worldMap->currentLvl]);
                break;
            case MONSTER:
                interactMonster(elem->value, player, targetCoordinates, worldMap->lvl[worldMap->currentLvl]);
                break;
            default:
                debug("Action : %d\n", contextAction);
                break;
        }
    }

    display(worldMap, player);
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

        ch = getInput();

    } while (ch != 'a');

    saveData(worldMap, player, storage);

    return 0;
}

int newGame() {

    map *worldMap = createMap(0);
    player* player = createPlayer();
    storageNode* storage = NULL;

    generateMonsters();

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

    generateMonsters();

    if(!parseSaveFile(worldMap, player, &storage)){
        waitKey("Error occurred while getting saved data");
    }

    game(worldMap, player, storage);

    destroyMap(worldMap);
    destroyStorage(storage);
    destroyPlayer(player);

    return 0;
}

