#include <cmath>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <cassert>

#include "raycaster.h"

#ifndef DEG_TO_RAD 
#define DEG_TO_RAD 0.0174533
#endif

float raycast(const Map* map, const sf::Vector2f* pos, float angle, sf::Vertex* line = nullptr) {
    // std::cout << angle << " | ";
    angle *= DEG_TO_RAD;
    float dx = 25 * std::cos(angle);    float dy = 25 * std::sin(angle);
    int h_endx = pos->x + (dx >= 0 ? (25 - std::fmod(pos->x, 25)) : -(1 + std::fmod(pos->x, 25)));
    int h_endy = pos->y + (h_endx - pos->x) * dy / dx;
    int v_endy = pos->y + (dy >= 0 ? (25 - std::fmod(pos->y, 25)) : -(1 + std::fmod(pos->y, 25)));
    int v_endx = pos->x + (v_endy - pos->y) * dx / dy;                
    int h_step = (dx >= 0) ? 25 : -25;    int v_step = dy >= 0 ? 25 : -25;

    // initialization SHOULD be good
    // if (line != nullptr) {
    //     line[0] = sf::Vertex(*pos, sf::Color::Red);
    //     line[1] = sf::Vertex(sf::Vector2f(h_endx, h_endy), sf::Color::Red);
    //     line[2] = sf::Vertex(*pos, sf::Color::Yellow);
    //     line[3] = sf::Vertex(sf::Vector2f(v_endx, v_endy), sf::Color::Yellow);
    // }

    // std::cout << (std::atan2(dy, dx) / DEG_TO_RAD) << " > ";
    // check horizontal
    dy = h_step * std::tan(angle);
    while (!map->collide(h_endx, h_endy)) {
        h_endx += h_step;       h_endy += dy;
        // std::cout << (std::atan2(h_endy, h_endx) / DEG_TO_RAD) << ", ";
    }
    // std::cout << std::endl;

    // check vertical
    dy = v_step / std::tan(angle); 
    while (!map->collide(v_endx, v_endy)) {
        v_endx += dx;       v_endy += v_step;
    }

    bool h_is_min = false;
    float h_dist = std::sqrt((pos->x - h_endx) * (pos->x - h_endx) + (pos->y - h_endy) * (pos->y - h_endy));
    float v_dist = std::sqrt((pos->x - v_endx) * (pos->x - v_endx) + (pos->y - v_endy) * (pos->y - v_endy));
    float dist = v_dist;
    if (h_dist < v_dist) {
        h_is_min = true;
        dist = h_dist;
    }

    // if (line != nullptr) {
    //     line[0] = sf::Vertex(*pos, sf::Color::Red);
    //     line[1] = sf::Vertex(sf::Vector2f(h_endx, h_endy), sf::Color::Black);
    //     line[2] = sf::Vertex(*pos, sf::Color::Yellow);
    //     line[3] = sf::Vertex(sf::Vector2f(v_endx, v_endy), sf::Color::Yellow);
    // }

    if (line != nullptr) {
        line[0] = sf::Vertex(*pos, sf::Color::Magenta);
        line[1] = sf::Vertex(h_is_min ? sf::Vector2f(h_endx, h_endy) : sf::Vector2f(v_endx, v_endy), sf::Color::Magenta);
    }

    // std::cout << dist << std::endl;
    return dist;
}
