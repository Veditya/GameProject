#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML\Graphics.hpp>

class Animation
{

private:
    // for frame texture
    sf::Vector2u imageCount;   //[frameRows,frameCols]
    sf::Vector2u currentImage; //[charRow,charCol]

    // for speed purpose
    float totalTime;  // time elapsed since last image
    float switchTime; // amount of time to switch to next frame

    // for display purpose
public:
    sf::IntRect uvRect;

public:
    Animation(sf::Texture *texture, sf::Vector2u _imageCount, float _switchTime);
    ~Animation();
    void update(int row, float deltaTime);
};

#endif