#ifndef RAYCAST_H
#define RAYCAST_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "Map.h"

struct Ray {
    float dist;
    float tex_offset;
    bool is_shaded = false;
};

float raycast(const Map* map, const sf::Vector2f* pos, float angle, Ray* ray, sf::Vertex* line);

#endif
