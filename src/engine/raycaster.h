#ifndef RAYCAST_H
#define RAYCAST_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "Map.h"

float raycast(const Map* map, const sf::Vector2f* pos, float angle, sf::Vertex* line);

#endif
