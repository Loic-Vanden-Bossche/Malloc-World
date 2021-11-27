#include "../headers/main.h"

int main(int argc, char **argv) {

    int exit = 0;

    for (int i = 0; i < argc; ++i) {
        if(strcmp(argv[i], "--debug") == 0){
            setDebug();
        }

        if(strcmp(argv[i], "--unicode") == 0){
            setUnicode();
        }
    }

    srand(time(NULL));

    while(!exit){

        switch (mainMenu()) {
            case 1:
                continueGame();
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
