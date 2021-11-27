//
// Created by Loïc Vanden Bossche on 21/11/2021.
//

#include "../headers/debugger.h"

int isDebug = 0;

void debug(const char *fmt, ...)
{
    va_list ap;

    if (isDebug) {
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
    }
}

void clrscr() {
    if(!isDebug) clearScreen();
}

void setDebug() {

    isDebug = 1;
};