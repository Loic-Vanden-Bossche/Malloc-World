//
// Created by Loïc Vanden Bossche on 05/11/2021.
//

#ifndef MALLOC_WORLD_ITEM_H
#define MALLOC_WORLD_ITEM_H

#include <stdio.h>

enum ItemType { WEAPON, TOOL, CRAFTING, ARMOR, HEAL };

enum RessourceType { PLANT, ROCK, TREE };

typedef struct ItemData {
    int id;
    char name[30];
    enum ItemType type;

    // For resources
    int maxQty;
    int mapElemId;

    // For ressource and tools
    enum RessourceType ressourceType;

    // For tools & weapons & armor
    int maxDurability;

    // For weapons
    int damages;

    // For armors
    float pRate;

    // For potions
    int healValue;

} itemData;

typedef struct Item {
    int id;
    int durabitity;
    int qty;
} item;

const itemData* getItemData(int id);

void printItemData(int id);

const itemData* getItemsData();

const itemData* getItemDataByRessourceId(int ressourceId);

#endif //MALLOC_WORLD_ITEM_H
