#ifndef _MAP_H_
#define _MAP_H_

#include <SFML/Graphics/Image.hpp>
#include <string>

using std::string;

class Map {
  private:
    sf::Image data;

  public:
    Map(const string name);
};

#endif
