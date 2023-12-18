#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/Map.h"

#define WIDTH 1280
#define HEIGHT 720

using std::string;

int main() {
    // INITIALIZE GAME OBJECTS
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");
    window.setFramerateLimit(60);
    sf::Clock clock;
    sf::VertexArray walls(sf::Lines, WIDTH * 2);
    
    Map map("backroom.png");
    sf::Texture texture;
    texture.loadFromImage(map.data);
    sf::Sprite mapSprite(texture);
    mapSprite.setScale(25, 25);

    // GAME LOOP
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        
        // EVENT LOOP
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        window.clear(sf::Color(0, 0, 255, 255));
        // TODO: draw screen
        window.draw(mapSprite);
        // window.draw(map);
        window.display();
    }
    return 0;
}
