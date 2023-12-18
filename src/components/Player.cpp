#include "Player.h"
#include <iostream>

Player::Player() : sf::Sprite() {
    if (!skin.loadFromFile("assets/arrow.png"))
        std::cout << "Error loading player texture" << std::endl;
    else {
        setTexture(skin);
        setScale(3, 3);
    }
}

