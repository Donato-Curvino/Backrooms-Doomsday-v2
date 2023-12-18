#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/Map.h"
#include "components/Player.h"

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

    Player player;
    player.setPosition(25, 25);

    // GAME LOOP
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        
        // EVENT LOOP
        sf::Event event;
        while (window.pollEvent(event)) {            
            switch (event.type) {
                case sf::Event::Closed:
                    window.close(); 
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
            }
        }

        player.move(dt.asSeconds(), map);

        window.clear(sf::Color(0, 0, 255, 255));
        window.draw(mapSprite);
        window.draw(player);
        window.display();
    }
    return 0;
}
