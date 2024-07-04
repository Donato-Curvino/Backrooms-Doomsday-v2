#include "Button.h"
#include <SFML/Graphics/Image.hpp>

Button::Button(std::string name, void (* cb) ()) : callback{cb} {
    sf::Image image;     
    sf::Vector2u size = image.getSize();   
    image.loadFromFile("romfs:/assets/" + name);
    texture.loadFromImage(image);

    mask = std::vector<bool>(size.x * size.y);
    for (int i = 0; i < mask.size(); i++) {
        mask[i] = ((sf::Color*)image.getPixelsPtr())[i].a == 255;
    }
}

bool Button::is_on_button(const sf::Vector2i& mouse_pos) {
    int x = mouse_pos.x / getScale().x - getPosition().x;
    int y = mouse_pos.y / getScale().y - getPosition().y;
    return (x < 0 || y < 0 || x >= texture.getSize().x || y >= texture.getSize().y) ? false : mask[x + y * texture.getSize().y];
}
