//
// Created by Loïc Vanden Bossche on 24/11/2021.
//

#ifndef MALLOC_WORLD_DISPLAY_H
#define MALLOC_WORLD_DISPLAY_H

#include "map.h"
#include "player.h"
#include "stdio.h"

typedef struct LogNode {

    char log[50];
    struct LogNode* next;
} logNode;

void setUnicode();
void display(map* worldMap, player* player);

void addLog( const char * format, ... );
void printLogs();
void displayWholeMap(map* worldMap);

#endif //MALLOC_WORLD_DISPLAY_H
