#ifndef CSCORE_H
#define CSCORE_H
#include <SFML/Graphics.hpp>

class CScore
{
public:
    int score = 0;

public:
    CScore() = default;
    ~CScore() = default;
    void reset()
    {
        score = 0;
    }
};

#endif