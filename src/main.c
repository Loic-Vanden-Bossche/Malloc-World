#include "../headers/main.h"

int main() {

    map *worldMap;
    worldMap = createMap(0,20);

    displayMap(*worldMap);

    saveData(*worldMap);

    destroyMap(worldMap);
    return 0;
}
