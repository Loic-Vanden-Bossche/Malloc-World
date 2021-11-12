//
// Created by Loïc Vanden Bossche on 19/10/2021.
//

#include "../headers/save.h"

const char* SAVE_FILE_LOCATION = "../saveFile.txt";

void parseSaveFile(){

    FILE *f;

    f = fopen("./saveFileTEST.txt","r");

    fclose(f);
}

void saveData(map* worldMap, player* player) {

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

    fclose(f);
}