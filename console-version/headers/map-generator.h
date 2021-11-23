//
// Created by Loïc Vanden Bossche on 16/11/2021.
//

#ifndef MALLOC_WORLD_MAP_GENERATOR_H
#define MALLOC_WORLD_MAP_GENERATOR_H

#include "math.h"
#include "time.h"
#include "map.h"
#include "debugger.h"
#include "pathfind.h"

int cellularAutomata(int** grid);
void populateMap(int** grid);

#endif //MALLOC_WORLD_MAP_GENERATOR_H
