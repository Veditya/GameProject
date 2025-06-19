#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include "headers/components/collider.h"
#include "headers/components/animation.h"
#include <SFML/Graphics.hpp>

class Player : public Entity<sf::CircleShape, Collider, Animation, sf::Vector2f>
{
private:
    int kills;
    bool mode;

public:
    Player();
    ~Player();

    void countKills();
    int getKills();
    bool checkMode();
    void update(float deltaTime);
    void Shoot(sf::Vector2f mousePos);
};

#endif