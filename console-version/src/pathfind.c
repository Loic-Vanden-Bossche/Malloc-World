//
// Created by Loïc Vanden Bossche on 20/11/2021.
//

#include "../headers/pathfind.h"

Pair make_pair(int first, int second){

    Pair pair = { first, second };

    return pair;
}

pPair make_pair_p(int first, Pair second) {

    pPair pair = { first, second };

    return pair;
}

int isValid(int row, int col)
{
    return (row >= 0) && (row < MAP_SIZE_Y) && (col >= 0)
           && (col < MAP_SIZE_X);
}

int isUnBlocked(int grid[][MAP_SIZE_X], int row, int col)
{
    return grid[col][row] == 1;
}

int isDestination(int row, int col, Pair dest)
{
    return (row == dest.first && col == dest.second);
}

double calculateHValue(int row, int col, Pair dest)
{
    return ((double)sqrt(
            (row - dest.first) * (row - dest.first)
            + (col - dest.second) * (col - dest.second)));
}

void insertPPair(pPairListNode** headRef, pPair value) {

    pPairListNode* newNode = (pPairListNode*) malloc(sizeof(pPairListNode));
    pPairListNode* last = *headRef;

    newNode->value = value;
    newNode->next = NULL;

    if(*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    while(last->next != NULL)
        last = last->next;

    last->next = newNode;
};

void insertPair(pairListNode** headRef, Pair value) {

    pairListNode* newNode = (pairListNode*) malloc(sizeof(pairListNode));
    pairListNode* last = *headRef;

    newNode->value = value;
    newNode->next = NULL;

    if(*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    while(last->next != NULL)
        last = last->next;

    last->next = newNode;
};

pPairListNode* removePPairFirstNode(pPairListNode* head)
{
    if (head == NULL)
        return NULL;

    head = head->next;

    return head;
}

pairListNode* removePairLastNode(pairListNode* head)
{
    if (head == NULL)
        return NULL;

    if (head->next == NULL) {
        return NULL;
    }

    pairListNode* second_last = head;
    while (second_last->next->next != NULL)
        second_last = second_last->next;

    second_last->next = NULL;

    return head;
}

pairListNode* getPairLastNode(pairListNode* list)
{
    if(list) {
        while(list->next) {
            list = list->next;
        }
    }
    return list;
}

void reverse(pairListNode** head_ref)
{
    pairListNode* prev = NULL;
    pairListNode* current = *head_ref;
    pairListNode* next = NULL;
    while (current != NULL) {

        next = current->next;

        current->next = prev;

        prev = current;
        current = next;
    }

    *head_ref = prev;
}


pairListNode* tracePath(cell cellDetails[][MAP_SIZE_X], Pair dest)
{
    int row = dest.first;
    int col = dest.second;

    pairListNode * path = NULL;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col)) {

        insertPair(&path, make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    insertPair(&path, make_pair(row, col));

    reverse(&path);

    return path;
}

void displayAStarResults(pathFindResult res) {

    switch (res.solved) {
        case 1:
            printf("The destination cell is found\n");
            break;
        case 0:
            printf("Source is invalid\n");
            break;
        case -1:
            printf("Destination is invalid\n");
            break;
        case -2:
            printf("Source or the destination is blocked\n");
            break;
        case -3:
            printf("We are already at the destination\n");
            break;
        case -4:
            printf("Failed to find the Destination Cell\n");
            break;
        default:
            printf("Unknown error occurred\n");
            break;

    }

    while (res.path->next != NULL) {
        printf("(%d,%d) -> ", res.path->value.first, res.path->value.second);
        res.path = res.path->next;
    }

    printf("(%d,%d)", res.path->value.first, res.path->value.second);
    printf("\n");
}

pathFindResult formatResult(pairListNode* path,int solved){
    pathFindResult res = { path, solved };
    return res;
}

pathFindResult aStarSearch(int grid[][MAP_SIZE_X], Pair src, Pair dest)
{
    if (isValid(src.first, src.second) == 0) {
        return formatResult(NULL, 0);
    }

    if (isValid(dest.first, dest.second) == 0) {
        return formatResult(NULL, -1);
    }

    if (isUnBlocked(grid, src.first, src.second) == 0
        || isUnBlocked(grid, dest.first, dest.second)
           == 0) {
        return formatResult(NULL, -2);
    }

    if (isDestination(src.first, src.second, dest)
        == 1) {
        return formatResult(NULL, -3);
    }

    int closedList[MAP_SIZE_Y][MAP_SIZE_X];
    memset(closedList, 0, sizeof(closedList));

    cell cellDetails[MAP_SIZE_Y][MAP_SIZE_X];

    int i, j;

    for (i = 0; i < MAP_SIZE_Y; i++) {
        for (j = 0; j < MAP_SIZE_X; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    pPairListNode* openList;

    openList = NULL;

    insertPPair(&openList, make_pair_p(0.0, make_pair(i, j)));

    while (openList != NULL) {
        pPair p = openList->value;

        openList = removePPairFirstNode(openList);

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = 1;

        double gNew, hNew, fNew;

        if (isValid(i - 1, j) == 1) {
            if (isDestination(i - 1, j, dest) == 1) {

                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                return formatResult(tracePath(cellDetails, dest), 1);
            } else if (closedList[i - 1][j] == 0
                     && isUnBlocked(grid, i - 1, j)
                        == 1) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i - 1][j].f == FLT_MAX
                    || cellDetails[i - 1][j].f > fNew) {
                    insertPPair(&openList, make_pair_p(fNew, make_pair(i - 1, j)));

                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        if (isValid(i + 1, j) == 1) {
            if (isDestination(i + 1, j, dest) == 1) {

                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                return formatResult(tracePath(cellDetails, dest), 1);

            } else if (closedList[i + 1][j] == 0
                     && isUnBlocked(grid, i + 1, j)
                        == 1) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i + 1][j].f == FLT_MAX
                    || cellDetails[i + 1][j].f > fNew) {
                    insertPPair(&openList, make_pair_p(
                            fNew, make_pair(i + 1, j)));

                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        if (isValid(i, j + 1) == 1) {
            if (isDestination(i, j + 1, dest) == 1) {

                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                return formatResult(tracePath(cellDetails, dest), 1);
            }

            else if (closedList[i][j + 1] == 0
                     && isUnBlocked(grid, i, j + 1)
                        == 1) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j + 1].f == FLT_MAX
                    || cellDetails[i][j + 1].f > fNew) {

                    insertPPair(&openList, make_pair_p(
                            fNew, make_pair(i, j + 1)));

                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        if (isValid(i, j - 1) == 1) {
            if (isDestination(i, j - 1, dest) == 1) {

                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;

                return formatResult(tracePath(cellDetails, dest), 1);
            }

            else if (closedList[i][j - 1] == 0
                     && isUnBlocked(grid, i, j - 1)
                        == 1) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j - 1].f == FLT_MAX
                    || cellDetails[i][j - 1].f > fNew) {
                    insertPPair(&openList, make_pair_p(
                            fNew, make_pair(i, j - 1)));

                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

        if(INCLUDE_DIAGS) {

            if (isValid(i - 1, j + 1) == 1) {
                if (isDestination(i - 1, j + 1, dest) == 1) {

                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                    return formatResult(tracePath(cellDetails, dest), 1);
                }

                else if (closedList[i - 1][j + 1] == 0
                         && isUnBlocked(grid, i - 1, j + 1)
                            == 1) {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i - 1, j + 1, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[i - 1][j + 1].f == FLT_MAX
                        || cellDetails[i - 1][j + 1].f > fNew) {
                        insertPPair(&openList, make_pair_p(
                                fNew, make_pair(i - 1, j + 1)));

                        cellDetails[i - 1][j + 1].f = fNew;
                        cellDetails[i - 1][j + 1].g = gNew;
                        cellDetails[i - 1][j + 1].h = hNew;
                        cellDetails[i - 1][j + 1].parent_i = i;
                        cellDetails[i - 1][j + 1].parent_j = j;
                    }
                }
            }

            if (isValid(i - 1, j - 1) == 1) {
                if (isDestination(i - 1, j - 1, dest) == 1) {

                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                    return formatResult(tracePath(cellDetails, dest), 1);
                }

                else if (closedList[i - 1][j - 1] == 0
                         && isUnBlocked(grid, i - 1, j - 1)
                            == 1) {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i - 1, j - 1, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[i - 1][j - 1].f == FLT_MAX
                        || cellDetails[i - 1][j - 1].f > fNew) {
                        insertPPair(&openList, make_pair_p(
                                fNew, make_pair(i - 1, j - 1)));

                        cellDetails[i - 1][j - 1].f = fNew;
                        cellDetails[i - 1][j - 1].g = gNew;
                        cellDetails[i - 1][j - 1].h = hNew;
                        cellDetails[i - 1][j - 1].parent_i = i;
                        cellDetails[i - 1][j - 1].parent_j = j;
                    }
                }
            }

            if (isValid(i + 1, j + 1) == 1) {
                if (isDestination(i + 1, j + 1, dest) == 1) {

                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                    return formatResult(tracePath(cellDetails, dest), 1);
                }

                else if (closedList[i + 1][j + 1] == 0
                         && isUnBlocked(grid, i + 1, j + 1)
                            == 1) {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i + 1, j + 1, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[i + 1][j + 1].f == FLT_MAX
                        || cellDetails[i + 1][j + 1].f > fNew) {

                        insertPPair(&openList, make_pair_p(
                                fNew, make_pair(i + 1, j + 1)));

                        cellDetails[i + 1][j + 1].f = fNew;
                        cellDetails[i + 1][j + 1].g = gNew;
                        cellDetails[i + 1][j + 1].h = hNew;
                        cellDetails[i + 1][j + 1].parent_i = i;
                        cellDetails[i + 1][j + 1].parent_j = j;
                    }
                }
            }

            if (isValid(i + 1, j - 1) == 1) {

                if (isDestination(i + 1, j - 1, dest) == 1) {

                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                    return formatResult(tracePath(cellDetails, dest), 1);
                }

                else if (closedList[i + 1][j - 1] == 0
                         && isUnBlocked(grid, i + 1, j - 1)
                            == 1) {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i + 1, j - 1, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[i + 1][j - 1].f == FLT_MAX
                        || cellDetails[i + 1][j - 1].f > fNew) {

                        insertPPair(&openList, make_pair_p(
                                fNew, make_pair(i + 1, j - 1)));

                        cellDetails[i + 1][j - 1].f = fNew;
                        cellDetails[i + 1][j - 1].g = gNew;
                        cellDetails[i + 1][j - 1].h = hNew;
                        cellDetails[i + 1][j - 1].parent_i = i;
                        cellDetails[i + 1][j - 1].parent_j = j;
                    }
                }
            }
        }
    }

    return formatResult(NULL, -4);
}

pathFindResult solveAStar(int** mapGrid,int xS,int yS,int xD,int yD)
{
    int grid[MAP_SIZE_Y][MAP_SIZE_X]
            = { 0 };

    for (int i = 0; i < MAP_SIZE_Y; ++i) {
        for (int j = 0; j < MAP_SIZE_X; ++j) {
            if(mapGrid[i][j] == 0) {
                grid[i][j] = 1;
            } else {
                grid[i][j] = 0;
            }
        }
    }

    Pair src = make_pair(xS, yS);
    Pair dest = make_pair(xD, yD);

    return aStarSearch(grid, src, dest);
}