//
// Created by Loïc Vanden Bossche on 12/11/2021.
//

#include "../headers/game.h"

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

int npcMenu() {

    clrscr();

    printf("=== menu PNJ ===\n");

    printf("1 - Reparer materiel\n");
    printf("2 - Liste des crafts\n");
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

void interactMonster(int monsterId, player* player, coordinate targetCoordinates, int** mapGrid ) {
    debug("This element is a monster !!\n");

    switch(fightMonster(monsterId - 12, player)){
        case 0:
            addLog("Vous etes mort");
            break;
        case 1:
            addLog("Vous avez battu le monstre");
            mapGrid[targetCoordinates.y][targetCoordinates.x] = 0;
            addLog("Vous avez gagner %d xp", monsterId);
            applyXp(player, monsterId);
            break;
        case -1:
            addLog("Vous navez pas d'armes");
            break;
        case -2:
            addLog("Vous fuyez");
            break;
    }
}

void interactPortal(map* worldMap, player* player, int portalValue) {

    switch (worldMap->currentLvl) {
        case 0:
            if(player->lvl >= 3) {
                setCurrentLvl(worldMap, 1, 1);
            } else {
                addLog("Le niveau 2 te sera accessible au niv 3");
            }
            break;
        case 1:
            if(portalValue == -2) {
                setCurrentLvl(worldMap, 0, 0);
            } else if (portalValue == -3) {

                if(player->lvl >= 7) {
                    setCurrentLvl(worldMap, 2, 1);
                } else {
                    addLog("Le niveau 3 te sera accessible au niv 7");
                }
            }
            break;

        case 2:
            setCurrentLvl(worldMap, 1, 0);
            break;
    }
}

void interactNPC(player* player, int currentLvl) {

    int menuRes = npcMenu();

    if(menuRes == 1) {
        addLog("%d items repare", repairItems(player->inventory));
    } else if (menuRes == 2) {
        const craft* craftData = getCraftDataById(selectCraftMenu(player->inventory, currentLvl + 1));

        if(craftData != NULL) {
            const itemData* itemTarget = getItemData(craftData->targetItemId);

            addLog("Vous avez crafter 1 %s", itemTarget->name);
        }
    }
}

void processContextAction(int contextAction, coordinate targetCoordinates,map* worldMap,player* player) {

    const mapElement* elem = getMapElementById(contextAction);

    if(elem != NULL) {
        switch (elem->type) {
            case WALL:
                addLog("La destination est bloque");
                break;
            case RESSOURCE:
                collectRessource(elem->value, player->inventory, targetCoordinates, worldMap->lvl[worldMap->currentLvl]);
                break;
            case MONSTER:
                interactMonster(elem->value, player, targetCoordinates, worldMap->lvl[worldMap->currentLvl]);
                break;
            case PORTAL:
                interactPortal(worldMap, player, elem->value);
                break;
            case NPC:
                interactNPC(player, worldMap->currentLvl);
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

