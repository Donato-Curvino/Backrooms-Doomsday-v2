#include "Map.h"
#include <iostream>

Map::Map(const string name) {
    if(!data.loadFromFile("assets/maps/" + name))
        std::cout << "Error loading map: " << "assets/maps/" + name << std::endl;
    // else
        // std::cout << (int)data.getPixel(0, 0).r << ", " << (int)data.getPixel(0, 0).g << ", " << (int)data.getPixel(0, 0).b << ", " << (int)data.getPixel(0, 0).a << std::endl;

    sf::Vector2u size = data.getSize();
    walls = vector<bool>(size.x * size.y);
    for (int i = 0; i < walls.size(); i++) {
        walls[i] = ((sf::Color*)data.getPixelsPtr())[i].g == 255;
    }

    // for (int i = 0; i < size.y; i++) {
    //     for (int j = 0; j < size.x; j++) 
    //         std::cout << walls[i * size.y + j] << " ";
    //     std::cout << std::endl;
    // }
} 

bool Map::collide(float posx, float posy) const {
    int x = posx / 25;
    int y = posy / 25;
    int tile = x + y * data.getSize().y;
    return tile >= walls.size() ? true : walls[x + y * data.getSize().y];
}

bool Map::collide(const sf::Vector2f& pos) const {
    return Map::collide(pos.x, pos.y);
}
