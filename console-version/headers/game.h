//
// Created by Loïc Vanden Bossche on 12/11/2021.
//

#ifndef MALLOC_WORLD_GAME_H
#define MALLOC_WORLD_GAME_H

#include "./save.h"
#include "./map.h"
#include "./player.h"
#include "storage.h"
#include "pathfind.h"
#include "display.h"

void display(map* worldMap, player* player, storageNode* storage);
int mainMenu();
int displayConfirm(char* message);
int newGame();
int continueGame();

#endif //MALLOC_WORLD_GAME_H
