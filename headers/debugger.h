//
// Created by Loïc Vanden Bossche on 21/11/2021.
//

#ifndef MALLOC_WORLD_DEBUGGER_H
#define MALLOC_WORLD_DEBUGGER_H

#include <stdarg.h>
#include <stdio.h>

#define clearScreen() printf("\e[1;1H\e[2J")

void debug(const char *fmt, ...);
void setDebug();

void clrscr();

#endif //MALLOC_WORLD_DEBUGGER_H
