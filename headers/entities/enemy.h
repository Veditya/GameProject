#ifndef ENEMY_H
#define ENEMY_H
#include "entity.h"
#include "headers/components/collider.h"
#include "headers/components/animation.h"
#include <SFML/Graphics.hpp>

class Enemy : public Entity<sf::RectangleShape, Collider, Animation>
{
public:
    Enemy();
    ~Enemy();
};

#endif