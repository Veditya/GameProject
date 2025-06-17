#include <SFML/Graphics.hpp>
#include <iostream>
#include <../headers/animation.h>
// #include <TGUI/TGUI.hpp>

int main()
{
    // window
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML-window", sf::Style::Close);

    // player
    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
    player.setFillColor(sf::Color::White);

    // player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/pokemon.png"))
        return -1;
    player.setTexture(&playerTexture);

    // player animation
    Animation animation(&playerTexture, sf::Vector2u(4, 4), 0.3f);
    float deltaTime = 0.0f;
    sf::Clock clock;

    // run gameloop
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event _event;
        while (window.pollEvent(_event))
        {
            if (_event.type == _event.Closed)
            {
                window.close();
            }
        }
        // keyboard input processing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            animation.update(1, deltaTime);
            player.move(-0.1f, 0.0f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            animation.update(2, deltaTime);
            player.move(0.05f, 0.0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            animation.update(3, deltaTime);
            player.move(0.0, -0.05f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            animation.update(0, deltaTime);
            player.move(0.0, 0.05f);
        }

        player.setTextureRect(animation.uvRect); // choose texture of input movement

        window.clear();
        window.draw(player);
        window.display();
    }
    return 0;
}

/*
GRAPHICS MODULE
-----------------------------------------------------------------------------------------
1.)window creation, open and close:

sf::RenderWindow window(sf::VideoMode(512,512),"SFML-window", sf::Style::Close | sf::Style::Titlebar);
    //run gameloop
    while(window.isOpen())
    {
        sf::Event _event;
        while (window.pollEvent(_event))
        {
            if(_event.type == _event.Closed)
            {
                window.close();
            }
        }
    }
----------------------------------------------------------------------------------------
2.) Events: {window_resize, userinput, }

switch (_event.type)
{
    case sf::Event::Closed:
    {
        window.close();
        break;
    }
    case sf::Event::Resized:
    {
        int newWidth = _event.size.width;
        int newHeight = _event.size.height;
        std::cout << "[" << newWidth << "," << newHeight << "]" << std::endl;
        break;
    }
    case sf::Event::TextEntered:
    {
        if (_event.text.unicode < 122)
        {
            std::cout << _event.text.unicode;
        }
    }
}
-------------------------------------------------------------------------------------------
3.) Shapes:

sf::RectangleShape square(sf::Vector2f(width,height));
square.setFillColor(sf::Color::Red);
window.draw(square);
window.display();
-----------------------------------------------------------------------------------------
4.)moving player using Keyboard input

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            square.move(-0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            square.move(0.1f, 0.0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            square.move(0.0, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            square.move(0.0, 0.1f);
        }

        window.clear();
        window.draw(square);
        window.display();
---------------------------------------------------------------------------------------------
5.) Mouse input:

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            square.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }
--------------------------------------------------------------------------------------------
6.) Textures:
sf::Texture playerTexture;
    playerTexture.loadFromFile("assets/kakashi.png");
    square.setTexture(&playerTexture);

texture Rectangle  : used to display only a part of the texture

player.setTextureRect(fullSize.x,fullSize.y,partialSize.x,partialSize.y);
------------------------------------------------------------------------------------------
7.) Animation:



*/