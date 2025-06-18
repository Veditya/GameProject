#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML\Graphics.hpp>

class Collider
{
public:
    sf::RectangleShape &body;

public:
    Collider(sf::RectangleShape &_body);

    ~Collider();

    bool checkCollision(Collider *other, float push);

    void move(float dx, float dy);

    sf::Vector2f GetPosition();

    sf::Vector2f GetHalfSize();
};

#endif