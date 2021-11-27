//
// Created by Loïc Vanden Bossche on 16/11/2021.
//

#include "../headers/map-generator.h"

// Cellular Automata

#define FILL_PROB 12

int randPick(void)
{
    if(rand()%100 < FILL_PROB)
        return TILE_WALL;
    else
        return TILE_FLOOR;
}

void initMap(int** grid, int** grid2)
{
    int xi, yi;

    for(yi=1; yi<MAP_SIZE_Y-1; yi++)
        for(xi=1; xi<MAP_SIZE_X-1; xi++)
            grid[yi][xi] = randPick();

    for(yi=0; yi<MAP_SIZE_Y; yi++)
        for(xi=0; xi<MAP_SIZE_X; xi++)
            grid2[yi][xi] = TILE_WALL;
}

void resetMap(int** grid) {
    for (int i = 0; i < MAP_SIZE_Y; ++i) {
        for (int j = 0; j < MAP_SIZE_X; ++j) {
            grid[i][j] = 0;
        }
    }
}

void generateMap(map* worldMap){

    pathFindResult res;

    float fillProb;

    for (int lvl = 0; lvl < 3; ++lvl) {

        debug("Generate lvl : %d\n", lvl);

        debug("\t- Generating skeleton\n");

        do {
            resetMap(worldMap->lvl[lvl]);
            cellularAutomata(worldMap->lvl[lvl]);

            res = solveAStar(worldMap->lvl[lvl], 1,1, MAP_SIZE_X - 2, MAP_SIZE_Y - 2);
            destroyPair(res.path);
        } while(res.solved != P_FOUND);

        int count = 0;

        debug("\t- Filling unreachable spaces\n");

        for (int i = 0; i < MAP_SIZE_Y; ++i) {
            for (int j = 0; j < MAP_SIZE_X; ++j) {
                if (worldMap->lvl[lvl][i][j] == 0) {
                    res = solveAStar(worldMap->lvl[lvl], 1, 1, j, i);
                    destroyPair(res.path);
                    if (res.solved != P_FOUND && res.solved != P_ALREADY_AT_DESTINATION) {
                        worldMap->lvl[lvl][i][j] = -1;
                        count++;
                    }
                } else {
                    count++;
                }
            }
        }

        fillProb = (count/(float)(MAP_SIZE_X*MAP_SIZE_Y));

        debug("\t- Fill prob : %f\n", fillProb);
        debug("\t- Populating lvl\n");
        populateMap(worldMap->lvl[lvl], lvl, fillProb);
        debug("`\n");

        setCurrentCoordinate(worldMap, (coordinate){ 1, 1 });
    }
}

void generation(int** grid, int** grid2, generation_params* params)
{
    int xi, yi, ii, jj;

    for(yi=1; yi<MAP_SIZE_Y-1; yi++)
        for(xi=1; xi<MAP_SIZE_X-1; xi++)
        {
            int adjcount_r1 = 0,
                    adjcount_r2 = 0;

            for(ii=-1; ii<=1; ii++)
                for(jj=-1; jj<=1; jj++)
                {
                    if(grid[yi+ii][xi+jj] != TILE_FLOOR)
                        adjcount_r1++;
                }
            for(ii=yi-2; ii<=yi+2; ii++)
                for(jj=xi-2; jj<=xi+2; jj++)
                {
                    if(abs(ii-yi)==2 && abs(jj-xi)==2)
                        continue;
                    if(ii<0 || jj<0 || ii>=MAP_SIZE_Y || jj>=MAP_SIZE_X)
                        continue;
                    if(grid[ii][jj] != TILE_FLOOR)
                        adjcount_r2++;
                }
            if(adjcount_r1 >= params->r1_cutoff || adjcount_r2 <= params->r2_cutoff)
                grid2[yi][xi] = TILE_WALL;
            else
                grid2[yi][xi] = TILE_FLOOR;
        }
    for(yi=1; yi<MAP_SIZE_Y-1; yi++)
        for(xi=1; xi<MAP_SIZE_X-1; xi++)
            grid[yi][xi] = grid2[yi][xi];
}

