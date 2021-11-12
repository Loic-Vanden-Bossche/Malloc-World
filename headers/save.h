//
// Created by Loïc Vanden Bossche on 19/10/2021.
//

#ifndef MALLOC_WORLD_SAVE_H
#define MALLOC_WORLD_SAVE_H

#include "map.h"
#include "player.h"
#include "stdio.h"

void parseSaveFile();

void saveData(map* worldMap, player* player);

#endif //MALLOC_WORLD_SAVE_H
