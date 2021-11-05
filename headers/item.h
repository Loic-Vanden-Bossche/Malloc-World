//
// Created by Loïc Vanden Bossche on 05/11/2021.
//

#ifndef MALLOC_WORLD_ITEM_H
#define MALLOC_WORLD_ITEM_H

#include <stdio.h>

enum ItemType { WEAPON, TOOL, CRAFTING, ARMOR, HEAL };

typedef struct ItemData {
    int id;
    char name[30];
    enum ItemType type;

    int maxDurability;
    int damages;
    int healValue;
    float pRate;
    int maxQty;

} itemData;

typedef struct Item {
    int id;
    int durabitity;
    int qty;
} item;

const itemData* getItemData(int id);

void printItemData(int id);

const itemData* getItemsData();

#endif //MALLOC_WORLD_ITEM_H
