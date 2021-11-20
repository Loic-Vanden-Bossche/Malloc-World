//
// Created by Loïc Vanden Bossche on 20/11/2021.
//

#ifndef MALLOC_WORLD_PATHFIND_H
#define MALLOC_WORLD_PATHFIND_H

#include "map.h"
#include <string.h>
#include <math.h>

#define ROW 9
#define COL 10

#define INCLUDE_DIAGS 0

#define FLT_MAX 99999999.0

typedef struct Pair {
    int first;
    int second;
} Pair;

typedef struct pPair {
    double first;
    Pair second;
} pPair;

typedef struct cell {
    int parent_i, parent_j;
    double f, g, h;
} cell;

typedef struct PpairListNode {

    pPair value;
    struct PpairListNode* next;
} pPairListNode;

typedef struct PairListNode {

    Pair value;
    struct PairListNode* next;
} pairListNode;

typedef struct PathFindResult {

    pairListNode* path;
    int solved;

} pathFindResult;

void insertPPair(pPairListNode** headRef, pPair value);
void insertPair(pairListNode** headRef, Pair value);

pPairListNode* removePPairFirstNode(pPairListNode* head);

pairListNode* removePairLastNode(pairListNode* head);

pairListNode* getPairLastNode(pairListNode* list);

Pair make_pair(int first, int second);

pPair make_pair_p(int first, Pair second);

int isValid(int row, int col);

int isUnBlocked(int grid[][MAP_SIZE_X], int row, int col);

int isDestination(int row, int col, Pair dest);

double calculateHValue(int row, int col, Pair dest);

pairListNode* tracePath(cell cellDetails[][MAP_SIZE_X], Pair dest);

pathFindResult aStarSearch(int grid[][MAP_SIZE_X], Pair src, Pair dest);

pathFindResult solveAStar(int** mapGrid,int xS,int yS,int xD,int yD);

void displayAStarResults(pathFindResult res);

#endif //MALLOC_WORLD_PATHFIND_H
