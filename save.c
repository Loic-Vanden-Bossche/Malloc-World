//
// Created by Loïc Vanden Bossche on 19/10/2021.
//

#include "stdio.h"
#include "save.h"

void parseSaveFile(){

    FILE *f;

    f = fopen("./saveFileTEST.txt","r");



    fclose(f);
}