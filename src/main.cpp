
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "ImGui + SFML Example");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    bool show_demo = true;
    float my_float = 0.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, Debugger");
        ImGui::Text("This is ImGui running inside SFML!");
        ImGui::Checkbox("Show ImGui Demo", &show_demo);
        ImGui::SliderFloat("My Float", &my_float, 0.0f, 1.0f);
        ImGui::End();

        if (show_demo)
            ImGui::ShowDemoWindow();

        window.clear(sf::Color(30, 30, 30));
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
