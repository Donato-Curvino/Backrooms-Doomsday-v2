#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "engine/Map.h"
#include "components/Player.h"
#include "components/Enemy.h"
#include "engine/raycaster.h"

#define WIDTH 1280
#define HEIGHT 720
#define FOV 30
#define DEG_TO_RAD 0.0174533

using std::string;

int main() {
    // INITIALIZE GAME OBJECTS
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");
    // window.setFramerateLimit(60);
    sf::Clock clock;
    sf::VertexArray walls(sf::Lines, WIDTH * 2);
    sf::RenderTexture wall_target;
    if (!wall_target.create(WIDTH, HEIGHT))
        return -1;
    
    Map map("backroomsTST.png");
    sf::Texture texture;
    texture.loadFromImage(map.data);
    sf::Sprite mapSprite(texture);
    mapSprite.setScale(25, 25);
    sf::Texture wall_tex;
    wall_tex.loadFromFile("assets/backwall.png");

    Player player;
    player.setPosition(112, 112);

    Enemy enemy("skinwalker_sheet.png", sf::Vector2u(75, 75), sf::Vector2f(312, 312));

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

        // raycasting
        sf::VertexArray cast_rays(sf::Lines, 2 * WIDTH);
        std::vector<Ray> rays(WIDTH);
        float da = FOV / (WIDTH * .5);
        float angle = player.getRotation() - (WIDTH / 2) * da;
        for (int i = 0; i < WIDTH; i++) {
            raycast(&map, &player.getPosition(), angle, &rays[i], &cast_rays[i * 2]);
            rays[i].dist *= std::cos((angle - player.getRotation()) * DEG_TO_RAD);
            angle += da;
        }

        // calculating wall height
        sf::VertexArray walls(sf::Lines, 2 * WIDTH);
        for (int i = 0; i < WIDTH; i++) {
            float len = HEIGHT * 25 / rays[i].dist;         // TODO: change "25" to scale of map
            walls[i * 2] = sf::Vertex(sf::Vector2f(i, HEIGHT * .5 + len), sf::Vector2f(rays[i].tex_offset, 0));
            walls[i * 2 + 1] = sf::Vertex(sf::Vector2f(i, HEIGHT * .5 - len), sf::Vector2f(rays[i].tex_offset, wall_tex.getSize().y));
            if (rays[i].is_shaded) {
                walls[i * 2].color = walls[i * 2 + 1].color = sf::Color(200, 200, 200);      
            }
        }

        enemy.animate(dt.asSeconds(), player.getRotation());
        enemy.getVisible(player.getPosition(), player.getRotation(), rays);

        window.clear(sf::Color(0, 0, 255, 255));
        // window.draw(mapSprite);
        // window.draw(cast_rays);
        // window.draw(player);
        // window.draw(walls, &wall_tex);
        wall_target.clear();
        wall_target.draw(walls, &wall_tex);
        wall_target.display();
        sf::Sprite wall_sprite(wall_target.getTexture());
        window.draw(wall_sprite);
        window.draw(enemy);
        window.display();
    }
    return 0;
}
