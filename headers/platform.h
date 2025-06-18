#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML\Graphics.hpp>
#include "collider.h"

class Platform
{
public:
    sf::RectangleShape body;
    Collider *collider;

public:
    Platform(sf::RectangleShape _body);
    ~Platform();
    void setCollider(Collider *_collider);
};

#endif