// #include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>
#include <string>
#include "../engine/raycaster.h"

class Enemy : public sf::Drawable, public sf::Transformable {
  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture m_texture;
    sf::VertexArray verticies;

    // these are seperate from the sprites position and angle on the screen
    float angle;
    sf::Vector2f position;

  public:
    Enemy(std::string tex_name, sf::Vector2f pos);
    void getVisible(const sf::Vector2f& cam_pos, float cam_angle, const std::vector<Ray>& rays);
};