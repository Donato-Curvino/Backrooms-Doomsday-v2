#include "Player.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

#define SPEED 75

typedef sf::Keyboard Kb;

Player::Player() : sf::Sprite() {
    if (!skin.loadFromFile("assets/arrow.png"))
        std::cout << "Error loading player texture" << std::endl;
    else {
        setOrigin(skin.getSize().x * .5, skin.getSize().y * .5);
        setTexture(skin);
        setScale(3, 3);
        
    }
}

void Player::move(const float dt) {
    if (Kb::isKeyPressed(Kb::W)) {
        // move forward
        sf::Sprite::move(0, -dt * SPEED);
    } else if (Kb::isKeyPressed(Kb::S)) {
        sf::Sprite::move(0, dt * SPEED);
    }

    if (Kb::isKeyPressed(Kb::A)) {
        sf::Sprite::move(-dt * SPEED, 0);
    } else if (Kb::isKeyPressed(Kb::D)) {
        sf::Sprite::move(dt * SPEED, 0);
    }

    if (Kb::isKeyPressed(Kb::Left)) {
        sf::Sprite::rotate(-dt * SPEED);
    } else if (Kb::isKeyPressed(Kb::Right)) {
        sf::Sprite::rotate(dt * SPEED);
    }
}
