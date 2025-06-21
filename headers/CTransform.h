#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include <SFML/Graphics.hpp>

class CTransform
{
public:
    sf::Vector2f position = {0.0, 0.0};
    sf::Vector2f velocity = {0.0, 0.0};
    float angle = 0.0;

public:
    CTransform(const sf::Vector2f &pos, const sf::Vector2f &vel, float ang) : position(pos), velocity(vel), angle(ang) {}

    ~CTransform() = default;
};

#endif