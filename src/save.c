//
// Created by Loïc Vanden Bossche on 19/10/2021.
//

#include "../headers/save.h"

// ==== Utils save functions ==== //

int checkItem(item *toCheck){

    const itemData* data = getItemData(toCheck->id);

    if(data == NULL)
        return 0;

    if(data->type == ARMOR || data->type == TOOL || data->type == WEAPON) {
        if (toCheck->qty != 1) return 0;
        if (toCheck->durabitity < 0 || toCheck->durabitity > 100) return 0;
    } else if (data->type == HEAL){
        if (toCheck->qty != 1) return 0;
        toCheck->durabitity = 0;
    } else {
        toCheck->durabitity = 0;
    }

    return 1;
}

// ==== Map save functions ==== //

void parseMapData(FILE * f, map* worldMap){

    char* buffer = malloc(BUFFER_LENGTH);

    // Skip main title line
    fgets(buffer, BUFFER_LENGTH, f);

    for (int lvl = 0; lvl < 3; ++lvl) {

        // Skip title line
        fgets(buffer, BUFFER_LENGTH, f);

        // Getting map infos for lvl
        for (int i = 0; i < MAP_SIZE_Y; ++i) {
            fgets(buffer, BUFFER_LENGTH, f);

            char* strToken = strtok(buffer, " ");

            int tokCount = 0;

            while (strToken != NULL) {

                if(atoi(strToken) == 1) {
                    setCurrentCoordinate(worldMap, (coordinate){ tokCount, i });
                } else {
                    worldMap->lvl[lvl][i][tokCount] = atoi(strToken);
                }

                tokCount++;

                if(tokCount >= MAP_SIZE_X) break;

                strToken = strtok(NULL, " ");
            }
        }
    }

    free(buffer);
}

// ==== Player save functions ==== //

int checkPlayerData(player *playerData){

    const int maxHp = calculateMaxHp(playerData->lvl);

    if(playerData->lvl < 1 || playerData->lvl > 10)
        return 0;

    if(playerData->maxHp != maxHp)
        playerData->maxHp = maxHp;

    if(playerData->hp > playerData->maxHp && playerData->hp < 0)
        return 0;

    for (int i = 0; i < 10; ++i) {
        if(playerData->inventory[i].id != 0)
            if(!checkItem(&playerData->inventory[i]))
                return 0;
    }

    return 1;
}

int parsePlayerData(FILE * f, player* player) {

    char* buffer = malloc(BUFFER_LENGTH);

    // Skip main title line
    fgets(buffer, BUFFER_LENGTH, f);
    fgets(buffer, BUFFER_LENGTH, f);

    // Getting player lvl
    fgets(buffer, BUFFER_LENGTH, f);
    sscanf(buffer,"{%d}", &player->lvl);

    // Getting player HPs
    fgets(buffer, BUFFER_LENGTH, f);
    sscanf(buffer,"{%d/%d}", &player->hp, &player->maxHp);

    // Getting player XPs
    fgets(buffer, BUFFER_LENGTH, f);
    sscanf(buffer,"{%d/}", &player->xp);

    // Getting player inventory
    // Skip title line
    fgets(buffer, BUFFER_LENGTH, f);
    for (int i = 0; i < 10; ++i) {
        fgets(buffer, BUFFER_LENGTH, f);
        sscanf(buffer, "{%d}@{%d}@{%d}",
               &player->inventory[i].qty,
               &player->inventory[i].id,
               &player->inventory[i].durabitity
               );
    }

    free(buffer);

    return checkPlayerData(player);
}

// ==== Storage save functions ==== //

int checkStorageData(storageNode *storage) {

    while (storage != NULL) {
        if(!checkItem(&storage->item)) return 0;
        storage = storage->next;
    }

    return 1;
}


int parseStorageData(FILE *f, storageNode** storage) {

    char* buffer = malloc(BUFFER_LENGTH);

    // Skip title line
    fgets(buffer, BUFFER_LENGTH, f);

    // Getting items in storage
    while(fgets(buffer, BUFFER_LENGTH, f)) {

        item newItem;
        sscanf(buffer, "{%d}@{%d}@{%d}",
               &newItem.qty,
               &newItem.id,
               &newItem.durabitity
        );

        appendToStorage(storage, newItem);
    }

    free(buffer);

    return checkStorageData(*storage);
}

// ==== Main save functions ==== //

int checkSaveFile(){

    FILE *file;
    file = fopen(SAVE_FILE_LOCATION, "r");

    if (file != NULL) return 1;

    return 0;
}

int parseSaveFile(map* worldMap, player* player, storageNode** storage){

    FILE *f;

    f = fopen(SAVE_FILE_LOCATION,"r");

    parseMapData(f, worldMap);
    debug("Map data parsed\n");

    if(parsePlayerData(f, player)) {
        debug("Player data successfully parsed\n");
    } else {
        debug("Error occurred while parsing player data\n");
        return 0;
    }

    if(parseStorageData(f, storage)) {
        debug("Storage data successfully parsed\n");
    } else {
        debug("Error occurred while parsing storage data\n");
        return 0;
    }

    fclose(f);

    return 1;
}

void saveData(map* worldMap, player* player, storageNode* storage) {

    FILE *f;

    f = fopen(SAVE_FILE_LOCATION,"w");

    fprintf(f,"=== MAP ===");

    for (int lvl = 0; lvl < 3; ++lvl) {
        fprintf(f,"\n-- ZONE %d --", lvl + 1);

        for (int i = 0; i < MAP_SIZE_Y; ++i) {
            fprintf(f,"\n");
            for (int j = 0; j < MAP_SIZE_X; ++j) {
                fprintf(f,"%d ", worldMap->lvl[lvl][i][j]);
            }
        }
    }

    fprintf(f,"\n\n=== PLAYER ===\n");
    fprintf(f,"{%d}\n", player->lvl);
    fprintf(f,"{%d/%d}\n", player->hp , player->maxHp);
    fprintf(f,"{%d/%d}\n", player->xp, 100);

    fprintf(f,"-- INVENTORY --\n");

    for (int i = 0; i < 10; ++i) {

        const item item = player->inventory[i];

        fprintf(f,"{%d}@{%d}@{%d}\n", item.qty, item.id, item.durabitity);
    }

    fprintf(f,"-- STORAGE --\n");

    while (storage != NULL) {
        fprintf(f, "{%d}@{%d}@{%d}\n", storage->item.qty, storage->item.id, storage->item.durabitity);
        storage = storage->next;
    }

    fclose(f);
}