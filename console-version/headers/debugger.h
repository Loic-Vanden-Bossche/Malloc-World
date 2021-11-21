//
// Created by Loïc Vanden Bossche on 21/11/2021.
//

#ifndef MALLOC_WORLD_DEBUGGER_H
#define MALLOC_WORLD_DEBUGGER_H

#include <stdarg.h>
#include <stdio.h>

void debug(const char *fmt, ...);
void setDebug(int isDebug);

#endif //MALLOC_WORLD_DEBUGGER_H
