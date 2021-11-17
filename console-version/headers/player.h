//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#ifndef MALLOC_WORLD_PLAYER_H
#define MALLOC_WORLD_PLAYER_H

#include "stdlib.h"
#include "stdio.h"
#include "item.h"

typedef struct Player {
    char name[20];
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

#endif //MALLOC_WORLD_PLAYER_H
