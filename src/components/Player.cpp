#include "../engine/cross_platform.h"
#include "Player.h"
#include <iostream>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

#define SPEED 100
#define DEG_TO_RAD 0.017453292519943295

typedef sf::Keyboard Kb;
typedef sf::Joystick Js;

Player::Player() : sf::Sprite() {
    if (!skin.loadFromFile(PATH_PREFIX("assets/arrow.png")))
        std::cout << "Error loading player texture" << std::endl;
    else {
        setOrigin(skin.getSize().x * .5, skin.getSize().y * .5);
        setTexture(skin);
        setScale(3, 3);
        
    }
}

void Player::move(const float dt, const Map& map) {
    // std::cout << M_PI / 180 << std::endl;
    float cos_angle = std::cos(getRotation() * DEG_TO_RAD) * SPEED * dt;
    float sin_angle = std::sin(getRotation() * DEG_TO_RAD) * SPEED * dt;
    float dx = 0, dy = 0;

    if (Kb::isKeyPressed(Kb::W)) {
        dx = cos_angle;             dy = sin_angle;
    } else if (Kb::isKeyPressed(Kb::S)) {
        dx = -cos_angle;            dy = -sin_angle;
    } else {
        float js_ry = Js::getAxisPosition(0, Js::Axis::Y) * .000025;
        // float js_ry = (int)Js::getAxisPosition(0, Js::Axis::Y) / INT32_MAX
        dx = js_ry * cos_angle;     dy = js_ry * sin_angle;
    }

    if (Kb::isKeyPressed(Kb::A)) {
        dx += sin_angle;             dy += -cos_angle;
    } else if (Kb::isKeyPressed(Kb::D)) {
        dx += -sin_angle;            dy += cos_angle;
    } else {
        float js_rx = Js::getAxisPosition(0, Js::Axis::X) * .000025;
        dx += js_rx * sin_angle;     dy += js_rx * cos_angle;
    }

    if (Kb::isKeyPressed(Kb::Left)) {
        sf::Sprite::rotate(-dt * SPEED);
    } else if (Kb::isKeyPressed(Kb::Right)) {
        sf::Sprite::rotate(dt * SPEED);
    } else {
        float js_lx = Js::getAxisPosition(0, Js::Axis::U) * .000025;
        sf::Sprite::rotate(js_lx * dt * SPEED);
    }

    sf::Vector2f curr_pos = getPosition();
    if (map.collide(curr_pos.x + hitbox + dx, curr_pos.y + hitbox) || map.collide(curr_pos.x + hitbox + dx, curr_pos.y - hitbox) 
      || map.collide(curr_pos.x - hitbox + dx, curr_pos.y + hitbox) || map.collide(curr_pos.x - hitbox + dx, curr_pos.y - hitbox))
        dx = 0;
    if (map.collide(curr_pos.x + hitbox, curr_pos.y + hitbox + dy) || map.collide(curr_pos.x + hitbox, curr_pos.y - hitbox + dy)
      || map.collide(curr_pos.x - hitbox, curr_pos.y + hitbox + dy) || map.collide(curr_pos.x - hitbox, curr_pos.y - hitbox + dy))
        dy = 0;
    sf::Sprite::move(dx, dy);
    // std::cout << getGlobalBounds().width << " | " << getGlobalBounds().height << std::endl;
}
