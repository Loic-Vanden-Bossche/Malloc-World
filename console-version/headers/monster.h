//
// Created by Loïc Vanden Bossche on 28/11/2021.
//

#ifndef MALLOC_WORLD_MONSTER_H
#define MALLOC_WORLD_MONSTER_H

#include "./map-generator.h"

typedef struct Monster {
    int id;
    char* name;
    int lvl;
    int maxHp;
    int damages;
} monster;

void generateMonsters();

void displayMonsters();

#endif //MALLOC_WORLD_MONSTER_H
