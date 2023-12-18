#include "Map.h"
#include <iostream>

Map::Map(const string name) {
    if(!data.loadFromFile("assets/maps/" + name))
        std::cout << "Error loading map: " << "assets/maps/" + name << std::endl;
    // else
        // std::cout << (int)data.getPixel(0, 0).r << ", " << (int)data.getPixel(0, 0).g << ", " << (int)data.getPixel(0, 0).b << ", " << (int)data.getPixel(0, 0).a << std::endl;

} 