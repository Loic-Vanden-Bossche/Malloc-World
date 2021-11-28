//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#ifndef MALLOC_WORLD_PLAYER_H
#define MALLOC_WORLD_PLAYER_H

#include "stdlib.h"
#include "stdio.h"
#include <math.h>
#include "item.h"
#include "craft.h"

typedef struct Player {
    int hp;
    int maxHp;
    int xp;
    int lvl;
    item inventory[10];
} player;

player* createPlayer();

void destroyPlayer();

void applyLvl(player *player, int lvl);

void applyHp(player *player, int hp);

void applyXp(player *player, int xp);

void displayPlayerInfos(player* player);

void displayPlayerInventory(item* inventory);

int addItem(int itemId, item playerInventory[10]);

int deleteItem(int itemId, item playerInventory[10]);

int calculateMaxHp(int lvl);

float getLvlProgression(int xp, int currentLvl);

int calculateXpForNextLvl(int lvl);

#endif //MALLOC_WORLD_PLAYER_H
