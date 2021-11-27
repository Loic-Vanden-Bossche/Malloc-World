#ifndef MALLOC_WORLD_CRAFT_H
#define MALLOC_WORLD_CRAFT_H
#include "item.h"

typedef struct Ingredient {
    int id;
    int qty;
} ingredient;

typedef struct Craft {
    int id;
    int targetItemId;
    ingredient ingredient[2];
    int ingNumber;
    int avaliableZones[3];
} craft;

void showCraftLvl (int zone);

item* craftItem ( item* items,int idCraft);

craft* getCraftData(int Zone);

void printCraftDataById(int id) ;

void isCratable(int id) ;

#endif //MALLOC_WORLD_CRAFT_H