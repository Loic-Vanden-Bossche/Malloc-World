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

void saveData(map worldMap) {

    FILE *f;

    f = fopen(SAVE_FILE_LOCATION,"w");

    fprintf(f,"=== MAP ===");

    for (int lvl = 0; lvl < 3; ++lvl) {
        fprintf(f,"\n-- ZONE %d --", lvl + 1);

        for (int i = 0; i < worldMap.mapSize; ++i) {
            fprintf(f,"\n");
            for (int j = 0; j < worldMap.mapSize; ++j) {
                fprintf(f,"%d ", worldMap.lvl[lvl][i][j]);
            }
        }
    }

    fprintf(f,"\n\n=== PLAYER ===");

    fclose(f);
}