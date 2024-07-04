#ifndef BUTTON_H
#define BUTTON_H

#include <vector>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
// #include <SFML/System/Vector2.hpp>

class Button : public sf::Sprite {
  private:
    sf::Texture texture;
    std::vector<bool> mask;
    void (* callback)();

    bool is_on_button(const sf::Vector2i& mouse_pos);

  public:
    Button(std::string name, void (* cb)());
    void press(sf::Vector2i mouse_pos);
};

#endif
