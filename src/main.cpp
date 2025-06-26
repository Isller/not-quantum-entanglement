#include "particle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

sf::Vector2f line1Start;
sf::Vector2f line1End;
sf::Vector2f line2Start;
sf::Vector2f line2End;

sf::Color blue = sf::Color::Cyan;
sf::Color purple = sf::Color(255, 179, 216, 255);

sf::Vector2f winDim{400, 400};
sf::Vector2i dragOffSet1, dragOffSet2;

float radius{150};

bool dragging = false;
bool entangeled = false;

int main()
{
    sf::ContextSettings setting;
    setting.antiAliasingLevel = 8;

    auto window1 = sf::RenderWindow(sf::VideoMode({static_cast<sf::Vector2u>(winDim)}), "Particle 1", sf::Style::Default, sf::State::Windowed, setting);
    auto window2 = sf::RenderWindow(sf::VideoMode({static_cast<sf::Vector2u>(winDim)}), "Particle 2", sf::Style::Default, sf::State::Windowed, setting);

    window1.setFramerateLimit(60);
    window2.setFramerateLimit(60);

    window1.setPosition({50, 300});
    window2.setPosition({750, 300});

    sf::CircleShape core1(0);
    core1.setPosition({winDim.x / 2, winDim.y / 2.f});
    sf::CircleShape core2(0);
    core2.setPosition({winDim.x / 2, winDim.y / 2.f});
    sf::CircleShape sub_core1(0);
    sf::CircleShape sub_core2(0);

    // Particles
    Particle wave_particle_1(window1, {winDim.x / 2, winDim.y / 2}, static_cast<sf::Vector2u>(winDim), 500, 200, blue, 256, 400, 0);

    Particle wave_particle_2(window2, {winDim.x / 2, winDim.y / 2}, static_cast<sf::Vector2u>(winDim), 500, 200, purple, 256, 400, 0);

    Particle sub_wave_particle_1(window1, {line1End}, static_cast<sf::Vector2u>(winDim), 500, 200, purple, 256, 400, 0);

    Particle sub_wave_particle_2(window2, {line2End}, static_cast<sf::Vector2u>(winDim), 500, 200, blue, 256, 400, 0);

    Particle core_wave_particle_1(window1, {winDim.x / 2, winDim.y / 2}, static_cast<sf::Vector2u>(winDim), 100, 50, sf::Color::White, 256, 400, 0);

    Particle sub_core_wave_particle_1(window1, {line1End}, static_cast<sf::Vector2u>(winDim), 100, 50, sf::Color::White, 256, 400, 0);

    Particle core_wave_particle_2(window2, {winDim.x / 2, winDim.y / 2}, static_cast<sf::Vector2u>(winDim), 100, 50, sf::Color::White, 256, 400, 0);

    Particle sub_core_wave_particle_2(window2, {line2End}, static_cast<sf::Vector2u>(winDim), 100, 50, sf::Color::White, 256, 400, 0);

    sf::Vector2f line1Start{core1.getPosition().x, core1.getPosition().x};
    sf::Vector2f line1End{-window1.getPosition().x + window2.getPosition().x + core2.getPosition().x,
                          -window1.getPosition().y + window2.getPosition().y + core2.getPosition().y};
    sf::Vector2f line2Start{core2.getPosition().x, core2.getPosition().x};
    sf::Vector2f line2End{-window2.getPosition().x + window1.getPosition().x + core1.getPosition().x,
                          -window2.getPosition().y + window1.getPosition().y + core1.getPosition().y};

    std::array line1 = {sf::Vertex{sf::Vector2f(line1Start), sf::Color::Cyan}, sf::Vertex{sf::Vector2f(line1End), sf::Color::Magenta}};

    std::array line2 = {sf::Vertex{sf::Vector2f(line2Start), sf::Color::Magenta}, sf::Vertex{sf::Vector2f(line2End), sf::Color::Cyan}};

    while (window1.isOpen() || window2.isOpen())
    {
        line1Start = {core1.getPosition().x, core1.getPosition().x};
        line1End = {-window1.getPosition().x + window2.getPosition().x + core2.getPosition().x,
                    -window1.getPosition().y + window2.getPosition().y + core2.getPosition().y};
        line2Start = {core2.getPosition().x, core2.getPosition().x};
        line2End = {-window2.getPosition().x + window1.getPosition().x + core1.getPosition().x,
                    -window2.getPosition().y + window1.getPosition().y + core1.getPosition().y};

        line1[0].position = line1Start;
        line1[1].position = line1End;
        line2[0].position = line2Start;
        line2[1].position = line2End;

        sub_core1.setPosition(line2End);
        sub_core2.setPosition(line1End);
        sub_wave_particle_1.setPosition(line1End);
        sub_wave_particle_2.setPosition(line2End);
        sub_core_wave_particle_1.setPosition(line1End);
        sub_core_wave_particle_2.setPosition(line2End);

        sf::Vector2f subPos1(line1End.x - radius, line1End.y - radius);
        sf::Vector2f subPos2(line2End.x - radius, line2End.y - radius);

        sf::Vector2i mouseGlobalPos = sf::Mouse::getPosition();
        while (const std::optional event1 = window1.pollEvent())
        {
            if (event1->is<sf::Event::Closed>())
            {
                window1.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
        {
            window1.close();
            window2.close();
        }

        while (const std::optional event2 = window2.pollEvent())
        {
            if (event2->is<sf::Event::Closed>())
            {
                window2.close();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (!dragging)
            {
                sf::Vector2i winPos1 = window1.getPosition();
                sf::Vector2i winPos2 = window2.getPosition();

                if (sf::Mouse::getPosition().x >= window1.getPosition().x &&
                        sf::Mouse::getPosition().x <= window1.getPosition().x + winDim.x &&
                        sf::Mouse::getPosition().y >= window1.getPosition().y &&
                        sf::Mouse::getPosition().y <= window1.getPosition().y + winDim.y ||
                    sf::Mouse::getPosition().x >= window2.getPosition().x &&
                        sf::Mouse::getPosition().x <= window2.getPosition().x + winDim.x &&
                        sf::Mouse::getPosition().y >= window2.getPosition().y &&
                        sf::Mouse::getPosition().y <= window2.getPosition().y + winDim.y)
                {
                    dragging = true;
                    dragOffSet1 = mouseGlobalPos - winPos1;
                    dragOffSet2 = mouseGlobalPos - winPos2;
                }
            }

            if (dragging)
            {
                if (window1.hasFocus())
                    window1.setPosition(mouseGlobalPos - dragOffSet1);
                else if (window2.hasFocus())
                    window2.setPosition(mouseGlobalPos - dragOffSet2);
            }
        }
        else
        {
            dragging = false;
        }

        if ((core1.getPosition().x - sub_core2.getPosition().x <= 50 &&
             core1.getPosition().x - sub_core2.getPosition().x >= -50 &&
             core1.getPosition().y - sub_core2.getPosition().y <= 50 &&
             core1.getPosition().y - sub_core2.getPosition().y >= -50) ||
            (core1.getPosition().x - sub_core1.getPosition().x <= 50 &&
             core1.getPosition().x - sub_core1.getPosition().x >= -50 &&
             core1.getPosition().y - sub_core1.getPosition().y <= 50 &&
             core1.getPosition().y - sub_core1.getPosition().y >= -50))
            entangeled = true;

        window1.clear();
        window2.clear();

        sub_wave_particle_1.render(window1);
        wave_particle_1.render(window1);

        sub_wave_particle_2.render(window2);
        wave_particle_2.render(window2);

        if (entangeled)
        {
            window1.draw(line1.data(), line1.size(), sf::PrimitiveType::Lines);
            window2.draw(line2.data(), line1.size(), sf::PrimitiveType::Lines);
            core_wave_particle_1.render(window1);
            sub_core_wave_particle_1.render(window1);
            core_wave_particle_2.render(window2);
            sub_core_wave_particle_2.render(window2);
            wave_particle_2.setAngle(-0.03);
            sub_wave_particle_1.setAngle(-0.03);
        }

        window1.display();
        window2.display();

        wave_particle_1.setAngle(0.03);
        sub_wave_particle_2.setAngle(0.03);
        core_wave_particle_1.setAngle(0.03);
        core_wave_particle_2.setAngle(-0.03);
        sub_core_wave_particle_1.setAngle(-0.03);
        sub_core_wave_particle_2.setAngle(0.03);
    }
}
