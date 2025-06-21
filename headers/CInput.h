#ifndef CINPUT_H
#define CINPUT_H
#include <SFML/Graphics.hpp>

class CInput
{
public:
    bool left = false;  // Left key pressed
    bool right = false; // Right key pressed
    bool up = false;    // Up key pressed
    bool down = false;  // Down key pressed
    bool shoot = false; // shoot key pressed

public:
    CInput() = default;
    ~CInput() = default;
};

#endif