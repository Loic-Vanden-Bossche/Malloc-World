//
// Created by Loïc Vanden Bossche on 19/10/2021.
//

#ifndef MALLOC_WORLD_SAVE_H
#define MALLOC_WORLD_SAVE_H

#include "map.h"
#include "player.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

int parseSaveFile(map* worldMap, player* player, storageNode** storage);
int checkSaveFile();
void saveData(map* worldMap, player* player, storageNode* storage);

#endif //MALLOC_WORLD_SAVE_H
