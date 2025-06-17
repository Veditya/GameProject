#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI + SFML");
    tgui::Gui gui(window);

    // Create a button
    auto button = tgui::Button::create("Click Me");
    button->setPosition(100, 100);
    button->setInheritedFont("assets/DejaVuSans.ttf");
    button->onPress([] {
        std::cout << "Button clicked!\n";
    });
    gui.add(button);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        gui.draw();
        window.display();
    }

    return 0;
}