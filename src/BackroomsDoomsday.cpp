#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "engine/Map.h"
#include "components/Player.h"
#include "engine/raycaster.h"

#define WIDTH 1280
#define HEIGHT 720
#define FOV 30

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
    player.setPosition(50, 50);

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

        sf::VertexArray rays(sf::Lines, 2 * WIDTH);
        std::vector<float> dists(WIDTH);
        float da = FOV / (WIDTH * .5);
        float angle = player.getRotation() - (WIDTH / 2) * da;
        for (int i = 0; i < WIDTH; i++) {
            dists[i] = raycast(&map, &player.getPosition(), angle, &rays[i * 2]);
            angle += da;
        }

        sf::VertexArray walls(sf::Lines, 2 * WIDTH);
        for (int i = 0; i < WIDTH; i++) {
            float len = HEIGHT * 25 / dists[i];
            walls[i * 2] = sf::Vertex(sf::Vector2f(i, HEIGHT * .5 - len), sf::Color::Red);
            walls[i * 2 + 1] = sf::Vertex(sf::Vector2f(i, HEIGHT * .5 + len), sf::Color::Red);
        }

        window.clear(sf::Color(0, 0, 255, 255));
        window.draw(mapSprite);
        window.draw(rays);
        window.draw(player);
        window.draw(walls);
        window.display();
    }
    return 0;
}
