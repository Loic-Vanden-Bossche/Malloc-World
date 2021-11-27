//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#include "../headers/player.h"

int const MAX_ITEM_STACK = 20;
int const MAX_PLAYER_HP = 100;

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

player* createPlayer() {

    player *newPlayer = malloc(sizeof(player));

    newPlayer->lvl = 1;
    newPlayer->hp = MAX_PLAYER_HP;
    newPlayer->maxHp = MAX_PLAYER_HP;
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

void applyXp(player *player, int xp){

    if(xp >= 0){
        player->xp = xp;
    }
}

void applyLvl(player *player, int lvl) {

    player->lvl = lvl;

    int maxHp = 100;

    for (int i = 0; i < lvl; ++i) {
        maxHp = maxHp * 1.2;
    }

    player->maxHp = maxHp;
}