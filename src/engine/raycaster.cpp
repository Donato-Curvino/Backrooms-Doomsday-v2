#include <cmath>
#include <iostream>
#include <SFML/Graphics/Color.hpp>

#include "raycaster.h"

#ifndef DEG_TO_RAD 
#define DEG_TO_RAD 0.017453292519943295
#endif

float raycast(const Map* map, const sf::Vector2f* pos, float angle, Ray* ray, sf::Vertex* line = nullptr) {
    angle *= DEG_TO_RAD;
    float dx = 25 * std::cos(angle);        float dy = 25 * std::sin(angle);
    float h_endx = pos->x + (dx >= 0 ? (25 - std::fmod(pos->x, 25)) : -(.0001 + std::fmod(pos->x, 25)));
    float h_endy = pos->y + (h_endx - pos->x) * dy / dx;
    float v_endy = pos->y + (dy >= 0 ? (25 - std::fmod(pos->y, 25)) : -(.0001 + std::fmod(pos->y, 25)));
    float v_endx = pos->x + (v_endy - pos->y) * dx / dy;                
    int h_step = (dx >= 0) ? 25 : -25;      int v_step = dy >= 0 ? 25 : -25;

    // check horizontal
    dy = h_step * std::tan(angle);
    while (!map->collide(h_endx, h_endy)) {
        h_endx += h_step;       h_endy += dy;
    }

    // check vertical
    dx = v_step / std::tan(angle); 
    while (!map->collide(v_endx, v_endy)) {
        v_endx += dx;       v_endy += v_step;
    }

    bool h_is_min = false;
    float h_dist = std::sqrt((pos->x - h_endx) * (pos->x - h_endx) + (pos->y - h_endy) * (pos->y - h_endy));
    float v_dist = std::sqrt((pos->x - v_endx) * (pos->x - v_endx) + (pos->y - v_endy) * (pos->y - v_endy));
    ray->dist = v_dist;
    ray->tex_offset = std::fmod(v_endx, 25);            //TODO: mod with actual wall texture instead of 25
    if (h_dist < v_dist) {
        h_is_min = true;
        ray->dist = h_dist;
        ray->tex_offset = std::fmod(h_endy, 25);
        ray->is_shaded = true;
    }

    if (line != nullptr) {
        line[0] = sf::Vertex(*pos, sf::Color::Red);
        line[1] = sf::Vertex(h_is_min ? sf::Vector2f(h_endx, h_endy) : sf::Vector2f(v_endx, v_endy), sf::Color::Red);
    }

    return ray->dist;
}
