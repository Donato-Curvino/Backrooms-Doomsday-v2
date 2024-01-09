#include "Enemy.h"
#include <iostream>
#include <cmath>
#include <SFML/Graphics/Vertex.hpp>

#ifndef M_PI
#define M_PI 3.14159265
#endif

#define WIDTH 1280
#define HEIGHT 720
#define FOV 30
#define DEG_TO_RAD 0.0174533

Enemy::Enemy(std::string tex_name, sf::Vector2f pos = sf::Vector2f(0.0, 0.0)) 
  : position{pos}, angle{0.0} {
    if (!m_texture.loadFromFile("assets/sprites/" + tex_name))
        std::cout << "Error loading texture: assets/sprites/" + tex_name << std::endl;

    verticies.setPrimitiveType(sf::Triangles);
}

bool isVisible(int x, float d, const std::vector<Ray>& rays) {
    // std::cout << x << " " << d << " | ";
    if (x < 0 || x >= WIDTH) return false;
    return d < rays[x].dist;
}

void Enemy::getVisible(const sf::Vector2f& cam_pos, float cam_angle, const std::vector<Ray>& rays) {
    // get calculated position and size on screen
    sf::Vector2f offset = cam_pos - position;
    float rel_angle = std::atan2(offset.y, offset.x) + M_PI - cam_angle * DEG_TO_RAD;
    float dist = std::sqrt(offset.x * offset.x + offset.y * offset.y) * std::cos(0);
    int size = HEIGHT * 25 / dist;

    sf::Vector2f screen_pos; 
    screen_pos.x = WIDTH * .5 + (rel_angle * WIDTH * .5 / (FOV * DEG_TO_RAD));
    screen_pos.y = HEIGHT * .5 + size;

    // get height mask

    // set vertex array based on height mask
    verticies.clear();                 // TODO: vector gets too big when too close
    int x = screen_pos.x - size;
    bool visible = false;
    // std::cout << screen_pos.x << " " << size << " | " << x;
    for (int i = 0; i < size * 2; i++) {
        float tex_x = ((float)i / (size * 2)) * m_texture.getSize().x;
        // std::cout << x << " ";
        if (isVisible(x, dist, rays)) {
            // std::cout << dist << " ";
            if (!visible) {
                // std::cout << "start -> ";
                visible = true;
                verticies.append(sf::Vertex(sf::Vector2f(x, screen_pos.y - 2 * size), sf::Vector2f(tex_x, 0)));
                verticies.append(sf::Vertex(sf::Vector2f(x, screen_pos.y), sf::Vector2f(tex_x, m_texture.getSize().y - 1)));
            }
        } else if (visible) {
            // std::cout << "end -> ";
            visible = false;
            if (verticies.getVertexCount() < 2)
                continue;
            verticies.append(sf::Vertex(sf::Vector2f(x, screen_pos.y - 2 * size), sf::Vector2f(tex_x, 0)));
            verticies.append(verticies[verticies.getVertexCount() - 2]);
            verticies.append(verticies[verticies.getVertexCount() - 2]);
            verticies.append(sf::Vertex(sf::Vector2f(x, screen_pos.y), sf::Vector2f(tex_x, m_texture.getSize().y - 1)));
        }
        x++;
    }
    if (visible) {
        verticies.append(sf::Vertex(sf::Vector2f(x, screen_pos.y - 2 * size), sf::Vector2f(m_texture.getSize().x - 1, 0)));
        verticies.append(verticies[verticies.getVertexCount() - 2]);
        verticies.append(verticies[verticies.getVertexCount() - 2]);
        verticies.append(sf::Vertex(sf::Vector2f(x, screen_pos.y), sf::Vector2f(m_texture.getSize().x - 1, m_texture.getSize().y - 1)));
    }
    // std::cout << " -> " << x << std::endl;
    // std::cout << std::endl;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(verticies, &m_texture);
}
