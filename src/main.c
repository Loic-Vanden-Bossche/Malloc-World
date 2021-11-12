#include "../headers/main.h"

int main() {

    int exit = 0;

    while(!exit){

        switch (mainMenu()) {
            case 1:
                game();
                break;
            case 2:
                if(displayConfirm("Êtes-vous sur d'écraser votre sauvegarde actuelle ?"))
                    newGame();
                break;
            case 3:
                exit = displayConfirm("Êtes-vous sur de vouloir quitter le jeu ?");
                break;
        }
    }

    return 0;
}
