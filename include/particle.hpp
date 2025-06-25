#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

class Particle
{
  private:
    sf::Color m_color;
    sf::Vector2u m_winDim;
    sf::Vector2f m_pos;
    int m_particles{2000};
    float m_radius{200};
    float m_fov{256};
    float m_viewDist{400};
    float m_angle{0};
    const float pi = 3.14159265358979323846;

    struct vec3
    {
        float x, y, z;
    };
    std::vector<vec3> points;

    sf::Vector2f projection(sf::Vector2f pos,const vec3 &p, float fov, float viewDist, sf::Vector2u winDim);

    vec3 rotateY(const vec3 &p, float angle);

    void coordGen();

  public:
    Particle(sf::RenderWindow& window,sf::Vector2f pos, sf::Vector2u winDim, int particles, float radius, sf::Color color, float fov, float viewDist, float angle);

    void setPosition(sf::Vector2f pos);
    void setAngle(float angle);
    void setFov(float fov);
    void setViewDist(float viewDist);

    void render(sf::RenderWindow &window);
};
