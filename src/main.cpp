#include <SFML/Graphics.hpp>
#include <iostream>
#include <../headers/animation.h>
#include <../headers/collider.h>
#include <../headers/player.h>
#include <../headers/platform.h>
// #include <TGUI/TGUI.hpp>

static float VIEW_HEIGHT = 512.0f;

int main()
{
    // window
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML-window", sf::Style::Close | sf::Style::Resize);

    // View
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    // player-section
    sf::RectangleShape square(sf::Vector2f(100.0f, 100.0f));
    sf::Texture pokemon;
    if (!pokemon.loadFromFile("assets/pokemon.png"))
        return -1;
    square.setTexture(&pokemon);

    Player player(square);
    player.setAnimation(new Animation(&pokemon, sf::Vector2u(4, 4), 0.3f));
    player.setCollider(new Collider(player.body));

    // platform section
    sf::RectangleShape sqr(sf::Vector2f(100.0f, 100.0f));
    sqr.setFillColor(sf::Color::White);
    sqr.setPosition(sf::Vector2f(250.0f, 250.0f));
    Platform platform1(sqr);
    platform1.setCollider(new Collider(platform1.body));

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
            if (_event.type == _event.Closed)
            {
                float aspectRatio = (float)window.getSize().x / (float)window.getSize().y; // of window
                view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
            }
        }

        player.update(deltaTime);

        // collision processing
        platform1.collider->checkCollision(player.collider, 0.01f);

        player.body.setTextureRect(player.animation->uvRect); // choose texture of input movement
        // view.setCenter(player.body.getPosition());

        window.clear();
        // window.setView(view);
        window.draw(player.body);
        window.draw(platform1.body);
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

8.) View: is a 2D camera.

9.) Collision


*/