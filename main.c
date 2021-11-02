#include <stdio.h>
#include "save-parser.h"
#include "map.h"

int main() {

    map *worldMap;
    worldMap = createMap(0,20);

    displayMap(*worldMap);
    destroyMap(worldMap);
    return 0;
}
