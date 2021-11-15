//
// Created by Loïc Vanden Bossche on 12/11/2021.
//

#ifndef MALLOC_WORLD_STORAGE_H
#define MALLOC_WORLD_STORAGE_H
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct StorageNode {
    item item;
    struct StorageNode* next;
} storageNode;

void appendToStorage(storageNode** headRef, item item);

void printStorage(storageNode* storage);

#endif //MALLOC_WORLD_STORAGE_H
