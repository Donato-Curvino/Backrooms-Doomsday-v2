#ifndef PLAER_H
#define PLAER_H

// #include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "../engine/Map.h"

// subclassing sf::Sprite already contains position and rotation data
class Player : public sf::Sprite {
  private:
    sf::Texture skin;
    float hitbox = 12.5;    // must be 1/2 the map's current scale

  public:
    // sf::Vector2f position;
    // float angle;

    Player();
    void move(const float dt, const Map& map);      // may return how much actually moved
};

#endif