int cellularAutomata(int** grid)
{
    int ii, jj;

    int generations = 1;

    generation_params* params = (generation_params*)malloc( sizeof(generation_params) * generations );

    params->r1_cutoff  = 20;
    params->r2_cutoff  = 1;
    params->reps 	   = 20;

    int **grid2;

    int yi,xi;

    grid2 = (int**)malloc(sizeof(int*) * MAP_SIZE_Y);

    for(yi=0; yi<MAP_SIZE_Y; yi++)
    {
        grid2[yi] = (int*)malloc(sizeof(int) * MAP_SIZE_X);
    }

    initMap(grid, grid2);

    for(ii=0; ii<generations; ii++)
    {
        for(jj=0; jj<params->reps; jj++)
            generation(grid, grid2, params);
    }

    for(yi=0; yi<MAP_SIZE_Y; yi++)
        grid[yi][0] = grid[yi][MAP_SIZE_X-1] = TILE_WALL;
    for(xi=0; xi<MAP_SIZE_X; xi++)
        grid[0][xi] = grid[MAP_SIZE_Y-1][xi] = TILE_WALL;

    for(yi=0; yi<MAP_SIZE_Y; yi++)
    {
         free(grid2[yi]);
    }

    free(grid2);
    free(params);

    return 0;
}

int getRandomNumber(int lower, int upper) {

    return (rand() % (upper - lower + 1)) + lower;
}

coordinate getRandomCoordinate(){

    coordinate res = {0, 0};

    res.x = getRandomNumber(1, MAP_SIZE_X - 1);
    res.y = getRandomNumber(1, MAP_SIZE_Y - 1);

    return res;
}

void printCoordinate(coordinate coords){
    debug("(%d, %d)\n", coords.x, coords.y);
}

#define TOTAL_ELEMENTS_RT 0.2

typedef enum MapElementRessourceType {
    R_MINERAL,
    R_WOOD,
    R_PLANT,
    R_MONSTER
} mapElementType;

mapElementType getRandomMapElementType() {

    float weights[4] = { 0.45, 0.25, 0.2, 0.1 };
    int results[4] = { R_PLANT, R_MONSTER, R_WOOD, R_MINERAL };

    float x = (float)rand()/(float)(RAND_MAX/1);

    float num = x;
    float s = 0;
    int lastIndex = 4 - 1;

    for (int i = 0; i < lastIndex; ++i) {
        s += weights[i];
        if (num < s) {
            return results[i];
        }
    }

    return results[lastIndex];
}

int getRandomMonster(int lvl){

    switch (lvl) {
        case 0:
            return getRandomNumber(12, 40);
        case 1:
            return getRandomNumber(41, 69);
        case 2:
            return getRandomNumber(70, 98);
        default:
            return 12;
    }
}

int getElementFromType(mapElementType type, int lvl){

    int startId = 3 + (lvl*3);

    switch (type) {
        case R_PLANT:
            return startId;
        case R_MINERAL:
            return startId+1;
        case R_WOOD:
            return startId+2;
        case R_MONSTER:
            return getRandomMonster(lvl);
    }
}

void populateMap(int** grid, int lvl, float fillProb) {

    coordinate coords;
    pathFindResult pRes;
    int isBlocked;
    mapElementType type;
    const int totalElements = ((MAP_SIZE_X*MAP_SIZE_Y) * fillProb) * TOTAL_ELEMENTS_RT;
    int totalElementTypes[4] = {0};

    for (int i = 0; i < totalElements; ++i) {

        do {

            pRes.solved = P_NOT_FOUND;
            pRes.path = NULL;

            coords = getRandomCoordinate();
            isBlocked = grid[coords.y][coords.x] != 0;

            if(!isBlocked) {
                type = getRandomMapElementType();
                grid[coords.y][coords.x] = getElementFromType(type, lvl);
                pRes = solveAStar(grid, 1, 1, MAP_SIZE_X - 2, MAP_SIZE_Y - 2);
                destroyPair(pRes.path);

                if(pRes.solved != P_FOUND) {
                    grid[coords.y][coords.x] = 0;
                }
            }

        } while(isBlocked || pRes.solved != P_FOUND);

        switch (type) {
            case R_PLANT:
                totalElementTypes[0]++;
                break;
            case R_WOOD:
                totalElementTypes[1]++;
                break;
            case R_MINERAL:
                totalElementTypes[2]++;
                break;
            case R_MONSTER:
                totalElementTypes[3]++;
                break;
        }
    }

    debug("\t\t - Plant prob : %f\n", (float)totalElementTypes[0]/totalElements);
    debug("\t\t - Wood prob : %f\n", (float)totalElementTypes[1]/totalElements);
    debug("\t\t - Mineral prob : %f\n", (float)totalElementTypes[2]/totalElements);
    debug("\t\t - Monster prob : %f\n", (float)totalElementTypes[3]/totalElements);

    switch(lvl){
        case 0:
            grid[MAP_SIZE_Y - 2][MAP_SIZE_X - 2] = -2;
            break;
        case 1:
            grid[1][1] = -2;
            grid[MAP_SIZE_Y - 2][MAP_SIZE_X - 2] = -3;
            break;
        case 2:
            grid[1][1] = -3;
            grid[MAP_SIZE_Y - 2][MAP_SIZE_X - 2] = 99;
            break;
    }
}