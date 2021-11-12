//
// Created by Loïc Vanden Bossche on 19/10/2021.
//

#include "../headers/save.h"

const char* SAVE_FILE_LOCATION = "../saveFile.txt";

const int BUFFER_LENGTH = 255;

void parseMapData(FILE * f, map* worldMap){

    char* buffer = malloc(BUFFER_LENGTH);

    // Skip main title line
    fgets(buffer, BUFFER_LENGTH, f);

    for (int lvl = 0; lvl < 3; ++lvl) {

        // Skip title line
        fgets(buffer, BUFFER_LENGTH, f);

        // Getting map infos for lvl
        for (int i = 0; i < worldMap->mapSize; ++i) {
            fgets(buffer, BUFFER_LENGTH, f);

            char* strToken = strtok (buffer, " ");

            int tokCount = 0;

            while (strToken != NULL) {
                worldMap->lvl[lvl][i][tokCount] = atoi(strToken);

                tokCount++;

                if(tokCount > worldMap->mapSize) break;

                strToken = strtok(NULL, " ");
            }
        }
    }

    free(buffer);
}

void parsePlayerData(FILE * f, player* player) {

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
}

void parseStorageData(FILE *f, storageNode** storage) {

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
}

void parseSaveFile(map* worldMap, player* player, storageNode** storage){

    FILE *f;

    f = fopen(SAVE_FILE_LOCATION,"r");

    parseMapData(f, worldMap);

    parsePlayerData(f, player);

    parseStorageData(f, storage);

    fclose(f);
}

void saveData(map* worldMap, player* player, storageNode* storage) {

    FILE *f;

    f = fopen(SAVE_FILE_LOCATION,"w");

    fprintf(f,"=== MAP ===");

    for (int lvl = 0; lvl < 3; ++lvl) {
        fprintf(f,"\n-- ZONE %d --", lvl + 1);

        for (int i = 0; i < worldMap->mapSize; ++i) {
            fprintf(f,"\n");
            for (int j = 0; j < worldMap->mapSize; ++j) {
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