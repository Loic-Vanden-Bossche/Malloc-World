//
// Created by Loïc Vanden Bossche on 05/11/2021.
//

#include "../headers/item.h"

const int itemsCount = 34;

const itemData itemList[34] = {

        { 1, "Epee en bois", WEAPON,
                .maxDurability = 10,
                .damages = 1
        },

        { 2, "Pioche en bois", TOOL,
                .maxDurability = 10,
                .ressourceType = ROCK
        },

        { 3, "Serpe en bois", TOOL,
                .maxDurability = 10,
                .ressourceType = PLANT
        },

        { 4, "Hache en bois", TOOL,
                .maxDurability = 10,
                .ressourceType = TREE
        },

        { 5, "Sapin", CRAFTING,
                .mapElemId = 5,
                .ressourceType = TREE
        },

        { 6, "Pierre", CRAFTING,
                .mapElemId = 4,
                .ressourceType = ROCK
        },

        { 7, "Herbe", CRAFTING,
                .mapElemId = 3,
                .ressourceType = PLANT
        },

        { 8, "Epee en pierre", WEAPON,
                .maxDurability = 10,
                .damages = 2
        },

        { 9, "Lance en pierre", WEAPON,
                .maxDurability = 8,
                .damages = 3
        },

        { 10, "Marteau en pierre", WEAPON,
                .maxDurability = 5,
                .damages = 4
        },

        { 11, "Plastron en pierre", ARMOR,
                .pRate = 0.1,
        },

        { 12, "Pioche en pierre", TOOL,
                .maxDurability = 10,
                .ressourceType = ROCK
        },

        { 13, "Serpe en pierre", TOOL,
                .maxDurability = 10,
                .ressourceType = PLANT
        },

        { 14, "Hache en pierre", TOOL,
                .maxDurability = 10,
                .ressourceType = TREE
        },

        { 15, "Potion de vie I", HEAL,
                .healValue = 30
        },

        { 16, "Hetre", CRAFTING,
                .mapElemId = 8,
                .ressourceType = TREE
        },

        { 17, "Fer", CRAFTING,
                .mapElemId = 7,
                .ressourceType = ROCK
        },

        { 18, "Lavande", CRAFTING,
                .mapElemId = 6,
                .ressourceType = PLANT
        },

        { 19, "Epee en fer", WEAPON,
                .maxDurability = 10,
                .damages = 5
        },

        { 20, "Lance en fer", WEAPON,
                .maxDurability = 8,
                .damages = 7
        },

        { 21, "Marteau en fer", WEAPON,
                .maxDurability = 5,
                .damages = 10
        },

        { 22, "Plastron en fer", ARMOR,
                .pRate = 0.2,
        },

        { 23, "Pioche en fer", TOOL,
                .maxDurability = 10,
                .ressourceType = ROCK
        },

        { 24, "Serpe en fer", TOOL,
                .maxDurability = 10,
                .ressourceType = PLANT
        },

        { 25, "Hache en fer", TOOL,
                .maxDurability = 10,
                .ressourceType = TREE
        },

        { 26, "Potion de vie II", HEAL,
                .healValue = 80
        },

        { 27, "Chene", CRAFTING,
                .mapElemId = 11,
                .ressourceType = TREE
        },

        { 28, "Diamant", CRAFTING,
                .mapElemId = 10,
                .ressourceType = ROCK
        },

        { 29, "Chanvre", CRAFTING,
                .mapElemId = 9,
                .ressourceType = PLANT
        },

        { 30, "Epee en diamant", WEAPON,
                .maxDurability = 10,
                .damages = 10
        },

        { 31, "Lance en diamant", WEAPON,
                .maxDurability = 8,
                .damages = 15
        },

        { 32, "Marteau en diamant", WEAPON,
                .maxDurability = 8,
                .damages = 15
        },

        { 33, "Plastron en diamant", ARMOR,
                .pRate = 0.4,
        },

        { 34, "Potion de vie III", HEAL,
                .healValue = 200
        },
};

const itemData* getItemData(int id) {
    for (int i = 0; i < itemsCount; ++i) {
        if(itemList[i].id == id) return &itemList[i];
    }

    return NULL;
}

const itemData* getItemDataByRessourceId(int ressourceId) {

    for (int i = 0; i < itemsCount; ++i) {
        if(itemList[i].type == CRAFTING && itemList[i].mapElemId == ressourceId) return &itemList[i];
    }

    return NULL;
}

void printItemData(int id) {

    const itemData* data = getItemData(id);

    printf("Infos de l'item : %s\n", data->name);

    switch (data->type) {

        case WEAPON:
            printf("\tDegats : %d\n", data->damages);
            printf("\tDurabilite : %d\n", data->maxDurability);
            break;

        case TOOL:
            printf("\tDurabilite : %d\n", data->maxDurability);
            break;

        case CRAFTING:
            printf("\tQuantite max : 20\n");
            break;

        case ARMOR:
            printf("\tDurabilite : %d\n", data->maxDurability);
            printf("\tProtection : %f\n", data->pRate);
            break;

        case HEAL:
            printf("\tHeal : %d\n", data->healValue);
            break;
    }
}

const itemData* getItemsData() {
    return itemList;
}