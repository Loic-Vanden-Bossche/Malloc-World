#ifndef MALLOC_WORLD_CRAFT_H
#define MALLOC_WORLD_CRAFT_H
#include "item.h"
typedef struct Ingrediant {
 int id;
 int qty;
} ingrediant;

typedef struct Craft {
 int id;
 int targetItemId;
ingrediant* ingrediant;
int avaliableZones[3];
} craft;


 item* craftItem ( item* items,int itemId);




#endif //MALLOC_WORLD_CRAFT_H
