#include "../headers/item.h"
#include "../headers/craft.h"

const int craftCount = 25;

const craft craftList[25] = {
    { 1, 1, {3,5} ,1 , { 1, 2, 3 }},
    { 2, 8, {{2, 5}, {3, 6}}, 2, { 1, 2, 3 }},
    { 3, 19, {{2, 16}, {4, 17}}, 2, { 0, 2, 3 }},
    { 4, 30, {{2, 27},{ 2, 28}}, 2, { 0, 0, 3 }},
    { 5, 9, {{3, 5}, {4, 6}}, 2, { 1, 2, 3 }},
    { 6, 20, {{3, 16}, {4, 17}}, 2, { 0, 2, 3 }},
    { 7, 31, {{2, 27}, {5, 28}}, 2, { 0, 0, 3 }},
    { 8, 10, {{2, 5}, {6, 6}}, 2, { 1, 2, 3 }},
    { 9, 21, {{2, 16}, {7, 17}}, 2, { 0, 2, 3 }},
    { 10, 32, {{2,27}, {8,28}}, 2, { 0, 0, 3 }},
    { 11, 11, {10, 6}, 1, { 1, 2, 3 }},
    { 12, 22, {12, 17}, 1, { 0, 2, 3 }},
    { 13, 33, {16, 28}, 1, { 0, 0, 3 }},
    { 14, 2, {3,5}, 1, { 1, 2, 3 }},
    { 15, 12, {{2, 5}, {3, 6}}, 2, { 1, 2, 3 }},
    { 16, 23, {{2, 16}, {4, 17}}, 2, { 0, 2, 3 }},
    { 17, 4, {3, 5}, 1, { 1, 2, 3 }},
    { 18, 14, {{2, 5}, {3, 6}}, 2, { 1, 2, 3 }},
    { 19, 25, {{2, 16}, {4, 17}}, 2,{ 0, 2, 3 }},
    { 20, 3, {3, 5}, 1, { 1, 2, 3 }},
    { 21, 13, {{2, 5}, {3, 6}}, 2, { 1, 2, 3 }},
    { 22, 24, {{2, 5}, {4, 17}}, 2, { 0, 2, 3 }},
    { 23, 15, {2, 7}, 1, { 1, 2, 3 }},
    { 24, 26, {2, 18}, 1, { 0, 2, 3 }},
    { 25, 34, {2, 29}, 1, { 0, 0, 3 }},
}; 

const craft* getCraftDataById(int id) {
    for (int i = 0; i < craftCount; ++i) {
        if(craftList[i].id == id){
            return &craftList[i];
        }
    }

    return NULL;
}

int isCraftable(int id, item inventory[10]) {

    const craft* data = getCraftDataById(id);

    int ingFound = 0;

    for (int i = 0; i < data->ingNumber; ++i) {
        for (int j = 0; j < 10; ++j) {
            if(data->ingredient[i].id == inventory[j].id) {
                if(inventory[j].qty >= data->ingredient[i].qty) {
                    ingFound++;
                    if(ingFound == data->ingNumber) return 1;
                }
            }
        }
    }

    return 0;
}

// 1 - Epée en bois | 3 bois - 1 roche | craftable : oui
    
void printCraftData(const craft* data, item inventory[10]) {

    if(data == NULL) return;

    const  itemData* targetItem = getItemData(data->targetItemId);

    printf("%s | ", targetItem->name);

    for (int i = 0; i < data->ingNumber; ++i) {

        const itemData* ingData = getItemData(data->ingredient[i].id);

        printf("%d %s ", data->ingredient[i].qty, ingData->name );

        if(i < data->ingNumber - 1) printf("- ");
    }

    printf("| craftable : %s \n", isCraftable(data->id, inventory) ? "oui" : "non");
}

int isInZone(const int avaliableZones[3], int zone) {
    for (int i = 0; i < 3; ++i) {
        if(avaliableZones[i] == zone)
            return 1;
    }

    return 0;
}

void printCrafts(item inventory[10], int zone) {

    for (int id = 1; id <= 25; ++id) {
        const craft* data = getCraftDataById(id);

        if(data != NULL) {
            if(isInZone(data->availableZones, zone) || zone == -1) {
                printf("%d - ", id);
                printCraftData(data, inventory);
            }
        }
    }
}

int selectCraftMenu(item inventory[10], int zone) {

    printCrafts(inventory, zone);
    printf("a - Quitter\n");

    int craftId;

    while(1) {

        craftId = 0;

        fflush(stdin);
        scanf("%d", &craftId);

        switch(craftId) {
            case 0:
                return 0;
            default:
                for (int id = 1; id <= 25; ++id) {
                    const craft* data = getCraftDataById(id);
                    if(data != NULL) {
                        if(isInZone(data->availableZones, zone) || zone == -1) {

                            if(craftId == data->id) {
                                switch (craftItem(data->id, inventory)) {
                                    case 0:
                                        return data->id;
                                    case -1:
                                        printf("Vous n'avez plus de place dans l'inventaire\n");
                                    case -2:
                                        printf("Vous n'avez pas des ressources necessaires\n");
                                }
                            };
                        }
                    }
                }
        }
    }

    return 0;
}

int craftItem(int id, item* inventory) {

    const craft* data = getCraftDataById(id);

    if(isCraftable(data->id, inventory)) {

        if(!addItem(data->targetItemId, inventory)) {
            for (int i = 0; i < data->ingNumber; ++i) {
                for (int j = 0; j < data->ingredient[i].qty; ++j) {
                    deleteItem(data->ingredient[i].id, inventory);
                }
            }

            return 0;
        }

        return -1;
    }

    return -2;
}