//
// Created by Loïc Vanden Bossche on 02/11/2021.
//

#include "../headers/player.h"

int const MAX_ITEM_STACK = 20;
int const MAX_PLAYER_HP = 100;

player* createPlayer() {

    player *newPlayer = malloc(sizeof(player));

    //newPlayer->inventory;

    newPlayer->lvl = 1;
    newPlayer->hp = 100;
    newPlayer->xp = 0;

    return newPlayer;
}

void displayPlayerInfos(player player){

    printf("HP: %d/%d\n", player.hp, player.maxHp);
    printf("XP: %d\n", player.xp);
    printf("LVL: %d\n", player.lvl);
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