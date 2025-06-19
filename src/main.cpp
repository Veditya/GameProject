#include <SFML/Graphics.hpp>
// #include <imgui-SFML.h>
// #include <imgui.h>
// #include <iostream>
// using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(720.0f, 720.0f), "sfml window", sf::Style::Close | sf::Style::Default);
    // window.setFramerateLimit(60);

    // ImGui::SFML::Init(window);

    // sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            // ImGui::SFML::ProcessEvent(evnt);
            if (evnt.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        // ImGui::SFML::Update(window, deltaClock.restart());

        window.clear(sf::Color(30, 30, 30));
        // ImGui::SFML::Render(window);
        window.display();
    }
    // ImGui::SFML::Shutdown(window);
    return 0;
}