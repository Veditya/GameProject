#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include "collider.h"
#include "animation.h"

class Player
{
public:
    sf::RectangleShape body;
    Collider *collider;
    Animation *animation;

public:
    Player(sf::RectangleShape _body);
    ~Player();

    void setCollider(Collider *_collider);
    void setAnimation(Animation *_animation);
    void update(float deltaTime);
};

#endif