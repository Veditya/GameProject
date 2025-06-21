#ifndef CLIFESPAN_H
#define CLIFESPAN_H
#include <SFML/Graphics.hpp>

class CLifespan
{
public:
    float remainingTime = 0.0f; // Remaining time in milliseconds

public:
    CLifespan(int _total) : remainingTime(_total) {}
};

#endif