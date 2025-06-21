#ifndef CSHAPE_H
#define CSHAPE_H
#include <SFML/Graphics.hpp>

class CShape
{
public:
    sf::CircleShape body;

public:
    CShape(float r, size_t p, const sf::Color &fill, const sf::Color &outline, float thick) : body(r, p)
    {
        body.setFillColor(fill);
        body.setOutlineColor(outline);
        body.setOutlineThickness(thick);
        body.setOrigin(r, r);
    }
};

#endif