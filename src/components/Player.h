#ifndef PLAER_H
#define PLAER_H

// #include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

// subclassing sf::Sprite already contains position and rotation data
class Player : public sf::Sprite {
  private:
    sf::Texture skin;

  public:
    // sf::Vector2f position;
    // float angle;

    Player();
};

#endif