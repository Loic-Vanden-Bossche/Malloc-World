//
// Created by Loïc Vanden Bossche on 12/11/2021.
//

#include "../headers/game.h"

void display(map* worldMap, player* player) {

    clrscr();

    displayMap(worldMap);
    displayPlayerInfos(player);
}

int mainMenu() {

    clrscr();

    printf("1 - Continuer\n");
    printf("2 - Nouvelle partie\n");
    printf("3 - Quitter\n");

    int ch;

    while(1) {

        ch = getch();

        if(ch == '1' || ch == '2' || ch == '3'){

            return ch - '0';
        }
    }
}

int displayConfirm(char* message) {

    clrscr();
    printf("%s Oui (o) Non (n)\n",message);

    int ch;

    while(1) {

        ch = getch();

        if (ch == 'o') return 1;
        else if (ch == 'n') return 0;
    }
}

int game() {

    map *worldMap = createMap(0);
    player* player = createPlayer();

    int ch = -1;

    do
    {
        display(worldMap, player);

        if (ch == 0 || ch == 224) {

            switch (getch()) {
                case 80:
                    printf("DOWN");
                    break;
                case 72:
                    printf("UP");
                    break;
                case 77:
                    printf("RIGHT");
                    break;
                case 75:
                    printf("LEFT");
                    break;
            }
        }
    } while ((ch = getch()) != 27);

    saveData(worldMap, player);

    destroyMap(worldMap);

    return 0;
}

int newGame() {

    game();
    return 0;
}
