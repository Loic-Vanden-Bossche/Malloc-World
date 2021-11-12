//
// Created by Loïc Vanden Bossche on 12/11/2021.
//

#ifndef MALLOC_WORLD_GAME_H
#define MALLOC_WORLD_GAME_H

#include <conio.h>
#include "./save.h"
#include "./map.h"
#include "./player.h"

#define clrscr() printf("\e[1;1H\e[2J")

void display(map* worldMap, player* player);
int mainMenu();
int displayConfirm(char* message);
int game();
int newGame();

#endif //MALLOC_WORLD_GAME_H
