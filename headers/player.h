//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#ifndef MALLOC_WORLD_PLAYER_H
#define MALLOC_WORLD_PLAYER_H

#include "stdlib.h"
#include "stdio.h"

typedef struct Item {
    int id;
    int qty;
} item;

typedef struct Player {
    char name[20];
    int hp;
    int maxHp;
    int xp;
    int lvl;
    item inventory[10];

} player;

player* createPlayer();

void applyLvl(player *player, int lvl);

#endif //MALLOC_WORLD_PLAYER_H
