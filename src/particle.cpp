#include "particle.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

sf::Vector2f Particle::projection(sf::Vector2f pos, const vec3 &p, float fov, float viewDist, sf::Vector2u winDim)
{
    float factor = fov / (p.z + viewDist);
    float x = p.x * factor + pos.x;
    float y = p.y * factor + pos.y;
    return {x, y};
}

Particle::vec3 Particle::rotateY(const vec3 &p, float angle)
{
    float sinA = std::sin(angle);
    float cosA = std::cos(angle);
    return {p.x * cosA - p.z * sinA, p.y, p.x * sinA + p.z * cosA};
}

void Particle::coordGen()
{

    for (int i = 0; i < m_particles; ++i)
    {
        float phi = std::acos(2.0f * static_cast<float>(rand()) / RAND_MAX - 1.0f);
        float theta = static_cast<float>(rand()) / RAND_MAX * 2 * pi;
        float x = m_radius * std::sin(phi) * std::cos(theta);
        float y = m_radius * std::sin(phi) * std::sin(theta);
        float z = m_radius * std::cos(phi);
        points.push_back({x, y, z});
    }
}

void Particle::setPosition(sf::Vector2f pos)
{
    m_pos = pos;
}

void Particle::setAngle(float angle)
{
    m_angle += angle;
}

void Particle::setFov(float fov)
{
    m_fov = fov;
}

void Particle::setViewDist(float viewDist)
{
    m_viewDist = viewDist;
}

void Particle::render(sf::RenderWindow &window)
{
    for (const auto &p : points)
    {
        vec3 rotated = rotateY(p, m_angle);
        sf::Vector2f projected = projection(m_pos, rotated, m_fov, m_viewDist, m_winDim);
        sf::CircleShape dot(0.5);
        dot.setFillColor(m_color);
        dot.setPosition(projected);
        window.draw(dot);
    }
}

Particle::Particle(sf::RenderWindow &window,sf::Vector2f pos, sf::Vector2u winDim, int particles, float radius, sf::Color color, float fov,float viewDist, float angle)
    : m_pos{pos}, m_winDim{winDim}, m_particles{particles}, m_radius{radius}, m_color{color}, m_fov{fov}, m_viewDist{viewDist}, m_angle{angle}
{
    coordGen();
}
