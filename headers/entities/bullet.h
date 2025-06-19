#ifndef BULLET_H
#define BULLET_H
#include "entity.h"
#include "headers/components/collider.h"
#include "headers/components/animation.h"
#include <SFML/Graphics.hpp>

class Bullet : public Entity<sf::CircleShape, Collider, Animation>
{
private:
    int ttl;

public:
    Bullet();
    ~Bullet();

    void vanish();
};

#endif