//
// Created by Loïc Vanden Bossche on 16/11/2021.
//

#include "../headers/map-generator.h"

// Cellular Automata

typedef struct {
    int r1_cutoff, r2_cutoff;
    int reps;
} generation_params;

int fillprob = 12;
int r1_cutoff = 5, r2_cutoff = 2;
generation_params *params;

generation_params *params_set;
int generations;

int randpick(void)
{
    if(rand()%100 < fillprob)
        return TILE_WALL;
    else
        return TILE_FLOOR;
}

void initmap(int** grid, int** grid2)
{
    int xi, yi;

    for(yi=1; yi<MAP_SIZE_Y-1; yi++)
        for(xi=1; xi<MAP_SIZE_X-1; xi++)
            grid[yi][xi] = randpick();

    for(yi=0; yi<MAP_SIZE_Y; yi++)
        for(xi=0; xi<MAP_SIZE_X; xi++)
            grid2[yi][xi] = TILE_WALL;
}

void generation(int** grid, int** grid2)
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

    generations = 1;

    params = params_set = (generation_params*)malloc( sizeof(generation_params) * generations );

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

    initmap(grid, grid2);

    for(ii=0; ii<generations; ii++)
    {
        params = &params_set[ii];
        for(jj=0; jj<params->reps; jj++)
            generation(grid, grid2);
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

    return 0;
}

typedef struct Coordinate {
    int x;
    int y;
} coordinate;

coordinate getRandomCoordinate(){

    coordinate res = {0, 0};

    res.x = (rand() % (MAP_SIZE_X - 2)) + 1;
    res.y = (rand() % (MAP_SIZE_Y - 2)) + 1;

    return res;
}

void printCoordinate(coordinate coords){
    debug("(%d, %d)\n", coords.x, coords.y);
}

#define TOTAL_RESOURCE_RT 0.07

void populateMap(int** grid) {

    coordinate coords;

    pathFindResult pRes;

    int isBlocked;

    const int totalResources = (MAP_SIZE_X*MAP_SIZE_Y) * TOTAL_RESOURCE_RT;

    for (int i = 0; i < totalResources; ++i) {

        do {

            pRes.solved = 0;
            pRes.path = NULL;

            coords = getRandomCoordinate();
            isBlocked = grid[coords.y][coords.x] != 0;

            if(!isBlocked) {
                grid[coords.y][coords.x] = 2;
                pRes = solveAStar(grid, 1, 1, 148, 38);
                destroyPair(pRes.path);

                if(pRes.solved != 1) {
                    grid[coords.y][coords.x] = 0;
                }
            }

        } while(isBlocked || pRes.solved != 1);
    }
}