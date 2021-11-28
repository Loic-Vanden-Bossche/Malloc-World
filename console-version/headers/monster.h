//
// Created by Loïc Vanden Bossche on 28/11/2021.
//

#ifndef MALLOC_WORLD_MONSTER_H
#define MALLOC_WORLD_MONSTER_H

#include "./map-generator.h"

typedef struct Monster {
    int id;
    char* name;
    int hp;
    int damages;
    int maxHp;
} monster;

#endif //MALLOC_WORLD_MONSTER_H
