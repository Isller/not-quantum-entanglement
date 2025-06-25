#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

sf::Vector2u winDim{400, 400};
int particles{2000};
float radius{200};
float fov{256};
float viewDist{400};
constexpr float pi = 3.14159265358979323846;

struct vec3
{
    float x, y, z;
};

sf::Vector2f projection(const vec3 &p, float fov, float viewDist, sf::Vector2u winDim)
{
    float factor = fov / (p.z + viewDist);
    float x = p.x * factor /* + static_cast<float>(winDim.x) / 2 */;
    float y = p.y * factor + static_cast<float>(winDim.y) / 2;
    return {x, y};
}

vec3 rotateY(const vec3 &p, float angle)
{
    float sinA = std::sin(angle);
    float cosA = std::cos(angle);
    return {p.x * cosA - p.z * sinA, p.y, p.x * sinA + p.z * cosA};
}

int main()
{
    sf::ContextSettings setting;
    setting.antiAliasingLevel = 8;

    auto window = sf::RenderWindow(sf::VideoMode({static_cast<sf::Vector2u>(winDim)}), "Particle 1", sf::Style::None,
                                   sf::State::Windowed, setting);
    window.setFramerateLimit(30);

    std::vector<vec3> points;

    for (int i = 0; i < particles; ++i)
    {
        float phi = std::acos(2.0f * static_cast<float>(rand()) / RAND_MAX - 1.0f);
        float theta = static_cast<float>(rand()) / RAND_MAX * 2 * pi;
        float x = radius * std::sin(phi) * std::cos(theta);
        float y = radius * std::sin(phi) * std::sin(theta);
        float z = radius * std::cos(phi);
        points.push_back({x, y, z});
    }

    float angle = 0.0f;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        for (const auto &p : points)
        {
            vec3 rotated = rotateY(p, angle);
            sf::Vector2f projected = projection(rotated, fov, viewDist, winDim);
            sf::CircleShape dot(0.5);
            dot.setFillColor(sf::Color(255,255,255,150));
            dot.setPosition(projected);
            window.draw(dot);
        }
        window.display();
        angle += 0.03f;
    }

    return 0;
}
