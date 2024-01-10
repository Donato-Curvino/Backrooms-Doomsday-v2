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
    sf::Vector2u tile_start;
    sf::Vector2u tile_size; 
    float frame_time;
    float active_frame_time;
    bool mirrored;

    // these are seperate from the sprites position and angle on the screen
    float angle;
    sf::Vector2f position;

  public:
    Enemy(std::string tex_name, sf::Vector2u t_sz, sf::Vector2f pos);
    void getVisible(const sf::Vector2f& cam_pos, float cam_angle, const std::vector<Ray>& rays);
    // TODO: animate
    void animate(float dt);
    // TODO: rotate in 3D
};