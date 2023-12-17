#include "Map.h"
#include <iostream>

Map::Map(const string name) {
    if(!data.loadFromFile("assets/maps/" + name))
        std::cout << "Error loading map: " << "assets/maps/" + name << std::endl;
    else
        std::cout << data.getPixel(0, 0).r << ", " << data.getPixel(0, 0).g << ", " << data.getPixel(0, 0).b << std::endl;
} 