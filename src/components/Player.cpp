#include "Player.h"
#include <iostream>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

#define SPEED 100
#define DEG_TO_RAD 0.0174533

typedef sf::Keyboard Kb;
typedef sf::Joystick Js;

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
    float cos_angle = std::cos(getRotation() * DEG_TO_RAD) * SPEED * dt;
    float sin_angle = std::sin(getRotation() * DEG_TO_RAD) * SPEED * dt;
    float dx = 0, dy = 0;

    if (Kb::isKeyPressed(Kb::W)) {
        dx = cos_angle;             dy = sin_angle;
    } else if (Kb::isKeyPressed(Kb::S)) {
        dx = -cos_angle;            dy = -sin_angle;
    } else {
        float js_ry = -Js::getAxisPosition(0, Js::Axis::Y) * .01;
        dx = js_ry * cos_angle;     dy = js_ry * sin_angle;
    }

    if (Kb::isKeyPressed(Kb::A)) {
        dx += sin_angle;             dy += -cos_angle;
    } else if (Kb::isKeyPressed(Kb::D)) {
        dx += -sin_angle;            dy += cos_angle;
    } else {
        float js_rx = Js::getAxisPosition(0, Js::Axis::X) * .01;
        dx += js_rx * sin_angle;     dy += js_rx * cos_angle;
    }

    if (Kb::isKeyPressed(Kb::Left)) {
        sf::Sprite::rotate(-dt * SPEED);
    } else if (Kb::isKeyPressed(Kb::Right)) {
        sf::Sprite::rotate(dt * SPEED);
    } else {
        float js_lx = Js::getAxisPosition(0, Js::Axis::Z) * .01;
        sf::Sprite::rotate(js_lx * dt * SPEED);
    }

    sf::Sprite::move(dx, dy);
}
