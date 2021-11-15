//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#include "../headers/player.h"

int const MAX_ITEM_STACK = 20;
int const MAX_PLAYER_HP = 100;

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

    return newPlayer;
}

void displayPlayerInventory(player* player){

    printf("Player inventory : \n");

    for (int i = 0; i < 10; ++i) {
        printf("id : %d, qty : %d, d : %d\n",
               player->inventory[i].id,
               player->inventory[i].qty,
               player->inventory[i].durabitity
               );
    }
}

void displayPlayerInfos(player* player){

    printf("HP: %d/%d\n", player->hp, player->maxHp);
    printf("XP: %d\n", player->xp);
    printf("LVL: %d\n", player->lvl);

    displayPlayerInventory(player);
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