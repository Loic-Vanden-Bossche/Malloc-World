//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#include "../headers/player.h"

int const MAX_ITEM_STACK = 20;
int const BASE_PLAYER_HP = 100;
int const BASE_PLAYER_XP = 100;

int addItem(int itemId, item playerInventory[10]) {

    const itemData* data = getItemData(itemId);

    if(data == NULL) return -1;

    if(data->type == CRAFTING) {
        for (int i = 0; i < 10; ++i) {
            if(playerInventory[i].id == itemId) {

                if(playerInventory[i].qty < MAX_ITEM_STACK) {
                    playerInventory[i].qty++;
                    return 0;
                }
            }
        }
    }

    for (int i = 0; i < 10; ++i) {
        if(playerInventory[i].id == 0) {
            playerInventory[i].id = data->id;
            playerInventory[i].durabitity = data->maxDurability;
            playerInventory[i].qty = 1;
            return 0;
        }
    }

    return -2;
}

int deleteItem(int itemId, item playerInventory[10]) {
    const itemData* data = getItemData(itemId);

    if(data == NULL) return -1;

    item* itemRef = NULL;

    for (int i = 0; i < 10; ++i) {
        if(playerInventory[i].id == itemId) {
            itemRef = &playerInventory[i];
        }
    }

    if(itemRef != NULL) {
        itemRef->qty--;

        if(itemRef->qty == 0) {
            for (int i = 0; i < 10; ++i) {
                if(itemRef->id == itemId) {

                    itemRef->id = 0;
                    itemRef->qty = 0;
                    itemRef->durabitity = 0;
                }
            }
        }

        return 0;
    }

    return -1;
}

int repairItems(item inventory[10]) {

    int repaired = 0;

    for (int i = 0; i < 10; ++i) {
        const itemData* data = getItemData(inventory[i].id);

        if(data != NULL) {
            if(data->type == WEAPON || data->type == TOOL) {
                if(inventory[i].durabitity < data->maxDurability) {
                    inventory[i].durabitity = data->maxDurability;
                    repaired++;
                }
            }
        }
    }

    return repaired;
}

player* createPlayer() {

    player *newPlayer = malloc(sizeof(player));

    newPlayer->lvl = 1;
    newPlayer->hp = BASE_PLAYER_HP;
    newPlayer->maxHp = BASE_PLAYER_HP;
    newPlayer->xp = 0;

    for (int i = 0; i < 10; ++i) {
        newPlayer->inventory[i].id = 0;
        newPlayer->inventory[i].qty = 0;
        newPlayer->inventory[i].durabitity = 0;
    }

    for (int itemId = 1; itemId <= 4; ++itemId)
        addItem(itemId, newPlayer->inventory);

    return newPlayer;
}

void destroyPlayer(player* player) {

    free(player);
}

void displayPlayerInventory(item* inventory) {

    printf("Player inventory : \n");

    for (int i = 0; i < 10; ++i) {
        printf("id : %d, qty : %d, d : %d\n",
               inventory[i].id,
               inventory[i].qty,
               inventory[i].durabitity
               );
    }
}

void displayPlayerInfos(player* player){

    printf("HP: %d/%d\n", player->hp, player->maxHp);
    printf("XP: %d\n", player->xp);
    printf("LVL: %d\n", player->lvl);

    displayPlayerInventory(player->inventory);
}

void applyHp(player *player, int hp){

    if(hp <= player->maxHp && hp >= 0){
        player->hp = hp;
    }
}

float getLvlFromXp(int xp) {

    return (float)xp/BASE_PLAYER_XP;
}

float getLvlProgression(int xp, int currentLvl) {
    return getLvlFromXp(xp) - (currentLvl - 1);
}

void applyXp(player *player, int xp){

    if(xp >= 0){
        player->xp += xp;

        float lvl = roundf(getLvlFromXp(player->xp));

        if(player->lvl != lvl) {
            applyLvl(player, lvl);
        }
    }
}

int calculateXpForNextLvl(int lvl) {

    int baseXp = BASE_PLAYER_XP;

    for (int i = 1; i < lvl; ++i) {
        baseXp *= 2;
    }

    return baseXp;
}

int calculateMaxHp(int lvl){

    int maxHp = 100;

    for (int i = 1; i <= 10; ++i) {

        if(lvl == i) return maxHp;

        if(i >= 6 && i < 8) maxHp += 50;
        else if(i == 8 || i == 9) maxHp += 75;
        else maxHp += (10*i);
    }

    return 0;
}

void applyLvl(player *player, int lvl) {

    player->lvl = lvl;

    int maxHp = 100;

    for (int i = 0; i < lvl; ++i) {
        maxHp *= 1.2;
    }

    player->maxHp = maxHp;
}