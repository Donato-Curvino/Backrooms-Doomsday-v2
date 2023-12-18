#ifndef _MAP_H_
#define _MAP_H_

#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

using std::string, std::vector;

class Map {
  private:
    vector<bool> walls;

  public:
    sf::Image data;

//   public:
    Map(const string name);
    bool collide(float x, float y) const;
    bool collide(const sf::Vector2f& pos) const;
};

#endif
