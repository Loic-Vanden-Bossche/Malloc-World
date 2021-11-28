#ifndef MALLOC_WORLD_CRAFT_H
#define MALLOC_WORLD_CRAFT_H
#include "item.h"
#include "player.h"

typedef struct Ingredient {
    int qty;
    int id;
} ingredient;

typedef struct Craft {
    int id;
    int targetItemId;
    ingredient ingredient[2];
    int ingNumber;
    int availableZones[3];
} craft;

void showCraftLvl (int zone);

int craftItem(int id, item* inventory);

craft* getCraftData(int Zone);

void printCraftDataById(int id, item inventory[10]);

void isCratable(int id);

int selectCraftMenu(item inventory[10], int zone);

void printCrafts(item inventory[10], int zone);

const craft* getCraftDataById(int id);



#endif //MALLOC_WORLD_CRAFT_H