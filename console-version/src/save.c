//
// Created by Loïc Vanden Bossche on 19/10/2021.
//

#include "../headers/save.h"

const char* SAVE_FILE_LOCATION = "../saveFile.txt";

const int BUFFER_LENGTH = 512;

// ==== Utils save functions ==== //

int calculateMaxHp(int lvl){

    int maxHp = 100;

    for (int i = 1; i <= 10; ++i) {

        if(lvl == i) return maxHp;

        if(i >= 6 && i < 8) maxHp += 50;
        else if(i == 8 || i == 9) maxHp += 75;
        else maxHp += (10*i);
    }

    return 0;
}

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
        for (int i = 0; i < worldMap->mapSizeY; ++i) {
            fgets(buffer, BUFFER_LENGTH, f);

            char* strToken = strtok (buffer, " ");

            int tokCount = 0;

            while (strToken != NULL) {
                worldMap->lvl[lvl][i][tokCount] = atoi(strToken);

                tokCount++;

                if(tokCount > worldMap->mapSizeX) break;

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

        printf("%d", newItem.id);

        appendToStorage(storage, newItem);
    }

    free(buffer);

    return checkStorageData(*storage);
}

// ==== Main save functions ==== //

int parseSaveFile(map* worldMap, player* player, storageNode** storage){

    FILE *f;

    f = fopen(SAVE_FILE_LOCATION,"r");

    parseMapData(f, worldMap);

    if(parsePlayerData(f, player)) {
        printf("Player data successfully parsed\n");
    } else {
        printf("Error occurred while parsing player data\n");
        return 0;
    }

    if(parseStorageData(f, storage)) {
        printf("Storage data successfully parsed\n");
    } else {
        printf("Error occurred while parsing storage data\n");
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

        for (int i = 0; i < worldMap->mapSizeY; ++i) {
            fprintf(f,"\n");
            for (int j = 0; j < worldMap->mapSizeX; ++j) {
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