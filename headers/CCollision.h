#ifndef CCOLLISION_H
#define CCOLLISION_H
#include <SFML/Graphics.hpp>

class CCollision
{
public:
    float radius; // Radius for circular collision detection

public:
    CCollision(float r) : radius(r) {}
};

#endif