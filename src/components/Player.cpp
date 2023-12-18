#include "Player.h"
#include <iostream>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>

#define SPEED 100
#define DEG_TO_RAD 0.0174533

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
    // std::cout << M_PI / 180 << std::endl;
    float dx = std::cos(getRotation() * DEG_TO_RAD) * SPEED * dt;
    float dy = std::sin(getRotation() * DEG_TO_RAD) * SPEED * dt;

    if (Kb::isKeyPressed(Kb::W)) {
        // move forward
        sf::Sprite::move(dx, dy);
    } else if (Kb::isKeyPressed(Kb::S)) {
        sf::Sprite::move(-dx, -dy);
    }

    if (Kb::isKeyPressed(Kb::A)) {
        sf::Sprite::move(dy, -dx);
    } else if (Kb::isKeyPressed(Kb::D)) {
        sf::Sprite::move(-dy, dx);
    }

    if (Kb::isKeyPressed(Kb::Left)) {
        sf::Sprite::rotate(-dt * SPEED);
    } else if (Kb::isKeyPressed(Kb::Right)) {
        sf::Sprite::rotate(dt * SPEED);
    }
}
